/******************************************************************************/
/*!
\file_name      Transform.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the declarations of the Transform component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "AEEngine.h"         // AEMtx33
#include "Component.h"        // Component base class
#include "../Math/Matrix3.h"  // Matrix3 class
#include "../Math/Vec2.h"     // Vector2 class

namespace object
{
class C_Transform final : public C_Component
{
	union
	{
		// [3][3] matrix that stores rows by columns. 
		// [1][0] is the second row, first column.
		math::Matrix3 m_transform;
		AEMtx33 m_AEtransform;
	};

	// Contains the x and y scalars of the object
	math::Vec2 m_size;

	// Direction in degrees
	float m_dir;

public:
	// Non-default constructor
	C_Transform(C_GameObject *obj);

	// Update function of the transform component
	void Update() override;

	// Getter functions
	math::Matrix3 *Get_Transform();
	math::Matrix3 Get_Matrix() const;
	AEMtx33 Get_AEMatrix() const;
	math::Vec2 Get_Position() const;
	math::Vec2 Get_Size() const;
	float Get_Dir() const;

	// Setter functions
	void Set_PositionX(float x, float offset = 0.0f);
	void Set_PositionY(float y, float offset = 0.0f);
	void Set_Position(float x, float y);
	void Set_Position_Global(float x, float y);
	void Set_Size(const math::Vec2 &rhs);
	void Set_Size(float x, float y);
	void Set_Dir(float angle);

	// Translate object
	void Translate(const math::Vec2 &rhs);
	void Translate(float x, float y);

	// Scale object
	void Scale(const math::Vec2 &rhs);
	void Scale(float x, float y);

	// Rotate object
	void Rotate(float angle);

	// Add direction function
	void Add_Dir(float angle);

	// Virtual functions for cloning
	C_Transform *Actual() override;
	C_Transform *Clone() const override;
};
} // namespace object