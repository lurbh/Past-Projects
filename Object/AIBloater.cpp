/******************************************************************************/
/*!
\file_name        AIBloater.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the implementation for the class C_AIBloater

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "AIBloater.h"

// FORWARD DECLARE ALL FUNCTIONS THAT ARE GOING TO BE ADDED

namespace
{
  void OnCollisionStarted(events::C_CollisionEvent p_event);
  void OnLogicUpdate(object::C_GameObject* p_object);
  void SpawnSmokeParticle(object::C_GameObject *p_object);
}

namespace object
{
/******************************************************************************/
/*!
  The Non-Default constructor for C_AIBloater
*/
/******************************************************************************/
C_AIBloater::C_AIBloater(C_GameObject *p_obj, C_GameObject * player, 
	COLLISIONMAP * p_map, int width, AISTATE wander, int hp)
  : C_Component{ p_obj, AIBLOATER }, m_aistate{ wander }, n_health{ hp },
  m_timemax{}, m_time{}, m_charge{ false }, m_direction{ false }, 
  m_player{ player }, m_boomtime{}, m_chargepos{}, m_map{ p_map }, 
  m_width{ width }, m_hitanimation{}, m_hit{ false }, mp_smokesys{ nullptr }
{
}

/******************************************************************************/
/*!
  Function to Connect to events 
*/
/******************************************************************************/
void C_AIBloater::Connect()
{
  events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
  events::C_EventDispatcher::Connect("SpawnSmokeParticle", 
  SpawnSmokeParticle, p_obj);
}

/******************************************************************************/
/*!
  Function to Clone C_AIBloater
*/
/******************************************************************************/
C_AIBloater *C_AIBloater::Clone() const
{
  return new C_AIBloater{ p_obj, m_player, m_map, m_width, m_aistate, n_health};
}

/******************************************************************************/
/*!
  Update Function for C_AIBloater
*/
/******************************************************************************/
void C_AIBloater::Update()
{
  // Stop update when game is paused
  if(utilities::C_OptionsManager::Get_Pause())
    return;

  // Flicker hit animation upon collision to bullets
  if (m_hit)
  {
    m_hitanimation += utilities::C_Timer::Get_dt();
    if (m_hitanimation > 0.1)
    {
      m_hitanimation = 0;
      m_hit = false;
    }
  }

  // Delay for how long before being able to be damage by a shotgun
  if (m_shotgunhit)
  {
    m_checktime += utilities::C_Timer::Get_dt();
    if (m_checktime > 1)
    {
      m_checktime = 0;
      m_shotgunhit = false;
    }
    return;
  }

  math::Vec2 enemypos, playerpos;
  enemypos = static_cast<object::C_Transform*>
	  (p_obj->Find_Component(TRANSFORM))->Get_Position();
  playerpos = static_cast<object::C_Transform*>
	  (m_player->Find_Component(TRANSFORM))->Get_Position();

  m_time += utilities::C_Timer::Get_dt();

  // Check the state of AI
  m_aistate = CheckState(m_aistate);

  float velocityx = static_cast<object::C_Rigidbody*>
	  (p_obj->Find_Component(RIGIDBODY))->Get_Velocity_Global().x;
  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>
	  (p_obj->Find_Component(SPRITE));
  bool flipx = p_sprite->Get_FlipX();

  // Flips sprite based on direction of movement
  if (velocityx < 0 && !flipx)
    p_sprite->Set_FlipX(true);

  if (velocityx > 0 && flipx)
    p_sprite->Set_FlipX(false);


  // Different actions based on which state the ai is
  switch (m_aistate)
  {
  case STATIC:
    m_hit ? p_sprite->Set_Texture("BloaterIdleRed") 
		: p_sprite->Set_Texture("BloaterIdle");
    static_cast<object::C_Rigidbody*>
		(p_obj->Find_Component(RIGIDBODY))->Set_Acceleration(0.0f);
    // When Static state is over set next state as wander
    if (m_time > m_timemax)
    {
      m_aistate = WANDER;
      m_timemax = AERandFloat() * 10;
      m_time = 0;
      m_direction = rand() % 2 ? true : false;
    }
    break;
  case WANDER:
    m_hit ? p_sprite->Set_Texture("BloaterWanderRed") 
		: p_sprite->Set_Texture("BloaterWander");
    // Stop movement when at edges or facing walls
    if (CheckTile() && velocityx != 0)
    {
      m_aistate = STATIC;
      break;
    }
    m_direction ? AddAcceleration(-50.0f) : AddAcceleration(50.0f);
    // When Wander state is over set next state as static
    if (m_time > m_timemax)
    {
      m_timemax = AERandFloat() * 5;
      m_aistate = STATIC;
      m_time = 0;
    }
    break;
  case ROLL:
    m_hit ? p_sprite->Set_Texture("BloaterChaseRed") 
		: p_sprite->Set_Texture("BloaterChase");
    // Stop movement when at edges or facing walls while charging
    if (CheckTile() && m_charge)
    {
      m_aistate = STATIC;
      break;
    }
    // Set charging direction based on player position
    if (!m_charge)
    {
      playerpos.x - enemypos.x > 0 ? m_chargepos = enemypos + 10 
		  : m_chargepos = enemypos - 10;
      m_charge = true;
    }
    // When not at charging position
    if (abs(m_chargepos.x - enemypos.x) > 0.5)
    {
      m_chargepos.x - enemypos.x > 0 ? 
		  AddAcceleration(300.0f) : AddAcceleration(-300.0f);
      m_chargepos.x - enemypos.x > 0 ? 
		  m_direction = false : m_direction = true;
    }
    // Stop charging when at charging position
    else
    {
      m_aistate = STATIC;
      m_direction = !m_direction;
    }
    break;
  case BOOM:
    // State when Bloater is dead
    m_boomtime += utilities::C_Timer::Get_dt();
    // Increases collider with time
    static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER))->
      Set_Size(80.0f / TILESCALE / (3.0f - (float)m_boomtime / 1.5f)
		  , 160.0f / TILESCALE / 3.0f);
    // Reset when time is more than 3
    if (m_boomtime > 3)
    {
      Reset();
    }
    break;
  }
}

/******************************************************************************/
/*!
  Function to get C_AIBloater
*/
/******************************************************************************/
C_AIBloater *C_AIBloater::Actual()
{
  return this;
}

/******************************************************************************/
/*!
  Function to call when AIBloater is dead
*/
/******************************************************************************/
void C_AIBloater::Death()
{
  auto p_sprite = static_cast<object::C_Sprite*>
	  (p_obj->Find_Component(SPRITE));
  // Set Next state to dead state
  m_boomtime = 0;
  m_aistate = BOOM;
  // Set sprtie to be transparent
  p_sprite->Set_Opacity(0.0f);
  // Dispatch events 
  events::C_EventDispatcher::DispatchEvent("BloaterDeath");
  events::C_EventDispatcher::DispatchEvent("SpawnSmokeParticle");
}

/******************************************************************************/
/*!
  Function to Check State of AIBloater
*/
/******************************************************************************/
AISTATE C_AIBloater::CheckState(AISTATE m_state)
{
  if (m_state == BOOM)
    return m_state;
  math::Vec2 enemypos, playerpos;
  enemypos = static_cast<object::C_Transform*>
	  (p_obj->Find_Component(TRANSFORM))->Get_Position();
  playerpos = static_cast<object::C_Transform*>
	  (m_player->Find_Component(TRANSFORM))->Get_Position();
  // Set to charge when the dist between player and ai is less than 8
  if (abs(playerpos.y - enemypos.y) <= 2)
  {
    if (abs(playerpos.x - enemypos.x) <= 8 && !m_charge)
      return ROLL;
  }
  return m_state;
}

/******************************************************************************/
/*!
  Function to add acceleration to AIBloater
*/
/******************************************************************************/
void C_AIBloater::AddAcceleration(float f_speed)
{
  object::C_Rigidbody *p_rigid = static_cast<object::C_Rigidbody*>
	  (p_obj->Find_Component(RIGIDBODY));
  p_rigid->Add_Acceleration(f_speed, 0.0f);
}

/******************************************************************************/
/*!
  Function to Set Max Time
*/
/******************************************************************************/
void C_AIBloater::SetMaxTime(float m_maxtime)
{
  m_timemax = m_maxtime;
}

/******************************************************************************/
/*!
  Function to Set Direction
*/
/******************************************************************************/
void C_AIBloater::SetDirection(bool m_setdirection)
{
  m_direction = m_setdirection;
}

/******************************************************************************/
/*!
  Function to Set AI state
*/
/******************************************************************************/
void C_AIBloater::SetState(AISTATE m_state)
{
  m_aistate = m_state;
}

/******************************************************************************/
/*!
  Function to Set pointer to player
*/
/******************************************************************************/
void C_AIBloater::Set_Player(C_GameObject * p_player)
{
  m_player = p_player;
}

/******************************************************************************/
/*!
  Function to get pointer to player
*/
/******************************************************************************/
C_GameObject * C_AIBloater::GetPlayer() const
{
  return m_player;
}

/******************************************************************************/
/*!
  Function to get AI state
*/
/******************************************************************************/
AISTATE C_AIBloater::GetState() const
{
  return m_aistate;
}

/******************************************************************************/
/*!
  Function to call to reset AI Bloater
*/
/******************************************************************************/
void C_AIBloater::Reset()
{
  // Reset all the values in AI Bloater
  auto p_sprite = static_cast<object::C_Sprite*>
	  (p_obj->Find_Component(SPRITE));
  auto p_box = static_cast<object::C_BoxCollider*>
	  (p_obj->Find_Component(BOXCOLLIDER));
  auto p_rigidbody = static_cast<object::C_Rigidbody*>
	  (p_obj->Find_Component(RIGIDBODY));
  p_box->Set_Size(80.0f / TILESCALE / 2.8f, 160.0f / TILESCALE / 2.8f);
  p_rigidbody->Set_Gravity(true);
  p_sprite->Set_Texture("BloaterIdle");
  p_sprite->Set_Opacity(1.0f);
  n_health = 5;
  m_boomtime = 0;
  m_time = 0;
  m_aistate = STATIC;
  mp_smokesys->Destroy();
  p_obj->Destroy();
}

/******************************************************************************/
/*!
  Function to check the tile to stop movement
*/
/******************************************************************************/
bool C_AIBloater::CheckTile()
{
  int x;
  math::Vec2 enemypos;
  enemypos = static_cast<object::C_BoxCollider*>
	  (p_obj->Find_Component(BOXCOLLIDER))->Get_Min();
  x = m_direction ? -1 : 
	  (enemypos.x = static_cast<object::C_BoxCollider*>
	  (p_obj->Find_Component(BOXCOLLIDER))->Get_Max().x, 1);

  // Return true if at edges or walls
  if ((!m_map[((int)enemypos.y - 1) * m_width + (int)enemypos.x + x])
    || (!m_map[((int)enemypos.y - 1) * m_width + (int)enemypos.x + x + x])
    || (m_map[((int)enemypos.y) * m_width + (int)enemypos.x + x]))
  {
    return true;
  }
  return false;
}

/******************************************************************************/
/*!
  Function to call when collision happen
*/
/******************************************************************************/
void C_AIBloater::CollisionStarted(object::C_GameObject* p_otherobject)
{
  if (m_aistate == BOOM)
    return;

  // Collision with Bullets
  if (p_otherobject->Get_Trait() == T_BULLET)
  {
    m_hit = true;
    events::C_EventDispatcher::DispatchEvent("Enrage");
    --n_health;
    m_aistate = ROLL;
    m_charge = false;
    m_boomtime = 0;
    if (n_health <= 0)
      Death();
  }

  // Collision with Shotgun Bullets
  if (p_otherobject->Get_Trait() == T_SHOTGUNBULLET && !m_shotgunhit)
  {
    m_hit = true;
    m_shotgunhit = true;
    events::C_EventDispatcher::DispatchEvent("Enrage");
    n_health -= 5;
    if (m_direction)
      AddAcceleration(1000.0f);
    else
      AddAcceleration(-1000.0f);
    if (n_health <= 0)
      Death();
  }
}
}

//////////////////////// FUNCTIONS TO BE CONNECTED MUST BE GLOBAL FUNCTIONS //////////////////////////////////////

namespace
{
/******************************************************************************/
/*!
  Function to call CollisionStarted
*/
/******************************************************************************/
void OnCollisionStarted(events::C_CollisionEvent p_event)
{
  (static_cast<object::C_AIBloater*>(p_event.Object()->
  Find_Component(AIBLOATER))->CollisionStarted(p_event.Other_Object()));
}

/******************************************************************************/
/*!
  Function to call Update
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject* p_object)
{
  (static_cast<object::C_AIBloater*>(p_object->Find_Component(AIBLOATER))
  ->Update());
}

/******************************************************************************/
/*!
  Function to call to spawn SmokeParticle
*/
/******************************************************************************/
void SpawnSmokeParticle(object::C_GameObject *p_object)
{
  if (p_object->Get_Active())
  {
    object::C_GameObject *p_smokesys = static_cast<object::C_AIBloater *>
    (p_object->Find_Component(AIBLOATER))->mp_smokesys;
    object::C_Transform *p_transform = static_cast<object::C_Transform *>
    (p_smokesys->Find_Component(TRANSFORM));

    object::C_Transform *p_bloatertrans = static_cast<object::C_Transform *>
    (p_object->Find_Component(TRANSFORM));

    p_transform->Set_Position(p_bloatertrans->Get_Position().x - 1.0f,
    p_bloatertrans->Get_Position().y - 1.4f);

    p_smokesys->Set_Active(true);
  }
}
}

