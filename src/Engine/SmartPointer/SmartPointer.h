#pragma once
#include "Counter.h"

template<class T>
class SharedPointer
{
public:
	//Default Constructor
	SharedPointer()
		:m_Pointer(nullptr),
		m_Counter(nullptr)
	{}

	//Destructor
	~SharedPointer()
	{
		ReleasePointer();
	}

	//Constructor with a Pointer - to avoid implicit conversion of types
	explicit SharedPointer(T* InPointer)
		:m_Pointer(InPointer),
		m_Counter(InPointer ? new Counter(1) : nullptr)
	{}


	//Copy Constructor
	SharedPointer(const SharedPointer& InOther)
		:m_Pointer(InOther.m_Pointer),
		m_Counter(InOther.m_Counter)
	{
		if (m_Counter)
		{
			(m_Counter->m_SharedReference)++;
		}
	}

	template<class U>
	SharedPointer(const SharedPointer<U>& InOther)
		:m_Pointer(InOther.m_Pointer),
		m_Counter(InOther.m_Counter)
	{
		if (m_Counter)
		{
			(m_Counter->m_SharedReference)++;
		}
	}

	//Assignment Operator
	SharedPointer& operator=(const SharedPointer& InOther)
	{
		if (m_Pointer != InOther.m_Pointer)
		{
			ReleasePointer();
			m_Pointer = InOther.m_Pointer;
			m_Counter = InOther.m_Counter;
			if (m_Counter)
			{
				(m_Counter->m_SharedReference)++;
			}
		}
		return *this;
	}
	
	template<class U>
	SharedPointer& operator=(const SharedPointer<U>& InOther)
	{
		if (m_Pointer != InOther.m_Pointer)
		{
			ReleasePointer();
			m_Pointer = InOther.m_Pointer;
			m_Counter = InOther.m_Counter;
			if (m_Counter)
			{
				(m_Counter->m_SharedReference)++;
			}
		}
		return *this;
	}

	//Assignment Operator nullptr
	SharedPointer& operator=(std::nullptr_t InNullPointer)
	{
		ReleasePointer();
		return *this;
	}

	//Arrow Operator
	T* operator->()
	{
		return m_Pointer;
	}

	const T* operator->() const
	{
		return m_Pointer;
	}

	//Indirection Operator
	T& operator*()
	{
		return *(m_Pointer);
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
		return m_Pointer != nullptr;
	}

	//Equal to Operator
	template<class U>
	bool operator==(const SharedPointer<U>& InOther)
	{
		return (m_Pointer == InOther.m_Pointer);
	}

private:

	void ReleasePointer()
	{
		if (m_Counter)
		{
			if ((--(m_Counter->m_SharedReference)) == 0)
			{
				//delete pointer
				delete m_Pointer;
				m_Pointer = nullptr;

				//delete counter
				delete m_Counter;
				m_Counter = nullptr;
			}
		}
	}

	T* m_Pointer;
	Counter* m_Counter;
};
