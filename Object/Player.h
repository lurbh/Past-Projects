/******************************************************************************/
/*!
\file_name        Player.h
\project_name     Double Tap
\primary_author   Ma Ming Shun, mingshun.ma,
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
#include "AIScreamer.h"
#include "../Actions/ActionsDispatcher.h"


namespace object
{
  class C_GameObject;

/******************************************************************************/
/*!
Class for Component for Player
*/
/******************************************************************************/
  class C_Player : public C_Component
  {
  public:
    enum Weapon { PISTOL, MACHINEGUN, SHOTGUN };
    enum FIREDIRECTION { NORMAL, UP, DOWN };
  private:
    int m_ammo;
    int m_health;
    int m_life;
    int m_machinefire;
    double m_fire_rate;
    Weapon m_weapon_type;
    FIREDIRECTION m_firedirection;
    bool m_keyactive;
    bool m_moving;
    bool m_jumping;
    bool m_lowlife;
    bool m_invulnerable;
    bool m_hit;
    bool m_shooting;
    double m_hitanimation;
    double m_invulnerabletime;
    double m_lowlifetime;
    double m_shootanimation;
    math::Vec2 m_checkpointpos;
    void ResetPos();
  public:
    C_Player(C_GameObject *p_obj);
    void Connect();
    bool GetLowLife()const;
    void CollisionStarted(object::C_GameObject* p_otherobject);
    //C_GameObject *mp_checkpoint;
    void Shoot();
    void ShootUp();
    void ShootDown();
    void PistolShoot();
    void MachineShoot();
    void ShotShoot();
    void PistolShootUp();
    void MachineShootUp();
    void ShotShootUp();
    void PistolShootDown();
    void MachineShootDown();
    void ShotShootDown();
    Weapon Get_Weapon() const;
    void Set_Weapon(Weapon weap);
    void Set_KeyActive(bool key);
    void Set_CheckpointPos(math::Vec2 pos);
    void Set_ShootAnimation(double time);
    void Set_Shoot(bool shoot);
    bool Get_Shoot() const;
    void Set_Moving(bool move);
    bool Get_Moving() const;
    void Set_Jumping(bool jump);
    bool Get_Jumping() const;
    inline int Get_Life() const { return m_life; }
    int Get_Health() const;
    int Get_Ammo() const;
    bool Get_Invulnerable() const;

    virtual C_Player *Clone() const override;
    virtual void Update() override;
    virtual C_Player *Actual() override;
  };
}