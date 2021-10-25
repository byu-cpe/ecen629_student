#!/usr/bin/python3

import pathlib
import argparse
import subprocess
import sys
import pandas
import re

ROUTER_PATH = pathlib.Path(__file__).absolute().parent.parent
CIRCUITS_PATH = ROUTER_PATH / "circuits"
RESULTS_PATH = ROUTER_PATH / "results"
ROUTER_BIN_PATH = ROUTER_PATH / "build" / "src" / "router"

designs = list(CIRCUITS_PATH.iterdir())

# Uncomment this to override and only run certain designs
# designs = [CIRCUITS_PATH / s for s in ["tiny", "small_dense", "med_dense", "med_sparse"]]


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


def error(*msg, returncode=-1):
    """Print an error message and exit program"""
    print_color(TermColors.RED, "ERROR:", *msg)
    sys.exit(returncode)


def run_router(circuit, w, print_to_stdout=False):
    segments = None
    mem = None
    runtime = None

    print_color(TermColors.PURPLE, "Routing", circuit.name, "W =", w)
    cmd = ["/usr/bin/time", "-v", str(ROUTER_BIN_PATH), str(circuit), str(w)]

    proc = subprocess.Popen(
        cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True
    )
    stdout = ""
    for line in proc.stdout:
        stdout += line
        if print_to_stdout:
            sys.stdout.write(line)
    stdout += proc.communicate()[0]

    # Get segments used
    m = re.search("^Segments used: (\d+)$", stdout, re.M)
    if m:
        segments = int(m.group(1))

    # Get memory usage
    m = re.search(r"^\s*Maximum resident set size \(kbytes\): (\d+)$", stdout, re.M)
    if m:
        mem = int(m.group(1))

    # Get runtime
    m = re.search(r"^\s*User time \(seconds\): (\d+\.\d+)$", stdout, re.M)
    if m:
        runtime = float(m.group(1))

    success = not proc.returncode
    return (success, segments, runtime, mem)


# Usage
# ./run_designs.py
#
# This will read in your minimium channel width file (results/minw.csv) and run each design
# with (W=Wmin) and (W=1.3*Wmin), collecting segment, runtime and memory results.
#
# --find_min_w: Perform a binary search to find the minimum channel width that is routable, and
#               write the results to the minw.csv file.
# --print: Print the stdout of each run of the router (by default it is hidden)
#
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--find_min_w", action="store_true")
    parser.add_argument("--print", action="store_true")
    args = parser.parse_args()

    min_w_csv_path = RESULTS_PATH / "minw.csv"

    if args.find_min_w:
        data = []
        for design in designs:
            print_color(TermColors.BLUE, design.name)

            # Binary search
            upper_bound = 50
            lower_bound = 1
            success = False
            while lower_bound < upper_bound:
                # Try midpoint (except on first try, test the upper bound)
                test_w = int((lower_bound + upper_bound) / 2) if success else upper_bound
                if run_router(design, test_w, print_to_stdout=args.print)[0]:
                    upper_bound = test_w
                    success = True
                else:
                    if lower_bound >= upper_bound - 1:
                        break
                    lower_bound = test_w + 1

            min_w = upper_bound if success else None
            data.append([design.name, min_w])
            print_color(TermColors.GREEN, "minW = ", min_w)

        df = pandas.DataFrame(data, columns=["design", "min_w"])

        df.to_csv(min_w_csv_path, index=False)
    else:
        assert min_w_csv_path.is_file()

        df = pandas.read_csv(min_w_csv_path, keep_default_na=False)

        data = []
        for i, row in df.iterrows():
            design_name = row["design"]

            if not row["min_w"]:
                print_color(TermColors.YELLOW, "Skipping", row["design"])
                continue
            circuit_path = CIRCUITS_PATH / row["design"]

            min_w = int(float(row["min_w"]))
            min_w_relaxed = int(min_w * 1.3)

            data.append(
                [design_name, min_w, *run_router(circuit_path, min_w, print_to_stdout=args.print)]
            )
            data.append(
                [
                    design_name,
                    min_w_relaxed,
                    *run_router(circuit_path, min_w_relaxed, print_to_stdout=args.print),
                ]
            )

        df = pandas.DataFrame(
            data, columns=["design", "w", "success", "segments", "runtime", "memory"]
        )
        df.to_csv(RESULTS_PATH / "results.csv", index=False)


if __name__ == "__main__":
    main()