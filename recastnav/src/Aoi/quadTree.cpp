#include "Aoi/quadTree.h"

namespace aoi
{
	QuadTree::QuadTree(const AABB &bound, unsigned _capacity, unsigned _maxLevel) :
		m_bound(bound),
		m_capacity(_capacity),
		m_maxLevel(_maxLevel)
	{
		m_isLeaf = true;

		m_objects.clear();
		m_foundObjects.clear();

		m_objects.reserve(_capacity);
		m_foundObjects.reserve(_capacity);
	}
	QuadTree::QuadTree(const QuadTree& other) :
		QuadTree(other.m_bound, other.m_capacity,other.m_maxLevel)
	{

	}
	QuadTree::QuadTree() :
		QuadTree({},0,0)
	{

	}
	QuadTree::~QuadTree()
	{
		Clear();
		if (m_child[0])
		{
			delete m_child[0];
			m_child[0] = nullptr;
		}
		if (m_child[1])
		{
			delete m_child[1];
			m_child[1] = nullptr;
		}
		if (m_child[2])
		{
			delete m_child[2];
			m_child[2] = nullptr;
		}
		if (m_child[3])
		{
			delete m_child[3];
			m_child[3] = nullptr;
		}
	}

	bool QuadTree::Insert(Agent* obj)
	{
		// 首次构造 m_quadtreePtr 为 null,只有成功插入后才有值
		if (obj->m_quadtreePtr != nullptr)
			return false;

		// 非叶子节点
		if (!m_isLeaf)
		{
			//是否有孩子
			if (QuadTree *child = GetChild(m_bound))
			{
				// 递归
				return child->Insert(obj);
			}
		}
		// 没有孩子，直接插入
		m_objects.push_back(obj);
		obj->m_quadtreePtr = this;

		//分割象限,是叶子节点，并且满足层级的情况下超过对象存储上限
		if (m_isLeaf && m_level < m_maxLevel && m_objects.size() >= m_capacity)
		{
			subdivide();
			Update(obj);
		}
		return true;
	}

	bool QuadTree::Remove(Agent* obj)
	{
		if (obj->m_quadtreePtr == nullptr) return false;

		// 对象的根不是挂在当前对象上
		if (obj->m_quadtreePtr != this) return obj->m_quadtreePtr->Remove(obj);

		m_objects.erase(std::find(m_objects.begin(), m_objects.end(), obj));
		obj->m_quadtreePtr = nullptr;
		discardEmptyBuckets();
		return true;
	}

	// 删除对象，同时重新插入对象到四叉树中，进行重新排列
	bool QuadTree::Update(Agent* obj)
	{
		if (!Remove(obj)) return false;

		// 如果这个obj 没有在当前节点之下，插入到node 的父节点下
		if (m_parentPtr != nullptr && !m_bound.Contains(obj->m_bound))
		{
			return m_parentPtr->Insert(obj);
		}
		// 非叶子节点
		if (!m_isLeaf)
		{
			if (QuadTree *child = GetChild(m_bound))
				return child->Insert(obj);
		}
		// 叶子节点，直接插入
		return this->Insert(obj);
	}

	// 搜寻指定范围内的对象，并以vector 返回
	std::vector<Agent*> &QuadTree::GetObjectsInBound(const AABB &bound)
	{
		m_foundObjects.clear();
		for (const auto&obj : m_objects)
		{
			// 包围盒地址不同
			if (&obj->m_bound != &bound)
			{
				// 如果两个包围盒不同，则检测是否相交
				if (obj->m_bound.Intersects(bound)) {
					m_foundObjects.push_back(obj);
				}
			}
		}

		// 不是叶子节点，节点有孩子
		if (!m_isLeaf)
		{
			// 查找这个范围内的孩子
			if (QuadTree* child = GetChild(bound))
			{
				child->GetObjectsInBound(bound);
				m_foundObjects.insert(m_foundObjects.end(), child->m_foundObjects.begin(), child->m_foundObjects.end());
			}
			else {
				// 查找所有其他孩子
				for (QuadTree* leaf : m_child)
				{
					if (leaf->m_bound.Intersects(bound)) {
						leaf->GetObjectsInBound(bound);
						m_foundObjects.insert(m_foundObjects.end(), leaf->m_foundObjects.begin(), leaf->m_foundObjects.end());
					}
				}
			}
		}
		return m_foundObjects;
	}

	// 获取孩子数
	unsigned QuadTree::TotalChild() const
	{
		unsigned total = 0;
		if (m_isLeaf) return total;
		for (QuadTree *child : m_child)
		{
			total += child->TotalChild();
		}
		return (total + 4);
	}

	void QuadTree::GetAllObjects(std::vector<Agent*>& objList)
	{
		if (!m_objects.empty())
		{
			objList.insert(objList.end(), m_objects.begin(), m_objects.end());
		}
		if (!m_isLeaf)
		{
			for (QuadTree *child : m_child)
			{
				child->GetAllObjects(objList);
			}
		}
	}

	// 获取对象数
	unsigned QuadTree::TotalObjects() const
	{
		unsigned total = (unsigned)m_objects.size();
		if (!m_isLeaf)
		{
			for (QuadTree* child : m_child)
			{
				total += child->TotalObjects();
			}
		}
		return total;
	}

	// 删除所有对象 和孩子节点
	void QuadTree::Clear()
	{
		if (!m_objects.empty()) {
			for (auto&& obj : m_objects)
			{
				if (obj->m_quadtreePtr) {
					obj->m_quadtreePtr = nullptr;
				}
			}
			m_objects.clear();
		}
		if (!m_isLeaf)
		{
			for (QuadTree *child : m_child)
			{
				child->Clear();
			}
			m_isLeaf = true;
		}
	}

	// private func

	// 分隔为四个象限
	void QuadTree::subdivide()
	{
		float width = m_bound.GetWidth() * 0.5f;
		float height = m_bound.GetHeight() * 0.5f;
		float x = 0, z = 0;
		for (unsigned i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0: x = m_bound.GetX() + width / 2; z = m_bound.GetZ() + height / 2; break;
			case 1: x = m_bound.GetX() - width / 2; z = m_bound.GetZ() + height / 2; break;
			case 2: x = m_bound.GetX() - width / 2; z = m_bound.GetZ() - height / 2; break;
			case 3: x = m_bound.GetX() + width / 2; z = m_bound.GetZ() - height / 2; break;
			default:
				break;
			}
			m_child[i] = new QuadTree({ x,z,width,height }, m_capacity, m_maxLevel);
			m_child[i]->m_level = m_level + 1;
			m_child[i]->m_isLeaf = true;
			m_child[i]->m_parentPtr = this;
		}
		m_isLeaf = false;
	}

	// 如果没有包含任何对象则销毁所有子对象
	void QuadTree::discardEmptyBuckets()
	{
		if (!m_objects.empty())
		{
			return;
		}
		if (!m_isLeaf)
		{
			for (QuadTree * child : m_child)
			{
				if (!child->m_isLeaf || !child->m_objects.empty())
				{
					return;
				}
			}
		}

		if (Clear(), m_parentPtr != nullptr)
		{
			m_parentPtr->discardEmptyBuckets();
		}
	}

	inline QuadTree* QuadTree::GetChild(const AABB& bound) const
	{
		bool left = bound.m_upperBound.x < m_bound.m_center.x;
		bool right = bound.m_lowerBound.x > m_bound.m_center.x;
		bool top = bound.m_lowerBound.z > m_bound.m_center.z;
		bool bottom = bound.m_upperBound.z < m_bound.m_center.z;

		if (left)
		{
			if (top)
			{
				return m_child[1];
			}
			if (bottom)
			{
				return m_child[2];
			}
		}
		else if (right)
		{
			if (top)
			{
				return m_child[0];
			}
			if (bottom)
			{
				return m_child[3];
			}
		}
		return nullptr; //Cannot contain boundary -- too large
	}

}
