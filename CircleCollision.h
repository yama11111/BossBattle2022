#pragma once
#include "Vec3.h"
#include "Transform.h"
#include <math.h>

using Math::Vec3;
using namespace Object;

bool CircleCollision(Vec3 a, Vec3 b);

bool CircleCollision(Vec3 a, Vec3 b, float R1, float R2);

bool CircleCollision(Transform a, Transform b, float R1, float R2);
