/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file matrixTest.cpp
 * @author Alexander Entinger, BSc
 * @brief test class for matrix template class
 */

#include "matrixTest.h"
#include "matrix.h"
#include <stdlib.h>
#include <time.h>

TEST_F(matrixTest, testConstructor) {
	// empty matrix (default ctor)
	matrix<unsigned int> m1;
	ASSERT_EQ(m1.getCols(), (unsigned int)(0));
	ASSERT_EQ(m1.getRows(), (unsigned int)(0));

	// matrix with one element
	matrix<unsigned int> m2(1, 1);
	ASSERT_EQ(m2.getCols(), (unsigned int)(1));
	ASSERT_EQ(m2.getRows(), (unsigned int)(1));
	*(m2.at(0, 0)) = 5;
	ASSERT_EQ(*(m2.at(0, 0)), (unsigned int)(5));
	*(m2.at(0, 0)) = 7;
	ASSERT_EQ(*(m2.at(0,0)), (unsigned int)(7));

	// vector with two elements (vertically)
	matrix<unsigned int> v1(2, 1);
	ASSERT_EQ(v1.getCols(), (unsigned int)(1));
	ASSERT_EQ(v1.getRows(), (unsigned int)(2));
	*(v1.at(0, 0)) = 1;
	*(v1.at(0, 1)) = 2;
	ASSERT_EQ(*(v1.at(0,0)), (unsigned int)(1));
	ASSERT_EQ(*(v1.at(0,1)), (unsigned int)(2));

	// vector with two elements (horizontally)
	matrix<unsigned int> v2(1, 2);
	ASSERT_EQ(v2.getCols(), (unsigned int)(2));
	ASSERT_EQ(v2.getRows(), (unsigned int)(1));
	*(v2.at(0, 0)) = 1;
	*(v2.at(1, 0)) = 2;
	ASSERT_EQ(*(v2.at(0,0)), (unsigned int)(1));
	ASSERT_EQ(*(v2.at(1,0)), (unsigned int)(2));

	// 2x2 matrix
	matrix<unsigned int> m3(2, 2);
	ASSERT_EQ(m3.getCols(), (unsigned int)(2));
	ASSERT_EQ(m3.getRows(), (unsigned int)(2));
	*(m3.at(0, 0)) = 1;
	*(m3.at(1, 0)) = 2;
	*(m3.at(0, 1)) = 3;
	*(m3.at(1, 1)) = 4;
	ASSERT_EQ(*(m3.at(0,0)), (unsigned int)(1));
	ASSERT_EQ(*(m3.at(1,0)), (unsigned int)(2));
	ASSERT_EQ(*(m3.at(0,1)), (unsigned int)(3));
	ASSERT_EQ(*(m3.at(1,1)), (unsigned int)(4));

	// 2x3 matrix
	matrix<unsigned int> m4(2, 3);
	ASSERT_EQ(m4.getCols(), (unsigned int)(3));
	ASSERT_EQ(m4.getRows(), (unsigned int)(2));
	*(m4.at(0, 0)) = 1;
	*(m4.at(1, 0)) = 2;
	*(m4.at(2, 0)) = 3;
	*(m4.at(0, 1)) = 4;
	*(m4.at(1, 1)) = 5;
	*(m4.at(2, 1)) = 6;
	ASSERT_EQ(*(m4.at(0,0)), (unsigned int)(1));
	ASSERT_EQ(*(m4.at(1,0)), (unsigned int)(2));
	ASSERT_EQ(*(m4.at(2,0)), (unsigned int)(3));
	ASSERT_EQ(*(m4.at(0,1)), (unsigned int)(4));
	ASSERT_EQ(*(m4.at(1,1)), (unsigned int)(5));
	ASSERT_EQ(*(m4.at(2,1)), (unsigned int)(6));
}

TEST_F(matrixTest, testSetIdentity) {
	matrix<unsigned int> m1;
	m1.setIdentity(0);
	ASSERT_EQ(m1.getCols(), (unsigned int)(0));
	ASSERT_EQ(m1.getRows(), (unsigned int)(0));

	m1.setIdentity(1);
	ASSERT_EQ(m1.getCols(), (unsigned int)(1));
	ASSERT_EQ(m1.getRows(), (unsigned int)(1));
	ASSERT_EQ(*(m1.at(0,0)), (unsigned int)(1));

	m1.setIdentity(2);
	ASSERT_EQ(m1.getCols(), (unsigned int)(2));
	ASSERT_EQ(m1.getRows(), (unsigned int)(2));
	ASSERT_EQ(*(m1.at(0,0)), (unsigned int)(1));
	ASSERT_EQ(*(m1.at(1,0)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(0,1)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(1,1)), (unsigned int)(1));

	m1.setIdentity(3);
	ASSERT_EQ(m1.getCols(), (unsigned int)(3));
	ASSERT_EQ(m1.getRows(), (unsigned int)(3));
	ASSERT_EQ(*(m1.at(0,0)), (unsigned int)(1));
	ASSERT_EQ(*(m1.at(1,0)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(2,0)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(0,1)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(1,1)), (unsigned int)(1));
	ASSERT_EQ(*(m1.at(2,1)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(0,2)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(1,2)), (unsigned int)(0));
	ASSERT_EQ(*(m1.at(2,2)), (unsigned int)(1));

	matrix<float> m2;
	m2.setIdentity(2);
	ASSERT_EQ(m2.getCols(), (unsigned int)(2));
	ASSERT_EQ(m2.getRows(), (unsigned int)(2));
	ASSERT_FLOAT_EQ(*(m2.at(0,0)), (float)(1.0));
	ASSERT_FLOAT_EQ(*(m2.at(1,0)), (float)(0.0));
	ASSERT_FLOAT_EQ(*(m2.at(0,1)), (float)(0.0));
	ASSERT_FLOAT_EQ(*(m2.at(1,1)), (float)(1.0));

	matrix<double> m3;
	m3.setIdentity(1);
	ASSERT_EQ(m3.getCols(), (unsigned int)(1));
	ASSERT_EQ(m3.getRows(), (unsigned int)(1));
	ASSERT_DOUBLE_EQ(*(m3.at(0,0)), (double)(1.0));
}

TEST_F(matrixTest, testAssignmentOperator) {
	matrix<unsigned int> m1(2, 2);
	*(m1.at(0, 0)) = 1;
	*(m1.at(1, 0)) = 2;
	*(m1.at(0, 1)) = 3;
	*(m1.at(1, 1)) = 4;

	matrix<unsigned int> m2(1, 1);
	ASSERT_EQ(m2.getCols(), (unsigned int)(1));
	ASSERT_EQ(m2.getRows(), (unsigned int)(1));

	m2 = m1;
	ASSERT_EQ(m2.getCols(), m1.getCols());
	ASSERT_EQ(m2.getRows(), m1.getRows());
	for (unsigned int y = 0; y < m2.getRows(); y++) {
		for (unsigned int x = 0; x < m2.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x,y)), *(m2.at(x,y)));
		}
	}
}

TEST_F(matrixTest, testCopyConstructor) {
	matrix<unsigned int> m1(2, 2);
	*(m1.at(0, 0)) = 1;
	*(m1.at(1, 0)) = 2;
	*(m1.at(0, 1)) = 3;
	*(m1.at(1, 1)) = 4;

	matrix<unsigned int> m2(m1);
	ASSERT_EQ(m2.getCols(), m1.getCols());
	ASSERT_EQ(m2.getRows(), m1.getRows());
	for (unsigned int y = 0; y < m2.getRows(); y++) {
		for (unsigned int x = 0; x < m2.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x,y)), *(m2.at(x,y)));
		}
	}
}

TEST_F(matrixTest, testScalarAddition) {
	matrix<unsigned int> m1(2, 2);

	unsigned int cnt = 0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			*(m1.at(x, y)) = cnt;
			cnt++;
		}
	}

	matrix<unsigned int> m2(m1);

	m1 = m1 + 2;
	m2 += 2;

	cnt = 0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x, y)), cnt + 2);
			ASSERT_EQ(*(m2.at(x, y)), cnt + 2);
			cnt++;
		}
	}
}

TEST_F(matrixTest, testScalarSubtraction) {
	matrix<int> m1(2, 2);

	int cnt = 0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			*(m1.at(x, y)) = cnt;
			cnt++;
		}
	}

	matrix<int> m2(m1);

	m1 = m1 - 2;
	m2 -= 2;

	cnt = 0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x, y)), cnt - 2);
			ASSERT_EQ(*(m2.at(x, y)), cnt - 2);
			cnt++;
		}
	}
}

TEST_F(matrixTest, testScalarMultiplication) {
	matrix<unsigned int> m1(2, 2);

	unsigned int cnt = 0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			*(m1.at(x, y)) = cnt;
			cnt++;
		}
	}

	matrix<unsigned int> m2(m1);

	m1 = m1 * 2;
	m2 *= 2;

	cnt = 0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x, y)), cnt * 2);
			ASSERT_EQ(*(m2.at(x, y)), cnt * 2);
			cnt++;
		}
	}
}

TEST_F(matrixTest, testScalarDivsion) {
	matrix<float> m1(2, 2);

	float cnt = 0.0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			*(m1.at(x, y)) = cnt;
			cnt += 1.0;
		}
	}

	matrix<float> m2(m1);

	m1 = m1 / 2.0;
	m2 /= 2.0;

	cnt = 0.0;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_FLOAT_EQ(*(m1.at(x, y)), cnt / 2.0);
			ASSERT_FLOAT_EQ(*(m2.at(x, y)), cnt / 2.0);
			cnt += 1.0;
		}
	}
}

TEST_F(matrixTest, testMatrixAddition) {

	srand(time(NULL));

	matrix<unsigned int> m1(2, 3);
	matrix<unsigned int> m2(2, 3);
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			*(m1.at(x, y)) = rand() % 10;
			*(m2.at(x, y)) = rand() % 10;
		}
	}
	matrix<unsigned int> m3;
	m3 = m1 + m2;
	ASSERT_EQ(m3.getRows(), m1.getRows());
	ASSERT_EQ(m3.getCols(), m1.getCols());
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x, y)) + *(m2.at(x, y)), *(m3.at(x,y)));
		}
	}

	m1 += m2;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x, y)), *(m3.at(x,y)));
		}
	}
}

TEST_F(matrixTest, testMatrixSubtraction) {

	srand(time(NULL));

	matrix<int> m1(2, 3);
	matrix<int> m2(2, 3);
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			*(m1.at(x, y)) = rand() % 10;
			*(m2.at(x, y)) = rand() % 10;
		}
	}
	matrix<int> m3;
	m3 = m1 - m2;
	ASSERT_EQ(m3.getRows(), m1.getRows());
	ASSERT_EQ(m3.getCols(), m1.getCols());
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x, y)) - *(m2.at(x, y)), *(m3.at(x,y)));
		}
	}

	m1 -= m2;
	for (unsigned int y = 0; y < m1.getRows(); y++) {
		for (unsigned int x = 0; x < m1.getCols(); x++) {
			ASSERT_EQ(*(m1.at(x, y)), *(m3.at(x,y)));
		}
	}
}

TEST_F(matrixTest, testMatrixMultiplication) {

	matrix<unsigned int> m1(1, 1);
	matrix<unsigned int> m2(1, 1);
	*(m1.at(0, 0)) = 2;
	*(m2.at(0, 0)) = 3;
	matrix<unsigned int> m3;
	m3 = m1 * m2;
	ASSERT_EQ(m1.getCols(), m3.getCols());
	ASSERT_EQ(m1.getRows(), m3.getRows());
	ASSERT_EQ(*(m3.at(0,0)), (unsigned int)(2*3));
	m1 *= m2;
	ASSERT_EQ(*(m3.at(0,0)), *(m1.at(0,0)));

	matrix<unsigned int> m4(2, 3);
	*(m4.at(0, 0)) = 1;
	*(m4.at(1, 0)) = 2;
	*(m4.at(2, 0)) = 3;
	*(m4.at(0, 1)) = 4;
	*(m4.at(1, 1)) = 5;
	*(m4.at(2, 1)) = 6;
	matrix<unsigned int> m5(3, 2);
	*(m5.at(0, 0)) = 1;
	*(m5.at(1, 0)) = 2;
	*(m5.at(0, 1)) = 3;
	*(m5.at(1, 1)) = 4;
	*(m5.at(0, 2)) = 5;
	*(m5.at(1, 2)) = 6;
	matrix<unsigned int> m6;
	m6 = m4 * m5;
	//std::cout << "m4 = " << std::endl << m4 << std::endl;
	//std::cout << "m5 = " << std::endl << m5 << std::endl;
	//std::cout << "m6 = " << std::endl << m6 << std::endl;
	ASSERT_EQ(m6.getRows(), (unsigned int)(2));
	ASSERT_EQ(m6.getCols(), (unsigned int)(2));
	ASSERT_EQ(*(m6.at(0,0)), (unsigned int)(22));
	ASSERT_EQ(*(m6.at(1,0)), (unsigned int)(28));
	ASSERT_EQ(*(m6.at(0,1)), (unsigned int)(49));
	ASSERT_EQ(*(m6.at(1,1)), (unsigned int)(64));

}

TEST_F(matrixTest, testTranspose) {
	matrix<unsigned int> m1(2, 2);
	*(m1.at(0, 0)) = 1;
	*(m1.at(1, 0)) = 2;
	*(m1.at(0, 1)) = 3;
	*(m1.at(1, 1)) = 4;
	matrix<unsigned int> m3;
	m3 = m1.transpose();
	ASSERT_EQ(*(m3.at(0, 0)), (unsigned int)(1));
	ASSERT_EQ(*(m3.at(1, 0)), (unsigned int)(3));
	ASSERT_EQ(*(m3.at(0, 1)), (unsigned int)(2));
	ASSERT_EQ(*(m3.at(1, 1)), (unsigned int)(4));

	matrix<unsigned int> m2(2, 3);
	*(m2.at(0, 0)) = 1;
	*(m2.at(1, 0)) = 2;
	*(m2.at(2, 0)) = 3;
	*(m2.at(0, 1)) = 4;
	*(m2.at(1, 1)) = 5;
	*(m2.at(2, 1)) = 6;
	matrix<unsigned int> m4;
	m4 = m2.transpose();
	ASSERT_EQ(m4.getRows(), m2.getCols());
	ASSERT_EQ(m4.getCols(), m2.getRows());
	ASSERT_EQ(*(m4.at(0,0)), (unsigned int)(1));
	ASSERT_EQ(*(m4.at(1,0)), (unsigned int)(4));
	ASSERT_EQ(*(m4.at(0,1)), (unsigned int)(2));
	ASSERT_EQ(*(m4.at(1,1)), (unsigned int)(5));
	ASSERT_EQ(*(m4.at(0,2)), (unsigned int)(3));
	ASSERT_EQ(*(m4.at(1,2)), (unsigned int)(6));
}

TEST_F(matrixTest, testInvert) {
	matrix<float> m1(2, 2);
	*(m1.at(0, 0)) = 4.0;
	*(m1.at(1, 0)) = 1.0;
	*(m1.at(0, 1)) = 1.0;
	*(m1.at(1, 1)) = 0.0;
	matrix<float> m2;
	m2 = m1 * m1.invert();
	ASSERT_EQ(*(m2.at(0,0)), (float)(1.0));
	ASSERT_EQ(*(m2.at(1,0)), (float)(0.0));
	ASSERT_EQ(*(m2.at(0,1)), (float)(0.0));
	ASSERT_EQ(*(m2.at(1,1)), (float)(1.0));

	matrix<float> m3(3,3);
	*(m3.at(0, 0)) = 1.0;
	*(m3.at(1, 0)) = 2.0;
	*(m3.at(2, 0)) = 0.0;
	*(m3.at(0, 1)) = 2.0;
	*(m3.at(1, 1)) = 3.0;
	*(m3.at(2, 1)) = 0.0;
	*(m3.at(0, 2)) = 3.0;
	*(m3.at(1, 2)) = 4.0;
	*(m3.at(2, 2)) = 1.0;
	matrix<float> m4;
	m4 = m3 * m3.invert();
	for(unsigned int y = 0; y < m4.getRows(); y++) {
		for(unsigned int x = 0; x < m4.getCols(); x++) {
			if(x ==y) {
				ASSERT_EQ(*(m4.at(x,y)), (float)(1.0));
			}
			else {
				ASSERT_EQ(*(m4.at(x,y)), (float)(0.0));
			}

		}
	}

	matrix<float> m5(1,1);
	*(m5.at(0,0)) = 4.0;
	matrix<float> m6;
	m6 = m5.invert();
	ASSERT_EQ(*(m6.at(0,0)), (float)(1.0/4.0));
}

TEST_F(matrixTest, testVectorMultiplication) {
	matrix<unsigned int> m1(2, 2);
	*(m1.at(0, 0)) = 1;
	*(m1.at(1, 0)) = 0;
	*(m1.at(0, 1)) = 0;
	*(m1.at(1, 1)) = 1;

	matrix<unsigned int> m2(2,1);
	*(m2.at(0, 0)) = 2;
	*(m2.at(0, 1)) = 5;

	matrix<unsigned int> m3;
	m3 = m1 * m2;
	ASSERT_EQ(m3.getRows(), (unsigned int)(2));
	ASSERT_EQ(m3.getCols(), (unsigned int)(1));
	ASSERT_EQ(*(m3.at(0,0)), (unsigned int)(2));
	ASSERT_EQ(*(m3.at(0,1)), (unsigned int)(5));
}
