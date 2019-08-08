/******************************************************************************/
/*!
\file_name        WeaponPickUp.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the implementation for the class C_WeaponPickUp

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "WeaponPickUp.h"

// FORWARD DECLARE ALL FUNCTIONS THAT ARE GOING TO BE ADDED

namespace
{
	void OnCollisionStarted(events::C_CollisionEvent p_event);
}

namespace object
{
/******************************************************************************/
/*!
The Non-Default constructor for C_WeaponPickUp
*/
/******************************************************************************/
C_WeaponPickUp::C_WeaponPickUp(C_GameObject *p_obj)
	: C_Component{ p_obj }
{
}

/******************************************************************************/
/*!
	Function to Connect to events
*/
/******************************************************************************/
void C_WeaponPickUp::Connect()
{
	events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
}

/******************************************************************************/
/*!
	Function to Clone C_WeaponPickUp
*/
/******************************************************************************/
C_WeaponPickUp *C_WeaponPickUp::Clone() const
{
	return new C_WeaponPickUp{ p_obj };
}

/******************************************************************************/
/*!
	Update Function for C_WeaponPickUp
*/
/******************************************************************************/
void C_WeaponPickUp::Update()
{
}

/******************************************************************************/
/*!
	Function to Get C_WeaponPickUp
*/
/******************************************************************************/
C_WeaponPickUp *C_WeaponPickUp::Actual()
{
	return this;
}
}

//////////////////////// FUNCTIONS TO BE CONNECTED MUST BE GLOBAL FUNCTIONS //////////////////////////////////////

namespace
{
/******************************************************************************/
/*!
	Collision Function for C_WeaponPickUp
*/
/******************************************************************************/
void OnCollisionStarted(events::C_CollisionEvent p_event)
{
	// Destroys particle effect and pickup upon collision with the player
	if (p_event.Other_Object()->Get_Name() == "Player")
	{
		p_event.Object()->Destroy();
		static_cast<object::C_WeaponPickUp *>(p_event.Object()->Find_Component(CUSTOM))->mp_aura->Destroy();
	}
}
}
