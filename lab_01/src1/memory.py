from algorythms import *
import matplotlib.pyplot as plt
import random
from time import *
from constant import *

sizeofInt = 4
sizeofChar = 1

def memory_Lev(length):
    memory_matrix = (length + 1) * (length + 1) * sizeofInt
    memory_str = (length + length + 2) * sizeofChar
    memory_length_str = 2 * sizeofInt
    memory_for_variable = 2 * sizeofInt
    return memory_matrix + memory_str + memory_length_str + memory_for_variable

def memory_DLev(length):
    memory_matrix = (length + 1) * (length + 1) * sizeofInt
    memory_str = (length + length + 2) * sizeofChar
    memory_length_str = 2 * sizeofInt
    memory_for_variable = 2 * sizeofInt
    return memory_matrix + memory_str + memory_length_str + memory_for_variable

def memory_DLevRec(length):
    memory_str = (length + length + 2) * sizeofChar
    memory_length_str = 2 * sizeofInt
    memory_for_variable = 4 * sizeofInt
    time_Rec_max = length * 2 
    return (memory_str + memory_length_str + memory_for_variable) * time_Rec_max

def memory_DLevRecWithCache(length):
    memory_matrix = (length + 1) * (length + 1) * sizeofInt
    memory_str = (length + length + 2) * sizeofChar
    memory_length_str = 2 * sizeofInt
    memory_for_variable = 4 * sizeofInt
    time_Rec_max = length * 2 
    return memory_matrix + (memory_str + memory_length_str + memory_for_variable) * time_Rec_max

def graph(mLev, mDL, mDLR, mDLRC, length):
    plt.figure(1)
    plt.plot(length, mLev, linestyle = 'dashed', label = "Левенштейн")
    plt.plot(length, mDL, linestyle = 'solid', label = "Дамерау-Левенштейн (матричный)")
    plt.plot(length, mDLR, linestyle = 'dotted', label="Дамерау-Левенштейн (рекурсия)")
    plt.plot(length, mDLRC, linestyle = 'dashdot', label="Дамерау-Левенштейн (с кэшем)")
    plt.legend(fontsize=12)
    plt.xlabel('Длина строки')
    plt.ylabel('память, байт')
    plt.grid()
    plt.show()

def compareAlgorithms():
    lengths = [i for i in range(0, 101, 10)]

    memLev = [0 for _ in range(0, 101, 10)]
    memDamerauLev = [0 for _ in range(0, 101, 10)]
    memDamerauLevRecursive = [0 for _ in range(0, 101, 10)]
    memDamerauLevRecursiveCache = [0 for _ in range(0, 101, 10)]

    for i in range(len(lengths)):
        memLev[i] = memory_Lev(lengths[i])
        memDamerauLev[i] = memory_DLev(lengths[i])
        memDamerauLevRecursive[i] = memory_DLevRec(lengths[i])
        memDamerauLevRecursiveCache[i] = memory_DLevRecWithCache(lengths[i])
        
    print("\nТаблица памяти для 4 алгоритмов: \n")
    
    print("Length | Levenshtein | Lev Domerau | Recursive | Cache")
    for id in range(len(memLev)):
        print(" %5d | %12d | %12d | %12d | %12d\n" \
              %(id, memLev[id],  memDamerauLev[id], memDamerauLevRecursive[id], memDamerauLevRecursiveCache[id]))


    graph(memLev, memDamerauLev, memDamerauLevRecursive, memDamerauLevRecursiveCache, lengths)

compareAlgorithms()