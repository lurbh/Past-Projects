/******************************************************************************/
/*!
\file_name      FadeOut.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains declarations of the Fade Out component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "FadeOut.h"

/*
	This namespace contains all declarations of the event functions that this
	file will use
*/
namespace
{
	void OnLogicUpdate(object::C_GameObject* p_object);
} // Anonymous namespace

namespace object
{
/******************************************************************************/
/*!
	Non-default constructor for the Pipe Hazard component class. This constructs
	the pipe hazard component.
*/
/******************************************************************************/
C_FadeOut::C_FadeOut(C_GameObject *p_obj)
	: C_Component{ p_obj }, m_wait_time{ 0.0 }, m_fade_out_speed{ 0.0f },
	m_fade_in_speed{ 0.0f }, p_sprite{ nullptr }, m_fade_out{ false },
	m_fade_out_complete{ false }, m_fade_in{ false },
	m_fade_in_complete{ false }, m_fade_in_first{ false }
{
}

/******************************************************************************/
/*!
	Connects all event functions and initialise the object's variables that
	will be used for the pipe hazard behaviours.
*/
/******************************************************************************/
void C_FadeOut::Connect()
{
	// Connect event function
	events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);

	// Initialize sprite component
	p_sprite = static_cast<C_Sprite *>(p_obj->Find_Component(SPRITE));
}

/******************************************************************************/
/*!
	The update function of Fade Out component. This function is called every
	frame.
*/
/******************************************************************************/
void C_FadeOut::Update()
{
	FadeInAndOut();
}

/******************************************************************************/
/*!
	This function deals with fading in the object sprite and then fading it out
	again.
*/
/******************************************************************************/
void C_FadeOut::FadeInAndOut()
{
	// When fade in effect is not completed
	if(!m_fade_in_complete)
	{
		// Fade In
		FadeIn();
		return;
	}

	// When fade out effect is not completed
	if(!m_fade_out_complete)
		FadeOut();  // Fade out
}

/******************************************************************************/
/*!
	This function deals with fading in the object's sprite.
*/
/******************************************************************************/
void C_FadeOut::FadeIn()
{
	// Compute change in opacity value 
	float opacity = p_sprite->Get_Opacity() + m_fade_out_speed *
		static_cast<float>(utilities::C_Timer::Get_dt());

	// If value is fully opaque
	if(opacity >= 1.0f)
	{
		// Fade in is complete
		m_fade_in_complete = true;
		opacity = 1.0f;
	}

	// Set the new opacity to the sprite
	p_sprite->Set_Opacity(opacity);
}

/******************************************************************************/
/*!
	This function deals with fading out the object's sprite.
*/
/******************************************************************************/
void C_FadeOut::FadeOut()
{
	// Decrement the wait time before Fade out starts
	m_wait_time -= utilities::C_Timer::Get_dt();

	// Wait time is over
	if(m_wait_time <= 0.0)
	{
		// Compute change in opacity value
		float opacity = p_sprite->Get_Opacity() - m_fade_out_speed *
			static_cast<float>(utilities::C_Timer::Get_dt());

		// If value is fully transparent
		if(opacity <= 0.0f)
		{
			// Fade out is complete
			opacity = 0.0f;
			m_fade_out_complete = true;
		}

		// Set the new opacity to the sprite
		p_sprite->Set_Opacity(opacity);
	}
}

/******************************************************************************/
/*!
	This function returns a pointer to the actual component.
*/
/******************************************************************************/
C_FadeOut *C_FadeOut::Actual()
{
	return this;
}

/******************************************************************************/
/*!
	This function clones a pointer to this component.
*/
/******************************************************************************/
C_FadeOut *C_FadeOut::Clone() const
{
	return new C_FadeOut{ p_obj };
}
} // namespace object

/*
	This namespace contains all definitions of the event functions that this
	file will use
*/
namespace
{
/******************************************************************************/
/*!
	This is an event update function that calls the update function every frame.
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject* p_object)
{
	(static_cast<object::C_FadeOut*>(p_object->Find_Component(CUSTOM))->Update());
}
} // Anonymous namespace
