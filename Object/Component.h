/******************************************************************************/
/*!
\file_name        Component.h
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the definition of the Component class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/
#pragma once
#include "../Defines/ComponentList.h"

namespace object
{

// Forward declaration of the GameObject to store a pointer to its owner
class C_GameObject;

/******************************************************************************/
/*!
  The component base class
 */
/******************************************************************************/
class C_Component
{
protected:
  // The type of the component e.g TRANSFORM
  COMPONENTTYPE m_type;
  // p_obj is a POINTER TO AN INCOMPLETE TYPE!
  C_GameObject *p_obj;

public:
  // Conversion constructor that takes in a COMPONENTTYPE and Pointer to object
  C_Component(C_GameObject* obj, COMPONENTTYPE type = CUSTOM);
  // Virtual destructor to ensure proper destructor calls for derived classes
  virtual ~C_Component() = default;
  
  virtual COMPONENTTYPE Get_Type() const;
  virtual C_GameObject *Get_Obj () const;
  virtual void Set_Obj          (C_GameObject *obj);
  virtual void Update           () {};
  
  // Pure virtual function that declares C_Component as an abstract base class
  virtual C_Component *Clone () const = 0;
  virtual C_Component *Actual()       = 0;
};
}