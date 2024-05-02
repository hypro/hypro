import os
from typing import Dict, Tuple, List

import numpy as np
import pandas as pd


def parse_logfiles(hypro_root: str, property: int) -> Tuple[Dict[Tuple[str, str], List[int] | List[bool]], List[str]]:
    exact_logs: str = os.path.join(hypro_root, "evaluation", f"property_{property}", "exact")
    overapproximate_logs: str = os.path.join(hypro_root, "evaluation", f"property_{property}", "overapproximate")

    result: Dict[Tuple[str, str], List[int] | List[bool]] = {}
    rows: List[str] = []

    # Exact
    for log in os.listdir(exact_logs):
        with open(log, 'r') as file:
            lines = file.readlines()

        for i, line in enumerate(lines[-5:], start=1):
            key, value = line.split(':', 1)
            result.setdefault((key, "E"), []).append(value.strip())

        # Append Row index
        filename = os.path.basename(file)
        rows.append(f"N_{filename.replace('.log', '').split('_')[1]},{filename.replace('.log', '').split('_')[2]}")

    # Overapproximate
    with open(overapproximate_logs, 'r') as file:
        lines = file.readlines()

    for i, line in enumerate(lines[-5:], start=1):
        key, value = line.split(':', 1)
        result.setdefault((key, "="), []).append(value.strip())

    return result, rows


def create_latex_table(data: Dict[Tuple[str, str], List[int] | List[bool]], rows: List[str]) -> str:
    # Create a two-dimensional array
    df = pd.DataFrame(data=data, index=rows)
    latex_table = df.to_latex(float_format="%.2f")

    return latex_table