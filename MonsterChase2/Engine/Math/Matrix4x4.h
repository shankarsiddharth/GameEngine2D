#pragma once
#include "Vector4.h"

#define MATRIX_DIMENSION 4

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(float InMatrixArray[MATRIX_DIMENSION][MATRIX_DIMENSION]);
	~Matrix4x4();

	Matrix4x4(const Matrix4x4& InOtherMatrix);
	Matrix4x4& operator=(const Matrix4x4& InOtherMatrix);

	Matrix4x4 operator*(const Matrix4x4& InOtherMatrix);
	Vector4 operator*(const Vector4& InVector);

	float operator[](const int RowColumnValue) const;

	void Transpose();

	//Column Based Operation
	static Matrix4x4 ZRotationMatrix(float InRadians);
	static Matrix4x4 TranslationMatrix(float InX, float InY, float InZ);

	static Matrix4x4 IdentityMatrix();
	static Matrix4x4 ScaleMatrix(float InScaleX, float InScaleY, float InScaleZ);

private:
	static Matrix4x4 InitializeMatrix(float InValue);

	float m_RC[MATRIX_DIMENSION][MATRIX_DIMENSION];
};