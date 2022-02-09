#pragma once

class Vector2
{
public:
	Vector2(int InX, int InY);
	Vector2();

	int X() const;
	int Y() const;

	void X(const int InX);
	void Y(const int InY);

	Vector2 operator+(const Vector2& InPoint);
	Vector2 operator-(const Vector2& InPoint);
	Vector2 operator*(const Vector2& InPoint);	
	void operator+=(const Vector2& InPoint);	
	void operator-=(const Vector2& InPoint);
	void operator*=(const Vector2& InPoint);

private:
	int m_X;
	int m_Y;
};

