from matrix import *
import matplotlib.pyplot as plt
from math import *
from time import *

sizeofInt = 4
sizeofChar = 1

def mem_stand_alg(m, n, p):
    return (m * n + n * p + p * m + 6) * sizeofInt

def mem_wino(m, n, p):
    return (m * n + n * p + p * m + 6 + m + n) * sizeofInt

def mem_wino_op(m, n, p):
    return (m * n + n * p + p * m + 8 + m + n) * sizeofInt

def mem_straccen(n):
    K = int(log2(n))
    mem_temp = 0
    for i in range(2, K):
        mem_temp = 19 * n * n / (i**2) * sizeofInt
    return (3 * n * n + 4) * sizeofInt + mem_temp

def graph(mLev, mDL, mDLRC, length):
    plt.figure(1)
    plt.plot(length, mLev, linestyle = 'dashed', label = "Стадарный алгоритм")
    plt.plot(length, mDL, linestyle = 'solid', label = "Алгоритм Винограда")
    plt.plot(length, mDLRC, linestyle = 'dashdot', label="Алгоритм Винограда с оптимизацией")
    plt.legend(fontsize=12)
    plt.title("Характеристики по памяти")
    plt.xlabel('Размер')
    plt.ylabel('Память, байт')
    plt.grid()
    plt.show()

def compareAlgorithms():
    lengths = [i for i in range(1, 21, 2)]
    lengthss = [i for i in range(1, 101, 10)]
    memStand = [0 for _ in range(1, 21, 2)]
    memWino = [0 for _ in range(1, 21, 2)]
    memWinoOp = [0 for _ in range(1, 21, 2)]

    for i in range(len(lengths)):
        memStand[i] = mem_stand_alg(lengths[i], lengths[i], lengths[i])
        memWino[i] = mem_wino(lengths[i], lengths[i], lengths[i])
        memWinoOp[i] = mem_wino_op(lengths[i], lengths[i], lengths[i])
    
    print(memStand, memWino)
    print("\nТаблица памяти для 4 алгоритмов: \n")
    
    # print("Length | Levenshtein | Lev Domerau | Recursive | Cache")
    # for id in range(len(memLev)):
    #     print(" %5d | %12d | %12d | %12d | %12d\n" \
    #           %(id, memLev[id],  memDamerauLev[id], memDamerauLevRecursive[id], memDamerauLevRecursiveCache[id]))


    graph(memStand, memWino, memWinoOp, lengthss)

compareAlgorithms()