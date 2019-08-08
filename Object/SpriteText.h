/******************************************************************************/
/*!
\file_name      SpriteTest.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains declarations of the Sprite Text component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "Component.h"                // Component base class
#include "../Defines/AllUtilities.h"  // AE Font functions

namespace object
{
class C_SpriteText final : public C_Component
{
	// Color struct for Sprite text
	struct Color
	{
		float r, g, b;

		Color() : r{ 0xFF }, g{ 0xFF }, b{ 0xFF } {}
	};

	u32 m_font_id;        // Fonts to use for sprite text
	std::string m_buffer; // Buffer that stores the text
	Color m_color;        // Color of the fonts

public:
	// Non-default constructor 
	C_SpriteText(C_GameObject *p_obj);

	// Update function
	void Update() override;

	// Destroys the font created by AE Font
	void Destroy_Font();

	// Getter functions
	inline unsigned int Get_Font() const { return m_font_id; };
	inline std::string Get_Buffer() const { return m_buffer; }
	inline Color Get_Color() const { return m_color; }

	// Setter fuunctions
	inline void Set_Font_Id(unsigned int id) { m_font_id = id; }
	inline void Set_Buffer(std::string buf) { m_buffer = buf; }
	inline void Set_Color(float r, float g, float b) { m_color.r = r; m_color.g = g; m_color.b = b; }

	// Virtual functions that clone the component
	C_SpriteText *Actual() override;
	C_SpriteText *Clone() const override;
};
}  // namespace object