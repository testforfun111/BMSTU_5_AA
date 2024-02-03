from random import randint
from math import *
from copy import deepcopy
START = 0
END = 100


def create_random_matrix(n):
	matrix = [[0] * n for _ in range(n)]

	for i in range(n):
		for j in range(n):
			matrix[i][j] = randint(START, END)

	return matrix


def input_matrix():
	try:
		n = int(input("Введите число строк: "))
		m = int(input("Введите число столбцов: "))

		if n < 1 or m < 1:
			print("\nОшибка! Размерность матрицы должна быть больше 0!")
			return []
	except:
		print("\nОшибка! Введено не число!")
		return []

	print("Введите элементы матрицы по одному в строке:")
	matrix = []

	for i in range(n):
		matrix.append([])

		for _ in range(m):
			try:
				elem = int(input())
				matrix[i].append(elem)
			except:
				print("\nОшибка! Введено не число!")
				return []
	
	return matrix


def print_matrix(matrix):
	for i in range(len(matrix)):
		for j in range(len(matrix[0])):
			print(" " + str(matrix[i][j]), end = "")
		print("")


def multiplicate(algorithm):
	print("\nВведите матрицу A!")
	A = input_matrix()

	if not len(A):
		return

	print("\nВведите матрицу B!")
	B = input_matrix()

	if not len(B):
		return

	if len(A[0]) != len(B):
		print("\nОшибка! Число столбцов матрицы A должно быть равно числу строк матрицы B!\n")
		return

	result = algorithm(A, B)

	print("\nПолученная матрица:")
	print_matrix(result)

def standard_mult(A, B):
	n = len(A)
	m = len(B[0])
	p = len(A[0])

	C = [[0] * m for _ in range(n)]

	for i in range(n):
		for j in range(m):
			for k in range(p):
				C[i][j] = C[i][j] + A[i][k] * B[k][j]

	return C

def optimized_standard_mult(A, B):
	n = len(A)
	m = len(B[0])
	p = len(A[0])

	C = [[0] * m for _ in range(n)]

	for i in range(n):
		for j in range(m):
			for k in range(p):
				C[i][j] += A[i][k] * B[k][j]

	return C

def winograd_mult(A, B):
	n = len(A)
	m = len(B[0])
	p = len(A[0])

	C = [[0] * m for _ in range(n)]

	row_factors = [0] * n

	for i in range(n):
		for j in range(p // 2):
			row_factors[i] = row_factors[i] + \
							 A[i][2 * j] * A[i][2 * j + 1]

	column_factors = [0] * m

	for i in range(m):
		for j in range(p // 2):
			column_factors[i] = column_factors[i] + \
								B[2 * j][i] * B[2 * j + 1][i]

	for i in range(n):
		for j in range(m):
			C[i][j] = -row_factors[i] - column_factors[j]

			for k in range(p // 2):
				C[i][j] = C[i][j] + (A[i][2 * k + 1] + B[2 * k][j]) * \
									(A[i][2 * k] + B[2 * k + 1][j])
	
	if p % 2 != 0:
		for i in range(n):
			for j in range(m):
				C[i][j] = C[i][j] + A[i][p - 1] * B[p - 1][j]
	
	return C


def optimized_winograd_mult(A, B):
	n = len(A)
	m = len(B[0])
	p = len(A[0])

	C = [[0] * m for _ in range(n)]

	row_factors = [0] * n

	for i in range(n):
		for j in range(p // 2):
			row_factors[i] += A[i][j << 1] * A[i][(j << 1) + 1]

	column_factors = [0] * m

	for i in range(m):
		for j in range(p // 2):
			column_factors[i] += B[j << 1][i] * B[(j << 1) + 1][i]

	for i in range(n):
		row_factors_temp = -row_factors[i]
		for j in range(m):
			C[i][j] = row_factors_temp - column_factors[j]
			for k in range(p // 2):
				index = k << 1
				C[i][j] += (A[i][index + 1] + B[index][j]) * (A[i][index] + B[index + 1][j])
	
	if p % 2 != 0:
		for i in range(n):
			temp_Ai = A[i][p - 1]
			for j in range(m):
				C[i][j] += temp_Ai * B[p - 1][j]
	
	return C

def split(matrix):
	row, col = len(matrix), len(matrix[0])
	row2, col2 = row//2, col//2
	matr1 = [matrix[i][:col2] for i in range(row2)]
	matr2 = [matrix[i][col2:] for i in range(row2)]
	matr3 = [matrix[i][:col2] for i in range(row2, row)]
	matr4 = [matrix[i][col2:] for i in range(row2, row)]

	return matr1, matr2, matr3, matr4 

def add_matrix(a, b):
	new_matrix = []
	for i in range(len(a)):
		new_matrix.append([])
		for j in range(len(a[0])):
			new_matrix[i].append(a[i][j] + b[i][j])
	return new_matrix

def sub_matrix(a, b):
	new_matrix = []
	for i in range(len(a)):
		new_matrix.append([])
		for j in range(len(a[0])):
			new_matrix[i].append(a[i][j] - b[i][j])
	return new_matrix

def default_matrix_multiplication(a, b):
	if len(a) != 2 or len(a[0]) != 2 or len(b) != 2 or len(b[0]) != 2:
		raise Exception("Matrices are not 2x2")
	new_matrix = [
		[a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]],
		[a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]],
	]
	return new_matrix

def strassen_mult_sq(x, y):
	if len(x) == 2 and len(x[0]) == 2:
		return default_matrix_multiplication(x, y)

	a, b, c, d = split(x)
	e, f, g, h = split(y)
	p1 = strassen_mult_sq(a, sub_matrix(f, h)) 
	p2 = strassen_mult_sq(add_matrix(a, b), h)	 
	p3 = strassen_mult_sq(add_matrix(c, d), e)	 
	p4 = strassen_mult_sq(d, sub_matrix(g, e))	 
	p5 = strassen_mult_sq(add_matrix(a, d), add_matrix(e, h))	 
	p6 = strassen_mult_sq(sub_matrix(b, d), add_matrix(g, h)) 
	p7 = strassen_mult_sq(sub_matrix(a, c), add_matrix(e, f)) 

	c11 = add_matrix(sub_matrix(add_matrix(p5, p4), p2), p6) 
	c12 = add_matrix(p1, p2)		 
	c21 = add_matrix(p3, p4)		 
	c22 = sub_matrix(sub_matrix(add_matrix(p1,p5), p3), p7) 

	C = []
	for i in range(len(c12)):
		C.append(c11[i] + c12[i])

	for i in range(len(c21)):
		C.append(c21[i] + c22[i])
	return C 
		
def strassen_mult(matrix1, matrix2):
	if len(matrix1[0]) != len(matrix2):
		raise Exception(
			f"Unable to multiply these matrices, please check the dimensions. \n"
			
		)
	dimension1 = [len(matrix1), len(matrix1[0])]
	dimension2 = [len(matrix2), len(matrix2[0])]
 
	maximum = max(max(dimension1), max(dimension2))
	maxim = int(pow(2, ceil(log2(maximum))))
	new_matrix1 = deepcopy(matrix1)
	new_matrix2 = deepcopy(matrix2)
 
	for i in range(0, maxim):
		if i < dimension1[0]:
			for j in range(dimension1[1], maxim):
				new_matrix1[i].append(0)
		else:
			new_matrix1.append([0] * maxim)
		if i < dimension2[0]:
			for j in range(dimension2[1], maxim):
				new_matrix2[i].append(0)
		else:
			new_matrix2.append([0] * maxim)
 
	final_matrix = strassen_mult_sq(new_matrix1, new_matrix2)
 
	# Removing the additional zeros
	for i in range(0, maxim):
		if i < dimension1[0]:
			for j in range(dimension2[1], maxim):
				final_matrix[i].pop()
		else:
			final_matrix.pop()
	return final_matrix