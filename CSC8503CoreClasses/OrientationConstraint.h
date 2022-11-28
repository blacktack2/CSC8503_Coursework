#pragma once
#include "Constraint.h"
#include "Transform.h"

namespace NCL {
	namespace CSC8503 {
		class GameObject;

		class OrientationConstraint : public Constraint {
		public:
			OrientationConstraint(GameObject* a, GameObject* b, Vector3 forward = Vector3(0, 0, 1));
			~OrientationConstraint();

			void UpdateConstraint(float dt) override;

		protected:
			GameObject* objectA;
			GameObject* objectB;

			Vector3 forward;
		};
	}
}

