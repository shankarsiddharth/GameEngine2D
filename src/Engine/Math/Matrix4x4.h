#pragma once
#include "Vector4.h"

#define MATRIX_DIMENSION_4 4

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(float InMatrixArray[MATRIX_DIMENSION_4][MATRIX_DIMENSION_4]);
	~Matrix4x4();

	Matrix4x4(const Matrix4x4& InOtherMatrix);
	Matrix4x4& operator=(const Matrix4x4& InOtherMatrix);

	Matrix4x4 operator*(const Matrix4x4& InOtherMatrix);
	Vector4 operator*(const Vector4& InVector);

	float operator[](const int RowColumnValue) const;
	bool operator==(const Matrix4x4& InOtherMatrix);

	void Transpose();

	static void SIMDMultiply(const Matrix4x4& InA, const Matrix4x4& InB, Matrix4x4& OutResult);

	//Column Based Operation
	static Matrix4x4 ZRotationMatrix(float InRadians);
	static Matrix4x4 TranslationMatrix(float InX, float InY, float InZ);

	static Matrix4x4 IdentityMatrix();
	static Matrix4x4 ScaleMatrix(float InScaleX, float InScaleY, float InScaleZ);

private:
	static Matrix4x4 InitializeMatrix(float InValue);
	static bool IsFloatEqual(float InA, float InB, float InToleranceValue = 1e-9f);

	float m_RC[MATRIX_DIMENSION_4][MATRIX_DIMENSION_4];
};