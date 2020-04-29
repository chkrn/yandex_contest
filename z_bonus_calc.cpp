// https://habr.com/ru/company/yandex/blog/206234/
// По условию задачи у вас есть формула с цифрами, операциями +-*/ и скобками.
// Нужно написать программу, которая ее вычисляет.

// Build: make

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
								std::vector<std::list<int>::iterator>
							>
				> readToList() {

	std::list<int> list;
	std::map<unsigned, std::vector<std::list<int>::iterator>> prio;

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

			unsigned curPrio = leftBrackets * 2;
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

	return std::pair<std::list<int>, std::map<unsigned, std::vector<std::list<int>::iterator>>>
		(std::move(list), std::move(prio));
}

int count(const std::list<int>& list, std::list<int>::const_iterator& i) {
	int rval = 0;
	Oper oper = Oper::no;

	while(i != list.end()) {
		if(*i >= 0) {
			if(oper == Oper::no || oper == Oper::plus)
				rval += *i;
			else
				rval -= *i;
			++i;
		} else if(*i == -'-') {
			oper = Oper::minus;
			++i;
		} else if(*i == -'+') {
			oper = Oper::plus;
			++i;
		} else if(*i == -'(') {
			if(oper == Oper::no || oper == Oper::plus)
				rval += count(list, ++i);
			else
				rval -= count(list, ++i);
		} else if(*i == -')') {
			++i;
			break;
		}
	}

	return rval;
}

int main() {
try {
	auto listAndPrio = readToList();

	std::cout << "Input:" << std::endl;
	printList(listAndPrio.first);

	//std::cout << "Answer:" << std::endl;
	//std::list<int>::const_iterator begin = list.begin();
	//std::cout << count(list, begin) << std::endl;

	return 0;
} catch(const std::runtime_error& e) {
	std::cerr << "ERROR: " << e.what() << std::endl;
	return 1;
}
}
