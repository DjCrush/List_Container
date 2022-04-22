#ifndef _LIST_
#define _LIST_

#include <initializer_list>
#include <iostream>

template<class T>
class List
{
private:
	struct Node
	{
		T value;
		Node* pNext;
		Node* pPrevious;
	};
    Node* m_pFirstNode;
	Node* m_pCurrentNode;
	Node* m_pLastNode;
	size_t m_nSize;
public:
	class const_iterator;
	class iterator
	{
	public:
		iterator(Node* it = nullptr) : it{ it } {}
		iterator& operator=(const iterator& rhs)
		{
			it = rhs.it;
			return *this;
		}
		iterator& operator++()
		{
			it = it->pNext;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp(*this);
			++(*this);
			return tmp;
		}
		iterator& operator--()
		{
			it = it->pPrevious;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp(*this);
			--(*this);
			return tmp;
		}
		T& operator*()
		{
			return it->value;
		}
		bool operator!=(const iterator& rhs) const
		{
			return it != rhs.it;
		}
	private:
		operator const_iterator() const
		{
			return it;
		}
		friend class List;
		friend class const_iterator;
		Node* getPtrNode() const
		{
			return it;
		}
		Node* it;
	};
	class const_iterator
	{
	public:
		const_iterator(Node* it = nullptr) : it{ it } {}
		const_iterator& operator=(const const_iterator& rhs)
		{
			it = rhs.it;
			return *this;
		}
		const_iterator& operator++()
		{
			it = it->pNext;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		const_iterator& operator--()
		{
			it = it->pPrevious;
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator tmp(*this);
			--(*this);
			return tmp;
		}
		const T& operator*() const
		{
			return it->value;
		}
		bool operator!=(const const_iterator& rhs) const
		{
			return it != rhs.it;
		}
	private:
		operator iterator() const
		{
			return it;
		}
		friend class List;
		friend class iterator;
		Node* getPtrNode() const
		{
			return it;
		}
		Node* it;
	};
	class reverse_iterator
	{
	public:
		reverse_iterator(Node* it = nullptr) : it{ it } {}
		reverse_iterator& operator=(const reverse_iterator& rhs)
		{
			it = rhs.it;
			return *this;
		}
		reverse_iterator& operator++()
		{
			it = it->pPrevious;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		reverse_iterator& operator--()
		{
			it = it->pNext;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			--(*this);
			return tmp;
		}
		T& operator*()
		{
			return it->value;
		}
		bool operator!=(const reverse_iterator& rhs) const
		{
			return it != rhs.it;
		}
	private:
		friend class List;

		Node* getPtrNode() const
		{
			return it;
		}
		Node* it;
	};
	class const_reverse_iterator
	{
	public:
		const_reverse_iterator(Node* it = nullptr) : it{ it } {}
		const_reverse_iterator& operator=(const const_reverse_iterator& rhs)
		{
			it = rhs.it;
			return *this;
		}
		const_reverse_iterator& operator++()
		{
			it = it->pPrevious;
			return *this;
		}
		const_reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		const_reverse_iterator& operator--()
		{
			it = it->pNext;
			return *this;
		}
		const_reverse_iterator operator--(int)
		{
			const_reverse_iterator tmp(*this);
			--(*this);
			return tmp;
		}
		const T& operator*() const
		{
			return it->value;
		}
		bool operator!=(const const_reverse_iterator& rhs) const
		{
			return it != rhs.it;
		}
	private:
		friend class List;
		Node* getPtrNode() const
		{
			return it;
		}
		Node* it;
	};
public:
	explicit List(size_t n = 0) : m_pFirstNode{nullptr}, m_pCurrentNode{nullptr}, m_pLastNode{nullptr}, m_nSize{n}
	{
		for (int i = 0; i < n; ++i)
		{
			Node* pTmpNode{new Node};
			if (!i)
			{
                m_pFirstNode = pTmpNode;
                m_pCurrentNode = pTmpNode;
                m_pLastNode = pTmpNode;
                pTmpNode->pPrevious = nullptr;
                pTmpNode->pNext = nullptr;
                pTmpNode->value = T{};
			}
			else
			{
                m_pCurrentNode->pNext = pTmpNode;
                m_pLastNode = pTmpNode;
                pTmpNode->pNext = nullptr;
                pTmpNode->pPrevious = m_pCurrentNode;
                pTmpNode->value = T{};
                m_pCurrentNode = pTmpNode;
			}
		}
	}
	List(size_t n, const T& val) : m_pFirstNode{ nullptr }, m_pCurrentNode{ nullptr }, m_pLastNode{ nullptr }, m_nSize{0}
	{
		for (int i = 0; i < n; ++i)
		{
			push_back(val);
		}
	}
	List(const std::initializer_list<T>& l) : m_pFirstNode{ nullptr }, m_pCurrentNode{ nullptr }, m_pLastNode{ nullptr }, m_nSize{0}
	{
		for (const auto& it : l)
		{
			push_back(it);
		}
	}
	List(const List& x) : m_pFirstNode{ nullptr }, m_pCurrentNode{ nullptr }, m_pLastNode{ nullptr }, m_nSize{0}
	{
		Node* pTmpNode{x.first_node };
		while (pTmpNode)
		{
			push_back(pTmpNode->value);
            pTmpNode = pTmpNode->pNext;
		}
	}
	void push_back(const T& value)
	{
		Node* pTmpNode{ new Node };
		if (!m_nSize)
		{
            m_pFirstNode = pTmpNode;
            m_pCurrentNode = pTmpNode;
            m_pLastNode = pTmpNode;
			pTmpNode->pPrevious = nullptr;
			pTmpNode->pNext = nullptr;
			pTmpNode->value = value;
		}
		else
		{
            m_pCurrentNode->pNext = pTmpNode;
            m_pLastNode = pTmpNode;
			pTmpNode->pNext = nullptr;
			pTmpNode->pPrevious = m_pCurrentNode;
			pTmpNode->value = value;
            m_pCurrentNode = pTmpNode;
		}
        ++m_nSize;
	}
	iterator erase(const_iterator position)
	{
		const_iterator it{ cbegin() };
		while (it != position)
		{
			++it;
		}
		Node* pCurrentNode{ it.getPtrNode() };
		if (pCurrentNode == m_pFirstNode)
		{
			Node* pNextNode{pCurrentNode->pNext };
			delete pCurrentNode;
            m_pFirstNode = pNextNode;
            pNextNode->pPrevious = nullptr;
			--m_nSize;
		}
		else if (pCurrentNode == m_pLastNode)
		{
			//cout << "last node" << endl;
		}
		else
		{
			Node* pPreviousNode{pCurrentNode->pPrevious };
			Node* ptr_next_node{ pCurrentNode->pNext };
            pPreviousNode->pNext = ptr_next_node;
			ptr_next_node->pPrevious = pPreviousNode;
			//delete ptr_current_node;
			//m_nSize--;
		}
		return it;
		//return iterator(ptr_next_node);
	}
	iterator begin() const
	{
		return iterator(m_pFirstNode);
	}
	iterator end() const
	{
		if (m_nSize)
		{
            return iterator(m_pLastNode->pNext);
		}
        return iterator();
	}
	const_iterator cbegin() const
	{
		return const_iterator(m_pFirstNode);
	}
	const_iterator cend() const
	{
		if (m_nSize)
		{
            return const_iterator(m_pLastNode->pNext);
		}
        return const_iterator();
	}
	reverse_iterator rbegin() const
	{
		return reverse_iterator(m_pLastNode);
	}
	reverse_iterator rend() const
	{
		if (m_nSize)
		{
            return reverse_iterator(m_pFirstNode->pPrevious);
		}
        return reverse_iterator();
	}
	const_reverse_iterator crbegin() const
	{
		return const_reverse_iterator(m_pLastNode);
	}
	const_reverse_iterator crend() const
	{
		if (m_nSize)
		{
            return const_reverse_iterator(m_pFirstNode->pPrevious);
		}
        return const_reverse_iterator();
	}
	void clear()
	{
		while (m_pFirstNode)
		{
			Node* ptr_tmp{ m_pFirstNode };
            m_pFirstNode = m_pFirstNode->pNext;
			delete ptr_tmp;
		}
        m_pFirstNode = nullptr;
        m_pLastNode = nullptr;
        m_nSize = 0;
	}
	bool empty() const
	{
		return m_nSize == 0;
	}
	size_t size() const
	{
		return m_nSize;
	}
	~List()
	{
		while (m_pFirstNode)
		{
            Node* pTmpNode{m_pFirstNode};
            m_pFirstNode = m_pFirstNode->pNext;
			delete pTmpNode;
		}
	}
};
#endif
