def createMatrix(n, m, element):
    matrix = [[element] * m for _ in range(n)]
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

    for i in range(0, n + 1):
        for j in range(0, m + 1):
            if (i == 0 or j == 0):
                matrix[i][j] = max(i, j)
            else:
                matrix[i][j] = min(matrix[i - 1][j] + 1,
                                    matrix[i][j - 1] + 1,
                                    matrix[i - 1][j - 1] +
                                      int(str1[i - 1] != str2[j - 1]))

    return matrix

def DDamerauLevenshtein(str1, str2):
    n = len(str1)
    m = len(str2)
    matrix = createMatrix(n + 1, m + 1, 0)

    for i in range(0, n + 1):
        for j in range(0, m + 1):
            if (i != 0 and j != 0):
                matrix[i][j] = min(matrix[i - 1][j] + 1,
                                    matrix[i][j - 1] + 1,
                                    matrix[i - 1][j - 1] + int(str1[i - 1] != str2[j - 1]))
                if (i > 1 and j > 1 and
                    str1[i - 1] == str2[j - 2] and
                    str1[i - 2] == str2[j - 1]):
                        matrix[i][j] = min(matrix[i][j], matrix[i - 2][j - 2] + 1)
            else:
                matrix[i][j] = max(i, j)
    
    return matrix

def DDamerauLevenshteinRecursive(str1, str2):
    n = len(str1)
    m = len(str2)

    if n != 0:
        if m != 0:
            add = DDamerauLevenshteinRecursive(str1, str2[:m-1]) + 1
            delete = DDamerauLevenshteinRecursive(str1[:n-1], str2) + 1
            change = DDamerauLevenshteinRecursive(str1[:n-1], str2[:m-1]) + int(str1[n- 1] != str2[m - 1])

            result = min(add, delete, change)

            if (n >= 2 and m >=2 and str1[n-1] == str2[m-2] and str1[n-2] == str2[m-1]):
                result = min(result, DDamerauLevenshteinRecursive(str1[:n-2], str2[:m-2]) + 1)
        else:
            return n 
    else:
        return m 
    return result

def Recursive(str1, str2, n, m, matrix):
    if (n != 0 and m != 0):
        if (matrix[n][m] == -1):
            delete = Recursive(str1, str2, n - 1, m, matrix) + 1
            insert = Recursive(str1, str2, n, m - 1, matrix) + 1
            change = Recursive(str1, str2, n - 1, m - 1, matrix) + int(str1[n - 1] != str2[m - 1])

            matrix[n][m] = min(insert, delete, change)
            if (n > 1 and m > 1 and str1[n - 1] == str2[m - 2] and str1[n - 2] == str2[m - 1]):
                matrix[n][m] = min(matrix[n][m],
                    Recursive(str1, str2, n - 2, m - 2, matrix) + 1)
    else:
        matrix[n][m] = max(n, m)

    return matrix[n][m]

def DDamerauLevenshteinRecurciveCache(str1, str2):
    n = len(str1)
    m = len(str2)

    matrix = createMatrix(n + 1, m + 1, -1)

    Recursive(str1, str2, n, m, matrix)

    return matrix
