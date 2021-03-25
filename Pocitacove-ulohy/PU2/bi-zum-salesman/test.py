import os
import queue
from collections import Counter
from threading import Thread

debug = False

if __name__ == "__main__":
    outputList = []
    for i in range(100):
        stream_project = os.popen("./kucerj56 data/distances-10.csv genetic-erx")
        stream_project_output = stream_project.read().split()
        # print("\n".join(stream_project_output))
        output_path = stream_project_output[-1]
        print(f"Output path: {output_path}")
        outputList += [output_path]

    print(Counter(outputList))
