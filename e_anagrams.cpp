/*
E. Анаграммы

Ограничение времени	1 секунда
Ограничение памяти	20Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

Даны две строки, состоящие из строчных латинских букв. Требуется определить, являются ли эти строки анаграммами, т. е. отличаются ли они только порядком следования символов.

Формат ввода
Входной файл содержит две строки строчных латинских символов, каждая не длиннее 100 000 символов. Строки разделяются символом перевода строки.

Формат вывода
Выходной файл должен содержать единицу, если строки являются анаграммами, и ноль в противном случае.

Пример 1

Ввод	Вывод
qiu		1
iuq

Пример 2

Ввод	Вывод
zprl	2
zprc
0
*/
#include <iostream>
#include <vector>

static inline int index(int symbol) {
	return symbol - 'a';
}

int main() {
	std::string line1, line2;
	std::cin >> line1 >> line2;

	if(line1.size() != line2.size()) {
		std::cout << 0;
		return 0;
	}

	std::vector<int> st1, st2;
	st1.resize(index('z') + 1, 0);
	st2.resize(st1.size(), 0);

	for(int c: line1)
		st1.at(index(c))++;
				
	for(int c: line2)
		st2.at(index(c))++;

	for(int i = 0; i < st1.size(); i++)
		if(st1[i] != st2[i]) {
			std::cout << 0;
			return 0;
		}

	std::cout << 1;
	return 0;
}
