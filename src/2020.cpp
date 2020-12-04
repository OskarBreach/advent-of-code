#include "2020.h"

#include "expenses.h"
#include "tobogganPasswords.h"
#include "tobogganTrajectory.h"
#include "passportProcessing.h"

#include "parsing.h"

#include <iostream>

namespace {
	void printDay01Solutions() {
		auto expenses{ parsing::getVector<uint32_t>("2020/input01.txt") };
		constexpr uint32_t target{ 2020 };

		auto twoMatchingExpenses{ advent2020::expenses::findTwoExpensesSummingToTarget(expenses, target) };
		auto threeMatchingExpenses{ advent2020::expenses::findThreeExpensesSummingToTarget(expenses, target) };

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
	void printDay03Solutions() {
		auto treeMap{ parsing::getVector<std::string>("2020/input03.txt") };

		auto te11{ advent2020::tobagganTrajectory::treesEncountered(treeMap, 1, 1) };
		auto te31{ advent2020::tobagganTrajectory::treesEncountered(treeMap, 3, 1) };
		auto te51{ advent2020::tobagganTrajectory::treesEncountered(treeMap, 5, 1) };
		auto te71{ advent2020::tobagganTrajectory::treesEncountered(treeMap, 7, 1) };
		auto te12{ advent2020::tobagganTrajectory::treesEncountered(treeMap, 1, 2) };

		std::cout << "Day 03:\n"
			<< "Part 1: " << te31 << '\n'
			<< "Part 2: " << te11 * te31 * te51 * te71 * te12
			<< " (" << te11 << " * " << te31 << " * " << te51 << " * " << te71 << " * " << te12 << ")\n"
			<< '\n';
	}
	void printDay04Solutions() {
		auto batchFile{ parsing::getVector<std::string>("2020/input04.txt") };
		const auto passports{ advent2020::passportProcessing::passportsFromBatchFile(std::move(batchFile)) };

		size_t passportsContainingAllRequiredFields{ 0 };
		size_t validPassports{ 0 };

		for (const auto& passport : passports) {
			if (advent2020::passportProcessing::passportContainsAllRequiredFields(passport)) {
				++passportsContainingAllRequiredFields;
				if (advent2020::passportProcessing::passportValid(passport)) {
					++validPassports;
				}
			}
		}

		std::cout << "Day 04:\n"
			<< "Part 1: " << passportsContainingAllRequiredFields << '\n'
			<< "Part 2: " << validPassports << '\n'
			<< '\n';
	}
}

void print2020Solutions() {
	std::cout << "Advent of Code 2020:" << "\n";
	printDay01Solutions();
	printDay02Solutions();
	printDay03Solutions();
	printDay04Solutions();
}
