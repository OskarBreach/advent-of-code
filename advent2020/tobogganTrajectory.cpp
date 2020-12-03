#include "tobogganTrajectory.h"

namespace advent2020::tobagganTrajectory {
	size_t treesEncountered(const std::vector<std::string>& treeMap, size_t right, size_t down) {
		size_t ret{ 0 };

		for (size_t x{ 0 }, y{ 0 }; y < treeMap.size(); y += down) {
			constexpr char tree{ '#' };
			const auto treeRow{ treeMap[y] };
			if (treeRow[x] == tree) {
				++ret;
			}
			x += right;
			x %= treeRow.length();
		}

		return ret;
	}
}
