/******************************************************************************/
/*!
\file_name        Bullet.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the declaration for the class C_Bullet

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"
#include "../Object/GameObject.h"
#include "../Defines/AllUtilities.h"
#include "../Types/Any.h"
#include "./AIBloater.h"
#include "./AIScreamer.h"


namespace object
{
class C_GameObject;

/******************************************************************************/
/*!
  Class for Component for Bullet
*/
/******************************************************************************/
class C_Bullet : public C_Component
{
    
public:
  C_Bullet(C_GameObject *p_obj);
  void CollisionStarted(object::C_GameObject* p_otherobject);
  void Connect();
  virtual C_Bullet *Clone() const override;
  virtual void Update() override;
  virtual C_Bullet *Actual() override;
  virtual void Reset();
};
}