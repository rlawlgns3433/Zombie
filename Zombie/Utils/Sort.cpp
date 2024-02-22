#include "pch.h"
#include "Sort.h"

namespace Utils
{
	bool Sort::sortGameObject(GameObject* obj1, GameObject* obj2)
	{
		if (obj1->sortLayer != obj2->sortLayer)
		{
			return obj1->sortLayer < obj2->sortLayer;
		}
		return obj1->sortOrder < obj2->sortOrder;
	}
}
