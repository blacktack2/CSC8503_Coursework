#pragma once

namespace NCL {
	enum class CollisionLayer {
		Default = 0,
		Player,
		Enemy,
		PlayerProj,
		EnemyProj,
		MAX_LAYER,

		InteractionDefault    = 1 << (int)Default | 1 << (int)Player | 1 << (int)Enemy | 1 << (int)PlayerProj | 1 << (int)EnemyProj,
		InteractionPlayer     = 1 << (int)Default | 1 << (int)Player | 1 << (int)Enemy |                        1 << (int)EnemyProj,
		InteractionEnemy      = 1 << (int)Default | 1 << (int)Player | 1 << (int)Enemy | 1 << (int)PlayerProj                      ,
		InteractionPlayerProj = 1 << (int)Default |                    1 << (int)Enemy                                             ,
		InteractionEnemyProj  = 1 << (int)Default | 1 << (int)Player                                                               ,
	};

	const int layerInteractions[(size_t)CollisionLayer::MAX_LAYER] = {
		(int)CollisionLayer::InteractionDefault,
		(int)CollisionLayer::InteractionPlayer,
		(int)CollisionLayer::InteractionEnemy,
		(int)CollisionLayer::InteractionPlayerProj,
		(int)CollisionLayer::InteractionEnemyProj,
	};

	static inline bool DoCollisionLayersOverlap(CollisionLayer a, CollisionLayer b) {
		return layerInteractions[(int)a] & (1 << (int)b);
	}
}