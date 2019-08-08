/******************************************************************************/
/*!
\file_name        AIBoss.cpp
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the member function definitions of the AIBoss
    class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/

#include "AIBoss.h"

namespace
{
  // Event related functions
  void BossKill                  (object::C_AIBoss *p_boss);
  void PlayPreLeapAnimation      (object::C_AIBoss *p_boss);
  void PlayPreThrowAnimation     (object::C_AIBoss *p_boss);
  void DestroyBoss               (object::C_GameObject *p_obj);
  void OnLogicUpdate             (object::C_GameObject *p_obj);
  void ActivateGravity           (object::C_GameObject *p_obj);
  void FlipBossSprite            (object::C_GameObject *p_obj);
  void OnCollisionStarted        (events::C_CollisionEvent p_event);
  void BossSpriteLeap            (object::C_Sprite *p_sprite, object::C_AIBoss *p_boss);
  void BossSpriteThrow           (object::C_Sprite *p_sprite, object::C_AIBoss *p_boss);
  void DeathAnimation            (object::C_Sprite *p_sprite, object::C_AIBoss *p_boss);
  void IdleSprite                (object::C_Sprite *p_sprite, object::C_AIBoss *p_boss);
  void TurnRed                   (object::C_Sprite *p_sprite, object::C_AIBoss *p_boss);
  void RevertRed                 (object::C_Sprite *p_sprite, object::C_AIBoss *p_boss);
  void BossSpriteRoar            (object::C_Sprite *p_sprite, object::C_AIBoss *p_boss);

  
  // Event dispatching functions
  EVENTDISPATCHFUNCTION(ActivateGravity);
  EVENTDISPATCHFUNCTION(FlipBossSprite);
  EVENTDISPATCHFUNCTION(DestroyBoss);
  EVENTDISPATCHFUNCTION(RoarSprite);
  EVENTDISPATCHFUNCTION(LeapSprite);
  EVENTDISPATCHFUNCTION(ThrowSprite);
  EVENTDISPATCHFUNCTION(DeathAnimation);
  EVENTDISPATCHFUNCTION(PreLeap);
  EVENTDISPATCHFUNCTION(PreThrow);
  EVENTDISPATCHFUNCTION(BossKill);
  EVENTDISPATCHFUNCTION(BossSummon);
  EVENTDISPATCHFUNCTION(BossThrow);
  EVENTDISPATCHFUNCTION(Enrage);
  EVENTDISPATCHFUNCTION(DisplayWinMenu);
  EVENTDISPATCHFUNCTION(IdleSprite);
  EVENTDISPATCHFUNCTION(TurnRed);
  EVENTDISPATCHFUNCTION(RevertRed);
  EVENTDISPATCHFUNCTION(AIBossSoundEffect);
  EVENTDISPATCHFUNCTION(AIBossBruteLandingSoundEffect);
  EVENTDISPATCHFUNCTION(AIBossBruteDeathSoundEffect);
}

namespace object
{
/******************************************************************************/
/*!
  The non default constructor for a AIBoss object
 */
/******************************************************************************/
C_AIBoss::C_AIBoss(C_GameObject *p_obj, C_GameObject *p_player, BOSSSTATE spawn, int n_hp)
: C_Component{ p_obj, AIBOSS }, m_player{ p_player }, m_state{ spawn }, 
  m_health{ n_hp }
{
}

/******************************************************************************/
/*!
  The connect function of the AIBoss class
 */
/******************************************************************************/
void C_AIBoss::Connect()
{
  auto p_sprite = static_cast<C_Sprite*>(p_obj->Find_Component(SPRITE));
  auto p_boss   = static_cast<C_AIBoss*>(p_obj->Find_Component(AIBOSS));

  events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
  events::C_EventDispatcher::Connect("ActivateGravity",  ActivateGravity,       p_obj);
  events::C_EventDispatcher::Connect("FlipBossSprite",   FlipBossSprite,        p_obj);
  events::C_EventDispatcher::Connect("DestroyBoss",      DestroyBoss,           p_obj);
  events::C_EventDispatcher::Connect("PreLeap",          PlayPreLeapAnimation,  p_boss);
  events::C_EventDispatcher::Connect("PreThrow",         PlayPreThrowAnimation, p_boss);
  events::C_EventDispatcher::Connect("BossKill",         BossKill,              p_boss);
  events::C_EventDispatcher::Connect("RoarSprite",       BossSpriteRoar,        p_sprite, p_boss);
  events::C_EventDispatcher::Connect("LeapSprite",       BossSpriteLeap,        p_sprite, p_boss);
  events::C_EventDispatcher::Connect("ThrowSprite",      BossSpriteThrow,       p_sprite, p_boss);
  events::C_EventDispatcher::Connect("DeathAnimation",   DeathAnimation,        p_sprite, p_boss);
  events::C_EventDispatcher::Connect("IdleSprite",       IdleSprite,            p_sprite, p_boss);
  events::C_EventDispatcher::Connect("TurnRed",          TurnRed,               p_sprite, p_boss);
  events::C_EventDispatcher::Connect("RevertRed",        RevertRed,             p_sprite, p_boss);
}

/******************************************************************************/
/*!
  Sets the player pointer on the AIBoss object
 */
/******************************************************************************/
void C_AIBoss::Set_Player(C_GameObject * p_player)
{
  m_player = p_player;
}

/******************************************************************************/
/*!
  Clones the AIBoss object
 */
/******************************************************************************/
C_AIBoss *C_AIBoss::Clone() const
{
  return new C_AIBoss{ p_obj, m_player };
}

/******************************************************************************/
/*!
  Activates gravity on the boss object
 */
/******************************************************************************/
void C_AIBoss::Gravity()
{
  auto p_rigid = static_cast<object::C_Rigidbody*>
                 (p_obj->Find_Component(RIGIDBODY));

  p_rigid->Set_Gravity(true);
}

/******************************************************************************/
/*!
  The leap action sequence of the AIBoss
 */
/******************************************************************************/
void C_AIBoss::Leap()
{
  // Create two separate action sequences to occur concurrently
  actions::C_ActionSequence actionseq;
  actions::C_ActionSequence actionseq2;
  
  // Initialize variables
  auto p_transform = static_cast<object::C_Transform*>
                     (p_obj->Find_Component(TRANSFORM));
  auto p_rigid     = static_cast<object::C_Rigidbody*>
                     (p_obj->Find_Component(RIGIDBODY));
  auto p_sprite    = static_cast<object::C_Sprite*>
                     (p_obj->Find_Component(SPRITE));
  
  switch(LeapCount)
  {
  case(0):
    p_sprite->Set_FlipX(true);

    actions::AddToSequence(actionseq,
                           p_transform->Get_Transform(),
                           math::Vec2{-15.0f, 20.0f},
                           1.0);
    actions::Wait(actionseq, 0.2);
    ++LeapCount;
    break;
  case(1):
    p_sprite->Set_FlipX(false);
    actions::AddToSequence(actionseq,
                           p_transform->Get_Transform(),
                           math::Vec2{15.0f, 20.0f},
                           1.0);
    actions::Wait(actionseq, 0.2);
    ++LeapCount;
    break;
  case(2):
    p_sprite->Set_FlipX(true);
    actions::AddToSequence(actionseq,
                           p_transform->Get_Transform(),
                           math::Vec2{-25.0f, 15.0f},
                           1.0);
    actions::Wait(actionseq, 0.1);
    ++LeapCount;
    break;
  case(3):
    p_sprite->Set_FlipX(false);
    actions::AddToSequence(actionseq,
                           p_transform->Get_Transform(),
                           math::Vec2{15.0f, 20.0f},
                           1.0);
    actions::Wait(actionseq, 0.2);
    LeapCount  = 0;
    m_substate = EXIT;
    break;
  }
  
  actions::AddToSequence(actionseq2, DispatchActivateGravity);
  actions::AddToSequence(actionseq,  utilities::DispatchCameraShakeEvent);
  actions::AddToSequence(actionseq,  DispatchAIBossBruteLandingSoundEffect);
  
  // Register sequences
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq2);
  
  p_rigid->Set_Gravity(false);
  p_rigid->Set_VelocityY(0);
}

/******************************************************************************/
/*!
  The JumpToPlatform action sequence for the AIBoss
 */
/******************************************************************************/
void C_AIBoss::JumpToPlatform()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Init variables
  auto p_transform = static_cast<object::C_Transform*>
                     (p_obj->Find_Component(TRANSFORM));
  auto p_rigid     = static_cast<object::C_Rigidbody*>
                     (p_obj->Find_Component(RIGIDBODY));
  
  // Add desired actions to sequences
  actions::AddToSequence(actionseq, DispatchAIBossSoundEffect);
  actions::AddToSequence(actionseq, DispatchPreLeap);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq,
                         p_transform->Get_Transform(),
                         math::Vec2{5.0f, 10.0f},
                         0.5);
  actions::AddToSequence(actionseq,
                         p_transform->Get_Transform(),
                         math::Vec2{5.0f, -6.0f},
                         0.5);
  actions::AddToSequence(actionseq, DispatchActivateGravity);
  actions::AddToSequence(actionseq, DispatchFlipBossSprite);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);

  p_rigid->Set_Gravity(false);
  p_rigid->Set_VelocityY(0);
}

/******************************************************************************/
/*!
  The Summon actions equence for the AIBoss class
 */
/******************************************************************************/
void C_AIBoss::Summon()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to the sequence
  actions::Wait(actionseq, 3);
  for(int i = 0; i < 3; ++i)
  {
    actions::AddToSequence(actionseq, DispatchBossSummon);
    actions::Wait(actionseq, 0.25);
  }
  actions::AddToSequence(actionseq, DispatchBossSummon);
  actions::Wait(actionseq, 0.7);
  actions::AddToSequence(actionseq, DispatchEnrage);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The ProjectileAttack action sequence generating function for the AIBoss
  object
 */
/******************************************************************************/
void C_AIBoss::ProjectileAttack()
{
  
  auto p_transform = static_cast<object::C_Transform*>
                     (p_obj->Find_Component(TRANSFORM))->Get_Transform();
  
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to the sequence
  actions::Wait(actionseq, 5);
  actions::AddToSequence(actionseq, DispatchAIBossSoundEffect);
  actions::AddToSequence(actionseq, DispatchPreThrow);
  actions::Wait(actionseq, 2.0);
  for(int i = 0; i < 30; ++i)
  {
    actions::AddToSequence(actionseq, DispatchThrowSprite);
    actions::AddToSequence(actionseq, DispatchBossThrow);
    actions::Wait(actionseq, 0.28);
  }
  actions::AddToSequence(actionseq, DispatchPreLeap);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq, p_transform, math::Vec2{-5.0, 10.0}, 1.0);
  actions::AddToSequence(actionseq, DispatchFlipBossSprite);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The update function of the AIBoss object
 */
/******************************************************************************/
void C_AIBoss::Update()
{
  // Skip this if the game is paused
  if(utilities::C_OptionsManager::Get_Pause())
  {
    return;
  }
  
  // Static local variables
  static double time = 0;
  static double checktime = 0;
  time += utilities::C_Timer::Get_dt();
  
  // If the boss was hit by the shotgun
  if(m_shotgunhit)
  {
    checktime += utilities::C_Timer::Get_dt();
    if(checktime > 1)
    {
      m_shotgunhit = false;
      checktime = 0;
    }
  }
  
  // The FSM for the Boss
  switch(m_state)
  {
  case(SPAWN):
    switch(m_substate)
    {
    case(ENTER):
      events::C_EventDispatcher::DispatchEvent("CameraLock");
      AS_SpawnSequence();
      m_substate = UPDATE;
      break;
    case(UPDATE):
      m_substate = EXIT;
      break;
    case(EXIT):
      m_substate = ENTER;
      time = 0;
      m_state = JUMP;
      break;
    }
    break;
  case(JUMP):
    switch(m_substate)
    {
    case(ENTER):
      PreLeapAnimation();
      m_substate = UPDATE;
      time = -2.0;
      break;
    case(UPDATE):
      if(time > 2.0)
      {
        time = 0;
        Leap();
      }
      break;
    case(EXIT):
      if(time > 2.0)
      {
        m_state = ROAR;
        m_substate = ENTER;
      }
      break;
    }
    break;
  case(ROAR):
    switch(m_substate)
    {
    case(ENTER):
      JumpToPlatform();
      Summon();
      m_substate = UPDATE;
      break;

    case(UPDATE):
      time = 0;
      ProjectileAttack();
      m_substate = EXIT;
      break;
    case(EXIT):
      if(time > 17)
      {
        m_state = JUMP;
        m_substate = ENTER;
      }
      break;
    }
    break;
  case(DEATH):
    switch(m_substate)
    {
    case(ENTER):
      AS_DeathSequence();
      m_substate = UPDATE;
      break;
    case(UPDATE):
      break;
    case(EXIT):
      break;
    }
  }
}

/******************************************************************************/
/*!
  Returns a pointer to this object
 */
/******************************************************************************/
C_AIBoss * C_AIBoss::Actual()
{
  return const_cast<C_AIBoss*>(this);
}

/******************************************************************************/
/*!
  The PreLeapAnimation action sequence generation function
 */
/******************************************************************************/
void C_AIBoss::PreLeapAnimation()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, DispatchAIBossSoundEffect);
  actions::AddToSequence(actionseq, DispatchRoarSprite);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq, DispatchLeapSprite);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The PreThrowAnimation action sequence generation function
 */
/******************************************************************************/
void C_AIBoss::PreThrowAnimation()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, DispatchRoarSprite);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq, DispatchThrowSprite);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The Death actionsequence for the AIBoss object
 */
/******************************************************************************/
void C_AIBoss::AS_DeathSequence()
{
  // Create new action sequence
  actions::C_ActionSequence actionseq;
  actions::C_ActionSequence actionseq2;

  auto p_opacity = static_cast<object::C_Sprite*>
                   (p_obj->Find_Component(SPRITE))->Get_Opacity_Ptr();
  
  // Add actions to sequence
  actions::AddToSequence(actionseq, DispatchAIBossBruteDeathSoundEffect);
  actions::AddToSequence(actionseq, DispatchDeathAnimation);
  actions::Wait(actionseq, 0.8);
  actions::AddToSequence(actionseq2, p_opacity, -1.0f, 1.0);
  actions::AddToSequence(actionseq, DispatchDestroyBoss);
  actions::AddToSequence(actionseq2, p_opacity, 1.0f, 1.0);
  actions::AddToSequence(actionseq, DispatchDisplayWinMenu);
  
  // Register action sequences
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq2);
}

/******************************************************************************/
/*!
  The Spawn actionsequence for the AIBoss object
 */
/******************************************************************************/
void C_AIBoss::AS_SpawnSequence()
{
  // Create new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to sequence
  actions::Wait(actionseq, 0);
  actions::AddToSequence(actionseq, utilities::DispatchBossCameraShakeEvent);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  Sets the current health to 1
 */
/******************************************************************************/
  void C_AIBoss::Kill()
  {
    m_health = 1;
  }

/******************************************************************************/
/*!
  The action sequence generating function that causes the boss to flicker red
 */
/******************************************************************************/
void C_AIBoss::RedSprite()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add the actions to the sequence
  actions::AddToSequence(actionseq, DispatchTurnRed);
  actions::AddToSequence(actionseq, DispatchRevertRed);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The Init Function of the Boss
 */
/******************************************************************************/
void C_AIBoss::Init()
{
  // Initialize variables
  m_health   = BOSS_MAX_HEALTH;
  m_state    = SPAWN;
  m_substate = ENTER;
}

/******************************************************************************/
/*!
  The Death Function of the boss
 */
/******************************************************************************/
void C_AIBoss::Death()
{
  // Clear actions and set variables
  actions::C_ActionDispatcher::Clear();
  m_state    = DEATH;
  m_substate = ENTER;
}

/******************************************************************************/
/*!
  The CollisionStarted function of the AIBoss
 */
/******************************************************************************/
void C_AIBoss::CollisionStarted(object::C_GameObject* p_otherobject)
{
  // If the boss is already dead, skip the update
  if(m_dead)
  {
    return;
  }
  
  // If the boss is hit by a bullet
  if(p_otherobject->Get_Trait() == T_BULLET)
  {
    --m_health;
    RedSprite();
    if(m_health <= 0)
    {
      m_dead = true;
      Death();
    }
  }
  // If the boss is hit by a shotgun
  else if(p_otherobject->Get_Trait() == T_SHOTGUNBULLET && !m_shotgunhit)
  {
    m_shotgunhit = true;
    m_health -= 5;
    RedSprite();
    if(m_health <= 0)
    {
      m_dead = true;
      Death();
    }
  }
}
}

namespace
{

/******************************************************************************/
/*!
  Helper function to call PreLeapAnimation member function
 */
/******************************************************************************/
  void PlayPreLeapAnimation(object::C_AIBoss *p_boss)
  {
    p_boss->PreLeapAnimation();
  }

/******************************************************************************/
/*!
  Helper function to call PlayPreThrowAnimation member function
 */
/******************************************************************************/
  void PlayPreThrowAnimation(object::C_AIBoss * p_boss)
  {
    p_boss->PreThrowAnimation();
  }
  
/******************************************************************************/
/*!
  The Collision Event function that calls CollisionStarted on the object
 */
/******************************************************************************/
  void OnCollisionStarted(events::C_CollisionEvent p_event)
  {
    static_cast<object::C_AIBoss*>
    (p_event.Object()->Find_Component(AIBOSS))->
    CollisionStarted(p_event.Other_Object());
  }
  
/******************************************************************************/
/*!
  Helper function to call Update member function
 */
/******************************************************************************/
  void OnLogicUpdate(object::C_GameObject *p_obj)
  {
    static_cast<object::C_AIBoss*>(p_obj->Find_Component(AIBOSS))->Update();
  }
/******************************************************************************/
/*!
  Sets the Roar Sprite on the boss
 */
/******************************************************************************/
  void BossSpriteRoar(object::C_Sprite *p_sprite, object::C_AIBoss *p_boss)
  {
    p_sprite->Set_Texture("BossRoar");
    p_boss->m_sprite = static_cast<object::C_AIBoss::CURRENTSPRITE>(1);
  }
  
/******************************************************************************/
/*!
  Sets the Leap Sprite on the boss
 */
/******************************************************************************/
  void BossSpriteLeap(object::C_Sprite *p_sprite, object::C_AIBoss *p_boss)
  {
    p_sprite->Set_Texture("BossCharge");
    p_boss->m_sprite = static_cast<object::C_AIBoss::CURRENTSPRITE>(2);
  }
  
/******************************************************************************/
/*!
  Sets the throw sprite on the boss
 */
/******************************************************************************/
  void BossSpriteThrow(object::C_Sprite *p_sprite, object::C_AIBoss *p_boss)
  {
    p_sprite->Set_Texture("BossThrow");
    p_boss->m_sprite = static_cast<object::C_AIBoss::CURRENTSPRITE>(3);
  }

/******************************************************************************/
/*!
  Flips the boss sprite across the Y Axis
 */
/******************************************************************************/
  void FlipBossSprite(object::C_GameObject * p_obj)
  {
    auto p_sprite = static_cast<object::C_Sprite*>
                    (p_obj->Find_Component(SPRITE));
    bool *p_flip  = p_sprite->Get_FlipPtr();

    *p_flip = *p_flip ? false : true;
  }
  
/******************************************************************************/
/*!
  Helper Function that calls the Gravity function on the boss
 */
/******************************************************************************/
  void ActivateGravity(object::C_GameObject * p_obj)
  {
    auto p_boss = static_cast<object::C_AIBoss*>(p_obj->Find_Component(AIBOSS));

    p_boss->Gravity();
  }

/******************************************************************************/
/*!
  Sets the Boss Death Animation
 */
/******************************************************************************/
  void DeathAnimation(object::C_Sprite *p_sprite, object::C_AIBoss *p_boss)
  {
    p_sprite->Set_Texture("BossDeath");
    p_boss->m_sprite = static_cast<object::C_AIBoss::CURRENTSPRITE>(4);
  }

/******************************************************************************/
/*!
  Helper function to call the cheat Function that sets the boss' health to 1
 */
/******************************************************************************/
  void BossKill(object::C_AIBoss * p_boss)
  {
    p_boss->Kill();
  }

/******************************************************************************/
/*!
  Sets the boss sprite to the idle sprite
 */
/******************************************************************************/
  void IdleSprite(object::C_Sprite * p_sprite, object::C_AIBoss * p_boss)
  {
    p_sprite->Set_Texture("BossIdle");
    p_boss->m_sprite = static_cast<object::C_AIBoss::CURRENTSPRITE>(0);
  }
  
/******************************************************************************/
/*!
  Turns the Boss current sprite red
 */
/******************************************************************************/
  void TurnRed(object::C_Sprite * p_sprite, object::C_AIBoss * p_boss)
  {
    // Alias
    using c_sprite = object::C_AIBoss::CURRENTSPRITE;
    
    // Set the texture based on the current texture
    switch(p_boss->m_sprite)
    {
    case(c_sprite::IDLE):
      p_sprite->Set_Texture("BossIdleRed");
      break;
    case(c_sprite::ROARSPRITE):
      p_sprite->Set_Texture("BossRoarRed");
      break;
    case(c_sprite::LEAPSPRITE):
      p_sprite->Set_Texture("BossChargeRed");
      break;
    case(c_sprite::THROWSPRITE):
      p_sprite->Set_Texture("BossThrowRed");
      break;
    default:
      return;
    }
  }

/******************************************************************************/
/*!
  Reverts the Boss current sprite to normal
 */
/******************************************************************************/
  void RevertRed(object::C_Sprite * p_sprite, object::C_AIBoss * p_boss)
  {
    // Alias
    using c_sprite = object::C_AIBoss::CURRENTSPRITE;
    
    // Set the texture based on the current texture
    switch(p_boss->m_sprite)
    {
    case(c_sprite::IDLE):
      p_sprite->Set_Texture("BossIdle");
      break;
    case(c_sprite::ROARSPRITE):
      p_sprite->Set_Texture("BossRoar");
      break;
    case(c_sprite::LEAPSPRITE):
      p_sprite->Set_Texture("BossCharge");
      break;
    case(c_sprite::THROWSPRITE):
      p_sprite->Set_Texture("BossThrow");
      break;
    default:
      return;
    }
  }

/******************************************************************************/
/*!
  Destroys the boss game object
 */
/******************************************************************************/
  void DestroyBoss(object::C_GameObject* p_obj)
  {
    p_obj->Destroy();
  }
}