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
		ReleasePointer();
	}

	//Constructor with a Pointer - to avoid implicit conversion of types
	explicit SharedPointer(T* i_Pointer)
		:pPointer(i_Pointer),
		pCounter(i_Pointer ? new Counter(1) : nullptr)
	{}


	//Copy Constructor
	SharedPointer(const SharedPointer& i_Other)
		:pPointer(i_Other.pPointer),
		pCounter(i_Other.pCounter)
	{
		if (pCounter)
		{
			(pCounter->sharedReference)++;
		}
	}

	template<class U>
	SharedPointer(const SharedPointer<U>& i_Other)
		:pPointer(i_Other.pPointer),
		pCounter(i_Other.pCounter)
	{
		if (pCounter)
		{
			(pCounter->sharedReference)++;
		}
	}

	//Assignment Operator
	SharedPointer& operator=(const SharedPointer& i_Other)
	{
		if (pPointer != i_Other.pPointer)
		{
			ReleasePointer();
			pPointer = i_Other.pPointer;
			pCounter = i_Other.pCounter;
			if (pCounter)
			{
				(pCounter->sharedReference)++;
			}
		}
		return *this;
	}
	
	template<class U>
	SharedPointer& operator=(const SharedPointer<U>& i_Other)
	{
		if (pPointer != i_Other.pPointer)
		{
			ReleasePointer();
			pPointer = i_Other.pPointer;
			pCounter = i_Other.pCounter;
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
		ReleasePointer();
		return *this;
	}

	//Arrow Operator
	T* operator->()
	{
		return pPointer;
	}

	const T* operator->() const
	{
		return pPointer;
	}

	//Indirection Operator
	T& operator*()
	{
		return *(pPointer);
	}

	////Remove this function
	////Temporary Access Operator
	//T* AccessPointer()
	//{
	//	return pPointer;
	//}

	//Operator bool check - ()
	operator bool()
	{
		return pPointer != nullptr;
	}

	//Equal to Operator
	template<class U>
	bool operator==(const SharedPointer<U>& i_Other)
	{
		return (pPointer == i_Other.pPointer);
	}

private:

	void ReleasePointer()
	{
		if (pCounter)
		{
			if ((--(pCounter->sharedReference)) == 0)
			{
				//delete pointer
				delete pPointer;
				pPointer = nullptr;

				//delete counter
				delete pCounter;
				pCounter = nullptr;
			}
		}
	}

	T* pPointer;
	Counter* pCounter;
};
