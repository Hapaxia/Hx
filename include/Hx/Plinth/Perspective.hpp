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

#ifndef HX_PERSPECTIVE_HPP
#define HX_PERSPECTIVE_HPP

#include "Generic.hpp"
#include "Matrix.hpp"
#include "Math.hpp"
#include <math.h>
#include <vector>

namespace hx
{

class Perspective
{
public:
	Perspective();
	void setDepth(double depth);
	double getDepth();
	void setScale(double scale);
	double getScale();
	void setProjectionOrigin(Vector2d origin);
	Vector2d getProjectionOrigin();
	void setTransformationOrigin(Vector3d origin);
	Vector3d getTransformationOrigin();

	Vector2d projectPoint(const Vector3d& point) const;

	void resetMatrix();
	void rotateMatrix(const Vector3d& rotationVector);
	void setMatrixAsRotation(const Vector3d& rotationVector);

	void transformPoint(Vector3d& point);
	void transformPoints(std::vector<Vector3d>& points);
	void transformPointFromPoint(Vector3d& point, const Vector3d& origPoint);
	void transformPointsFromPoints(std::vector<Vector3d>& points, const std::vector<Vector3d>& origPoints);

	void translatePoint(Vector3d& point, const Vector3d& translationVector);
	void scalePoint(Vector3d& point, const Vector3d& scaleVector);
	void scalePoint(Vector3d& point, double scalar);
	void rotatePoint(Vector3d& point, const Vector3d& rotationVector);
	void rotatePoints(std::vector<Vector3d>& points, const Vector3d& rotationVector);

private:
	double m_depth;
	Vector2d m_projectionOrigin;
	Vector3d m_transformationOrigin;
	std::vector<hx::Matrix> m_matrices3x3x3;
	hx::Matrix m_matrix3x3;
	double m_scale;

	void subtractTransformationOrigin(Vector3d& point);
	void addTransformationOrigin(Vector3d& point);
	void setMatrixAny3x3(hx::Matrix& matrix, std::vector<std::vector<double>> matrixGrid);
	void setMatrix3x3(std::vector<std::vector<double>> matrixGrid);
	void unscaleVector(Vector3d& vector);
	void scaleVector(Vector3d& vector);
	void makeMatrixFromMatrices();
	void multiplyMatrixWithMatrices();
};


} // namespace hx
#endif // HX_PERSPECTIVE_HPP