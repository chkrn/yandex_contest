/*
D. Генерация скобочных последовательностей

Ограничение времени	1 секунда
Ограничение памяти	20Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

Дано целое число n. Требуется вывести все правильные скобочные последовательности длины 2 ⋅ n, упорядоченные лексикографически (см. https://ru.wikipedia.org/wiki/Лексикографический_порядок).

В задаче используются только круглые скобки.

Желательно получить решение, которое работает за время, пропорциональное общему количеству правильных скобочных последовательностей в ответе, и при этом использует объём памяти, пропорциональный n.

Формат ввода
Единственная строка входного файла содержит целое число n, 0 ≤ n ≤ 11

Формат вывода
Выходной файл содержит сгенерированные правильные скобочные последовательности, упорядоченные лексикографически.

Пример 1

Ввод	Вывод
2		(())
		()()
Пример 2

Ввод	Вывод
3		((()))
		(()())
		(())()
		()(())
		()()()
*/
#include <iostream>
#include <deque>

static std::deque<bool> line;

static void step(int left, int right) {
	if(left) {
		line.push_back(true);
		step(left - 1, right);
		line.pop_back();
	}

	if(right) {
		if(right > left) {
			line.push_back(false);
			step(left, right - 1);
			line.pop_back();
		}
		
		return;
	}

	for(bool i: line)
		std::cout << (i ? '(' : ')');
		
	std::cout << std::endl;
}


int main() {
	int n;
	std::cin >> n;

	step(n, n);

	return 0;
}
