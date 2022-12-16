#pragma once
#include "GameObject.h"
#include "StateMachine.h"

namespace NCL {
	namespace CSC8503 {
		class OrientationConstraint;

		class NPCObject : public GameObject {
		public:
			NPCObject(GameWorld& gameWorld);
			~NPCObject();

			virtual void Update(float dt) override;

			void Wander(float dt);
		private:
			StateMachine stateMachine;

			OrientationConstraint* orientationConstraint;

			Vector3 wanderDir = Vector3(0, 0, -1);

			const float wanderForce = 100.0f;
		};
	}
}