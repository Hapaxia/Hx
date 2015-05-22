//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Plinth
//
// Copyright(c) 2015 M.J.Silk
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

#include "Perspective.hpp"

namespace hx
{

Perspective::Perspective() :
m_depth(0.0),
m_projectionOrigin({ 0.0, 0.0 }),
m_transformationOrigin({ 0.0, 0.0, 0.0 }),
m_matrices3x3x3(3),
m_matrix3x3(),
m_scale(1.0)
{
	for (auto& matrix : m_matrices3x3x3)
		matrix.setSize({ 3, 3 });
	m_matrix3x3.setSize({ 3, 3 });
	resetMatrix();
}

void Perspective::setDepth(double depth)
{
	m_depth = depth;
}

double Perspective::getDepth()
{
	return m_depth;
}

void Perspective::setScale(double scale)
{
	m_scale = scale;
}

double Perspective::getScale()
{
	return m_scale;
}

void Perspective::setProjectionOrigin(Vector2d origin)
{
	m_projectionOrigin = origin;
}

Vector2d Perspective::getProjectionOrigin()
{
	return m_projectionOrigin;
}

void Perspective::setTransformationOrigin(Vector3d origin)
{
	m_transformationOrigin = origin;
}

Vector3d Perspective::getTransformationOrigin()
{
	return m_transformationOrigin;
}







Vector2d Perspective::projectPoint(const Vector3d& point) const
{
	return{ (m_scale * point.x / (point.z * m_depth + 1.0) + m_projectionOrigin.x), (m_scale * point.y / (point.z * m_depth + 1.0) + m_projectionOrigin.y) };
}

void Perspective::translatePoint(Vector3d& point, const Vector3d& translationVector)
{
	point.x += translationVector.x;
	point.y += translationVector.y;
	point.z += translationVector.z;
}

void Perspective::scalePoint(Vector3d& point, const Vector3d& scaleVector)
{
	subtractTransformationOrigin(point);
	point.x *= scaleVector.x;
	point.y *= scaleVector.y;
	point.z *= scaleVector.z;
	addTransformationOrigin(point);
}

void Perspective::scalePoint(Vector3d& point, double scalar)
{
	scalePoint(point, { scalar, scalar, scalar });
}

void Perspective::rotatePoint(Vector3d& point, const Vector3d& rotationVector)
{
	Vector3d rotationVectorInRadians{ hx::radiansFromDegrees(rotationVector.x), hx::radiansFromDegrees(rotationVector.y), hx::radiansFromDegrees(rotationVector.z) };
	setMatrixAny3x3(m_matrices3x3x3[0], {	{ 1.0, 0.0, 0.0 },
											{ 0.0, cos(rotationVectorInRadians.x), -sin(rotationVectorInRadians.x) },
											{ 0.0, sin(rotationVectorInRadians.x), cos(rotationVectorInRadians.x) } });
	setMatrixAny3x3(m_matrices3x3x3[1], {	{ cos(rotationVectorInRadians.y), 0.0, sin(rotationVectorInRadians.y) },
											{ 0.0, 1.0, 0.0 },
											{ -sin(rotationVectorInRadians.y), 0.0, cos(rotationVectorInRadians.y) } });
	setMatrixAny3x3(m_matrices3x3x3[2], {	{ cos(rotationVectorInRadians.z), -sin(rotationVectorInRadians.z), 0.0 },
											{ sin(rotationVectorInRadians.z), cos(rotationVectorInRadians.z), 0.0 },
											{ 0.0, 0.0, 1.0 } });
	makeMatrixFromMatrices();
	subtractTransformationOrigin(point);
	m_matrix3x3.multiplyVector(point);
	addTransformationOrigin(point);
}

void Perspective::rotatePoints(std::vector<Vector3d>& points, const Vector3d& rotationVector)
{
	Vector3d rotationVectorInRadians{ hx::radiansFromDegrees(rotationVector.x), hx::radiansFromDegrees(rotationVector.y), hx::radiansFromDegrees(rotationVector.z) };
	setMatrixAny3x3(m_matrices3x3x3[0], {	{ 1.0, 0.0, 0.0 },
											{ 0.0, cos(rotationVectorInRadians.x), -sin(rotationVectorInRadians.x) },
											{ 0.0, sin(rotationVectorInRadians.x), cos(rotationVectorInRadians.x) } });
	setMatrixAny3x3(m_matrices3x3x3[1], {	{ cos(rotationVectorInRadians.y), 0.0, sin(rotationVectorInRadians.y) },
											{ 0.0, 1.0, 0.0 },
											{ -sin(rotationVectorInRadians.y), 0.0, cos(rotationVectorInRadians.y) } });
	setMatrixAny3x3(m_matrices3x3x3[2], {	{ cos(rotationVectorInRadians.z), -sin(rotationVectorInRadians.z), 0.0 },
											{ sin(rotationVectorInRadians.z), cos(rotationVectorInRadians.z), 0.0 },
											{ 0.0, 0.0, 1.0 } });
	makeMatrixFromMatrices();
	for (auto& point : points)
	{
		subtractTransformationOrigin(point);
		m_matrix3x3.multiplyVector(point);
		addTransformationOrigin(point);
	}
}

void Perspective::rotateMatrix(const Vector3d& rotationVector)
{
	Vector3d rotationVectorInRadians{ hx::radiansFromDegrees(rotationVector.x), hx::radiansFromDegrees(rotationVector.y), hx::radiansFromDegrees(rotationVector.z) };
	setMatrixAny3x3(m_matrices3x3x3[0], { { 1.0, 0.0, 0.0 },
	{ 0.0, cos(rotationVectorInRadians.x), -sin(rotationVectorInRadians.x) },
	{ 0.0, sin(rotationVectorInRadians.x), cos(rotationVectorInRadians.x) } });
	setMatrixAny3x3(m_matrices3x3x3[1], { { cos(rotationVectorInRadians.y), 0.0, sin(rotationVectorInRadians.y) },
	{ 0.0, 1.0, 0.0 },
	{ -sin(rotationVectorInRadians.y), 0.0, cos(rotationVectorInRadians.y) } });
	setMatrixAny3x3(m_matrices3x3x3[2], { { cos(rotationVectorInRadians.z), -sin(rotationVectorInRadians.z), 0.0 },
	{ sin(rotationVectorInRadians.z), cos(rotationVectorInRadians.z), 0.0 },
	{ 0.0, 0.0, 1.0 } });
	multiplyMatrixWithMatrices();
}

void Perspective::setMatrixAsRotation(const Vector3d& rotationVector)
{
	Vector3d rotationVectorInRadians{ hx::radiansFromDegrees(rotationVector.x), hx::radiansFromDegrees(rotationVector.y), hx::radiansFromDegrees(rotationVector.z) };
	setMatrixAny3x3(m_matrices3x3x3[0], { { 1.0, 0.0, 0.0 },
	{ 0.0, cos(rotationVectorInRadians.x), -sin(rotationVectorInRadians.x) },
	{ 0.0, sin(rotationVectorInRadians.x), cos(rotationVectorInRadians.x) } });
	setMatrixAny3x3(m_matrices3x3x3[1], { { cos(rotationVectorInRadians.y), 0.0, sin(rotationVectorInRadians.y) },
	{ 0.0, 1.0, 0.0 },
	{ -sin(rotationVectorInRadians.y), 0.0, cos(rotationVectorInRadians.y) } });
	setMatrixAny3x3(m_matrices3x3x3[2], { { cos(rotationVectorInRadians.z), -sin(rotationVectorInRadians.z), 0.0 },
	{ sin(rotationVectorInRadians.z), cos(rotationVectorInRadians.z), 0.0 },
	{ 0.0, 0.0, 1.0 } });
	makeMatrixFromMatrices();
}

void Perspective::transformPoint(Vector3d& point)
{
	subtractTransformationOrigin(point);
	m_matrix3x3.multiplyVector(point);
	addTransformationOrigin(point);
}

void Perspective::transformPoints(std::vector<Vector3d>& points)
{
	for (auto& point : points)
		transformPoint(point);
}

void Perspective::resetMatrix()
{
	setMatrix3x3({ { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } });
}

void Perspective::transformPointFromPoint(Vector3d& point, const Vector3d& origPoint)
{
	point = origPoint;
	transformPoint(point);
}

void Perspective::transformPointsFromPoints(std::vector<Vector3d>& points, const std::vector<Vector3d>& origPoints)
{
	points = origPoints;
	for (auto& point : points)
		transformPoint(point);
}














// PRIVATE

void Perspective::subtractTransformationOrigin(Vector3d& point)
{
	translatePoint(point, { -m_transformationOrigin.x, -m_transformationOrigin.y, -m_transformationOrigin.z });
}

void Perspective::addTransformationOrigin(Vector3d& point)
{
	translatePoint(point, m_transformationOrigin);
}

void Perspective::setMatrixAny3x3(hx::Matrix& matrix, std::vector<std::vector<double>> matrixGrid)
{
	for (unsigned int row{ 0 }; row < 3; ++row)
	{
		for (unsigned int column{ 0 }; column < 3; ++column)
			matrix.setElement({ column, row }, matrixGrid[row][column]);
	}
}

void Perspective::setMatrix3x3(std::vector<std::vector<double>> matrixGrid)
{
	for (unsigned int row{ 0 }; row < 3; ++row)
	{
		for (unsigned int column{ 0 }; column < 3; ++column)
			m_matrix3x3.setElement({ column, row }, matrixGrid[row][column]);
	}
}

void Perspective::unscaleVector(Vector3d& vector)
{
	vector.x /= m_scale;
	vector.y /= m_scale;
	vector.z /= m_scale;
}

void Perspective::scaleVector(Vector3d& vector)
{
	vector.x *= m_scale;
	vector.y *= m_scale;
	vector.z *= m_scale;
}

void Perspective::makeMatrixFromMatrices()
{
	m_matrix3x3 = m_matrices3x3x3[0]; // use only matrices created from the rotation vector
	m_matrix3x3 = m_matrix3x3 * m_matrices3x3x3[1];
	m_matrix3x3 = m_matrix3x3 * m_matrices3x3x3[2];
}

void Perspective::multiplyMatrixWithMatrices()
{
	m_matrix3x3 = m_matrix3x3 * m_matrices3x3x3[0]; // multiply the current matrix with the new ones from the rotation vector
	m_matrix3x3 = m_matrix3x3 * m_matrices3x3x3[1];
	m_matrix3x3 = m_matrix3x3 * m_matrices3x3x3[2];
}

} // hx