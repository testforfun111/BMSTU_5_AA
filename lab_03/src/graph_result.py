import matplotlib.pyplot as plt

def get_times(filename):
    arr_len = []
    arr_times = []
    with open(filename, "r") as f:
        data =f.readline().split()
        for i in range(0, len(data), 2):
            arr_len.append(int(data[i]))
            arr_times.append(float(data[i + 1]))
    return arr_len, arr_times

def get_graph_result(filename1, filename2, filename3):
    arr_len1, arr_stand_time = get_times(filename1)
    arr_len2, arr_wino_time = get_times(filename2)
    arr_len3, arr_op_wino_time = get_times(filename3)
    print(arr_stand_time)
    if (len(arr_len1) != len(arr_len2)):
        return
    
    labels = ["Битонная сортировка",
              "Поразрядная сортировка",
              "Сортировка пузырьком"]
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(arr_len1, arr_stand_time, linestyle = 'dotted', label = labels[0])
    plot.plot(arr_len1, arr_wino_time, linestyle = 'dashed', label = labels[1])
    plot.plot(arr_len1, arr_op_wino_time, linestyle = 'solid', label = labels[2])

    plt.legend()
    plt.grid()
    plt.title("Характеристики времени")
    plt.ylabel("Затраченное время(c)")
    plt.xlabel("Размер массива")

    plt.show()

# get_graph_result("stand.txt", "wino.txt", "op_wino.txt")
get_graph_result("bitonic.txt", "radix.txt", "bubble.txt")
