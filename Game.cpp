#include "Game.h"
#include "Calc.h"
#include "Random.h"
#include "Def.h"

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
	enemy.pos_ = { 0,enemy.scale_.y,20 };

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

	camera.Initialize({ { 0,60.0f,-100.0f } });
}

void Game::Update()
{	
	player.Update();
	enemy.Update();
	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			floor[i][j].Update();
		}
	}

	if (keys->IsTrigger(DIK_SPACE))
	{
		camera.Shaking(3.0f, 0.2f);
	}
	camera.Update();
	vp = camera.GetViewProjection();
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
