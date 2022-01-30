#include "Point2D.h"

Point2D::Point2D(int InX, int InY)
{
	m_X = InX;
	m_Y = InY;
}

Point2D::Point2D()
	:m_X(0),
	m_Y(1)
{

}

int Point2D::X() const
{
	return m_X;
}

void Point2D::X(const int InX)
{
	m_X = InX;
}

int Point2D::Y() const
{
	return m_Y;
}

void Point2D::Y(const int InY)
{
	m_Y = InY;
}

Point2D Point2D::operator*(const Point2D& InPoint)
{
	return Point2D(m_X * InPoint.m_X, m_Y * InPoint.m_Y);
}

void Point2D::operator*=(const Point2D& InPoint)
{
	m_X *= InPoint.m_X;
	m_Y *= InPoint.m_Y;
}

void Point2D::operator-=(const Point2D& InPoint)
{
	m_X -= InPoint.m_X;
	m_Y -= InPoint.m_Y;
}

void Point2D::operator+=(const Point2D& InPoint)
{
	m_X += InPoint.m_X;
	m_Y += InPoint.m_Y;
}

Point2D Point2D::operator+(const Point2D& InPoint)
{
	return Point2D(m_X + InPoint.m_X, m_Y + InPoint.m_Y);
}

Point2D Point2D::operator-(const Point2D& InPoint)
{
	return Point2D(m_X - InPoint.m_X, m_Y - InPoint.m_Y);
}
