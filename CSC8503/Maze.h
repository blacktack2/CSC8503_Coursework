#include "NavigationGrid.h"

namespace NCL {
	namespace CSC8503 {
		class GameWorld;

		class Maze {
		public:
			Maze(GameWorld& gameWorld, float size, float height, int boundsX, int boundsZ, Vector3 position);

			NavigationGrid& GetNavGrid() {
				return navGrid;
			}
		private:
			GameWorld& gameWorld;
			NavigationGrid navGrid;
		};
	}
}