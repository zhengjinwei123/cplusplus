#pragma once
#ifndef _MYAOI_QUAD_TREE_H__
#define _MYAOI_QUAD_TREE_H__

#include "Aoi/aabb.h"
#include "Aoi/agent.h"
#include <vector>

namespace  aoi {
	class Agent;

	class QuadTree
	{
	public:
		QuadTree(const AABB &bound, unsigned _capacity, unsigned _maxLevel);
		QuadTree(const QuadTree&);
		QuadTree();
		~QuadTree();
	public:
		bool Insert(Agent* obj);
		bool Remove(Agent* obj);
		bool Update(Agent* obj);

		std::vector<Agent*> &GetObjectsInBound(const AABB &bound);
		unsigned TotalChild() const;
		unsigned TotalObjects() const;
		void Clear();

		void GetAllObjects(std::vector<Agent*>& objList);

	public:
		std::vector<Agent*> m_objects, m_foundObjects;
	protected:
		bool m_isLeaf = true;
		unsigned m_level = 0;
		unsigned m_capacity;
		unsigned m_maxLevel;
		AABB m_bound;
		QuadTree* m_parentPtr = nullptr;
		QuadTree* m_child[4] = { nullptr,nullptr,nullptr,nullptr };
		
		void subdivide();
		void discardEmptyBuckets();
		inline QuadTree* GetChild(const AABB& bound) const;
	};
}
#endif // !_MYAOI_QUAD_TREE_H__
