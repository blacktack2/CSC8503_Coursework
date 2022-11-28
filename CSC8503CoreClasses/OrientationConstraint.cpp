#include "OrientationConstraint.h"
#include "GameObject.h"
#include "PhysicsObject.h"
using namespace NCL;
using namespace Maths;
using namespace CSC8503;

OrientationConstraint::OrientationConstraint(GameObject* a, GameObject* b, Vector3 f) {
	objectA = a;
	objectB = b;
	forward = f;
}

OrientationConstraint::~OrientationConstraint() {

}

void OrientationConstraint::UpdateConstraint(float dt) {
	Vector3 relativePos = objectA->GetTransform().GetPosition() - objectB->GetTransform().GetPosition();

	Vector3 expectedDirection = relativePos.Normalised();
	Vector3 actualDirection = objectB->GetTransform().GetOrientation() * forward;

	Vector3 directionDelta = expectedDirection - actualDirection;

	if (directionDelta == Vector3(0)) {
		return;
	}

	float offset = directionDelta.Length();

	PhysicsObject* physB = objectB->GetPhysicsObject();

	Matrix3 inertia = physB->GetInertiaTensor();

	float biasFactor = 0.01f;
	float bias = -(biasFactor / dt) * offset;

	Vector3 angularImpulse = (inertia * Vector3::Cross(directionDelta, expectedDirection)) * bias;

	physB->ApplyAngularImpulse(angularImpulse);
}