import os
import sys
import matplotlib.pyplot as plt
import numpy as np

sizes_file_path = os.path.join(os.getcwd(), "input.txt")

if not os.path.isfile(sizes_file_path):
    print("Missing input file")
    sys.exit(1)

data_dir = os.path.join(os.getcwd(), "output/qs")

if not os.path.isdir(data_dir):
    print("Missing data directory")

x = []
ys = []
colors = ["black", "blue", "red", "green", "yellow", "purple", "pink", "brown"]

try:
    with open(sizes_file_path, "r") as sizes_file:
        lines = sizes_file.readlines()

        for line in lines:
            line = line.strip()
            x.append(int(line))

    sizes_file.close()

    data_file_names = os.listdir(data_dir)
    for data_file_name in data_file_names:
        data_file_path = os.path.join(data_dir, data_file_name)

        with open(data_file_path, "r") as data_file:
            y1 = []
            y2 = []
            y3 = []

            header = data_file.readline().strip()

            for line in data_file:
                line = line.strip().split(" ")

                y1.append(int(line[1]))
                y2.append(int(line[2]))
                y3.append(float(line[3]))

            sublist = [header, y1, y2, y3]
            ys.append(sublist)
        data_file.close()

    image_dir = os.path.join(os.getcwd(), "images")

    plt.title("Comparisons (qs)")
    for id, _y in enumerate(ys):
        plt.plot(x, _y[1], label=_y[0], color=colors[id])
    plt.ylabel("Records Compared")
    plt.xlabel("List Size")
    plt.legend()

    image_path = os.path.join(image_dir, "comparisons_qs.png")
    plt.savefig(image_path)
    plt.clf()

    plt.title("Copies (qs)")
    for id, _y in enumerate(ys):
        plt.plot(x, _y[2], label=_y[0], color=colors[id])
    plt.ylabel("Records Copied")
    plt.xlabel("List Size")
    plt.legend()

    image_path = os.path.join(image_dir, "copies_qs.png")
    plt.savefig(image_path)
    plt.clf()

    plt.title("Execution Time (qs)")
    for id, _y in enumerate(ys):
        plt.plot(x, _y[3], label=_y[0], color=colors[id])
    plt.ylabel("Time in seconds")
    plt.xlabel("List Size")
    plt.legend()

    image_path = os.path.join(image_dir, "time_qs.png")
    plt.savefig(image_path)
    plt.clf()

    # check which version has the greatest number of lower metrics
    # for the greater test size
    alg_scores = [0, 0, 0, 0, 0, 0, 0, 0]

    compared_rank = []
    copied_rank = []
    time_rank = []

    for idx, _y in enumerate(ys):
        compared_rank.append([idx, _y[1]])
        copied_rank.append([idx, _y[2]])
        time_rank.append([idx, _y[3]])

    compared_rank = sorted(compared_rank, key=lambda x: x[1])
    copied_rank = sorted(copied_rank, key=lambda x: x[1])
    time_rank = sorted(time_rank, key=lambda x: x[1])

    for idx, alg in enumerate(compared_rank):
        alg_scores[alg[0]] += idx
    for idx, alg in enumerate(copied_rank):
        alg_scores[alg[0]] += idx
    for idx, alg in enumerate(time_rank):
        alg_scores[alg[0]] += idx

    min_score = np.inf
    min_alg = 0
    for idx, i in enumerate(alg_scores):
        if i < min_score:
            min_score = i
            min_alg = idx

    y = []
    y.append(ys[min_alg])

    other_files = ["hs.txt", "ms.txt"]
    for name in other_files:
        data_file_name = os.path.join(os.getcwd(), "output/" + name)
        with open(data_file_name, "r") as data_file:
            y1 = []
            y2 = []
            y3 = []

            header = data_file.readline().strip()

            for line in data_file:
                line = line.strip().split(" ")

                y1.append(int(line[1]))
                y2.append(int(line[2]))
                y3.append(float(line[3]))

            sublist = [header, y1, y2, y3]
            y.append(sublist)
        data_file.close()

    plt.title("Comparisons")
    for id, _y in enumerate(y):
        plt.plot(x, _y[1], label=_y[0], color=colors[id])
    plt.ylabel("Records Compared")
    plt.xlabel("List Size")
    plt.legend()

    image_path = os.path.join(image_dir, "comparisons.png")
    plt.savefig(image_path)
    plt.clf()

    plt.title("Copies")
    for id, _y in enumerate(y):
        plt.plot(x, _y[2], label=_y[0], color=colors[id])
    plt.ylabel("Records Copied")
    plt.xlabel("List Size")
    plt.legend()

    image_path = os.path.join(image_dir, "copies.png")
    plt.savefig(image_path)
    plt.clf()

    plt.title("Execution Time")
    for id, _y in enumerate(y):
        plt.plot(x, _y[3], label=_y[0], color=colors[id])
    plt.ylabel("Time in seconds")
    plt.xlabel("List Size")
    plt.legend()

    image_path = os.path.join(image_dir, "time.png")
    plt.savefig(image_path)
    plt.clf()

except Exception as e:
    print(f"Error: {e}")
