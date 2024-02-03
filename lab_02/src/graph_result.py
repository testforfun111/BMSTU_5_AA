import matplotlib.pyplot as plt
from time_test import measure_time, TimeTest


def get_graph_result():
    """
        Графический вывод результатов
        замеров времени.
    """

    sizes = [size for size in range(TimeTest.min_size, 
                                    TimeTest.max_size, 
                                    TimeTest.step)]
    results, _ = measure_time()

    # labels = ["Стандартный алгоритм",
    #           "Алгоритм Винограда",
    #           "Оптимизированный алгоритм Винограда", 
    #           "Алгоритм Штрассена"]
    labels = ["Стандартный алгоритм",
              "Алгоритм Винограда",
              "Оптимизированный алгоритм Винограда"]
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, results[0], linestyle = 'dotted', label = labels[0])
    plot.plot(sizes, results[1], linestyle = 'dashed', label = labels[1])
    plot.plot(sizes, results[2], linestyle = 'solid', label = labels[2])
    # plot.plot(sizes, results[3], label = labels[3])

    plt.legend()
    plt.grid()
    plt.title("Замеры времени")
    plt.ylabel("Затраченное время(c)")
    plt.xlabel("Размер")

    plt.show()
