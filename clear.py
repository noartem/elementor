import os
import shutil

shutil.rmtree("build")
shutil.rmtree(".xmake")
shutil.rmtree("tests/screenshots_diff")
shutil.rmtree("tests/screenshots_new")
os.remove("CMakeLists.txt")
