#pragma once
#include "Vector2.h"
#include "CollisionDetection.h"
#include "Debug.h"

namespace NCL {
	using namespace NCL::Maths;
	namespace CSC8503 {
		template<class T>
		class QuadTree;

		template<class T>
		struct QuadTreeEntry {
			Vector3 pos;
			Vector3 size;
			T object;

			QuadTreeEntry(T obj, Vector3 pos, Vector3 size) {
				object		= obj;
				this->pos	= pos;
				this->size	= size;
			}
		};

		template<class T>
		class QuadTreeNode	{
		public:
			typedef std::function<void(std::list<QuadTreeEntry<T>>&)> QuadTreeFunc;
		protected:
			friend class QuadTree<T>;

			QuadTreeNode() {}

			QuadTreeNode(Vector2 pos, Vector2 size) {
				children		= nullptr;
				this->position	= pos;
				this->size		= size;
			}

			~QuadTreeNode() {
				delete[] children;
			}

			void Insert(T& object, const Vector3& objectPos, const Vector3& objectSize, int depthLeft, int maxSize, bool isDynamic) {
				if (!CollisionDetection::AABBTest(objectPos, Vector3(position.x, 0, position.y), objectSize, Vector3(size.x, 1000.0f, size.y))) {
					return;
				}
				if (children) {
					for (int i = 0; i < 4; i++) {
						children[i].Insert(object, objectPos, objectSize, depthLeft - 1, maxSize, isDynamic);
					}
				} else {
					if (isDynamic) {
						dynamicContents.push_back(QuadTreeEntry<T>(object, objectPos, objectSize));
					} else {
						staticContents.push_back(QuadTreeEntry<T>(object, objectPos, objectSize));
					}
					if ((int)(dynamicContents.size() + staticContents.size()) > maxSize && depthLeft > 0 && !children) {
						Split();
						for (const auto& i : dynamicContents) {
							for (int j = 0; j < 4; j++) {
								auto entry = i;
								children[j].Insert(entry.object, entry.pos, entry.size, depthLeft - 1, maxSize, true);
							}
						}
						dynamicContents.clear();
						for (const auto& i : staticContents) {
							for (int j = 0; j < 4; j++) {
								auto entry = i;
								children[j].Insert(entry.object, entry.pos, entry.size, depthLeft - 1, maxSize, false);
							}
						}
						staticContents.clear();
					}
				}
			}

			std::list<QuadTreeEntry<T>>* Clear(int maxSize) {
				if (children) {
					bool removeChildren = true;
					std::vector<std::list<QuadTreeEntry<T>>*> childStatics{};
					for (int i = 0; i < 4; i++) {
						childStatics.push_back(children[i].Clear(maxSize));
						removeChildren &= childStatics.back() == nullptr;
					}
					if (removeChildren) {
						for (auto& statics : childStatics) {
							if (statics == nullptr) {
								continue;
							}
							for (auto& i : *statics) {
								auto entry = i;
								staticContents.push_back(i);
							}
						}

						delete[] children;
						children = nullptr;
					}
				} else {
					dynamicContents.clear();
				}
				if (staticContents.size() > maxSize) {
					return &staticContents;
				} else {
					return nullptr;
				}
			}

			void FullClear() {
				delete[] children;
				children = nullptr;

				dynamicContents.clear();
				staticContents.clear();
			}

			void Split() {
				Vector2 halfSize = size * 0.5f;
				children = new QuadTreeNode<T>[4]{
					QuadTreeNode<T>(position + Vector2(-1,  1) * halfSize, halfSize),
					QuadTreeNode<T>(position + Vector2( 1,  1) * halfSize, halfSize),
					QuadTreeNode<T>(position + Vector2(-1, -1) * halfSize, halfSize),
					QuadTreeNode<T>(position + Vector2( 1, -1) * halfSize, halfSize),
				};
			}

			void DebugDraw() {
				if (children) {
					for (int i = 0; i < 4; i++) {
						children[i].DebugDraw();
					}
				} else {
					Debug::DrawLine(Vector3(position.x, -1000, position.y), Vector3(position.x, 1000, position.y), Vector4());
				}
			}

			void OperateOnContents(QuadTreeFunc& func) {
				if (children) {
					for (int i = 0; i < 4; i++) {
						children[i].OperateOnContents(func);
					}
				} else if (!dynamicContents.empty()) {
					func(dynamicContents);
				}
			}

		protected:
			std::list<QuadTreeEntry<T>> dynamicContents;
			std::list<QuadTreeEntry<T>> staticContents;

			Vector2 position;
			Vector2 size;

			QuadTreeNode<T>* children;
		};
	}
}


namespace NCL {
	using namespace NCL::Maths;
	namespace CSC8503 {
		template<class T>
		class QuadTree
		{
		public:
			QuadTree(Vector2 size, int maxDepth = 6, int maxSize = 5){
				root = QuadTreeNode<T>(Vector2(), size);
				this->maxDepth	= maxDepth;
				this->maxSize	= maxSize;
			}
			~QuadTree() {
			}

			void Insert(T object, const Vector3& pos, const Vector3& size, bool isStatic) {
				root.Insert(object, pos, size, maxDepth, maxSize, isStatic);
			}

			void Clear() {
				root.Clear(maxSize);
			}

			void FullClear() {
				root.FullClear();
			}

			void DebugDraw() {
				root.DebugDraw();
			}

			void OperateOnContents(typename QuadTreeNode<T>::QuadTreeFunc  func) {
				root.OperateOnContents(func);
			}

		protected:
			QuadTreeNode<T> root;
			int maxDepth;
			int maxSize;
		};
	}
}