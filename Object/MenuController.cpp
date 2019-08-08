/******************************************************************************/
/*!
\file_name      MenuController.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the definitions of the Menu Controller component class.
	This class allows object to take in behaviour of menu, allowing different
	version of controls for different types of menu.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "MenuController.h"

/*
	This namespace contains all declarations of the event functions that this
	file will use
*/
namespace
{
void OnLogicUpdate(object::C_GameObject* p_object);
}

namespace object
{
/******************************************************************************/
/*!
	Non-default constructor. This constructs a MenuController component.
*/
/******************************************************************************/
C_MenuController::C_MenuController(C_GameObject *p_obj)
	: C_Component{ p_obj }
{
}

/******************************************************************************/
/*!
	This function connects all event functions that this component will be using.
*/
/******************************************************************************/
void C_MenuController::Connect()
{
	events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
}

/******************************************************************************/
/*!
	The update function for this component. This function will call different
	function depending on the menu type.
*/
/******************************************************************************/
void C_MenuController::Update()
{
	switch(m_mode)
	{
	case PAUSEMENU:
		PauseMenu();
		break;
	case OPTIONMENU:
		OptionsMenu();
		break;
	case HOWTOPLAYMENU:
		HowToPlayMenu();
		break;
	case WINMENU:
		WinMenu();
		break;
	}
}

/******************************************************************************/
/*!
	The function holds the update call for a Pause Menu.
*/
/******************************************************************************/
void C_MenuController::PauseMenu()
{
	// If the menu is not paused
	if(!m_pause)
	{
		// Escape to close menu
		if(AEInputCheckTriggered(AEVK_ESCAPE) && m_esc_close)
		{
			m_selection = 0;
			events::C_EventDispatcher::DispatchEvent(m_close);
		}

		// Up and down to select buttons
		if(AEInputCheckTriggered(AEVK_UP))
		{
			m_selection = --m_selection > 0 ? m_selection : 0;
			events::C_EventDispatcher::DispatchEvent(m_refresh);
		}
		else if(AEInputCheckTriggered(AEVK_DOWN))
		{
			m_selection = ++m_selection < m_max_selection ? m_selection
				: m_max_selection - 1;
			events::C_EventDispatcher::DispatchEvent(m_refresh);
		}

		// Pressing enter will execute the selected button functions
		if(AEInputCheckTriggered(AEVK_RETURN))
		{
			events::C_EventDispatcher::DispatchEvent(m_execute);
		}
	}
}

/******************************************************************************/
/*!
	The function holds the update call for a Options Menu.
*/
/******************************************************************************/
void C_MenuController::OptionsMenu()
{
	// Up and down to select buttons
	if(AEInputCheckTriggered(AEVK_UP))
	{
		m_selection = --m_selection > 0 ? m_selection : 0;
		events::C_EventDispatcher::DispatchEvent(m_refresh);
	}
	else if(AEInputCheckTriggered(AEVK_DOWN))
	{
		m_selection = ++m_selection < m_max_selection ? m_selection
			: m_max_selection - 1;
		events::C_EventDispatcher::DispatchEvent(m_refresh);
	}

	// Pressing enter will execute the selected button functions
	if(AEInputCheckTriggered(AEVK_RETURN))
	{
		events::C_EventDispatcher::DispatchEvent(m_execute);
	}
}

/******************************************************************************/
/*!
	The function holds the update call for a How To Play Menu.
*/
/******************************************************************************/
void C_MenuController::HowToPlayMenu()
{
	// Press escape to close the menu
	if(AEInputCheckTriggered(AEVK_ESCAPE) && m_esc_close)
	{
		m_selection = 0;
		events::C_EventDispatcher::DispatchEvent(m_close);
	}
}

/******************************************************************************/
/*!
	The function holds the update call for a Win Menu.
*/
/******************************************************************************/
void C_MenuController::WinMenu()
{
	// Press enter to close the menu
	if(AEInputCheckTriggered(AEVK_RETURN) && !m_esc_close)
	{
		m_selection = 0;
		events::C_EventDispatcher::DispatchEvent(m_close);
	}
}

/******************************************************************************/
/*!
	This function returns a pointer to the actual component.
*/
/******************************************************************************/
C_MenuController *C_MenuController::Actual()
{
	return this;
}

/******************************************************************************/
/*!
	This function returns a pointer to the clone of this component
*/
/******************************************************************************/
C_MenuController *C_MenuController::Clone() const
{
	return new C_MenuController{ p_obj };
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
	This is an event update function that calls the update function every frame.
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject* p_object)
{
	static_cast<object::C_MenuController*>(p_object->
		Find_Component(CUSTOM))->Update();
}
}  // Anonymous namespace
