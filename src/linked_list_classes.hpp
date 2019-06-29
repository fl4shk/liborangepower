#ifndef liborangepower_linked_list_classes_hpp
#define liborangepower_linked_list_classes_hpp

//#include "misc_types.hpp"

#include "gen_class_innards_defines.hpp"

namespace liborangepower
{

namespace containers
{

template<typename Type>
class CircLinkedList
{
public:		// types
	class Node final
	{
		friend class CircLinkedList;

	private:		// variables
		Node * _next = nullptr, * _prev = nullptr;

	public:		// variables
		Type data;

	public:		// functions
		Node() = default;

		inline Node(const Type& s_data)
			: data(s_data)
		{
		}
		inline Node(Type&& s_data)
			: data(std::move(s_data))
		{
		}

		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Node);

		~Node() = default;

		GEN_GETTER_BY_VAL(next)
		GEN_GETTER_BY_VAL(prev)
	};

	class NodeIterator final
	{
		friend class CircLinkedList;

	private:		// variables
		Node* _node = nullptr;

	public:		// functions
		NodeIterator() = default;
		inline NodeIterator(Node* s_node)
			: _node(s_node)
		{
		}

		//GEN_COPY_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeIterator);
		//GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeIterator);
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(NodeIterator);

		~NodeIterator() = default;

		inline NodeIterator& operator ++ ()
		{
			_node = _node->next();
			return *this;
		}

		inline NodeIterator& operator -- ()
		{
			_node = _node->prev();
			return *this;
		}

		inline operator Node* () const
		{
			return _node;
		}

		//inline Type& operator * () const
		//inline Node& operator * ()
		//{
		//	return *_node;
		//}
		inline Node& operator * () const
		{
			return *_node;
		}

		inline Node* operator -> () const
		{
			return _node;
		}

		inline bool operator == (const NodeIterator& other) const
		{
			return (_node == other._node);
		}
		inline bool operator != (const NodeIterator& other) const
		{
			//return (!((*this) == other));
			return (_node != other._node);
		}
	};

private:		// variables
	Node _head;

public:		// functions
	inline CircLinkedList()
	{
		_head._next = &_head;
		_head._prev = &_head;
	}

	//GEN_NO_CM_CONSTRUCTORS_AND_ASSIGN(CircLinkedList);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(CircLinkedList)

	virtual inline ~CircLinkedList()
	{
		//for (auto iter=_head.next(); iter!=&_head; )
		//{
		//	auto to_delete = iter;
		//	iter = iter->next;
		//	delete to_delete;
		//}

		//while (_head._prev != &_head)
		//{
		//	remove_after(&_head);
		//}
		while (!empty())
		{
			//remove(begin());
			pop_front();
		}
	}

	inline Node* head()
	{
		return &_head;
	}

	inline bool empty() const
	{
		return (_head._next == &_head);
	}

	inline NodeIterator begin()
	{
		return NodeIterator(head()->next());
	}
	inline NodeIterator end()
	{
		return NodeIterator(head());
	}

	inline NodeIterator cbegin() const
	{
		return NodeIterator(_head._next);
	}
	inline NodeIterator cend() const
	{
		return NodeIterator(_head._next->_prev);
	}

	//inline NodeIterator rbegin()
	//{
	//	return NodeIterator(head()->prev());
	//}
	//inline NodeIterator rend()
	//{
	//	return NodeIterator(head());
	//}

	bool contains(Node* where) const
	{
		//for (auto iter : *this)
		for (auto iter=cbegin(); iter!=cend(); ++iter)
		{
			if (where == iter)
			{
				return true;
			}
		}

		return false;
	}

	inline NodeIterator front()
	{
		return NodeIterator(_head._next);
	}
	inline NodeIterator back()
	{
		return NodeIterator(_head._prev);
	}

	inline NodeIterator push_front(const Type& to_push)
	{
		return insert_after(head(), to_push);
	}
	inline NodeIterator push_front(Type&& to_push)
	{
		return insert_after(head(), std::move(to_push));
	}
	inline NodeIterator push_back(const Type& to_push)
	{
		return insert_before(head(), to_push);
	}
	inline NodeIterator push_back(Type&& to_push)
	{
		return insert_before(head(), std::move(to_push));
	}
	inline void pop_front()
	{
		remove_after(head());
	}
	inline void pop_back()
	{
		remove_before(head());
	}


	inline NodeIterator insert_before(Node* where, const Type& to_insert)
	{
		return _inner_insert_before(where, new Node(to_insert));
	}
	inline NodeIterator insert_before(Node* where, Type&& to_insert)
	{
		return _inner_insert_before(where, new Node(std::move(to_insert)));
	}

	inline NodeIterator insert_after(Node* where, const Type& to_insert)
	{
		return _inner_insert_after(where, new Node(to_insert));
	}
	inline NodeIterator insert_after(Node* where, Type&& to_insert)
	{
		return _inner_insert_after(where, new Node(std::move(to_insert)));
	}

	inline void remove_before(Node* where)
	{
		auto old_prev = where->_prev;

		auto old_prev_prev = old_prev->_prev;

		old_prev_prev->_next = where;
		where->_prev = old_prev_prev;

		delete old_prev;
	}
	inline void remove_after(Node* where)
	{
		auto old_next = where->_next;
		auto old_next_next = old_next->_next;

		old_next_next->_prev = where;
		where->_next = old_next_next;

		delete old_next;
	}
	inline void remove(Node* where)
	{
		auto old_next = where->_next;
		auto old_prev = where->_prev;

		old_next->_prev = old_prev;
		old_prev->_next = old_next;

		delete where;
	}

private:		// functions
	inline NodeIterator _inner_insert_before(Node* where, Node* what)
	{
		auto old_prev = where->_prev;

		old_prev->_next = what;
		what->_prev = old_prev;

		where->_prev = what;
		what->_next = where;

		return NodeIterator(what);
	}

	inline NodeIterator _inner_insert_after(Node* where, Node* what)
	{
		auto old_next = where->_next;

		old_next->_prev = what;
		what->_next = old_next;

		where->_next = what;
		what->_prev = where;

		return NodeIterator(what);
	}
};


} // namespace containers

} // namespace containers


#endif		// liborangepower_linked_list_classes_hpp
