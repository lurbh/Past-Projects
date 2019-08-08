/******************************************************************************/
/*!
\file_name      Transform.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the definitions of the Transform component class. This
	class contains all transformations variables of the object.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "Transform.h"

namespace object
{
/******************************************************************************/
/*!
	Non-default constructor. This constructs a Transform component.
*/
/******************************************************************************/
C_Transform::C_Transform(C_GameObject *obj)
	: C_Component{ obj, TRANSFORM }, m_transform{}, m_size{ 1.0f, 1.0f }, m_dir{ 0 }
{

}

/******************************************************************************/
/*!
	The update function for this component.
*/
/******************************************************************************/
void C_Transform::Update()
{
}

/******************************************************************************/
/*!
	This function returns a pointer to the transform matrix.
*/
/******************************************************************************/
math::Matrix3 *C_Transform::Get_Transform()
{
	return &m_transform;
}

/******************************************************************************/
/*!
This function returns the transform matrix.
*/
/******************************************************************************/
math::Matrix3 C_Transform::Get_Matrix() const
{
	return m_transform;
}

/******************************************************************************/
/*!
	This function returns the AE version of transform matrix.
*/
/******************************************************************************/
AEMtx33 C_Transform::Get_AEMatrix() const
{
	return m_AEtransform;
}

/******************************************************************************/
/*!
	This function returns the position vector of the object.
*/
/******************************************************************************/
math::Vec2 C_Transform::Get_Position() const
{
	math::Vec2 position;

	position.x = m_transform.m_matrix[0][2] / TILESCALE;
	position.y = m_transform.m_matrix[1][2] / TILESCALE;

	return position;
}

/******************************************************************************/
/*!
	This function returns the size vector of the object.
*/
/******************************************************************************/
math::Vec2 C_Transform::Get_Size() const
{
	return m_size;
}

/******************************************************************************/
/*!
	This function returns the direction of the object.
*/
/******************************************************************************/
float C_Transform::Get_Dir() const
{
	return m_dir;
}

/******************************************************************************/
/*!
	This function sets the x position of the object.
*/
/******************************************************************************/
void C_Transform::Set_PositionX(float x, float offset)
{
	m_transform.m_matrix[0][2] =
		static_cast<int>(x) * TILESCALE + TILESCALE / 2.0f - offset;
}

/******************************************************************************/
/*!
	This function sets the y position of the object.
*/
/******************************************************************************/
void C_Transform::Set_PositionY(float y, float offset)
{
	m_transform.m_matrix[1][2] =
		static_cast<float>(static_cast<int>(y)) * TILESCALE + TILESCALE / 2.0f -
		offset * TILESCALE;
}

/******************************************************************************/
/*!
	This function sets the tile map position of the object.
*/
/******************************************************************************/
void C_Transform::Set_Position(float x, float y)
{
	m_transform.m_matrix[0][2] = x * TILESCALE + TILESCALE / 2.0f;
	m_transform.m_matrix[1][2] = y * TILESCALE + TILESCALE / 2.0f;
}

/******************************************************************************/
/*!
	This function sets the global position of the object.
*/
/******************************************************************************/
void C_Transform::Set_Position_Global(float x, float y)
{
	m_transform.m_matrix[0][2] = x;
	m_transform.m_matrix[1][2] = y;
}

/******************************************************************************/
/*!
	This function sets the size of the object.
*/
/******************************************************************************/
void C_Transform::Set_Size(const math::Vec2 & rhs)
{
	m_size = rhs;
}

/******************************************************************************/
/*!
	This function sets the size of the object.
*/
/******************************************************************************/
void C_Transform::Set_Size(float x, float y)
{
	m_size = math::Vec2{ x, y };
}

/******************************************************************************/
/*!
	This function sets the direction of the object.
*/
/******************************************************************************/
void C_Transform::Set_Dir(float angle)
{
	m_dir = angle;
}

/******************************************************************************/
/*!
	This function translate the object by passing in a vector.
*/
/******************************************************************************/
void C_Transform::Translate(const math::Vec2 &rhs)
{
	m_transform.Translate(rhs);
}

/******************************************************************************/
/*!
	This function translate the object by passing in a x and y position.
*/
/******************************************************************************/
void C_Transform::Translate(float x, float y)
{
	m_transform.Translate(x, y);
}

/******************************************************************************/
/*!
	This function scale the object by passing in a vector.
*/
/******************************************************************************/
void C_Transform::Scale(const math::Vec2 &rhs)
{
	m_size.x *= rhs.x;
	m_size.y *= rhs.y;

	m_transform.Scale(rhs);
}

/******************************************************************************/
/*!
	This function scale the object by passing in a x and y scalar value.
*/
/******************************************************************************/
void C_Transform::Scale(float x, float y)
{
	m_size.x = x;
	m_size.y = y;

	m_transform.Scale(x, y);
}

/******************************************************************************/
/*!
	This function rotate the object.
*/
/******************************************************************************/
void C_Transform::Rotate(float angle)
{
	Add_Dir(angle);

	m_transform.Rotate(angle);
}

/******************************************************************************/
/*!
	This function adds direction.
*/
/******************************************************************************/
void C_Transform::Add_Dir(float angle)
{
	m_dir += angle;
}

/******************************************************************************/
/*!
	This function returns a pointer to the actual component.
*/
/******************************************************************************/
C_Transform * C_Transform::Actual()
{
	return this;
}

/******************************************************************************/
/*!
	This function returns a pointer to the clone of this component
*/
/******************************************************************************/
C_Transform * C_Transform::Clone() const
{
	C_Transform *p_clone = new C_Transform{ p_obj };

	p_clone->m_transform = m_transform;
	p_clone->m_size = m_size;
	p_clone->m_dir = m_dir;

	return p_clone;
}
} // namespace object