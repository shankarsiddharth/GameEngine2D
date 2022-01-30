#pragma once
class Point2D
{
public:
	Point2D(int InX, int InY);
	Point2D();

	int X() const;
	int Y() const;

	void X(const int InX);
	void Y(const int InY);

	Point2D operator+(const Point2D& InPoint);
	Point2D operator-(const Point2D& InPoint);
	Point2D operator*(const Point2D& InPoint);	
	void operator+=(const Point2D& InPoint);	
	void operator-=(const Point2D& InPoint);
	void operator*=(const Point2D& InPoint);

private:
	int m_X;
	int m_Y;
};

