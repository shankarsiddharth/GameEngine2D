#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "MonsterChaseGame.h"
#include <iostream>
#include "Math/Matrix4x4.h"
#include <string>
#include <chrono>
#include "Helpers/EngineHelpers.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	const int LOOPCOUNT = 10000;

	float matArray[4][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
	Matrix4x4 newMatrix(matArray);
	Matrix4x4 newMatrix1(matArray);

	Matrix4x4 resultMatrixSIMD;
	Matrix4x4 resultMatrix;

	newMatrix1.Transpose();

	//SIMD Multiplication
	std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < LOOPCOUNT; i++)
	{
		resultMatrixSIMD = Matrix4x4();
		Matrix4x4::SIMDMultiply(newMatrix, newMatrix1, resultMatrixSIMD);
	}
	std::chrono::steady_clock::time_point endTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration SIMDtimeTaken = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
	std::string logTimeTaken = "Time Taken SIMD: " + std::to_string(SIMDtimeTaken.count()) + " microseconds.";
	EngineHelpers::DebugPrint(logTimeTaken);

	newMatrix1.Transpose();

	//Standard Multiplication
	startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < LOOPCOUNT; i++)
	{
		resultMatrix = newMatrix * newMatrix1;
	}
	endTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
	logTimeTaken = "Time Taken: " + std::to_string(timeTaken.count()) + " microseconds.";
	EngineHelpers::DebugPrint(logTimeTaken);

	if (resultMatrixSIMD == resultMatrix)
	{
		std::string logString = "Matrix SIMD Multiplication & Standard Multiplication values are same.";
		EngineHelpers::DebugPrint(logString);
	}
	else
	{
		std::string logString = "Mismatch in Matrix SIMD Multiplication & Standard Multiplication values.";
		EngineHelpers::DebugPrint(logString);
	}

	if (SIMDtimeTaken < timeTaken)
	{
		std::string logString = "Matrix SIMD Multiplication takes less time than standard multiplication.";
		EngineHelpers::DebugPrint(logString);
	}
	else
	{
		std::string logString = "Matrix SIMD Multiplication takes less time than standard multiplication.";
		EngineHelpers::DebugPrint(logString);
	}

	/*Vector4 newVector(17, 18, 19, 20);

	Vector4 resultV = newMatrix * newVector;

	Matrix4x4 resultM = newMatrix * newMatrix1;

	resultM.Transpose();

	Matrix4x4 resultMRZ = Matrix4x4::ZRotationMatrix(10);

	std::string resultString = "Value: " + std::to_string(newMatrix[43]);
	EngineHelpers::DebugPrint(resultString);
	*/
	return 0;

}