#pragma once
#include "CollisionVolume.h"

namespace NCL {
	class OBBVolume : CollisionVolume
	{
	public:
		OBBVolume(const Maths::Vector3& halfDims, CollisionLayer layer = CollisionLayer::Default) {
			type		= VolumeType::OBB;
			this->layer = layer;
			halfSizes	= halfDims;
		}
		~OBBVolume() {}

		Maths::Vector3 GetHalfDimensions() const {
			return halfSizes;
		}
	protected:
		Maths::Vector3 halfSizes;
	};
}

