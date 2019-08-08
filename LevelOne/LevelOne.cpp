/*****************************************************************************/
/*!
\file_name        LevelOne.cpp
\project_name     Double Tap
\primary_author   Ma Ming Shun, mingshun.ma, 440002516
\brief
This file contains the implementation for Level one

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/*****************************************************************************/

#include "LevelOne.h"


namespace
{
	object::C_GameObject* p_player;
	void Shoot(C_LevelOne *);
	void ShootUp(C_LevelOne *);
	void ShootDown(C_LevelOne *);
	void UpdateHP(C_LevelOne *level);
	void UpdateLife(C_LevelOne *level);
	void SpriteMachineGun(C_LevelOne *level);
	void SpritePistol(C_LevelOne *level);
	void SpriteShotgun(C_LevelOne *level);
	void ScreamerShoot(C_LevelOne *level);
	void BossShoot(C_LevelOne *level);
	void BossSummon(C_LevelOne *level);
	void LockCamera(C_LevelOne *level);
	void RefreshAmmoInfo(C_LevelOne *level);
	void DisplayMenu(C_LevelOne *level);
	void CloseMenu(C_LevelOne *level);
	void RefreshMenu(C_LevelOne *level);
	void ExecuteMenu(C_LevelOne *level);
	void DisplayHowToPlay(C_LevelOne *level);
	void CloseHowToPlay(C_LevelOne *level);
	void DisplayOptions(C_LevelOne *level);
	void CloseOptions(C_LevelOne *level);
	void RefreshOptions(C_LevelOne *level);
	void ExecuteOptions(C_LevelOne *level);
	void DisplayCredits(C_LevelOne *level);
	void CloseCredits(C_LevelOne *level);
	void DisplayConfirmation(C_LevelOne *level);
	void CloseConfirmation(C_LevelOne *level);
	void RefreshConfirmation(C_LevelOne *level);
	void ExecuteConfirmation(C_LevelOne *level);
	void DisplayWinMenu(C_LevelOne *level);
	void CloseWinMenu(C_LevelOne *level);
	void DisplayLoseMenu(C_LevelOne *level);
	void CloseLoseMenu(C_LevelOne *level);
	void RefreshLoseMenu(C_LevelOne *level);
	void ExecuteLoseMenu(C_LevelOne *level);
	void UpdateCheckpointPos(C_LevelOne *level);
	void NextLevel(C_LevelOne *level);
	void BloaterDeathSoundEffect(C_LevelOne *level);
	void AIBossSoundEffect(C_LevelOne *level);
	void SetCameraShakeTrue(C_LevelOne *level);
	void SetCameraShakeFalse(C_LevelOne *level);
	void ToggleHeartWarning(C_LevelOne *level);
	void AIBossBruteLandingSoundEffect(C_LevelOne *level);
	void AIBossBruteDeathSoundEffect(C_LevelOne *level);

	void ToBoss(object::C_GameObject* p_obj)
	{
		static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM))->Set_Position(165, 19);
	}
}

int & C_LevelOne::GetBossWaveCount()
{
	return BossWaveCount;
}

int & C_LevelOne::GetBossShootCount()    
 {       
	return BossShootCount;
}

/*****************************************************************************/
/*!
Load all the assets required for level one
*/
/*****************************************************************************/
void C_LevelOne::Load()
{

	/*****************************************************************************/
	/*                                Defines                                    */
	/*****************************************************************************/
	object::C_Transform *p_transform;
	object::C_Sprite *p_sprite;
	object::C_BoxCollider *p_box;
	object::C_Rigidbody *p_rigid;
	object::C_GameObject *p_obj;
	object::C_ParticleSystem *p_particlesys;
	graphics::Texture *p_tex;

	/*****************************************************************************/
	/*                               Load Tiles                                  */
	/*****************************************************************************/
	p_obj = CreateObject("Wall");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Tile.png", "Wall");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Wall");

	p_obj = CreateObject("Floor");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Floor.png", "Floor");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Floor");

	p_obj = CreateObject("BuildingBlock1");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BuildingTile.png", "BuildingBlock1");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BuildingBlock1");

	p_obj = CreateObject("BuildingBlock1_Left");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BuildingTile_Left.png", "BuildingBlock1_Left");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BuildingBlock1_Left");

	p_obj = CreateObject("BuildingBlock1_Right");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BuildingTile_Right.png", "BuildingBlock1_Right");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BuildingBlock1_Right");


	p_obj = CreateObject("BuildingBlock2");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BuildingTile2.png", "BuildingBlock2");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BuildingBlock2");

	p_obj = CreateObject("BuildingBlock2_Left");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BuildingTile2_Left.png", "BuildingBlock2_Left");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BuildingBlock2_Left");

	p_obj = CreateObject("BuildingBlock2_Right");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BuildingTile2_Right.png", "BuildingBlock2_Right");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BuildingBlock2_Right");

	/*****************************************************************************/
	/*                            Load Tiles End                                 */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                            Create Tile Object                             */
	/*****************************************************************************/
	//Create game object.
	p_obj = CreateObject("Tile");

	//Add components
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Assign variables
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Load sprites
	p_tex = Load_Texture("res/Tile.png", "Tile");
	p_sprite->Add_Texture(p_tex);

	p_sprite->Set_Texture("Tile");

	/*****************************************************************************/
	/*                          Create Tile Object End                           */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                          Create Background                                */
	/*****************************************************************************/

	//Create game object
	p_obj = CreateObject("Background");

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Load sprites
	p_tex = Load_Texture("res/Background.png", "Background");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Background");

	//Set transfrom
	p_transform->Scale(7845.0f / TILESCALE, 2000 / TILESCALE);

	/*****************************************************************************/
	/*                       Create Background End                               */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                       Create Directional Keys                             */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("DirectionalKeys");

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Load sprites
	p_tex = Load_Texture("res/DirectionalKeys.png", "DirectionalKeys");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("DirectionalKeys");

	//Set transfrom
	p_transform->Scale(300.0f / TILESCALE / 3.0f, 300.0f / TILESCALE / 3.0f);

	/*****************************************************************************/
	/*                       Create Directional Keys End                         */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                       Create Shoot Button                                 */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("ShootButton");

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Load sprites
	p_tex = Load_Texture("res/shootButton.png", "ShootButton");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ShootButton");

	//Set transfrom
	p_transform->Scale(250.0f / TILESCALE / 3.0f, 200.0f / TILESCALE / 3.0f);

	/*****************************************************************************/
	/*                       Create Shoot Button End                             */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                          Create Jump Button                               */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("JumpButton");

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Load sprites
	p_tex = Load_Texture("res/SpaceBar.png", "JumpButton");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("JumpButton");

	//Set transfrom
	p_transform->Scale(300.0f / TILESCALE / 3.0f, 250.0f / TILESCALE / 3.0f);

	/*****************************************************************************/
	/*                       Create Jump Button End                              */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                            Create Player                                  */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("Player", T_PLAYER);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_Player{ p_obj });

	//Assign variables.
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));

	//Set transfrom.
	p_transform->Scale(80.0f / TILESCALE / 2.4f, 160.0f / TILESCALE / 2.4f);

	//Set box collider.
	p_box->Set_Size(1.0f, 2.0f);

	//Load sprites.
	p_tex = Load_Texture("res/Animation_PlayerPistol_Idle.png", "PlayerIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_Jumping.png", "PlayerJump", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_PlayerPistol_Move.png", "PlayerMove", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_Shoot.png", "PistolShoot", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_ShootUp.png", "PistolShootUp", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_ShootUp_Idle.png", "PistolShootUpIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_ShootDown.png", "PistolShootDown", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_PlayerPistol_Idle_Red.png", "PlayerIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_Jumping_Red.png", "PlayerJumpRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_PlayerPistol_Move_Red.png", "PlayerMoveRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_Shoot_Red.png", "PistolShootRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_ShootUp_Red.png", "PistolShootUpRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_ShootUp_Idle_Red.png", "PistolShootUpIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Pistol_ShootDown_Red.png", "PistolShootDownRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);

	p_tex = Load_Texture("res/Animation_Machinegun_Idle.png", "PlayerMachinegunIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machingun_Jumping.png", "PlayerMachinegunJump", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_Move.png", "PlayerMachinegunMove", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_Shoot.png", "MachinegunShoot", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_ShootUp.png", "MachinegunShootUp", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_ShootUp_Idle.png", "MachinegunShootUpIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_ShootDown.png", "MachinegunShootDown", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_Idle_Red.png", "PlayerMachinegunIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machingun_Jumping_Red.png", "PlayerMachinegunJumpRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_Move_Red.png", "PlayerMachinegunMoveRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_Shoot_Red.png", "MachinegunShootRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_ShootUp_Red.png", "MachinegunShootUpRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_ShootUp_Idle_Red.png", "MachinegunShootUpIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Machinegun_ShootDown_Red.png", "MachinegunShootDownRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);

	p_tex = Load_Texture("res/Animation_Shotgun_Idle.png", "PlayerShotgunIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_Jumping.png", "PlayerShotgunJump", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_Move.png", "PlayerShotgunMove", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_Shoot.png", "ShotgunShoot", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_ShootUp.png", "ShotgunShootUp", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_ShootUp_Idle.png", "ShotgunShootUpIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_ShootDown.png", "ShotgunShootDown", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_Idle_Red.png", "PlayerShotgunIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_Jumping_Red.png", "PlayerShotgunJumpRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_Move_Red.png", "PlayerShotgunMoveRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_Shoot_Red.png", "ShotgunShootRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_ShootUp_Red.png", "ShotgunShootUpRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_ShootUp_Idle_Red.png", "ShotgunShootUpIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Shotgun_ShootDown_Red.png", "ShotgunShootDownRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);

	p_sprite->Set_Texture("PlayerIdle");

	/*****************************************************************************/
	/*                          Create Player End                                */
	/*****************************************************************************/


	/*****************************************************************************/
	/*                         Create Normal Zombie                              */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("Enemy", T_ENEMY);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_AI{ p_obj, false, p_player, reinterpret_cast<COLLISIONMAP *>(m_map), LevelOneWidth });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));

	//Set transfrom.
	p_transform->Translate(-15.0f, -5.0f);
	p_transform->Scale(80.0f / TILESCALE / 2.4f, 160.0f / TILESCALE / 2.4f);

	//Set box collider.
	p_box->Set_Size(1.0f, 2.0f);

	//Load sprites.
	p_tex = Load_Texture("res/Animation_Zombie_Idle.png", "ZombieIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Zombie_Wander.png", "ZombieWander", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Zombie_Chase.png", "ZombieChase", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Zombie_Idle_Red.png", "ZombieIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Zombie_Wander_Red.png", "ZombieWanderRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Zombie_Chase_Red.png", "ZombieChaseRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Zombie_Death.png", "ZombieDeath", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ZombieIdle");


	/*****************************************************************************/
	/*                      Create Normal Zombie End                             */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                         Create Speedster                                  */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("EnemySpeed", T_ENEMY);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_AI{ p_obj, false, p_player, reinterpret_cast<COLLISIONMAP *>(m_map), LevelOneWidth, 110.0f });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));

	//Set transform.
	p_transform->Translate(-15.0f, -5.0f);
	p_transform->Scale(80.0f / TILESCALE / 2.4f, 160.0f / TILESCALE / 2.4f);

	//Set box collider.
	p_box->Set_Size(1.0f, 2.0f);

	//Load sprites.
	p_tex = Load_Texture("res/Animation_Speedster_Idle.png", "ZombieIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Speedster_Wander.png", "ZombieWander", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Speedster_Chase.png", "ZombieChase", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Speedster_Idle_Red.png", "ZombieIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Speedster_Wander_Red.png", "ZombieWanderRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Speedster_Chase_Red.png", "ZombieChaseRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Speedster_Death.png", "ZombieDeath", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ZombieIdle");

	/*****************************************************************************/
	/*                         Create Speedster End                              */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                           Create Bloater                                  */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("Bloater", T_ENEMY);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_AIBloater{ p_obj, p_player, reinterpret_cast<COLLISIONMAP *>(m_map), LevelOneWidth });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));

	//Set transform.
	p_transform->Scale(80.0f / TILESCALE / 2.4f, 160.0f / TILESCALE / 2.4f);
	p_transform->Translate(-5.0f, -5.0f);

	//Set box collider.
	p_box->Set_Size(1.0f, 2.0f);

	//Load sprites.
	p_tex = Load_Texture("res/Animation_Bloater_Idle.png", "BloaterIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Bloater_Wander.png", "BloaterWander", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Bloater_Chase.png", "BloaterChase", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/BuildingBlock.png", "BloaterBoom", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Bloater_Idle_Red.png", "BloaterIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Bloater_Wander_Red.png", "BloaterWanderRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Bloater_Chase_Red.png", "BloaterChaseRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BloaterIdle");

	/*****************************************************************************/
	/*                           Create Bloater End                              */
	/*****************************************************************************/


	/*****************************************************************************/
	/*                           Create Screamer                                 */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("Screamer", T_ENEMY);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_AIScreamer{ p_obj, p_player, reinterpret_cast<COLLISIONMAP *>(m_map), LevelOneWidth });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));

	//Set transform.
	p_transform->Scale(80.0f / TILESCALE / 2.4f, 160.0f / TILESCALE / 2.4f);
	p_transform->Translate(-10.0f, -5.0f);

	//Set box collider.
	p_box->Set_Size(1.0f, 2.0f);

	//Load sprites.
	p_tex = Load_Texture("res/Animation_Screamer_Idle.png", "ScreamerIdle", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Wander.png", "ScreamerWander", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Shoot.png", "ScreamerShoot", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Idle.png", "ScreamerScream", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Death.png", "ScreamerDeath", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Idle_Red.png", "ScreamerIdleRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Wander_Red.png", "ScreamerWanderRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Shoot_Red.png", "ScreamerShootRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Screamer_Idle_Red.png", "ScreamerScreamRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ScreamerIdle");

	/*****************************************************************************/
	/*                         Create Screamer End                               */
	/*****************************************************************************/


	/*****************************************************************************/
	/*                            Create Brute                                   */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("Boss", T_ENEMY);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_AIBoss{ p_obj, p_player });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));
	p_rigid = static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY));

	//Set transform.
	p_transform->Scale(150.0f / TILESCALE, 100.0f / TILESCALE);

	//Set box collider.
	p_box->Set_Size(3.0f, 3.0f);

	//Load sprites.
	p_tex = Load_Texture("res/Animation_Brute_Charge.png", "BossCharge", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Brute_Death.png", "BossDeath", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Brute_Roar.png", "BossRoar", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Brute_Throw.png", "BossThrow", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Brute_Charge_Red.png", "BossChargeRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Brute_Death_Red.png", "BossDeathRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Brute_Roar_Red.png", "BossRoarRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Animation_Brute_Throw_Red.png", "BossThrowRed", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("BossCharge");

	/*****************************************************************************/
	/*                          Create Brute End                                 */
	/*****************************************************************************/


	/*****************************************************************************/
	/*                          Create Bullet                                    */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("Bullet", T_BULLET);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_Bullet{ p_obj });

	//Assign variables.
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));
	p_rigid = static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY));

	//Set transform.
	p_transform->Scale(100.0f / TILESCALE / 5, 100.0f / TILESCALE / 5);

	//Set box collider.
	p_box->Set_Size(100.0f / TILESCALE / 5, 100.0f / TILESCALE / 5);

	//Set reigid body.
	p_rigid->Set_Friction(0);
	p_rigid->Set_Gravity(false);

	//Load Sprite.
	p_tex = Load_Texture("res/Bullet.png", "Bullet");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Bullet");

	/*****************************************************************************/
	/*                          Create Bullet End                                */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                         Create Shotgun Bullet                             */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("ShotgunBullet", T_SHOTGUNBULLET);

	//Add component.
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_ShotgunBullet{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });

	//Assign variables.
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_rigid = static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY));
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_box = static_cast<object::C_BoxCollider*>(p_obj->Find_Component(BOXCOLLIDER));

	p_rigid->Set_Friction(0);
	p_rigid->Set_Gravity(false);

	//Load sprites.
	p_tex = Load_Texture("res/Animation_Shotgun.png", "ShotgunBullet", 0.2f, 5);
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ShotgunBullet");
	p_sprite->Get_Texture()->m_fps = 70.0f;
	p_transform->Scale(200.0f / TILESCALE, 160.0f / TILESCALE);

	p_box->Set_Size(200.0f / TILESCALE, 160.0f / TILESCALE);
	p_box->Set_Ghost(true);

	/*****************************************************************************/
	/*                       Create Shotgun Bullet End                           */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                          Create Boss Bullet                               */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("BossBullet", T_ENEMYBULLET);

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_Rigidbody{ p_obj });

	//Assign variables
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_rigid = static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY));
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));

	//Set transfrom
	p_transform->Scale(2.0f, 2.0f);

	//Load sprite
	p_tex = Load_Texture("res/Rock5.png", "Bullet1");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Bullet1");

	//Set reigid body.
	p_rigid->Set_Friction(0);

	/*****************************************************************************/
	/*                       Create Boss Bullet End                              */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                          Create Checkpoint                                */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("Checkpoint", T_CHECKPOINT);

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Checkpoint{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Set transfrom
	p_transform->Scale(250.0f / TILESCALE / 6, 250.0f / TILESCALE / 6);

	//Load sprite
	p_tex = Load_Texture("res/LanternOn.png", "LanternOn");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/LanternOff.png", "LanternOff");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("LanternOff");

	/*****************************************************************************/
	/*                          Create Checkpoint End                            */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                            Create Shotgun                                 */
	/*****************************************************************************/

	//Create game object
	p_obj = CreateObject("ShotGunPickUp", T_WEAPON);

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_WeaponPickUp{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Set transfrom
	p_transform->Scale(320.0f / TILESCALE / 5.0f, 110.0f / TILESCALE / 5.0f);

	//Load sprite
	p_tex = Load_Texture("res/ShotgunGlow.png", "ShotGunPickUp");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ShotGunPickUp");

	/*****************************************************************************/
	/*                            Create Shotgun End                             */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                            Create Machinegun                              */
	/*****************************************************************************/

	//Create game object
	p_obj = CreateObject("MachineGunPickUp", T_WEAPON);

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_BoxCollider{ p_obj });
	p_obj->Add_Component(object::C_WeaponPickUp{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Set transfrom
	p_transform->Scale(425.0f / TILESCALE / 5.7f, 175.0f / TILESCALE / 5.7f);

	//Load sprite
	p_tex = Load_Texture("res/MachineGunGlow.png", "MachineGunPickUp");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("MachineGunPickUp");


	/*****************************************************************************/
	/*                         Create Machinegun End                             */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                            Create Healthbar                               */
	/*****************************************************************************/
	//Create game object.
	p_obj = CreateObject("HealthBar");

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Set transfrom
	p_transform->Scale(508.0f / TILESCALE / 2.0f, 130.0f / TILESCALE / 2.0f);

	//Load sprite
	p_tex = Load_Texture("res/HealthBar_0.png", "HealthBar0");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/HealthBar_1.png", "HealthBar1");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/HealthBar_2.png", "HealthBar2");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/HealthBar_3.png", "HealthBar3");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/HealthBar_4.png", "HealthBar4");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/HealthBar_5.png", "HealthBar5");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("HealthBar5");

	/*****************************************************************************/
	/*                         Create Healthbar End                              */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                           Create LifeHUD                                  */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("LifeHUD");

	//Add component
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_Transform{ p_obj });

	//Assign variables
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));

	//Load sprite
	p_tex = Load_Texture("res/Heart_Animation.png", "LifeHUDAnimate", 0.25f, 4);
	p_tex->m_fps = 9.0f;
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("LifeHUDAnimate");
	p_sprite->Set_Animate(false);

	//Set transform.
	p_transform->Scale(75.0f / TILESCALE / 1.5f, 71.0f / TILESCALE / 1.5f);

	/*****************************************************************************/
	/*                           Create LifeHUD End                              */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                              Create GunHUD                                */
	/*****************************************************************************/

	//Create game object.
	p_obj = CreateObject("GunHUD");

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));

	//Set transform.
	p_transform->Scale(200.0f / TILESCALE / 3.5f, 200.0f / TILESCALE / 3.5f);

	//Load sprite
	p_tex = Load_Texture("res/Pistol.png", "Pistol");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/MachineGun.png", "MachineGun");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Shotgun.png", "Shotgun");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Pistol");

	/*****************************************************************************/
	/*                           Create GunHUD End                               */
	/*****************************************************************************/

	/*****************************************************************************/
	/*                           Create Ammo HUD                                 */
	/*****************************************************************************/
	//Create font
	m_ammo_max_font = AEGfxCreateFont("Arial.ttf", 50, true, false);
	m_ammo_min_font = AEGfxCreateFont("Arial.ttf", 40, true, false);

	//Create game object
	p_obj = CreateObject("AmmoText");

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_SpriteText{ p_obj });

	//Add sprite text component
	object::C_SpriteText *p_spritetext = static_cast<object::C_SpriteText*>(p_obj->Find_Component(SPRITETEXT));
	p_spritetext->Set_Color(0xFF, 0xFF, 0xFF);
	p_spritetext->Set_Buffer("0");

	//Create game object
	p_obj = CreateObject("AmmoTextDivider");

	//Add component
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Add sprite text component
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Slash.png", "Slash");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Slash");
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_transform->Scale(57.0f / TILESCALE / 2.2f, 97.0f / TILESCALE / 2.2f);

	/*****************************************************************************/
	/*                          Create Ammo HUD End                              */
	/*****************************************************************************/

	/////////////////////////// TRANSITION BOX ///////////////////////////////////////////

	/////////// CREATE OBJECT ///////////////////
	p_obj = CreateObject("TransitionBox");

	////////// ADD COMPONENTS ///////////////////
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_FadeOut{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Tile.png", "TransitionSprite");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("TransitionSprite");
	p_transform->Scale(50.0f / TILESCALE / 0.005f, 50.0f / TILESCALE / 0.005f);

	/////////////////////////// TRANSITION BOX END /////////////////////////////////////////

	/*****************************************************************************/
	/*                          Create pause menu                                */
	/*****************************************************************************/

	/////////// CREATE OBJECT ///////////////////
	p_obj = CreateObject("MenuBox");

	////////// ADD COMPONENTS ///////////////////
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_MenuController{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/PausePanel.png", "MenuBox");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("MenuBox");
	p_transform->Scale(1100.0f / TILESCALE / 3.0f, 1180.0f / TILESCALE / 2.25f);

	////////////////////////// PAUSE HEADER //////////////////////////////////////////
	p_obj = CreateObject("PauseHeader");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Pause.png", "PauseHeader");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("PauseHeader");
	p_transform->Scale(410.0f / TILESCALE, 77.0f / TILESCALE);

	////////////////////////// RESUME BUTTON //////////////////////////////////////////
	p_obj = CreateObject("ResumeButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/ResumeGame.png", "ResumeButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/ResumeGame_Highlighted.png", "ResumeButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ResumeButtonGlow");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	////////////////////////// HOW TO PLAY BUTTON //////////////////////////////////////
	p_obj = CreateObject("HowToPlayButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/HowToPlay_button.png", "HowToPlayButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/HowToPlay_highlighted.png", "HowToPlayButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("HowToPlayButton");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	////////////////////////// OPTIONS BUTTON //////////////////////////////////////////
	p_obj = CreateObject("OptionsButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite//
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Options.png", "OptionsButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/OptionsGlow.png", "OptionsButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("OptionsButton");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	////////////////////////// RESTART BUTTON //////////////////////////////////////////
	p_obj = CreateObject("RestartButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite//
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Restart.png", "RestartButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Restart_Highlighted.png", "RestartButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("RestartButton");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	/////////////////////////////// CREDITS BUTTON ///////////////////////////////
	p_obj = CreateObject("CreditsButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	///////////// SPRITE COMPONENT /////////////////////
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Credits.png", "CreditsButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/CreditsGlow.png", "CreditsButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("CreditsButton");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);
	/////////////////////////////// CREDITS BUTTON ///////////////////////////////

	////////////////////////// QUIT BUTTON //////////////////////////////////////////
	p_obj = CreateObject("QuitButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite//
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/QuitGame.png", "QuitButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/QuitGame_Highlighted.png", "QuitButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("QuitButton");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);


	/*****************************************************************************/
	/*                          Create Pause Menu End                            */
	/*****************************************************************************/

	/////////////////////////// CONFIRMATION HEADER //////////////////////////////////
	p_obj = CreateObject("ConfirmationHeader");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/ReturnToMenu.png", "ConfirmationHeader");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("ConfirmationHeader");
	p_transform->Scale(410.0f / TILESCALE / 1.25f, 154.0f / TILESCALE / 1.25f);

	/////////////////////////// YES BUTTON //////////////////////////////////////////
	p_obj = CreateObject("YesButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BigYes.png", "YesButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/BigYes_highlighted.png", "YesButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("YesButton");
	p_transform->Scale(410.0f / TILESCALE / 1.5f, 77.0f / TILESCALE / 1.5f);

	/////////////////////////// NO BUTTON //////////////////////////////////////////
	p_obj = CreateObject("NoButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/BigNo.png", "NoButton");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/BigNo_highlighted.png", "NoButtonGlow");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("NoButtonGlow");
	p_transform->Scale(410.0f / TILESCALE / 1.5f, 77.0f / TILESCALE / 1.5f);

	/////////////////////////// LEVEL CLEARED HEADER /////////////////////////////////
	p_obj = CreateObject("LevelClearedHeader");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/YouSurvive_text.png", "LevelClearedHeader");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("LevelClearedHeader");
	p_transform->Scale(582.0f / TILESCALE / 2.0f, 105.0f / TILESCALE / 2.0f);

	/////////////////////////// TRY AGAIN HEADER /////////////////////////////////
	p_obj = CreateObject("TryAgainHeader");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/GameOver_Text.png", "TryAgainHeader");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("TryAgainHeader");
	p_transform->Scale(611.0f / TILESCALE / 2.0f, 226.0f / TILESCALE / 2.0f);

	/////////////////////////// FULLSCREEN BUTTON //////////////////////////////////
	p_obj = CreateObject("FullscreenButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite//
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/FullScreen.png", "FullScreen");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/FullScreen_Highlight.png", "FullScreenHighlighted");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("FullScreenHighlighted");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	/////////////////////////// SOUNDFX BUTTON //////////////////////////////////
	p_obj = CreateObject("SoundFXButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite//
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/SoundFX.png", "SoundFX");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/SoundFX_Highlight.png", "SoundFXHighlighted");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("SoundFX");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	/////////////////////// BACK BUTTON //////////////////////////////////
	p_obj = CreateObject("BackButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite//
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Back.png", "Back");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/Back_Highlighted.png", "BackHighlighted");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Back");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	/////////////////////////// YES/NO BUTTON //////////////////////////////////
	p_obj = CreateObject("YesNoButton");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Yes_Highlighted.png", "YesHighlight");
	p_sprite->Add_Texture(p_tex);
	p_tex = Load_Texture("res/No_Highlighted.png", "NoHighlight");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("YesHighlight");
	p_transform->Scale(410.0f / TILESCALE / 2.0f, 77.0f / TILESCALE / 2.0f);

	/////////////////////////// ESCAPE TO CONTINUE //////////////////////////////////
	p_obj = CreateObject("Escape");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Escape.png", "Escape");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Escape");
	p_transform->Scale(409.0f / TILESCALE, 53.0f / TILESCALE);

	//////////////////////////// CREDITS SCREEN ////////////////////////////////////
	p_obj = CreateObject("CreditsScreen");

	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });
	p_obj->Add_Component(object::C_MenuController{ p_obj });

	///////////// SPRITE COMPONENT /////////////////////
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/CreditScreenBorder.png", "CreditsScreen");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("CreditsScreen");
	p_transform->Scale(1024.0f / TILESCALE / 1.25f, 768.0f / TILESCALE / 1.25f);

	/////////////////////////// ENTER TO CONTINUE //////////////////////////////////
	p_obj = CreateObject("Continue");
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_Sprite{ p_obj });

	//Load sprite
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_sprite = static_cast<object::C_Sprite*>(p_obj->Find_Component(SPRITE));
	p_tex = Load_Texture("res/Continue.png", "Continue");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("Continue");
	p_transform->Scale(521.0f / TILESCALE / 1.25f, 53.0f / TILESCALE / 1.25f);

	////////////////// PICKUP PARTICLE /////////////////////////////////////////////////
	//Create game object.
	mp_pickup_particle_prefab = CreateObject("PickupParticle");

	/////////////// ADD COMPONENTS ////////////////////
	mp_pickup_particle_prefab->Add_Component(object::C_Transform{ p_obj });
	mp_pickup_particle_prefab->Add_Component(object::C_Sprite{ p_obj });
	mp_pickup_particle_prefab->Add_Component(object::C_Rigidbody{ p_obj });
	mp_pickup_particle_prefab->Add_Component(object::C_Particle{ p_obj });

	//Assign variables
	p_sprite = static_cast<object::C_Sprite*>(mp_pickup_particle_prefab->Find_Component(SPRITE));
	p_rigid = static_cast<object::C_Rigidbody*>(mp_pickup_particle_prefab->Find_Component(RIGIDBODY));

	/////////////// COMPONENT /////////////////////
	p_rigid->Set_Gravity(false);
	p_tex = Load_Texture("res/CircleGlowParticle.png", "CircleGlowParticle");
	p_sprite->Add_Texture(p_tex);
	p_sprite->Set_Texture("CircleGlowParticle");
	////////////////// PICKUP PARTICLE END ///////////////////////////////////////////

	////////////////// PICKUP SYSTEM/////////////////////////////////////////////////
	//Create game object.
	p_obj = CreateObject("PickupParticleSystem");

	/////////////// ADD COMPONENTS ////////////////////
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_ParticleSystem{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_particlesys = static_cast<object::C_ParticleSystem*>(p_obj->Find_Component(PARTICLESYSTEM));

	/////////////// COMPONENT INITIALISE /////////////////////
	p_particlesys->Set_Particle(mp_pickup_particle_prefab);
	p_particlesys->Set_MinParticles(20);
	p_particlesys->Set_MaxParticles(40);
	p_particlesys->Set_Loop(true);
	p_particlesys->Set_Pattern(object::ParticleType::PT_PICKUP);
	////////////////// PICKUP SYSTEM END ///////////////////////////////////////////

	////////////////// RAIN PARTICLE /////////////////////////////////////////////////
	//Create game object.
	mp_rain_particle_prefab = CreateObject("RainParticle");

	/////////////// ADD COMPONENTS ////////////////////
	mp_rain_particle_prefab->Add_Component(object::C_Transform{ p_obj });
	mp_rain_particle_prefab->Add_Component(object::C_Sprite{ p_obj });
	mp_rain_particle_prefab->Add_Component(object::C_Rigidbody{ p_obj });
	mp_rain_particle_prefab->Add_Component(object::C_Particle{ p_obj });

	//Assign variables
	p_sprite = static_cast<object::C_Sprite*>(mp_rain_particle_prefab->Find_Component(SPRITE));
	p_rigid = static_cast<object::C_Rigidbody*>(mp_rain_particle_prefab->Find_Component(RIGIDBODY));

	/////////////// COMPONENT /////////////////////
	p_sprite->Set_RGB(227.0f, 233.0f, 242.0f);
	p_rigid->Set_Gravity(false);
	////////////////// RAIN PARTICLE END ///////////////////////////////////////////

	////////////////// RAIN PARTICLE SYSTEM/////////////////////////////////////////////////
	//Create game object.///////////////////////////
	p_obj = CreateObject("RainParticleSystem");

	/////////////// ADD COMPONENTS ////////////////////
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_ParticleSystem{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_particlesys = static_cast<object::C_ParticleSystem*>(p_obj->Find_Component(PARTICLESYSTEM));

	/////////////// COMPONENT INITIALISE /////////////////////
	p_particlesys->Set_Particle(mp_rain_particle_prefab);
	p_particlesys->Set_MinParticles(75);
	p_particlesys->Set_MaxParticles(150);
	p_particlesys->Set_Loop(true);
	p_particlesys->Set_Pattern(object::ParticleType::PT_RAIN);

	////////////////// RAIN PARTICLE SYSTEM END ///////////////////////////////////////////

	////////////////// SMOKE PARTICLE /////////////////////////////////////////////////
	//Create game object.
	mp_smoke_particle_prefab = CreateObject("SmokeParticle");

	/////////////// ADD COMPONENTS ////////////////////
	mp_smoke_particle_prefab->Add_Component(object::C_Transform{ p_obj });
	mp_smoke_particle_prefab->Add_Component(object::C_Sprite{ p_obj });
	mp_smoke_particle_prefab->Add_Component(object::C_Rigidbody{ p_obj });
	mp_smoke_particle_prefab->Add_Component(object::C_Particle{ p_obj });

	//Assign variables
	p_sprite = static_cast<object::C_Sprite*>(mp_smoke_particle_prefab->Find_Component(SPRITE));
	p_rigid = static_cast<object::C_Rigidbody*>(mp_smoke_particle_prefab->Find_Component(RIGIDBODY));

	/////////////// COMPONENT /////////////////////
	p_sprite->Set_RGB(180.0f, 190.0f, 200.0f);
	p_rigid->Set_Gravity(false);
	////////////////// SMOKE PARTICLE END ///////////////////////////////////////////

	////////////////// SMOKE SYSTEM/////////////////////////////////////////////////
	//Create game object.///////////////////////////
	p_obj = CreateObject("SmokeParticleSystem");

	/////////////// ADD COMPONENTS ////////////////////
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_ParticleSystem{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_particlesys = static_cast<object::C_ParticleSystem*>(p_obj->Find_Component(PARTICLESYSTEM));

	/////////////// COMPONENT INITIALISE /////////////////////
	p_particlesys->Set_Particle(mp_smoke_particle_prefab);
	p_particlesys->Set_MinParticles(75);
	p_particlesys->Set_MaxParticles(150);
	p_particlesys->Set_Loop(true);
	p_particlesys->Set_Pattern(object::ParticleType::PT_BLOATERSMOKE);

	////////////////// SMOKE SYSTEM END ///////////////////////////////////////////

	////////////////// SPIT PARTICLE /////////////////////////////////////////////////
	//Create game object.///////////////////////////
	mp_spit_particle_prefab = CreateObject("SpitParticle", T_ENEMYBULLET);

	/////////////// ADD COMPONENTS ////////////////////
	mp_spit_particle_prefab->Add_Component(object::C_Transform{ p_obj });
	mp_spit_particle_prefab->Add_Component(object::C_Sprite{ p_obj });
	mp_spit_particle_prefab->Add_Component(object::C_BoxCollider{ p_obj });
	mp_spit_particle_prefab->Add_Component(object::C_Rigidbody{ p_obj });
	mp_spit_particle_prefab->Add_Component(object::C_Particle{ p_obj });

	//Assign variables
	p_sprite = static_cast<object::C_Sprite*>(mp_spit_particle_prefab->Find_Component(SPRITE));
	p_rigid = static_cast<object::C_Rigidbody*>(mp_spit_particle_prefab->Find_Component(RIGIDBODY));

	/////////////// COMPONENT /////////////////////
	p_sprite->Set_RGB(151.0f, 198.0f, 139.0f);
	p_rigid->Set_Gravity(true);
	////////////////// SPIT PARTICLE END ///////////////////////////////////////////

	////////////////// SPIT SYSTEM/////////////////////////////////////////////////
	//Create game object.///////////////////////////
	p_obj = CreateObject("SpitParticleSystem");

	/////////////// ADD COMPONENTS ////////////////////
	p_obj->Add_Component(object::C_Transform{ p_obj });
	p_obj->Add_Component(object::C_ParticleSystem{ p_obj });

	//Assign variables
	p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));
	p_particlesys = static_cast<object::C_ParticleSystem*>(p_obj->Find_Component(PARTICLESYSTEM));

	/////////////// COMPONENT INITIALISE /////////////////////
	p_particlesys->Set_Particle(mp_spit_particle_prefab);
	p_particlesys->Set_MinParticles(5);
	p_particlesys->Set_MaxParticles(10);
	p_particlesys->Set_Loop(false);
	p_particlesys->Set_Collidable(true);
	p_particlesys->Set_Pattern(object::ParticleType::PT_SCREAMERSPIT);

	////////////////// SPIT SYSTEM END ///////////////////////////////////////////

	/////////////////////////// SOUNDFILES ///////////////////////////////////////////

	m_sound_system.Init();
	m_sound_system.Create_Sound("res/Sounds/BloaterDeath.ogg", SOUNDEFFECTE, SFX, "BloaterDeath");
	m_sound_system.Create_Sound("res/Sounds/BrokenPipe.ogg", SOUNDEFFECT, SFX, "BrokenPipe");
	m_sound_system.Create_Sound("res/Sounds/Burning.ogg", SOUNDEFFECT, SFX, "Burning");
	m_sound_system.Create_Sound("res/Sounds/Death.ogg", SOUNDEFFECTP, SFX, "Death");
	m_sound_system.Create_Sound("res/Sounds/HeartBeat.ogg", SOUNDEFFECTP, SFX, "HeartBeat");
	m_sound_system.Create_Sound("res/Sounds/MachineGun.ogg", SOUNDEFFECTP, SFX, "MachineGun");
	m_sound_system.Create_Sound("res/Sounds/Pistol.ogg", SOUNDEFFECTP, SFX, "Pistol");
	m_sound_system.Create_Sound("res/Sounds/PlayerDamge.ogg", SOUNDEFFECTP, SFX, "PlayerDamge");
	m_sound_system.Create_Sound("res/Sounds/Rain.ogg", BACKGROUND, BGM, "Rain");
	m_sound_system.Create_Sound("res/Sounds/Screamer.ogg", SOUNDEFFECTE, SFX, "Screamer");
	m_sound_system.Create_Sound("res/Sounds/Shotgun.ogg", SOUNDEFFECTP, SFX, "Shotgun");
	m_sound_system.Create_Sound("res/Sounds/Thunder.ogg", SOUNDEFFECT, SFX, "Thunder");
	m_sound_system.Create_Sound("res/Sounds/WeaponPickup.ogg", SOUNDEFFECTP, SFX, "WeaponPickup");
	m_sound_system.Create_Sound("res/Sounds/Zap.ogg", SOUNDEFFECT, SFX, "Zap");
	m_sound_system.Create_Sound("res/Sounds/ZombieGrowl.ogg", SOUNDEFFECTE, SFX, "ZombieGrowl");
	m_sound_system.Create_Sound("res/Sounds/ZombieGrunt.ogg", SOUNDEFFECTE, SFX, "ZombieGrunt");
	m_sound_system.Create_Sound("res/Sounds/DEEPWATERS.ogg", BACKGROUND, BGM, "DEEPWATERS");
	m_sound_system.Create_Sound("res/Sounds/FLOORIT.ogg", BACKGROUND, BGM, "FLOORIT");
	m_sound_system.Create_Sound("res/Sounds/UNTIMELYDEMISE.ogg", BACKGROUND, BGM, "UNTIMELYDEMISE");
	m_sound_system.Create_Sound("res/Sounds/BossDeath.ogg", SOUNDEFFECTE, SFX, "BossDeath");
	m_sound_system.Create_Sound("res/Sounds/BruteLand.ogg", SOUNDEFFECTE, SFX, "BruteLand");


	/////////////////// LOAD MAPDATA ///////////////////////////////////////////////

	SetMap("levelone.txt");

	/////////////////// END LOADING MAPDATA /////////////////////////////////////////
}
/*****************************************************************************/
/*!
  Initalise Level one
*/
/*****************************************************************************/
void C_LevelOne::Init()
{
	m_camerashake = false;
	cameralock = false;
	// Menu
	m_menu_active = false;
	m_howtoplay_active = false;
	m_options_active = false;
	m_credits_active = false;
	m_confirmation_active = false;
	m_lose_active = false;
	m_win_active = false;

	// ALWAYS INIT CAMERA
	utilities::C_Camera::Init();

	object::C_GameObject *p_obj;

	p_obj = CreateObjectInstance("Background");
	p_obj->Set_Active(true);
	static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM))->Set_PositionX(100);
	static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM))->Set_PositionY(25, 1);

	p_obj = CreateObjectInstance("DirectionalKeys");
	p_obj->Set_Active(true);
	static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM))->Set_Position(8, 42);

	p_obj = CreateObjectInstance("JumpButton");
	p_obj->Set_Active(true);
	static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM))->Set_Position(19, 35);

	p_obj = CreateObjectInstance("ShootButton");
	p_obj->Set_Active(true);
	static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM))->Set_Position(32, 28);

	/////////////// CREATE STATIC TILES /////////////////////////////////////

	CreateMap();



	/////////////// 1 PLAYER INSTANCE CREATED /////////////
	p_player = CreateObjectInstance("Player");
	////////////// CONNECT EVENTS ///////////////////////
	static_cast<object::C_Player*>(p_player->Find_Component(PLAYER))->Connect();

	//////////////// 5 CHECKPOINT INSTANCES CREATED //////////////
	for (int i = 0; i < 5; ++i)
	{
		p_obj = CreateObjectInstance("Checkpoint");
		auto p_checkpoint = static_cast<object::C_Checkpoint*>(p_obj->Find_Component(CUSTOM));
		p_checkpoint->Connect();
		p_checkpoint->Set_Player_Transform(static_cast<object::C_Transform*>(p_player->Find_Component(TRANSFORM))->Get_Transform());
	}

	//////////////// CREATE MAX_BULLET_BOSS NUMBER OF BULLETS ////////////////
	// Current value = 200
	for (int i = 0; i < MAX_BULLET_PLAYER; ++i)
	{
		p_obj = CreateObjectInstance("Bullet");

		////////// CONNECT EVENTS ////////////////
		static_cast<object::C_Bullet*>(p_obj->Find_Component(BULLET))->Connect();
	}

	//////////////// CREATE MAX_SHOTGUN_BULLET NUMBER OF BULLETS ////////////////
	// Current value = 15
	for (int i = 0; i < MAX_SHOTGUN_BULLET; ++i)
	{
		p_obj = CreateObjectInstance("ShotgunBullet");

		////////// CONNECT EVENTS ////////////////
		static_cast<object::C_ShotgunBullet*>(p_obj->Find_Component(BULLET))->Connect();
	}

	//////////////// CREATE MAX_BULLET_BOSS NUMBER OF BULLETS ////////////////
	// Current value = 50
	for (int i = 0; i < MAX_BULLET_BOSS; ++i)
	{
		p_obj = CreateObjectInstance("BossBullet");
	}

	////////////// 5 BLOATER INSTANCES CREATED ////////////
	for (int i = 0; i < 2; i++)
	{
		p_obj = CreateObjectInstance("Bloater");
		static_cast<object::C_AIBloater*>(p_obj->Find_Component(AIBLOATER))->Set_Player(p_player);

		/////////////// SMOKE PARTICLE SYSTE< CREATED /////////////
		mp_smoke_particleobj = CreateObjectInstance("SmokeParticleSystem");
		mp_smoke_particlesys = static_cast<object::C_ParticleSystem*>(mp_smoke_particleobj->Find_Component(PARTICLESYSTEM));
		mp_smoke_particlesys->Connect();
		mp_smoke_particleobj->Destroy();

		static_cast<object::C_AIBloater*>(p_obj->Find_Component(AIBLOATER))->Set_Smoke_Sys(mp_smoke_particleobj);
		/////////////// CONNECT EVENTS //////////////////////
		static_cast<object::C_AIBloater*>(p_obj->Find_Component(AIBLOATER))->Connect();
	}

	////////////// 5 SCREAMER INSTANCES CREATED ////////////
	for (int i = 0; i < 5; i++)
	{
		p_obj = CreateObjectInstance("Screamer");
		static_cast<object::C_AIScreamer*>(p_obj->Find_Component(AISCREAM))->Set_Player(p_player);

		/////////////// SPIT PARTICLE SYSTEM CREATED /////////////
		mp_spit_particleobj = CreateObjectInstance("SpitParticleSystem");
		mp_spit_particlesys = static_cast<object::C_ParticleSystem*>(mp_spit_particleobj->Find_Component(PARTICLESYSTEM));
		mp_spit_particlesys->Connect();
		mp_spit_particleobj->Destroy();

		static_cast<object::C_AIScreamer*>(p_obj->Find_Component(AISCREAM))->Set_Spit_Sys(mp_spit_particleobj);

		/////////////// CONNECT EVENTS //////////////////////
		static_cast<object::C_AIScreamer*>(p_obj->Find_Component(AISCREAM))->Connect();
	}

	////////////// 30 ENEMY INSTANCES CREATED ////////////
	for (int i = 0; i < 30; i++)
	{
		p_obj = CreateObjectInstance("Enemy");
		static_cast<object::C_AI*>(p_obj->Find_Component(AI))->Set_Player(p_player);
		/////////////// CONNECT EVENTS //////////////////////
		static_cast<object::C_AI*>(p_obj->Find_Component(AI))->Connect();
	}

	////////////// 10 ENEMYSPEED INSTANCES CREATED ////////////
	for (int i = 0; i < 10; i++)
	{
		p_obj = CreateObjectInstance("EnemySpeed");
		static_cast<object::C_AI*>(p_obj->Find_Component(AI))->Set_Player(p_player);
		/////////////// CONNECT EVENTS //////////////////////
		static_cast<object::C_AI*>(p_obj->Find_Component(AI))->Connect();
	}

	////////////// BOSS /////////////////////////////////
	p_obj = CreateObjectInstance("Boss");
	static_cast<object::C_AIBoss*>(p_obj->Find_Component(AIBOSS))->Connect();

	// shotgun pickup 
	mp_pickup_particleobj = CreateObjectInstance("PickupParticleSystem");
	static_cast<object::C_ParticleSystem*>(mp_pickup_particleobj->Find_Component(PARTICLESYSTEM))->Connect();
	p_obj = CreateObjectInstance("ShotGunPickUp");
	object::C_WeaponPickUp *p_pickup = static_cast<object::C_WeaponPickUp*>(p_obj->Find_Component(CUSTOM));
	p_pickup->Set_Aura(mp_pickup_particleobj);
	p_pickup->Connect();

	// machine gun pickup
	mp_pickup_particleobj = CreateObjectInstance("PickupParticleSystem");
	static_cast<object::C_ParticleSystem*>(mp_pickup_particleobj->Find_Component(PARTICLESYSTEM))->Connect();
	p_obj = CreateObjectInstance("MachineGunPickUp");
	p_pickup = static_cast<object::C_WeaponPickUp*>(p_obj->Find_Component(CUSTOM));
	p_pickup->Set_Aura(mp_pickup_particleobj);
	p_pickup->Connect();


	mp_rain_particlesys = CreateObjectInstance("RainParticleSystem");
	mp_rain_particlesys->Set_Active(true);
	static_cast<object::C_ParticleSystem*>(mp_rain_particlesys->Find_Component(PARTICLESYSTEM))->Connect();

	/////////////// CREATE HUD INSTANCES ////////////////////////////////////
	// Life
	m_player_life = static_cast<object::C_Player*>(p_player->Find_Component(PLAYER))->Get_Life();
	for (int i = 0; i < PLAYER_MAX_LIFE; ++i)
		mp_life_hud[i] = CreateObjectInstance("LifeHUD");

	mp_health = CreateObjectInstance("HealthBar");

	mp_health_indicator = CreateObjectInstance("LifeHUD");
	static_cast<object::C_Transform*>(mp_health_indicator->Find_Component(TRANSFORM))->Scale(75.0f / TILESCALE / 2.0f, 71.0f / TILESCALE / 2.0f);

	// Gun Hud
	mp_gun_hud = CreateObjectInstance("GunHUD");

	// Ammo Text Divider
	mp_ammo_divider = CreateObjectInstance("AmmoTextDivider");

	// Ammo Text
	mp_ammo_min_text = CreateObjectInstance("AmmoText");
	object::C_SpriteText *p_spritetext = static_cast<object::C_SpriteText*>(mp_ammo_min_text->Find_Component(SPRITETEXT));
	p_spritetext->Set_Font_Id(m_ammo_min_font);

	mp_ammo_max_text = CreateObjectInstance("AmmoText");
	p_spritetext = static_cast<object::C_SpriteText*>(mp_ammo_max_text->Find_Component(SPRITETEXT));
	p_spritetext->Set_Font_Id(m_ammo_max_font);

	// TransitionSprite
	p_obj = CreateObjectInstance("TransitionBox");
	object::C_FadeOut *p_fade_effect = static_cast<object::C_FadeOut*>(p_obj->Find_Component(CUSTOM));
	p_fade_effect->Set_Fade_Out(true);
	p_fade_effect->Set_Fade_Out_Speed(0.5f);
	p_fade_effect->Set_Wait_Time(0.4);
	p_fade_effect->Connect();

	// Menu Box
	mp_menu_box = CreateObjectInstance("MenuBox");
	object::C_MenuController *p_menu_controller = static_cast<object::C_MenuController*>(mp_menu_box->Find_Component(CUSTOM));
	p_menu_controller->Set_Max_Selection(6);
	p_menu_controller->Set_Close("CloseMenu");
	p_menu_controller->Set_Refresh("RefreshMenu");
	p_menu_controller->Set_Execute("ExecuteMenu");
	p_menu_controller->Set_Mode(object::MENUMODE::PAUSEMENU);
	p_menu_controller->Connect();
	mp_menu_header = CreateObjectInstance("PauseHeader");
	mp_resume_button = CreateObjectInstance("ResumeButton");
	mp_howtoplay_button = CreateObjectInstance("HowToPlayButton");
	mp_options_button = CreateObjectInstance("OptionsButton");
	mp_restart_button = CreateObjectInstance("RestartButton");
	mp_credits_button = CreateObjectInstance("CreditsButton");
	mp_quit_button = CreateObjectInstance("QuitButton");
	mp_menu_box->Destroy();
	mp_menu_header->Destroy();
	mp_howtoplay_button->Destroy();
	mp_resume_button->Destroy();
	mp_options_button->Destroy();
	mp_restart_button->Destroy();
	mp_credits_button->Destroy();
	mp_quit_button->Destroy();

	// HowToPlay Box
	mp_howtoplay_box = CreateObjectInstance("MenuBox");
	p_menu_controller = static_cast<object::C_MenuController*>(mp_howtoplay_box->Find_Component(CUSTOM));
	p_menu_controller->Set_Max_Selection(1);
	p_menu_controller->Set_Close("CloseHowToPlay");
	p_menu_controller->Set_Mode(object::MENUMODE::HOWTOPLAYMENU);
	p_menu_controller->Connect();
	static_cast<object::C_Transform*>(mp_howtoplay_box->Find_Component(TRANSFORM))->Scale(1100.0f / TILESCALE / 1.25f, 1080.0f / TILESCALE / 2.0f);
	mp_howtoplay_header = CreateObjectInstance("HowToPlayButton");
	static_cast<object::C_Transform*>(mp_howtoplay_header->Find_Component(TRANSFORM))->Scale(142.0f / TILESCALE / 0.4f, 27.0f / TILESCALE / 0.4f);
	mp_move_key = CreateObjectInstance("DirectionalKeys");
	static_cast<object::C_Transform*>(mp_move_key->Find_Component(TRANSFORM))->Scale(300.0f / TILESCALE / 1.25f, 300.0f / TILESCALE / 1.25f);
	mp_shoot_key = CreateObjectInstance("ShootButton");
	static_cast<object::C_Transform*>(mp_shoot_key->Find_Component(TRANSFORM))->Scale(250.0f / TILESCALE / 1.25f, 200.0f / TILESCALE / 1.25f);
	mp_jump_key = CreateObjectInstance("JumpButton");
	static_cast<object::C_Transform*>(mp_jump_key->Find_Component(TRANSFORM))->Scale(300.0f / TILESCALE / 1.45f, 250.0f / TILESCALE / 1.45f);
	mp_howtoplay_esc = CreateObjectInstance("Escape");
	mp_howtoplay_box->Destroy();
	mp_howtoplay_header->Destroy();
	mp_move_key->Destroy();
	mp_shoot_key->Destroy();
	mp_jump_key->Destroy();
	mp_howtoplay_esc->Destroy();

	// Options Box
	mp_options_box = CreateObjectInstance("MenuBox");
	static_cast<object::C_Transform*>(mp_options_box->Find_Component(TRANSFORM))->Scale(1100.0f / TILESCALE / 2.5f, 1080.0f / TILESCALE / 2.0f);
	p_menu_controller = static_cast<object::C_MenuController*>(mp_options_box->Find_Component(CUSTOM));
	p_menu_controller->Set_Max_Selection(3);
	p_menu_controller->Set_Close("CloseOptions");
	p_menu_controller->Set_Refresh("RefreshOptions");
	p_menu_controller->Set_Execute("ExecuteOptions");
	p_menu_controller->Set_Mode(object::MENUMODE::OPTIONMENU);
	p_menu_controller->Connect();
	mp_options_header = CreateObjectInstance("OptionsButton");
	static_cast<object::C_Transform*>(mp_options_header->Find_Component(TRANSFORM))->Scale(410.0f / TILESCALE, 77.0f / TILESCALE);
	mp_fullscreen_button = CreateObjectInstance("FullscreenButton");
	mp_fullscreen_selector = CreateObjectInstance("YesNoButton");
	mp_soundfx_button = CreateObjectInstance("SoundFXButton");
	mp_soundfx_selector = CreateObjectInstance("YesNoButton");
	mp_options_back = CreateObjectInstance("BackButton");
	mp_options_box->Destroy();
	mp_options_header->Destroy();
	mp_fullscreen_button->Destroy();
	mp_fullscreen_selector->Destroy();
	mp_soundfx_button->Destroy();
	mp_soundfx_selector->Destroy();

	utilities::C_OptionsManager::Get_FullScreen() ? static_cast<object::C_Sprite *>(mp_fullscreen_selector->Find_Component(SPRITE))->Set_Texture("YesHighlight")
		: static_cast<object::C_Sprite *>(mp_fullscreen_selector->Find_Component(SPRITE))->Set_Texture("NoHighlight");
	utilities::C_OptionsManager::Get_SoundFX() ? static_cast<object::C_Sprite *>(mp_soundfx_selector->Find_Component(SPRITE))->Set_Texture("YesHighlight")
		: static_cast<object::C_Sprite *>(mp_soundfx_selector->Find_Component(SPRITE))->Set_Texture("NoHighlight");

	// Credits Box
	mp_credits_box = CreateObjectInstance("CreditsScreen");
	p_menu_controller = static_cast<object::C_MenuController*>(mp_credits_box->Find_Component(CUSTOM));
	p_menu_controller->Set_Max_Selection(1);
	p_menu_controller->Set_Close("CloseCredits");
	p_menu_controller->Set_Mode(object::MENUMODE::HOWTOPLAYMENU);
	p_menu_controller->Connect();
	mp_credits_esc = CreateObjectInstance("Escape");
	mp_credits_box->Destroy();
	mp_credits_esc->Destroy();

	// Win Box
	mp_win_box = CreateObjectInstance("MenuBox");
	p_menu_controller = static_cast<object::C_MenuController*>(mp_win_box->Find_Component(CUSTOM));
	p_menu_controller->Set_Max_Selection(1);
	p_menu_controller->Set_Close("CloseWinMenu");
	p_menu_controller->Set_Esc_Close(false);
	p_menu_controller->Set_Mode(object::MENUMODE::WINMENU);
	p_menu_controller->Connect();
	static_cast<object::C_Transform*>(mp_win_box->Find_Component(TRANSFORM))->Scale(1100.0f / TILESCALE / 2.25f, 1080.0f / TILESCALE / 4.0f);
	mp_win_header = CreateObjectInstance("LevelClearedHeader");
	mp_continue = CreateObjectInstance("Continue");
	mp_win_box->Destroy();
	mp_win_header->Destroy();
	mp_continue->Destroy();

	// Lose Box
	mp_lose_box = CreateObjectInstance("MenuBox");
	p_menu_controller = static_cast<object::C_MenuController*>(mp_lose_box->Find_Component(CUSTOM));
	p_menu_controller->Set_Max_Selection(2);
	p_menu_controller->Set_Close("CloseLoseMenu");
	p_menu_controller->Set_Refresh("RefreshLoseMenu");
	p_menu_controller->Set_Execute("ExecuteLoseMenu");
	p_menu_controller->Set_Esc_Close(false);
	p_menu_controller->Set_Mode(object::MENUMODE::PAUSEMENU);
	p_menu_controller->Connect();
	static_cast<object::C_Transform*>(mp_lose_box->Find_Component(TRANSFORM))->Scale(482.0f / TILESCALE, 477.0f / TILESCALE / 1.4f);
	mp_lose_header = CreateObjectInstance("TryAgainHeader");
	mp_lose_yes_button = CreateObjectInstance("YesButton");
	static_cast<object::C_Sprite*>(mp_lose_yes_button->Find_Component(SPRITE))->Set_Texture("YesButtonGlow");
	mp_lose_no_button = CreateObjectInstance("NoButton");
	static_cast<object::C_Sprite*>(mp_lose_no_button->Find_Component(SPRITE))->Set_Texture("NoButton");
	mp_lose_box->Destroy();
	mp_lose_header->Destroy();
	mp_lose_yes_button->Destroy();
	mp_lose_no_button->Destroy();

	// Confirmation Box
	mp_confirmation_box = CreateObjectInstance("MenuBox");
	p_menu_controller = static_cast<object::C_MenuController*>(mp_confirmation_box->Find_Component(CUSTOM));
	p_menu_controller->Set_Max_Selection(2);
	p_menu_controller->Set_Close("CloseConfirmation");
	p_menu_controller->Set_Refresh("RefreshConfirmation");
	p_menu_controller->Set_Execute("ExecuteConfirmation");
	p_menu_controller->Set_Mode(object::MENUMODE::PAUSEMENU);
	p_menu_controller->Connect();
	static_cast<object::C_Transform*>(mp_confirmation_box->Find_Component(TRANSFORM))->Scale(482.0f / TILESCALE, 477.0f / TILESCALE / 1.4f);
	mp_confirmation_header = CreateObjectInstance("ConfirmationHeader");
	mp_yes_button = CreateObjectInstance("YesButton");
	mp_no_button = CreateObjectInstance("NoButton");
	mp_confirmation_box->Destroy();
	mp_confirmation_header->Destroy();
	mp_yes_button->Destroy();
	mp_no_button->Destroy();

	////////////// SPAWN OBJECTS AT THE SPECIFIED LOCATIONS ////////////////////

	//////////// PLAYER /////////////////
	SpawnAtPosition("Player", 6, 45); // 180, 25 boss

									  /////////// ENEMIES ////////////////
	SpawnAtPosition("Enemy", 40, 24);
	SpawnAtPosition("Enemy", 42, 24);
	SpawnAtPosition("Enemy", 86, 28);
	SpawnAtPosition("Enemy", 89, 28);
	SpawnAtPosition("Enemy", 91, 28);
	SpawnAtPosition("Enemy", 96, 28);
	SpawnAtPosition("Enemy", 98, 28);
	SpawnAtPosition("Enemy", 110, 32);
	SpawnAtPosition("Enemy", 112, 32);
	SpawnAtPosition("Enemy", 115, 32);
	SpawnAtPosition("Enemy", 117, 32);
	SpawnAtPosition("Enemy", 126, 32);
	SpawnAtPosition("Enemy", 129, 32);
	SpawnAtPosition("Enemy", 136, 22);
	SpawnAtPosition("Enemy", 138, 22);
	SpawnAtPosition("Enemy", 145, 22);
	SpawnAtPosition("Enemy", 148, 22);
	SpawnAtPosition("Enemy", 153, 22);


	/////////// SPECIAL INFECTED //////////
	// Speeders
	SpawnAtPosition("EnemySpeed", 44, 24);
	SpawnAtPosition("EnemySpeed", 94, 28);
	SpawnAtPosition("EnemySpeed", 119, 32);
	SpawnAtPosition("EnemySpeed", 143, 22);

	// Screamers
	SpawnAtPosition("Screamer", 140, 22);
	SpawnAtPosition("Screamer", 123, 32);

	// Bloaters
	SpawnAtPosition("Bloater", 100, 28);
	SpawnAtPosition("Bloater", 150, 22);

	//SpawnAtPosition("ShotGunPickUp", 6, 45);

	// Boss
	p_obj = SpawnAtPosition("Boss", 190, 22);
	p_obj->Set_Active(false);

	/////////// WEAPON PICK UPS //////////
	SpawnAtPosition("PickupParticleSystem", 126.5, 30.5);
	SpawnAtPosition("ShotGunPickUp", 127, 31);
	SpawnAtPosition("PickupParticleSystem", 67, 37.5);
	SpawnAtPosition("MachineGunPickUp", 67.5, 38);

	////////// Checkpoint /////////////////////
	SpawnAtPosition("Checkpoint", 7, 37);
	SpawnAtPosition("Checkpoint", 71, 33);
	SpawnAtPosition("Checkpoint", 165, 19);
	SpawnAtPosition("Checkpoint", 130, 31);
	SpawnAtPosition("TransitionBox", 6, 45);

	//////////////////// CONNECT LEVELSPLASH EVENTS //////////////////////////////////
	events::C_EventDispatcher::Connect("ToBoss", ToBoss, p_player);
	events::C_EventDispatcher::Connect("ShootEvent", Shoot, this);
	events::C_EventDispatcher::Connect("ShootUpEvent", ShootUp, this);
	events::C_EventDispatcher::Connect("ShootDownEvent", ShootDown, this);
	events::C_EventDispatcher::Connect("ScreamerShoot", ScreamerShoot, this);
	events::C_EventDispatcher::Connect("UpdateHP", UpdateHP, this);
	events::C_EventDispatcher::Connect("UpdateLife", UpdateLife, this);
	events::C_EventDispatcher::Connect("MachineGun", SpriteMachineGun, this);
	events::C_EventDispatcher::Connect("Pistol", SpritePistol, this);
	events::C_EventDispatcher::Connect("Shotgun", SpriteShotgun, this);
	events::C_EventDispatcher::Connect("BossThrow", BossShoot, this);
	events::C_EventDispatcher::Connect("BossSummon", BossSummon, this);
	events::C_EventDispatcher::Connect("CameraLock", LockCamera, this);
	events::C_EventDispatcher::Connect("RefreshAmmoInfo", RefreshAmmoInfo, this);
	events::C_EventDispatcher::Connect("DisplayMenu", DisplayMenu, this);
	events::C_EventDispatcher::Connect("CloseMenu", CloseMenu, this);
	events::C_EventDispatcher::Connect("RefreshMenu", RefreshMenu, this);
	events::C_EventDispatcher::Connect("ExecuteMenu", ExecuteMenu, this);
	events::C_EventDispatcher::Connect("DisplayHowToPlay", DisplayHowToPlay, this);
	events::C_EventDispatcher::Connect("CloseHowToPlay", CloseHowToPlay, this);
	events::C_EventDispatcher::Connect("DisplayOptions", DisplayOptions, this);
	events::C_EventDispatcher::Connect("CloseOptions", CloseOptions, this);
	events::C_EventDispatcher::Connect("RefreshOptions", RefreshOptions, this);
	events::C_EventDispatcher::Connect("ExecuteOptions", ExecuteOptions, this);
	events::C_EventDispatcher::Connect("DisplayCredits", DisplayCredits, this);
	events::C_EventDispatcher::Connect("CloseCredits", CloseCredits, this);
	events::C_EventDispatcher::Connect("DisplayConfirmation", DisplayConfirmation, this);
	events::C_EventDispatcher::Connect("CloseConfirmation", CloseConfirmation, this);
	events::C_EventDispatcher::Connect("RefreshConfirmation", RefreshConfirmation, this);
	events::C_EventDispatcher::Connect("ExecuteConfirmation", ExecuteConfirmation, this);
	events::C_EventDispatcher::Connect("DisplayWinMenu", DisplayWinMenu, this);
	events::C_EventDispatcher::Connect("CloseWinMenu", CloseWinMenu, this);
	events::C_EventDispatcher::Connect("DisplayLoseMenu", DisplayLoseMenu, this);
	events::C_EventDispatcher::Connect("CloseLoseMenu", CloseLoseMenu, this);
	events::C_EventDispatcher::Connect("RefreshLoseMenu", RefreshLoseMenu, this);
	events::C_EventDispatcher::Connect("ExecuteLoseMenu", ExecuteLoseMenu, this);
	events::C_EventDispatcher::Connect("Checkpointpos", UpdateCheckpointPos, this);
	events::C_EventDispatcher::Connect("NextLevel", NextLevel, this);
	events::C_EventDispatcher::Connect("BloaterDeath", BloaterDeathSoundEffect, this);
	events::C_EventDispatcher::Connect("AIBossSoundEffect", AIBossSoundEffect, this);
	events::C_EventDispatcher::Connect("StartCameraShake", SetCameraShakeTrue, this);
	events::C_EventDispatcher::Connect("EndCameraShake", SetCameraShakeFalse, this);
	events::C_EventDispatcher::Connect("ToggleHeartWarning", ToggleHeartWarning, this);
	events::C_EventDispatcher::Connect("AIBossBruteLandingSoundEffect", AIBossBruteLandingSoundEffect, this);
	events::C_EventDispatcher::Connect("AIBossBruteDeathSoundEffect", AIBossBruteDeathSoundEffect, this);
	utilities::Connect(); // CONNECT CAMERA EVENTS

						  //////////////////// END CONNECT LEVELSPLASH EVENTS /////////////////////////////

	events::C_EventDispatcher::DispatchEvent("UpdateHP");

	////////////////////// PLAY ANY BACKGROUND SOUND ////////////////////////////////////
	m_sound_system.Play_Sound("Rain", 0.3f, 1, true);
	m_sound_system.Play_Sound("UNTIMELYDEMISE", 0.4f, 0, true);
}
/*****************************************************************************/
/*!
Level one update function
*/
/*****************************************************************************/
void C_LevelOne::Update()
{
	if (AEInputCheckTriggered(AEVK_O))
		events::C_EventDispatcher::DispatchEvent("DisplayWinMenu");
	if (AEInputCheckTriggered(AEVK_I))
		events::C_EventDispatcher::DispatchEvent("DisplayLoseMenu");

	m_sound_system.Update();

	if (!m_win_active && !m_lose_active && !m_menu_active)
	{
		if (AEInputCheckTriggered(AEVK_ESCAPE))
			events::C_EventDispatcher::DispatchEvent("DisplayMenu");
	}

	if (utilities::C_OptionsManager::Get_Pause())
		return;


	// THIS FUNCTION UPDATES THE CAMERA POSITION TO THE POSITION SPECIFIED
	math::Vec2 camerapos = static_cast<object::C_Transform*>(p_player->Find_Component(TRANSFORM))->Get_Position();
	float windowwidth = WINDOW_WIDTH / 2 / TILESCALE;
	float windowheight = WINDOW_WIDTH / 2 / TILESCALE;

	if (m_camerashake)
	{
		utilities::C_Camera::Update(utilities::C_Camera::Get_Position());
	}
	else
	{
		if (cameralock)
		{
			camerapos.x = 181.0f;
			camerapos.y = 25.0f;
		}
		else
		{
			if (camerapos.x - windowwidth < 0)
				camerapos.x = 0 + windowwidth;
			else if (camerapos.x + windowwidth > LevelOneWidth)
				camerapos.x = LevelOneWidth - windowwidth;

			if (camerapos.y - windowheight < 0)
				camerapos.y = 0 + windowheight;
			else if (camerapos.y + windowheight > LevelOneHeight)
				camerapos.y = LevelOneHeight - windowheight;
		}
		utilities::C_Camera::Update(camerapos.x, camerapos.y);
	}

	Update_HUD();

	if (mp_checkpoint)
	{
		math::Vec2 playerpos, checkpointpos;
		playerpos = static_cast<object::C_Transform*>(p_player->Find_Component(TRANSFORM))->Get_Position();
		checkpointpos = static_cast<object::C_Transform*>(mp_checkpoint->Find_Component(TRANSFORM))->Get_Position();
		if (abs(playerpos.x - checkpointpos.x) <= 1)
		{

			checkpointpos.y += 1;
			static_cast<object::C_Player*>(p_player->Find_Component(PLAYER))->Set_CheckpointPos(checkpointpos);
			static_cast<object::C_Checkpoint*>(mp_checkpoint->Find_Component(CUSTOM))->Set_Active(false);
			static_cast<object::C_Sprite*>(mp_checkpoint->Find_Component(SPRITE))->Set_Texture("LanternOn");
			mp_checkpoint = nullptr;
		}
	}
}
/*****************************************************************************/
/*!
Level one draw function
*/
/*****************************************************************************/
void C_LevelOne::Draw()
{
}
/*****************************************************************************/
/*!
Level one free functions
*/
/*****************************************************************************/
void C_LevelOne::Free()
{
	m_obj_mgr.Free_All_Inst();
	m_sound_system.Stop_All_Sounds();
}
/*****************************************************************************/
/*!
Level one unload function
*/
/*****************************************************************************/
void C_LevelOne::Unload()
{
	m_resource_mgr.Unload_All_Texture();
	m_obj_mgr.Unload_All_Object();
	m_sound_system.Release_System();
}


////////////////////////////////////////// PLEASE PUT THESE FUNCTIONS ////////////////////////////////////////////////////////////////////

/*****************************************************************************/
/*!
creates a clone of an object
*/
/*****************************************************************************/
C_LevelOne *C_LevelOne::Clone() const
{
	return new C_LevelOne;
}
/*****************************************************************************/
/*!
Returns a pointer to itself.
*/
/*****************************************************************************/
C_LevelOne *C_LevelOne::Actual() const
{
	return const_cast<C_LevelOne *>(this);
}
/*****************************************************************************/
/*!
Level one unload function
*/
/*****************************************************************************/
void C_LevelOne::Update_HUD()
{
	float camX, camY;
	AEGfxGetCamPosition(&camX, &camY);

	object::C_Transform *p_transform = static_cast<object::C_Transform*>(mp_ammo_max_text->Find_Component(TRANSFORM));

	float ammo_max_text_posX = camX + WINDOW_WIDTH / 2 - p_transform->Get_Size().x * TILESCALE * 1.25f;
	float ammo_max_text_posY = camY - WINDOW_HEIGHT / 2 + p_transform->Get_Size().y * TILESCALE * 1.5f;

	p_transform->Set_Position_Global(ammo_max_text_posX, ammo_max_text_posY);

	p_transform = static_cast<object::C_Transform*>(mp_ammo_min_text->Find_Component(TRANSFORM));
	p_transform->Set_Position_Global(ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 2.0f,
		ammo_max_text_posY + p_transform->Get_Size().y * TILESCALE * 0.1f);

	p_transform = static_cast<object::C_Transform*>(mp_ammo_divider->Find_Component(TRANSFORM));
	p_transform->Set_Position_Global(ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 1.65f,
		ammo_max_text_posY - p_transform->Get_Size().y * TILESCALE * 0.4f);

	p_transform = static_cast<object::C_Transform*>(mp_gun_hud->Find_Component(TRANSFORM));
	object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(mp_gun_hud->Find_Component(SPRITE));
	if (p_sprite->Get_Texture()->m_name == "Shotgun")
	{
		p_transform->Set_Position_Global(ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 1.35f,
			ammo_max_text_posY - p_transform->Get_Size().y * TILESCALE * 0.5f);
	}
	else if (p_sprite->Get_Texture()->m_name == "MachineGun")
	{
		p_transform->Set_Position_Global(ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 1.5f,
			ammo_max_text_posY - p_transform->Get_Size().y * TILESCALE * 0.4f);
	}
	else
	{
		p_transform->Set_Position_Global(ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 3.0f,
			ammo_max_text_posY - p_transform->Get_Size().y * TILESCALE * 0.4f);
	}

	p_transform = static_cast<object::C_Transform*>(mp_health->Find_Component(TRANSFORM));
	p_transform->Set_Position_Global(ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 0.37f,
		ammo_max_text_posY + p_transform->Get_Size().y * TILESCALE * 0.6f);

	p_transform = static_cast<object::C_Transform*>(mp_life_hud[0]->Find_Component(TRANSFORM));

	float life_HUD_posX = ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 4.0f;
	float life_HUD_posY = ammo_max_text_posY + p_transform->Get_Size().y * TILESCALE * 2.0f;

	for (int i = 0; i < m_player_life; ++i)
	{
		p_transform = static_cast<object::C_Transform*>(mp_life_hud[i]->Find_Component(TRANSFORM));
		p_transform->Set_Position_Global(life_HUD_posX, life_HUD_posY);
		life_HUD_posX += p_transform->Get_Size().x * TILESCALE;
	}

	p_transform = static_cast<object::C_Transform*>(mp_health_indicator->Find_Component(TRANSFORM));
	p_transform->Set_Position_Global(ammo_max_text_posX - p_transform->Get_Size().x * TILESCALE * 5.04f,
		ammo_max_text_posY + p_transform->Get_Size().y * TILESCALE * 1.04f);

	p_transform = static_cast<object::C_Transform*>(mp_rain_particlesys->Find_Component(TRANSFORM));
	p_transform->Set_Position_Global(camX - WINDOW_WIDTH / 2, camY + WINDOW_HEIGHT / 2);

}

namespace
{

	/*****************************************************************************/
	/*!
	Function that shoot stright
	*/
	/*****************************************************************************/
	void Shoot(C_LevelOne *level)
	{
		object::C_Transform *p_transform = static_cast<object::C_Transform *>(p_player->Find_Component(TRANSFORM));

		math::Vec2 position = p_transform->Get_Position();
		math::Vec2 size = p_transform->Get_Size();

		object::C_GameObject *p_obj;

		if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::SHOTGUN)
		{
			level->m_sound_system.Play_Sound("Shotgun", 3.0f);
			if (static_cast<object::C_Sprite *>(p_player->Find_Component(SPRITE))->Get_FlipX())
			{
				position.x -= (200.0f / TILESCALE / 2) + 1.0f;
				p_obj = level->SpawnAtPosition("ShotgunBullet", position.x, position.y - size.y / 2.0f + 0.75f);
				static_cast<object::C_Sprite *>(p_obj->Find_Component(SPRITE))->Set_FlipX(true);
			}
			else
			{
				position.x += (200.0f / TILESCALE / 2);
				p_obj = level->SpawnAtPosition("ShotgunBullet", position.x, position.y - size.y / 2.0f + 0.75f);
				static_cast<object::C_Sprite *>(p_obj->Find_Component(SPRITE))->Set_FlipX(false);
			}
		}

		else
		{
			math::Vec2 velocity;
			if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::PISTOL)
				level->m_sound_system.Play_Sound("Pistol");
			else if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::MACHINEGUN)
				level->m_sound_system.Play_Sound("MachineGun");
			if (static_cast<object::C_Sprite*>(p_player->Find_Component(SPRITE))->Get_FlipX())
			{
				position.x += -1.0f;
				velocity.x = -20;
			}
			else
			{
				velocity.x = 20;
			}

			// X and Y offset added
			p_obj = level->SpawnAtPosition("Bullet", position.x, position.y - size.y / 2.0f + 0.75f);
			static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY))->Set_Velocity(velocity);
		}
	}
	/*****************************************************************************/
	/*!
	Function that shoot up
	*/
	/*****************************************************************************/
	void ShootUp(C_LevelOne *level)
	{
		object::C_Transform *p_transform = static_cast<object::C_Transform *>(p_player->Find_Component(TRANSFORM));

		math::Vec2 position = p_transform->Get_Position();
		math::Vec2 size = p_transform->Get_Size();

		object::C_GameObject *p_obj;

		if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::SHOTGUN)
		{
			level->m_sound_system.Play_Sound("Shotgun", 3.0f);
			position.x -= 0.5f;
			position.y += (200.0f / TILESCALE / 2) + 1.0f;
			p_obj = level->SpawnAtPosition("ShotgunBullet", position.x, position.y);
			static_cast<object::C_Transform *>(p_obj->Find_Component(TRANSFORM))->Rotate(90.0f);
		}

		else
		{
			if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::PISTOL)
				level->m_sound_system.Play_Sound("Pistol");
			else if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::MACHINEGUN)
				level->m_sound_system.Play_Sound("MachineGun");
			math::Vec2 velocity;
			velocity.y = 20;
			position.x -= 0.5f;
			position.y += 0.5f;
			// X and Y offset added
			p_obj = level->SpawnAtPosition("Bullet", position.x, position.y);
			static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY))->Set_Velocity(velocity);
			static_cast<object::C_Transform *>(p_obj->Find_Component(TRANSFORM))->Rotate(90.0f);
		}
	}
	/*****************************************************************************/
	/*!
	Function that shoot down
	*/
	/*****************************************************************************/
	void ShootDown(C_LevelOne *level)
	{
		object::C_Transform *p_transform = static_cast<object::C_Transform *>(p_player->Find_Component(TRANSFORM));

		math::Vec2 position = p_transform->Get_Position();
		math::Vec2 size = p_transform->Get_Size();

		object::C_GameObject *p_obj;

		if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::SHOTGUN)
		{
			level->m_sound_system.Play_Sound("Shotgun", 3.0f);
			position.x -= 0.5f;
			position.y -= (200.0f / TILESCALE / 2) + 1.0f;
			p_obj = level->SpawnAtPosition("ShotgunBullet", position.x, position.y);
			static_cast<object::C_Transform *>(p_obj->Find_Component(TRANSFORM))->Rotate(-90.0f);
		}

		else
		{
			if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::PISTOL)
				level->m_sound_system.Play_Sound("Pistol");
			else if (static_cast<object::C_Player *>(p_player->Find_Component(PLAYER))->Get_Weapon() == object::C_Player::MACHINEGUN)
				level->m_sound_system.Play_Sound("MachineGun");
			math::Vec2 velocity;
			velocity.y = -20;
			position.x -= 0.5f;
			position.y -= 0.5f;
			// X and Y offset added
			p_obj = level->SpawnAtPosition("Bullet", position.x, position.y);
			static_cast<object::C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY))->Set_Velocity(velocity);
			static_cast<object::C_Transform *>(p_obj->Find_Component(TRANSFORM))->Rotate(-90.0f);
		}
	}
	/*****************************************************************************/
	/*!
	Update player's HP
	*/
	/*****************************************************************************/
	void UpdateHP(C_LevelOne *level)
	{
		int health = static_cast<object::C_Player*>(p_player->Find_Component(PLAYER))->Get_Health();

		object::C_Sprite *p_sprite = static_cast<object::C_Sprite*>(level->mp_health->Find_Component(SPRITE));

		if (static_cast<object::C_Player*>(p_player->Find_Component(PLAYER))->Get_Health() != 5)
			level->m_sound_system.Play_Sound("PlayerDamge");

		switch (health)
		{
		case 0:
			p_sprite->Set_Texture("HealthBar0");
			break;
		case 1:
			events::C_EventDispatcher::DispatchEvent("ToggleHeartWarning");
			level->m_sound_system.Play_Sound("HeartBeat", 0.4f, 4, true);
			p_sprite->Set_Texture("HealthBar1");
			break;
		case 2:
			p_sprite->Set_Texture("HealthBar2");
			break;
		case 3:
			p_sprite->Set_Texture("HealthBar3");
			break;
		case 4:
			p_sprite->Set_Texture("HealthBar4");
			break;
		case 5:
			p_sprite->Set_Texture("HealthBar5");
			break;
		}
	}
	/*****************************************************************************/
	/*!
	update players life
	*/
	/*****************************************************************************/
	void UpdateLife(C_LevelOne *level)
	{
		level->m_sound_system.Play_Sound("PlayerDamge");

		level->m_player_life = static_cast<object::C_Player*>(p_player->Find_Component(PLAYER))->Get_Life();
		level->m_sound_system.Stop_Channel(4);
		if (level->m_player_life >= 0)
			level->mp_life_hud[level->m_player_life]->Destroy();
		else
			events::C_EventDispatcher::DispatchEvent("DisplayLoseMenu");
	}
	/*****************************************************************************/
	/*!
	change hud sprite to machingun
	*/
	/*****************************************************************************/
	void SpriteMachineGun(C_LevelOne *level)
	{
		level->m_sound_system.Play_Sound("WeaponPickup");
		static_cast<object::C_Sprite*>(level->mp_gun_hud->Find_Component(SPRITE))->Set_Texture("MachineGun");
		static_cast<object::C_Transform*>(level->mp_gun_hud->Find_Component(TRANSFORM))->Scale(425.0f / TILESCALE / 3.5f, 175.0f / TILESCALE / 3.5f);

		char buffer[100];
		sprintf_s(buffer, "%i", MAX_MACHINEGUN_BULLET);

		static_cast<object::C_SpriteText*>(level->mp_ammo_max_text->Find_Component(SPRITETEXT))->Set_Buffer(buffer);
	}
	/*****************************************************************************/
	/*!
	change hud sprite to pistol
	*/
	/*****************************************************************************/
	void SpritePistol(C_LevelOne *level)
	{
		static_cast<object::C_Sprite*>(level->mp_gun_hud->Find_Component(SPRITE))->Set_Texture("Pistol");
		static_cast<object::C_Transform*>(level->mp_gun_hud->Find_Component(TRANSFORM))->Scale(200.0f / TILESCALE / 3.5f, 200.0f / TILESCALE / 3.5f);

		char buffer[100];
		sprintf_s(buffer, "%i", MAX_PISTOL_BULLET);

		static_cast<object::C_SpriteText*>(level->mp_ammo_max_text->Find_Component(SPRITETEXT))->Set_Buffer(buffer);

	}
	/*****************************************************************************/
	/*!
	change hud sprite to shotgun
	*/
	/*****************************************************************************/
	void SpriteShotgun(C_LevelOne *level)
	{
		level->m_sound_system.Play_Sound("WeaponPickup");
		static_cast<object::C_Sprite*>(level->mp_gun_hud->Find_Component(SPRITE))->Set_Texture("Shotgun");
		static_cast<object::C_Transform*>(level->mp_gun_hud->Find_Component(TRANSFORM))->Scale(300.0f / TILESCALE / 2.5f, 100.0f / TILESCALE / 2.5f);

		char buffer[100];
		sprintf_s(buffer, "%i", MAX_SHOTGUN_BULLET);

		static_cast<object::C_SpriteText*>(level->mp_ammo_max_text->Find_Component(SPRITETEXT))->Set_Buffer(buffer);
	}
	/*****************************************************************************/
	/*!
	Lock camera during boss fight
	*/
	/*****************************************************************************/
	void LockCamera(C_LevelOne *level)
	{
		level->cameralock = true;
		level->m_sound_system.Pause_Unpause_Channel(0);
		level->m_sound_system.Play_Sound("FLOORIT", 0.6f, 3, true);
	}
	/*****************************************************************************/
	/*!
	will casue screamer to spit.
	*/
	/*****************************************************************************/
	void ScreamerShoot(C_LevelOne *level)
	{
		static double selapsed = 0;
		static const double sdelay = 2;
		static int scount = 0;
		selapsed += utilities::C_Timer::Get_dt();

		if (selapsed > sdelay)
		{
			selapsed = 0;
			++scount;

			object::C_GameObject *p_obj = level->FindActiveInstByName("Screamer");

			if (!p_obj)
			{
				return;
			}

			object::C_Transform *p_transform = static_cast<object::C_Transform*>(p_obj->Find_Component(TRANSFORM));

			math::Vec2 position = p_transform->Get_Position();
			math::Vec2 playerposition = static_cast<object::C_Transform*>(p_player->Find_Component(TRANSFORM))->Get_Position();

			events::C_EventDispatcher::DispatchEvent("SpawnSpitParticle");

			if (scount >= 5)
			{
				selapsed = 0;
				scount = 0;
				events::C_EventDispatcher::DispatchEvent("ScreamerShootComplete");
			}

		}
	}

	/*****************************************************************************/
	/*!
	will casue screamer to spit.
	*/
	/*****************************************************************************/
	void BossShoot(C_LevelOne *level)
	{
		auto boss_pos = static_cast<object::C_Transform*>(level->FindInstByName("Boss")->Find_Component(TRANSFORM))->Get_Position();

		auto p_bullet = level->SpawnAtPosition("BossBullet", boss_pos.x, boss_pos.y);

		int &count = level->GetBossShootCount();

		switch (count)
		{
		case(0):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-15, 15);
			++count;
			break;
		case(1):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-4, 12);
			++count;
			break;
		case(2):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-10, 17);
			++count;
			break;
		case(3):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-18, 20);
			++count;
			break;
		case(4):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-12, 18);
			++count;
			break;
		case(5):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-20, 8);
			++count;
			break;
		case(6):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-25, 12);
			++count;
			break;
		case(7):
			static_cast<object::C_Rigidbody*>(p_bullet->Find_Component(RIGIDBODY))->Set_Velocity(-35, 14);
			++count;
			break;
		default:
			count = rand() % 8;
			break;
		}
	}

	/*****************************************************************************/
	/*!
	Spawns the boss
	*/
	/*****************************************************************************/
	void BossSummon(C_LevelOne *level)
	{
		int &wave = level->GetBossWaveCount();

		switch (wave)
		{
		case(0):
			level->SpawnAtPosition("Enemy", 180, 35);
			++wave;
			break;
		case(1):
			level->SpawnAtPosition("Enemy", 182, 35);
			++wave;
			break;
		case(2):
			level->SpawnAtPosition("Enemy", 184, 35);
			++wave;
			break;
		case(3):
			level->SpawnAtPosition("Enemy", 175, 35);
			++wave;
			break;
		case(4):
			level->SpawnAtPosition("Enemy", 183, 35);
			++wave;
			break;
		case(5):
			level->SpawnAtPosition("Enemy", 185, 35);
			++wave;
			break;
		case(6):
			wave = 0;
			break;
		}
	}
	/*****************************************************************************/
	/*!
	Refresh ammo
	*/
	/*****************************************************************************/
	void RefreshAmmoInfo(C_LevelOne *level)
	{
		char buffer[100];
		sprintf_s(buffer, "%i", static_cast<object::C_Player*>(p_player->Find_Component(PLAYER))->Get_Ammo());
		static_cast<object::C_SpriteText*>(level->mp_ammo_min_text->Find_Component(SPRITETEXT))->Set_Buffer(buffer);
	}
	/*****************************************************************************/
	/*!
	Display pause menu.
	*/
	/*****************************************************************************/
	void DisplayMenu(C_LevelOne *level)
	{
		level->m_sound_system.Pause_Unpause_Sound(SFX);
		level->m_sound_system.Adjust_Volume(0.25f, false, MAIN);

		float camX, camY;
		AEGfxGetCamPosition(&camX, &camY);

		object::C_Transform *p_menu_transform = static_cast<object::C_Transform*>(level->mp_menu_box->Find_Component(TRANSFORM));
		object::C_Transform *p_menu_header_transform = static_cast<object::C_Transform*>(level->mp_menu_header->Find_Component(TRANSFORM));
		object::C_Transform *p_resume_button_transform = static_cast<object::C_Transform*>(level->mp_resume_button->Find_Component(TRANSFORM));
		object::C_Transform *p_howtoplay_button_transform = static_cast<object::C_Transform*>(level->mp_howtoplay_button->Find_Component(TRANSFORM));
		object::C_Transform *p_options_button_transform = static_cast<object::C_Transform*>(level->mp_options_button->Find_Component(TRANSFORM));
		object::C_Transform *p_restart_button_transform = static_cast<object::C_Transform*>(level->mp_restart_button->Find_Component(TRANSFORM));
		object::C_Transform *p_credits_button_transform = static_cast<object::C_Transform*>(level->mp_credits_button->Find_Component(TRANSFORM));
		object::C_Transform *p_quit_button_transform = static_cast<object::C_Transform*>(level->mp_quit_button->Find_Component(TRANSFORM));

		p_menu_transform->Set_Position_Global(camX, camY);
		level->mp_menu_box->Set_Active(true);

		float posX = p_menu_transform->Get_Position().x * TILESCALE;
		float posY = p_menu_transform->Get_Position().y * TILESCALE + 2.5f * p_menu_header_transform->Get_Size().y * TILESCALE;

		p_menu_header_transform->Set_Position_Global(posX, posY);
		level->mp_menu_header->Set_Active(true);

		posY = p_menu_transform->Get_Position().y * TILESCALE + 2.5f * p_resume_button_transform->Get_Size().y * TILESCALE;

		p_resume_button_transform->Set_Position_Global(posX, posY);
		level->mp_resume_button->Set_Active(true);

		posY = p_menu_transform->Get_Position().y * TILESCALE + 1.0f * p_resume_button_transform->Get_Size().y * TILESCALE;

		p_howtoplay_button_transform->Set_Position_Global(posX, posY);
		level->mp_howtoplay_button->Set_Active(true);

		posY = p_menu_transform->Get_Position().y * TILESCALE - 0.5f * p_resume_button_transform->Get_Size().y * TILESCALE;

		p_options_button_transform->Set_Position_Global(posX, posY);
		level->mp_options_button->Set_Active(true);

		posY = p_menu_transform->Get_Position().y * TILESCALE - 2.0f * p_resume_button_transform->Get_Size().y * TILESCALE;

		p_restart_button_transform->Set_Position_Global(posX, posY);
		level->mp_restart_button->Set_Active(true);

		posY = p_menu_transform->Get_Position().y * TILESCALE - 3.5f * p_resume_button_transform->Get_Size().y * TILESCALE;

		p_credits_button_transform->Set_Position_Global(posX, posY);
		level->mp_credits_button->Set_Active(true);

		posY = p_menu_transform->Get_Position().y * TILESCALE - 5.0f * p_resume_button_transform->Get_Size().y * TILESCALE;

		p_quit_button_transform->Set_Position_Global(posX, posY);
		level->mp_quit_button->Set_Active(true);

		level->m_menu_active = true;

		utilities::C_OptionsManager::Set_Pause(true);
	}
	/*****************************************************************************/
	/*!
	Close the pause menu
	*/
	/*****************************************************************************/
	void CloseMenu(C_LevelOne *level)
	{
		if(level->m_menu_active)
		{
			static_cast<object::C_Sprite*>(level->mp_resume_button->Find_Component(SPRITE))->Set_Texture("ResumeButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_howtoplay_button->Find_Component(SPRITE))->Set_Texture("HowToPlayButton");
			static_cast<object::C_Sprite*>(level->mp_options_button->Find_Component(SPRITE))->Set_Texture("OptionsButton");
			static_cast<object::C_Sprite*>(level->mp_restart_button->Find_Component(SPRITE))->Set_Texture("RestartButton");
			static_cast<object::C_Sprite*>(level->mp_credits_button->Find_Component(SPRITE))->Set_Texture("CreditsButton");
			static_cast<object::C_Sprite*>(level->mp_quit_button->Find_Component(SPRITE))->Set_Texture("QuitButton");


			level->mp_menu_box->Destroy();
			level->mp_menu_header->Destroy();
			level->mp_resume_button->Destroy();
			level->mp_howtoplay_button->Destroy();
			level->mp_options_button->Destroy();
			level->mp_restart_button->Destroy();
			level->mp_credits_button->Destroy();
			level->mp_quit_button->Destroy();

			level->m_menu_active = false;

			level->m_sound_system.Pause_Unpause_Sound(SFX);
			level->m_sound_system.Adjust_Volume(1.0f, false, MAIN);

			utilities::C_OptionsManager::Set_Pause(false);
		}
	}

	/*****************************************************************************/
	/*!
	Refresh the sprites for the pause menu
	*/
	/*****************************************************************************/
	void RefreshMenu(C_LevelOne *level)
	{
		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM));
		switch(p_menu->Get_Selection())
		{
		case 0:
			static_cast<object::C_Sprite*>(level->mp_resume_button->Find_Component(SPRITE))->Set_Texture("ResumeButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_howtoplay_button->Find_Component(SPRITE))->Set_Texture("HowToPlayButton");
			static_cast<object::C_Sprite*>(level->mp_options_button->Find_Component(SPRITE))->Set_Texture("OptionsButton");
			static_cast<object::C_Sprite*>(level->mp_restart_button->Find_Component(SPRITE))->Set_Texture("RestartButton");
			static_cast<object::C_Sprite*>(level->mp_credits_button->Find_Component(SPRITE))->Set_Texture("CreditsButton");
			static_cast<object::C_Sprite*>(level->mp_quit_button->Find_Component(SPRITE))->Set_Texture("QuitButton");
			break;
		case 1:
			static_cast<object::C_Sprite*>(level->mp_resume_button->Find_Component(SPRITE))->Set_Texture("ResumeButton");
			static_cast<object::C_Sprite*>(level->mp_howtoplay_button->Find_Component(SPRITE))->Set_Texture("HowToPlayButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_options_button->Find_Component(SPRITE))->Set_Texture("OptionsButton");
			static_cast<object::C_Sprite*>(level->mp_restart_button->Find_Component(SPRITE))->Set_Texture("RestartButton");
			static_cast<object::C_Sprite*>(level->mp_credits_button->Find_Component(SPRITE))->Set_Texture("CreditsButton");
			static_cast<object::C_Sprite*>(level->mp_quit_button->Find_Component(SPRITE))->Set_Texture("QuitButton");
			break;
		case 2:
			static_cast<object::C_Sprite*>(level->mp_resume_button->Find_Component(SPRITE))->Set_Texture("ResumeButton");
			static_cast<object::C_Sprite*>(level->mp_howtoplay_button->Find_Component(SPRITE))->Set_Texture("HowToPlayButton");
			static_cast<object::C_Sprite*>(level->mp_options_button->Find_Component(SPRITE))->Set_Texture("OptionsButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_restart_button->Find_Component(SPRITE))->Set_Texture("RestartButton");
			static_cast<object::C_Sprite*>(level->mp_credits_button->Find_Component(SPRITE))->Set_Texture("CreditsButton");
			static_cast<object::C_Sprite*>(level->mp_quit_button->Find_Component(SPRITE))->Set_Texture("QuitButton");
			break;
		case 3:
			static_cast<object::C_Sprite*>(level->mp_resume_button->Find_Component(SPRITE))->Set_Texture("ResumeButton");
			static_cast<object::C_Sprite*>(level->mp_howtoplay_button->Find_Component(SPRITE))->Set_Texture("HowToPlayButton");
			static_cast<object::C_Sprite*>(level->mp_options_button->Find_Component(SPRITE))->Set_Texture("OptionsButton");
			static_cast<object::C_Sprite*>(level->mp_restart_button->Find_Component(SPRITE))->Set_Texture("RestartButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_credits_button->Find_Component(SPRITE))->Set_Texture("CreditsButton");
			static_cast<object::C_Sprite*>(level->mp_quit_button->Find_Component(SPRITE))->Set_Texture("QuitButton");
			break;
		case 4:
			static_cast<object::C_Sprite*>(level->mp_resume_button->Find_Component(SPRITE))->Set_Texture("ResumeButton");
			static_cast<object::C_Sprite*>(level->mp_howtoplay_button->Find_Component(SPRITE))->Set_Texture("HowToPlayButton");
			static_cast<object::C_Sprite*>(level->mp_options_button->Find_Component(SPRITE))->Set_Texture("OptionsButton");
			static_cast<object::C_Sprite*>(level->mp_restart_button->Find_Component(SPRITE))->Set_Texture("RestartButton");
			static_cast<object::C_Sprite*>(level->mp_credits_button->Find_Component(SPRITE))->Set_Texture("CreditsButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_quit_button->Find_Component(SPRITE))->Set_Texture("QuitButton");
			break;
		case 5:
			static_cast<object::C_Sprite*>(level->mp_resume_button->Find_Component(SPRITE))->Set_Texture("ResumeButton");
			static_cast<object::C_Sprite*>(level->mp_howtoplay_button->Find_Component(SPRITE))->Set_Texture("HowToPlayButton");
			static_cast<object::C_Sprite*>(level->mp_options_button->Find_Component(SPRITE))->Set_Texture("OptionsButton");
			static_cast<object::C_Sprite*>(level->mp_restart_button->Find_Component(SPRITE))->Set_Texture("RestartButton");
			static_cast<object::C_Sprite*>(level->mp_credits_button->Find_Component(SPRITE))->Set_Texture("CreditsButton");
			static_cast<object::C_Sprite*>(level->mp_quit_button->Find_Component(SPRITE))->Set_Texture("QuitButtonGlow");
			break;
		}
	}

	/*****************************************************************************/
	/*!
	Carry out the actions
	*/
	/*****************************************************************************/
	void ExecuteMenu(C_LevelOne *level)
	{
		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM));
		switch(p_menu->Get_Selection())
		{
		case 0:
			events::C_EventDispatcher::DispatchEvent("CloseMenu");
			break;
		case 1:
			events::C_EventDispatcher::DispatchEvent("DisplayHowToPlay");
			break;
		case 2:
			events::C_EventDispatcher::DispatchEvent("DisplayOptions");
			break;
		case 3:
			events::C_EventDispatcher::DispatchEvent("CloseMenu");
			events::C_EventDispatcher::DispatchEvent("RestartGame");
			break;
		case 4:
			events::C_EventDispatcher::DispatchEvent("DisplayCredits");
			break;
		case 5:
			events::C_EventDispatcher::DispatchEvent("DisplayConfirmation");
			break;
		}
	}

	/*****************************************************************************/
	/*!
	Display how to play menu
	*/
	/*****************************************************************************/
	void DisplayHowToPlay(C_LevelOne *level)
	{
		float camX, camY;
		AEGfxGetCamPosition(&camX, &camY);

		object::C_Transform *p_howtoplay_transform = static_cast<object::C_Transform*>(level->mp_howtoplay_box->Find_Component(TRANSFORM));
		object::C_Transform *p_howtoplay_header_transform = static_cast<object::C_Transform*>(level->mp_howtoplay_header->Find_Component(TRANSFORM));
		object::C_Transform *p_shoot_key_transform = static_cast<object::C_Transform*>(level->mp_shoot_key->Find_Component(TRANSFORM));
		object::C_Transform *p_move_key_transform = static_cast<object::C_Transform*>(level->mp_move_key->Find_Component(TRANSFORM));
		object::C_Transform *p_jump_key_transform = static_cast<object::C_Transform*>(level->mp_jump_key->Find_Component(TRANSFORM));
		object::C_Transform *p_howtoplay_esc_transform = static_cast<object::C_Transform*>(level->mp_howtoplay_esc->Find_Component(TRANSFORM));

		p_howtoplay_transform->Set_Position_Global(camX, camY);
		level->mp_howtoplay_box->Set_Active(true);

		float posX = p_howtoplay_transform->Get_Position().x * TILESCALE;
		float posY = p_howtoplay_transform->Get_Position().y * TILESCALE + 3.0f * p_howtoplay_header_transform->Get_Size().y * TILESCALE;

		p_howtoplay_header_transform->Set_Position_Global(posX, posY);
		level->mp_howtoplay_header->Set_Active(true);

		posX = p_howtoplay_transform->Get_Position().x * TILESCALE - 1.5f * p_shoot_key_transform->Get_Size().x * TILESCALE;
		posY = p_howtoplay_transform->Get_Position().y * TILESCALE - 0.55f * p_shoot_key_transform->Get_Size().y * TILESCALE;

		p_shoot_key_transform->Set_Position_Global(posX, posY);
		level->mp_shoot_key->Set_Active(true);

		posX = p_howtoplay_transform->Get_Position().x * TILESCALE;
		posY = p_howtoplay_transform->Get_Position().y * TILESCALE - 0.2f * p_move_key_transform->Get_Size().y * TILESCALE;

		p_move_key_transform->Set_Position_Global(posX, posY);
		level->mp_move_key->Set_Active(true);

		posX = p_howtoplay_transform->Get_Position().x * TILESCALE + 1.35f * p_jump_key_transform->Get_Size().x * TILESCALE;
		posY = p_howtoplay_transform->Get_Position().y * TILESCALE - 0.55f * p_jump_key_transform->Get_Size().y * TILESCALE;

		p_jump_key_transform->Set_Position_Global(posX, posY);
		level->mp_jump_key->Set_Active(true);

		posX = p_howtoplay_transform->Get_Position().x * TILESCALE;
		posY = p_howtoplay_transform->Get_Position().y * TILESCALE - 4.25f * p_howtoplay_esc_transform->Get_Size().y * TILESCALE;

		p_howtoplay_esc_transform->Set_Position_Global(posX, posY);
		level->mp_howtoplay_esc->Set_Active(true);

		level->m_howtoplay_active = true;

		if(level->m_menu_active)
			static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_win_active)
			static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_lose_active)
			static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(true);
	}
	/*****************************************************************************/
	/*!
	close the how to play menu
	*/
	/*****************************************************************************/
	void CloseHowToPlay(C_LevelOne *level)
	{
		if(level->m_howtoplay_active)
		{
			level->mp_howtoplay_box->Destroy();
			level->mp_howtoplay_header->Destroy();
			level->mp_move_key->Destroy();
			level->mp_shoot_key->Destroy();
			level->mp_jump_key->Destroy();
			level->mp_howtoplay_esc->Destroy();
			level->m_howtoplay_active = false;

			if(level->m_menu_active)
				static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if(level->m_win_active)
				static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if(level->m_lose_active)
				static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(false);
		}
	}
	/*****************************************************************************/
	/*!
	Display options menu
	*/
	/*****************************************************************************/
	void DisplayOptions(C_LevelOne *level)
	{
		float camX, camY;
		AEGfxGetCamPosition(&camX, &camY);

		object::C_Transform *p_options_transform = static_cast<object::C_Transform*>(level->mp_options_box->Find_Component(TRANSFORM));
		object::C_Transform *p_options_header_transform = static_cast<object::C_Transform*>(level->mp_options_header->Find_Component(TRANSFORM));
		object::C_Transform *p_fullscreen_button_transform = static_cast<object::C_Transform*>(level->mp_fullscreen_button->Find_Component(TRANSFORM));
		object::C_Transform *p_fullscreen_selector_transform = static_cast<object::C_Transform*>(level->mp_fullscreen_selector->Find_Component(TRANSFORM));
		object::C_Transform *p_soundfx_button_transform = static_cast<object::C_Transform*>(level->mp_soundfx_button->Find_Component(TRANSFORM));
		object::C_Transform *p_soundfx_selector_transform = static_cast<object::C_Transform*>(level->mp_soundfx_selector->Find_Component(TRANSFORM));
		object::C_Transform *p_back_button_transform = static_cast<object::C_Transform*>(level->mp_options_back->Find_Component(TRANSFORM));

		p_options_transform->Set_Position_Global(camX, camY);
		level->mp_options_box->Set_Active(true);

		float posX = p_options_transform->Get_Position().x * TILESCALE;
		float posY = p_options_transform->Get_Position().y * TILESCALE + 2.5f * p_options_header_transform->Get_Size().y * TILESCALE;

		p_options_header_transform->Set_Position_Global(posX, posY);
		level->mp_options_header->Set_Active(true);

		posX = p_options_transform->Get_Position().x * TILESCALE - 0.5f * p_fullscreen_button_transform->Get_Size().x * TILESCALE;
		posY = p_options_transform->Get_Position().y * TILESCALE + 2.0f * p_fullscreen_button_transform->Get_Size().y * TILESCALE;

		p_fullscreen_button_transform->Set_Position_Global(posX, posY);
		level->mp_fullscreen_button->Set_Active(true);

		posX = p_options_transform->Get_Position().x * TILESCALE + 0.6f * p_fullscreen_selector_transform->Get_Size().x * TILESCALE;

		p_fullscreen_selector_transform->Set_Position_Global(posX, posY);
		level->mp_fullscreen_selector->Set_Active(true);

		posX = p_options_transform->Get_Position().x * TILESCALE - 0.57f * p_soundfx_button_transform->Get_Size().x * TILESCALE;
		posY = p_options_transform->Get_Position().y * TILESCALE;

		p_soundfx_button_transform->Set_Position_Global(posX, posY);
		level->mp_soundfx_button->Set_Active(true);

		posX = p_options_transform->Get_Position().x * TILESCALE + 0.6f * p_soundfx_selector_transform->Get_Size().x * TILESCALE;

		p_soundfx_selector_transform->Set_Position_Global(posX, posY);
		level->mp_soundfx_selector->Set_Active(true);

		posX = p_options_transform->Get_Position().x * TILESCALE;
		posY = p_options_transform->Get_Position().y * TILESCALE - 5.0f * p_back_button_transform->Get_Size().y * TILESCALE;

		p_back_button_transform->Set_Position_Global(posX, posY);
		level->mp_options_back->Set_Active(true);

		level->m_options_active = true;

		if(level->m_menu_active)
			static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_win_active)
			static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_lose_active)
			static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(true);
	}

	/*****************************************************************************/
	/*!
	Close option menu.
	*/
	/*****************************************************************************/
	void CloseOptions(C_LevelOne *level)
	{
		if(level->m_options_active)
		{
			static_cast<object::C_Sprite*>(level->mp_fullscreen_button->Find_Component(SPRITE))->Set_Texture("FullScreenHighlighted");
			static_cast<object::C_Sprite*>(level->mp_soundfx_button->Find_Component(SPRITE))->Set_Texture("SoundFX");
			static_cast<object::C_Sprite*>(level->mp_options_back->Find_Component(SPRITE))->Set_Texture("Back");

			static_cast<object::C_MenuController*>(level->mp_options_box->Find_Component(CUSTOM))->Set_Selection(0);

			level->mp_options_box->Destroy();
			level->mp_options_header->Destroy();
			level->mp_fullscreen_button->Destroy();
			level->mp_fullscreen_selector->Destroy();
			level->mp_soundfx_button->Destroy();
			level->mp_soundfx_selector->Destroy();
			level->mp_options_back->Destroy();
			level->m_options_active = false;

			if(level->m_menu_active)
				static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if(level->m_win_active)
				static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if(level->m_lose_active)
				static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(false);
		}
	}

	/*****************************************************************************/
	/*!
	Refresh the options menu.
	*/
	/*****************************************************************************/
	void RefreshOptions(C_LevelOne *level)
	{
		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_options_box->Find_Component(CUSTOM));
		switch(p_menu->Get_Selection())
		{
		case 0:
			static_cast<object::C_Sprite*>(level->mp_fullscreen_button->Find_Component(SPRITE))->Set_Texture("FullScreenHighlighted");
			static_cast<object::C_Sprite*>(level->mp_soundfx_button->Find_Component(SPRITE))->Set_Texture("SoundFX");
			static_cast<object::C_Sprite*>(level->mp_options_back->Find_Component(SPRITE))->Set_Texture("Back");
			break;
		case 1:
			static_cast<object::C_Sprite*>(level->mp_fullscreen_button->Find_Component(SPRITE))->Set_Texture("FullScreen");
			static_cast<object::C_Sprite*>(level->mp_soundfx_button->Find_Component(SPRITE))->Set_Texture("SoundFXHighlighted");
			static_cast<object::C_Sprite*>(level->mp_options_back->Find_Component(SPRITE))->Set_Texture("Back");
			break;
		case 2:
			static_cast<object::C_Sprite*>(level->mp_fullscreen_button->Find_Component(SPRITE))->Set_Texture("FullScreen");
			static_cast<object::C_Sprite*>(level->mp_soundfx_button->Find_Component(SPRITE))->Set_Texture("SoundFX");
			static_cast<object::C_Sprite*>(level->mp_options_back->Find_Component(SPRITE))->Set_Texture("BackHighlighted");
			break;
		}
	}
	/*****************************************************************************/
	/*!
	Carry out the actions in options menu.
	*/
	/*****************************************************************************/
	void ExecuteOptions(C_LevelOne *level)
	{

		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_options_box->Find_Component(CUSTOM));
		switch(p_menu->Get_Selection())
		{
		case 0:
			events::C_EventDispatcher::DispatchEvent("ToggleFullScreen");
			utilities::C_OptionsManager::Get_FullScreen() ? static_cast<object::C_Sprite*>(level->mp_fullscreen_selector->Find_Component(SPRITE))->Set_Texture("NoHighlight")
				: static_cast<object::C_Sprite*>(level->mp_fullscreen_selector->Find_Component(SPRITE))->Set_Texture("YesHighlight");
			break;
		case 1:
			events::C_EventDispatcher::DispatchEvent("ToggleSoundFX");
			utilities::C_OptionsManager::Get_SoundFX() ? (static_cast<object::C_Sprite*>(level->mp_soundfx_selector->Find_Component(SPRITE))->Set_Texture("NoHighlight"),
				level->m_sound_system.MuteAllChannel())
				: (static_cast<object::C_Sprite*>(level->mp_soundfx_selector->Find_Component(SPRITE))->Set_Texture("YesHighlight"),
					level->m_sound_system.UnmuteAllChannel());
			break;
		case 2:
			events::C_EventDispatcher::DispatchEvent("CloseOptions");
			break;
		}
	}

	/*****************************************************************************/
	/*!
		Display credits menu.
	*/
	/*****************************************************************************/
	void DisplayCredits(C_LevelOne *level)
	{
		float camX, camY;
		AEGfxGetCamPosition(&camX, &camY);

		object::C_Transform *p_credits_transform = static_cast<object::C_Transform*>(level->mp_credits_box->Find_Component(TRANSFORM));
		object::C_Transform *p_credits_esc_transform = static_cast<object::C_Transform*>(level->mp_credits_esc->Find_Component(TRANSFORM));

		p_credits_transform->Set_Position_Global(camX, camY);
		level->mp_credits_box->Set_Active(true);

		float posX = p_credits_transform->Get_Position().x * TILESCALE;
		float posY = p_credits_transform->Get_Position().y * TILESCALE - 5.0f * p_credits_esc_transform->Get_Size().y * TILESCALE;

		p_credits_esc_transform->Set_Position_Global(posX, posY);
		level->mp_credits_esc->Set_Active(true);

		level->m_credits_active = true;

		if(level->m_menu_active)
			static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_win_active)
			static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_lose_active)
			static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(true);
	}

	/*****************************************************************************/
	/*!
		Close credits menu.
	*/
	/*****************************************************************************/
	void CloseCredits(C_LevelOne *level)
	{
		if(level->m_credits_active)
		{
			level->mp_credits_box->Destroy();
			level->mp_credits_esc->Destroy();
			level->m_credits_active = false;

			if(level->m_menu_active)
				static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if(level->m_win_active)
				static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if(level->m_lose_active)
				static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(false);
		}
	}

	/*****************************************************************************/
	/*!
	Display confirmation screen.
	*/
	/*****************************************************************************/
	void DisplayConfirmation(C_LevelOne *level)
	{
		float camX, camY;
		AEGfxGetCamPosition(&camX, &camY);

		object::C_Transform *p_confirmation_transform = static_cast<object::C_Transform*>(level->mp_confirmation_box->Find_Component(TRANSFORM));
		object::C_Transform *p_cfm_header_transform = static_cast<object::C_Transform*>(level->mp_confirmation_header->Find_Component(TRANSFORM));
		object::C_Transform *p_no_button_transform = static_cast<object::C_Transform*>(level->mp_no_button->Find_Component(TRANSFORM));
		object::C_Transform *p_yes_button_transform = static_cast<object::C_Transform*>(level->mp_yes_button->Find_Component(TRANSFORM));

		p_confirmation_transform->Set_Position_Global(camX, camY);
		level->mp_confirmation_box->Set_Active(true);

		float posX = p_confirmation_transform->Get_Position().x * TILESCALE;
		float posY = p_confirmation_transform->Get_Position().y * TILESCALE + 0.75f * p_cfm_header_transform->Get_Size().y * TILESCALE;

		p_cfm_header_transform->Set_Position_Global(posX, posY);
		level->mp_confirmation_header->Set_Active(true);

		posY = p_confirmation_transform->Get_Position().y * TILESCALE - 0.5f * p_no_button_transform->Get_Size().y * TILESCALE;

		p_no_button_transform->Set_Position_Global(posX, posY);
		level->mp_no_button->Set_Active(true);

		posY = p_confirmation_transform->Get_Position().y * TILESCALE - 2.0f * p_yes_button_transform->Get_Size().y * TILESCALE;

		p_yes_button_transform->Set_Position_Global(posX, posY);
		level->mp_yes_button->Set_Active(true);

		level->m_confirmation_active = true;

		if(level->m_menu_active)
			static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_win_active)
			static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(true);
		else if(level->m_lose_active)
			static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(true);
	}

	/*****************************************************************************/
	/*!
	Close confirmation Screen.
	*/
	/*****************************************************************************/
	void CloseConfirmation(C_LevelOne *level)
	{
		if (level->m_confirmation_active)
		{
			static_cast<object::C_Sprite*>(level->mp_no_button->Find_Component(SPRITE))->Set_Texture("NoButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_yes_button->Find_Component(SPRITE))->Set_Texture("YesButton");

			level->mp_confirmation_box->Destroy();
			level->mp_confirmation_header->Destroy();
			level->mp_no_button->Destroy();
			level->mp_yes_button->Destroy();

			level->m_confirmation_active = false;

			if (level->m_menu_active)
				static_cast<object::C_MenuController*>(level->mp_menu_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if (level->m_win_active)
				static_cast<object::C_MenuController*>(level->mp_win_box->Find_Component(CUSTOM))->Set_Pause(false);
			else if (level->m_lose_active)
				static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM))->Set_Pause(false);
		}
	}

	/*****************************************************************************/
	/*!
	Refreash the sprites in the confirmation screen.
	*/
	/*****************************************************************************/
	void RefreshConfirmation(C_LevelOne *level)
	{
		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_confirmation_box->Find_Component(CUSTOM));
		switch (p_menu->Get_Selection())
		{
		case 0:
			static_cast<object::C_Sprite*>(level->mp_no_button->Find_Component(SPRITE))->Set_Texture("NoButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_yes_button->Find_Component(SPRITE))->Set_Texture("YesButton");
			break;
		case 1:
			static_cast<object::C_Sprite*>(level->mp_no_button->Find_Component(SPRITE))->Set_Texture("NoButton");
			static_cast<object::C_Sprite*>(level->mp_yes_button->Find_Component(SPRITE))->Set_Texture("YesButtonGlow");
			break;
		}
	}

	/*****************************************************************************/
	/*!
	Execute conformation action.
	*/
	/*****************************************************************************/
	void ExecuteConfirmation(C_LevelOne *level)
	{
		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_confirmation_box->Find_Component(CUSTOM));
		switch (p_menu->Get_Selection())
		{
		case 0:
			events::C_EventDispatcher::DispatchEvent("CloseConfirmation");
			break;
		case 1:
			utilities::C_OptionsManager::Set_Pause(false);
			events::C_EventDispatcher::DispatchEvent("CloseConfirmation");
			events::C_EventDispatcher::DispatchEvent("LevelMenu");
			break;
		}
	}

	/*****************************************************************************/
	/*!
	Display win screen.
	*/
	/*****************************************************************************/
	void DisplayWinMenu(C_LevelOne *level)
	{
		float camX, camY;
		AEGfxGetCamPosition(&camX, &camY);

		object::C_Transform *p_win_box_transform = static_cast<object::C_Transform*>(level->mp_win_box->Find_Component(TRANSFORM));
		object::C_Transform *p_win_header_transform = static_cast<object::C_Transform*>(level->mp_win_header->Find_Component(TRANSFORM));
		object::C_Transform *p_continue_transform = static_cast<object::C_Transform*>(level->mp_continue->Find_Component(TRANSFORM));

		p_win_box_transform->Set_Position_Global(camX, camY);
		level->mp_win_box->Set_Active(true);

		float posX = p_win_box_transform->Get_Position().x * TILESCALE;
		float posY = p_win_box_transform->Get_Position().y * TILESCALE + 1.25f * p_win_header_transform->Get_Size().y * TILESCALE;

		p_win_header_transform->Set_Position_Global(posX, posY);
		level->mp_win_header->Set_Active(true);

		posY = p_win_box_transform->Get_Position().y * TILESCALE - 0.5f * p_continue_transform->Get_Size().y * TILESCALE;

		p_continue_transform->Set_Position_Global(posX, posY);
		level->mp_continue->Set_Active(true);

		level->m_win_active = true;

		utilities::C_OptionsManager::Set_Pause(true);
	}
	/*****************************************************************************/
	/*!
	Close win screen.
	*/
	/*****************************************************************************/
	void CloseWinMenu(C_LevelOne *level)
	{
		if (level->m_win_active)
		{
			level->mp_win_box->Destroy();
			level->mp_win_header->Destroy();
			level->mp_continue->Destroy();

			level->m_win_active = false;

			utilities::C_OptionsManager::Set_Pause(false);
			events::C_EventDispatcher::DispatchEvent("LevelTwo");
		}
	}

	/*****************************************************************************/
	/*!
	Display lose menu screen
	*/
	/*****************************************************************************/
	void DisplayLoseMenu(C_LevelOne *level)
	{
		float camX, camY;
		AEGfxGetCamPosition(&camX, &camY);

		object::C_Transform *p_box_transform = static_cast<object::C_Transform*>(level->mp_lose_box->Find_Component(TRANSFORM));
		object::C_Transform *p_header_transform = static_cast<object::C_Transform*>(level->mp_lose_header->Find_Component(TRANSFORM));
		object::C_Transform *p_yes_button_transform = static_cast<object::C_Transform*>(level->mp_lose_yes_button->Find_Component(TRANSFORM));
		object::C_Transform *p_no_button_transform = static_cast<object::C_Transform*>(level->mp_lose_no_button->Find_Component(TRANSFORM));

		p_box_transform->Set_Position_Global(camX, camY);
		level->mp_lose_box->Set_Active(true);

		float posX = p_box_transform->Get_Position().x * TILESCALE;
		float posY = p_box_transform->Get_Position().y * TILESCALE + 0.8f * p_header_transform->Get_Size().y * TILESCALE;

		p_header_transform->Set_Position_Global(posX, posY);
		level->mp_lose_header->Set_Active(true);

		posY = p_box_transform->Get_Position().y * TILESCALE - 0.5f * p_yes_button_transform->Get_Size().y * TILESCALE;

		p_yes_button_transform->Set_Position_Global(posX, posY);
		level->mp_lose_yes_button->Set_Active(true);

		posY = p_box_transform->Get_Position().y * TILESCALE - 2.0f * p_no_button_transform->Get_Size().y * TILESCALE;

		p_no_button_transform->Set_Position_Global(posX, posY);
		level->mp_lose_no_button->Set_Active(true);

		level->m_lose_active = true;

		utilities::C_OptionsManager::Set_Pause(true);
	}
	/*****************************************************************************/
	/*!
	Closes the lose menu screen.
	*/
	/*****************************************************************************/
	void CloseLoseMenu(C_LevelOne *level)
	{
		if (level->m_lose_active)
		{
			static_cast<object::C_Sprite*>(level->mp_lose_no_button->Find_Component(SPRITE))->Set_Texture("NoButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_lose_yes_button->Find_Component(SPRITE))->Set_Texture("YesButton");

			level->mp_lose_box->Destroy();
			level->mp_lose_header->Destroy();
			level->mp_lose_no_button->Destroy();
			level->mp_lose_yes_button->Destroy();

			level->m_lose_active = false;

			utilities::C_OptionsManager::Set_Pause(false);
		}
	}

	/*****************************************************************************/
	/*!
	Refresh the Lose menu screen's sprites.
	*/
	/*****************************************************************************/
	void RefreshLoseMenu(C_LevelOne *level)
	{
		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM));
		switch (p_menu->Get_Selection())
		{
		case 0:
			static_cast<object::C_Sprite*>(level->mp_lose_yes_button->Find_Component(SPRITE))->Set_Texture("YesButtonGlow");
			static_cast<object::C_Sprite*>(level->mp_lose_no_button->Find_Component(SPRITE))->Set_Texture("NoButton");
			break;
		case 1:
			static_cast<object::C_Sprite*>(level->mp_lose_yes_button->Find_Component(SPRITE))->Set_Texture("YesButton");
			static_cast<object::C_Sprite*>(level->mp_lose_no_button->Find_Component(SPRITE))->Set_Texture("NoButtonGlow");
			break;
		}
	}

	/*****************************************************************************/
	/*!
	Carry out the action selected by the player in the lose screen.
	*/
	/*****************************************************************************/
	void ExecuteLoseMenu(C_LevelOne *level)
	{
		object::C_MenuController *p_menu = static_cast<object::C_MenuController*>(level->mp_lose_box->Find_Component(CUSTOM));
		switch (p_menu->Get_Selection())
		{
		case 0:
			events::C_EventDispatcher::DispatchEvent("CloseLoseMenu");
			events::C_EventDispatcher::DispatchEvent("RestartGame");
			break;
		case 1:
			events::C_EventDispatcher::DispatchEvent("DisplayConfirmation");
			break;
		}
	}
	/*****************************************************************************/
	/*!
	Update current checkpoint pos.
	*/
	/*****************************************************************************/
	void UpdateCheckpointPos(C_LevelOne *level)
	{
		level->mp_checkpoint = level->FindActiveInstByName("Checkpoint");
	}
	/*****************************************************************************/
	/*!
	Go to the next level
	*/
	/*****************************************************************************/
	void NextLevel(C_LevelOne *level)
	{
		UNREFERENCED_PARAMETER(level);
		events::C_EventDispatcher::DispatchEvent("LevelTwo");
	}
	/*****************************************************************************/
	/*!
	PLay bloated death sound effect.
	*/
	/*****************************************************************************/
	void BloaterDeathSoundEffect(C_LevelOne *level)
	{
		level->m_sound_system.Play_Sound("BloaterDeath", 1.0f);
	}
	/*****************************************************************************/
	/*!
	PLay boss sound FX
	*/
	/*****************************************************************************/
	void AIBossSoundEffect(C_LevelOne *level)
	{
		level->m_sound_system.Play_Sound("ZombieGrowl");
	}
	/*****************************************************************************/
	/*!
	Set shake camera boolean to true.
	*/
	/*****************************************************************************/
	void SetCameraShakeTrue(C_LevelOne * level)
	{
		level->SetCameraShake(true);
	}
	/*****************************************************************************/
	/*!
	Set shake camera boolean to false.
	*/
	/*****************************************************************************/
	void SetCameraShakeFalse(C_LevelOne * level)
	{
		level->SetCameraShake(false);
	}
	/*****************************************************************************/
	/*!
	Set hart in hud to animate.
	*/
	/*****************************************************************************/
	void ToggleHeartWarning(C_LevelOne *level)
	{
		object::C_Sprite* p_sprite = static_cast<object::C_Sprite*>(level->mp_health_indicator->Find_Component(SPRITE));

		p_sprite->Get_Animate() ? p_sprite->Set_Animate(false) : p_sprite->Set_Animate(true);
	}
	/*****************************************************************************/
	/*!
	Play boss landing sound effect.
	*/
	/*****************************************************************************/
	void AIBossBruteLandingSoundEffect(C_LevelOne *level)
	{
		level->m_sound_system.Play_Sound("BruteLand", 1.5f);
	}
	/*****************************************************************************/
	/*!
	Play boss death sound
	*/
	/*****************************************************************************/
	void AIBossBruteDeathSoundEffect(C_LevelOne *level)
	{
		level->m_sound_system.Play_Sound("BossDeath");
	}
}
