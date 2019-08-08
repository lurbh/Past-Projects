/******************************************************************************/
/*!
\file_name      GameObject.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the definitions of the Game Object class. The game object
	class is designed with a component based architect where every variables and
	behaviours are determined by the components the game object contains.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "GameObject.h"

namespace object
{
/******************************************************************************/
/*!
	Non-default constructor. This constructs a Game Object.
*/
/******************************************************************************/
C_GameObject::C_GameObject(std::string name, TRAIT trait)
	: m_name{ name }, m_trait{ trait }
{
}

/******************************************************************************/
/*!
	Destructor. Destruct the game object and clear the component list.
*/
/******************************************************************************/
C_GameObject::~C_GameObject()
{
	for(auto it = m_component_list.begin(); it != m_component_list.end(); ++it)
	{
		delete *it;
	}
}

/******************************************************************************/
/*!
	This function add components to the game object.
*/
/******************************************************************************/
void C_GameObject::Add_Component(C_Component *component)
{
	m_component_list.push_back(component);
}

/******************************************************************************/
/*!
	This function find components based on its type of the game object.
*/
/******************************************************************************/
C_Component *C_GameObject::Find_Component(COMPONENTTYPE type)
{
	for(auto it = m_component_list.begin(); it != m_component_list.end(); ++it)
	{
		if((*it)->Get_Type() == type)
		{
			return *it;
		}
	}

	return nullptr;
}

/******************************************************************************/
/*!
	This function returns a pointer to the sprite component of the object
*/
/******************************************************************************/
C_Sprite * C_GameObject::Sprite()
{
	for(auto it = m_component_list.begin(); it != m_component_list.end(); ++it)
	{
		if((*it)->Get_Type() == SPRITE)
		{
			return static_cast<C_Sprite*>(*it);
		}
	}
	return nullptr;
}

/******************************************************************************/
/*!
	This function destroys the object by setting it to inactive.
*/
/******************************************************************************/
void C_GameObject::Destroy()
{
	static_cast<C_Transform *>(Find_Component(TRANSFORM))->Set_Position(999, 999);
	m_active = false;
}

/******************************************************************************/
/*!
	This function returns true if object is active, false otherwise.
*/
/******************************************************************************/
bool C_GameObject::Get_Active() const
{
	return m_active;
}

/******************************************************************************/
/*!
This function returns the name of the game object.
*/
/******************************************************************************/
std::string C_GameObject::Get_Name() const
{
	return m_name;
}

/******************************************************************************/
/*!
	This function returns the trait type of the game object.
*/
/******************************************************************************/
TRAIT C_GameObject::Get_Trait() const
{
	return m_trait;
}

/******************************************************************************/
/*!
	This function sets the activity of the object.
*/
/******************************************************************************/
void C_GameObject::Set_Active(bool active)
{
	m_active = active;
}

/******************************************************************************/
/*!
	This function sets the name of the object.
*/
/******************************************************************************/
void C_GameObject::Set_Name(std::string name)
{
	m_name = name;
}

/******************************************************************************/
/*!
	This function returns a pointer to the clone of this component
*/
/******************************************************************************/
C_GameObject *C_GameObject::Clone()
{
	C_GameObject *p_clone = new C_GameObject{ m_name, m_trait };

	for(auto it = m_component_list.begin(); it != m_component_list.end(); ++it)
	{
		p_clone->m_component_list.push_back((*it)->Clone());
	}

	return p_clone;
}
} // namespace object
