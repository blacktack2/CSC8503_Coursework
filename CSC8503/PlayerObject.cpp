#include "PlayerObject.h"

#include "PhysicsObject.h"
#include "Window.h"

using namespace NCL;
using namespace CSC8503;

PlayerObject::PlayerObject(int id) : GameObject(),
id(id), rootSequence(std::string("Root-Player").append(std::to_string(id))) {
	BehaviourAction* groundMovement = new BehaviourAction(std::string("GroundMovement-Player").append(std::to_string(id)),
		[&](float dt, BehaviourState state)->BehaviourState {
			switch (state) {
				case Initialise:
					return Ongoing;
				case Ongoing:
					HandleGroundInput(dt);
					return Ongoing;
				case Success: case Failure: default:
					return state;
			}
		}
	);

	rootSequence.AddChild(groundMovement);
}

PlayerObject::~PlayerObject() {
}

void PlayerObject::Update(float dt) {
	rootSequence.Execute(dt);
}

void PlayerObject::HandleGroundInput(float dt) {
	const float moveForce = 40;
	const float rotateTorque = 4;
	const float jumpForce = 1000;
	Vector3 movement = Vector3(0);
	Vector3 rotation = Vector3(0);
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::A)) {
		rotation.y += rotateTorque;
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::D)) {
		rotation.y -= rotateTorque;
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::W)) {
		movement.z -= moveForce;
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::S)) {
		movement.z += moveForce;
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE)) {
		movement.y += jumpForce;
	}
	physicsObject->AddForce(transform.GetOrientation() * movement);
	physicsObject->AddTorque(rotation);
}
