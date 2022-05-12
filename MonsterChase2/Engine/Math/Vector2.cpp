#include "Vector2.h"

Vector2 Vector2::PerpendicularVector(const Vector2& InVector)
{
	return Vector2(-1.0f * InVector.m_Y, InVector.m_X);
}

const Vector2 Vector2::Zero(0.0f, 0.0f);

Vector2 Vector2::operator/(float const& InValue)
{
	Vector2 result(Vector2::Zero);
	result.m_X = m_X / InValue;
	result.m_Y = m_Y / InValue;
	return result;
}

Vector2 Vector2::operator*(float const& InValue)
{
	Vector2 result(Vector2::Zero);
	result.m_X = m_X * InValue;
	result.m_Y = m_Y * InValue;
	return result;
}

Vector2::Vector2(float InX, float InY)
{
	m_X = InX;
	m_Y = InY;
}

Vector2::Vector2()
	:m_X(0),
	m_Y(1)
{

}

float Vector2::X() const
{
	return m_X;
}

void Vector2::X(const float InX)
{
	m_X = InX;
}

float Vector2::Y() const
{
	return m_Y;
}

void Vector2::Y(const float InY)
{
	m_Y = InY;
}

Vector2 Vector2::operator*(const Vector2& InVector)
{
	return Vector2(m_X * InVector.m_X, m_Y * InVector.m_Y);
}

void Vector2::operator*=(const Vector2& InVector)
{
	m_X *= InVector.m_X;
	m_Y *= InVector.m_Y;
}

void Vector2::operator-=(const Vector2& InVector)
{
	m_X -= InVector.m_X;
	m_Y -= InVector.m_Y;
}

void Vector2::operator+=(const Vector2& InVector)
{
	m_X += InVector.m_X;
	m_Y += InVector.m_Y;
}

Vector2 Vector2::operator+(const Vector2& InVector)
{
	return Vector2(m_X + InVector.m_X, m_Y + InVector.m_Y);
}

Vector2 Vector2::operator-(const Vector2& InVector)
{
	return Vector2(m_X - InVector.m_X, m_Y - InVector.m_Y);
}
