// https://habr.com/ru/company/yandex/blog/206234/
// По условию задачи у вас есть формула с цифрами, операциями +-*/ и скобками.
// Нужно написать программу, которая ее вычисляет.

// Сборка: make

// Примеры:
//
// $ echo '3 + 55 / (7 + 4)' | ./calc
// Input:
// 3 + 55 / 7 + 4
// > pri = 2
// 7 + 4
// > pri = 1
// 55 / 11
// > pri = 0
// 3 + 5
// Answer:
// 8
//
// echo '( (2 + 5) * 3 ) * ( 3 - 1 ) + 55 / (7 + 4)' | ./calc
// Input:
// 2 + 5 * 3 * 3 - 1 + 55 / 7 + 4
// > pri = 4
// 2 + 5
// > pri = 3
// 7 * 3
// > pri = 2
// 3 - 1
// 7 + 4
// > pri = 1
// 21 * 2
// 55 / 11
// > pri = 0
// 42 + 5
// Answer:
// 47
//


#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <utility>

enum class Reading {
	start,
	integer,
	oper,
	leftBracket,
	rightBracket
};

enum class Oper {
	no,
	minus,
	plus,
	mul,
	div
};

static void printList(std::list<int> list) {
	for(int i: list)
		if(i >= 0)
			std::cout << i << " ";
		else
			std::cout << static_cast<char>(-i) << " ";

	std::cout << std::endl;
}

static std::pair<
					std::list<int>,
					std::map<
								unsigned,
								std::vector<std::list<int>::iterator>,
								std::greater<unsigned>
							>
				> readToList() {

	std::list<int> list;
	std::map<unsigned, std::vector<std::list<int>::iterator>, std::greater<unsigned>> prio;

	char s;
	int integerInput = 0;
	int leftBrackets = 0;
	int rightBrackets = 0;
	Reading reading = Reading::start;

	while(std::cin >> s) {
		if(s >= '0' && s <= '9') {
			if(reading == Reading::integer)
				integerInput *= 10;
			integerInput += (s - '0');
			reading = Reading::integer;
		} else if(s == '+' || s == '-' || s == '*' || s == '/') {
			if(reading != Reading::integer && reading != Reading::rightBracket)
				throw std::runtime_error("Operator not after integer value or right bracket");

			if(reading == Reading::integer) {
				list.push_back(integerInput);
				integerInput = 0;
			}

			list.push_back(-s);
			reading = Reading::oper;

			// Вот здесь несложно расширить приоритет и добавить поддержку новых операторов
			unsigned curPrio = (leftBrackets - rightBrackets) * 2;
			if(s == '*' || s == '/')
				curPrio += 1;
			prio[curPrio].push_back(std::prev(list.end()));
			
		} else if(s == '(') {
			leftBrackets++;

			if(reading != Reading::start && reading != Reading::leftBracket && reading != Reading::oper)
				throw std::runtime_error("Left bracket not after operator or left bracket or at start");

			reading = Reading::leftBracket;
		} else if(s == ')') {
			rightBrackets++;

			if(reading != Reading::integer && reading != Reading::rightBracket)
				throw std::runtime_error("Right bracket not after integer or another right bracket");

			if(rightBrackets > leftBrackets)
				throw std::runtime_error("Detected more right brackets than left");

			if(reading == Reading::integer) {
				list.push_back(integerInput);
				integerInput = 0;
			}

			reading = Reading::rightBracket;
		}
	}

	if(reading != Reading::integer && reading != Reading::rightBracket)
		throw std::runtime_error("Not integer and not right bracket at the end of input");

	if(rightBrackets != leftBrackets)
		throw std::runtime_error("Left and right brackets nums mismatch (after all input analyze)");

	if(reading == Reading::integer) {
		list.push_back(integerInput);
		integerInput = 0;
	}

	return std::pair<std::list<int>, std::map<unsigned, std::vector<std::list<int>::iterator>, std::greater<unsigned>>>
		(std::move(list), std::move(prio));
}

int main() {
try {
	auto listAndPrio = readToList();

	std::cout << "Input:" << std::endl;
	printList(listAndPrio.first);

	for(auto v : listAndPrio.second) {
		std::cout << "> pri = " << v.first << std::endl;
		for(auto i : v.second) {

			switch(*i) {
				case -'+':
					std::cout << *std::prev(i) << " + " << *std::next(i) << std::endl;
					*std::prev(i) += *std::next(i);
				break;
				case -'-':
					std::cout << *std::prev(i) << " - " << *std::next(i) << std::endl;
					*std::prev(i) -= *std::next(i);
				break;
				case -'*':
					std::cout << *std::prev(i) << " * " << *std::next(i) << std::endl;
					*std::prev(i) *= *std::next(i);
				break;
				case -'/':
					std::cout << *std::prev(i) << " / " << *std::next(i) << std::endl;
					*std::prev(i) /= *std::next(i);
				break;
				default:
				throw std::runtime_error("Unexpected operator");
			}
			listAndPrio.first.erase(std::next(i));
			listAndPrio.first.erase(i);
		}
	}

	std::cout << "Answer:" << std::endl << listAndPrio.first.front() << std::endl;

	return 0;
} catch(const std::runtime_error& e) {
	std::cerr << "ERROR: " << e.what() << std::endl;
	return 1;
}
}
