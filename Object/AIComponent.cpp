/******************************************************************************/
/*!
\file_name        AIComponent.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the implementation for the class C_AI

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "AIComponent.h"

// FORWARD DECLARE ALL FUNCTIONS THAT ARE GOING TO BE ADDED

namespace
{
  void OnCollisionStarted(events::C_CollisionEvent p_event);
  void OnLogicUpdate(object::C_GameObject* p_object);
  void MakeEnrage(object::C_GameObject* p_object);
}

namespace object
{
/******************************************************************************/
/*!
  The Non-Default constructor for C_AI
*/
/******************************************************************************/
C_AI::C_AI(C_GameObject *p_obj, bool m_static, C_GameObject * p_player, 
  COLLISIONMAP * p_map, int width, float vel, AISTATE m_wander, int n_hp)
  : C_Component{ p_obj, AI }, m_aistate{ m_wander }, n_health{ n_hp }, 
  m_timemax{}, m_time{}, m_map{ p_map }, m_chasevel{ vel },
  m_direction{}, m_alwaysstatic{ m_static }, m_player{ p_player },
  m_width{ width }, m_hitanimation{}, m_hit{ false }
{
}

/******************************************************************************/
/*!
  Function to Connect to events
*/
/******************************************************************************/
void C_AI::Connect()
{
  events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
  events::C_EventDispatcher::Connect("Enrage", MakeEnrage, p_obj);
}

/******************************************************************************/
/*!
  Function to Clone C_AI
*/
/******************************************************************************/
C_AI *C_AI::Clone() const
{
  return new C_AI{ p_obj, m_alwaysstatic, m_player, m_map,
    m_width, m_chasevel, m_aistate, n_health };
}

/******************************************************************************/
/*!
  Update Function for C_AIBloater
*/
/******************************************************************************/
void C_AI::Update()
{
  // Stop update when game is paused
  if(utilities::C_OptionsManager::Get_Pause())
    return;

  // Death animation when health is zero
  if (m_dead)
  {
    m_deathanimation += utilities::C_Timer::Get_dt();
    if (m_deathanimation > 1)
    {
      Reset();
    }
    return;
  }

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
      m_shotgunhit = false;
      m_checktime = 0;
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
  if (m_direction && !flipx)
    p_sprite->Set_FlipX(true);

  if (!m_direction && flipx)
    p_sprite->Set_FlipX(false);

  // Different actions based on which state the ai is
  switch (m_aistate)
  {
  case STATIC:
    m_hit ? p_sprite->Set_Texture("ZombieIdleRed") 
    : p_sprite->Set_Texture("ZombieIdle");
    AddAcceleration(0.0f);
    // When Static state is over set next state as wander if alwaysstatic is false
    if (!m_alwaysstatic)
    {
      if (m_time > m_timemax)
      {
        m_aistate = WANDER;
        m_timemax = AERandFloat() * 10;
        m_time = 0;
        m_direction = rand() % 2 ? true : false;
      }
    }
    break;
  case WANDER:
    m_hit ? p_sprite->Set_Texture("ZombieWanderRed") 
    : p_sprite->Set_Texture("ZombieWander");
    // Stop movement when at edges or facing walls
    if (CheckTile())
    {
      m_aistate = STATIC;
      m_direction ? AddAcceleration(10.0f) : AddAcceleration(-10.0f);
      break;
    }
    m_direction ? AddAcceleration(-50.0f) : AddAcceleration(50.0f);
    // When Wander state is over set next state as static
    if (!m_alwaysstatic)
    {
      if (m_time > m_timemax)
      {
        m_timemax = AERandFloat() * 5;
        m_aistate = STATIC;
        m_time = 0;
      }
    }
    break;
  case CHASE:
    m_hit ? p_sprite->Set_Texture("ZombieChaseRed") 
    : p_sprite->Set_Texture("ZombieChase");
    // Stop movement when at edges or facing walls
    if ((CheckTile() || CheckTile2()) && velocityx != 0)
    {
      m_aistate = STATIC;
      break;
    }
    // Set chase direction
    if ((playerpos.x - enemypos.x > 3) || (playerpos.x - enemypos.x < -3))
    {
      playerpos.x - enemypos.x > 0 ? m_direction = false : m_direction = true;
    }
    m_direction ? AddAcceleration(-m_chasevel) : AddAcceleration(m_chasevel);
    break;
  case ENRAGE:
    m_hit ? p_sprite->Set_Texture("ZombieChaseRed") 
    : p_sprite->Set_Texture("ZombieChase");
    // Stop movement when at edges or facing walls
    if ((CheckTile() || (CheckTile2() && abs(playerpos.y - enemypos.y) >= 2)) 
    && velocityx != 0)
    {
      m_aistate = STATIC;
      break;
    }
    // Set chase direction
    if ((playerpos.x - enemypos.x > 3) || (playerpos.x - enemypos.x < -3))
    {
      playerpos.x - enemypos.x > 0 ? m_direction = false : m_direction = true;
    }
    m_direction ? AddAcceleration(-m_chasevel - 30.0f) 
    : AddAcceleration(m_chasevel + 30.0f);
    break;
  }
}

/******************************************************************************/
/*!
  Function to get C_AI
*/
/******************************************************************************/
C_AI *C_AI::Actual()
{
  return this;
}

/******************************************************************************/
/*!
  Function to call when AI is dead
*/
/******************************************************************************/
void C_AI::Death()
{
  auto p_sprite = static_cast<object::C_Sprite*>
    (p_obj->Find_Component(SPRITE));
  auto p_box = static_cast<object::C_BoxCollider*>
    (p_obj->Find_Component(BOXCOLLIDER));
  auto p_rigidbody = static_cast<object::C_Rigidbody*>
    (p_obj->Find_Component(RIGIDBODY));
  m_deathanimation = 0;
  m_dead = true;
  m_hit = false;
  // Set next state as death
  m_aistate = DEATH;
  // Set collider and gravity to false
  p_box->Set_Active(false);
  p_rigidbody->Set_Gravity(false);
  p_rigidbody->Set_VelocityX(0);
  p_sprite->Set_Texture("ZombieDeath");
}

/******************************************************************************/
/*!
  Function to Check State of AI
*/
/******************************************************************************/
AISTATE C_AI::CheckState(AISTATE m_state)
{
  math::Vec2 enemypos, playerpos;
  enemypos = static_cast<object::C_Transform*>
    (p_obj->Find_Component(TRANSFORM))->Get_Position();
  playerpos = static_cast<object::C_Transform*>
    (m_player->Find_Component(TRANSFORM))->Get_Position();
  // Keep as enrage while player at the same level as the player
  if (m_state == ENRAGE && abs(playerpos.y - enemypos.y) <= 5)
    return m_state;

  // Set to chase when the dist between player and ai is less than 8
  if (abs(playerpos.y - enemypos.y) <= 3)
  {
    if (abs(playerpos.x - enemypos.x) <= 5)
      return CHASE;
  }
  if (m_state == CHASE || m_state == ENRAGE)
    return STATIC;
  return m_state;
}

/******************************************************************************/
/*!
  Function to add acceleration to AI
*/
/******************************************************************************/
void C_AI::AddAcceleration(float f_speed)
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
void C_AI::SetMaxTime(float m_maxtime)
{
  m_timemax = m_maxtime;
}

/******************************************************************************/
/*!
  Function to Set Direction
*/
/******************************************************************************/
void C_AI::SetDirection(bool m_setdirection)
{
  m_direction = m_setdirection;
}

/******************************************************************************/
/*!
  Function to Set AI state
*/
/******************************************************************************/
void C_AI::SetState(AISTATE m_state)
{
  m_aistate = m_state;
}

/******************************************************************************/
/*!
  Function to Set pointer to player
*/
/******************************************************************************/
C_GameObject * C_AI::GetPlayer() const
{
  return m_player;
}

/******************************************************************************/
/*!
Function to call to reset AI Bloater
*/
/******************************************************************************/
void C_AI::Reset()
{
  auto p_sprite = static_cast<object::C_Sprite*>
    (p_obj->Find_Component(SPRITE));
  auto p_box = static_cast<object::C_BoxCollider*>
    (p_obj->Find_Component(BOXCOLLIDER));
  auto p_rigidbody = static_cast<object::C_Rigidbody*>
    (p_obj->Find_Component(RIGIDBODY));
  m_deathanimation = 0;
  // Set collider and gravity to true
  p_box->Set_Active(true);
  p_rigidbody->Set_Gravity(true);
  p_sprite->Set_Texture("ZombieIdle");
  m_dead = false;
  m_hit = false;
  n_health = 5;
  m_time = 0;
  m_aistate = STATIC;
  p_obj->Destroy();
}

/******************************************************************************/
/*!
  Function to Set pointer to player
*/
/******************************************************************************/
void C_AI::Set_Player(C_GameObject * p_player)
{
  m_player = p_player;
}

/******************************************************************************/
/*!
  Function to Set ai state to enrage
*/
/******************************************************************************/
void C_AI::Enrage()
{
  math::Vec2 enemypos, playerpos;
  enemypos = static_cast<object::C_Transform*>
    (p_obj->Find_Component(TRANSFORM))->Get_Position();
  playerpos = static_cast<object::C_Transform*>
    (m_player->Find_Component(TRANSFORM))->Get_Position();
  if (abs(playerpos.y - enemypos.y) <= 6)
    m_aistate = ENRAGE;
}

/******************************************************************************/
/*!
  Function to check the tile to stop movement
*/
/******************************************************************************/
bool C_AI::CheckTile()
{
  int x;
  math::Vec2 enemypos;
  enemypos = static_cast<object::C_BoxCollider*>
    (p_obj->Find_Component(BOXCOLLIDER))->Get_Min();
  x = m_direction ? -1 : (enemypos.x = static_cast<object::C_BoxCollider*>
    (p_obj->Find_Component(BOXCOLLIDER))->Get_Max().x, 1);

  if ((!m_map[((int)enemypos.y - 1) * m_width + (int)enemypos.x + x])
    || (m_map[((int)enemypos.y) * m_width + (int)enemypos.x + x]))
  {
    return true;
  }
  return false;
}

/******************************************************************************/
/*!
  Function to check the tile to stop movement
*/
/******************************************************************************/
bool C_AI::CheckTile2()
{
  math::Vec2 enemypos = static_cast<object::C_Transform*>
    (p_obj->Find_Component(TRANSFORM))->Get_Position();
  if (m_map[((int)enemypos.y + 2) * m_width + (int)enemypos.x])
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
void C_AI::CollisionStarted(object::C_GameObject* p_otherobject)
{
  if (p_otherobject->Get_Trait() == T_BULLET)
  {
    m_hit = true;
    events::C_EventDispatcher::DispatchEvent("Enrage");
    --n_health;
    if (n_health <= 0)
      Death();
    return;
  }
  if (p_otherobject->Get_Trait() == T_SHOTGUNBULLET && !m_shotgunhit)
  {
    m_hit = true;
    m_shotgunhit = true;
    events::C_EventDispatcher::DispatchEvent("Enrage");
    if (m_direction)
      AddAcceleration(1000.0f);
    else
      AddAcceleration(-1000.0f);
    n_health -= 5;
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
  (static_cast<object::C_AI*>(p_event.Object()->Find_Component(AI))->
  CollisionStarted(p_event.Other_Object()));
}

/******************************************************************************/
/*!
  Function to call Update
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject* p_object)
{
  (static_cast<object::C_AI*>(p_object->Find_Component(AI))->Update());
}

/******************************************************************************/
/*!
 Function to call Enrage
*/
/******************************************************************************/
void MakeEnrage(object::C_GameObject* p_object)
{
  (static_cast<object::C_AI*>(p_object->Find_Component(AI))->Enrage());
}
}

