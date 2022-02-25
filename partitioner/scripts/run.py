import pathlib
import re
import subprocess
import sys
import time
import pandas

PARTITIONER_PATH = pathlib.Path(__file__).resolve().parent.parent
CIRCUITS_PATH = PARTITIONER_PATH / "circuits"


def main():
    df = pandas.DataFrame(columns=["circuit", "runtime", "cuts"])
    for c in sorted(CIRCUITS_PATH.glob("*")):
        print(c)
        lines = ""
        try:
            t1 = time.time()
            cmd = [str(PARTITIONER_PATH / "build" / "src" / "partitioner"), str(c), "0"]
            print(" ".join(cmd))
            p = subprocess.run(
                cmd,
                universal_newlines=True,
                capture_output=True,
                timeout=60 * 60,
            )
            t2 = time.time()
        except subprocess.TimeoutExpired as e:
            continue

        lines = p.stdout
        print(lines)

        runtime = t2 - t1

        m = re.search("^Solution cost: (\d+)$", lines, re.M)
        if not m:
            print("Could not find solution in output, skipping.")
            continue
        cuts = m.group(1)

        df.loc[len(df)] = [c.name, runtime, cuts]
        print(df)

        del p

    (PARTITIONER_PATH / "results").mkdir(exist_ok=True)
    df.to_csv(PARTITIONER_PATH / "results" / "results.csv", index=False)


if __name__ == "__main__":
    main()
