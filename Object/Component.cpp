/******************************************************************************/
/*!
\file_name        Component.cpp
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the member function definition of the Component class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/
#include "Component.h"

namespace object
{
/******************************************************************************/
/*!
  The non default constructor of the component object 
 */
/******************************************************************************/
C_Component::C_Component(C_GameObject * obj, COMPONENTTYPE type)
:  p_obj{obj}, m_type{type}
{
}

/******************************************************************************/
/*!
  Returns the type of the component
 */
/******************************************************************************/
COMPONENTTYPE C_Component::Get_Type() const
{
  return m_type;
}

/******************************************************************************/
/*!
  Returns the pointer to the object
 */
/******************************************************************************/
C_GameObject * C_Component::Get_Obj() const
{
  return p_obj;
}

/******************************************************************************/
/*!
  Sets the pointer to the object
 */
/******************************************************************************/
void C_Component::Set_Obj(C_GameObject * obj)
{
  p_obj = obj;
}
}