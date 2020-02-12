#pragma once

template <typename T> class List
{
private:
	struct Node
	{
		T Value;
		Node* prev = nullptr;
		Node* next = nullptr;
	};
	Node* _begin = nullptr;
	Node* _end = nullptr;

	int _size;

public: 
	void AddBack(T* value)
	{
		Node* node = new Node();
		node->Value = *value;
		if (_begin == _end == nullptr)
		{
			_end = _begin = node;
			_size = 1;
		}
		else
		{
			_end->next = node;
			node->prev = _end;
			_end = node;
			_size++;
		}
	}
	void RemoveBack()
	{
		if (_begin == _end == nullptr)
			return;
		if (_begin == _end && _begin != nullptr)
		{
			delete(_begin);
			_begin = _end = nullptr;

		}
		else
		{
			_end->prev->next = nullptr;
			Node* toDelete = _end;
			_end = _end->prev;

			delete(toDelete);
		}
		_size--;
	}

	T* GetAt(int position)
	{
		if (position > _size || position < 1)
			return nullptr;
		if (position < _size / 2)
		{
			int counter = 1;
			Node* curr = _begin;
			while (counter != position)
			{
				curr = curr->next;
				counter++;
			}
			return curr;
		}
		else
		{
			int counter = _size;
			Node* curr = _begin;
			while (counter != position)
			{
				curr = curr->next;
				counter--;
			}
			return curr;
		}
	}
	template <typename Proc>
	void Foreach(Proc proc)
	{
		Node* curr = _begin;
		do
		{
			proc(curr);
			curr = curr->next;
		} while (_begin != _end);
	}
};