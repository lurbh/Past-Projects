/******************************************************************************/
/*!
\file_name      SpriteText.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains definitions of the Sprite Text component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "SpriteText.h"

namespace object
{
/******************************************************************************/
/*!
Non-default constructor. This constructs the Sprite Text component.
*/
/******************************************************************************/
C_SpriteText::C_SpriteText(C_GameObject *p_obj)
	: C_Component{ p_obj, SPRITETEXT }, m_font_id{}, m_buffer{ "" }, m_color{}
{
}

/******************************************************************************/
/*!
The update function of sprite text component
*/
/******************************************************************************/
void C_SpriteText::Update()
{
}

/******************************************************************************/
/*!
The function destroys the AE Font.
*/
/******************************************************************************/
void C_SpriteText::Destroy_Font()
{
	AEGfxDestroyFont(m_font_id);
}

/******************************************************************************/
/*!
This function returns a pointer to the actual component.
*/
/******************************************************************************/
C_SpriteText *C_SpriteText::Actual()
{
	return this;
}

/******************************************************************************/
/*!
This function clones a pointer to this component.
*/
/******************************************************************************/
C_SpriteText *C_SpriteText::Clone() const
{
	C_SpriteText *p_clone = new C_SpriteText(p_obj);

	p_clone->m_font_id = m_font_id;

	p_clone->m_buffer = m_buffer;

	p_clone->m_color = m_color;

	return p_clone;
}
} // namespace object