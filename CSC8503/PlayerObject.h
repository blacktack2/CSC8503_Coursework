#pragma once
#include "BehaviourNode.h"
#include "BehaviourSelector.h"
#include "BehaviourSequence.h"
#include "BehaviourParallel.h"
#include "BehaviourAction.h"
#include "GameObject.h"

namespace NCL {
	namespace CSC8503 {
		class PlayerObject : public GameObject {
		public:
			PlayerObject(int id);
			~PlayerObject();

			virtual void Update(float dt) override;
		protected:
			int id;
			BehaviourParallel rootSequence;
		private:
			void HandleGroundInput(float dt);
		};
	}
}
