/******************************************************************************/
/*!
\file_name        AIScreamer.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the implementation for the class C_AIScreamer

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "AIScreamer.h"

// FORWARD DECLARE ALL FUNCTIONS THAT ARE GOING TO BE ADDED
namespace
{
  void OnCollisionStarted(events::C_CollisionEvent p_event);
  void OnLogicUpdate(object::C_GameObject* p_object);
  void ShootStop(object::C_GameObject* p_object);
  void SpawnSpitParticle(object::C_GameObject* p_object);
}

namespace object
{

/******************************************************************************/
/*!
  The Non-Default constructor for C_AIScreamer
*/
/******************************************************************************/
C_AIScreamer::C_AIScreamer(C_GameObject *p_obj, C_GameObject * player, 
  COLLISIONMAP * p_map, int width, AISTATE wander, int hp)
  : C_Component{ p_obj, AISCREAM }, m_aistate{ wander }, n_health{ hp }, 
  m_timemax{}, m_time{}, m_deathanimation{ 0 },
  m_direction{ false }, m_player{ player }, m_screamtime{}, 
  m_scream{ false }, m_map{ p_map }, m_width{ width },
  m_hitanimation{}, m_hit{ false }
{
}

/******************************************************************************/
/*!
  Function to Connect to events
*/
/******************************************************************************/
void C_AIScreamer::Connect()
{
  events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
  events::C_EventDispatcher::Connect("ShootComplete", ShootStop, p_obj);
  events::C_EventDispatcher::Connect("SpawnSpitParticle", 
    SpawnSpitParticle, p_obj);
  mp_transform = static_cast<C_Transform*>(p_obj->Find_Component(TRANSFORM));
}

/******************************************************************************/
/*!
  Function to Clone C_AIScreamer
*/
/******************************************************************************/
C_AIScreamer *C_AIScreamer::Clone() const
{
  return new C_AIScreamer{ p_obj, m_player, m_map, m_width, 
  m_aistate, n_health };
}

/******************************************************************************/
/*!
  Update Function for C_AIScreamer
*/
/******************************************************************************/
void C_AIScreamer::Update()
{
  // Stop update when game is paused
  if(utilities::C_OptionsManager::Get_Pause())
    return;

  object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>
    (p_obj->Find_Component(SPRITE));
  math::Vec2 enemypos, playerpos;
  enemypos = static_cast<object::C_Transform*>
    (p_obj->Find_Component(TRANSFORM))->Get_Position();
  playerpos = static_cast<object::C_Transform*>
    (m_player->Find_Component(TRANSFORM))->Get_Position();
  m_time += utilities::C_Timer::Get_dt();

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
      m_checktime = 0;
      m_shotgunhit = false;
    }
    return;
  }

  // Check the state of AI
  m_aistate = CheckState(m_aistate);

  float velocityx = static_cast<object::C_Rigidbody*>
  (p_obj->Find_Component(RIGIDBODY))->Get_Velocity_Global().x;
  bool flipx = p_sprite->Get_FlipX();


  // Flips sprite based on direction of movement
  if (velocityx < 0 && !flipx)
  {
    mp_transform->Set_Dir(180.0f);
    static_cast<C_Transform*>(mp_spitsys->Find_Component(TRANSFORM))
    ->Set_Dir(180.0f);
    p_sprite->Set_FlipX(true);
  }

  if (velocityx > 0 && flipx)
  {
    mp_transform->Set_Dir(0.0f);
    static_cast<C_Transform*>(mp_spitsys->Find_Component(TRANSFORM))
    ->Set_Dir(0.0f);
    p_sprite->Set_FlipX(false);
  }

  // Different actions based on which state the ai is
  switch (m_aistate)
  {
  case STATIC:
    m_hit ? p_sprite->Set_Texture("ScreamerIdleRed") 
    : p_sprite->Set_Texture("ScreamerIdle");
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
    m_hit ? p_sprite->Set_Texture("ScreamerWanderRed") 
    : p_sprite->Set_Texture("ScreamerWander");
    // Stop movement when at edges or facing walls
    if (CheckTile())
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
  case SCREAM:
    m_hit ? p_sprite->Set_Texture("ScreamerScreamRed") 
    : p_sprite->Set_Texture("ScreamerScream");
    m_direction ? AddAcceleration(-10.0f) : AddAcceleration(10.0f);
    // Sent events to scream and enrage all zombies
    if (!m_scream)
    {
      m_scream = true;
      events::C_EventDispatcher::DispatchEvent("Enrage");
      events::C_EventDispatcher::DispatchEvent("Scream");
    }
    // Set to shoot after screaming
    else 
    {
      m_screamtime += utilities::C_Timer::Get_dt();
      if (m_screamtime > 1)
      {
        m_aistate = SHOOT;
        m_scream = false;
        m_screamtime = 0;
      }
    }
    break;
  case SHOOT:
    // Send event to shoot
    m_hit ? p_sprite->Set_Texture("ScreamerShootRed") 
    : p_sprite->Set_Texture("ScreamerShoot");
    events::C_EventDispatcher::DispatchEvent("ScreamerShoot");
    break;
  }

}

/******************************************************************************/
/*!
  Function to get C_AIScreamer
*/
/******************************************************************************/
C_AIScreamer *C_AIScreamer::Actual()
{
  return this;
}

/******************************************************************************/
/*!
  Function to call when AIScreamer is dead
*/
/******************************************************************************/
void C_AIScreamer::Death()
{
  auto p_sprite = static_cast<object::C_Sprite*>
  (p_obj->Find_Component(SPRITE));
  auto p_box = static_cast<object::C_BoxCollider*>
  (p_obj->Find_Component(BOXCOLLIDER));
  auto p_rigidbody = static_cast<object::C_Rigidbody*>
  (p_obj->Find_Component(RIGIDBODY));
  m_deathanimation = 0;
  m_dead = true;
  // Set next state as death
  m_aistate = DEATH;
  // Set collider and gravity to false
  p_box->Set_Active(false);
  p_rigidbody->Set_Gravity(false);
  p_rigidbody->Set_VelocityX(0);
  p_sprite->Set_Texture("ScreamerDeath");

}

/******************************************************************************/
/*!
  Function to Check State of AI
*/
/******************************************************************************/
AISTATE C_AIScreamer::CheckState(AISTATE m_state)
{
  if (m_state == SHOOT || m_state == DEATH)
    return m_state;
  math::Vec2 enemypos, playerpos;
  enemypos = static_cast<object::C_Transform*>
  (p_obj->Find_Component(TRANSFORM))->Get_Position();
  playerpos = static_cast<object::C_Transform*>
  (m_player->Find_Component(TRANSFORM))->Get_Position();
  m_direction = playerpos.x - enemypos.x > 0 ? false : true;
  // Set to scream when the dist between player and ai is less than 8
  if (abs(playerpos.y - enemypos.y) <= 3)
  {
    if (abs(playerpos.x - enemypos.x) <= 8)
      return SCREAM;
  }
  return m_state;
}

/******************************************************************************/
/*!
  Function to Check State of AIScreamer
*/
/******************************************************************************/
void C_AIScreamer::AddAcceleration(float f_speed)
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
void C_AIScreamer::SetMaxTime(float m_maxtime)
{
  m_timemax = m_maxtime;
}

/******************************************************************************/
/*!
  Function to Set Direction
*/
/******************************************************************************/
void C_AIScreamer::SetDirection(bool m_setdirection)
{
  m_direction = m_setdirection;
}

/******************************************************************************/
/*!
  Function to Set AI state
*/
/******************************************************************************/
void C_AIScreamer::SetState(AISTATE m_state)
{
  m_aistate = m_state;
}

/******************************************************************************/
/*!
  Function to get pointer to player
*/
/******************************************************************************/
C_GameObject * C_AIScreamer::GetPlayer() const
{
  return m_player;
}

/******************************************************************************/
/*!
  Function to get AI state
*/
/******************************************************************************/
AISTATE C_AIScreamer::GetState() const
{
  return m_aistate;
}

/******************************************************************************/
/*!
  Function to call to reset AI Screamer
*/
/******************************************************************************/
void C_AIScreamer::Reset()
{
  m_scream = false;
  m_screamtime = 0;
  m_time = 0;
  m_aistate = STATIC;
  p_obj->Destroy();
}

/******************************************************************************/
/*!
  Function to call when collision happen
*/
/******************************************************************************/
void C_AIScreamer::CollisionStarted(object::C_GameObject* p_otherobject)
{
  if (p_otherobject->Get_Trait() == T_BULLET)
  {
    m_hit = true;
    --n_health;
    if (n_health <= 0)
      Death();
    else
      m_aistate = SCREAM;
  }
  if (p_otherobject->Get_Trait() == T_SHOTGUNBULLET && !m_shotgunhit)
  {
    m_hit = true;
    m_shotgunhit = true;
    n_health -= 5;
    if (m_direction)
      AddAcceleration(1000.0f);
    else
      AddAcceleration(-1000.0f);
    if (n_health <= 0)
      Death();
    else
      m_aistate = SCREAM;

  }
}

/******************************************************************************/
/*!
  Function to Set pointer to player
*/
/******************************************************************************/
void C_AIScreamer::Set_Player(C_GameObject * p_player)
{
  m_player = p_player;
}

/******************************************************************************/
/*!
  Function to Set AI state to static
*/
/******************************************************************************/
void C_AIScreamer::ScreamStop()
{
  m_aistate = STATIC;
}

/******************************************************************************/
/*!
  Function to check the tile to stop movement
*/
/******************************************************************************/
bool C_AIScreamer::CheckTile()
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
  (static_cast<object::C_AIScreamer*>(p_event.Object()->
  Find_Component(AISCREAM))->CollisionStarted(p_event.Other_Object()));
}

/******************************************************************************/
/*!
  Function to call Update
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject* p_object)
{
  (static_cast<object::C_AIScreamer*>(p_object->Find_Component(AISCREAM))
  ->Update());
}

/******************************************************************************/
/*!
  Function to stop shooting
*/
/******************************************************************************/
void ShootStop(object::C_GameObject* p_object)
{
  (static_cast<object::C_AIScreamer*>(p_object->Find_Component(AISCREAM))
  ->ScreamStop());
}

/******************************************************************************/
/*!
  Function to spawn spit Particle
*/
/******************************************************************************/
void SpawnSpitParticle(object::C_GameObject* p_object)
{
  if (p_object->Get_Active())
  {
    object::C_GameObject *p_spitsys = static_cast<object::C_AIScreamer *>
    (p_object->Find_Component(AISCREAM))->mp_spitsys;
    object::C_Transform *p_transform = static_cast<object::C_Transform *>
    (p_spitsys->Find_Component(TRANSFORM));
    object::C_ParticleSystem *p_system = 
    static_cast<object::C_ParticleSystem *>
    (p_spitsys->Find_Component(PARTICLESYSTEM));

    object::C_Transform *p_screamertrans = 
    static_cast<object::C_Transform *>
    (p_object->Find_Component(TRANSFORM));

    p_transform->Set_Position(p_screamertrans->Get_Position().x - 1.0f, 
    p_screamertrans->Get_Position().y - 0.7f);
    p_system->Emit();
  }
}
}

