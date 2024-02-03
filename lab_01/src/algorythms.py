def createMatrix(n, m, element):
    matrix = []
    matrix.append([j for j in range(m)])
    for i in range(1, n):
        matrix.append([])
        for j in range(m):
            if j == 0:
                matrix[i].append(i) 
            else:
                matrix[i].append(element)
    return matrix

def printMatrix(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i][j], end = "  ")
        print("")

def DLevenshtein(str1, str2):
    n = len(str1)
    m = len(str2)
    matrix = createMatrix(n + 1, m + 1, 0)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            delete = matrix[i - 1][j] + 1
            insert = matrix[i][j - 1] + 1
            change = matrix[i - 1][j - 1]

            if (str1[i - 1] != str2[j - 1]):
                change += 1

            matrix[i][j] = min(insert, delete, change)

    return matrix

def DDamerauLevenshtein(str1, str2):
    n = len(str1)
    m = len(str2)
    matrix = createMatrix(n + 1, m + 1, 0)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            delete = matrix[i - 1][j] + 1
            insert = matrix[i][j - 1] + 1
            change = matrix[i - 1][j - 1]
            if (str1[i - 1] != str2[j - 1]):
                change += 1
            swap = n
            if (i > 1 and j > 1 and
                str1[i - 1] == str2[j - 2] and
                str1[i - 2] == str2[j - 1]):
                    swap = matrix[i - 2][j - 2] + 1

            matrix[i][j] = min(insert, delete, change, swap)

    return matrix

def DDamerauLevenshteinRecursive(str1, str2):
    n = len(str1)
    m = len(str2)

    if ((n == 0) or (m == 0)):
        return abs(n - m)

    add = DDamerauLevenshteinRecursive(str1, str2[:m-1]) + 1
    delete = DDamerauLevenshteinRecursive(str1[:n-1], str2) + 1
    change = DDamerauLevenshteinRecursive(str1[:n-1], str2[:m-1]) + int(str1[n- 1] != str2[m - 1])

    minDistance = min(add, delete, change)

    if (n >= 2 and m >=2 and str1[n-1] == str2[m-2] and str1[n-2] == str2[m-1]):
        minDistance = min(minDistance, DDamerauLevenshteinRecursive(str1[:n-2], str2[:m-2]) + 1)

    return minDistance

def RecursiveWithCache(str1, str2, n, m, matrix):
    if (matrix[n][m] != None):
        return matrix[n][m]

    delete = RecursiveWithCache(str1, str2, n - 1, m, matrix) + 1
    insert = RecursiveWithCache(str1, str2, n, m - 1, matrix) + 1
    change = RecursiveWithCache(str1, str2, n - 1, m - 1, matrix) + int(str1[n - 1] != str2[m - 1])

    matrix[n][m] = min(insert, delete, change)
    if (n > 1 and m > 1 and str1[n - 1] == str2[m - 2] and str1[n - 2] == str2[m - 1]):
        matrix[n][m] = min(matrix[n][m],
            RecursiveWithCache(str1, str2, n - 2, m - 2, matrix) + 1)

    return matrix[n][m]

def DDamerauLevenshteinRecurciveCache(str1, str2):
    n = len(str1)
    m = len(str2)

    matrix = createMatrix(n + 1, m + 1, None)

    RecursiveWithCache(str1, str2, n, m, matrix)

    return matrix
