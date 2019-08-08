/******************************************************************************/
/*!
\file_name		ObjectManager.cpp
\project_name	Double Tap
\primary_author	Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the definitions of the Object Manager class. This class
	manages all unique objects and object instances in the game. The manager
	creates and stores all game objects and instances and also clears the game
	objects and instances when the game exits.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "ObjectManager.h"

namespace object
{
/******************************************************************************/
/*!
	Destructor of the Object Manager. It destruct the Object Manager and deletes
	all object in object vector and all object instances in the object instances
	vector.
*/
/******************************************************************************/
C_ObjectManager::~C_ObjectManager()
{
	// Deletes all object instances
	for(auto itr = m_obj_inst_list.begin(); itr != m_obj_inst_list.end(); ++itr)
		delete(*itr);

	// Destroys all unique object
	for(auto itr = m_obj_list.begin(); itr != m_obj_list.end(); ++itr)
		Destroy(*itr);

	/*
		Creates empty vectors and swap with the original object vector and object
		instances vector and let std::vector clear itself when it is out of
		scope
	*/
	ObjectVector temp;
	ObjectInstVector temp2;

	m_obj_list.swap(temp);
	m_obj_inst_list.swap(temp2);
}

/******************************************************************************/
/*!
	This function create and insert a unique object into the object vector and
	returns the pointer to the object.
*/
/******************************************************************************/
C_GameObject *C_ObjectManager::Push_Obj(std::string name, TRAIT trait)
{
	// Create the game object with name and trait
	C_GameObject *temp = new C_GameObject(name, trait);

	// Insert the game object into the object vector
	m_obj_list.push_back(temp);

	// Returns the pointer to the created game object
	return temp;
}

/******************************************************************************/
/*!
	This function create and insert an object instance of a unique object in the
	object vector and returns the pointer to the object instance.
*/
/******************************************************************************/
C_GameObject *C_ObjectManager::Push_Obj_Inst(std::string name)
{
	// Grab the unique object from the object vector by name
	C_GameObject *temp = Get_Obj_By_Name(name);

	// Return nullptr if object does not exist in the object vector
	if(!temp)
		return nullptr;

	// Clone the unique object
	C_GameObject *temp_inst = temp->Clone();

	// Copy all its component by cloning
	for(auto it = temp_inst->getCompVec().begin();
		it != temp_inst->getCompVec().end(); ++it)
	{
		(*it)->Set_Obj(temp_inst);
	}

	// Insert the create object instance into object instance list
	m_obj_inst_list.push_back(temp_inst);

	// Return the pointer to the object instance.
	return temp_inst;
}

/******************************************************************************/
/*!
	This function destroys the object instance by setting the object instance to
	inactive.
*/
/******************************************************************************/
void C_ObjectManager::Destroy_Inst(C_GameObject *obj)
{
	// Return if obj is already inactive
	if(!obj->Get_Active())
		return;

	obj->Set_Active(false);
}

/******************************************************************************/
/*!
	This function destroys the unique object by freeing the object's mesh.
*/
/******************************************************************************/
void C_ObjectManager::Destroy(C_GameObject *obj)
{
	object::C_Sprite *p_sprite =
		static_cast<object::C_Sprite *>(obj->Find_Component(SPRITE));

	if(p_sprite)
		p_sprite->Free_Mesh();
}

/******************************************************************************/
/*!
	This function destroys all unique object in the object vector.
*/
/******************************************************************************/
void C_ObjectManager::Unload_All_Object()
{
	//	Traverse the object vector, destroy and delete all object
	for(auto itr = m_obj_list.begin(); itr != m_obj_list.end(); ++itr)
	{
		Destroy(*itr);
		delete *itr;
	}

	ObjectVector temp;
	m_obj_list.swap(temp);
}

/******************************************************************************/
/*!
	This function destroys all object instances in the object instance vector.
*/
/******************************************************************************/
void C_ObjectManager::Free_All_Inst()
{
	//	Traverse the object instance vector and delete all object instance
	for(auto itr = m_obj_inst_list.begin(); itr < m_obj_inst_list.end(); ++itr)
		delete(*itr);

	ObjectInstVector temp;
	m_obj_inst_list.swap(temp);
}

/******************************************************************************/
/*!
	This function returns the pointer to the game object list.
*/
/******************************************************************************/
std::vector<object::C_GameObject *> *C_ObjectManager::Get_Obj_List()
{
	return &m_obj_list;
}

/******************************************************************************/
/*!
	This function returns the pointer to the game object instance list.
*/
/******************************************************************************/
std::vector<object::C_GameObject *> *C_ObjectManager::Get_Inst_List()
{
	return &m_obj_inst_list;
}

/******************************************************************************/
/*!
	This function returns the pointer to the game object by searching for it in
	the object vector based on the object's name.
*/
/******************************************************************************/
C_GameObject *C_ObjectManager::Get_Obj_By_Name(std::string name)
{
	/*
		Traverse the object vector and search for the object with given name and
		return a pointer to it.
	*/
	for(auto itr = m_obj_list.begin(); itr != m_obj_list.end(); ++itr)
	{
		if((*itr)->Get_Name() == name)
			return *itr;
	}

	return nullptr;
}

/******************************************************************************/
/*!
	This function returns the pointer to a game object instance by searching for
	it in the object instance vector based on the object instance's name. Return
	nullptr if it doesn't exist in the object instance vector.
*/
/******************************************************************************/
C_GameObject *C_ObjectManager::Get_Inst_By_Name(std::string name)
{
	/*
		Traverse the object instance vector and search for the object instance
		with given name and return a pointer to it.
	*/
	for(auto itr = m_obj_inst_list.begin(); itr != m_obj_inst_list.end(); ++itr)
	{
		if((*itr)->Get_Name() == name)
			return *itr;
	}

	return nullptr;
}

/******************************************************************************/
/*!
	This function returns the pointer to the first active game object instance
	with given name. Return nullptr if the object instance does not exist.
*/
/******************************************************************************/
C_GameObject *C_ObjectManager::Get_Active_Inst_By_Name(std::string name)
{
	/*
		Traverse the object instance vector and search for the object instance
		with given name and return a pointer to it if it's active
	*/
	for(auto itr = m_obj_inst_list.begin(); itr != m_obj_inst_list.end(); ++itr)
	{
		if((*itr)->Get_Name() == name)
			if((*itr)->Get_Active())
				return *itr;
	}

	return nullptr;
}
} // namespace object