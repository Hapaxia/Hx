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

#include "Vertices.hpp"

namespace hx
{
	namespace Bezier
	{

Vertices::Offset Vertices::Offset::operator+(const Offset& rhs)
{
	Offset returnOffset{ this->x, this->y };
	returnOffset.x += rhs.x;
	returnOffset.y += rhs.y;
	return returnOffset;
}

Vertices::Offset Vertices::Offset::operator-(const Offset& rhs)
{
	Offset returnOffset{ this->x, this->y };
	returnOffset.x -= rhs.x;
	returnOffset.y -= rhs.y;
	return returnOffset;
}

Vertices::Position Vertices::Position::operator+(const Offset& rhs)
{
	Position returnPosition{ this->x, this->y };
	returnPosition.x += rhs.x;
	returnPosition.y += rhs.y;
	return returnPosition;
}

Vertices::Position Vertices::Position::operator-(const Offset& rhs)
{
	Position returnPosition{ this->x, this->y };
	returnPosition.x -= rhs.x;
	returnPosition.y -= rhs.y;
	return returnPosition;
}

Vertices::Offset Vertices::Position::operator-(const Position& rhs) const
{
	Offset returnOffset{ this->x, this->y };
	returnOffset.x -= rhs.x;
	returnOffset.y -= rhs.y;
	return returnOffset;
}

Vertices::Vertex::Vertex() :
	position({ 0.0, 0.0 }),
	frontHandle({ 0.0, 0.0 }),
	backHandle({ 0.0, 0.0 })
{
}

Vertices::Vertices() :
	m_vertices(0),
	m_throwsExceptions(true)
{
}

// sets the number of vertices in the spline. resets all vertices. only sets if given number is two or higher.
void Vertices::setNumberOfVertices(unsigned int numberOfVertices)
{
	if (numberOfVertices < 2)
	{
		if (m_throwsExceptions)
			throw "Spline requires at least two vertices.";
		return;
	}
	m_vertices.resize(0);
	addVertices(numberOfVertices);
}

// loads vertices from vector of vertices
void Vertices::loadFromVector(std::vector<Vertex>& vertices)
{
	m_vertices = vertices;
}

// returns the number of vertices in the spline
unsigned int Vertices::getNumberOfVertices()
{
	return m_vertices.size();
}

// adds a vertex to the end of the spline
void Vertices::addVertex()
{
	m_vertices.push_back(Vertex());
}

void Vertices::addVertex(const Position& position)
{
	addVertex();
	m_vertices.back().position = position;
}

// adds multiple vertices to the end of the spline
void Vertices::addVertices(unsigned int numberOfVerticesToAdd)
{
	for (unsigned int b{ 0 }; b < numberOfVerticesToAdd; ++b)
		addVertex();
}

// removes a vertex from the end of the spline
void Vertices::removeLastVertex()
{
	if (m_vertices.size() > 0)
		m_vertices.pop_back();
	if (m_vertices.size() > 0)
		m_vertices.back().frontHandle = { 0.0, 0.0 }; // stop last vertex having a front handle
}

// removes multiple vertices from the end of the spline
void Vertices::removeLastVertices(unsigned int numberOfVerticesToRemove)
{
	for (unsigned int b{ 0 }; b < numberOfVerticesToRemove; ++b)
		removeLastVertex();
}

// moves vertex to given position
void Vertices::moveVertex(unsigned int vertexIndex, const Position& position)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return;
	}
	m_vertices[vertexIndex].position = position;
}

// returns position of vertex
Vertices::Position Vertices::getVertex(unsigned int vertexIndex)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return{ 0.0, 0.0 };
	}
	return m_vertices[vertexIndex].position;
}

// sets front handle's offset
void Vertices::moveFrontHandle(unsigned int vertexIndex, const Offset& offset)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return;
	}
	if (vertexIndex == m_vertices.size() - 1)
	{
		if (m_throwsExceptions)
			throw "Final vertex does not have a front handle.";
		return;
	}
	m_vertices[vertexIndex].frontHandle = offset;
}

// sets back handle's offset
void Vertices::moveBackHandle(unsigned int vertexIndex, const Offset& offset)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return;
	}
	if (vertexIndex == 0)
	{
		if (m_throwsExceptions)
			throw "Initial vertex does not have a back handle.";
		return;
	}
	m_vertices[vertexIndex].backHandle = offset;
}

// sets front handle's absolute position
void Vertices::moveFrontHandleAbsolute(unsigned int vertexIndex, const Position& position)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return;
	}
	if (vertexIndex == m_vertices.size() - 1)
	{
		if (m_throwsExceptions)
			throw "Final vertex does not have a front handle.";
		return;
	}
	m_vertices[vertexIndex].frontHandle = position - m_vertices[vertexIndex].position;
}

// sets back handle's absolute position
void Vertices::moveBackHandleAbsolute(unsigned int vertexIndex, const Position& position)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return;
	}
	if (vertexIndex == 0)
	{
		if (m_throwsExceptions)
			throw "Initial vertex does not have a back handle.";
		return;
	}
	m_vertices[vertexIndex].backHandle = position - m_vertices[vertexIndex].position;
}

// returns front handle's offset
Vertices::Offset Vertices::getFrontHandle(unsigned int vertexIndex)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return{ 0.0, 0.0 };
	}
	if (vertexIndex == m_vertices.size() - 1)
	{
		if (m_throwsExceptions)
			throw "Final vertex does not have a front handle.";
		return{ 0.0, 0.0 };
	}
	return m_vertices[vertexIndex].frontHandle;
}

// returns back handle's offset
Vertices::Offset Vertices::getBackHandle(unsigned int vertexIndex)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return{ 0.0, 0.0 };
	}
	if (vertexIndex == 0)
	{
		if (m_throwsExceptions)
			throw "Initial vertex does not have a back handle.";
		return{ 0.0, 0.0 };
	}
	return m_vertices[vertexIndex].backHandle;
}

// returns front handle's absolute position
Vertices::Position Vertices::getFrontHandleAbsolute(unsigned int vertexIndex)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return{ 0.0, 0.0 };
	}
	if (vertexIndex == m_vertices.size() - 1)
	{
		if (m_throwsExceptions)
			throw "Final vertex does not have a front handle.";
		return{ 0.0, 0.0 };
	}
	return m_vertices[vertexIndex].position + m_vertices[vertexIndex].frontHandle;
}

// returns back handle's absolute position
Vertices::Position Vertices::getBackHandleAbsolute(unsigned int vertexIndex)
{
	if (!isVertexIndexInRange(vertexIndex))
	{
		if (m_throwsExceptions)
			throwExceptionVertexIndexOutOfRange();
		return{ 0.0, 0.0 };
	}
	if (vertexIndex == 0)
	{
		if (m_throwsExceptions)
			throw "Initial vertex does not have a back handle.";
		return{ 0.0, 0.0 };
	}
	return m_vertices[vertexIndex].position + m_vertices[vertexIndex].backHandle;
}

// reset spline
void Vertices::reset()
{
	m_vertices.resize(0);
}

void Vertices::setThrowsExceptions(bool doesThrow)
{
	m_throwsExceptions = doesThrow;
}

bool Vertices::getThrowsExceptions()
{
	return m_throwsExceptions;
}

/*
void BezierSplineCubicVertices::update()
{

}
*/


// PRIVATE

bool Vertices::isVertexIndexInRange(unsigned int index)
{
	return index < m_vertices.size();
}

void Vertices::throwExceptionVertexIndexOutOfRange()
{
	if (m_throwsExceptions)
		throw "Vertex does not exist.";
}

	} // namespace Bezier
} // namespace hx