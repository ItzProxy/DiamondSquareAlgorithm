#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DiamondSquare/PointValue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(PointTest)
	{
	public:
		
		float threshold = 0.05f;

		TEST_METHOD(MidPoint)
		{
			Point test1 = Point(
				5, 5
			);
			Point test2 = Point(
				0, 0
			);
			Assert::AreEqual(Point(2,2), test1.findMidPoint(test2));
		}

		TEST_METHOD(Check_X) {
			Point test = Point(
				5, 6
			);
			Assert::AreEqual(5, test.getX());
		}

		TEST_METHOD(CHECK_Y) {
			Point test = Point(
				5, 6
			);
			Assert::AreEqual(6, test.getY());
		}

		TEST_METHOD(CHECK_VAL) {
			PointValue test1 = PointValue(
				5, 5, 10
			);
			Assert::IsTrue((float)10 - test1.getValue() <= threshold);
		}

	};

	TEST_CLASS(DiamondSquareMethod) {
		TEST_METHOD()
	};
}