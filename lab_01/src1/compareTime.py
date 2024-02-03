from algorythms import *
import matplotlib.pyplot as plt
import random
from time import *
import string 
from constant import *

def getProcessTime(str1, str2, func):
    time_res = 0

    for _ in range(TIMES):
        time_start = process_time()
        func(str1, str2)
        time_end = process_time()

        time_res += (time_end - time_start)

    return time_res

def graph(tLev, tDL, tDLR, tDLRC, length):
    plt.figure(1)
    plt.plot(length, tLev, linestyle = 'dashed', label = "Левенштейн")
    plt.plot(length, tDL, linestyle = 'solid', label = "Дамерау-Левенштейн (матричный)")
    plt.legend(fontsize=12)
    plt.xlabel('Длина строки')
    plt.ylabel('Время, мс')
    plt.grid()
    plt.show()

    plt.figure(2)
    plt.plot(length, tDL, linestyle = 'dashed', label = "Дамерау-Левенштейн (матричный)")
    plt.plot(length, tDLR, linestyle = 'solid', label="Дамерау-Левенштейн (рекурсия)")
    plt.plot(length, tDLRC, linestyle = 'dotted', label="Дамерау-Левенштейн (с кэшем)")
    plt.legend(fontsize=12)
    plt.xlabel('Длина строки')
    plt.ylabel('Время, мс')
    plt.grid()
    plt.show()
    
    plt.figure(3)
    plt.plot(length, tDLRC, linestyle = 'dashed', label="Дамерау-Левенштейн (с кэшем)")
    plt.plot(length, tDL, linestyle = 'solid', label = "Дамерау-Левенштейн (матричный)")
    plt.legend(fontsize=12)
    plt.xlabel('Длина строки')
    plt.ylabel('Время, мс')
    plt.grid()
    plt.show()

def compareAlgorithms():
    length = [i for i in range(START, END)]

    timeLev = [0 for _ in range(START, END)]
    timeDamerauLev = [0 for _ in range(START, END)]
    timeDamerauLevRecursive = [0 for _ in range(START, END)]
    timeDamerauLevRecursiveCache = [0 for _ in range(START, END)]
    str1 = ''
    str2 = ''
    for num in range(START, END):
        if num:
            letter = random.choice(string.ascii_lowercase)
            str1 += letter
            letter = random.choice(string.ascii_lowercase)
            str2 += letter
        print("Run with length:\t", num)
        timeLev[num] = getProcessTime(str1, str2, FUNCS[0])
        timeDamerauLev[num] = getProcessTime(str1, str2, FUNCS[1])
        timeDamerauLevRecursive[num] = getProcessTime(str1, str2, FUNCS[2])
        timeDamerauLevRecursiveCache[num] = getProcessTime(str1, str2, FUNCS[3])

    print("\nТаблица времени для 4 алгоритмов: \n")
    
    print("Length | Levenshtein | Lev Domerau | Recursive | Cache")
    for id in range(START, END):
        print(" %5d | %12.5f | %12.5f | %12.5f | %12.5f\n" \
              %(id, timeLev[id],  timeDamerauLev[id], timeDamerauLevRecursive[id], timeDamerauLevRecursiveCache[id]))


    graph(timeLev, timeDamerauLev, timeDamerauLevRecursive, timeDamerauLevRecursiveCache, length)

