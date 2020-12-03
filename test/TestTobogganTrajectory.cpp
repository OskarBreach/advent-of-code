#include "AutoRun.h"

#include "tobogganTrajectory.h"

namespace TestTobogganTrajectory {
	using gppUnit::equals;
	class Base : public Auto::TestCase {
		std::vector<std::string> treeMap{
			"..##.......",
			"#...#...#..",
			".#....#..#.",
			"..#.#...#.#",
			".#...##..#.",
			"..#.##.....",
			".#.#.#....#",
			".#........#",
			"#.##...#...",
			"#...##....#",
			".#..#...#.#"
		};

		size_t right{ 0 };
		size_t down{ 0 };

	protected: 
		void givenTreeMap() {}

		void whenTrajectory(size_t right_, size_t down_) {
			right = right_;
			down = down_;
		}

		void thenTreesEncountered(size_t expected) {
			auto actual{ advent2020::tobagganTrajectory::treesEncountered(treeMap, right, down) };
			confirm.that(actual, equals(expected), __FUNCTION__);
		}
	};

	class TestGivenTrajectory : Base {
		void test() {
			givenTreeMap();
			whenTrajectory(3, 1);
			thenTreesEncountered(7);
		}
	} GPPUNIT_INSTANCE;

	class TestStraightDownTrajectory : Base {
		void test() {
			givenTreeMap();
			whenTrajectory(0, 1);
			thenTreesEncountered(3);
		}
	} GPPUNIT_INSTANCE;

	class TestOtherTrajectory : Base {
		void test() {
			givenTreeMap();
			whenTrajectory(1, 1);
			thenTreesEncountered(2);
		}
	} GPPUNIT_INSTANCE;

	class TestFastStraightDownTrajectory : Base {
		void test() {
			givenTreeMap();
			whenTrajectory(0, 2);
			thenTreesEncountered(1);
		}
	} GPPUNIT_INSTANCE;
}
