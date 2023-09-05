import os

def generate_parameters():
    PROPERTY_PATH: str = os.path.join(os.getcwd(), "examples", "nn_prop_inputs", "acasxu")
    NNET_PATH: str = os.path.join(os.getcwd(), "examples", "nnet", "acasxu")
    OUTPUT_PATH: str = os.path.join(os.getcwd(), "evaluation")
    EXAMPLE: str = os.path.join(os.getcwd(), "build", "bin", "example_ACASbenchmarkVerification")

    output_file = "parameters.txt"
    with open(output_file, "w") as parameter_file:
        property_1: str = os.path.join(PROPERTY_PATH, "poly_prop1_5D_artificial_bounds.in")
        safe_1: str = os.path.join(PROPERTY_PATH, "poly_prop1_safe.in")
        for i in range(1, 6):
            for j in range(1, 10):
                # NNet
                nnet: str = os.path.join(NNET_PATH, f"ACASXU_experimental_v2a_{i}_{j}.nnet")
                output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_1", "over", f"nnet_{i}_{j}.log")
                output_exact: str = os.path.join(OUTPUT_PATH, "property_1", "exact", f"nnet_{i}_{j}.log")
                parameter_file.write(property_1)
                parameter_file.write(safe_1)
                parameter_file.write(nnet)
                parameter_file.write(output_overapproximate)
                parameter_file.write(output_exact)

        property_2: str = os.path.join(PROPERTY_PATH, "poly_prop2_5D_artificial_bounds.in")
        safe_2: str = os.path.join(PROPERTY_PATH, "poly_prop2_safe.in")
        for i in range(2, 6):
            for j in range(1, 9):
                # NNet
                nnet: str = os.path.join(NNET_PATH, f"ACASXU_experimental_v2a_{i}_{j}.nnet")
                output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_2", "over", f"nnet_{i}_{j}.log")
                output_exact: str = os.path.join(OUTPUT_PATH, "property_2", "exact", f"nnet_{i}_{j}.log")
                parameter_file.write(property_2)
                parameter_file.write(safe_2)
                parameter_file.write(nnet)
                parameter_file.write(output_overapproximate)
                parameter_file.write(output_exact)

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
                parameter_file.write(property_3)
                parameter_file.write(safe_3)
                parameter_file.write(nnet)
                parameter_file.write(output_overapproximate)
                parameter_file.write(output_exact)

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
                parameter_file.write(property_4)
                parameter_file.write(safe_4)
                parameter_file.write(nnet)
                parameter_file.write(output_overapproximate)
                parameter_file.write(output_exact)

        property_5: str = os.path.join(PROPERTY_PATH, "poly_prop5_5D_artificial_bounds.in")
        safe_5: str = os.path.join(PROPERTY_PATH, "poly_prop5_safe.in")
        nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_1_1.nnet")
        output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_5", "over", f"nnet_1_1.log")
        output_exact: str = os.path.join(OUTPUT_PATH, "property_5", "exact", f"nnet_1_1.log")
        parameter_file.write(property_5)
        parameter_file.write(safe_5)
        parameter_file.write(nnet)
        parameter_file.write(output_overapproximate)
        parameter_file.write(output_exact)

        property_6: str = os.path.join(PROPERTY_PATH, "poly_prop6_5D_artificial_bounds.in")
        safe_6: str = os.path.join(PROPERTY_PATH, "poly_prop6_safe.in")
        nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_1_1.nnet")
        output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_6", "over", f"nnet_1_1.log")
        output_exact: str = os.path.join(OUTPUT_PATH, "property_6", "exact", f"nnet_1_1.log")
        parameter_file.write(property_6)
        parameter_file.write(safe_6)
        parameter_file.write(nnet)
        parameter_file.write(output_overapproximate)
        parameter_file.write(output_exact)

        property_7: str = os.path.join(PROPERTY_PATH, "poly_prop7_5D_artificial_bounds.in")
        safe_7: str = os.path.join(PROPERTY_PATH, "poly_prop7_safe.in")
        nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_1_1.nnet")
        output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_7", "over", f"nnet_1_9.log")
        output_exact: str = os.path.join(OUTPUT_PATH, "property_7", "exact", f"nnet_1_9.log")
        parameter_file.write(property_7)
        parameter_file.write(safe_7)
        parameter_file.write(nnet)
        parameter_file.write(output_overapproximate)
        parameter_file.write(output_exact)

        property_8: str = os.path.join(PROPERTY_PATH, "poly_prop8_5D_artificial_bounds.in")
        safe_8: str = os.path.join(PROPERTY_PATH, "poly_prop8_safe.in")
        nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_2_9.nnet")
        output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_8", "over", f"nnet_2_9.log")
        output_exact: str = os.path.join(OUTPUT_PATH, "property_8", "exact", f"nnet_2_9.log")
        parameter_file.write(property_8)
        parameter_file.write(safe_8)
        parameter_file.write(nnet)
        parameter_file.write(output_overapproximate)
        parameter_file.write(output_exact)

        property_9: str = os.path.join(PROPERTY_PATH, "poly_prop9_5D_artificial_bounds.in")
        safe_9: str = os.path.join(PROPERTY_PATH, "poly_prop9_safe.in")
        nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_3_3.nnet")
        output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_9", "over", f"nnet_3_3.log")
        output_exact: str = os.path.join(OUTPUT_PATH, "property_9", "exact", f"nnet_3_3.log")
        parameter_file.write(property_9)
        parameter_file.write(safe_9)
        parameter_file.write(nnet)
        parameter_file.write(output_overapproximate)
        parameter_file.write(output_exact)

        property_10: str = os.path.join(PROPERTY_PATH, "poly_prop10_5D_artificial_bounds.in")
        safe_10: str = os.path.join(PROPERTY_PATH, "poly_prop10_safe.in")
        nnet: str = os.path.join(NNET_PATH, "ACASXU_experimental_v2a_4_5.nnet")
        output_overapproximate: str = os.path.join(OUTPUT_PATH, "property_10", "over", f"nnet_4_5.log")
        output_exact: str = os.path.join(OUTPUT_PATH, "property_10", "exact", f"nnet_4_5.log")
        parameter_file.write(property_10)
        parameter_file.write(safe_10)
        parameter_file.write(nnet)
        parameter_file.write(output_overapproximate)
        parameter_file.write(output_exact)


if __name__ == "__main__":
    generate_parameters()
