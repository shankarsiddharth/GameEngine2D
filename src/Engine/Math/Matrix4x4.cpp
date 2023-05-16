#include "Matrix4x4.h"
#include <cassert>
#include <corecrt_math.h>
#include <intrin.h>

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			m_RC[i][j] = 0.0f;
		}
	}
}

Matrix4x4::Matrix4x4(float InMatrix[MATRIX_DIMENSION_4][MATRIX_DIMENSION_4])
{
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			m_RC[i][j] = InMatrix[i][j];
		}
	}
}

Matrix4x4::Matrix4x4(const Matrix4x4& InOtherMatrix)
{
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			m_RC[i][j] = InOtherMatrix.m_RC[i][j];
		}
	}
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& InOtherMatrix)
{
	Matrix4x4 resultMatrix(InitializeMatrix(0.0f));
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			for (int k = 0; k < MATRIX_DIMENSION_4; k++)
			{
				resultMatrix.m_RC[i][j] += m_RC[i][k] * InOtherMatrix.m_RC[k][j];
			}
		}
	}
	return resultMatrix;
}

Vector4 Matrix4x4::operator*(const Vector4& InVector)
{
	Vector4 resultVector(Vector4::Zero);
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			float iValue = 0.0f;
			if (j == 0) iValue = InVector.X() * m_RC[i][j];
			if (j == 1) iValue = InVector.Y() * m_RC[i][j];
			if (j == 2) iValue = InVector.Z() * m_RC[i][j];
			if (j == 3) iValue = InVector.W() * m_RC[i][j];
			if (i == 0) resultVector.X(resultVector.X() + iValue);
			if (i == 1) resultVector.Y(resultVector.Y() + iValue);
			if (i == 2) resultVector.Z(resultVector.Z() + iValue);
			if (i == 3) resultVector.W(resultVector.W() + iValue);
		}
	}
	return resultVector;
}

float Matrix4x4::operator[](const int RowColumnValue) const
{
	int columnValue = RowColumnValue % 10;
	int columnIndex = columnValue - 1;

	int rowValue = RowColumnValue / 10;
	int rowIndex = rowValue - 1;

	assert(columnIndex >= 0 && columnIndex < MATRIX_DIMENSION_4);
	assert(rowIndex >= 0 && rowIndex < MATRIX_DIMENSION_4);

	return m_RC[rowIndex][columnIndex];
}

bool Matrix4x4::operator==(const Matrix4x4& InOtherMatrix)
{
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			if (!IsFloatEqual(m_RC[i][j], InOtherMatrix.m_RC[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}

void Matrix4x4::Transpose()
{
	Matrix4x4 transposeMatrix;
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			transposeMatrix.m_RC[j][i] = m_RC[i][j];
		}
	}
	*this = transposeMatrix;
}

void Matrix4x4::SIMDMultiply(const Matrix4x4& InA, const Matrix4x4& InTransposeMatrixB, Matrix4x4& OutResult)
{
	__declspec(align(16)) Matrix4x4 transposeMatrixB(InTransposeMatrixB);

	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			__m128* m1 = (__m128*) InA.m_RC[i];
			__m128* m2 = (__m128*) transposeMatrixB.m_RC[j];
			float* res;
			for (int k = 0; k < MATRIX_DIMENSION_4; k+=MATRIX_DIMENSION_4)
			{
				__m128 m3 = _mm_mul_ps(*m1, *m2);
				res = (float*)&m3;
				OutResult.m_RC[i][j] += res[0]+res[1]+res[2]+res[3];
				m1++;
				m2++;
			}			
		}		
	}
}

Matrix4x4 Matrix4x4::ZRotationMatrix(float InRadians)
{
	float sinValue = sinf(InRadians);
	float cosValue = cosf(InRadians);

	Matrix4x4 zRotationMatrix(InitializeMatrix(0.0f));

	zRotationMatrix.m_RC[0][0] = cosValue;
	zRotationMatrix.m_RC[0][1] = -sinValue;
	zRotationMatrix.m_RC[1][0] = sinValue;
	zRotationMatrix.m_RC[1][1] = cosValue;
	zRotationMatrix.m_RC[2][2] = 1.0f;
	zRotationMatrix.m_RC[3][3] = 1.0f;

	return zRotationMatrix;
}

Matrix4x4 Matrix4x4::TranslationMatrix(float InX, float InY, float InZ)
{
	Matrix4x4 translationMatrix(InitializeMatrix(0.0f));

	translationMatrix.m_RC[0][0] = 1.0f;
	translationMatrix.m_RC[1][1] = 1.0f;
	translationMatrix.m_RC[2][2] = 1.0f;
	translationMatrix.m_RC[3][3] = 1.0f;

	translationMatrix.m_RC[0][3] = InX;
	translationMatrix.m_RC[1][3] = InY;
	translationMatrix.m_RC[2][3] = InZ;

	return translationMatrix;
}

Matrix4x4 Matrix4x4::IdentityMatrix()
{
	Matrix4x4 identityMatrix;
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			identityMatrix.m_RC[i][j] = 0.0f;
			if (i == j)
			{
				identityMatrix.m_RC[i][j] = 1.0f;
			}
		}
	}
	return identityMatrix;
}

Matrix4x4 Matrix4x4::ScaleMatrix(float InScaleX, float InScaleY, float InScaleZ)
{
	Matrix4x4 scaleMatrix(InitializeMatrix(0.0f));
	scaleMatrix.m_RC[0][0] = InScaleX;
	scaleMatrix.m_RC[1][1] = InScaleY;
	scaleMatrix.m_RC[2][2] = InScaleZ;
	scaleMatrix.m_RC[3][3] = 1.0f;
	return scaleMatrix;
}

Matrix4x4 Matrix4x4::InitializeMatrix(float InValue)
{
	Matrix4x4 newMatrix;
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			newMatrix.m_RC[i][j] = InValue;
		}
	}
	return newMatrix;
}

bool Matrix4x4::IsFloatEqual(float InA, float InB, float InToleranceValue/* = 1e-9f*/)
{
	if (fabs((double)InA - (double)InB) < InToleranceValue)
	{
		return true;
	}
	return false;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& InOtherMatrix)
{
	for (int i = 0; i < MATRIX_DIMENSION_4; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION_4; j++)
		{
			m_RC[i][j] = InOtherMatrix.m_RC[i][j];
		}
	}
	return *this;
}

Matrix4x4::~Matrix4x4()
{

}
