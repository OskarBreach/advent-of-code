#include "expenses.h"

namespace advent2020::expenses {
	std::vector<uint32_t> findTwoExpensesSummingToTarget(const std::vector<uint32_t>& expenses, uint32_t target) {
		for (const auto& expense1 : expenses) {
			for (const auto& expense2 : expenses) {
				if (expense1 + expense2 == target) {
					return { expense1, expense2 };
				}
			}
		}
		return {};
	}

	std::vector<uint32_t> findThreeExpensesSummingToTarget(const std::vector<uint32_t>& expenses, uint32_t target) {
		for (const auto& expense1 : expenses) {
			for (const auto& expense2 : expenses) {
				for (const auto& expense3 : expenses) {
					if (expense1 + expense2 + expense3 == target) {
						return { expense1, expense2, expense3 };
					}
				}
			}
		}
		return {};
	}
}
