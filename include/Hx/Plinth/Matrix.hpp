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

// matrix class

#ifndef HX_MATRIX_HPP
#define HX_MATRIX_HPP

#include "Generic.hpp"
//#include "Math.hpp"
#include <vector>

namespace hx
{

// two-dimensional array with class interface which can be used for matrix calculations (element type is double)
class Matrix
{
public:
	Matrix();
	void clear();
	void fill(double value);
	void resize(Vector2u size);
	void setSize(Vector2u size);
	void setElement(Vector2u element, double value);
	double getElement(Vector2u element);
	Vector2u getSize();

	template<class T>
	void multiplyVector(Vector2<T>& vector);
	template<class T>
	void multiplyVector(Vector3<T>& vector);

	template<class T>
	Vector2<T> vectorFromMultiply(const Vector2<T>& vector);
	template<class T>
	Vector3<T> vectorFromMultiply(const Vector3<T>& vector);

	Matrix operator+(const Matrix& matrix);
	Matrix operator-(const Matrix& matrix);
	Matrix operator*(double scalar);
	Matrix operator*(const Matrix& matrix);
	template<class T>
	Matrix operator*(const Vector2<T> vector);
	template<class T>
	Matrix operator*(const Vector3<T> vector);

private:
	std::vector<std::vector<double>> m_matrix;
	double* pElement(Vector2u elementLocation);
	void resizeMatrix(std::vector<std::vector<double>>& matrix, Vector2u size);
	Vector2u Matrix::getSizeOfMatrix(const std::vector<std::vector<double>>& matrix);
};

template<class T>
Matrix Matrix::operator*(const Vector2<T> vector)
{
	Matrix columnVector;
	columnVector.resize({ 1, 2 });
	columnVector.m_matrix[0][0] = static_cast<double>(vector.x);
	columnVector.m_matrix[1][0] = static_cast<double>(vector.y);
	*this = *this * columnVector;
	return *this;
}

template<class T>
Matrix Matrix::operator*(const Vector3<T> vector)
{
	Matrix columnVector;
	columnVector.resize({ 1, 3 });
	columnVector.m_matrix[0][0] = static_cast<double>(vector.x);
	columnVector.m_matrix[1][0] = static_cast<double>(vector.y);
	columnVector.m_matrix[2][0] = static_cast<double>(vector.z);
	*this = *this * columnVector;
	return *this;
}

template<class T>
void Matrix::multiplyVector(Vector2<T>& vector)
{
	Matrix v{ *this };
	v = v * vector;
	vector.x = static_cast<T>(v.m_matrix[0][0]);
	vector.y = static_cast<T>(v.m_matrix[1][0]);
}

template<class T>
void Matrix::multiplyVector(Vector3<T>& vector)
{
	Matrix v{ *this };
	v = v * vector;
	vector.x = static_cast<T>(v.m_matrix[0][0]);
	vector.y = static_cast<T>(v.m_matrix[1][0]);
	vector.z = static_cast<T>(v.m_matrix[2][0]);
}

template<class T>
Vector2<T> Matrix::vectorFromMultiply(const Vector2<T>& vector)
{
	Matrix v{ *this };
	v = v * vector;
	//vector.x = static_cast<T>(v.m_matrix[0][0]);
	//vector.y = static_cast<T>(v.m_matrix[1][0]);
	//return vector;
	return{ static_cast<T>(v.m_matrix[0][0]), static_cast<T>(v.m_matrix[1][0]) };
}

template<class T>
Vector3<T> Matrix::vectorFromMultiply(const Vector3<T>& vector)
{
	Matrix v{ *this };
	v = v * vector;
	//vector.x = static_cast<T>(v.m_matrix[0][0]);
	//vector.y = static_cast<T>(v.m_matrix[1][0]);
	//vector.z = static_cast<T>(v.m_matrix[2][0]);
	//return vector;
	return{ static_cast<T>(v.m_matrix[0][0]), static_cast<T>(v.m_matrix[1][0]), static_cast<T>(v.m_matrix[2][0]) };
}

} // hx
#endif // HX_MATRIX_HPP