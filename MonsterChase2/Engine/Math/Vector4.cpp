#include "Vector4.h"

const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);

float Vector4::DotProduct(const Vector4& InVectorLHS, const Vector4& InVectorRHS)
{
	return	InVectorLHS.X() * InVectorRHS.X()
		+ InVectorLHS.Y() * InVectorRHS.Y()
		+ InVectorLHS.Z() * InVectorRHS.Z()
		+ InVectorLHS.W() * InVectorRHS.W();
}

Vector4::Vector4()
	:m_X(0),
	m_Y(0),
	m_Z(0),
	m_W(0)
{

}

Vector4::Vector4(const Vector2& InOther, float InZ, float InW)
	:m_X(InOther.X()),
	m_Y(InOther.Y()),
	m_Z(InZ),
	m_W(InW)
{

}

Vector4& Vector4::operator=(const Vector4& InOther)
{
	m_X = InOther.m_X;
	m_Y = InOther.m_Y;
	m_Z = InOther.m_Z;
	m_W = InOther.m_W;
	return *this;
}

Vector4::~Vector4()
{

}

Vector4::Vector4(float InX, float InY, float InZ, float InW)
	:m_X(InX),
	m_Y(InY),
	m_Z(InZ),
	m_W(InW)
{

}

Vector4::Vector4(const Vector4& InOther)
	:m_X(InOther.m_X),
	m_Y(InOther.m_Y),
	m_Z(InOther.m_Z),
	m_W(InOther.m_W)
{

}

float Vector4::X() const
{
	return m_X;
}

void Vector4::X(const float InX)
{
	m_X = InX;
}

float Vector4::Y() const
{
	return m_Y;
}

void Vector4::Y(const float InY)
{
	m_Y = InY;
}

float Vector4::Z() const
{
	return m_Z;
}

void Vector4::Z(const float InZ)
{
	m_Z = InZ;
}

float Vector4::W() const
{
	return m_W;
}

void Vector4::W(const float InW)
{
	m_W = InW;
}

Vector4 Vector4::operator+(const Vector4& InVector)
{
	return Vector4(
		m_X + InVector.m_X,
		m_Y + InVector.m_Y,
		m_Z + InVector.m_Z,
		m_W + InVector.m_W
	);
}

Vector4 Vector4::operator-(const Vector4& InVector)
{
	return Vector4(
		m_X - InVector.m_X,
		m_Y - InVector.m_Y,
		m_Z - InVector.m_Z,
		m_W - InVector.m_W
	);
}

Vector4& Vector4::operator+=(const Vector4& InVector)
{
	m_X -= InVector.m_X;
	m_Y -= InVector.m_Y;
	m_Z -= InVector.m_Z;
	m_W -= InVector.m_W;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& InVector)
{
	m_X -= InVector.m_X;
	m_Y -= InVector.m_Y;
	m_Z -= InVector.m_Z;
	m_W -= InVector.m_W;
	return *this;
}

Vector4 Vector4::operator/(float const& InValue)
{
	return Vector4(
		m_X / InValue,
		m_Y / InValue,
		m_Z / InValue,
		m_W / InValue
	);
}

Vector4 Vector4::operator*(float const& InValue)
{
	return Vector4(
		m_X * InValue,
		m_Y * InValue,
		m_Z * InValue,
		m_W * InValue
	);
}

Vector4& Vector4::operator*=(float const& InValue)
{
	m_X *= InValue;
	m_Y *= InValue;
	m_Z *= InValue;
	m_W *= InValue;
	return *this;
}

Vector4& Vector4::operator/=(float const& InValue)
{
	m_X /= InValue;
	m_Y /= InValue;
	m_Z /= InValue;
	m_W /= InValue;
	return *this;
}
