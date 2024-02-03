from algorythms import *
from compareTime import *
from constant import *

def InputStrings():
    str1 = input("Введите 1-ую строку: ")
    str2 = input("Введите 2-ую строку: ")
    return str1, str2

def algorithm(func, name_algorithm):
    str1, str2 = InputStrings()
    matrix = func(str1, str2)
    if (func == FUNCS[2]):
        print("Расстояние" +  name_algorithm + ":", str(matrix))
    else:   
        printMatrix(matrix)
        print("Расстояние" +  name_algorithm + ":", str(matrix[len(str1)][len(str2)]))

option = -1

while (option != 0):
    print(MENU)
    option = int(input("Ввести выбор: "))

    if option >= 1 and option <= 4:
        algorithm(FUNCS[option - 1], NAME_ALGORITHMS[option - 1])
    elif (option == 5):
        compareAlgorithms()
    elif (option == 0):
        break
    else:
        print("\nВвод неправильный, еще раз!\n")