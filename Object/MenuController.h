/******************************************************************************/
/*!
\file_name      MenuController.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the declarations of the Menu Controller component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"  // EventDispatcher class
#include "../Object/GameObject.h"       // GameObject class

namespace object
{
// Types of menu
enum MENUMODE
{
	PAUSEMENU,    // Pause Menu controls
	OPTIONMENU,   // Options Menu controls
	HOWTOPLAYMENU,// How To Play Menu controls
	WINMENU       // Win Menu controls
};

class C_MenuController : public C_Component
{
	bool m_esc_close = true;    // Boolean for pressing "ESCAPE" to close
	bool m_pause = false;       // Boolean to pause the menu itself
	int m_selection = 0;        // Selection for buttons on the menu
	int m_max_selection = 0;    // Max selection a menu can have
	std::string m_close = "";   // Holds the close menu event's string
	std::string m_refresh = ""; // Holds the refresh menu event's string
	std::string m_execute = ""; // Holds the execute menu event's string

	MENUMODE m_mode = PAUSEMENU;// Type of menu controls the object use

	void PauseMenu();           // Pause Menu controls
	void OptionsMenu();         // Options Menu controls
	void HowToPlayMenu();       // How To Play Menu controls
	void WinMenu();             // Win Menu controls

public:
	// Non-default constructor
	C_MenuController(C_GameObject *p_obj);

	// Connects all events
	void Connect();

	// Update function for MenuController component
	void Update() override;

	// Getter functions
	inline int Get_Selection() const { return m_selection; }

	// Setter functions
	inline void Set_Mode(MENUMODE mode) { m_mode = mode; }
	inline void Set_Close(std::string event_name) { m_close = event_name; }
	inline void Set_Refresh(std::string event_name) { m_refresh = event_name; }
	inline void Set_Execute(std::string event_name) { m_execute = event_name; }
	inline void Set_Selection(int num) { m_selection = num; }
	inline void Set_Max_Selection(int num) { m_max_selection = num; }
	inline void Set_Pause(bool pause) { m_pause = pause; }
	inline void Set_Esc_Close(bool close) { m_esc_close = close; }

	// Virtual functions for cloning MenuController component
	C_MenuController *Actual() override;
	C_MenuController *Clone() const override;

};
}