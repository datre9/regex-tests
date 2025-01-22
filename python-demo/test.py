import os
import re
import time

toWrite = ""

def benchmark(text, regex, title):
    global toWrite
    toWrite += f"{title}\n"
    
    for _ in range(1000):
        startTime = time.time_ns()
        
        re.findall(regex, text)
        
        endTime = time.time_ns()
        
        toWrite += f"{endTime - startTime}\n"

def stringFromFile(path) -> str:
    file_path = os.path.join(os.path.dirname(__file__), path)
    with open(file_path, "r", encoding="utf-8") as file:
        return file.read()


abc1 = stringFromFile("../abc1.txt")
abc2 = stringFromFile("../abc2.txt")
abc3 = stringFromFile("../abc3.txt")

regexKMP = re.compile("(ab)+", 0)


benchmark(abc1, regexKMP, "KMP1")
benchmark(abc2, regexKMP, "KMP2")
benchmark(abc3, regexKMP, "KMP3")


output_path = os.path.join(os.path.dirname(__file__), "results.csv")
with open(output_path, "w") as output:
    output.write(toWrite)