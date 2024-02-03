import matplotlib.pyplot as plt
from math import *

sizeofInt = 4
sizeofChar = 1
lens = [2, 4, 8, 16, 32, 64, 128, 256, 512]
def mem_bitonic(N):
    return (N + 4 * log2(N)) * sizeofInt

def mem_radix(N):
    return (2 * N + 19) * sizeofInt

def mem_bubble(N):
    return (N + 4) * sizeofInt

def graph(bitonic, radix, bubble):
    plt.figure(1)
    plt.plot(lens, bitonic, linestyle = 'dashed', label = "Битонная сортировка")
    plt.plot(lens, radix, linestyle = 'solid', label = "Поразрядная сортировка")
    plt.plot(lens, bubble, linestyle = 'dashdot', label="Сортировка пузырьком")
    plt.legend(fontsize=12)
    plt.title("Характеристики по памяти")
    plt.xlabel('Размер')
    plt.ylabel('Память, байт')
    plt.grid()
    plt.show()

def compareAlgorithms():
    bintonic = []
    radix = []
    bubble = []

    for i in range(len(lens)):
        bintonic.append(mem_bitonic(lens[i]))
        radix.append(mem_radix(lens[i]))
        bubble.append(mem_bubble(lens[i]))

    graph(bintonic, radix, bubble)

compareAlgorithms()