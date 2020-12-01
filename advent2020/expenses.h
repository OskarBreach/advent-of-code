#pragma once

#include <vector>

namespace advent2020::expenses {
	std::vector<uint32_t> findTwoExpensesSummingToTarget(const std::vector<uint32_t>& expenses, uint32_t target);
	std::vector<uint32_t> findThreeExpensesSummingToTarget(const std::vector<uint32_t>& expenses, uint32_t target);
}
