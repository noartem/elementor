import os
import shutil

shutil.rmtree("build")
shutil.rmtree(".xmake")
os.remove("CMakeLists.txt")
