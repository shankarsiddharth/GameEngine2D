#pragma once

class Vector4
{
public:
	Vector4();
	~Vector4();

	Vector4(float InX, float InY, float InZ, float InW);
	Vector4(const Vector4& InOther);

	float X() const;
	float Y() const;
	float Z() const;
	float W() const;

	void X(const float InX);
	void Y(const float InY);
	void Z(const float InZ);
	void W(const float InW);

	Vector4 operator+(const Vector4& InVector);
	Vector4 operator-(const Vector4& InVector);
	Vector4 operator*(const Vector4& InVector);
	Vector4 operator/(const Vector4& InVector);

	Vector4& operator+=(const Vector4& InVector);
	Vector4& operator-=(const Vector4& InVector);
	
	Vector4& operator*=(float const& InValue);
	Vector4& operator/=(float const& InValue);

	Vector4 operator / (float const& InValue);
	Vector4 operator * (float const& InValue);

	static float DotProduct(const Vector4& InVector);

	static const Vector4 Zero;

private:
	float m_X;
	float m_Y;
	float m_Z;
	float m_W;
};