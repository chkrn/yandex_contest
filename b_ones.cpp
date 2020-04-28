/*
B. Последовательно идущие единицы

Ограничение времени	1 секунда
Ограничение памяти	64Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

Требуется найти в бинарном векторе самую длинную последовательность единиц и вывести её длину.

Желательно получить решение, работающее за линейное время и при этом проходящее по входному массиву только один раз.

Формат ввода

Первая строка входного файла содержит одно число n, n ≤ 10000. Каждая из следующих n строк содержит ровно одно число — очередной элемент массива.

Формат вывода

Выходной файл должен содержать единственное число — длину самой длинной последовательности единиц во входном массиве.

Пример
Ввод	Вывод
5		1
1
0
1
0
1
*/
#include <iostream>

int main() {
	int n, curValue, curLen = 0, maxLen = 0;
	std::cin >> n;

	for(int i = 0; i < n; i++) {
		std::cin >> curValue;
		
		if(curValue != 1) {
			if(curLen > maxLen)
				maxLen = curLen;
			
			curLen = 0;
			continue;
		}
		
		curLen++;
	}
	
	if(curLen > maxLen)
		maxLen = curLen;

	std::cout << maxLen;

	return 0;
}