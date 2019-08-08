/******************************************************************************/
/*!
\file_name		ObjectManager.h
\project_name	Double Tap
\primary_author	Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the declarations of the Object Manager class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "GameObject.h" // Object class

namespace object
{
class C_ObjectManager
{
	using ObjectVector = std::vector<object::C_GameObject *>;
	using ObjectInstVector = std::vector<object::C_GameObject *>;

	// Vector that holds all unique object in this level
	ObjectVector m_obj_list;

	// Vector that holds all object instances
	ObjectInstVector m_obj_inst_list;

public:
	// Destructor of the Object Manager
	~C_ObjectManager();

	// Insert a unique object in the object vector
	C_GameObject *Push_Obj(std::string name, TRAIT trait);

	// Insert an object instance in the object instance vector
	C_GameObject *Push_Obj_Inst(std::string name);

	// Destroy an object instance
	void Destroy_Inst(C_GameObject *obj);

	// Destroy a unique object
	void Destroy(C_GameObject *obj);

	// Destroys all unique object
	void Unload_All_Object();

	// Destroys all object instances
	void Free_All_Inst();

	// Getters for object list and object instances list
	ObjectVector *Get_Obj_List();
	ObjectInstVector *Get_Inst_List();

	// Getters for specific object
	C_GameObject *Get_Obj_By_Name(std::string name);
	C_GameObject *Get_Inst_By_Name(std::string name);
	C_GameObject *Get_Active_Inst_By_Name(std::string name);
};
} // namespace object