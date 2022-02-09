
template<class T>
void GameObject::AddComponent(T* newComponent)
{
	componentList.push_back(newComponent);
}


template<class T>
void GameObject::RemoveComponent()
{
	for (std::vector<Component*>::iterator iterator = componentList.begin(); iterator != componentList.end();)
	{
		if (dynamic_cast<T*>(*iterator) != nullptr)
		{
			Component* element = *iterator;
			if (element != nullptr)
			{
				delete element;
				element = nullptr;
			}
			iterator = componentList.erase(iterator);
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
	for (std::vector<Component*>::iterator iterator = componentList.begin(); iterator != componentList.end(); ++iterator)
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
	for (std::vector<Component*>::iterator iterator = componentList.begin(); iterator != componentList.end(); ++iterator)
	{
		if (dynamic_cast<T*>(*iterator) != nullptr)
		{
			return true;
		}
	}
	return false;
}
