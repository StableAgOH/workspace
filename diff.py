import argparse
import difflib
import itertools
import logging
import subprocess
import sys


def exec_and_check(command, msg: str, **kwargs):
    try:
        subprocess.run(command, check=True, **kwargs)
    except:
        logging.error(msg)
        exit(0)


def compile(filename: str):
    logging.info(f"Compiling {filename}")
    exec_and_check(["g++", f"{filename}.cpp", "-o", filename, "-O2", "-std=c++20"], f"Failed to compile {filename}")
    logging.debug(f"Compiled {filename}")


logging.basicConfig(level=logging.INFO, format="[%(levelname)s] %(message)s")

parser = argparse.ArgumentParser()
parser.add_argument("your_code")
parser.add_argument("answer_code")

args = parser.parse_args()
solution = args.your_code.split(".")[0]
answer = args.answer_code.split(".")[0]
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
    output1 = list(map(lambda s: s.rstrip(" "), open("out.txt", "r").readlines()))
    while output1 and output1[-1] == "\n":
        output1.pop()
    output2 = list(map(lambda s: s.rstrip(" "), open("out2.txt", "r").readlines()))
    while output2 and output2[-1] == "\n":
        output2.pop()
    diff = list(difflib.context_diff(output1, output2, args.your_code, args.answer_code))
    if diff:
        if len(diff) > 100:
            logging.warning("Diff result is too long for output")
        else:
            sys.stdout.writelines(diff)
        logging.error("Two output do not match")
        exit()
