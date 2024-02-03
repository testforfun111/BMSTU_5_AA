import csv
import matplotlib.pyplot as plt

def read_file1(file_name):
    size = []
    arr1 = []
    arr2 = []
    with open(file_name, mode ='r') as f:
        csvFile = csv.reader(f)
        i = 0
        for line in csvFile:
            if i < 2:
                i += 1
                continue
            else:
                size.append(int(line[0]))
                arr1.append(float(line[2]))
                arr2.append(float(line[3]))
    return size, arr1, arr2

def read_file2(file_name):
    size = []
    arr = []
    with open(file_name, mode ='r') as f:
        csvFile = csv.reader(f)
        i = 0
        for line in csvFile:
            if i < 2:
                i += 1
                continue
            else:
                size.append(int(line[0]))
                arr.append(float(line[1]))
    return size, arr

                
def time_graph1(sizes_text, without_thread, four_thread):
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes_text, without_thread, label="без многопоточности", marker="*")
    plot.plot(sizes_text, four_thread, label="c 12 потоками", marker="<")

    plt.legend()
    plt.grid()
    tit = "Временные характеристики"
    plt.title(tit)
    plt.ylabel("Время (мс)")
    plt.xlabel("Размер строка")

    plt.show()


def time_graph2(sizes_thread, times):
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes_thread, times, marker="*")

    plt.legend()
    plt.grid()
    tit = "Временные характеристики"
    plt.title(tit)
    plt.ylabel("Время (мс)")
    plt.xlabel("Количество потоков")

    plt.show()

sizes, without_thread, many_thread= read_file1("../../tex/csv/4patok.csv")
time_graph1(sizes, without_thread, many_thread)

sizes, times = read_file2("../../tex/csv/manypatok.csv")
time_graph2(sizes, times)
