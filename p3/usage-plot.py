import os
import sys
import matplotlib.pyplot as plt

# AUX FUNCTIONS #############################


def plot_bars(x, ys):
    colors = ["red", "green"]
    file_name = os.path.join(os.getcwd(), "images/usage.png")
    plt.bar(x, ys, width=0.5, color=colors)
    plt.xlabel("Implementation")
    plt.ylabel("Mean Time")
    plt.title("Execution Time")
    plt.savefig(file_name)
    plt.clf()


def read_file_and_plot(file_names):
    x = ["tree", "hash"]
    ys = []

    for file_name in file_names:
        mean = 0

        with open(file_name, "r") as file:
            lines = file.readlines()

            for line in lines:
                line = line.strip()

                value = float(line)
                mean += value

            mean /= len(lines)
            ys.append(mean)
        file.close()

    plot_bars(x, ys)


# SCRIPT BODY #####################################

out_dir = os.path.join(os.getcwd(), "output")

tree_file_name = os.path.join(out_dir, "usage-tree.txt")
hash_file_name = os.path.join(out_dir, "usage-hash.txt")

if not os.path.isfile(tree_file_name) or not os.path.isfile(hash_file_name):
    print("Missing output file")
    sys.exit(1)

read_file_and_plot([tree_file_name, hash_file_name])
