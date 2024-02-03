from dataclasses import dataclass
from time import process_time

from matrix import *
TIMES = 1
@dataclass
class TimeTest:
	to_ms = 1000
	iters = 30
	min_size = 10
	max_size = 110
	step = 10
	odd = 1


def get_time_alg(alg, A, B):
	start = process_time()
	for _ in range(TIMES):
		alg(A, B)
	result = process_time() - start

	return result / TIMES

def time_strassen_mult(matrix1, matrix2):
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
				  
	start = process_time()
	for _ in range(TIMES):
		final_matrix = strassen_mult_sq(new_matrix1, new_matrix2)
	result = process_time() - start
 
	return result

def time_test(size_type):
	"""
		Проведение временных замеров 
		работы алгоритмов умножения 
		матриц в зависимости
		от четности размера.
	"""

	algorithms = [standard_mult,
				  winograd_mult,
				  optimized_winograd_mult,
				  strassen_mult]
	results = [[], [], [], []]

	if size_type == TimeTest.odd:
		start, stop = TimeTest.min_size + 1, TimeTest.max_size + 1
	else:
		start, stop = TimeTest.min_size, TimeTest.max_size

	for alg in enumerate(algorithms):
		for n in range(start, stop, TimeTest.step):
			result = 0
			A = create_random_matrix(n)
			B = create_random_matrix(n)
				
			for _ in range(TimeTest.iters):
				if (alg == strassen_mult):
					result = time_strassen_mult(A, B)
				else:
					result += get_time_alg(alg[1], A, B)
			print("Progress:\t", n, "%")

			results[alg[0]].append(result / TimeTest.iters)
	
	return results

def measure_time():
	"""
		Проведение временных замеров 
		работы алгоритмов умножения
		матриц.
	"""

	print("Выберите тип размера:\n" + \
		  "  1 - нечетный;\n" + \
		  "  2 - четный.")
	size_type = int(input("Выбор: "))

	results = time_test(size_type)
	
	return results, size_type

	
def print_time():
	results, size_type = measure_time()
	msgs = ["нечетного",
			"четного"]

	print("\n\nРезультаты замеров времени для " + msgs[size_type - 1] + " размера:\n")

	i = 0

	if size_type == TimeTest.odd:
		start, stop = TimeTest.min_size + 1, TimeTest.max_size + 1
	else:
		start, stop = TimeTest.min_size, TimeTest.max_size

	for size in range(start, stop, TimeTest.step):
		print(" %4d & %.4f & %.4f & %.4f & %.4f\n " %(size, \
			results[0][i] * TimeTest.to_ms, \
			results[1][i] * TimeTest.to_ms,
			results[2][i] * TimeTest.to_ms, \
			results[3][i] * TimeTest.to_ms))
		i += 1
