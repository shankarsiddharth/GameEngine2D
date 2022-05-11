//#include <Windows.h>
//
//#if defined _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#endif // _DEBUG
//
//#include "MonsterChaseGame.h"
//#include <iostream>
//#include "Math/Matrix4x4.h"
//
//int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
//{
//
//	float matArray[4][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
//	Matrix4x4 newMatrix(matArray);
//	Matrix4x4 newMatrix1(matArray);
//
//	Vector4 newVector(17, 18, 19, 20);
//
//	Vector4 resultV = newMatrix * newVector;
//
//	Matrix4x4 resultM = newMatrix * newMatrix1;
//
//	resultM.Transpose();
//
//	Matrix4x4 resultMRZ = Matrix4x4::ZRotationMatrix(10);
//
//	int q = 0;
//
//#ifdef _DEBUG
//	const size_t	lenBuffer = 65;
//	char			Buffer[lenBuffer];
//
//	sprintf_s(Buffer, lenBuffer, "Value %f\n", newMatrix[43]);
//	OutputDebugStringA(Buffer);
//#endif // __DEBUG
//
//#if defined _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG
//	return 0;
//
//}