/******************************************************************************/
/*!
\file_name        AIBossWitch.cpp
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the member function definitions of the AIBossWitch 
        class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/

#include "AIBossWitch.h"

// Macros for the boss actions
#define CHASE(ACTIONSEQ, INDEX) actions::AddToSequence(##ACTIONSEQ, DispatchAIBossWitchAttackSoundEffect); actions::AddToSequence(##ACTIONSEQ, DispatchActivate ## INDEX ## Collider); actions::AddToSequence(##ACTIONSEQ, Dispatch ## INDEX ## FlockChase);
#define RECALL(ACTIONSEQ, INDEX) actions::AddToSequence(##ACTIONSEQ, DispatchAIBossWitchAttackSoundEffect); actions::AddToSequence(##ACTIONSEQ, DispatchDeactivate ## INDEX ## Collider); actions::AddToSequence(##ACTIONSEQ, DispatchRecall ## INDEX ## Flock);
#define FALL(ACTIONSEQ, INDEX) actions::AddToSequence(##ACTIONSEQ, DispatchAIBossWitchAttackSoundEffect); actions::AddToSequence(##ACTIONSEQ, DispatchActivate ## INDEX ## Collider); actions::AddToSequence(##ACTIONSEQ, Dispatch ## INDEX ## FlockFall);
#define RECALLALL(ACTIONSEQ) actions::AddToSequence(##ACTIONSEQ, DispatchAIBossWitchAttackSoundEffect); actions::AddToSequence(##ACTIONSEQ, DispatchDeactivateColliders); actions::AddToSequence(##ACTIONSEQ, DispatchRecallAllFlocks);
#define ENCIRCLE(ACTIONSEQ) actions::AddToSequence(##ACTIONSEQ, DispatchAIBossWitchAttackSoundEffect); actions::AddToSequence(##ACTIONSEQ, DispatchActivateColliders); actions::AddToSequence(##ACTIONSEQ, DispatchEncircle);
#define RAIN(ACTIONSEQ) actions::AddToSequence(##ACTIONSEQ, DispatchAIBossWitchAttackSoundEffect); actions::AddToSequence(##ACTIONSEQ, DispatchActivateColliders); actions::AddToSequence(##ACTIONSEQ, DispatchRain);
#define RISE(ACTIONSEQ) actions::AddToSequence(##ACTIONSEQ, DispatchAIBossWitchAttackSoundEffect); actions::AddToSequence(##ACTIONSEQ, DispatchDeactivateColliders); actions::AddToSequence(##ACTIONSEQ, DispatchAllFlocksRise);

namespace
{
  // Event response functions
  void OnCollisionStarted(events::C_CollisionEvent p_event);
  void OnLogicUpdate     (object::C_GameObject* p_obj);
  void ActivateCollider  (object::C_BoxCollider* p_box);
  void DeactivateCollider(object::C_BoxCollider* p_box);
  void RestartBoss       (object::C_AIBossWitch* p_boss);
  void PrepareBossPhase2 (object::C_AIBossWitch* p_boss);
  void RelocateBoss      (object::C_Transform* p_transform);
  void DestroyBoss       (object::C_GameObject* p_obj);
  void TurnRed           (object::C_Sprite * p_sprite);
  void RevertRed         (object::C_Sprite * p_sprite);
  void BossKill          (object::C_AIBossWitch *p_boss);

  // Event dispatch functions
  EVENTDISPATCHFUNCTION(ActivateColliders);
  EVENTDISPATCHFUNCTION(ActivateFlocks);
  EVENTDISPATCHFUNCTION(DeactivateColliders);
  EVENTDISPATCHFUNCTION(DeactivateFlocks);
  EVENTDISPATCHFUNCTION(ActivateFirstCollider);
  EVENTDISPATCHFUNCTION(ActivateSecondCollider);
  EVENTDISPATCHFUNCTION(ActivateThirdCollider);
  EVENTDISPATCHFUNCTION(ActivateFourthCollider);
  EVENTDISPATCHFUNCTION(ActivateFifthCollider);
  EVENTDISPATCHFUNCTION(ActivateSixthCollider);
  EVENTDISPATCHFUNCTION(ActivateSeventhCollider);
  EVENTDISPATCHFUNCTION(ActivateEighthCollider);
  EVENTDISPATCHFUNCTION(ActivateNinthCollider);
  EVENTDISPATCHFUNCTION(ActivateTenthCollider);
  EVENTDISPATCHFUNCTION(ActivateEleventhCollider);
  EVENTDISPATCHFUNCTION(ActivateTwelfthCollider);
  EVENTDISPATCHFUNCTION(DeactivateFirstCollider);
  EVENTDISPATCHFUNCTION(DeactivateSecondCollider);
  EVENTDISPATCHFUNCTION(DeactivateThirdCollider);
  EVENTDISPATCHFUNCTION(DeactivateFourthCollider);
  EVENTDISPATCHFUNCTION(DeactivateFifthCollider);
  EVENTDISPATCHFUNCTION(DeactivateSixthCollider);
  EVENTDISPATCHFUNCTION(DeactivateSeventhCollider);
  EVENTDISPATCHFUNCTION(DeactivateEighthCollider);
  EVENTDISPATCHFUNCTION(DeactivateNinthCollider);
  EVENTDISPATCHFUNCTION(DeactivateTenthCollider);
  EVENTDISPATCHFUNCTION(DeactivateEleventhCollider);
  EVENTDISPATCHFUNCTION(DeactivateTwelfthCollider);
  EVENTDISPATCHFUNCTION(FirstFlockChase);
  EVENTDISPATCHFUNCTION(SecondFlockChase);
  EVENTDISPATCHFUNCTION(ThirdFlockChase);
  EVENTDISPATCHFUNCTION(FourthFlockChase);
  EVENTDISPATCHFUNCTION(FifthFlockChase);
  EVENTDISPATCHFUNCTION(SixthFlockChase);
  EVENTDISPATCHFUNCTION(SeventhFlockChase);
  EVENTDISPATCHFUNCTION(EighthFlockChase);
  EVENTDISPATCHFUNCTION(NinthFlockChase);
  EVENTDISPATCHFUNCTION(TenthFlockChase);
  EVENTDISPATCHFUNCTION(EleventhFlockChase);
  EVENTDISPATCHFUNCTION(TwelfthFlockChase);
  EVENTDISPATCHFUNCTION(RecallFirstFlock);
  EVENTDISPATCHFUNCTION(RecallSecondFlock);
  EVENTDISPATCHFUNCTION(RecallThirdFlock);
  EVENTDISPATCHFUNCTION(RecallFourthFlock);
  EVENTDISPATCHFUNCTION(RecallFifthFlock);
  EVENTDISPATCHFUNCTION(RecallSixthFlock);
  EVENTDISPATCHFUNCTION(RecallSeventhFlock);
  EVENTDISPATCHFUNCTION(RecallEighthFlock);
  EVENTDISPATCHFUNCTION(RecallNinthFlock);
  EVENTDISPATCHFUNCTION(RecallTenthFlock);
  EVENTDISPATCHFUNCTION(RecallEleventhFlock);
  EVENTDISPATCHFUNCTION(RecallTwelfthFlock);
  EVENTDISPATCHFUNCTION(RecallAllFlocks);
  EVENTDISPATCHFUNCTION(FirstFlockFall);
  EVENTDISPATCHFUNCTION(SecondFlockFall);
  EVENTDISPATCHFUNCTION(ThirdFlockFall);
  EVENTDISPATCHFUNCTION(FourthFlockFall);
  EVENTDISPATCHFUNCTION(FifthFlockFall);
  EVENTDISPATCHFUNCTION(SixthFlockFall);
  EVENTDISPATCHFUNCTION(SeventhFlockFall);
  EVENTDISPATCHFUNCTION(EighthFlockFall);
  EVENTDISPATCHFUNCTION(NinthFlockFall);
  EVENTDISPATCHFUNCTION(TenthFlockFall);
  EVENTDISPATCHFUNCTION(EleventhFlockFall);
  EVENTDISPATCHFUNCTION(TwelfthFlockFall);
  EVENTDISPATCHFUNCTION(Divide3to12);
  EVENTDISPATCHFUNCTION(Divide1to3);
  EVENTDISPATCHFUNCTION(Divide4to8);
  EVENTDISPATCHFUNCTION(Concat121);
  EVENTDISPATCHFUNCTION(Concat8to4);
  EVENTDISPATCHFUNCTION(Rain);
  EVENTDISPATCHFUNCTION(Loop);
  EVENTDISPATCHFUNCTION(AllFlocksRise);
  EVENTDISPATCHFUNCTION(CameraLock);
  EVENTDISPATCHFUNCTION(CameraLock2);
  EVENTDISPATCHFUNCTION(CameraUnlock);
  EVENTDISPATCHFUNCTION(RelocateBoss);
  EVENTDISPATCHFUNCTION(PrepareBossPhase2);
  EVENTDISPATCHFUNCTION(PrepareFlocksPhase2);
  EVENTDISPATCHFUNCTION(Encircle);
  EVENTDISPATCHFUNCTION(DestroyBoss);
  EVENTDISPATCHFUNCTION(DisplayWinMenu);
  EVENTDISPATCHFUNCTION(FirstPartition);
  EVENTDISPATCHFUNCTION(DestroyFirstPartition);
  EVENTDISPATCHFUNCTION(SecondPartition);
  EVENTDISPATCHFUNCTION(AIBossWitchDeathSoundEffect);
  EVENTDISPATCHFUNCTION(AIBossWitchAttackSoundEffect);
  EVENTDISPATCHFUNCTION(TurnRed);
  EVENTDISPATCHFUNCTION(RevertRed);
  EVENTDISPATCHFUNCTION(DeactivateCollider);
  EVENTDISPATCHFUNCTION(ActivateCollider);
}

namespace object
{
/******************************************************************************/
/*!
  Non default constructor for an AIBossWitch object
 */
/******************************************************************************/
C_AIBossWitch::C_AIBossWitch(C_GameObject *p_obj, math::Matrix3 *player_transform)
: C_Component{p_obj, AIBOSS}, m_player_transform{player_transform}
{
}

/******************************************************************************/
/*!
  This function sets the player transform pointer on the boss
 */
/******************************************************************************/
void C_AIBossWitch::Set_Player_Transform(math::Matrix3 * p_transform)
{
  m_player_transform = p_transform;
}

/******************************************************************************/
/*!
  This function returns a pointer to the object
 */
/******************************************************************************/
C_AIBossWitch * C_AIBossWitch::Actual()
{
  return this;
}

/******************************************************************************/
/*!
  This function creates a clone of this object
 */
/******************************************************************************/
C_AIBossWitch * C_AIBossWitch::Clone() const
{
  return new C_AIBossWitch{p_obj, m_player_transform};
}

/******************************************************************************/
/*!
  This function restarts the last state of the boss
 */
/******************************************************************************/
void C_AIBossWitch::Restart()
{
  m_state    = ATTACK;
  m_substate = ENTER;
}

/******************************************************************************/
/*!
  This function prepares the boss for phase 2
 */
/******************************************************************************/
void C_AIBossWitch::InitPhase2()
{
  m_dead     = false;
  m_instance = SECOND;
  m_state    = SPAWN;
  m_substate = ENTER;
  m_health   = BOSS_SECOND_HP;
}

/******************************************************************************/
/*!
  This function causes the boss to flicker red
 */
/******************************************************************************/
void C_AIBossWitch::RedSprite()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, DispatchTurnRed);
  actions::AddToSequence(actionseq, DispatchRevertRed);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  This function sets the hp of the boss to 15
 */
/******************************************************************************/
void C_AIBossWitch::Kill()
{
  m_health = 15;
}

/******************************************************************************/
/*!
  This function connects functions to events
 */
/******************************************************************************/
void C_AIBossWitch::Connect()
{
  // Initialize variables
  auto p_box        = static_cast<C_BoxCollider*>
                      (p_obj->Find_Component(BOXCOLLIDER));
  auto p_boss       = static_cast<C_AIBossWitch*>
                      (p_obj->Find_Component(AIBOSS));
  auto p_transform  = static_cast<C_Transform*>
                      (p_obj->Find_Component(TRANSFORM));
  auto p_sprite     = static_cast<C_Sprite*>
                      (p_obj->Find_Component(SPRITE));
  
  // Connect functions to events
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
  events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
  
  events::C_EventDispatcher::Connect("Loop",                RestartBoss,        p_boss);
  events::C_EventDispatcher::Connect("ActivateCollider",    ActivateCollider,   p_box);
  events::C_EventDispatcher::Connect("DeactivateCollider",  DeactivateCollider, p_box);
  events::C_EventDispatcher::Connect("RelocateBoss",        RelocateBoss,       p_transform);
  events::C_EventDispatcher::Connect("PrepareBossPhase2",   PrepareBossPhase2,  p_boss);
  events::C_EventDispatcher::Connect("DestroyBoss",         DestroyBoss,        p_obj);
  events::C_EventDispatcher::Connect("BossKill",            BossKill,           p_boss);
  events::C_EventDispatcher::Connect("TurnRed",             TurnRed,            p_sprite);
  events::C_EventDispatcher::Connect("RevertRed",           RevertRed,          p_sprite);
}

/******************************************************************************/
/*!
  The collision resolution function of the boss
 */
/******************************************************************************/
void C_AIBossWitch::CollisionStarted(object::C_GameObject *obj)
{
  // If the boss is already dead, skip
  if(m_dead)
  {
    return;
  }
  
  // If the boss was hit by a bullet
  if(obj->Get_Trait() == T_BULLET)
  {
    // Flicker red
    RedSprite();
    // If the boss ran out of lives
    if(!--m_health)
    {
      m_dead = true;
      actions::C_ActionDispatcher::Clear();
      m_state = DEATH;
      m_substate = ENTER;
    }
  }
}

/******************************************************************************/
/*!
  The update function of the boss
 */
/******************************************************************************/
void C_AIBossWitch::Update()
{
  // If the game is paused. skip
  if(utilities::C_OptionsManager::Get_Pause())
  {
    return;
  }
  
  updatetime += utilities::C_Timer::Get_dt();
  
  // The FSM of the boss
  switch(m_instance)
  {
    case(FIRST):
      switch(m_state)
      {
        case(SPAWN):
          switch(m_substate)
          {
            case(ENTER):
              AS_PlayFirstSpawnAnimation();
              m_substate = UPDATE;
              break;
            case(UPDATE):
              m_substate = EXIT;
              break;
            case(EXIT):
              m_state = ATTACK;
              m_substate = ENTER;
              break;
          }
          break;
        case(ATTACK):
          switch(m_substate)
          {
            case(ENTER):
              AS_Attack();
              AS_MovementSequence();
              m_substate = UPDATE;
              updatetime = 0.0;
              break;
            case(UPDATE):
              if(updatetime > 10.0)
              {  
                AS_FloatMovementSequence();
                updatetime = 0;
              }
              break;
            case(EXIT):
              break;
          }
          break;
        case(DEATH):
          switch(m_substate)
          {
          case(ENTER):
            AS_FirstDeath();
            m_substate = UPDATE;
            break;
          case(UPDATE):
            break;
          case(EXIT):
            break;
          }
      }
      break;
    case(SECOND):
      switch(m_state)
      {
        case(SPAWN):
          switch(m_substate)
          {
            case(ENTER):
              AS_PlaySecondSpawnAnimation();
              updatetime = 0.0;
              m_substate = UPDATE;
              break;
            case(UPDATE):
              if(updatetime > 5.0)
                m_substate = EXIT;
              break;
            case(EXIT):
              m_state = ATTACK;
              m_substate = ENTER;
              break;
          }
          break;
        case(ATTACK):
          switch(m_substate)
          {
            case(ENTER):
              AS_Attack2();
              AS_MovementSequence2();
              m_substate = UPDATE;
              updatetime = 10.0;
              break;
            case(UPDATE):
              if(updatetime > 10.0)
              {  
                AS_FloatMovementSequence();
                updatetime = 0;
              }
              break;
            case(EXIT):
              break;
          }
          break;
        case(DEATH):
          switch(m_substate)
          {
          case(ENTER):
            AS_SecondDeath();
            m_substate = UPDATE;
            break;
          case(UPDATE):
            break;
          case(EXIT):
            break;
          }
      }
      break;
  }
}

/******************************************************************************/
/*!
  The Action sequence for the first spawn animation
 */
/******************************************************************************/
void C_AIBossWitch::AS_PlayFirstSpawnAnimation()
{
  // Create new action sequence
  actions::C_ActionSequence actionseq;
  
  auto p_matrix = static_cast<C_Transform*>
                  (p_obj->Find_Component(TRANSFORM))->Get_Transform();
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, DispatchDeactivateCollider);
  actions::AddToSequence(actionseq, DispatchCameraLock);
  actions::AddToSequence(actionseq, DispatchFirstPartition);
  actions::Wait(actionseq, 0);
  actions::AddToSequence(actionseq, utilities::DispatchBossCameraShakeEvent);
  actions::AddToSequence(actionseq, DispatchActivateFlocks);
  actions::AddToSequence(actionseq, DispatchRecallAllFlocks);
  actions::Wait(actionseq, 1.0);
  actions::AddToSequence(actionseq, DispatchActivateCollider);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{-20.0f, -6.0f}, 5.0);
  actions::Wait(actionseq, 1.0);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The movement sequence for the first phase of the boss fight
 */
/******************************************************************************/
void C_AIBossWitch::AS_MovementSequence()
{
  // Create new action sequence
  actions::C_ActionSequence actionseq;
  
  auto p_matrix = static_cast<C_Transform*>
                  (p_obj->Find_Component(TRANSFORM))->Get_Transform();
  
  // Add actions to the sequence
  actions::Wait(actionseq, 10.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{10.0f, 0.0f}, 1.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{-7.0f, 0.0f}, 5.0);
  actions::Wait(actionseq, 3.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{-10.0f, 0.0f}, 1.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{0.0f, 5.0f}, 1.0);
  actions::Wait(actionseq, 3.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{0.0f, -5.0f}, 2.0);
  actions::Wait(actionseq, 11.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{10.0f, 0.0f}, 1.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{7.0f, 0.0f}, 5.0);
  actions::Wait(actionseq, 3.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{-10.0f, 0.0f}, 1.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{0.0f, 5.0f}, 2.0);
  actions::Wait(actionseq, 1.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{0.0f, -5.0f}, 1.0);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The floating sequence of the boss
 */
/******************************************************************************/
void C_AIBossWitch::AS_FloatMovementSequence()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  auto p_matrix = static_cast<C_Transform*>
                  (p_obj->Find_Component(TRANSFORM))->Get_Transform();
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{0.0f, 5.0f}, 5.0);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{0.0f, -5.0f}, 5.0);
  
  // Register the sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The action sequence for the first death of the boss
 */
/******************************************************************************/
void C_AIBossWitch::AS_FirstDeath()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  auto p_matrix = static_cast<C_Transform*>
                  (p_obj->Find_Component(TRANSFORM))->Get_Transform();
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, DispatchAIBossWitchDeathSoundEffect);
  RECALLALL(actionseq);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{0.0f, 5.0f}, 5.0);
  RISE(actionseq);
  actions::AddToSequence(actionseq, p_matrix, math::Vec2{30.0f, 0.0f}, 1.0);
  actions::AddToSequence(actionseq, DispatchDeactivateFlocks);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq, DispatchRelocateBoss);
  actions::AddToSequence(actionseq, DispatchCameraUnlock);
  actions::AddToSequence(actionseq, DispatchDestroyFirstPartition);
  actions::AddToSequence(actionseq, DispatchPrepareBossPhase2);
  actions::AddToSequence(actionseq, DispatchPrepareFlocksPhase2);
  
  // Register the actions
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The action sequence for the second death of the boss
 */
/******************************************************************************/
void C_AIBossWitch::AS_SecondDeath()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  auto p_opacity = static_cast<C_Sprite*>
                   (p_obj->Find_Component(SPRITE))->Get_Opacity_Ptr();
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, DispatchAIBossWitchDeathSoundEffect);
  RISE(actionseq);
  actions::Wait(actionseq, 1.0);
  actions::AddToSequence(actionseq, p_opacity, -1.0f, 1.0);
  actions::AddToSequence(actionseq, DispatchDeactivateFlocks);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq, DispatchDestroyBoss);
  actions::AddToSequence(actionseq, p_opacity, 1.0f, 1.0);
  actions::AddToSequence(actionseq, DispatchDisplayWinMenu);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The second spawn animation action sequence for the boss
 */
/******************************************************************************/
void C_AIBossWitch::AS_PlaySecondSpawnAnimation()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to the sequence
  actions::AddToSequence(actionseq, DispatchCameraLock2);
  actions::AddToSequence(actionseq, DispatchSecondPartition);
  actions::AddToSequence(actionseq, utilities::DispatchBossCameraShakeEvent);
  actions::AddToSequence(actionseq, DispatchActivateFlocks);
  actions::AddToSequence(actionseq, DispatchRecallAllFlocks);
  actions::Wait(actionseq, 7.0);
  actions::AddToSequence(actionseq, DispatchActivateColliders);
  
  // Register the action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The second attack sequence for the boss
 */
/******************************************************************************/
void C_AIBossWitch::AS_Attack2()
{
  // Create a new action sequence
  actions::C_ActionSequence actionseq;
  
  // Add actions to the sequence
  CHASE(actionseq, First);
  actions::Wait(actionseq, 0.1);
  CHASE(actionseq, Second);
  actions::Wait(actionseq, 0.1);
  CHASE(actionseq, Third);
  actions::Wait(actionseq, 0.1);
  CHASE(actionseq, Fourth);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, First);
  actions::Wait(actionseq, 0.1);
  RECALL(actionseq, Second);
  actions::Wait(actionseq, 0.1);
  RECALL(actionseq, Third);
  actions::Wait(actionseq, 0.1);
  RECALL(actionseq, Fourth);
  actions::Wait(actionseq, 0.1);
  actions::Wait(actionseq, 1.5);
  CHASE(actionseq, First);
  actions::Wait(actionseq, 0.1);
  CHASE(actionseq, Second);
  actions::Wait(actionseq, 0.1);
  CHASE(actionseq, Third);
  actions::Wait(actionseq, 0.1);
  CHASE(actionseq, Fourth);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, First);
  actions::Wait(actionseq, 0.1);
  RECALL(actionseq, Second);
  actions::Wait(actionseq, 0.1);
  RECALL(actionseq, Third);
  actions::Wait(actionseq, 0.1);
  RECALL(actionseq, Fourth);
  actions::Wait(actionseq, 0.1);
  actions::Wait(actionseq, 4.0);
  actions::AddToSequence(actionseq, DispatchDivide4to8);
  RISE(actionseq);
  actions::Wait(actionseq, 5.0);
  FALL(actionseq, First);
  actions::Wait(actionseq, 0.5);
  FALL(actionseq, Second);
  actions::Wait(actionseq, 0.5);
  FALL(actionseq, Third);
  actions::Wait(actionseq, 0.5);
  FALL(actionseq, Fourth);
  actions::Wait(actionseq, 0.5);
  FALL(actionseq, Fifth);
  actions::Wait(actionseq, 0.5);
  FALL(actionseq, Sixth);
  actions::Wait(actionseq, 0.5); 
  FALL(actionseq, Seventh);
  actions::Wait(actionseq, 0.5);
  FALL(actionseq, Eighth);
  actions::Wait(actionseq, 2.0);
  RECALLALL(actionseq);
  actions::Wait(actionseq, 5.0);
  ENCIRCLE(actionseq);
  actions::Wait(actionseq, 2.0);
  RECALLALL(actionseq);
  actions::Wait(actionseq, 2.0);
  ENCIRCLE(actionseq);
  actions::Wait(actionseq, 2.0);
  RECALLALL(actionseq);
  actions::Wait(actionseq, 2.0);
  ENCIRCLE(actionseq);
  actions::Wait(actionseq, 2.0);
  RECALLALL(actionseq);
  actions::Wait(actionseq, 2.0);
  ENCIRCLE(actionseq);
  actions::Wait(actionseq, 2.0);
  RECALLALL(actionseq);
  actions::Wait(actionseq, 2.0);
  ENCIRCLE(actionseq);
  actions::Wait(actionseq, 2.0);
  RECALLALL(actionseq);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq, DispatchConcat8to4);
  actions::AddToSequence(actionseq, DispatchLoop);

  // Register actionsequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The second movement sequence of the boss
 */
/******************************************************************************/
void C_AIBossWitch::AS_MovementSequence2()
{
  // Create new action sequence
  actions::C_ActionSequence actionseq;
  
  auto transform = static_cast<object::C_Transform*>
                   (p_obj->Find_Component(TRANSFORM))->Get_Transform();
  
  // Add actions to the sequence
  actions::Wait(actionseq, 0.3);
  actions::AddToSequence(actionseq, transform, math::Vec2{-10.0f, 0.0f}, 0.5);
  actions::Wait(actionseq, 2.7);
  actions::AddToSequence(actionseq, transform, math::Vec2{10.0f, 0.0f}, 0.5);
  actions::Wait(actionseq, 0.5);
  actions::AddToSequence(actionseq, transform, math::Vec2{-15.0f, 10.0f}, 4.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{-20.0f, -10.0f}, 2.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{-3.0f, 2.5f}, 1.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{3.0f, 2.5f}, 1.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{20.0f, -10.0f}, 2.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{3.0f, 2.5f}, 1.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{-3.0f, 2.5f}, 1.0);
  actions::Wait(actionseq, 2.0);
  actions::Wait(actionseq, 7.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{-10.0f, -5.0f}, 1.0);
  actions::Wait(actionseq, 3.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{10.0f, 0.0f}, 1.0);
  actions::Wait(actionseq, 3.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{-10.0f, 0.0f}, 1.0);
  actions::Wait(actionseq, 3.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{10.0f, 5.0f}, 1.0);
  actions::Wait(actionseq, 2.0);
  actions::AddToSequence(actionseq, transform, math::Vec2{15.0f, -10.0f}, 4.0);

  // Register action sequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}

/******************************************************************************/
/*!
  The attack sequence of the boss
 */
/******************************************************************************/
void C_AIBossWitch::AS_Attack()
{
  // Create new action sequence
  actions::C_ActionSequence actionseq;

  // Add actions to the sequence
  actions::Wait(actionseq, 10.0);
  CHASE(actionseq, First);
  actions::Wait(actionseq, 1.0);
  CHASE(actionseq, Second);
  actions::Wait(actionseq, 1.0);
  CHASE(actionseq, Third);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, First);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, Second);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, Third);
  actions::Wait(actionseq, 1.0);
  actions::AddToSequence(actionseq, DispatchDivide3to12);
  RISE(actionseq);
  actions::Wait(actionseq, 3.0);
  CHASE(actionseq, First);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Second);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Third);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Fourth);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Fifth);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Sixth);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Seventh);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Eighth);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Ninth);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Tenth);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Eleventh);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Twelfth);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, First);
  actions::Wait(actionseq, 0.2);
  RECALL(actionseq, Second);
  actions::Wait(actionseq, 0.2);
  RECALL(actionseq, Third);
  actions::Wait(actionseq, 0.2);
  RISE(actionseq);
  actions::Wait(actionseq, 2.0);
  RECALLALL(actionseq);
  actions::Wait(actionseq, 1.0);
  CHASE(actionseq, First);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Second);
  actions::Wait(actionseq, 0.5);
  CHASE(actionseq, Third);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, First);
  actions::Wait(actionseq, 0.2);
  RECALL(actionseq, Second);
  actions::Wait(actionseq, 0.2);
  RECALL(actionseq, Third);
  actions::Wait(actionseq, 5.0);
  actions::AddToSequence(actionseq, DispatchConcat121);
  actions::Wait(actionseq, 2.0);
  CHASE(actionseq, First);
  actions::Wait(actionseq, 3.0);
  actions::AddToSequence(actionseq, DispatchDivide1to3);
  RAIN(actionseq);
  actions::Wait(actionseq, 1.0);
  RECALL(actionseq, First);
  RECALL(actionseq, Second);
  RECALL(actionseq, Third);
  actions::AddToSequence(actionseq, DispatchLoop);
  
  // Register actionsequence
  actions::C_ActionDispatcher::Register_Action_Sequence(actionseq);
}
}

namespace
{
/******************************************************************************/
/*!
  Helper function to call collision started on the boss
 */
/******************************************************************************/
  void OnCollisionStarted(events::C_CollisionEvent p_event)
  {
    static_cast<object::C_AIBossWitch*>
    (p_event.Object()->Find_Component(AIBOSS))->CollisionStarted(p_event.Other_Object());
  }

/******************************************************************************/
/*!
  Helper function to call update on the boss
 */
/******************************************************************************/
  void OnLogicUpdate(object::C_GameObject* p_obj)
  {
    static_cast<object::C_AIBossWitch*>(p_obj->Find_Component(AIBOSS))->Update();
  }

/******************************************************************************/
/*!
  Activates the collider on the boss
 */
/******************************************************************************/
  void ActivateCollider(object::C_BoxCollider* p_box)
  {
    p_box->Set_Active(true);
  }

/******************************************************************************/
/*!
  Deactivates the collider on the boss
 */
/******************************************************************************/
  void DeactivateCollider(object::C_BoxCollider* p_box)
  {
    p_box->Set_Active(false);
  }

/******************************************************************************/
/*!
  Helper function to call the member function restart on the boss
 */
/******************************************************************************/
  void RestartBoss(object::C_AIBossWitch * p_boss)
  {
    p_boss->Restart();
  }

/******************************************************************************/
/*!
  Helper function to call InitPhase2 on the boss
 */
/******************************************************************************/
  void PrepareBossPhase2(object::C_AIBossWitch * p_boss)
  {
    p_boss->InitPhase2();
  }

/******************************************************************************/
/*!
  Relocates the boss to coordinates 193, 32
 */
/******************************************************************************/
  void RelocateBoss(object::C_Transform * p_transform)
  {
    p_transform->Set_Position(193, 32);
  }

/******************************************************************************/
/*!
  Sets the boss texture to the red texture
 */
/******************************************************************************/
  void TurnRed(object::C_Sprite * p_sprite)
  {
    p_sprite->Set_Texture("BossIdleRed");
  }

/******************************************************************************/
/*!
  Sets the boss texture to the normal texture
 */
/******************************************************************************/
  void RevertRed(object::C_Sprite * p_sprite)
  {
    p_sprite->Set_Texture("BossIdle");
  }

/******************************************************************************/
/*!
  This function destroys the boss game object
 */
/******************************************************************************/
  void DestroyBoss(object::C_GameObject * p_obj)
  {
    p_obj->Destroy();
  }

/******************************************************************************/
/*!
  This function calls the cheat function that sets the boss' health to 1.
 */
/******************************************************************************/
  void BossKill(object::C_AIBossWitch *p_boss)
  {
    p_boss->Kill();
  }
}
