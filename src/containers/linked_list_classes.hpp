#ifndef liborangepower_containers_linked_list_classes_hpp
#define liborangepower_containers_linked_list_classes_hpp

//#include "misc/misc_types.hpp"

#include <iostream>
#include <stack>
#include <vector>
#include <stdint.h>
#include "../gen_class_innards_defines.hpp"

namespace liborangepower
{

namespace containers
{

template<typename Type>
class PtrCircLinkList
{
public:		// types
	class Node final
	{
		friend class PtrCircLinkList;

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

	template<bool _reverse> 
	class NodeIterator final
	{
		friend class PtrCircLinkList;

	public:		// constants
		static constexpr bool REVERSE = _reverse;

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
			_node = !REVERSE ? _node->next() : _node->prev();
			return *this;
		}

		inline NodeIterator& operator -- ()
		{
			_node = !REVERSE ? _node->prev() : _node->next();
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
	inline PtrCircLinkList()
	{
		_head._next = &_head;
		_head._prev = &_head;
	}

	//GEN_NO_CM_CONSTRUCTORS_AND_ASSIGN(PtrCircLinkList);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(PtrCircLinkList)

	virtual inline ~PtrCircLinkList()
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

	inline NodeIterator<false> begin()
	{
		return NodeIterator<false>(head()->next());
	}
	inline const NodeIterator<false> begin() const
	{
		return NodeIterator<false>(head()->next());
	}
	inline NodeIterator<false> end()
	{
		return NodeIterator<false>(head());
	}
	inline const NodeIterator<false> end() const
	{
		return NodeIterator<false>(head());
	}

	inline NodeIterator<true> rbegin()
	{
		return NodeIterator<true>(_head._prev);
	}
	inline const NodeIterator<true> rbegin() const
	{
		return NodeIterator<true>(_head._prev);
	}
	inline NodeIterator<true> rend()
	{
		return NodeIterator<true>(_head._prev->_next);
	}
	inline const NodeIterator<true> rend() const
	{
		return NodeIterator<true>(_head._prev->_next);
	}

	inline const NodeIterator<false> cbegin() const
	{
		return NodeIterator<false>(_head._next);
	}
	inline const NodeIterator<false> cend() const
	{
		return NodeIterator<false>(_head._next->_prev);
	}
	inline const NodeIterator<true> crbegin() const
	{
		return NodeIterator<true>(_head._prev);
	}
	inline const NodeIterator<true> crend() const
	{
		return NodeIterator<true>(_head._prev->_next);
	}

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

	template<bool reverse=false>
	inline NodeIterator<reverse> front()
	{
		return NodeIterator<reverse>(_head._next);
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> back()
	{
		return NodeIterator<reverse>(_head._prev);
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> push_front(const Type& to_push)
	{
		return insert_after<reverse>(head(), to_push);
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> push_front(Type&& to_push)
	{
		return insert_after<reverse>(head(), std::move(to_push));
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> push_back(const Type& to_push)
	{
		return insert_before<reverse>(head(), to_push);
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> push_back(Type&& to_push)
	{
		return insert_before<reverse>(head(), std::move(to_push));
	}
	inline void pop_front()
	{
		remove_after(head());
	}
	inline void pop_back()
	{
		remove_before(head());
	}


	template<bool reverse=false>
	inline NodeIterator<reverse> insert_before(Node* where,
		const Type& to_insert)
	{
		return _inner_insert_before<reverse>(where, new Node(to_insert));
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> insert_before(Node* where,
		Type&& to_insert)
	{
		return _inner_insert_before<reverse>(where,
			new Node(std::move(to_insert)));
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> insert_after(Node* where,
		const Type& to_insert)
	{
		return _inner_insert_after<reverse>(where, new Node(to_insert));
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> insert_after(Node* where,
		Type&& to_insert)
	{
		return _inner_insert_after<reverse>(where,
			new Node(std::move(to_insert)));
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
	template<bool reverse=false>
	inline NodeIterator<reverse> _inner_insert_before(Node* where,
		Node* what)
	{
		auto old_prev = where->_prev;

		old_prev->_next = what;
		what->_prev = old_prev;

		where->_prev = what;
		what->_next = where;

		return NodeIterator<reverse>(what);
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> _inner_insert_after(Node* where,
		Node* what)
	{
		auto old_next = where->_next;

		old_next->_prev = what;
		what->_next = old_next;

		where->_next = what;
		what->_prev = where;

		return NodeIterator<reverse>(what);
	}
};

template<typename Type, typename ArgIndexT=int64_t>
class IndCircLinkList
{
public:		// types
	using IndexT = ArgIndexT;

public:		// constants
	static constexpr IndexT NULL_INDEX = -1;

public:		// types

	class Node final
	{
		friend class IndCircLinkList;

	private:		// variables
		ArgIndexT _next = NULL_INDEX, _prev = NULL_INDEX;

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

		GEN_GETTER_BY_VAL(next);
		GEN_GETTER_BY_VAL(prev);
	};

	template<bool _reverse> 
	class NodeIterator final
	{
		friend class IndCircLinkList;

	public:		// constants
		static constexpr bool REVERSE = _reverse;

	private:		// variables
		IndCircLinkList* _list = nullptr;
		IndexT _node_index = NULL_INDEX;

	public:		// functions
		NodeIterator() = default;
		inline NodeIterator(IndCircLinkList* s_list, IndexT s_node_index)
			: _list(s_list), _node_index(s_node_index)
		{
		}
		inline NodeIterator(const IndCircLinkList* s_list,
			IndexT s_node_index)
			: _list(const_cast<IndCircLinkList*>(s_list)),
			_node_index(s_node_index)
		{
		}

		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(NodeIterator);

		~NodeIterator() = default;

		inline Node& node()
		{
			return _list->at(_node_index);
		}
		inline const Node& node() const
		{
			return _list->at(_node_index);
		}

		inline operator Node* () const
		{
			return node();
		}

		inline Node& operator * () const
		{
			return _list->at(_node_index);
		}
		inline Node* operator -> () const
		{
			return &_list->at(_node_index);
		}

		inline NodeIterator& operator ++ ()
		{
			_node_index = !_reverse ? node().next() : node().prev();
			return *this;
		}

		inline NodeIterator& operator -- ()
		{
			_node_index = !_reverse ? node().prev() : node().next();
			return *this;
		}

		inline bool operator == (const NodeIterator& other) const
		{
			return ((_list == other._list)
				&& (_node_index == other._node_index));
		}
		inline bool operator != (const NodeIterator& other) const
		{
			return ((_list != other._list)
				|| (_node_index != other._node_index));
		}
	};


public:		// constants
	static constexpr IndexT HEAD_INDEX = 0;
private:		// variables
	std::vector<IndexT> _avail_index_stack;
	std::vector<Node> _node_vec;

public:		// functions
	inline IndCircLinkList()
	{
		_node_vec.push_back(Node());
		head()._next = HEAD_INDEX;
		head()._prev = HEAD_INDEX;
	}

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(IndCircLinkList);

	virtual inline ~IndCircLinkList() = default;

	inline Node& head()
	{
		return at(HEAD_INDEX);
	}
	inline const Node& head() const
	{
		return at(HEAD_INDEX);
	}

	inline Node& at(ArgIndexT index)
	{
		return _node_vec.at(index);
	}
	inline const Node& at(ArgIndexT index) const
	{
		return _node_vec.at(index);
	}

	inline bool empty() const
	{
		return (head()._next == HEAD_INDEX);
	}

	inline NodeIterator<false> begin()
	{
		return NodeIterator<false>(this, head().next());
	}
	inline const NodeIterator<false> begin() const
	{
		return NodeIterator<false>(this, head().next());
	}
	inline NodeIterator<false> end()
	{
		return NodeIterator<false>(this, HEAD_INDEX);
	}
	inline const NodeIterator<false> end() const
	{
		return NodeIterator<false>(this, HEAD_INDEX);
	}

	inline NodeIterator<true> rbegin()
	{
		return NodeIterator<true>(this, head().prev());
	}
	inline const NodeIterator<true> rbegin() const
	{
		return NodeIterator<true>(this, head().prev());
	}
	inline NodeIterator<true> rend()
	{
		return NodeIterator<true>(this, HEAD_INDEX);
	}
	inline const NodeIterator<true> rend() const
	{
		return NodeIterator<true>(this, HEAD_INDEX);
	}

	inline const NodeIterator<false> cbegin() const
	{
		return NodeIterator<false>(this, head().next());
	}
	inline const NodeIterator<false> cend() const
	{
		return NodeIterator<false>(this, HEAD_INDEX);
	}
	inline const NodeIterator<true> crbegin() const
	{
		return NodeIterator<true>(this, head().prev());
	}
	inline const NodeIterator<true> crend() const
	{
		return NodeIterator<true>(this, HEAD_INDEX);
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> front()
	{
		return NodeIterator<reverse>(this, head().next());
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> back()
	{
		return NodeIterator<reverse>(this, head().prev());
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> push_front(const Type& to_push)
	{
		return insert_after<reverse>(HEAD_INDEX, to_push);
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> push_front(Type&& to_push)
	{
		return insert_after<reverse>(HEAD_INDEX, std::move(to_push));
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> push_back(const Type& to_push)
	{
		return insert_before<reverse>(HEAD_INDEX, to_push);
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> push_back(Type&& to_push)
	{
		return insert_before<reverse>(HEAD_INDEX, std::move(to_push));
	}
	inline void pop_front()
	{
		remove_after(HEAD_INDEX);
	}
	inline void pop_back()
	{
		remove_before(HEAD_INDEX);
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> insert_before(IndexT where,
		const Type& to_insert)
	{
		return _inner_insert_before<reverse>(where, Node(to_insert));
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> insert_before(IndexT where,
		Type&& to_insert)
	{
		return _inner_insert_before<reverse>(where,
			Node(std::move(to_insert)));
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> insert_after(IndexT where,
		const Type& to_insert)
	{
		return _inner_insert_after<reverse>(where, Node(to_insert));
	}
	template<bool reverse=false>
	inline NodeIterator<reverse> insert_after(IndexT where,
		Type&& to_insert)
	{
		return _inner_insert_after<reverse>(where,
			Node(std::move(to_insert)));
	}

	inline void remove_before(IndexT where)
	{
		const auto old_prev = at(where)._prev;
		const auto old_prev_prev = at(old_prev)._prev;

		at(old_prev_prev)._next = where;
		at(where)._prev = old_prev_prev;

		at(old_prev)._next = NULL_INDEX;
		at(old_prev)._prev = NULL_INDEX;
		at(old_prev).data = Type();
		_avail_index_stack.push_back(old_prev);
	}
	inline void remove_after(IndexT where)
	{
		const auto old_next = at(where)._next;
		const auto old_next_next = at(old_next)._next;

		at(old_next_next)._next = where;
		at(where)._next = old_next_next;

		at(old_next)._next = NULL_INDEX;
		at(old_next)._prev = NULL_INDEX;
		at(old_next).data = Type();
		_avail_index_stack.push_back(old_next);
	}
	inline void remove(IndexT where)
	{
		const auto old_next = at(where)._next;
		const auto old_prev = at(where)._prev;

		at(old_next)._prev = old_prev;
		at(old_prev)._next = old_next;

		at(where)._next = NULL_INDEX;
		at(where)._prev = NULL_INDEX;
		at(where).data = Type();
		_avail_index_stack.push_back(where);
	}

private:		// functions
	template<bool reverse=false>
	inline NodeIterator<reverse> _inner_insert_before(IndexT where,
		Node&& what)
	{
		const auto what_index = _alloc_what_index(std::move(what));

		const auto old_prev = at(where)._prev;

		at(old_prev)._next = what_index;
		at(what_index)._prev = old_prev;

		at(where)._prev = what_index;
		at(what_index)._next = where;

		return NodeIterator<reverse>(this, what_index);
	}

	template<bool reverse=false>
	inline NodeIterator<reverse> _inner_insert_after(IndexT where,
		Node&& what)
	{
		const auto what_index = _alloc_what_index(std::move(what));

		const auto old_next = at(where)._next;

		at(old_next)._prev = what_index;
		at(what_index)._next = old_next;

		at(where)._next = what_index;
		at(what_index)._prev = where;

		return NodeIterator<reverse>(this, what_index);
	}

	inline IndexT _alloc_what_index(Node&& what)
	{
		if (_avail_index_stack.empty())
		{
			const auto ret = _node_vec.size();
			_node_vec.push_back(std::move(what));
			return ret;
		}
		else // if (!_avail_index_stack.empty())
		{
			const auto ret = _avail_index_stack.back();
			_node_vec.at(ret) = std::move(what);
			return ret;
		}
	}
};


} // namespace containers

} // namespace liborangepower

template<typename Type>
std::ostream& operator << (std::ostream& os,
	const liborangepower::containers::PtrCircLinkList<Type>& to_print)
{
	for (auto iter=to_print.begin(); iter!=to_print.end(); ++iter)
	{
		os << iter->data;

		auto temp_iter = iter;
		++temp_iter;

		if (temp_iter != to_print.end())
		{
			os << ",";
		}
		os << "\n";
	}
	return os;
}
template<typename Type>
std::ostream& operator << (std::ostream& os,
	const liborangepower::containers::IndCircLinkList<Type>& to_print)
{
	for (auto iter=to_print.begin(); iter!=to_print.end(); ++iter)
	{
		os << iter->data;

		auto temp_iter = iter;
		++temp_iter;

		if (temp_iter != to_print.end())
		{
			os << ",";
		}
		os << "\n";
	}
	return os;
}


#endif		// liborangepower_containers_linked_list_classes_hpp
