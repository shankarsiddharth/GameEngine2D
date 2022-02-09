#include "Vector2.h"

Vector2::Vector2(int InX, int InY)
{
	m_X = InX;
	m_Y = InY;
}

Vector2::Vector2()
	:m_X(0),
	m_Y(1)
{

}

int Vector2::X() const
{
	return m_X;
}

void Vector2::X(const int InX)
{
	m_X = InX;
}

int Vector2::Y() const
{
	return m_Y;
}

void Vector2::Y(const int InY)
{
	m_Y = InY;
}

Vector2 Vector2::operator*(const Vector2& InPoint)
{
	return Vector2(m_X * InPoint.m_X, m_Y * InPoint.m_Y);
}

void Vector2::operator*=(const Vector2& InPoint)
{
	m_X *= InPoint.m_X;
	m_Y *= InPoint.m_Y;
}

void Vector2::operator-=(const Vector2& InPoint)
{
	m_X -= InPoint.m_X;
	m_Y -= InPoint.m_Y;
}

void Vector2::operator+=(const Vector2& InPoint)
{
	m_X += InPoint.m_X;
	m_Y += InPoint.m_Y;
}

Vector2 Vector2::operator+(const Vector2& InPoint)
{
	return Vector2(m_X + InPoint.m_X, m_Y + InPoint.m_Y);
}

Vector2 Vector2::operator-(const Vector2& InPoint)
{
	return Vector2(m_X - InPoint.m_X, m_Y - InPoint.m_Y);
}
