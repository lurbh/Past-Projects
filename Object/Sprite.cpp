/******************************************************************************/
/*!
\file_name		Sprite.cpp
\project_name	Double Tap
\primary_author	Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the definitions of the Sprite component class. This
	class manages the sprites of the game object. By animating and drawing
	the textures of the object. It also manipulates all graphical properties
	of a texture (e.g. transparencies, tints, colors).

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "Sprite.h"

namespace object
{
/******************************************************************************/
/*!
	Non-default constructor. Construct a sprite component by passing in a
	pointer to its owner.
*/
/******************************************************************************/
C_Sprite::C_Sprite(C_GameObject *p_obj)
	: C_Component{ p_obj, SPRITE }, mp_texture{ nullptr }, mp_mesh{ nullptr },
	m_elapsed{ 0.0 }, m_FlipX{ false }, m_FlipY{ false }, m_animate{ true },
	m_CurrFrame{ 0 }, m_Opacity{ 1.0f }, m_tint{}, m_argb{}
{
}

/******************************************************************************/
/*!
	Destructor. Destruct the sprite component freeing the allocated memory in
	the texture container.
*/
/******************************************************************************/
C_Sprite::~C_Sprite()
{
	std::vector<graphics::Texture*> copy;
	copy.swap(m_texture_list);
}

/******************************************************************************/
/*!
	The update function of the sprite component. Animate and draw the texture.
*/
/******************************************************************************/
void C_Sprite::Update()
{
	Animate();
	Draw();
}

/******************************************************************************/
/*!
	This function changes the texture to draw creating an animating effect.
*/
/******************************************************************************/
void C_Sprite::Animate()
{
	// If there's a texture
	if(mp_texture)
	{
		// Game is not paused and animate boolean is true
		if(!utilities::C_OptionsManager::Get_Pause() && m_animate)
		{
			m_elapsed += utilities::C_Timer::Get_dt();

			// Check if the current frame elapsed has pass the animation fps
			if(m_elapsed >= 1.0 / mp_texture->m_fps)
			{
				// Change frame
				++m_CurrFrame;

				if(m_CurrFrame >= mp_texture->m_num_frames)
					m_CurrFrame = 0;

				m_elapsed = 0.0;
			}
		}

		// Set the texture based on the current frame number
		AEGfxTextureSet(mp_texture->mp_texture, mp_texture->m_uv[m_CurrFrame],
			0.0f);
	}
}

/******************************************************************************/
/*!
	This function draw the mesh onto the screen.
*/
/******************************************************************************/
void C_Sprite::Draw()
{
	AEGfxSetTintColor(m_tint.r, m_tint.g, m_tint.b, m_tint.a);
	AEGfxSetTransparency(m_Opacity);
	AEGfxMeshDraw(mp_mesh, AE_GFX_MDM_TRIANGLES);
}

/******************************************************************************/
/*!
	This function creates the mesh of the object.
*/
/******************************************************************************/
void C_Sprite::CreateMesh()
{
	float u = mp_texture ? mp_texture->m_clip_size : 1.0f;

	AEGfxMeshStart();

	AEGfxTriAdd(-0.5f,  0.5f, m_argb.color, 0.0f, 0.0f,
				 0.5f, -0.5f, m_argb.color, u   , 1.0f,
				-0.5f, -0.5f, m_argb.color, 0.0f, 1.0f);
	AEGfxTriAdd(-0.5f,  0.5f, m_argb.color, 0.0f, 0.0f,
				 0.5f, -0.5f, m_argb.color, u   , 1.0f,
				 0.5f,  0.5f, m_argb.color, u   , 0.0f);

	mp_mesh = AEGfxMeshEnd();
}

/******************************************************************************/
/*!
This function frees the mesh of the object.
*/
/******************************************************************************/
void C_Sprite::Free_Mesh()
{
	AEGfxMeshFree(mp_mesh);
}

/******************************************************************************/
/*!
This function insert the texture that the sprite component will be using.
*/
/******************************************************************************/
void C_Sprite::Add_Texture(graphics::Texture *texture)
{
	m_texture_list.push_back(texture);
}

/******************************************************************************/
/*!
This function sets the texture that the sprite will be using by searching
for the name of the texture in its texture container.
*/
/******************************************************************************/
void C_Sprite::Set_Texture(std::string name)
{
	for(auto it = m_texture_list.begin(); it != m_texture_list.end(); ++it)
	{
		if((*it)->m_name == name)
			mp_texture = *it;
	}
}

/******************************************************************************/
/*!
This function return the pointer to the actual sprite component object.
*/
/******************************************************************************/
C_Sprite *C_Sprite::Actual()
{
	return this;
}

/******************************************************************************/
/*!
The clone function of the sprite component class.
*/
/******************************************************************************/
C_Sprite *C_Sprite::Clone() const
{
	C_Sprite *p_clone = new C_Sprite(p_obj);

	for(auto it = m_texture_list.begin(); it != m_texture_list.end(); ++it)
	{
		p_clone->m_texture_list.push_back(*it);
	}

	p_clone->mp_texture = mp_texture;

	p_clone->mp_mesh = mp_mesh;

	p_clone->m_animate = m_animate;

	return p_clone;
}
}	// namespace object