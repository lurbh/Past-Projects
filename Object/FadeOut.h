/******************************************************************************/
/*!
\file_name      FadeOut.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
This file contains declarations of the Fade Out component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"  // EventDispatcher class
#include "../Object/GameObject.h"       // GameObject class
#include "../Defines/AllUtilities.h"    // Timer

namespace object
{
class C_FadeOut : public C_Component
{
	double m_wait_time;       // Wait time for change in fade effect
	float m_fade_out_speed;   // Fade out speed
	float m_fade_in_speed;    // Fade in speed

	C_Sprite *p_sprite;       // Sprite component of the object

	bool m_fade_out;          // Boolean when object is fading out
	bool m_fade_out_complete; // Boolean when fade out is complete
	bool m_fade_in;           // Boolean when object is fading in
	bool m_fade_in_complete;  // Boolean when fade in is complete

	bool m_fade_in_first;     // Boolean for choosing to fade in first

	void FadeInAndOut();      // Function that deals with fading in and out
	void FadeIn();            // Function that deals with fade in only
	void FadeOut();           // Function that deals with fade out only

public:
	// Non-default constructor
	C_FadeOut(C_GameObject *p_obj);

	// Connect all events
	void Connect();

	// Update function
	void Update() override;

	// Getter function
	inline bool Get_Fade_Out_Complete() { return m_fade_out_complete; }

	// Setter functions
	inline void Set_Wait_Time(double time) { m_wait_time = time; }
	inline void Set_Fade_Out_Speed(float spd) { m_fade_out_speed = spd; }
	inline void Set_Fade_In_Speed(float spd) { m_fade_in_speed = spd; }
	inline void Set_Fade_Out(bool active) { m_fade_out = active; }
	inline void Set_Fade_In(bool active) { m_fade_in = active; }
	inline void Set_Fade_In_First(bool active) { m_fade_in_first = active; }
	inline void Set_Fade_In_Complete(bool active) { m_fade_in_complete = active; }

	// Virtual function for cloning of component
	C_FadeOut *Actual() override;
	C_FadeOut *Clone() const override;
};
} // namespace object