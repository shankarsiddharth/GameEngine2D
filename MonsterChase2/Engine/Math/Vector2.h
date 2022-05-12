#pragma once

class Vector2
{
public:
	Vector2(float InX, float InY);
	Vector2();

	float X() const;
	float Y() const;

	void X(const float InX);
	void Y(const float InY);

	Vector2 operator+(const Vector2& InVector);
	Vector2 operator-(const Vector2& InVector);
	Vector2 operator*(const Vector2& InVector);	
	void operator+=(const Vector2& InVector);	
	void operator-=(const Vector2& InVector);
	void operator*=(const Vector2& InVector);

	Vector2 operator / (float const& InValue);
	Vector2 operator * (float const& InValue);

	static Vector2 PerpendicularVector(const Vector2& InVector);

	static const Vector2 Zero;

private:
	float m_X;
	float m_Y;
};

