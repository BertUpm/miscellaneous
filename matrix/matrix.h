/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file matrix.h
 * @brief template class for matrix operations
 * @autor Alexander Entinger, BSc
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <string.h>
#include <iostream>
#include <assert.h>
#include <algorithm>

template<class T>
class matrix {
public:
	/**
	 * @brief Default constructor
	 */
	matrix();
	/**
	 * @brief Constructor
	 * @param rows number of rows of the matrix
	 * @param cols number of cols of the matrix
	 */
	matrix(unsigned int const rows, unsigned int const cols);
	/**
	 * @brief Copy Constructor
	 * @param other matrix to copy
	 */
	matrix(matrix &other);
	/**
	 * @brief Destructor
	 */
	~matrix(); // DTor

	/**
	 * @brief assignment operator overloaded
	 * @param other matrix to assign to another matrix
	 * @return assigned matrix
	 */
	matrix<T> &operator=(matrix<T> &other);
	/**
	 * @brief operator overloading of the multiplying operation for matrixes
	 * @param other matrix for multiplication
	 * @return result of the multiplication
	 */
	matrix<T> &operator*(matrix<T> &right);
	matrix<T> &operator*=(matrix<T>& matrix) {
		return *this = *this * matrix;
	}
	/**
	 * @brief operator overloading of the addition operation for matrixes
	 * @param other matrix for addition
	 * @return result of the addition
	 */
	matrix<T> &operator+(matrix<T> &right);
	matrix<T> &operator+=(matrix<T>& matrix) {
		return *this = *this + matrix;
	}
	/**
	 * @brief operator overloading of the subtraction operation for matrixes
	 * @param other matrix for subtraction
	 * @return result of the subtraction
	 */
	matrix<T> &operator-(matrix<T> &right);
	matrix<T> &operator-=(matrix<T>& matrix) {
		return *this = *this - matrix;
	}
	/**
	 * @brief operator overloading of the multiplying operation for scalars
	 * @param scalar for multiplication
	 * @return result of the multiplication
	 */
	matrix<T> &operator*(T const scalar);
	matrix<T> &operator*=(T const scalar) {
		return *this = *this * scalar;
	}
	/**
	 * @brief operator overloading of the division operation for scalars
	 * @param scalar for multiplication
	 * @return result of the multiplication
	 */
	matrix<T> &operator/(T const scalar);
	matrix<T> &operator/=(T const scalar) {
		return *this = *this / scalar;
	}
	/**
	 * @brief operator overloading of the adding a scalar value
	 * @param scalar for adding
	 * @return result of the adding
	 */
	matrix<T> &operator+(T const scalar);
	matrix<T> &operator+=(T const scalar) {
		return *this = *this + scalar;
	}
	/**
	 * @brief operator overloading of the subtracting a scalar value
	 * @param scalar for subtraction
	 * @return result of subtraction
	 */
	matrix<T> &operator-(const T scalar);
	matrix<T> &operator-=(const T scalar) {
		return *this = *this - scalar;
	}

	/**
	 * @brief access operator for matrix
	 * @param row which row to access
	 * @param col wich column to access
	 * @return pointer to that matrix element
	 */
	T *at(unsigned int const col, unsigned int const row);

	/**
	 * @brief sets the matrix as an identity matrix with the dimension dim
	 * @param dim dimension of the identity matrix
	 */
	void setIdentity(unsigned int const dim);

	/**
	 * @brief returns a transposed matrix
	 * @return transposed matrix
	 */
	matrix<T> &transpose();

	/**
	 * @brief inverts a square matrix
	 * @return inverted matrix
	 */
	matrix<T> &invert();

	/**
	 * @brief returns the number of rows, rows go downwards
	 * @return number of rows of the matrix
	 */
	unsigned int getRows() const {
		return mRows;
	}
	/**
	 * @brief returns the number of cols, cols go right
	 * @return number of cols of the matrix
	 */
	unsigned int getCols() const {
		return mCols;
	}

private:
	T* mpMatrix;
	unsigned int mRows;
	unsigned int mCols;

	/**
	 * @brief determines, wether there are only zeros in a column or nor
	 * @param col column to investigate
	 * @return true if here are only zeros, false otherwise
	 */
	bool onlyZeroInCol(unsigned int const col);
	/**
	 * @brief swaps the elements from row 1 with the elements from row 2
	 * @param row1 1st row
	 * @param row2 2nd row
	 */
	void swapRow(unsigned int const row1, unsigned int const row2);
	/**
	 * @brief divides all elements the row row by the value val
	 * @param row row to divide
	 * @param val value for division
	 */
	void divideRow(unsigned int const row, T const val);
};

/**
 * @brief overloading of the << operator for comforable printing of the matrix
 */
template<typename T>
std::ostream &operator<<(std::ostream& os, matrix<T> &m) {
	for (unsigned int y = 0; y < m.getRows(); y++) {
		os << "| ";
		for (unsigned int x = 0; x < m.getCols(); x++) {
			os << *(m.at(x, y)) << " | ";
		}
		os << std::endl;
	}
	return os;
}

/**
 * @brief Default constructor
 */
template<class T>
matrix<T>::matrix() {
	this->mpMatrix = 0;
	this->mCols = 0;
	this->mRows = 0;
}

/**
 * @brief Constructor
 * @param rows number of rows of the matrix
 * @param cols number of cols of the matrix
 */
template<class T>
matrix<T>::matrix(unsigned int const rows, unsigned int const cols) {
	assert(rows >= 0);
	assert(cols >= 0);
	mRows = rows;
	mCols = cols;
	mpMatrix = new T[mRows * mCols];
	assert(mpMatrix != 0);
	memset((void *) mpMatrix, 0, mRows * mCols); // initialize picture to zero
}

/**
 * @brief Copy Constructor
 * @param other matrix to copy
 */
template<class T>
matrix<T>::matrix(matrix<T> &other) {
	// create new matrix
	this->mRows = other.getRows();
	this->mCols = other.getCols();
	this->mpMatrix = new T[this->mRows * this->mCols];
	assert(this->mpMatrix != 0);
	// copy elements
	for (unsigned int y = 0; y < this->mRows; y++) {
		for (unsigned int x = 0; x < this->mCols; x++) {
			*this->at(x, y) = *other.at(x, y);
		}
	}
}

/**
 * @brief Destructor
 */
template<class T>
matrix<T>::~matrix() {
	if (mpMatrix != 0) {
		delete[] mpMatrix;
		mpMatrix = 0;
	}
}

/**
 * @brief assignment operator overloaded
 * @param other matrix to assign to another matrix
 * @return assigned matrix
 */
template<class T>
matrix<T> &matrix<T>::operator=(matrix<T> &other) {
	if (this != &other) { // self assignment protection
		// delete old matrix
		if (this->mpMatrix != 0) {
			delete[] this->mpMatrix;
			this->mpMatrix = 0;
		}
		// create new matrix
		this->mRows = other.getRows();
		this->mCols = other.getCols();
		this->mpMatrix = new T[this->mRows * this->mCols];
		assert(this->mpMatrix != 0);
		// copy elements
		for (unsigned int y = 0; y < this->mRows; y++) {
			for (unsigned int x = 0; x < this->mCols; x++) {
				*((*this).at(x, y)) = *(other.at(x, y));
			}
		}
	}
	return *this;
}

/**
 * @brief operator overloading of the multiplying operation
 * @param other matrix for multiplication
 * @return result of the multiplication
 */
template<class T>
matrix<T> &matrix<T>::operator*(matrix<T> &right) {
	assert(this->getCols() == right.getRows());
	matrix<T> *res = new matrix<T>(this->getRows(), right.getCols());

	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < right.getCols(); j++) {
			*(res->at(j, i)) = 0.0;
			for (unsigned int k = 0; k < this->getCols(); k++) {
				*(res->at(j, i)) += (*(this->at(k, i))) * (*right.at(j, k));
			}
		}
	}

	return *res;
}

/**
 * @brief operator overloading of the addition operation for matrixes
 * @param other matrix for addition
 * @return result of the addition
 */
template<typename T>
matrix<T> &matrix<T>::operator+(matrix<T> &right) {
	assert(this->getCols() == right.getCols());
	assert(this->getRows() == right.getRows());

	matrix<T> *res = new matrix<T>(this->getRows(), this->getCols());

	for (unsigned int y = 0; y < this->getRows(); y++) {
		for (unsigned int x = 0; x < this->getCols(); x++) {
			*(res->at(x, y)) = *(this->at(x, y)) + *(right.at(x, y));
		}
	}

	return *res;
}

/**
 * @brief operator overloading of the subtraction operation for matrixes
 * @param other matrix for subtraction
 * @return result of the subtraction
 */
template<typename T>
matrix<T> &matrix<T>::operator-(matrix<T> &right) {
	assert(this->getCols() == right.getCols());
	assert(this->getRows() == right.getRows());

	matrix<T> *res = new matrix<T>(this->getRows(), this->getCols());

	for (unsigned int y = 0; y < this->getRows(); y++) {
		for (unsigned int x = 0; x < this->getCols(); x++) {
			*(res->at(x, y)) = *(this->at(x, y)) - *(right.at(x, y));
		}
	}

	return *res;
}

/**
 * @brief operator overloading of the multiplying operation for scalars
 * @param scalar for multiplication
 * @return result of the multiplication
 */
template<class T>
matrix<T> &matrix<T>::operator*(T const scalar) {
	for (unsigned int y = 0; y < this->getRows(); y++) {
		for (unsigned int x = 0; x < this->getCols(); x++) {
			*(this->at(x, y)) *= scalar;
		}
	}
	return *this;
}

/**
 * @brief operator overloading of the division operation for scalars
 * @param scalar for multiplication
 * @return result of the multiplication
 */
template<class T>
matrix<T> &matrix<T>::operator/(T const scalar) {
	for (unsigned int y = 0; y < this->getRows(); y++) {
		for (unsigned int x = 0; x < this->getCols(); x++) {
			*(this->at(x, y)) /= scalar;
		}
	}
	return *this;
}

/**
 * @brief operator overloading of the adding a scalar value
 * @param scalar for adding
 * @return result of the adding
 */
template<class T>
matrix<T> &matrix<T>::operator+(T const scalar) {
	for (unsigned int y = 0; y < this->getRows(); y++) {
		for (unsigned int x = 0; x < this->getCols(); x++) {
			*(this->at(x, y)) += scalar;
		}
	}
	return *this;
}

/**
 * @brief operator overloading of the subtracting a scalar value
 * @param scalar for subtraction
 * @return result of subtraction
 */
template<class T>
matrix<T> &matrix<T>::operator-(T const scalar) {
	for (unsigned int y = 0; y < this->getRows(); y++) {
		for (unsigned int x = 0; x < this->getCols(); x++) {
			*(this->at(x, y)) -= scalar;
		}
	}
	return *this;
}

/**
 * @brief access operator for matrix
 * @param row which row to access
 * @param col wich column to access
 * @return pointer to that matrix element
 */
template<class T>
T *matrix<T>::at(unsigned int const col, unsigned int const row) {
	assert(row < this->mRows);
	assert(col < this->mCols);
	return &(this->mpMatrix[row * this->mCols + col]);
}

/**
 * @brief sets the matrix as an identity matrix with the dimension dim
 * @param dim dimension of the identity matrix
 */
template<class T>
void matrix<T>::setIdentity(unsigned int const dim) {
	// resize the matrix
	if (this->mpMatrix != 0) {
		delete[] this->mpMatrix;
		this->mpMatrix = 0;
	}
	mpMatrix = new T[dim * dim];
	assert(mpMatrix != 0);
	memset((void *) mpMatrix, 0, dim * dim);
	this->mRows = dim;
	this->mCols = dim;
	// assign the identity values
	for (unsigned int y = 0; y < this->mRows; y++) {
		for (unsigned int x = 0; x < this->mCols; x++) {
			if (y == x)
				*(this->at(x, y)) = (T) (1.0);
			else
				*(this->at(x, y)) = (T) (0.0);
		}
	}
}

/**
 * @brief returns a transposed matrix
 * @return transposed matrix
 */
template<class T>
matrix<T> &matrix<T>::transpose() {
	matrix<T> *res = new matrix<T>(this->getCols(), this->getRows());

	for (unsigned int y = 0; y < this->mRows; y++) {
		for (unsigned int x = 0; x < this->mCols; x++) {
			*(res->at(y, x)) = *(this->at(x, y));
		}
	}

	return *res;
}

/**
 * @brief inverts a square matrix
 * @return inverted matrix
 */
template<class T>
matrix<T> &matrix<T>::invert() {
	assert(this->getRows() == this->getCols());
	// save matrix content
	matrix<T> tmpCpy(*this);
	matrix<T> *res = new matrix<T>(this->getRows(), this->getCols());
	res->setIdentity(this->getCols());

	// build the row echelon matrix form (http://en.wikipedia.org/wiki/Row_echelon_form)
	unsigned int x_start = 0;
	unsigned int y_start = 0;

	// find column where at least one value is different from 0
	for (; x_start < this->mCols && this->onlyZeroInCol(x_start);
			x_start++)
		;

	do {
		// guarantee that there is always a value != 0 at the starting position
		for (unsigned int rowCnt = 1;
				(*(this->at(x_start, y_start)) == (T) (0.0))
						&& rowCnt < this->mRows; rowCnt++) {
			res->swapRow(y_start, y_start + rowCnt);
			this->swapRow(y_start, y_start + rowCnt);
		}
		// divide the first row through the value at the starting position
		res->divideRow(y_start, *(this->at(x_start, y_start)));
		this->divideRow(y_start, *(this->at(x_start, y_start)));

		// subtract from all other rows the first row with the aim to get the first element in each row zero
		for (unsigned int y = y_start + 1; y < this->mRows; y++) {
			T rowMultFact = (T) (0.0);
			if ((*(this->at(x_start, y_start))) != (T) (0.0)) {
				rowMultFact = (T) (-1.0) * (*(this->at(x_start, y)))
						/ (*(this->at(x_start, y_start)));
			}
			for (unsigned int x = 0; x < this->mCols; x++) {
				*(this->at(x, y)) += rowMultFact * (*(this->at(x, y_start))); // subtract x times row start from all the other rows
				*(res->at(x, y)) += rowMultFact * (*(res->at(x, y_start))); // subtract x times row start from all the other rows
			}
		}
		// move to the next sub matrix
		x_start++;
		y_start++;
	} while (x_start < this->mCols && y_start < this->mRows);

	// now subtract lines with a factor from each other, until there are only zeros preceeding a one
	// deal with all the lines, start with row 0
	for (unsigned int y = 0; y < this->mRows - 1; y++) {
		// deal with all the subrows
		for (unsigned int y2 = y + 1; y2 < this->mRows; y2++) {
			T rowMultFact = (T) (0.0);
			if ((*(this->at(y2, y2))) != (T) (0.0)) {
				rowMultFact = (T) (-1.0) * (*(this->at(y2, y)))
						/ (*(this->at(y2, y2)));
			}
			// subtract from the row above the rows beneath
			for (unsigned int x = 0; x < this->mCols; x++) {
				*(res->at(x, y)) += rowMultFact * (*(res->at(x, y2)));
				*(this->at(x, y)) += rowMultFact * (*(this->at(x, y2)));
			}
		}
	}

	// restore matrix
	*this = tmpCpy;

	return *res;
}

/**
 * @brief swaps the elements from row 1 with the elements from row 2
 * @param row1 1st row
 * @param row2 2nd row
 */
template<typename T>
void matrix<T>::swapRow(unsigned int const row1, unsigned int const row2) {
	for (unsigned int x = 0; x < this->mCols; x++) {
		std::swap(*(this->at(x, row1)), *(this->at(x, row2)));
	}
}

/**
 * @brief divides all elements the row row by the value val
 * @param row row to divide
 * @param val value for division
 */
template<typename T>
void matrix<T>::divideRow(unsigned int const row, T const val) {
	if (val != (T) (0.0)) {
		for (unsigned int x = 0; x < this->mCols; x++) {
			(*(this->at(x, row))) /= val;
		}
	}
}

/**
 * @brief determines, wether there are only zeros in a column or nor
 * @param col column to investigate
 * @return true if here are only zeros, false otherwise
 */
template <typename T>
bool matrix<T>::onlyZeroInCol(unsigned int const col) {

	for(unsigned int y = 0; y < this->mRows; y++) {
		if((*(this->at(col, y))) != (T)(0.0)) {
			return false;
		}
	}

	return true;
}

#endif /* MATRIX_H_ */
