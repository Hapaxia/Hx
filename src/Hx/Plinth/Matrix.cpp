//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Plinth
//
// Copyright(c) 2014 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty.In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#include "Matrix.hpp"

namespace hx
{

Matrix::Matrix()
{

}

void Matrix::clear()
{
	fill(0.0);
}

void Matrix::fill(double value)
{
	if (m_matrix.empty())
		return;
	for (auto& row : m_matrix)
	{
		for (auto& element : row)
			element = value;
	}
}

void Matrix::resize(Vector2u size)
{
	resizeMatrix(m_matrix, size);
}

void Matrix::setSize(Vector2u size)
{
	resize(size);
}


void Matrix::setElement(Vector2u elementLocation, double value)
{
	*pElement(elementLocation) = value;
}

double Matrix::getElement(Vector2u elementLocation)
{
	return{ *pElement(elementLocation) };
}

Vector2u Matrix::getSize()
{
	return getSizeOfMatrix(m_matrix);
}









Matrix Matrix::operator+(const Matrix& matrix)
{
	// make sure both matrices are the same size and no sizes are zero
	if ((getSizeOfMatrix(m_matrix).x != getSizeOfMatrix(matrix.m_matrix).x) ||
		(getSizeOfMatrix(m_matrix).y != getSizeOfMatrix(matrix.m_matrix).y) ||
		(getSize().x == 0) ||
		(getSize().y == 0))
		return *this;

	Matrix temp;
	temp.resize(getSize());
	for (unsigned int row{ 0 }; row < m_matrix.size(); ++row)
	{
		for (unsigned int column{ 0 }; column < m_matrix[0].size(); ++column)
			temp.setElement({ column, row }, m_matrix[row][column] + matrix.m_matrix[row][column]);
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix& matrix)
{
	// make sure both matrices are the same size and no sizes are zero
	if ((getSizeOfMatrix(m_matrix).x != getSizeOfMatrix(matrix.m_matrix).x) ||
		(getSizeOfMatrix(m_matrix).y != getSizeOfMatrix(matrix.m_matrix).y) ||
		(getSize().x == 0) ||
		(getSize().y == 0))
		return *this;

	Matrix temp;
	temp.resize(getSize());
	for (unsigned int row{ 0 }; row < m_matrix.size(); ++row)
	{
		for (unsigned int column{ 0 }; column < m_matrix[0].size(); ++column)
			temp.setElement({ column, row }, m_matrix[row][column] - matrix.m_matrix[row][column]);
	}
	return temp;
}

Matrix Matrix::operator*(double scalar)
{
	// make sure no sizes are zero
	if ((getSize().x == 0) ||
		(getSize().y == 0))
		return *this;

	Matrix temp;
	temp.resize(getSize());
	for (unsigned int row{ 0 }; row < m_matrix.size(); ++row)
	{
		for (unsigned int column{ 0 }; column < m_matrix[0].size(); ++column)
			temp.setElement({ column, row }, m_matrix[row][column] * scalar);
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix& matrix)
{
	// sizes need very specific testing. the following code isn't right. it was copied from above.
	// for more information, see (http://en.wikipedia.org/wiki/Matrix_%28mathematics%29#Matrix_multiplication) and (http://en.wikipedia.org/wiki/Matrix_multiplication)

	// make sure both matrices are opposite size (matrix1.x = matrix2.y, matrix1.y = matrix2.x) and no sizes are zero
	// make sure that left matrix columns are same as right matrix rows (size) and that no matrix sizes are zero.
	if ((getSizeOfMatrix(m_matrix).x != getSizeOfMatrix(matrix.m_matrix).y) ||
		(getSize().x == 0) ||
		(getSize().y == 0) ||
		(getSizeOfMatrix(matrix.m_matrix).x == 0) ||
		(getSizeOfMatrix(matrix.m_matrix).y == 0))
		return *this;

	Matrix temp;
	temp.resize({ getSizeOfMatrix(matrix.m_matrix).x, getSizeOfMatrix(m_matrix).y });
	for (unsigned int row{ 0 }; row < getSizeOfMatrix(m_matrix).y; ++row)
	{
		for (unsigned int column{ 0 }; column < getSizeOfMatrix(matrix.m_matrix).x; ++column)
		{
			double value{ 0.0 };
			for (unsigned int leftColumnRightRow{ 0 }; leftColumnRightRow < getSizeOfMatrix(m_matrix).x; ++leftColumnRightRow)
				value += m_matrix[row][leftColumnRightRow] * matrix.m_matrix[leftColumnRightRow][column];
			temp.setElement({ column, row }, value);
		}
	}
	return temp;
}




// PRIVATE

double* Matrix::pElement(Vector2u elementLocation)
{
	return &m_matrix[elementLocation.y][elementLocation.x];
}

void Matrix::resizeMatrix(std::vector<std::vector<double>>& matrix, Vector2u size)
{
	if (getSize().x != size.x || getSize().y != size.y)
	{
		m_matrix.resize(size.y);
		for (auto& row : m_matrix)
			row.resize(size.x);
	}
}

Vector2u Matrix::getSizeOfMatrix(const std::vector<std::vector<double>>& matrix)
{
	return{ matrix.size() > 0 ? matrix[0].size() : 0, matrix.size() };
}



} // namespace hx