/******************************************************************************/
/*!
\file_name		Sprite.h
\project_name	Double Tap
\primary_author	Koh Wen Lin, wenlin.koh, 390004216
\brief
This file contains the declarations of the Sprite component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once


#include <vector>	                // std::vector
#include "Component.h"				// Component base class
#include "../Graphics/Texture.h"	// Texture class
#include "../Defines/AllUtilities.h"// Timer and OptionsManager

namespace object
{
struct Tint	// Tint class for tinting object during draw
{
	float r, g, b, a;

	Tint() : r{ 1.0f }, g{ 1.0f }, b{ 1.0f }, a{ 1.0f } {}
};

union Color	// Color class for mesh creation
{
	unsigned char arr[4];
	unsigned int color;

	Color() : color{ 0xFFFFFFFF } {}
};

class C_Sprite final : public C_Component
{
	std::vector<graphics::Texture *> m_texture_list;// List of textures
	graphics::Texture *mp_texture;					// Current texture
	AEGfxVertexList *mp_mesh;						// Object's mesh
	double m_elapsed;								// Elapsed time per frame
	bool m_animate;									// Boolean to animate sprite

	GETSET(bool, FlipX)								// Boolean to flip X coord
	GETSET(bool, FlipY)								// Boolean to flip Y coord						
	GETSET(int, CurrFrame)							// Current frame
	GETSET(float, Opacity)							// Transparency value

	Tint m_tint;									// Tint for drawing object
	Color m_argb;									// Mesh color for object

public:
	// Non-default constructor
	C_Sprite(C_GameObject *p_obj);

	// Destructor
	~C_Sprite();

	// Virtual update function
	void Update() override;

	// Animate the texture
	void Animate();

	// Draw the texture
	void Draw();

	// Texture helper functions
	// Creates mesh for sprite component
	void CreateMesh();

	// Free mesh for sprite component
	void Free_Mesh();

	// Add Texture into sprite component
	void Add_Texture(graphics::Texture *texture);

	// Set current texture for sprite component
	void Set_Texture(std::string name);

	// Getter functions
	inline bool Get_Animate() const { return m_animate; }
	inline bool *Get_FlipPtr() { return &m_FlipX; }
	inline float *Get_Opacity_Ptr() { return &m_Opacity; }
	inline float Get_UV(unsigned index) { return mp_texture->m_uv[index]; }
	inline AEGfxVertexList *Get_Mesh() { return mp_mesh; }
	inline graphics::Texture *Get_Texture() { return mp_texture; }

	// Setter functions
	inline void Set_Animate(bool active) { m_animate = active, m_CurrFrame = 0; }

	inline void Set_Tint(float r, float g, float b, float a)
	{
		m_tint.r = r, m_tint.g = g, m_tint.b = b, m_tint.a = a;
	}

	inline void Set_RGB(float r, float g, float b)
	{
		m_argb.arr[2] = (u8)r, m_argb.arr[1] = (u8)g, m_argb.arr[0] = (u8)b;
	}

	// virtual clone functions
	virtual C_Sprite *Actual() override;
	virtual C_Sprite *Clone() const override;
};
}	// namespace object