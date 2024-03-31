import os
from os import path
import subprocess

ctx = os.getcwd()
os.chdir(path.dirname(__file__))


def sh(args):
    if isinstance(args, str):
        args = args.split(" ")

    process = subprocess.Popen(args)
    process.wait()


if not path.isdir("./tests/screenshots_new"):
    os.mkdir("./tests/screenshots_new")

sh("xmake")
sh("xmake run make-screenshots")

os.chdir("tests")
sh("python compare_screenshots.py")
os.chdir("..")

os.chdir(ctx)
