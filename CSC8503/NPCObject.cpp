#include "NPCObject.h"

#include "EnemyObject.h"
#include "GameWorld.h"
#include "OrientationConstraint.h"
#include "PhysicsObject.h"
#include "PlayerObject.h"
#include "StateTransition.h"
#include "State.h"

using namespace NCL;
using namespace CSC8503;

NPCObject::NPCObject(GameWorld& gameWorld) : GameObject(gameWorld), stateMachine() {
	orientationConstraint = new OrientationConstraint(this, Vector3(0, 1, 0));
	gameWorld.AddConstraint(orientationConstraint);

	State* wanderState = new State(
		[&](float dt)->void {
			Wander(dt);
		}
	);

	stateMachine.AddState(wanderState);
}

NPCObject::~NPCObject() {
}

void NPCObject::Update(float dt) {
	transform.SetPosition(Vector3(transform.GetPosition().x, std::max(1.0f, transform.GetPosition().y), transform.GetPosition().z));

	stateMachine.Update(dt);
}

void NPCObject::Wander(float dt) {
	wanderDir += Vector3(((float)rand() / (float)RAND_MAX) * 0.2f - 0.1f, 0, ((float)rand() / (float)RAND_MAX) * 0.2f - 0.1f);
	wanderDir.Normalise();
	physicsObject->AddForce(wanderDir * wanderForce * dt);
}
