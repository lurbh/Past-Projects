/******************************************************************************/
/*!
\file_name      GameObject.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
This file contains the declarations of the Game Object class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include <vector>                     // std::vector
#include <type_traits>                // std::enable_if
#include "../Defines/AllComponents.h" // Components class
#include "../Defines/TraitList.h"     // All Trait type of an object

namespace object
{
class C_GameObject
{
	std::vector<C_Component*> m_component_list; // Components list
	std::string m_name;                         // Name of the object
	TRAIT m_trait;                              // Trait type of the object
	bool m_active = false;                      // Boolean for object is active

public:
	// Non-default constructor and act as default constructor
	C_GameObject(std::string name = "", TRAIT trait = DEFAULT);

	// Destructor
	~C_GameObject();

	// Add components into the game object
	void Add_Component(C_Component *component);

	// Find component in a game object
	C_Component *Find_Component(COMPONENTTYPE type);

	// Returns the pointer to the sprite component
	C_Sprite *Sprite();

	// Destroy the object by setting it to inactive
	void Destroy();

	// Getter functions
	bool Get_Active() const;
	std::string Get_Name() const;
	TRAIT Get_Trait() const;

	// Setter functions
	void Set_Active(bool active);
	void Set_Name(std::string name);

	// Creates and return a pointer to a copy of the game object
	C_GameObject *Clone();

	// Template functions that add components into the game object
	template <typename T>
	void Add_Component(const T &component)
	{
		T *p_clone = component.Clone();

		m_component_list.push_back(p_clone);

		component.~T();
	}

	// Returns a pointer to the component lists of the game object
	std::vector<C_Component*>& getCompVec()
	{
		return m_component_list;
	}
};

// Template functor that return a pointer to a component in the game object
template<typename COMP, typename = typename std::enable_if<std::is_base_of<C_Component, typename std::remove_reference<COMP>::type>::value>::type>
struct Get_Comp
{
	Get_Comp(C_GameObject& objIn) : comp(nullptr)
	{
		COMPONENTTYPE type = COMP().Get_Type();
		auto & vec = objIn.getCompVec();
		for(auto & elem : vec)
		{
			if(type == elem->Get_Type())
			{
				comp = dynamic_cast<COMP*>(elem);
				break;
			}
		}
	}
	COMP* comp;
	COMP* operator()() { return comp; }
};
} // namespace object