#pragma once
#include "Counter.h"

template<class T>
class SharedPointer
{
public:
	//Default Constructor
	SharedPointer()
		:pPointer(nullptr),
		pCounter(nullptr)
	{}

	//Destructor
	~SharedPointer()
	{
		if (pCounter)
		{
			if ((--(pCounter->sharedReference)) == 0)
			{
				delete pPointer;
				pPointer = nullptr;
			}
		}
	}

	//Constructor with a Pointer - avoid implicit conversion of types
	explicit SharedPointer(T* i_Pointer)
		:pPointer(i_Pointer),
		pCounter(i_Pointer ? new Counter(1, 0) : nullptr)
	{}


	//Copy Constructor
	SharedPointer(const SharedPointer& i_OtherPointer)
		:pPointer(i_OtherPointer.pPointer),
		pCounter(i_OtherPointer.pCounter)
	{
		if (pCounter)
		{
			(pCounter->sharedReference)++;
		}
	}

	template<class U>
	SharedPointer(const SharedPointer<U>& i_OtherPointer)
		:pPointer(i_OtherPointer.pPointer),
		pCounter(i_OtherPointer.pPointer)
	{
		if (pCounter)
		{
			(pCounter->sharedReference)++;
		}
	}

	//Assignment Operator
	SharedPointer& operator=(const SharedPointer& i_OtherPointer)
	{
		if (this != &i_OtherPointer)
		{
			~SharedPointer();
			pPointer = i_OtherPointer.pPointer;
			pCounter = i_OtherPointer.pCounter;
			if (pCounter)
			{
				(pCounter->sharedReference)++;
			}
		}
		return *this;
	}
	
	//Assignment Operator nullptr
	SharedPointer& operator=(std::nullptr_t i_NullPointer)
	{
		~SharedPointer();
		return *this;
	}

	//Arrow Operator
	T* operator->()
	{
		return pPointer;
	}

	//Indirection Operator
	T* operator*()
	{
		return *(pPointer);
	}

	//Operator bool check - ()
	operator bool()
	{
		return pPointer != nullptr;
	}

	//Equal to Operator
	template<class U>
	bool operator==(const SharedPointer<U>& i_OtherPointer)
	{
		return (pPointer == i_OtherPointer.pPointer);
	}

private:
	T* pPointer;
	Counter* pCounter;
};
