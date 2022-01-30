#pragma once
#include <xutility>

template <class T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* next;
		Node(T val) : data(val), next(nullptr) {}
		Node() : next(nullptr) {}
		~Node() {
			delete data;
			data = nullptr;
			next = nullptr;
		}
	};
	Node* head;
	
public:
	LinkedList() : head(nullptr) {
		index = -1;
	}
	LinkedList(const LinkedList<T>& ll) = delete;
	LinkedList& operator=(LinkedList const&) = delete;
	~LinkedList();
	void insert(T);	
	void deleteNode(T);
	T& operator[](size_t index);
	T& operator[](size_t index) const;
	size_t getLength();

private:
	struct Node* search(T n)
	{
		Node* node = head;
		while (node != nullptr)
		{
			if (node->data == n)
				return node;
			node = node->next;
		}

		//std::cerr << "index not found \n";
		return nullptr;
	}

	size_t index;
};

template <class T>
size_t LinkedList<T>::getLength()
{
	return index + 1;
}

template <class T>
T& LinkedList<T>::operator[](size_t list_index) const
{
	if (list_index < 0 || list_index > index)
	{
		//Out of Bounds Exception
	}
	Node* node = head;
	size_t count = 0;
	while (node != nullptr)
	{
		if (list_index == count)
		{
			return node->data;
		}
		node = node->next;
		count++;
	}

	//std::cerr << "index not found \n";	
	return *(new T());
}

template <class T>
T& LinkedList<T>::operator[](size_t list_index)
{
	if (list_index < 0 || list_index > index)
	{
		//Out of Bounds Exception
	}
	Node* node = head;
	size_t count = 0;
	while (node != nullptr)
	{
		if (list_index == count)
		{
			return node->data;
		}	
		node = node->next;
		count++;
	}

	//std::cerr << "index not found \n";
	return *(new T());
}

template <class T>
void LinkedList<T>::insert(T data)
{
	Node* t = new Node(data);
	Node* tmp = head;
	if (tmp == nullptr)
	{
		head = t;		
	}
	else
	{
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		tmp->next = t;		
	}
	index++;
}

template <class T>
void LinkedList<T>::deleteNode(T data)
{
	Node* node = search(data);
	Node* tmp = head;

	if (tmp == node)
	{
		head = tmp->next;
		delete node;
		node = nullptr;
		index--;
	}
	else if (node != nullptr)
	{
		while (node != nullptr)
		{
			if (tmp->next == node)
			{
				tmp->next = node->next;
				delete node;
				node = nullptr;
				index--;
				return;
			}
			tmp = tmp->next;
		}		
	}
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Node* tmp = nullptr;
	while (head)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = nullptr;
}

