/******************************************************************************/
/*!
\file_name      DoorMenuEffect.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
This file contains the definitions of the Game Object class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "DoorMenuEffect.h"

/*
This namespace contains all declarations of the event functions that this
file will use
*/
namespace
{
	void OnCollisionStarted(events::C_CollisionEvent p_event);
	void OnLogicUpdate(object::C_GameObject *p_object);
} //  Anonymous namespace

namespace object
{
/******************************************************************************/
/*!
	Non-default constructor. This constructs a Door Menu Effect component.
*/
/******************************************************************************/
C_DoorMenuEffect::C_DoorMenuEffect(C_GameObject *p_obj)
	: C_Component{ p_obj }, m_is_glow{ false }
{
}

/******************************************************************************/
/*!
	This function connects all events and initialize the core component that will
	be used.
*/
/******************************************************************************/
void C_DoorMenuEffect::Connect()
{
	events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
	events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
	mp_transform = static_cast<C_Transform*>(p_obj->Find_Component(TRANSFORM));
}

/******************************************************************************/
/*!
	This function update the component every frame
*/
/******************************************************************************/
void C_DoorMenuEffect::Update()
{
	m_elapsed -= utilities::C_Timer::Get_dt();
	if(m_elapsed <= 0.0)
		Normal();
}

/******************************************************************************/
/*!
	The function deactivates the door's effect.
*/
/******************************************************************************/
void C_DoorMenuEffect::Normal()
{
	if(m_is_glow)
	{
		static_cast<C_Sprite*>(p_obj->Find_Component(SPRITE))->
			Set_Texture("DoorClose");
		mp_sprite->Set_Texture(m_normal);
		events::C_EventDispatcher::DispatchEvent("DeactivateDoorParticle");
		m_is_glow = false;
	}
}

/******************************************************************************/
/*!
	The function activates the door's effect.
*/
/******************************************************************************/
void C_DoorMenuEffect::Glow()
{
	if(!m_is_glow)
	{
		static_cast<C_Sprite*>(p_obj->Find_Component(SPRITE))->Set_Texture("DoorOpen");
		mp_sprite->Set_Texture(m_glow);

		mp_particlesys_transform->Set_Position(mp_transform->Get_Position().x - 1.0f,
			mp_transform->Get_Position().y - 0.7f * mp_transform->Get_Size().y);

		mp_enter_key_transform->Set_Position(mp_transform->Get_Position().x - 0.2f * mp_transform->Get_Size().x,
			mp_transform->Get_Position().y - 0.9f * mp_transform->Get_Size().y);

		events::C_EventDispatcher::DispatchEvent("ActivateDoorParticle");
		m_is_glow = true;
	}
}

/******************************************************************************/
/*!
	This function returns a pointer to the clone of this component
*/
/******************************************************************************/
C_DoorMenuEffect *C_DoorMenuEffect::Actual()
{
	return this;
}

/******************************************************************************/
/*!
	This function returns a pointer to the clone of this component
*/
/******************************************************************************/
C_DoorMenuEffect *C_DoorMenuEffect::Clone() const
{
	return new C_DoorMenuEffect{ p_obj };
}
} // namespace object

/*
	This namespace contains all declarations of the event functions that this
	file will use
*/
namespace
{
/******************************************************************************/
/*!
	This is an event function that allows the object to detect objects that
	collided with this object and allows the object to perform collision events.
*/
/******************************************************************************/
void OnCollisionStarted(events::C_CollisionEvent p_event)
{
	object::C_DoorMenuEffect *p_door = static_cast<object::C_DoorMenuEffect *>(p_event.Object()->Find_Component(CUSTOM));

	p_door->Set_Elapsed(0.3);

	if(p_event.Other_Object()->Get_Name() == "Player")
		p_door->Glow();

	if(AEInputCheckTriggered(AEVK_RETURN))
		events::C_EventDispatcher::DispatchEvent(p_door->Get_Next_Level());
}

/******************************************************************************/
/*!
	This is an event update function that calls the update function every frame.
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject *p_object)
{
	(static_cast<object::C_DoorMenuEffect*>(p_object->Find_Component(CUSTOM))->Update());
}
} // Anonymous namespace
