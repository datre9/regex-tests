import os
import re
import time
import tracemalloc

file_path = os.path.join(os.path.dirname(__file__), "../adventures-of-huckleberry-finn.txt")
with open(file_path, "r", encoding="utf-8") as file:
    string = file.read()

toWrite = "id;time(ns);memory(B)\n"
regex = re.compile("finn|huckleberry", re.IGNORECASE)

for i in range(100):
    tracemalloc.start()
    startTime = time.time_ns()
    
    re.findall(regex, string)
    
    endTime = time.time_ns()
    endMemory = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    tracemalloc.reset_peak()
    
    toWrite += f"{i};{endTime - startTime};{endMemory[1]}\n"

output_path = os.path.join(os.path.dirname(__file__), "results.csv")
with open(output_path, "w") as output:
    output.write(toWrite)