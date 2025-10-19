import argparse
import difflib
import itertools
import logging
import subprocess
import sys

logging.basicConfig(level=logging.INFO, format="[%(levelname)s] %(message)s")


def exec_and_check(command, msg: str, **kwargs):
    try:
        subprocess.run(command, check=True, **kwargs)
    except subprocess.CalledProcessError as e:
        logging.error(f"{msg}: {e.output}")
        exit(e.returncode)


def compile(filename: str):
    logging.info(f"Compiling {filename}")
    exec_and_check(
        ["g++", f"{filename}.cpp", "-o", filename, "-O2", "-std=c++23", "-lstdc++exp"],
        f"Failed to compile {filename}",
    )


parser = argparse.ArgumentParser()
parser.add_argument("your_code")
parser.add_argument("answer_code")
parser.add_argument("--cache", action="store_true", help="do not compile")

args = parser.parse_args()
solution = args.your_code.split(".")[0]
answer = args.answer_code.split(".")[0]

if not args.cache:
    compile(solution)
    compile(answer)

for i in itertools.count(1):
    logging.info(f"Testcase No.{i}")
    exec_and_check(
        ["python", "gen.py"],
        f"Failed to generate testcase",
        stdout=open("in.txt", "w"),
    )
    exec_and_check(
        solution,
        f"Runtime error when running your code",
        stdin=open("in.txt", "r"),
        stdout=open("out.txt", "w"),
    )
    exec_and_check(
        answer,
        f"Runtime error when running answer code",
        stdin=open("in.txt", "r"),
        stdout=open("out2.txt", "w"),
    )
    out1 = list(map(lambda s: s.rstrip(" \n"), open("out.txt", "r").readlines()))
    while out1 and out1[-1] == "\n":
        out1.pop()
    out2 = list(map(lambda s: s.rstrip(" \n"), open("out2.txt", "r").readlines()))
    while out2 and out2[-1] == "\n":
        out2.pop()
    diff = list(difflib.context_diff(out1, out2, args.your_code, args.answer_code))
    if diff:
        if len(diff) > 100:
            logging.warning("Diff result is too long for output")
        else:
            sys.stdout.writelines(diff)
        logging.error("Two output do not match")
        exit()
