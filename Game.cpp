#include "Game.h"
#include "Calc.h"
#include "Random.h"
#include "Def.h"
#include "Ease.h"

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Object;

Game::Game() {}

Game::~Game() {}

void Game::Initialize()
{
	// ----- Input ----- //
	keys = Keys::GetInstance();
	mouse = Mouse::GetInstance();
	pad = Pad::GetInstance();
	// ----------------- //

	// ----- Pipeline ----- //
	texM.Initialize();
	texM.SetRootParameterIndex(rpM.PushBackTR());
	cbM.SetRootParameterIndexMaterial(rpM.PushBackCBV());
	cbM.SetRootParameterIndexTransform(rpM.PushBackCBV());

	Transform::StaticInitialize(&cbM);
	Sprite::StaticInitialize(&texM);
	Model::StaticInitialize(&texM);

	pplnSet2D.Initialize(PipelineSet::Type::SpriteT, rpM.Get());
	pplnSet3D.Initialize(PipelineSet::Type::ModelT, rpM.Get());
	// -------------------- //

	Srand();

	plainTex = texM.Load(L"Resources/white.png", false);
	playerTex = texM.Load(L"Resources/player.png", false);
	enemyTex = texM.Load(L"Resources/enemy.png", false);

	m1.reset(new Model());
	s1.reset(new Sprite({ 64,64 }));

	player.Initialize({});
	player.scale_ = { 5,5,5 };
	player.pos_ = { 0,player.scale_.y,0 };

	enemy.Initialize({});
	enemy.scale_ = { 10,10,10 };
	enemy.pos_ = { 0,enemy.scale_.y,60 };

	heightE.Initialize(enemy.scale_.y + 200, enemy.scale_.y, 3.0f);
	heightT.Initialize(100);
	heightT.SetActive(true);

	const size_t s = 8;
	for (size_t i = 0; i < s; i++)
	{
		std::vector<Transform> fs;
		for (size_t j = 0; j < s; j++)
		{
			Transform f;
			f.Initialize({});
			f.scale_ = { 20,1,20 };
			f.pos_ = 
			{ 
				((f.scale_.x * 2.0f) * j) - ((s - 1) * (f.scale_.x)),
				-f.scale_.y,
				((f.scale_.z * 2.0f) * i) - ((s - 1) * (f.scale_.z))
			};
			float c = 1.0f - (((i + j) % 2 == 0) * 0.5f);
			f.SetColor({ c,c,c,1.0f });
			fs.push_back(f);
		}
		floor.push_back(fs);
	}

	CameraManager::StaticInitialize(&player, &enemy);
	cameraM.Initialize();
	cameraM.ActStartAnimation();
}

void Game::Update()
{
	const float Speed = 1.0f;
	player.pos_.x += Speed * keys->Horizontal();
	player.pos_.z -= Speed * keys->Vertical();

	if (keys->IsMove())
	{
		Vec3 velocity = { (float)keys->Horizontal(), 0, (float)keys->Vertical() };
		player.rota_ = AdjustAngle(velocity);
	}

	player.Update();

	heightT.Update();
	enemy.pos_.y = heightE.In(heightT.Ratio());
	enemy.Update();

	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			floor[i][j].Update();
		}
	}

	if (keys->IsTrigger(DIK_1)) 
	{
		heightT.Reset(true);
		enemy.pos_.y = heightE.In(heightT.Ratio());
		player.pos_ = { 0,player.scale_.y,0 };
		cameraM.ActStartAnimation(); 
	}

	cameraM.Update();
	vp = cameraM.GetViewProjection();
}

void Game::Draw()
{
	texM.SetSRVDrawCommand();

	// -------------------------- //
	pplnSet2D.SetDrawCommand();
	// ----- 背景スプライト ----- //

	// -------------------------- //
	pplnSet3D.SetDrawCommand();
	// --------- モデル --------- //

	m1->Draw(player, vp, playerTex);
	m1->Draw(enemy, vp, enemyTex);
	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			m1->Draw(floor[i][j], vp, plainTex);
		}
	}

	// -------------------------- //
	pplnSet2D.SetDrawCommand();
	// ----- 前景スプライト ----- //
	
	// -------------------------- //
}
