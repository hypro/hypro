#!/usr/bin/env python3
"""
Run multiple benchmarks consecutively.
Required arguments (positional):
    tool: The path to the tool (hydra) executable
    settings: Path to a text file that contains the command line
        arguments for the benchmarks to run. For example, if hydra
        should be called with
        `./bin/hydra -m bball.model -r support_function --setting BoxLinearOptimizationOn`
        then the settings file should contain a line
        `-m bball.model -r support_function --setting BoxLinearOptimizationOn`
        Paths to the model (-m) should be given relative to the settings file.
        Empty lines and lines that start with '#' are ignored.
    output: Path to a file to write the output to. The output will
        be given in csv-format with the measured time, safety result and
        error messages if an error occured.
Optional arguments:
    -t <seconds> A time limit in seconds. If the execution of a benchmark
        model takes longer than the given time it will be terminated.
        This is indicated in the output.
    -m <megabyte> A memory limit in megabyte. If the execution of a benchmark
        model uses more space than allowed it will be terminated.
        This is NOT indicated in the output but will cause an error 
        in the tool execution and the error message has to be interpreted.
    --verbose Verbose execution: The output of the tool will be printed.
    --benchmark Faster execution: The output is written to a file and analyzed
        after execution is complete. This lowers runtime but disables
        the timeout and verbose option as well as skipping functionality.
        (These arguments are ignored.)
Example calls:
    (1) `python3 run_hydra.py ../bin/hydra input/settings results.csv -t 1200 -m 16000 --verbose`
        Call for testing models with a timeout of 20min and memout of 16gb with verbose mode.
    (2) `python3 run_hydra.py ../bin/hydra input/settings results.csv --benchmark`
        Call for benchmarking and faster execution. Adding the timeout or verbose option
        will have no effect.
"""
import os
import sys
import argparse
import subprocess
import time
import re
import csv
import json
import select
import fcntl
import resource
import tempfile

def limit_mem(memLimit):
    """Limit the memory-usage to memLimit (in MB)."""
    if memLimit:
        memLimit = memLimit * 1024 * 1024
        resource.setrlimit(
            resource.RLIMIT_AS, (memLimit, resource.RLIM_INFINITY))

def read_file(fileName):
    """Return the lines of the file as a list. Lines that start with
    '#' and empty lines are ignored. Multiple whitespaces are removed
    from lines and lines are stripped."""
    with open(fileName, 'r') as f:
        lines = [" ".join(line.split()) for line in f]
    return list(filter(lambda l: l != '' and not l.startswith('#'), lines))

class Results(object):
    """Stores results from a model execution."""
    def __init__(self, modelName, instance=''):
        self.modelName = modelName
        self.instance = instance
        self.startTime = -1
        self.endTime = -1
        self.timeout = False
        self.skipped = False
        self.safetyResult = None
        self.error = False
        self.errorMsg = None

    def set_error(self, errorMsg):
        self.error = True
        self.errorMsg = errorMsg.strip()

    def get_csv_header():
        h = ['Tool', 'Benchmark ID', 'Instance', 'Verified', 'Time']
        return h

    def get_csv_footer():
        f = ['End of HyDRA']
        return f

    def to_csv(self):
        line = [
            'HyDRA',
            self.modelName.replace('.model',''),
            self.instance,
            '1' if self.safetyResult == 'Safe' else '0',
            str(self.endTime - self.startTime) \
                if self.endTime > 0 and self.startTime > 0 else ''
            ]
        return line

    def to_string(self):
        runningTime = str(self.endTime - self.startTime) \
                      if self.endTime > 0 and self.startTime > 0 else ''
        head = self.modelName + ": "
        body = [
            self.safetyResult or "No safety result",
            "running time: " + runningTime,
            "Error: " + self.errorMsg if self.error else None
        ]
        return head + ", ".join(filter(None, body))

class Model(object):
    def __init__(self, clString, name=None):
        self.clString = clString
        self.name = name or self._get_name(clString)

    def _get_name(self, clString):
        clArgs = clString.split(' ')
        name = os.path.basename(clArgs[clArgs.index('-m')+1])
        return name

    def run(self, benchmark, *args, **kwargs):
        """Run the model with the given parameters and return the results."""
        result = Results(self.name)
        result.startTime = time.time()
        if benchmark:
            print('[+] Running %s.'%self.name)
            self._run_benchmark(result, *args, **kwargs)
        else:
            print('[+] Running %s. Press enter to skip.'%self.name)
            self._run_test(result, *args, **kwargs)
        result.endTime = time.time()
        return result

    def _run_test(self, result, tool, timeLimit, memLimit, verbose):
        params = self.get_process_params(tool)
        process = subprocess.Popen(
            params, stdout=subprocess.PIPE, stderr=subprocess.PIPE, 
            universal_newlines=True, preexec_fn=lambda: limit_mem(memLimit))
        # Make stdout non-blocking to enable reading during execution (to avoid
        # filling the pipe and losing output), while also checking for timeouts 
        # and skips.
        pStdoutFlags = fcntl.fcntl(process.stdout, fcntl.F_GETFL)
        fcntl.fcntl(process.stdout, fcntl.F_SETFL, pStdoutFlags | os.O_NONBLOCK)

        while process.poll() is None:
            for line in process.stdout.readlines():
                self._parse_line(result, line, verbose)
            if self._check_skip(result):
                self._stop_run(process)
                print('[+] Skipped %s'%self.name)
            if self._check_timeout(result, timeLimit):
                print('[-] Timeout %s'%self.name)
                self._stop_run(process)
        # Read errors after process is done because stderr usually fits in 
        # the pipe.
        errors = process.stderr.readlines()
        if errors:
            print('[-] Errors during execution: ')
            result.set_error(errors[0])
            for line in errors:
                print(line, end='')
        return result

    def _run_benchmark(self, result, tool, timeLimit, memLimit, verbose):
        stdoutFile = tempfile.TemporaryFile(mode='w+')
        stderrFile = tempfile.TemporaryFile(mode='w+')
        params = self.get_process_params(tool)
        process = subprocess.Popen(
            params, stdout=stdoutFile, stderr=stderrFile, 
            universal_newlines=True, preexec_fn=lambda: limit_mem(memLimit))
        process.wait()
        stdoutFile.seek(0)
        stderrFile.seek(0)
        self._parse_output(result, stdoutFile, stderrFile)
        return result

    def _parse_output(self, result, stdoutFile, stderrFile):
        for line in stdoutFile:
            self._parse_line(result, line, False)
        errors = stderrFile.readlines()
        if errors:
            print('[-] Errors during execution: ')
            result.set_error(errors[0])
            for line in errors:
                print(line, end='')
        return result

    def get_process_params(self, tool):
        """Build subprocess parameters from clString and tool path.""" 
        hydraArgs = self.clString.split(' ')
        cmd = ['stdbuf', '-oL', tool] + hydraArgs
        return cmd

    def _stop_run(self, process):
        process.terminate()
        process.wait()
        return True    

    def _check_skip(self, result):
        """Check if enter was pressed to skip execution."""
        if select.select([sys.stdin], [], [], 0)[0] != []:
            sys.stdin.readline()
            result.skipped = True
            return True
        else:
            return False

    def _check_timeout(self, result, timeLimit):
        if timeLimit is None:
            return False
        elif time.time() - result.startTime > timeLimit:
            result.timeout = True
            return True        

    def _parse_line(self, result, line, verbose):
        if line.strip() == "Could not verify safety.":
            result.safetyResult = 'Unsafe'
        elif line.strip() == "The model is safe.":
            result.safetyResult = 'Safe'
        if verbose:
            print(line, end='')

def get_cli_args():
    parser = argparse.ArgumentParser(
        description='Run the models given in the settings file with the given '+\
        'tool and write the results to the output file.',
        epilog='Example call: %(prog)s ../bin/hydra input/settings results.csv '+\
        '-t 1200 -m 16000 --verbose')    
    parser.add_argument(
        'tool', metavar='path', help='Path to the tool executable')
    parser.add_argument(
        'settings', metavar='settings-file', 
        help='Filename that contains the command line arguments.')
    parser.add_argument(
        'output', metavar='output-file', 
        help='File to write results to (as csv).')
    parser.add_argument(
        '-t', dest='timeLimit', metavar='seconds', type=int, default=None,
        help='Time limit for a single model execution (in seconds).')
    parser.add_argument(
        '-m', dest='memLimit', metavar='megabyte', type=int, default=None,
        help='Memory limit for a single model execution (in mb).')
    parser.add_argument(
        '--verbose', action='store_true', 
        help='Write the tool-output to stdout.')
    parser.add_argument(
        '--benchmark', action='store_true',
        help='Option for benchmarking that enables faster execution '+\
             'by reading tool output after execution. Disables timeout and '+\
             'verbose option as well as skipping models.')
    args = parser.parse_args()
    return args

def main():
    args = get_cli_args()
    tool = os.path.abspath(os.path.expanduser(args.tool))
    settingsFile = os.path.abspath(os.path.expanduser(args.settings))
    settingsDir = os.path.dirname(settingsFile)
    outputFile = os.path.abspath(os.path.expanduser(args.output))
    os.chdir(settingsDir)
    settingsList = read_file(settingsFile)
    resultList = []
    for s in settingsList:
        m = Model(s)
        result = m.run(args.benchmark, tool, args.timeLimit, 
                       args.memLimit, args.verbose)
        resultList.append(result)    
    csvWriter = csv.writer(open(outputFile, 'w'), delimiter=';')
    #csvWriter.writerow(Results.get_csv_header())
    print("Results:")
    for result in resultList:
        csvWriter.writerow(result.to_csv())
        print(result.to_string())
    #csvWriter.writerow(Results.get_csv_footer())

if __name__=='__main__':
    main()
