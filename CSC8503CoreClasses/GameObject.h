#pragma once
#include "CollisionVolume.h"
#include "Transform.h"

using std::vector;

namespace NCL::CSC8503 {
	class GameWorld;
	class NetworkObject;
	class PhysicsObject;
	class RenderObject;

	class GameObject	{
	public:
		GameObject(GameWorld& gameWorld, std::string name = "");

		GameObject(GameObject& other);
		GameObject& operator=(GameObject other);

		~GameObject();

		virtual void Update(float dt) {}

		void SetBoundingVolume(CollisionVolume* vol) {
			boundingVolume = vol;
		}

		const CollisionVolume* GetBoundingVolume() const {
			return boundingVolume;
		}

		bool IsActive() const {
			return isActive;
		}

		Transform& GetTransform() {
			return transform;
		}

		RenderObject* GetRenderObject() const {
			return renderObject;
		}

		PhysicsObject* GetPhysicsObject() const {
			return physicsObject;
		}

		NetworkObject* GetNetworkObject() const {
			return networkObject;
		}

		void SetRenderObject(RenderObject* newObject) {
			renderObject = newObject;
		}

		void SetPhysicsObject(PhysicsObject* newObject) {
			physicsObject = newObject;
		}

		const std::string& GetName() const {
			return name;
		}

		virtual void OnCollisionBegin(GameObject* otherObject) {
			//std::cout << "OnCollisionBegin event occured!\n";
		}

		virtual void OnCollisionEnd(GameObject* otherObject) {
			//std::cout << "OnCollisionEnd event occured!\n";
		}

		virtual void OnTriggerBegin(GameObject* otherObject) {
			//std::cout << "OnTriggerBegin event occured!\n";
		}

		virtual void OnTriggerEnd(GameObject* otherObject) {
			//std::cout << "OnTriggerEnd event occured!\n";
		}

		bool GetBroadphaseAABB(Vector3&outsize) const;

		void UpdateBroadphaseAABB();

		void SetWorldID(int newID) {
			worldID = newID;
		}

		int GetWorldID() const {
			return worldID;
		}

		void Delete() {
			markDelete = true;
		}
		bool IsMarkedDelete() {
			return markDelete;
		}
	protected:
		GameWorld& gameWorld;

		Transform transform;

		CollisionVolume* boundingVolume;
		PhysicsObject*   physicsObject;
		RenderObject*    renderObject;
		NetworkObject*   networkObject;

		bool isActive;
		int  worldID;
		std::string	name;

		Vector3 broadphaseAABB;
	private:
		bool markDelete = false;
	};
}
