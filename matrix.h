#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

struct Matrix {
	int w, h;
	std::vector<std::vector<double>> data;

	/*
	 * Creates a matrix from a list of vectors.
	 * Each vector is one row.
	 * Example:
	 *   Matrix m = Matrix::create({
	 *     {0, 1},
	 *     {2, 3},
	 *     {4, 5},
	 *   });
	 * This would result in a 3x2 matrix.
	*/
	static Matrix create(std::vector<std::vector<double>> data)
	{
		Matrix res;
		res.h = data.size();
		res.w = data[0].size();

		res.data = data;
		return res;
	}

	/*
	 * Creates a matrix filled with zeros.
	 * Example:
	 *   Matrix::zerofill(2, 3);
	 * 
	 * Would result in
	 * [0, 0, 0]
	 * [0, 0, 0]
	*/

	static Matrix zerofill(int h, int w)
	{
		std::vector<double> inner;
		for(int i = 0; i < w; i++)
			inner.push_back(0);
		std::vector<std::vector<double>> outer;
		for(int i = 0; i < h; i++)
			outer.push_back(inner);

		return Matrix::create(outer);
	}
	
	/*
	 * Fills a matrix with random numbers.
	 * Example:
	 *   Matrix::random(2, 3);
	 * Could result in
	 * [0.03  0.15  0.87]
	 * [0.19  0.54  0.80]
	 */

	static Matrix random(int h, int w)
	{
		Matrix res = Matrix::zerofill(h, w);

		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] = std::rand() % 1000000 / (double) 1000000;

		return res;
	}

	/*
	 * Finds the highest number in a matrix.
	 */

	double max()
	{
		double max = 0;
		for(int i = 0; i < this->h; i++)
			for(int j = 0; j < this->w; j++)
				if(this->data[i][j] > max) {
					max = this->data[i][j];
				}
		return max;
	}

	/*
	 * Calculates the sum of all elements in a matrix.
	 */

	double sum()
	{
		double res = 0;
		for(int i = 0; i < this->h; i++)
			for(int j = 0; j < this->w; j++)
				res += this->data[i][j];
		return res;
	}

	/*
	 * Prints a matrix to console in a readable way.
	 */

	void log()
	{
		int spc = std::floor(std::log10(this->max())) + 7;
		if(spc < 5)
			spc = 4;
		for(int i = 0; i < this->h; i++)
			logarr(this->data[i], spc);
	}

	/*
	 * Number to string method for Matrix::log().
	 */

	static std::string num_to_fixed(double n, int spc)
	{
		std::string res;

		if(std::abs(n) < 0.01) {
			res = "0";
		} else {
			int a = std::abs(n);
			int b = std::abs((int) (n * 100) % 100);
			std::string c = b < 10 ? "0" : "";
			res = std::to_string(a) + "." + c + std::to_string(b);
		}

		res = n > 0 ? " " + res : "-" + res;

		while(res.size() < spc)
			res = " " + res;

		return res;
	}

	/*
	 * Vector printing method for Matrix::log().
	 */

	static void logarr(std::vector<double> v, int spc)
	{
		std::cout << "[";
		for(int i = 0; i < v.size(); i++) {
			std::cout << Matrix::num_to_fixed(v[i], spc);
			if(i < v.size() - 1)
				std::cout << "  ";
		}
		std::cout << "]\n";
	}

	/*
	 * Multiplies each element in the matrix by -1.
	 */

	Matrix negative()
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] = -res.data[i][j];
		return res;	
	}

	/*
	 * Adds a scalar number to a matrix.
	 * Example:
	 * [0  1]       [5  6]
	 * [2  3] + 5 = [7  8]
	 */

	Matrix add_scalar(double n)
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] += n;
		return res;
	}

	/*
	 * Multiplies every element in the matrix by a scalar value.
	 */

	Matrix multiply_scalar(double n)
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] *= n;
		return res;
	}
	
	/*
	 * Divides every value in a matrix by a scalar value.
	 */

	Matrix divide_scalar(double n)
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] /= n;
		return res;
	}

	/*
	 * Adds two matrices together. The two must have equal dimensions.
	 * Element result[i][j] will equal a[i][j] + b[i][j].
	 */

	Matrix add(Matrix b)
	{
		Matrix a = *this;
		if(a.w != b.w) {
			std::cout << "Matrix error: Can not do addition with matrices of different sizes.\n";
			std::cout << "Matrix A has width " << a.w << " and matrix B has width " << b.w << '\n';
		}
		if(a.h != b.h) {
			std::cout << "Matrix error: Can not do addition with matrices of different sizes.\n";
			std::cout << "Matrix A has height " << a.h << " and matrix B has height " << b.h << '\n';
		}


		Matrix res = Matrix::zerofill(a.h, a.w);

		for(int i = 0; i < a.h; i++)
			for(int j = 0; j < a.w; j++)
				res.data[i][j] = a.data[i][j] + b.data[i][j];

		return res;
	}

	/*
	 * Finds the dot product of two matrices.
	 */

	Matrix dot(Matrix b)
	{
		Matrix a = *this;
		if(a.w != b.h) {
			std::cout << "Matrix error: To do a dot product, the width of the first must be equal to the height of the second\n";
			std::cout << "Matrix A has width " << a.w << " and matrix B has height " << b.h << '\n';
		}

		Matrix res = Matrix::zerofill(a.h, b.w);

		for(int i = 0; i < a.h; i++)
			for(int j = 0; j < b.w; j++) {
				double val = 0;
				for(int k = 0; k < a.w; k++) {
					val += a.data[i][k] * b.data[k][j];
				}
				res.data[i][j] = val;
			}

		return res;
	}

	/*
	 * Multiplies each element in matrix a by the element at the
	 * same location in matrix b.
	 */

	Matrix multiply(Matrix b)
	{
		Matrix a = *this;
		if(a.w != b.w || a.h != b.h) {
			std::cout << "Matrix error: To do multiplication, both matrices must have the same dimensions\n";
		}

		Matrix res = Matrix::zerofill(a.h, a.w);

		for(int i = 0; i < a.h; i++)
			for(int j = 0; j < a.w; j++)
				res.data[i][j] = a.data[i][j] * b.data[i][j];

		return res;
	}

	/*
	 * Transposes a matrix.
	 */

	Matrix transpose()
	{
		Matrix res = Matrix::zerofill(this->w, this->h);

		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++) {
				res.data[i][j] = this->data[j][i];
			}
		return res;
	}

	/*
	 * Mirrors a matrix vertically.
	 */

	Matrix flip_columns()
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++) {
			res.data[i] = this->data[this->h - i - 1];
		}
		return res;
	}
	
	/*
	 * Mirrors a matrix horizontally.
	 */

	Matrix flip_rows()
	{
		return this->transpose().flip_columns().transpose();
	}

	/*
	 * Rotates a matrix anti-clockwise.
	 */

	Matrix rotate_left()
	{
		return this->transpose().flip_columns();
	}

	/*
	 * Rotates a matrix clockwise.
	 */

	Matrix rotate_right()
	{
		return this->rotate_left().rotate_left().rotate_left();
	}

	/*
	 * Applies the sigmoid function to each element in the matrix.
	 */

	Matrix sigmoid()
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] = 1 / (1 + std::exp(-res.data[i][j]));

		return res;
	}

	/*
	 * Applies the relu function to each element in the matrix.
	 */
	
	Matrix relu(double w = 0.001)
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++) 
				if(res.data[i][j] < 0)
					res.data[i][j] *= w;

		return res;
	}

	/*
	 * Applies the sigmoid derivative function to each element in the matrix.
	 */
	
	Matrix sigmoid_derivative()
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++) {	
				double n = 1 / (1 + std::exp(-res.data[i][j]));
				res.data[i][j] = n * (1 - n);
			}

		return res;
	}

	/*
	 * Applies the hyperbolic tangent function to each element in the matrix.
	 */
	
	Matrix tanh()
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] = std::tanh(res.data[i][j]);

		return res;
	}

	/*
	 * Rounds each element in a matrix to an integer.
	 */
	
	Matrix round()
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] = std::round(res.data[i][j]);

		return res;
	}
	
	/*
	 * Make each element 1 if it is >= 0, else make it 0.
	 */

	Matrix to_binary()
	{
		Matrix res = *this;
		for(int i = 0; i < res.h; i++)
			for(int j = 0; j < res.w; j++)
				res.data[i][j] = res.data[i][j] >= 0 ? 1 : 0;

		return res;
	}

	/*
	 * Helpful operator functions.
	 */
	
	Matrix operator*(Matrix b)
	{
		return this->dot(b);
	}

	Matrix operator*(double n)
	{
		return this->multiply_scalar(n);
	}

	Matrix operator+(Matrix b)
	{
		return this->add(b);
	}
	
	Matrix operator+(double n)
	{
		return this->add_scalar(n);
	}

	Matrix operator-(Matrix b)
	{
		return this->add(b.negative());
	}
	
	Matrix operator-(double n)
	{
		return this->add_scalar(-n);
	}

	Matrix operator-()
	{
		return this->negative();
	}
	
	Matrix operator/(double n)
	{
		return this->divide_scalar(n);
	}
	
	void operator+=(double n)
	{
		this->data = (*this + n).data;
	}	
	
	void operator-=(double n)
	{
		this->data = (*this - n).data;
	}	
	
	void operator*=(double n)
	{
		this->data = (*this * n).data;
	}	
	
	void operator/=(double n)
	{
		this->data = (*this / n).data;
	}	
	
	void operator++(int)
	{
		this->data = (*this + 1).data;
	}

	void operator--(int)
	{
		this->data = (*this - 1).data;
	}

};

#endif // MATRIX_MATRIX_H
