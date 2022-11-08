#pragma once
#include "Model.h"
//#include "Keys.h"

using namespace DX;
//using namespace Input;
using namespace Math;
using namespace Object;

class Player {
public:
	Model* model;
	Transform transform;
	//Keys key;

	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& vp, const UINT tex);
};
