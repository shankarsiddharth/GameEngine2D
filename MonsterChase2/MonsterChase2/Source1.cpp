//#include <assert.h>
//#include <stdio.h>
//#include <stdint.h>
//#include <Windows.h>
//
//#if defined _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#endif // _DEBUG
//#include "Object/GameObject.h"
//#include "Component/Component.h"
//
//
//int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
//{
//	GameObject* go = new GameObject();
//	Component* c1 = new Component(*go);
//	Component* c2 = new Component(*go);
//	Component* c3 = new Component(*go);
//	go->AddComponent(c1);
//	go->AddComponent(c2);
//	go->AddComponent(c3);
//	//go->RemoveComponent<Component>();
//	go->RemoveAllComponents();
//	delete go;
//
//	int a = 0;
//
//#if defined _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG
//	return 0;
//
//}