/******************************************************************************/
/*!
\file_name        ShotgunBullet.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the declaration for the class C_ShotgunBullet

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once
#include "Bullet.h"

namespace object
{
class C_ShotgunBullet final : public C_Bullet
{
  double m_bullettime;
  double m_bulletmaxtime = 0.1;

public:
  C_ShotgunBullet(C_GameObject* p_obj);
  void Connect();
  virtual C_ShotgunBullet *Clone() const override;
  virtual void Update() override;
  void Reset();
  virtual C_ShotgunBullet *Actual() override;
};
}