#ifndef _LIST_
#define _LIST_

#include <initializer_list>
#include <algorithm>

template<typename T>
class List
{
private:
	struct Node
	{
		T value;
		Node* next;
		Node* previous;
	};
	Node* first_node;
	Node* current_node;
	Node* last_node;
	size_t m_size;
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
			it = it->next;
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
			it = it->previous;
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
			it = it->next;
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
			it = it->previous;
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
			it = it->previous;
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
			it = it->next;
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
			it = it->previous;
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
			it = it->next;
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
	explicit List() : first_node{ nullptr }, current_node{ nullptr }, last_node{ nullptr }, m_size{ 0 } {}
	explicit List(size_t n) : first_node{ nullptr }, current_node{ nullptr }, last_node{ nullptr }, m_size{ 0 }
	{
		for (int i{}; i < n; ++i)
		{
			Node* ptr_tmp_node{ new Node };
			if (!i)
			{
				first_node = ptr_tmp_node;
				current_node = ptr_tmp_node;
				last_node = ptr_tmp_node;
				ptr_tmp_node->previous = nullptr;
				ptr_tmp_node->next = nullptr;
				ptr_tmp_node->value = T{};
			}
			else
			{
				current_node->next = ptr_tmp_node;
				last_node = ptr_tmp_node;
				ptr_tmp_node->next = nullptr;
				ptr_tmp_node->previous = current_node;
				ptr_tmp_node->value = T{};
				current_node = ptr_tmp_node;
			}
		}
		m_size += n;
	}
	List(size_t n, const T& val) : first_node{ nullptr }, current_node{ nullptr }, last_node{ nullptr }, m_size{}
	{
		for (int i{}; i < n; ++i)
		{
			push_back(val);
		}
	}
	List(std::initializer_list<T> l) : first_node{ nullptr }, current_node{ nullptr }, last_node{ nullptr }, m_size{}
	{
		for (const auto& it : l)
		{
			push_back(it);
		}
	}
	List(const List& x) : first_node{ nullptr }, current_node{ nullptr }, last_node{ nullptr }, m_size{}
	{
		Node* ptr_tmp_node{ x.first_node };
		while (ptr_tmp_node != nullptr)
		{
			push_back(ptr_tmp_node->value);
			ptr_tmp_node = ptr_tmp_node->next;
		}
	}
	void push_back(const T& value)
	{
		Node* ptr_tmp_node{ new Node };
		if (!m_size)
		{
			first_node = ptr_tmp_node;
			current_node = ptr_tmp_node;
			last_node = ptr_tmp_node;
			ptr_tmp_node->previous = nullptr;
			ptr_tmp_node->next = nullptr;
			ptr_tmp_node->value = value;
		}
		else
		{
			current_node->next = ptr_tmp_node;
			last_node = ptr_tmp_node;
			ptr_tmp_node->next = nullptr;
			ptr_tmp_node->previous = current_node;
			ptr_tmp_node->value = value;
			current_node = ptr_tmp_node;
		}
		m_size++;
	}
	iterator erase(const_iterator position)
	{
		const_iterator it{ cbegin() };
		while (it != position)
		{
			it++;
		}
		Node* ptr_current_node{ it.getPtrNode() };
		if (ptr_current_node == first_node)
		{
			Node* ptr_next_node{ ptr_current_node->next };
			delete ptr_current_node;
			first_node = ptr_next_node;
			ptr_next_node->previous = nullptr;
			m_size--;
		}
		else if (ptr_current_node == last_node)
		{
			//cout << "last node" << endl;
		}
		else
		{
			Node* ptr_previous_node{ ptr_current_node->previous };
			Node* ptr_next_node{ ptr_current_node->next };
			ptr_previous_node->next = ptr_next_node;
			ptr_next_node->previous = ptr_previous_node;
			//delete ptr_current_node;
			//m_size--;
		}
		return it;
		//return iterator(ptr_next_node);
	}
	iterator begin() const
	{
		return iterator(first_node);
	}
	iterator end() const
	{
		if (!m_size)
		{
			return iterator();
		}
		return iterator(last_node->next);
	}
	const_iterator cbegin() const
	{
		return const_iterator(first_node);
	}
	const_iterator cend() const
	{
		if (!m_size)
		{
			return const_iterator();
		}
		return const_iterator(last_node->next);
	}
	reverse_iterator rbegin() const
	{
		return reverse_iterator(last_node);
	}
	reverse_iterator rend() const
	{
		if (!m_size)
		{
			return reverse_iterator();
		}
		return reverse_iterator(first_node->previous);
	}
	const_reverse_iterator crbegin() const
	{
		return const_reverse_iterator(last_node);
	}
	const_reverse_iterator crend() const
	{
		if (!m_size)
		{
			return const_reverse_iterator();
		}
		return const_reverse_iterator(first_node->previous);
	}
	void clear()
	{
		while (first_node != nullptr)
		{
			Node* ptr_tmp{ first_node };
			first_node = first_node->next;
			delete ptr_tmp;
		}
		first_node = nullptr;
		last_node = nullptr;
		m_size = 0;
	}
	bool empty() const
	{
		return m_size == 0;
	}
	size_t size() const
	{
		return m_size;
	}
	~List()
	{
		while (first_node != nullptr)
		{
			Node* ptr_tmp_node{ first_node };
			first_node = first_node->next;
			delete ptr_tmp_node;
		}
	}
};
#endif
