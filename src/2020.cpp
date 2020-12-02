#include "2020.h"

#include "expenses.h"
#include "tobogganPasswords.h"

#include "parsing.h"

#include <iostream>

namespace {
	void printDay01Solutions() {
		const auto expenses{ parsing::getVector<uint32_t>("2020/input01.txt") };
		constexpr uint32_t target{ 2020 };

		const auto twoMatchingExpenses{ advent2020::expenses::findTwoExpensesSummingToTarget(expenses, target) };
		const auto threeMatchingExpenses{ advent2020::expenses::findThreeExpensesSummingToTarget(expenses, target) };

		std::cout << "Day 01:\n"
			<< "Part 1: " << twoMatchingExpenses[0] * twoMatchingExpenses[1] 
			<< " (" << twoMatchingExpenses[0] << " * " << twoMatchingExpenses[1] << ")\n"
			<< "Part 2: " << threeMatchingExpenses[0] * threeMatchingExpenses[1] * threeMatchingExpenses [2] 
			<< " (" << threeMatchingExpenses[0] << " * " << threeMatchingExpenses[1] << " * " << threeMatchingExpenses[2] << ")\n"
			<< '\n';
	}
	void printDay02Solutions() {
		const auto passwords{ parsing::getVector<std::string>("2020/input02.txt") };

		size_t acceptedByOldScheme{ 0 };
		size_t acceptedByNewScheme{ 0 };

		for (const auto& password : passwords) {
			if (advent2020::tobogganPasswords::passwordValidOldScheme(password)) {
				++acceptedByOldScheme;
			}
			if (advent2020::tobogganPasswords::passwordValidNewScheme(password)) {
				++acceptedByNewScheme;
			}
		}

		std::cout << "Day 02:\n"
			<< "Part 1: " << acceptedByOldScheme << '\n'
			<< "Part 2: " << acceptedByNewScheme << '\n'
			<< '\n';
	}
}

void print2020Solutions() {
	std::cout << "Advent of Code 2020:" << "\n";
	printDay01Solutions();
	printDay02Solutions();
}
