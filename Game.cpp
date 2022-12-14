#include "Game.h"
#include "Calc.h"
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
}

void Game::Update()
{
	t1.Update();
	t2.Update();
	t3.Update();
	vp.Update();

	player.Update();
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
	player.Draw(vp, playerTex);

	// -------------------------- //
	pplnSet2D.SetDrawCommand();
	// ----- 前景スプライト ----- //

	s1->Draw(t3, plainTex);
	
	// -------------------------- //
}
