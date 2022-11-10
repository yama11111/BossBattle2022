#include "Game.h"
#include "Calc.h"
#include "Def.h"
#include "CircleCollision.h"
#include "Ease.h"
#include "Random.h"

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

	t1.Initialize({});
	t2.Initialize({});
	t3.Initialize({});

	vp.Initialize({});

	player.Initialize(m1.get());
	enemy.Initialize(m1.get());

	heightE.Initialize(enemy.transform.scale_.y + 200, enemy.transform.scale_.y, 3.0f);
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
			f.scale_ = { 20,20,20 };
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

	vp.Initialize({});
	vp.eye_ = { 0,200.0f,-500.0f };

	CameraManager::StaticInitialize(&player.transform, &enemy.transform);
	cameraM.Initialize();
	cameraM.ActStartAnimation();
}

void Game::Update()
{
	t1.Update();
	t2.Update();
	t3.Update();
	vp.Update();

	if (keys->IsMove())
	{
		Vec3 velocity = { (float)keys->Horizontal(), 0, (float)keys->Vertical() };
		//player.transform.rota_ = AdjustAngle(velocity);
	}

	//向きベクトル
	Vec3 a = cameraM.CameraVelocity();

	player.Update(a);

	heightT.Update();
	enemy.transform.pos_.y = heightE.In(heightT.Ratio());
	enemy.Update(player);

	//if (CircleCollision(player.GetWorldPosition(), enemy.GetWorldPosition())) {
		//enemy.OnCollision();
	//}

	if (keys->IsDown(DIK_RIGHT))
		vp.eye_.y++;

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
		enemy.transform.pos_.y = heightE.In(heightT.Ratio());
		player.transform.pos_ = { 0,player.transform.scale_.y,0 };
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

	s1->Draw(t1, plainTex);

	// -------------------------- //
	pplnSet3D.SetDrawCommand();
	// --------- モデル --------- //

	//m1->Draw(t2, vp, plainTex);
	player.Draw(vp, playerTex, enemyTex);
	enemy.Draw(vp, enemyTex, plainTex);

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

	s1->Draw(t3, plainTex);

	// -------------------------- //
}
