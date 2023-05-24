import os
import subprocess
from concurrent.futures import ThreadPoolExecutor

from tqdm import tqdm
import parse_results


def execute_command(command, output_file):
    with open(output_file, "w") as log_file:
        result = subprocess.run(command, stdout=log_file)
        if result.returncode != 0:
            print("Command execution failed for:", command)

def run_process(example: str, property: str, safe: str, nnet: str, output_overapproximate: str,
                output_exact: str) -> None:
    directory_path_overapproximate = os.path.dirname(output_overapproximate)
    directory_path_exact = os.path.dirname(output_exact)

    if not os.path.exists(directory_path_overapproximate):
        os.makedirs(directory_path_overapproximate)
    if not os.path.exists(directory_path_exact):
        os.makedirs(directory_path_exact)

    commands = [
        [example, "O", nnet, property, safe],
        [example, "E", nnet, property, safe]
    ]
    output_files = [output_overapproximate, output_exact]

    with ThreadPoolExecutor() as executor:
        futures = []
        for command, output_file in zip(commands, output_files):
            future = executor.submit(execute_command, command, output_file)
            futures.append(future)

        # Wait for all the processes to finish
        for future in futures:
            future.result()


def run_benchmarks():
    total_iterations = 5 * 9 + 4 * 9 + 45 - 3 + 45 - 3 + 1 + 1 + 1 + 1 + 1 + 1
    progress_bar = tqdm(total=total_iterations, desc=" Overall Progress")

    PROPERTY_PATH: str = os.path.join(os.getcwd(), "examples", "nn_prop_inputs", "acasxu")
    NNET_PATH: str = os.path.join(os.getcwd(), "examples", "nnet", "acasxu")
    OUTPUT_PATH: str = os.path.join(os.getcwd(), "evaluation")
    EXAMPLE: str = os.path.join(os.getcwd(), "build", "bin", "example_ACASbenchmarkVerification")

    tqdm.write("Property 1 (all 45 networks)")
    property_1: str = os.path.join(PROPERTY_PATH, "poly_prop1_5D_artificial_bounds.in")
    safe_1: str = os.path.join(PROPERTY_PATH, "poly_prop1_safe.in")
    for i in range(1, 6):
        for j in range(1, 10):
            # NNet
            nnet: str = os.path.join(NNET_PATH, f"ACASXU_experimental_v2a_{i}_{j}.nnet")
            output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_1", "over", f"nnet_{i}_{j}.log")
            output_exact: str = os.path.join(OUTPUT_PATH, "property_1", "exact", f"nnet_{i}_{j}.log")
            run_process(EXAMPLE, property_1, safe_1, nnet, output_overapproximate, output_exact)
            progress_bar.update(1)

    tqdm.write("Property 2 (for all x >=2 and y)")
    property_2: str = os.path.join(PROPERTY_PATH, "poly_prop2_5D_artificial_bounds.in")
    safe_2: str = os.path.join(PROPERTY_PATH, "poly_prop2_safe.in")
    for i in range(2, 6):
        for j in range(1, 9):
            # NNet
            nnet: str = os.path.join(NNET_PATH, f"ACASXU_experimental_v2a_{i}_{j}.nnet")
            output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_2", "over", f"nnet_{i}_{j}.log")
            output_exact: str = os.path.join(OUTPUT_PATH, "property_2", "exact", f"nnet_{i}_{j}.log")
            run_process(EXAMPLE, property_2, safe_2, nnet, output_overapproximate, output_exact)
            progress_bar.update(1)

    tqdm.write("Property 3 (all networks except N1,7 N1,8 N1,9)")
    property_3: str = os.path.join(PROPERTY_PATH, "poly_prop3_5D_artificial_bounds.in")
    safe_3: str = os.path.join(PROPERTY_PATH, "poly_prop3_safe.in")
    for i in range(1, 6):
        for j in range(1, 10):
            # Skip certain networks
            if i == 1 and j in [7, 8, 9]:
                continue
            # NNet
            nnet: str = os.path.join(NNET_PATH, f"ACASXU_experimental_v2a_{i}_{j}.nnet")
            output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_3", "over", f"nnet_{i}_{j}.log")
            output_exact: str = os.path.join(OUTPUT_PATH, "property_3", "exact", f"nnet_{i}_{j}.log")
            run_process(EXAMPLE, property_3, safe_3, nnet, output_overapproximate, output_exact)
            progress_bar.update(1)

    tqdm.write("Property 4 (all networks except N1,7 N1,8 N1,9)")
    property_4: str = os.path.join(PROPERTY_PATH, "poly_prop4_5D_artificial_bounds.in")
    safe_4: str = os.path.join(PROPERTY_PATH, "poly_prop4_safe.in")
    for i in range(1, 6):
        for j in range(1, 10):
            # Skip certain networks
            if i == 1 and j in [7, 8, 9]:
                continue
            # NNet
            nnet: str = os.path.join(NNET_PATH, f"ACASXU_experimental_v2a_{i}_{j}.nnet")
            output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_4", "over", f"nnet_{i}_{j}.log")
            output_exact: str = os.path.join(OUTPUT_PATH, "property_4", "exact", f"nnet_{i}_{j}.log")
            run_process(EXAMPLE, property_4, safe_4, nnet, output_overapproximate, output_exact)
            progress_bar.update(1)

    tqdm.write("Property 5 (only N1,1)")
    property_5: str = os.path.join(PROPERTY_PATH, "poly_prop5_5D_artificial_bounds.in")
    safe_5: str = os.path.join(PROPERTY_PATH, "poly_prop5_safe.in")
    nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_1_1.nnet")
    output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_5", "over", f"nnet_1_1.log")
    output_exact: str = os.path.join(OUTPUT_PATH, "property_5", "exact", f"nnet_1_1.log")
    run_process(EXAMPLE, property_5, safe_5, nnet, output_overapproximate, output_exact)
    progress_bar.update(1)

    tqdm.write("Property 6 (only N1,1)")
    property_6: str = os.path.join(PROPERTY_PATH, "poly_prop6_5D_artificial_bounds.in")
    safe_6: str = os.path.join(PROPERTY_PATH, "poly_prop6_safe.in")
    nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_1_1.nnet")
    output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_6", "over", f"nnet_1_1.log")
    output_exact: str = os.path.join(OUTPUT_PATH, "property_6", "exact", f"nnet_1_1.log")
    run_process(EXAMPLE, property_6, safe_6, nnet, output_overapproximate, output_exact)
    progress_bar.update(1)

    tqdm.write("Property 7 (only N1,9)")
    property_7: str = os.path.join(PROPERTY_PATH, "poly_prop7_5D_artificial_bounds.in")
    safe_7: str = os.path.join(PROPERTY_PATH, "poly_prop7_safe.in")
    nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_1_1.nnet")
    output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_7", "over", f"nnet_1_9.log")
    output_exact: str = os.path.join(OUTPUT_PATH, "property_7", "exact", f"nnet_1_9.log")
    run_process(EXAMPLE, property_7, safe_7, nnet, output_overapproximate, output_exact)
    progress_bar.update(1)

    tqdm.write("Property 8 (only N2,9)")
    property_8: str = os.path.join(PROPERTY_PATH, "poly_prop8_5D_artificial_bounds.in")
    safe_8: str = os.path.join(PROPERTY_PATH, "poly_prop8_safe.in")
    nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_2_9.nnet")
    output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_8", "over", f"nnet_2_9.log")
    output_exact: str = os.path.join(OUTPUT_PATH, "property_8", "exact", f"nnet_2_9.log")
    run_process(EXAMPLE, property_8, safe_8, nnet, output_overapproximate, output_exact)
    progress_bar.update(1)

    tqdm.write("Property 9 (only N3,3)")
    property_9: str = os.path.join(PROPERTY_PATH, "poly_prop9_5D_artificial_bounds.in")
    safe_9: str = os.path.join(PROPERTY_PATH, "poly_prop9_safe.in")
    nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_3_3.nnet")
    output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_9", "over", f"nnet_3_3.log")
    output_exact: str = os.path.join(OUTPUT_PATH, "property_9", "exact", f"nnet_3_3.log")
    run_process(EXAMPLE, property_9, safe_9, nnet, output_overapproximate, output_exact)
    progress_bar.update(1)

    tqdm.write("Property 10 (only N4,5)")
    property_10: str = os.path.join(PROPERTY_PATH, "poly_prop10_5D_artificial_bounds.in")
    safe_10: str = os.path.join(PROPERTY_PATH, "poly_prop10_safe.in")
    nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_4_5.nnet")
    output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_10", "over", f"nnet_4_5.log")
    output_exact: str = os.path.join(OUTPUT_PATH, "property_10", "exact", f"nnet_4_5.log")
    run_process(EXAMPLE, property_10, safe_10, nnet, output_overapproximate, output_exact)
    progress_bar.update(1)


def create_tables():
    HYPRO_ROOT: str = os.getcwd()
    for property in range(1, 11):
        data, rows = parse_results.parse_logfiles(HYPRO_ROOT, property)
        table = parse_results.create_latex_table(data, rows)
        print(table)


if __name__ == "__main__":
    run_benchmarks()
    # create_tables()
