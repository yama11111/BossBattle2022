#pragma once
#include "Model.h"
//#include "Keys.h"

using namespace DX;
//using namespace Input;
using namespace Math;
using namespace Object;

class Player {
public:
	Model model;
	Transform transform;
	TextureManager* t;
	//Keys key;

	void Initialize(TextureManager* textre);
	void Update();
	void Draw(Math::MatViewProjection& vp, const UINT tex);
};
