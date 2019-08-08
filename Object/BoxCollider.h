/******************************************************************************/
/*!
\file_name        BoxCollider.h
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the definition of the BoxCollider class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/
#pragma once

#include "Component.h"
#include "../Defines/AllMath.h"
#include "../Defines/CollisionSide.h"
#include "../Defines/AllUtilities.h"

namespace object
{
/******************************************************************************/
/*!
  The BoxCollider class definition
 */
/******************************************************************************/
  class C_BoxCollider final : public C_Component
  {
    math::Vec2 m_min;
    math::Vec2 m_max;
    math::Vec2 m_size;
    math::Vec2 m_offset;
    bool       m_active;
    bool       m_grounded;
    bool       m_ghost;
    char       m_flag;
  
  public:
    // Constructors
    C_BoxCollider(C_GameObject *p_obj);
    C_BoxCollider(C_GameObject *p_obj, math::Vec2 min, math::Vec2 max, 
                  math::Vec2 size, math::Vec2 offset = math::Vec2{ 0.0f, 0.0f }, 
                  bool ghost = false);
    
    // Setter functions
    void Reset_Flag  ();
    void Set_Min     (math::Vec2 min);
    void Set_Min     (float x, float y);
    void Set_MinY    (float y);
    void Set_Max     (math::Vec2 max);
    void Set_Max     (float x, float y);
    void Set_MaxY    (float y);
    void Set_Size    (math::Vec2 size);
    void Set_Size    (float x, float y);
    void Set_Flag    (unsigned side);
    void Set_Ghost   (bool ghost);
    void Set_Grounded(bool grounded);
    void Set_Active  (bool active);
    void Set_Offset  (float x, float y);
    
    // Getter functions
    math::Vec2 Get_Offset  () const;
    math::Vec2 Get_Min     () const;
    math::Vec2 Get_Max     () const;
    math::Vec2 Get_Size    () const;
    char       Get_Flag    () const;
    bool       Is_Active   () const;
    bool       Get_Grounded() const;
    bool       Get_Ghost   () const;
    
    // Virtual functions
    virtual C_BoxCollider* Clone () const override;
    virtual C_BoxCollider* Actual() override;
  };
}