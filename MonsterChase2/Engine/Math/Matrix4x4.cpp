#include "Matrix4x4.h"
#include <cassert>

Matrix4x4::Matrix4x4()
{

}

Matrix4x4::Matrix4x4(float InMatrix[MATRIX_DIMENSION][MATRIX_DIMENSION])
{
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
		{
			m_RC[i][j] = InMatrix[i][j];
		}
	}
}

Matrix4x4::Matrix4x4(const Matrix4x4& InOtherMatrix)
{
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
		{
			m_RC[i][j] = InOtherMatrix.m_RC[i][j];
		}
	}
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& InOtherMatrix)
{
	Matrix4x4 resultMatrix;
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
		{
			for (int k = 0; k < MATRIX_DIMENSION; k++)
			{
				resultMatrix.m_RC[i][j] += m_RC[i][k] * InOtherMatrix.m_RC[k][j];
			}
		}
	}
	return resultMatrix;
}

Matrix4x4 Matrix4x4::operator*(const Vector4& InVector)
{
	// TODO: Matrix x Vector
	return Matrix4x4();
}

float Matrix4x4::operator[](const int RowColumnValue) const
{
	int columnValue = RowColumnValue % 10;
	int columnIndex = columnValue - 1;

	int rowValue = RowColumnValue / 10;
	int rowIndex = rowValue - 1;

	assert(columnIndex >= 0 && columnIndex < MATRIX_DIMENSION);
	assert(rowIndex >= 0 && rowIndex < MATRIX_DIMENSION);

	return m_RC[rowIndex][columnIndex];
}

void Matrix4x4::Transpose()
{
	Matrix4x4 transposeMatrix;
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
		{
			transposeMatrix.m_RC[j][i] = m_RC[i][j];
		}
	}
	*this = transposeMatrix;
}

Matrix4x4 Matrix4x4::ZRotationMatrix(float InRadians)
{
	//TODO: ZRotation Matrix
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::TranslationMatrix(float InX, float InY, float InZ)
{
	//TODO: Translation Matrix
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::IdentityMatrix()
{
	Matrix4x4 identityMatrix;
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
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
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
		{
			newMatrix.m_RC[i][j] = InValue;
		}
	}
	return newMatrix;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& InOtherMatrix)
{
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0 ; j < MATRIX_DIMENSION; j++)
		{
			m_RC[i][j] = InOtherMatrix.m_RC[i][j];
		}
	}
	return *this;
}

Matrix4x4::~Matrix4x4()
{

}
