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

// Cubic Bezier Vertices (basis of a bezier spline)

// collection of vertices which each have a position and two controllers("handles").

// maybe add colour/id/data to each vertex?

// throws (char*) exceptions. these exception throws can be turned off: setThrowsExceptions(false);

#ifndef HX_PLINTH_BEZIER_VERTICES_HPP
#define HX_PLINTH_BEZIER_VERTICES_HPP

#include <vector>

namespace hx
{
	namespace Bezier
	{

class Vertices
{
public:
	struct Offset
	{
		double x, y;

		// offsets can be offset by offsets
		Offset operator+(const Offset& rhs);
		Offset operator-(const Offset& rhs);
	};
	struct Position
	{
		double x, y;

		// points can be offset by offsets
		Position operator+(const Offset& rhs);
		Position operator-(const Offset& rhs);

		// difference between two points is an offset
		Offset operator-(const Position& rhs) const;
	};

	class Vertex
	{
	public:
		Position position; // absolute position of vertex
		Offset frontHandle; // offset from position
		Offset backHandle; // offset from position
		Vertex();
	};

	Vertices();
	void reset();
	void loadFromVector(std::vector<Vertex>& vertices);
	void setNumberOfVertices(unsigned int numberOfVertices);
	unsigned int getNumberOfVertices();
	void addVertex();
	void addVertex(const Position& position);
	void addVertices(unsigned int numberOfVerticesToAdd);
	void removeLastVertex();
	void removeLastVertices(unsigned int numberOfVerticesToRemove);
	void moveVertex(unsigned int vertexIndex, const Position& position);
	Position getVertex(unsigned int vertexIndex);
	void moveFrontHandle(unsigned int vertexIndex, const Offset& offset);
	void moveBackHandle(unsigned int vertexIndex, const Offset& offset);
	void moveFrontHandleAbsolute(unsigned int vertexIndex, const Position& position);
	void moveBackHandleAbsolute(unsigned int vertexIndex, const Position& position);
	Offset getFrontHandle(unsigned int vertexIndex);
	Offset getBackHandle(unsigned int vertexIndex);
	Position getFrontHandleAbsolute(unsigned int vertexIndex);
	Position getBackHandleAbsolute(unsigned int vertexIndex);
	void setThrowsExceptions(bool doesThrow);
	bool getThrowsExceptions();
	//void update();

private:
	//BezierCubic m_bezier;
	std::vector<Vertex> m_vertices;
	bool m_throwsExceptions;

	bool isVertexIndexInRange(unsigned int index);
	void throwExceptionVertexIndexOutOfRange();
};

	} // namespace Bezier
} // namespace hx

#endif // HX_PLINTH_BEZIER_VERTICES_HPP