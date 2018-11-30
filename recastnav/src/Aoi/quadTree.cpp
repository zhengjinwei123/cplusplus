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
		// �״ι��� m_quadtreePtr Ϊ null,ֻ�гɹ���������ֵ
		if (obj->m_quadtreePtr != nullptr)
			return false;

		// ��Ҷ�ӽڵ�
		if (!m_isLeaf)
		{
			//�Ƿ��к���
			if (QuadTree *child = GetChild(m_bound))
			{
				// �ݹ�
				return child->Insert(obj);
			}
		}
		// û�к��ӣ�ֱ�Ӳ���
		m_objects.push_back(obj);
		obj->m_quadtreePtr = this;

		//�ָ�����,��Ҷ�ӽڵ㣬��������㼶������³�������洢����
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

		// ����ĸ����ǹ��ڵ�ǰ������
		if (obj->m_quadtreePtr != this) return obj->m_quadtreePtr->Remove(obj);

		m_objects.erase(std::find(m_objects.begin(), m_objects.end(), obj));
		obj->m_quadtreePtr = nullptr;
		discardEmptyBuckets();
		return true;
	}

	// ɾ������ͬʱ���²�������Ĳ����У�������������
	bool QuadTree::Update(Agent* obj)
	{
		if (!Remove(obj)) return false;

		// ������obj û���ڵ�ǰ�ڵ�֮�£����뵽node �ĸ��ڵ���
		if (m_parentPtr != nullptr && !m_bound.Contains(obj->m_bound))
		{
			return m_parentPtr->Insert(obj);
		}
		// ��Ҷ�ӽڵ�
		if (!m_isLeaf)
		{
			if (QuadTree *child = GetChild(m_bound))
				return child->Insert(obj);
		}
		// Ҷ�ӽڵ㣬ֱ�Ӳ���
		return this->Insert(obj);
	}

	// ��Ѱָ����Χ�ڵĶ��󣬲���vector ����
	std::vector<Agent*> &QuadTree::GetObjectsInBound(const AABB &bound)
	{
		m_foundObjects.clear();
		for (const auto&obj : m_objects)
		{
			// ��Χ�е�ַ��ͬ
			if (&obj->m_bound != &bound)
			{
				// ���������Χ�в�ͬ�������Ƿ��ཻ
				if (obj->m_bound.Intersects(bound)) {
					m_foundObjects.push_back(obj);
				}
			}
		}

		// ����Ҷ�ӽڵ㣬�ڵ��к���
		if (!m_isLeaf)
		{
			// ���������Χ�ڵĺ���
			if (QuadTree* child = GetChild(bound))
			{
				child->GetObjectsInBound(bound);
				m_foundObjects.insert(m_foundObjects.end(), child->m_foundObjects.begin(), child->m_foundObjects.end());
			}
			else {
				// ����������������
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

	// ��ȡ������
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

	// ��ȡ������
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

	// ɾ�����ж��� �ͺ��ӽڵ�
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

	// �ָ�Ϊ�ĸ�����
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

	// ���û�а����κζ��������������Ӷ���
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
