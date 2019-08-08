/******************************************************************************/
/*!
\file_name        WeaponPickUp.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the declaration for the class C_WeaponPickUp

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"
#include "../Object/GameObject.h"
#include "../Defines/AllUtilities.h"
#include "../Types/Any.h"

namespace object
{
class C_WeaponPickUp : public C_Component
{

public:
	C_GameObject *mp_aura; // pointer to Particle system
	
	C_WeaponPickUp(C_GameObject *p_obj);
	void Connect();

	inline void Set_Aura(C_GameObject *p_aura) { mp_aura = p_aura; }

	virtual C_WeaponPickUp *Clone() const override;
	virtual void Update() override;
	virtual C_WeaponPickUp *Actual() override;
};
}