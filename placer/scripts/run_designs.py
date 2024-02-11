#!/usr/bin/python3

import pathlib
import argparse
import subprocess
import sys
import pandas
import re
from sys import platform

PLACER_PATH = pathlib.Path(__file__).absolute().parent.parent
CIRCUITS_PATH = PLACER_PATH / "circuits"
RESULTS_PATH = PLACER_PATH / "results"
PLACER_BIN_PATH = PLACER_PATH / "build" / "src" / "placer"

TIME_PATH = "/usr/bin/time"
# time doesn't have a -v option on mac, install gtime using `brew install gnu-time`
if platform == "darwin":
    TIME_PATH = "gtime"

    # check for gtime
    gtime_check = subprocess.run(["which", f"{TIME_PATH}"], stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)
    if gtime_check.returncode != 0:
        print("time doesn't have a -v option on mac, install gtime using `brew install gnu-time`", file=sys.stderr)
        sys.exit(1)

designs = list(CIRCUITS_PATH.iterdir())
designs.sort()

# Uncomment this to override and only run certain designs

class TermColors:
    """Terminal codes for printing in color"""

    PURPLE = "\033[95m"
    BLUE = "\033[94m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    RED = "\033[91m"
    END = "\033[0m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"


def print_color(color, *msg):
    """Print a message in color"""
    print(color + " ".join(str(item) for item in msg), TermColors.END)


def error(*msg, return_code=-1):
    """Print an error message and exit program"""
    print_color(TermColors.RED, "ERROR:", *msg)
    sys.exit(return_code)


def run_placer(circuit, greedy, print_to_stdout=False):
    HPWL_rand = None
    HPWL_ap = None
    HPWL_legal = None
    overlap_cost = None

    print_color(TermColors.PURPLE, f"Placing {circuit.name}, {greedy}")
    cmd = [TIME_PATH, "-v", str(PLACER_BIN_PATH), str(circuit), greedy]

    proc = subprocess.Popen(
        cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True
    )
    stdout = ""
    for line in proc.stdout:
        stdout += line
        if print_to_stdout:
            sys.stdout.write(line)
    stdout += proc.communicate()[0]

    # Get HPWL_rand
    m = re.search(r"^HPWL \(random placement\): ([\d.]+)$", stdout, re.M)
    if m:
        HPWL_rand = float(m.group(1))

    # Get HPWL_ap
    m = re.search(r"^HPWL \(after AP\): ([\d.]+)$", stdout, re.M)
    if m:
        HPWL_ap = float(m.group(1))

    # Get HPWL_legal
    m = re.search(r"^HPWL \(after legalization\): ([\d.]+)$", stdout, re.M)
    if m:
        HPWL_legal = float(m.group(1))

    # Get overlap cost
    m = re.search(r"^Overlap cost: (\d+)$", stdout, re.M)
    if m:
        overlap_cost = int(m.group(1))

    success = not proc.returncode
    return success, HPWL_rand, HPWL_ap, HPWL_legal, overlap_cost


# Usage
# ./run_designs.py
#
# --print: Print the stdout of each run (by default it is hidden)
#
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--print", action="store_true")
    args = parser.parse_args()

    data = []
    for circuit_path in designs:
        for greedy in ["hungry", "greedy"]:
            design_name = circuit_path.name

            data.append(
                [design_name, greedy, *run_placer(circuit_path, greedy, print_to_stdout=args.print)]
            )

    df = pandas.DataFrame(
        data, columns=["design", "method", "success", "HPWL rand", "HPWL ap", "HPWL legal", "Overlap cost"]
    )
    df.to_csv(RESULTS_PATH / "results.csv", index=False)


if __name__ == "__main__":
    main()
