#!/bin/bash 
 
# check whether user had supplied -h or --help . If yes display usage
if [[ ( $@ == "--help") ||  $@ == "-h" || $# -le 3 ]]; then 
	echo "Usage: $0 <acasxu|drones|thermostat|sonar> <exact|overapprox> <network> <input_property> [safety_property]"
	exit 0
fi

# check if a correct benchmark was specified
if [[ ($1 != "acasxu") && ($1 != "drones") && ($1 != "thermostat") && ($1 != "sonar") ]]; then
    echo "Error: benchmark $1 not found"
    echo "Usage: $0 <acasxu|drones|thermostat|sonar> <exact|overapprox> <network> <input_property> [safety_property]"
    exit 1
fi

# check if a correct reachability method was specified
if [[ ($2 != "exact") && ($2 != "overapprox") ]]; then
    echo "Not supported reachability method: $2"
    echo "Usage: $0 <acasxu|drones|thermostat|sonar> <exact|overapprox> <network> <input_property> [safety_property]"
    exit 1
fi

if [ $1 == "acasxu" ]; then
    NNET_FILE="../examples/nn_benchmarks/networks/nnet/acasxu/$3"
    if ! [[ -f $NNET_FILE ]]; then
        echo "Not valid neural network input file: $3"
        echo "Example: $0 $1 $2 ACASXU_experimental_v2a_2_4.nnet <input_property> <safety_property>"
        exit 2
    fi
    
    INPUT_PROP="../examples/nn_benchmarks/properties/acasxu/properties/$4"
    if ! [[ -f $INPUT_PROP ]]; then
        echo "Not valid input property file: $4"
        echo "Example: $0 $1 $2 $3 poly_prop3_input.in <safety_property>"
        exit 2
    fi

    SAFETY_PROP="../examples/nn_benchmarks/properties/acasxu/safe_sets/$5"
    if ! [[ -f $SAFETY_PROP ]]; then
        echo "Not valid safe set file: $5"
        echo "Example: $0 $1 $2 $3 $4 poly_prop3_safe.in"
        exit 2
    fi

    IS_UNBOUNDED=""
    if [ "$#" -gt 5 ] && [ "$6" = "unbounded" ]; then
        IS_UNBOUNDED="unbounded"
    else
        IS_UNBOUNDED=""
    fi

    BINARY_FILE="./bin/example_ACASbenchmark_verification"
    if ! [[ -f $BINARY_FILE ]]; then
        echo "Binary file $BINARY_FILE not found"
        echo "Compile the example first: \$ make example_ACASbenchmark_verification"
        exit 3
    fi

    CMD="$BINARY_FILE $2 $NNET_FILE $INPUT_PROP $SAFETY_PROP $IS_UNBOUNDED"
    eval "$CMD";

fi

if [ $1 == "drones" ]; then
    NNET_FILE="../examples/nn_benchmarks/networks/nnet/drones/$3"
    if ! [[ -f $NNET_FILE ]]; then
        echo "Not valid neural network input file: $3"
        echo "Example: $0 $1 $2 AC1.nnet <input_property> <safety_property>"
        exit 2
    fi

    INPUT_PROP="../examples/nn_benchmarks/properties/drones/properties/$4"
    if ! [[ -f $INPUT_PROP ]]; then
        echo "Not valid input property file: $4"
        echo "Example: $0 $1 $2 $3 prop_AC1_01.in <safety_property>"
        exit 2
    fi

    SAFETY_PROP="../examples/nn_benchmarks/properties/drones/safe_sets/$5"
    if ! [[ -f $SAFETY_PROP ]]; then
        echo "Not valid safe set file: $5"
        echo "Example: $0 $1 $2 $3 $4 safe_AC1_01.in"
        exit 2
    fi

    BINARY_FILE="./bin/example_drones_verification"
    if ! [[ -f $BINARY_FILE ]]; then
        echo "Binary file $BINARY_FILE not found"
        echo "Compile the example first: \$ make example_drones_verification"
        exit 3
    fi

    CMD="$BINARY_FILE $2 $NNET_FILE $INPUT_PROP $SAFETY_PROP"
    eval "$CMD";
fi

if [ $1 == "thermostat" ]; then
    NNET_FILE="../examples/nn_benchmarks/networks/nnet/thermostat/$3"
    if ! [[ -f $NNET_FILE ]]; then
        echo "Not valid neural network input file: $3"
        echo "Example: $0 $1 $2 fc_thermostat.nnet <input_property>"
        exit 2
    fi

    INPUT_PROP="../examples/nn_benchmarks/properties/thermostat/properties/$4"
    if ! [[ -f $INPUT_PROP ]]; then
        echo "Not valid input property file: $4"
        echo "Example: $0 $1 $2 $3 poly_thermostat.in"
        exit 2
    fi

    SAFETY_PROP="../examples/nn_benchmarks/properties/thermostat/safe_sets/$5"
    if ! [[ -f $SAFETY_PROP ]]; then
        echo "Not valid safe set file: $5"
        echo "Example: $0 $1 $2 $3 $4 safe_AC1_01.in"
        exit 2
    fi

    BINARY_FILE="./bin/example_thermostat_verification"
    if ! [[ -f $BINARY_FILE ]]; then
        echo "Binary file $BINARY_FILE not found"
        echo "Compile the example first: \$ make example_thermostat_verification"
        exit 3
    fi

    CMD="$BINARY_FILE $2 $NNET_FILE $INPUT_PROP $SAFETY_PROP"
    eval "$CMD";
fi

if [ $1 == "sonar" ]; then
    NNET_FILE="../examples/nn_benchmarks/networks/nnet/sonar/$3"
    if ! [[ -f $NNET_FILE ]]; then
        echo "Not valid neural network input file: $3"
        echo "Example: $0 $1 $2 sonar_detector.nnet <input_property>"
        exit 2
    fi

    INPUT_PROP="../examples/nn_benchmarks/properties/sonar/$4"
    if ! [[ -f $INPUT_PROP ]]; then
        echo "Not valid input property file: $4, format should be sonar_N_P.in, where N is the input number, and P is the ground truth label"
        echo "Example: $0 $1 $2 $3 sonar_37_R.in"
        exit 2
    fi

    BINARY_FILE="./bin/example_robustness"
    if ! [[ -f $BINARY_FILE ]]; then
        echo "Binary file $BINARY_FILE not found"
        echo "Compile the example first: \$ make example_robustness"
        exit 3
    fi

    CMD="$BINARY_FILE $2 $NNET_FILE $INPUT_PROP"
    eval "$CMD";
fi
