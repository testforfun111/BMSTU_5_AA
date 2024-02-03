from algorythms import *

MENU = ''' Меню
1. Расстояние Левенштейна 
2. Расстояние Дамерау-Левенштейна 
3. Расстояние Дамерау-Левенштейна (рекурсивно)
4. Расстояние Дамерау-Левенштейна (рекурсивно с кешем) 
5. Измерить время 
0. Выход  
'''
FUNCS = [DLevenshtein, DDamerauLevenshtein, DDamerauLevenshteinRecursive, DDamerauLevenshteinRecurciveCache]
NAME_ALGORITHMS = ["Левенштейна", "Дамерау-Левенштейна", "Дамерау-Левенштейна (рекурсивно)", "Дамерау-Левенштейна (рекурсивно с кешем)"]

TIMES = 10000
START = 0
END = 8