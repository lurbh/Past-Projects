/******************************************************************************/
/*!
\file_name        AIBossStealth.cpp
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the member function definitions of the AIBossStealth
        class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/
#include "AIBossStealth.h"

namespace
{
  // Event connected functions
  void OnLogicUpdate                (object::C_GameObject *p_obj);
  void DestroyBoss                  (object::C_GameObject* p_obj);
  void BossKill                     (object::C_AIBossStealth *p_boss);
  void OnCollisionStarted           (events::C_CollisionEvent event);
  void ActivateCollider             (object::C_BoxCollider *p_box);
  void DeactivateCollider           (object::C_BoxCollider *p_box);
  void EnableGravity                (object::C_Rigidbody *p_rigid);
  void DisableGravity               (object::C_Rigidbody *p_rigid);
  void EnableFlipX                  (object::C_Sprite *p_sprite);
  void DisableFlipX                 (object::C_Sprite *p_sprite);
  void EnableFlipY                  (object::C_Sprite *p_sprite);
  void DisableFlipY                 (object::C_Sprite *p_sprite);
  void SetDeathAnimation            (object::C_Sprite *p_sprite);
  void DeathAnimation               (object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss);
  void SetIdleAnimation             (object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss);
  void SetFlickerFadeAnimation      (object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss);
  void SetFlickerAttackAnimation    (object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss);
  void SetPoundAnimation            (object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss);
  void TurnRed                      (object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss);
  void RevertRed                    (object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss);
  
  // Event dispatching functions
  EVENTDISPATCHFUNCTION(DisplayWinMenu);
  EVENTDISPATCHFUNCTION(DeathAnimation);
  EVENTDISPATCHFUNCTION(DestroyBoss);
  EVENTDISPATCHFUNCTION(SpawnAnimation);
  EVENTDISPATCHFUNCTION(IdleAnimation);
  EVENTDISPATCHFUNCTION(StateEnterAnimation);
  EVENTDISPATCHFUNCTION(FlickerFadeAnimation);
  EVENTDISPATCHFUNCTION(FlickerPreAttackAnimation);
  EVENTDISPATCHFUNCTION(FlickerAttackAnimation);
  EVENTDISPATCHFUNCTION(PoundAnimation);
  EVENTDISPATCHFUNCTION(PoundParticleSpawn);
  EVENTDISPATCHFUNCTION(ActivateCollider);
  EVENTDISPATCHFUNCTION(DeactivateCollider);
  EVENTDISPATCHFUNCTION(DisableGravity);
  EVENTDISPATCHFUNCTION(EnableGravity);
  EVENTDISPATCHFUNCTION(EnableFlipX);
  EVENTDISPATCHFUNCTION(EnableFlipY);
  EVENTDISPATCHFUNCTION(DisableFlipX);
  EVENTDISPATCHFUNCTION(DisableFlipY);
  EVENTDISPATCHFUNCTION(AIBossStealthSoundEffect);
  EVENTDISPATCHFUNCTION(AIBossStealthLandingSoundEffect);
  EVENTDISPATCHFUNCTION(AIBossStealthDeathSoundEffect);
  EVENTDISPATCHFUNCTION(TurnRed);
  EVENTDISPATCHFUNCTION(RevertRed)
}

namespace object
{

/******************************************************************************/
/*!
  The non default constructor of an AIBossStealth object
 */
/******************************************************************************/
  C_AIBossStealth::C_AIBossStealth(C_GameObject * p_obj, math::Matrix3 *player_transform, 
                                   BOSSSTATE spawn, int n_hp)
  : C_Component{ p_obj, AIBOSS }, m_player_transform{ player_transform },
    m_state{ spawn }, m_health{ n_hp }
  {
  }

/******************************************************************************/
/*!
  The setter function that sets the player transform pointer
 */
/******************************************************************************/
  void C_AIBossStealth::Set_Player_Transform(math::Matrix3 * p_transform)
  {
    m_player_transform = p_transform;
  }

/******************************************************************************/
/*!
  Event connection function
 */
/******************************************************************************/
  void C_AIBossStealth::Connect()
  {
    // Initialize variables
    auto p_sprite = static_cast<C_Sprite*>       (p_obj->Find_Component(SPRITE));
    auto p_box    = static_cast<C_BoxCollider*>  (p_obj->Find_Component(BOXCOLLIDER));
    auto p_rigid  = static_cast<C_Rigidbody*>    (p_obj->Find_Component(RIGIDBODY));
    auto p_boss   = static_cast<C_AIBossStealth*>(p_obj->Find_Component(AIBOSS));
  
    // Connect functions to events
    events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
    events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
    events::C_EventDispatcher::Connect("TurnRed",                  TurnRed,                   p_sprite, p_boss);
    events::C_EventDispatcher::Connect("RevertRed",                RevertRed,                 p_sprite, p_boss);
    events::C_EventDispatcher::Connect("DeathAnimation",           DeathAnimation,            p_sprite, p_boss);
    events::C_EventDispatcher::Connect("IdleAnimation",            SetIdleAnimation,          p_sprite, p_boss);
    events::C_EventDispatcher::Connect("FlickerFadeAnimation",     SetFlickerFadeAnimation,   p_sprite, p_boss);
    events::C_EventDispatcher::Connect("FlickerAttackAnimation",   SetFlickerAttackAnimation, p_sprite, p_boss);
    events::C_EventDispatcher::Connect("PoundAnimation",           SetPoundAnimation,         p_sprite, p_boss);
    events::C_EventDispatcher::Connect("EnableFlipX",              EnableFlipX,               p_sprite);
    events::C_EventDispatcher::Connect("DisableFlipX",             DisableFlipX,              p_sprite);
    events::C_EventDispatcher::Connect("EnableFlipY",              EnableFlipY,               p_sprite);
    events::C_EventDispatcher::Connect("DisableFlipY",             DisableFlipY,              p_sprite);
    events::C_EventDispatcher::Connect("ActivateCollider",         ActivateCollider,          p_box);
    events::C_EventDispatcher::Connect("DeactivateCollider",       DeactivateCollider,        p_box);
    events::C_EventDispatcher::Connect("DisableGravity",           DisableGravity,            p_rigid);
    events::C_EventDispatcher::Connect("EnableGravity",            EnableGravity,             p_rigid);
    events::C_EventDispatcher::Connect("DestroyBoss",              DestroyBoss,               p_obj);
    events::C_EventDispatcher::Connect("BossKill",                 BossKill,                  p_boss);
  }

/******************************************************************************/
/*!
  Cheat function that sets the boss health to 1
 */
/******************************************************************************/
  void C_AIBossStealth::Kill()
  {
      m_health = 1;
  }
  
/******************************************************************************/
/*!
  The Update function of the Boss
 */
/******************************************************************************/
  void C_AIBossStealth::Update()
  {
    // If the game is paused, skip the update
    if(utilities::C_OptionsManager::Get_Pause())
    {
      return;
    }
    
    // Static variables
    static double time      = 0;
    static double checktime = 0;
    static int    count     = 0;

    time += utilities::C_Timer::Get_dt();
    
    // If the player was hit by the shotgun
    if (m_shotgunhit)
    {
      checktime += utilities::C_Timer::Get_dt();
      if (checktime > 1)
      {
        m_shotgunhit = false;
        checktime = 0;
      }
    }
    
    // The FSM for the boss
    switch(m_state)
    {
    case(SPAWN):
      switch(m_substate)
      {
      case(ENTER):
        events::C_EventDispatcher::DispatchEvent("CameraLock");
        AS_SpawnAnimation();
        time = 0;
        m_substate = UPDATE;
        break;
      case(UPDATE):
        if(time > 1)
        {
          m_substate = EXIT;
        }
        break;
      case(EXIT):
        m_state = FLICKER;
        m_substate = ENTER;
        time = 5;
        break;
      }
      break;
    case(FLICKER):
      switch(m_substate)
      {
      case(ENTER):
        AS_StateEnterAnimation();
        m_substate = UPDATE;
        break;
      case(UPDATE):
        if(time > 2.5)
        {
          AS_FlickerState();
          time = 0;
          ++count;
          break;
        }
        if(count > NUM_ITERATIONS_FLICKER)
        {
          m_substate = EXIT;
        }
        break;
      case(EXIT):
        actions::C_ActionDispatcher::Clear();
        m_state = FALL;
        m_substate = ENTER;
        time = 10;
        count = 0;
        break;
      }
      break;
    case(FALL):
      switch(m_substate)
      {
      case(ENTER):
        AS_StateEnterAnimation();
        m_substate = UPDATE;
        break;
      case(UPDATE):
        if(time > 4.5)
        {
          AS_FallState();
          time = 0;
          ++count;
        }
        if(count > NUM_ITERATIONS_FALL)
        {
          m_substate = EXIT;
        }
        break;
      case(EXIT):
        actions::C_ActionDispatcher::Clear();
        count = 0;
        time = 5;
        m_state = POUND;
        m_substate = ENTER;
        break;
      }
      break;
    case(POUND):
      switch(m_substate)
      {
      case(ENTER):
        AS_StateEnterAnimation();
        m_substate = UPDATE;
        break;
      case(UPDATE):
        if (time > 3.5)
        {
          AS_PoundState();
          time = 0;
          ++count;
        }
        if (count > NUM_ITERATIONS_POUND)
        {
          m_substate = EXIT;
        }
        break;
      case(EXIT):
        actions::C_ActionDispatcher::Clear();
        count = 0;
        time = 5;
        m_state = FLICKER;
        m_substate = ENTER;
        break;
      }
      break;
    case(DEATH):
      switch(m_substate)
      {
      case(ENTER):
        Death();
        m_substate = UPDATE;
        break;
      case(UPDATE):
        m_substate = EXIT;
        break;
      case(EXIT):
        break;
      }
      break;
    }
  }
  
/******************************************************************************/
/*!
  This function causes the boss to flicker red
 */
/******************************************************************************/
  void C_AIBossStealth::RedSprite()
  {
    // Create a new action sequence
    actions::C_ActionSequence actionseq;
    
    // Add actions to sequence
    actions::AddToSequence(actionseq, DispatchTurnRed);
    actions::AddToSequence(actionseq, DispatchRevertRed);
    
    // Register the action sequence
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  }

/******************************************************************************/
/*!
  The initialize function for the boss
 */
/******************************************************************************/
  void C_AIBossStealth::Init()
  {
    m_health   = BOSS_MAX_HEALTH;
    m_state    = SPAWN;
    m_substate = ENTER;
  }

/******************************************************************************/
/*!
  The death action sequence for the boss
 */
/******************************************************************************/
  void C_AIBossStealth::Death()
  {
    // Create two action sequences
    actions::C_ActionSequence actionseq;
    actions::C_ActionSequence actionseq2;

    auto p_opacity = static_cast<object::C_Sprite*>
                     (p_obj->Find_Component(SPRITE))->Get_Opacity_Ptr();

    // Add actions to the sequences
    actions::AddToSequence(actionseq, DispatchAIBossStealthDeathSoundEffect);
    actions::AddToSequence(actionseq, DispatchDeathAnimation);
    actions::Wait(actionseq, 0.8);
    actions::AddToSequence(actionseq2, p_opacity, -1.0f, 1.0);
    actions::AddToSequence(actionseq, DispatchDestroyBoss);
    actions::AddToSequence(actionseq2, p_opacity, 1.0f, 1.0);
    actions::AddToSequence(actionseq, DispatchDisplayWinMenu);
    
    // Register the action sequences
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq2);
  }
  
/******************************************************************************/
/*!
  The Spawn action sequence for the boss
 */
/******************************************************************************/
  void C_AIBossStealth::AS_SpawnAnimation()
  {
    // Create an action sequence
    actions::C_ActionSequence actionseq;
    
    // Add actions to the sequence
    actions::AddToSequence(actionseq, utilities::DispatchBossCameraShakeEvent);
    actions::AddToSequence(actionseq, DispatchSpawnAnimation);
    actions::Wait(actionseq, 0.5);
    actions::AddToSequence(actionseq, DispatchIdleAnimation);
    actions::AddToSequence(actionseq, DispatchActivateCollider);
    
    // Register the action sequence
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  }

/******************************************************************************/
/*!
  The State enter action sequence
 */
/******************************************************************************/
  void C_AIBossStealth::AS_StateEnterAnimation()
  {
    // Create a new action sequence
    actions::C_ActionSequence actionseq;
    
    // Add actions to the sequence
    actions::Wait(actionseq, 0.5);
    actions::AddToSequence(actionseq, DispatchIdleAnimation);
    
    // Register the action sequence
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  }

/******************************************************************************/
/*!
  The State enter action sequence
 */
/******************************************************************************/
  void C_AIBossStealth::AS_FlickerState()
  {
    // Initialize variables
    auto p_opacity   = static_cast<C_Sprite*>
                       (p_obj->Find_Component(SPRITE))->Get_Opacity_Ptr();
    auto p_transform = static_cast<C_Transform*>
                       (p_obj->Find_Component(TRANSFORM))->Get_Transform();
    auto boss_posX   = &p_transform->m_matrix[0][2];
    
    // Compute the displacement vector from the player to the boss
    math::Vec2 displacement{(m_player_transform->m_matrix[0][2] - *boss_posX) / TILESCALE, 0 };
    
    // Create a nenw action sequence
    actions::C_ActionSequence actionseq;

    // Add actions to the sequence
    actions::AddToSequence(actionseq, DispatchAIBossStealthSoundEffect);
    actions::AddToSequence(actionseq, DispatchFlickerFadeAnimation);
    actions::AddToSequence(actionseq, DispatchDisableGravity);
    actions::Wait(actionseq, 0.1);
    actions::AddToSequence(actionseq, DispatchDeactivateCollider);
    actions::AddToSequence(actionseq, p_opacity, -1.0f, 0.5);
    actions::AddToSequence(actionseq, DispatchFlickerPreAttackAnimation);
    actions::AddToSequence(actionseq, p_transform, displacement, 1.0);
    displacement.x > 0?
    actions::AddToSequence(actionseq, DispatchDisableFlipX):
    actions::AddToSequence(actionseq, DispatchEnableFlipX);
    actions::AddToSequence(actionseq, DispatchActivateCollider);
    actions::Wait(actionseq, 0.1);
    actions::AddToSequence(actionseq, DispatchEnableGravity);
    actions::AddToSequence(actionseq, p_opacity, 1.0f, 0.5);
    actions::AddToSequence(actionseq, DispatchFlickerAttackAnimation);
    
    // Register the action sequence
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  }

/******************************************************************************/
/*!
  The pound state action sequence
 */
/******************************************************************************/
  void C_AIBossStealth::AS_PoundState()
  {
    // Create a new action sequence
    actions::C_ActionSequence actionseq;
    
    // Add actions to the sequence
    actions::AddToSequence(actionseq, DispatchAIBossStealthSoundEffect);
    actions::Wait(actionseq, 0.5);
    actions::AddToSequence(actionseq, DispatchPoundAnimation);
    actions::AddToSequence(actionseq, DispatchAIBossStealthLandingSoundEffect);
    actions::AddToSequence(actionseq, DispatchPoundParticleSpawn);
    actions::Wait(actionseq, 0.5);
    actions::AddToSequence(actionseq, DispatchAIBossStealthLandingSoundEffect);
    actions::AddToSequence(actionseq, DispatchPoundParticleSpawn);
    actions::Wait(actionseq, 0.5);
    actions::AddToSequence(actionseq, DispatchIdleAnimation);
    actions::Wait(actionseq, 0.5);
    
    // Register the action sequence
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  }

/******************************************************************************/
/*!
  The fall state action sequence
 */
/******************************************************************************/
  void C_AIBossStealth::AS_FallState()
  {
    // Initialize variables
    auto p_transform   = static_cast<C_Transform*>
                         (p_obj->Find_Component(TRANSFORM))->Get_Transform();
    auto boss_posX     = &p_transform->m_matrix[0][2];
    auto boss_posY     = &p_transform->m_matrix[1][2];
    auto displacementX = m_player_transform->m_matrix[0][2] - *boss_posX;
    
    // Create a new action sequence
    actions::C_ActionSequence actionseq;
    
    // Add actions to the sequence
    actions::AddToSequence(actionseq, DispatchAIBossStealthSoundEffect);
    actions::AddToSequence(actionseq, DispatchDisableGravity);
    actions::AddToSequence(actionseq, DispatchEnableFlipY);
    actions::AddToSequence(actionseq, boss_posY, 16.0f * TILESCALE, 1.0);
    displacementX > 0.0f?
    actions::AddToSequence(actionseq, DispatchDisableFlipX):
    actions::AddToSequence(actionseq, DispatchEnableFlipX);
    actions::AddToSequence(actionseq, boss_posX, displacementX, 1.0);
    actions::Wait(actionseq, 0.5);
    actions::AddToSequence(actionseq, DispatchAIBossStealthSoundEffect);
    actions::AddToSequence(actionseq, DispatchDisableFlipY);
    actions::AddToSequence(actionseq, DispatchEnableGravity);
    actions::Wait(actionseq, 1.1);
    actions::AddToSequence(actionseq, DispatchAIBossStealthLandingSoundEffect);
    actions::AddToSequence(actionseq, DispatchPoundParticleSpawn);
    
    // Register the action sequence
    actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
  }

/******************************************************************************/
/*!
  The collision resolution function
 */
/******************************************************************************/
  void C_AIBossStealth::CollisionStarted(object::C_GameObject* p_otherobject)
  {
    // If the boss is dead, skip
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
        actions::C_ActionDispatcher::Clear();
        events::C_EventDispatcher::DispatchEvent("ActivateCollider");
        events::C_EventDispatcher::DispatchEvent("ActivateGravity");
        events::C_EventDispatcher::DispatchEvent("DisableFlipY");
        m_state = DEATH;
        m_substate = ENTER;
      }
    }
    
    // If the boss is hit by a shotgun
    if(p_otherobject->Get_Trait() == T_SHOTGUNBULLET && !m_shotgunhit)
    {
      m_shotgunhit = true;
      m_health -= 5;
      RedSprite();

      if(m_health <= 0)
      {
        actions::C_ActionDispatcher::Clear();
        events::C_EventDispatcher::DispatchEvent("ActivateCollider");
        events::C_EventDispatcher::DispatchEvent("ActivateGravity");
        events::C_EventDispatcher::DispatchEvent("DisableFlipY");
        m_state = DEATH;
        m_substate = ENTER;
      }
    }
  }

/******************************************************************************/
/*!
  Returns a pointer to the object
 */
/******************************************************************************/
  C_AIBossStealth * C_AIBossStealth::Actual()
  {
    return this;
  }

/******************************************************************************/
/*!
  Creates a clone of this object and returns a pointer to it
 */
/******************************************************************************/
  C_AIBossStealth * C_AIBossStealth::Clone() const
  {
    return new C_AIBossStealth{p_obj, m_player_transform, SPAWN, m_health};
  }

}

namespace
{
/******************************************************************************/
/*!
  Helper function to call the Update function on this object
 */
/******************************************************************************/
  void OnLogicUpdate(object::C_GameObject *p_obj)
  {
    auto p_boss = static_cast<object::C_AIBossStealth*>(p_obj->Find_Component(AIBOSS));

    p_boss->Update();
  }

/******************************************************************************/
/*!
  Helper function to call collision started on this object
 */
/******************************************************************************/
  void OnCollisionStarted(events::C_CollisionEvent event)
  {
    static_cast<object::C_AIBossStealth *>(event.Object()->Find_Component(AIBOSS))->
                                           CollisionStarted(event.Other_Object());
  }

/******************************************************************************/
/*!
  Sets the spawn animation of the boss
 */
/******************************************************************************/
  void SetSpawnAnimation(object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss)
  {
    SetIdleAnimation(p_sprite, p_boss);
  }

/******************************************************************************/
/*!
  Sets the Idle animation of the boss
 */
/******************************************************************************/
  void SetIdleAnimation(object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss)
  {
    p_sprite->Set_Texture("BossIdle");
    p_boss->m_sprite = object::C_AIBossStealth::CURRENTSPRITE::IDLESPRITE;
  }

/******************************************************************************/
/*!
  Sets the flicker fade animation of the boss
 */
/******************************************************************************/
  void SetFlickerFadeAnimation(object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss)
  {
    p_sprite->Set_Texture("BossFlickerFade");
    p_boss->m_sprite = object::C_AIBossStealth::CURRENTSPRITE::FLICKERFADESPRITE;
  }

/******************************************************************************/
/*!
  Sets the flicker attack animation of the boss
 */
/******************************************************************************/
  void SetFlickerAttackAnimation(object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss)
  {
    p_sprite->Set_Texture("BossFlickerAttack");
    p_boss->m_sprite = object::C_AIBossStealth::CURRENTSPRITE::FLICKERATTACKSPRITE;
  }

/******************************************************************************/
/*!
  Sets the Pound animation of the boss
 */
/******************************************************************************/
  void SetPoundAnimation(object::C_Sprite *p_sprite, object::C_AIBossStealth *p_boss)
  {
    p_sprite->Set_Texture("BossPound");
    p_boss->m_sprite =   object::C_AIBossStealth::CURRENTSPRITE::POUNDSPRITE;
  }

/******************************************************************************/
/*!
  This function turns the boss red
 */
/******************************************************************************/
  void TurnRed(object::C_Sprite * p_sprite, object::C_AIBossStealth * p_boss)
  {
    // Alias
    using c_sprite = object::C_AIBossStealth::CURRENTSPRITE;
    
    // Set the relevant red texture
    switch(p_boss->m_sprite)
    {
    case(c_sprite::IDLESPRITE):
      p_sprite->Set_Texture("BossIdleRed");
      break;
    case(c_sprite::FLICKERFADESPRITE):
      p_sprite->Set_Texture("BossFlickerFadeRed");
      break;
    case(c_sprite::FLICKERATTACKSPRITE):
      p_sprite->Set_Texture("BossFlickerAttackRed");
      break;
    case(c_sprite::POUNDSPRITE):
      p_sprite->Set_Texture("BossPoundRed");
      break;
    default:
      return;
    }
  }

/******************************************************************************/
/*!
  This function turns the boss sprite back to normal
 */
/******************************************************************************/
  void RevertRed(object::C_Sprite * p_sprite, object::C_AIBossStealth * p_boss)
  {
    // Alias
    using c_sprite = object::C_AIBossStealth::CURRENTSPRITE;
    
    // Set the relevant sprite
    switch(p_boss->m_sprite)
    {
    case(c_sprite::IDLESPRITE):
      p_sprite->Set_Texture("BossIdle");
      break;
    case(c_sprite::FLICKERFADESPRITE):
      p_sprite->Set_Texture("BossFlickerFade");
      break;
    case(c_sprite::FLICKERATTACKSPRITE):
      p_sprite->Set_Texture("BossFlickerAttack");
      break;
    case(c_sprite::POUNDSPRITE):
      p_sprite->Set_Texture("BossPound");
      break;
    default:
      return;
    }
  }

/******************************************************************************/
/*!
  This function activates the collider on the boss
 */
/******************************************************************************/
  void ActivateCollider(object::C_BoxCollider * p_box)
  {
    p_box->Set_Active(true);
  }

/******************************************************************************/
/*!
  This function deactivates the collider on the boss
 */
/******************************************************************************/
  void DeactivateCollider(object::C_BoxCollider * p_box)
  {
    p_box->Set_Active(false);
  }

/******************************************************************************/
/*!
  This function enables gravity on the boss
 */
/******************************************************************************/
  void EnableGravity(object::C_Rigidbody * p_rigid)
  {
    p_rigid->Set_Gravity(true);
  }

/******************************************************************************/
/*!
  This function disables gravity on the boss
 */
/******************************************************************************/
  void DisableGravity(object::C_Rigidbody * p_rigid)
  {
    p_rigid->Set_Gravity(false);
  }

/******************************************************************************/
/*!
  This function flips the sprite of the boss across the Y axis
 */
/******************************************************************************/
  void EnableFlipX(object::C_Sprite * p_sprite)
  {
    p_sprite->Set_FlipX(true);
  }

/******************************************************************************/
/*!
  This function disables the flipping of the sprite across the Y axis
 */
/******************************************************************************/
  void DisableFlipX(object::C_Sprite * p_sprite)
  {
    p_sprite->Set_FlipX(false);
  }

/******************************************************************************/
/*!
  This function enables the flipping of the sprite across the X axis
 */
/******************************************************************************/
  void EnableFlipY(object::C_Sprite * p_sprite)
  {
    p_sprite->Set_FlipY(true);
  }

/******************************************************************************/
/*!
  This function disables the flipping of the sprite across the X axis
 */
/******************************************************************************/
  void DisableFlipY(object::C_Sprite * p_sprite)
  {
    p_sprite->Set_FlipY(false);
  }

/******************************************************************************/
/*!
  This function sets the dealth animation on the boss
 */
/******************************************************************************/
  void DeathAnimation(object::C_Sprite * p_sprite, object::C_AIBossStealth *p_boss)
  {
    p_sprite->Set_Texture("BossDeath");
    p_boss->m_sprite = object::C_AIBossStealth::CURRENTSPRITE::DEATHSPRITE;
  }

/******************************************************************************/
/*!
  This function destroys the boss game object
 */
/******************************************************************************/
  void DestroyBoss(object::C_GameObject* p_obj)
  {
    p_obj->Destroy();
  }

/******************************************************************************/
/*!
  This function is the helper function to call the cheat that sets the boss
  health to 1
 */
/******************************************************************************/
  void BossKill(object::C_AIBossStealth *p_boss)
  {
    p_boss->Kill();
  }
}
