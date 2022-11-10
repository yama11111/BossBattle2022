#include "CircleCollision.h"

bool CircleCollision(Vec3 a, Vec3 b) {
	Vec3 posA, posB;

	posA = a;

	posB = b;

	Vec3 anser;

	float R1 = 5.0f;
	float R2 = 10.0f;

	anser.x = (posB.x - posA.x) * (posB.x - posA.x);
	anser.y = (posB.y - posA.y) * (posB.y - posA.y);
	anser.z = (posB.z - posA.z) * (posB.z - posA.z);

	if (anser.x + anser.y + anser.z <= (R1 + R2) * (R1 + R2)) {
		return true;
	}

	return false;;
}

bool CircleCollision(Vec3 a, Vec3 b, float R1, float R2) {
	Vec3 posA, posB;

	posA = a;

	posB = b;

	Vec3 anser;

	anser.x = (posB.x - posA.x) * (posB.x - posA.x);
	anser.y = (posB.y - posA.y) * (posB.y - posA.y);
	anser.z = (posB.z - posA.z) * (posB.z - posA.z);

	if (anser.x + anser.y + anser.z <= (R1 + R2) * (R1 + R2)) {
		return true;
	}

	return false;
}

bool CircleCollision(Transform a, Transform b, float R1, float R2){
	Vec3 posA, posB;

	posA = a.pos_;

	posB = b.pos_;

	Vec3 anser;

	anser.x = (posB.x - posA.x) * (posB.x - posA.x);
	anser.y = (posB.y - posA.y) * (posB.y - posA.y);
	anser.z = (posB.z - posA.z) * (posB.z - posA.z);

	if (anser.x + anser.y + anser.z <= (R1 + R2) * (R1 + R2)) {
		return true;
	}

	return false;;
}