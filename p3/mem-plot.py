import os
import sys
import matplotlib.pyplot as plt
import numpy as np
import math


# AUX FUNCTIONS ##################################


# reduce all elements by the first element
def normalize_array(arr):
    if len(arr) >= 0 and arr[0] - 1 > 0:
        val = arr[0] - 1
        for i, x in enumerate(arr):
            arr[i] = x - val
    return arr


# receive lists of axis values and plot all the graphs
def plot_graphs(xs, ys, ts, name):
    image_dir = os.path.join(os.getcwd(), "images")
    phases = ["Insert", "Print All", "Delete All With Meanings", "Print Rest", "Clean"]
    images = ["1.png", "2.png", "3.png", "4.png", "5.png"]

    for i in range(len(xs)):
        colors = ["red" if t == "R" else "blue" if t == "W" else "green" for t in ts[i]]
        plt.scatter(xs[i], ys[i], c=colors)
        plt.plot(xs[i], ys[i], color="black", linewidth=0.5)
        plt.title(phases[i])
        plt.xlabel("Memory Access")
        plt.ylabel("Memory Address")
        plt.scatter([], [], c="red", label="Read")
        plt.scatter([], [], c="blue", label="Write")
        plt.legend()

        img_name = os.path.join(image_dir, name + "-" + images[i])
        plt.savefig(img_name)
        plt.clf()


# read the file lines, parse the arguments and plot the correspondent graph
def read_file_and_plot(file_name, img_name):
    xs = []
    ys = []
    ts = []

    with open(file_name, "r") as file:
        lines = file.readlines()

        prev_log_phase = 0
        x = []
        y = []
        t = []

        for line in lines:
            # parse the line
            line = line.strip().split(" ")

            log_type = line[0]
            if log_type == "I" or log_type == "F":
                continue

            log_phase = int(line[1])
            log_count = int(line[2])
            # log_struct_id = line[3]   useless here
            # log_time = float(line[4]) useless here
            log_mem_addr = int(line[5])
            # log_mem_size = int(line[6]) useless here

            if log_phase > 1 and log_phase != prev_log_phase:
                x = normalize_array(x)

                xs.append(x)
                ys.append(y)
                ts.append(t)

                x = [log_count - 1]
                y = [log_mem_addr]
                t = [log_type]

                prev_log_phase = log_phase
            else:
                x.append(log_count - 1)
                y.append(log_mem_addr)
                t.append(log_type)

        if len(x) > 0:
            xs.append(x)
            ys.append(y)
            ts.append(t)

    file.close()

    plot_graphs(xs, ys, ts, img_name)


# SCRIPT BODY ######################################3

# get output files
out_dir = os.path.join(os.getcwd(), "output")

tree_file_name = os.path.join(out_dir, "mem-tree.txt")
hash_file_name = os.path.join(out_dir, "mem-hash.txt")

if not os.path.isfile(tree_file_name) or not os.path.isfile(hash_file_name):
    print("Missing output file")
    sys.exit(1)

# open and plot data
try:
    read_file_and_plot(tree_file_name, "tree")
    read_file_and_plot(hash_file_name, "hash")
except Exception as e:
    print(f"Script Error: {e}")
