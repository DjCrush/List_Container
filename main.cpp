#ifndef _LIST_
#define _LIST_

template<class T>
class List
{
private:
	struct Node
	{
		T value;
		Node* next;
		Node* previous;
	};
	Node* previous;
	Node* ptr;
	Node* first_element;
	Node* end_element;
	size_t size_;
public:
	class iterator
	{
	public:
		iterator(Node* it = nullptr) : it{it} {}
		iterator& operator = ( const iterator& rhs)
		{
			this->it = rhs.it;
			return *this;
		}
		bool operator!=(const iterator& rhs) const
		{
			return (this->it != rhs.it);
		}
		iterator& operator++()
		{
			this->it = this->it->next;
			return *this;
		}
		T operator*() const
		{
			return this->it->value;
		}
	private:
		Node* it;
	};

public:
	List() : previous{ nullptr }, ptr{ nullptr }, first_element{ nullptr }, size_{ 0 } {}
	void push_back(const T& value)
	{
		Node* t{ new Node };
		t->value = value;
		t->next = nullptr;
		end_element = nullptr;
		if (size_ == 0)
		{
			ptr = t;
			first_element = t;
			t->previous = nullptr;
			previous = t;
		}
		else
		{
			t->previous = previous;
			ptr->next = t;
			ptr = t;
			previous = t;
		}
		size_++;
	}
	iterator begin() const
	{
		return iterator(first_element);
	}
	iterator end() const
	{
		return iterator(nullptr);
	}
	T& operator[](const size_t& index)
	{
		Node* t{ first_element };
		size_t t_index{ 0 };
		while (t_index != index)
		{
			t = t->next;
			t_index++;
		}
		return t->value;
	}
	void erase(size_t index)
	{
		Node* t{ first_element };
		size_t t_index{ 0 };
		while (t_index != index)
		{
			t = t->next;
			t_index++;
		}
		Node* previous_element = t->previous;
		Node* next_element = t->next;
		delete t;
		previous_element->next = next_element;
		size_--;
	}
	size_t size() const
	{
		return size_;
	}
	~List()
	{}
};
#endif
