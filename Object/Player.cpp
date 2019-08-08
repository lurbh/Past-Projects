/******************************************************************************/
/*!
\file_name        Player.cpp
\project_name     Double Tap
\primary_author   Ma Ming Shun, mingshun.ma,
\brief
This file contains the implementation for the class C_Bullet

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "Player.h"

// FORWARD DECLARE ALL FUNCTIONS THAT ARE GOING TO BE ADDED

namespace
{
  void OnKeyPress(object::C_GameObject *const p_this);
  void OnCollisionStarted(events::C_CollisionEvent p_event);
  void OnLogicUpdate(object::C_GameObject* p_object);
}

namespace object
{
/******************************************************************************/
/*!
The Non-Default constructor for C_Player
*/
/******************************************************************************/
C_Player::C_Player(C_GameObject *p_obj)
  : C_Component{ p_obj, PLAYER }, m_invulnerable{ false },
  m_invulnerabletime{}, m_health{ PLAYER_MAX_HEALTH },
  m_life{ PLAYER_MAX_LIFE }, m_checkpointpos{ 0, 0 }, m_hitanimation{},
  m_hit{ false }, m_lowlifetime{}, m_lowlife{ false }, m_shootanimation{}
{
}

/******************************************************************************/
/*!
Function to Connect to events
*/
/******************************************************************************/
void C_Player::Connect()
{
  events::C_EventDispatcher::Connect("KeyboardEvent", types::C_Any<void(*)
    (C_GameObject * const), C_GameObject * const>{OnKeyPress, p_obj});
  events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
}

/******************************************************************************/
/*!
Function to Clone C_Player
*/
/******************************************************************************/
C_Player *C_Player::Clone() const
{
  return new C_Player{ p_obj };
}

/******************************************************************************/
/*!
Update Function for C_Player
*/
/******************************************************************************/
void C_Player::Update()
{
  if (utilities::C_OptionsManager::Get_Pause())
    return;

  if (AEInputCheckTriggered(AEVK_NUMPAD1))
    events::C_EventDispatcher::DispatchEvent("LevelOne");
  if (AEInputCheckTriggered(AEVK_NUMPAD2))
    events::C_EventDispatcher::DispatchEvent("LevelTwo");
  if (AEInputCheckTriggered(AEVK_NUMPAD3))
    events::C_EventDispatcher::DispatchEvent("LevelThree");

  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  object::C_BoxCollider *p_collider = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));
  m_fire_rate -= utilities::C_Timer::Get_dt();
  // Set player to fade in and out while invulnerable
  if (m_invulnerable)
  {
    m_invulnerabletime += utilities::C_Timer::Get_dt();
    m_hitanimation += utilities::C_Timer::Get_dt();

    if (m_hitanimation < 0.25)
      p_sprite->Set_Opacity(0.30f);
    else if (m_hitanimation < 0.5)
      p_sprite->Set_Opacity(1.0f);
    else
      m_hitanimation = 0;

    // Stop invulnerability after 1.5s 
    if (m_invulnerabletime > 1.5)
    {
      p_sprite->Set_Opacity(1.0f);
      m_invulnerable = false;
      m_invulnerabletime = 0;
    }
  }

  // Keeps the shooting animation for 0.5s
  if (m_shooting)
  {
    m_shootanimation += utilities::C_Timer::Get_dt();

    // Set sprites back after 0.5s based on weapons
    if (m_shootanimation > 0.5)
    {
      switch (Get_Weapon())
      {
      case PISTOL:
        if (Get_Health() == 2)
          GetLowLife() ? p_sprite->Set_Texture("PlayerIdleRed") : p_sprite->Set_Texture("PlayerIdle");
        else
          Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerIdleRed") : p_sprite->Set_Texture("PlayerIdle");
        break;
      case MACHINEGUN:
        if (Get_Health() == 2)
          GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
        else
          Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
        break;
      case SHOTGUN:
        if (Get_Health() == 2)
          GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunIdleRed") : p_sprite->Set_Texture("PlayerShotgunIdle");
        else
          Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunIdleRed") : p_sprite->Set_Texture("PlayerShotgunIdle");
        break;
      }
      m_shooting = false;
      m_shootanimation = 0;
    }
  }

  // When health is 2 set sprites to blink
  if (m_health == 2)
  {
    m_lowlifetime += utilities::C_Timer::Get_dt();
    if (m_lowlifetime < 0.25)
      m_lowlife = true;
    else if (m_lowlifetime < 0.5)
      m_lowlife = false;
    else
      m_lowlifetime = 0;
    if (!m_moving && !m_jumping && !m_shooting)
    {
      m_shootanimation = 0;
      switch (m_weapon_type)
      {
      case PISTOL:
        m_lowlife ?
          p_sprite->Set_Texture("PlayerIdleRed") : p_sprite->Set_Texture("PlayerIdle");
        break;
      case MACHINEGUN:
        m_lowlife ?
          p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
        break;
      case SHOTGUN:
        m_lowlife ?
          p_sprite->Set_Texture("PlayerShotgunIdleRed") : p_sprite->Set_Texture("PlayerShotgunIdle");
        break;
      }
    }
  }

  // Reset player pos when player falls out of the screen
  if (static_cast<object::C_Transform*>
    (p_obj->Find_Component(TRANSFORM))->Get_Position().y <= 3)
  {
    --m_health;
    events::C_EventDispatcher::DispatchEvent("UpdateHP");
    if (m_health <= 0)
    {
      --m_life;
      events::C_EventDispatcher::DispatchEvent("UpdateLife");
      events::C_EventDispatcher::DispatchEvent("ToggleHeartWarning");
      m_health = PLAYER_MAX_HEALTH;
    }

    ResetPos();
  }

  // Continue firing in burst when MACHINEGUN is fired
  if (m_weapon_type == MACHINEGUN)
  {
    // While burst is still on
    if (m_machinefire > 0)
      switch (m_firedirection)
      {
      case NORMAL:
        MachineShoot();
        break;
      case UP:
        MachineShootUp();
        break;
      case DOWN:
        MachineShootDown();
        break;
      }
    // if not shooting reset sprite
    else if (!m_shooting && !m_moving)
    {
      if (Get_Health() == 2)
        GetLowLife() ?
        p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
      else
        Get_Health() <= 1 ?
        p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
    }
  }

  if (m_jumping && p_collider->Get_Grounded() && !m_keyactive)
  {
    m_jumping = false;
    switch (Get_Weapon())
    {
    case PISTOL:
      if (Get_Health() == 2)
        GetLowLife() ? p_sprite->Set_Texture("PlayerIdleRed") : p_sprite->Set_Texture("PlayerIdle");
      else
        Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerIdleRed") : p_sprite->Set_Texture("PlayerIdle");
      break;
    case MACHINEGUN:
      if (Get_Health() == 2)
        GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
      else
        Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
      break;
    case SHOTGUN:
      if (Get_Health() == 2)
        GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunIdleRed") : p_sprite->Set_Texture("PlayerShotgunIdle");
      else
        Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunIdleRed") : p_sprite->Set_Texture("PlayerShotgunIdle");
      break;
    }
  }
}

/******************************************************************************/
/*!
Function to get C_Player
*/
/******************************************************************************/
C_Player *C_Player::Actual()
{
  return this;
}

/******************************************************************************/
/*!
Function to shoot based on weapon
*/
/******************************************************************************/
void C_Player::Shoot()
{
  m_shooting = true;
  m_firedirection = NORMAL;
  switch (m_weapon_type)
  {
  case PISTOL:
    PistolShoot();
    break;
  case MACHINEGUN:
    MachineShoot();
    // Set to burst 4 more times
    m_machinefire = m_machinefire >= 0 ? m_machinefire : 4;
    break;
  case SHOTGUN:
    ShotShoot();
    break;
  }
}

/******************************************************************************/
/*!
Function to shoot up based on weapon
*/
/******************************************************************************/
void C_Player::ShootUp()
{
  m_shooting = true;
  m_firedirection = UP;
  switch (m_weapon_type)
  {
  case PISTOL:
    PistolShootUp();
    break;
  case MACHINEGUN:
    MachineShootUp();
    // Set to burst 4 more times
    m_machinefire = m_machinefire >= 0 ? m_machinefire : 4;
    break;
  case SHOTGUN:
    ShotShootUp();
    break;
  }
}

/******************************************************************************/
/*!
Function to shoot down based on weapon
*/
/******************************************************************************/
void C_Player::ShootDown()
{
  m_shooting = true;
  m_firedirection = DOWN;
  switch (m_weapon_type)
  {
  case PISTOL:
    PistolShootDown();
    break;
  case MACHINEGUN:
    MachineShootDown();
    // Set to burst 4 more times
    m_machinefire = m_machinefire >= 0 ? m_machinefire : 4;
    break;
  case SHOTGUN:
    ShotShootDown();
    break;
  }
}

/******************************************************************************/
/*!
Function to shoot with pistol
*/
/******************************************************************************/
void C_Player::PistolShoot()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    if (m_moving && !m_jumping)
      GetLowLife() ? p_sprite->Set_Texture("PlayerMoveRed") : p_sprite->Set_Texture("PlayerMove");
    else
      GetLowLife() ? p_sprite->Set_Texture("PistolShootRed") : p_sprite->Set_Texture("PistolShoot");
  else
    if (m_moving && !m_jumping)
      Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMoveRed") : p_sprite->Set_Texture("PlayerMove");
    else
      Get_Health() <= 1 ? p_sprite->Set_Texture("PistolShootRed") : p_sprite->Set_Texture("PistolShoot");

  if (m_fire_rate <= 0.0)
  {
    events::C_EventDispatcher::DispatchEvent("ShootEvent");
    m_fire_rate = 0.025;
  }
}

/******************************************************************************/
/*!
Function to shoot with Machine Gun
*/
/******************************************************************************/
void C_Player::MachineShoot()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    if (m_moving && !m_jumping)
      GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunMoveRed") : p_sprite->Set_Texture("PlayerMachinegunMove");
    else
      GetLowLife() ? p_sprite->Set_Texture("MachinegunShootRed") : p_sprite->Set_Texture("MachinegunShoot");
  else
    if (m_moving && !m_jumping)
      Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunMoveRed") : p_sprite->Set_Texture("PlayerMachinegunMove");
    else
      Get_Health() <= 1 ? p_sprite->Set_Texture("MachinegunShootRed") : p_sprite->Set_Texture("MachinegunShoot");
  if (m_fire_rate <= 0.0)
  {
    if (m_ammo-- > 0)
    {
      --m_machinefire;
      events::C_EventDispatcher::DispatchEvent("ShootEvent");
      events::C_EventDispatcher::DispatchEvent("RefreshAmmoInfo");
      m_fire_rate = 0.05;
      if (m_ammo == 0)
      {
        Set_Weapon(PISTOL);
        events::C_EventDispatcher::DispatchEvent("Pistol");
        m_machinefire = 0;
      }
    }
  }
}

/******************************************************************************/
/*!
Function to shoot with Shotgun
*/
/******************************************************************************/
void C_Player::ShotShoot()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    if (m_moving && !m_jumping)
      GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunMoveRed") : p_sprite->Set_Texture("PlayerShotgunMove");
    else
      GetLowLife() ? p_sprite->Set_Texture("ShotgunShootRed") : p_sprite->Set_Texture("ShotgunShoot");
  else
    if (m_moving && !m_jumping)
      Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunMoveRed") : p_sprite->Set_Texture("PlayerShotgunMove");
    else
      Get_Health() <= 1 ? p_sprite->Set_Texture("ShotgunShootRed") : p_sprite->Set_Texture("ShotgunShoot");
  if (m_fire_rate <= 0.0)
  {
    if (m_ammo-- > 0)
    {
      events::C_EventDispatcher::DispatchEvent("ShootEvent");
      events::C_EventDispatcher::DispatchEvent("RefreshAmmoInfo");
      m_fire_rate = 1.0;
      if (m_ammo == 0)
      {
        Set_Weapon(PISTOL);
        events::C_EventDispatcher::DispatchEvent("Pistol");
      }
    }
  }
}

/******************************************************************************/
/*!
Function to shoot up with pistol
*/
/******************************************************************************/
void C_Player::PistolShootUp()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    if (m_moving && !m_jumping)
      GetLowLife() ? p_sprite->Set_Texture("PistolShootUpRed") : p_sprite->Set_Texture("PistolShootUp");
    else
      GetLowLife() ? p_sprite->Set_Texture("PistolShootUpIdleRed") : p_sprite->Set_Texture("PistolShootUpIdle");
  else
    if (m_moving && !m_jumping)
	  Get_Health() <= 1 ? p_sprite->Set_Texture("PistolShootUpRed") : p_sprite->Set_Texture("PistolShootUp");
    else
      Get_Health() <= 1 ? p_sprite->Set_Texture("PistolShootUpIdleRed") : p_sprite->Set_Texture("PistolShootUpIdle");
  if (m_fire_rate <= 0.0)
  {
    events::C_EventDispatcher::DispatchEvent("ShootUpEvent");
    m_fire_rate = 0.025;
  }
}

/******************************************************************************/
/*!
Function to shoot up with Machine Gun
*/
/******************************************************************************/
void C_Player::MachineShootUp()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    if (m_moving && !m_jumping)
      GetLowLife() ? p_sprite->Set_Texture("MachinegunShootUpRed") : p_sprite->Set_Texture("MachinegunShootUp");
    else
      GetLowLife() ? p_sprite->Set_Texture("MachinegunShootUpIdleRed") : p_sprite->Set_Texture("MachinegunShootUpIdle");
  else
    if (m_moving && !m_jumping)
		Get_Health() <= 1 ? p_sprite->Set_Texture("MachinegunShootUpRed") : p_sprite->Set_Texture("MachinegunShootUp");
    else
      Get_Health() <= 1 ? p_sprite->Set_Texture("MachinegunShootUpIdleRed") : p_sprite->Set_Texture("MachinegunShootUpIdle");
  if (m_fire_rate <= 0.0)
  {
    if (m_ammo-- > 0)
    {
      --m_machinefire;
      events::C_EventDispatcher::DispatchEvent("ShootUpEvent");
      events::C_EventDispatcher::DispatchEvent("RefreshAmmoInfo");
      m_fire_rate = 0.05;
      if (m_ammo == 0)
      {
        Set_Weapon(PISTOL);
        events::C_EventDispatcher::DispatchEvent("Pistol");
        m_machinefire = 0;
      }
    }
  }
}

/******************************************************************************/
/*!
Function to shoot up with Shotgun
*/
/******************************************************************************/
void C_Player::ShotShootUp()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    if (m_moving && !m_jumping)
      GetLowLife() ? p_sprite->Set_Texture("ShotgunShootUpRed") : p_sprite->Set_Texture("ShotgunShootUp");
    else
      GetLowLife() ? p_sprite->Set_Texture("ShotgunShootIdleRed") : p_sprite->Set_Texture("ShotgunShootUpIdle");
  else
    if (m_moving && !m_jumping)
		Get_Health() <= 1 ? p_sprite->Set_Texture("ShotgunShootUpRed") : p_sprite->Set_Texture("ShotgunShootUp");
    else
      Get_Health() <= 1 ? p_sprite->Set_Texture("ShotgunShootUpIdleRed") : p_sprite->Set_Texture("ShotgunShootUpIdle");
  if (m_fire_rate <= 0.0)
  {
    if (m_ammo-- > 0)
    {
      events::C_EventDispatcher::DispatchEvent("ShootUpEvent");
      events::C_EventDispatcher::DispatchEvent("RefreshAmmoInfo");
      m_fire_rate = 1.0;
      if (m_ammo == 0)
      {
        Set_Weapon(PISTOL);
        events::C_EventDispatcher::DispatchEvent("Pistol");
      }
    }
  }
}

/******************************************************************************/
/*!
Function to shoot down with pistol
*/
/******************************************************************************/
void C_Player::PistolShootDown()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    GetLowLife() ? p_sprite->Set_Texture("PistolShootDownRed") : p_sprite->Set_Texture("PistolShootDown");
  else
    Get_Health() <= 1 ? p_sprite->Set_Texture("PistolShootDownRed") : p_sprite->Set_Texture("PistolShootDown");
  if (m_fire_rate <= 0.0)
  {
    events::C_EventDispatcher::DispatchEvent("ShootDownEvent");
    m_fire_rate = 0.025;
  }
}

/******************************************************************************/
/*!
Function to shoot down with Machine Gun
*/
/******************************************************************************/
void C_Player::MachineShootDown()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    GetLowLife() ? p_sprite->Set_Texture("MachinegunShootDownRed") : p_sprite->Set_Texture("MachinegunShootDown");
  else
    Get_Health() <= 1 ? p_sprite->Set_Texture("MachinegunShootDownRed") : p_sprite->Set_Texture("MachinegunShootDown");
  if (m_fire_rate <= 0.0)
  {
    if (m_ammo-- > 0)
    {
      --m_machinefire;
      events::C_EventDispatcher::DispatchEvent("ShootDownEvent");
      events::C_EventDispatcher::DispatchEvent("RefreshAmmoInfo");
      m_fire_rate = 0.05;
      if (m_ammo == 0)
      {
        Set_Weapon(PISTOL);
        events::C_EventDispatcher::DispatchEvent("Pistol");
        m_machinefire = 0;
      }
    }
  }
}

/******************************************************************************/
/*!
Function to shoot down with Shotgun
*/
/******************************************************************************/
void C_Player::ShotShootDown()
{
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
  if (Get_Health() == 2)
    GetLowLife() ? p_sprite->Set_Texture("ShotgunShootDownRed") : p_sprite->Set_Texture("ShotgunShootDown");
  else
    Get_Health() <= 1 ? p_sprite->Set_Texture("ShotgunShootDownRed") : p_sprite->Set_Texture("ShotgunShootDown");
  if (m_fire_rate <= 0.0)
  {
    if (m_ammo-- > 0)
    {
      events::C_EventDispatcher::DispatchEvent("ShootDownEvent");
      events::C_EventDispatcher::DispatchEvent("RefreshAmmoInfo");
      m_fire_rate = 1.0;
      if (m_ammo == 0)
      {
        Set_Weapon(PISTOL);
        events::C_EventDispatcher::DispatchEvent("Pistol");
      }
    }
  }

}

/******************************************************************************/
/*!
Function to get weapon
*/
/******************************************************************************/
C_Player::Weapon C_Player::Get_Weapon() const
{
  return m_weapon_type;
}

/******************************************************************************/
/*!
Function to set weapon
*/
/******************************************************************************/
void C_Player::Set_Weapon(Weapon weap)
{
  m_fire_rate = 0.0;
  if (m_weapon_type == weap)
  {
    switch (m_weapon_type)
    {
    case MACHINEGUN:
      m_ammo += 200;
      break;
    case SHOTGUN:
      m_ammo += 16;
      break;
    }
    return;
  }

  m_weapon_type = weap;
  switch (m_weapon_type)
  {
  case MACHINEGUN:
    m_ammo = 200;
    break;
  case SHOTGUN:
    m_ammo = 16;
    break;
  }

  events::C_EventDispatcher::DispatchEvent("RefreshAmmoInfo");
}

/******************************************************************************/
/*!
Function to set key active
*/
/******************************************************************************/
void C_Player::Set_KeyActive(bool key)
{
  m_keyactive = key;
}

/******************************************************************************/
/*!
Function to set checkpoint position
*/
/******************************************************************************/
void C_Player::Set_CheckpointPos(math::Vec2 pos)
{
  m_checkpointpos = pos;
}

/******************************************************************************/
/*!
Function to set if player is shooting
*/
/******************************************************************************/
void C_Player::Set_Shoot(bool shoot)
{
  m_shooting = shoot;
}

/******************************************************************************/
/*!
Function to set Shoot Animation time
*/
/******************************************************************************/
void C_Player::Set_ShootAnimation(double time)
{
  m_shootanimation = time;
}

/******************************************************************************/
/*!
Function to get if player is shooting
*/
/******************************************************************************/
bool C_Player::Get_Shoot() const
{
  return m_shooting;
}

void C_Player::Set_Moving(bool move)
{
  m_moving = move;
}

bool C_Player::Get_Moving() const
{
  return m_moving;
}

void C_Player::Set_Jumping(bool jump)
{
  m_jumping = jump;
}

bool C_Player::Get_Jumping() const
{
  return m_jumping;
}

/******************************************************************************/
/*!
Function to get health of player
*/
/******************************************************************************/
int C_Player::Get_Health() const
{
  return m_health;
}

/******************************************************************************/
/*!
Function to get ammo
*/
/******************************************************************************/
int C_Player::Get_Ammo() const
{
  return m_ammo;
}

/******************************************************************************/
/*!
Function to get invulnerability of the player
*/
/******************************************************************************/
bool C_Player::Get_Invulnerable() const
{
  return m_invulnerable;
}

/******************************************************************************/
/*!
Function to check if player has low life
*/
/******************************************************************************/
bool C_Player::GetLowLife() const
{
  return m_lowlife;
}

/******************************************************************************/
/*!
Function to reset player position
*/
/******************************************************************************/
void C_Player::ResetPos()
{
  static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM))->
    Set_Position(m_checkpointpos.x, m_checkpointpos.y);
  if (m_health <= 0)
  {
    m_health = PLAYER_MAX_HEALTH;
  }
}

/******************************************************************************/
/*!
Function to call when collision happen
*/
/******************************************************************************/
void C_Player::CollisionStarted(object::C_GameObject* p_otherobject)
{
  if (!p_otherobject)
  {
    if (!m_invulnerable)
    {
      events::C_EventDispatcher::DispatchEvent("UpdateHP");
      --m_health;
      m_invulnerable = true;
      if (m_health <= 0)
      {
        --m_life;
        events::C_EventDispatcher::DispatchEvent("UpdateLife");
        events::C_EventDispatcher::DispatchEvent("ToggleHeartWarning");
        ResetPos();
        m_health = PLAYER_MAX_HEALTH;
      }
    }
    return;
  }

  TRAIT type = p_otherobject->Get_Trait();

  // If player is not invulnerable
  if (!m_invulnerable)
  {
    // If the other object is a enemy or a enemy bullet
    if (type == T_ENEMY || type == T_ENEMYBULLET)
    {
      events::C_EventDispatcher::DispatchEvent("CameraShake");
      events::C_EventDispatcher::DispatchEvent("UpdateHP");
      --m_health;
      m_invulnerable = true;
      if (m_health <= 0)
      {
        --m_life;
        events::C_EventDispatcher::DispatchEvent("UpdateLife");
        events::C_EventDispatcher::DispatchEvent("ToggleHeartWarning");
        ResetPos();
        m_health = PLAYER_MAX_HEALTH;
      }
    }
    // If the other object is a hazard
    else if (type == T_HAZARD)
    {
      events::C_EventDispatcher::DispatchEvent("CameraShake");
      --m_health;
      events::C_EventDispatcher::DispatchEvent("UpdateHP");
      // Stop movement and push player back
      static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE))->Get_FlipX() ?
        static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY))
        ->Set_VelocityX(0.0f) :
        static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY))
        ->Set_VelocityX(0.0f);
      static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE))->Get_FlipX() ?
        static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY))
        ->Set_Acceleration(2500.0f) :
        static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY))
        ->Set_Acceleration(-2500.0f);
      m_invulnerable = true;
      if (m_health <= 0)
      {
        --m_life;
        events::C_EventDispatcher::DispatchEvent("UpdateLife");
        events::C_EventDispatcher::DispatchEvent("ToggleHeartWarning");
        ResetPos();
        m_health = PLAYER_MAX_HEALTH;
      }
    }
  }
}

}

//////////////////////// FUNCTIONS TO BE CONNECTED MUST BE GLOBAL FUNCTIONS //////////////////////////////////////
namespace
{

/******************************************************************************/
/*!
Function to check keyboard input
*/
/******************************************************************************/
void OnKeyPress(object::C_GameObject *const p_this)
{
  // stop checking if game is paused
  if (utilities::C_OptionsManager::Get_Pause())
  {
    return;
  }

  using WEAPON = object::C_Player::Weapon;
  object::C_Player * p_player = static_cast<object::C_Player*>(p_this->Find_Component(PLAYER));
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(p_this->Find_Component(SPRITE));
  object::C_BoxCollider *p_collider = static_cast<object::C_BoxCollider*>(p_this->Find_Component(BOXCOLLIDER));
  object::C_Rigidbody *p_rigid = static_cast<object::C_Rigidbody*>(p_this->Find_Component(RIGIDBODY));
  if (utilities::C_Keyboard::KeyIsReleased(AEVK_SPACE))
  {
    p_player->Set_KeyActive(false);
  }
  if (utilities::C_Keyboard::KeyIsReleased(AEVK_LEFT) || utilities::C_Keyboard::KeyIsReleased(AEVK_RIGHT))
  {
    p_player->Set_Moving(false);
    if (!p_player->Get_Shoot() && !p_player->Get_Jumping())
    {
      // Reset player sprite when no input is read
      switch (p_player->Get_Weapon())
      {
      case WEAPON::PISTOL:
        if (p_player->Get_Health() == 2)
          p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerIdleRed") : p_sprite->Set_Texture("PlayerIdle");
        else
          p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerIdleRed") : p_sprite->Set_Texture("PlayerIdle");
        break;
      case WEAPON::MACHINEGUN:
        if (p_player->Get_Health() == 2)
          p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
        else
          p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunIdleRed") : p_sprite->Set_Texture("PlayerMachinegunIdle");
        break;
      case WEAPON::SHOTGUN:
        if (p_player->Get_Health() == 2)
          p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunIdleRed") : p_sprite->Set_Texture("PlayerShotgunIdle");
        else
          p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunIdleRed") : p_sprite->Set_Texture("PlayerShotgunIdle");
        break;
      }
    }
  }

  // Moving left
  if (utilities::C_Keyboard::KeyIsPressed(AEVK_LEFT))
  {
    p_rigid->Set_VelocityX(-7.0);
    p_sprite->Set_FlipX(true);
    p_player->Set_Moving(true);
    // Set Sprite if player is not shooting
    if (!p_player->Get_Shoot())
    {
      // Set Sprite based on player health and weapon
      switch (p_player->Get_Weapon())
      {
      case WEAPON::PISTOL:
        if (p_player->Get_Health() == 2)
        {
          if (p_collider->Get_Grounded())
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerMoveRed") : p_sprite->Set_Texture("PlayerMove");
          else
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerJumpRed") : p_sprite->Set_Texture("PlayerJump");
        }
        else
        {
          if (p_collider->Get_Grounded())
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMoveRed") : p_sprite->Set_Texture("PlayerMove");
          else
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerJumpRed") : p_sprite->Set_Texture("PlayerJump");
        }
        break;
      case WEAPON::MACHINEGUN:
        if (p_player->Get_Health() == 2)
        {
          if (p_collider->Get_Grounded())
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunMoveRed") : p_sprite->Set_Texture("PlayerMachinegunMove");
          else
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunJumpRed") : p_sprite->Set_Texture("PlayerMachinegunJump");
        }
        else
          if (p_collider->Get_Grounded())
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunMoveRed") : p_sprite->Set_Texture("PlayerMachinegunMove");
          else
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunJumpRed") : p_sprite->Set_Texture("PlayerMachinegunJump");
        break;
      case WEAPON::SHOTGUN:
        if (p_player->Get_Health() == 2)
        {
          if (p_collider->Get_Grounded())
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunMoveRed") : p_sprite->Set_Texture("PlayerShotgunMove");
          else
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunJumpRed") : p_sprite->Set_Texture("PlayerShotgunJump");
        }
        else
          if (p_collider->Get_Grounded())
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunMoveRed") : p_sprite->Set_Texture("PlayerShotgunMove");
          else
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunJumpRed") : p_sprite->Set_Texture("PlayerShotgunJump");
        break;
      }
    }

  }

  // Moving right
  if (utilities::C_Keyboard::KeyIsPressed(AEVK_RIGHT))
  {
    p_rigid->Set_VelocityX(7.0);
    p_sprite->Set_FlipX(false);
    p_player->Set_Moving(true);
    // Set Sprite if player is not shooting
    if (!p_player->Get_Shoot())
    {
      // Set Sprite based on player health and weapon
      switch (p_player->Get_Weapon())
      {
      case WEAPON::PISTOL:
        if (p_player->Get_Health() == 2)
        {
          if (p_collider->Get_Grounded())
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerMoveRed") : p_sprite->Set_Texture("PlayerMove");
          else
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerJumpRed") : p_sprite->Set_Texture("PlayerJump");
        }
        else
          if (p_collider->Get_Grounded())
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMoveRed") : p_sprite->Set_Texture("PlayerMove");
          else
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerJumpRed") : p_sprite->Set_Texture("PlayerJump");
        break;
      case WEAPON::MACHINEGUN:
        if (p_player->Get_Health() == 2)
        {
          if (p_collider->Get_Grounded())
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunMoveRed") : p_sprite->Set_Texture("PlayerMachinegunMove");
          else
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerMachinegunJumpRed") : p_sprite->Set_Texture("PlayerMachinegunJump");
        }
        else
          if (p_collider->Get_Grounded())
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunMoveRed") : p_sprite->Set_Texture("PlayerMachinegunMove");
          else
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerMachinegunJumpRed") : p_sprite->Set_Texture("PlayerMachinegunJump");
        break;
      case WEAPON::SHOTGUN:
        if (p_player->Get_Health() == 2)
        {
          if (p_collider->Get_Grounded())
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunMoveRed") : p_sprite->Set_Texture("PlayerShotgunMove");
          else
            p_player->GetLowLife() ? p_sprite->Set_Texture("PlayerShotgunJumpRed") : p_sprite->Set_Texture("PlayerShotgunJump");
        }
        else
          if (p_collider->Get_Grounded())
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunMoveRed") : p_sprite->Set_Texture("PlayerShotgunMove");
          else
            p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PlayerShotgunJumpRed") : p_sprite->Set_Texture("PlayerShotgunJump");
        break;
      }
    }
  }

  if (utilities::C_Keyboard::KeyIsTriggered(AEVK_SPACE) &&
    p_collider->Get_Grounded())
  {
    p_player->Set_KeyActive(true);
    p_player->Set_Jumping(true);
    p_rigid->Set_VelocityY(17.0);
    // Set Sprite based on player health and weapon
    switch (p_player->Get_Weapon())
    {
    case WEAPON::PISTOL:
      if (p_player->Get_Health() == 2)
        p_player->GetLowLife() ? p_sprite->Set_Texture("PistolJumpRed") : p_sprite->Set_Texture("PistolJump");
      else
        p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("PistolJumpRed") : p_sprite->Set_Texture("PistolJump");
      break;
    case WEAPON::MACHINEGUN:
      if (p_player->Get_Health() == 2)
        p_player->GetLowLife() ? p_sprite->Set_Texture("MachinegunJumpRed") : p_sprite->Set_Texture("MachinegunJump");
      else
        p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("MachinegunJumpRed") : p_sprite->Set_Texture("MachinegunJump");
      break;
    case WEAPON::SHOTGUN:
      if (p_player->Get_Health() == 2)
        p_player->GetLowLife() ? p_sprite->Set_Texture("ShotgunJumpRed") : p_sprite->Set_Texture("ShotgunJump");
      else
        p_player->Get_Health() <= 1 ? p_sprite->Set_Texture("ShotgunJumpRed") : p_sprite->Set_Texture("ShotgunJump");
      break;
    }
  }
  // Shooting
  if (utilities::C_Keyboard::KeyIsTriggered(AEVK_Z))
  {
    if (utilities::C_Keyboard::KeyIsPressed(AEVK_DOWN) &&
      !p_collider->Get_Grounded())
    {
      p_player->ShootDown();
    }
    else if (utilities::C_Keyboard::KeyIsPressed(AEVK_UP))
    {
      p_player->ShootUp();
    }
    else
    {
      p_player->Shoot();
    }
    p_player->Set_Shoot(true);
    p_player->Set_ShootAnimation(0);
  }
  // Cheat to kill boss
  if (AEInputCheckTriggered(AEVK_L))
  {
    events::C_EventDispatcher::DispatchEvent("BossKill");
  }
  // Cheat to teleport to boss
  if (utilities::C_Keyboard::KeyIsTriggered(AEVK_K))
  {
	  events::C_EventDispatcher::DispatchEvent("ToBoss");
  }

}

/******************************************************************************/
/*!
Function to call CollisionStarted
*/
/******************************************************************************/
void OnCollisionStarted(events::C_CollisionEvent p_event)
{
  static_cast<object::C_Player*>(p_event.Object()->Find_Component(PLAYER))
  ->CollisionStarted(p_event.Other_Object());

  if (!p_event.Other_Object())
  {
    return;
  }
  // Set Shotgun as weapon
  if (p_event.Other_Object()->Get_Name() == "ShotGunPickUp")
  {
    static_cast<object::C_Player*>(p_event.Object()->Find_Component(PLAYER))
    ->Set_Weapon(object::C_Player::SHOTGUN);
    events::C_EventDispatcher::DispatchEvent("Shotgun");
  }
  // Set MachineGun as weapon
  else if (p_event.Other_Object()->Get_Name() == "MachineGunPickUp")
  {
    static_cast<object::C_Player*>(p_event.Object()->Find_Component(PLAYER))
    ->Set_Weapon(object::C_Player::MACHINEGUN);
    events::C_EventDispatcher::DispatchEvent("MachineGun");
  }
}

/******************************************************************************/
/*!
Function to call Update
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject* p_object)
{
  static_cast<object::C_Player*>(p_object->Find_Component(PLAYER))->Update();
}
}
