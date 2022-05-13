
template<class T>
void GameObject::AddComponent(T* InNewComponent)
{
	m_ComponentList.push_back(InNewComponent);
}


template<class T>
void GameObject::RemoveComponent()
{
	for (std::vector<Component*>::iterator iterator = m_ComponentList.begin(); iterator != m_ComponentList.end();)
	{
		if (dynamic_cast<T*>(*iterator) != nullptr)
		{
			Component* element = *iterator;
			if (element != nullptr)
			{
				delete element;
				element = nullptr;
			}
			iterator = m_ComponentList.erase(iterator);
		}
		else
		{
			++iterator;
		}
	}	
}

template<class T>
T* GameObject::GetComponent()
{
	for (std::vector<Component*>::iterator iterator = m_ComponentList.begin(); iterator != m_ComponentList.end(); ++iterator)
	{
		if (dynamic_cast<T*>(*iterator) != nullptr)
		{
			return dynamic_cast<T*>(*iterator);
		}
	}
	return nullptr;
}


template<class T>
bool GameObject::HasComponent()
{
	for (std::vector<Component*>::iterator iterator = m_ComponentList.begin(); iterator != m_ComponentList.end(); ++iterator)
	{
		if (dynamic_cast<T*>(*iterator) != nullptr)
		{
			return true;
		}
	}
	return false;
}
