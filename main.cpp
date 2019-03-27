#include "pch.h"
#include <iostream>
#include <list>

using std::cout;
using std::endl;

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
	class Iterator
	{
	public:
		Iterator(Node* it = nullptr) : it{ it } {}
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
	Iterator begin()
	{
		return Iterator(first_element);
	}
	Iterator end()
	{
		return Iterator(nullptr);
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
	size_t size()
	{
		return size_;
	}
	~List()
	{}

};

struct Point
{
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	int x;
	int y;
};

int main()
{
	List<Point> a;
	for (int i = 0; i < 10; ++i)
	{
		a.push_back(Point(100 + i, 300));
	}
	for(const auto& it : a)
	{
		cout << it.x << '\t' << it.y << '\n';
	}
	a.erase(3);
	a.erase(5);
	cout << '\n';
	for (int i = 0; i < a.size(); ++i)
	{
		cout << a[i].x << '\t' << a[i].y << '\n';
	}
	cout << a.size();
	return 0;
}
