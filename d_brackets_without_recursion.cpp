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
#include <vector>

static int n, left, right, depth = 0;
static bool fwd = true;
static std::vector<bool> line;


static bool forward(bool value) {
	if(value)
		left--;
	else
		right--;

	line[depth] = value;
	depth++;
	fwd = true;
	return true;
}

static bool back() {
	if(depth == 0)
		return false;
	depth--;

	if(line[depth])
		left++;
	else
		right++;

	fwd = false;
	return true;
}

static bool tick() {
	if(fwd) {
		if(left)
			return forward(true);
		else if(right == 1) {
			forward(false);
			for(bool i: line)
				std::cout << (i ? '(' : ')');
			std::cout << std::endl;
			return back();
		} else if(right > left)
			return forward(false);
		else
			return back();
	} else { // back
		if(line[depth] && right > left) {
			return forward(false);
		} else {
			return back();
		}
	}
}

int main() {
	std::cin >> n;
	
	line.resize(n * 2);
	left = right = n;

	while(tick())
		;
	
	return 0;
}

