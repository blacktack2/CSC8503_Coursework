#pragma once

namespace NCL {
	enum class CollisionLayer {
		Default = 0,
		Layer1,
		Layer2,
		MAX_LAYER
	};

	const int layerInteractions[3] = {
		1 << (int)CollisionLayer::Default | 1 << (int)CollisionLayer::Layer1, // Default
		1 << (int)CollisionLayer::Default | 1 << (int)CollisionLayer::Layer1, // Layer1
		1 << (int)CollisionLayer::Layer2                                      // Layer2
	};

	static inline bool DoCollisionLayersOverlap(CollisionLayer a, CollisionLayer b) {
		return layerInteractions[(int)a] & (1 << (int)b);
	}
}