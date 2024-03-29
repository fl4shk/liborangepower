#ifndef liborangepower_containers_linked_list_classes_hpp
#define liborangepower_containers_linked_list_classes_hpp

//#include "misc/misc_types.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <type_traits>
#include "../gen_class_innards_defines.hpp"

#include "../concepts/is_specialization_concepts.hpp"

namespace liborangepower {
namespace containers {
//--------
//template<typename T>
//class PtrCircLinkList {
//public:		// types
//	//--------
//	using ElemT = T;
//	//--------
//	class Node final {
//		friend class PtrCircLinkList;
//	public:		// types
//		//template<typename OtherT>
//		//using CopyConstructEnIf = std::enable_if<std::is_copy_assignable
//		//	<OtherT>::value, Node>;
//
//		//template<typename OtherT>
//		//using MoveConstructEnIf = std::enable_if<std::is_move_assignable
//		//	<OtherT>::value, Node>;
//	private:		// variables
//		Node * _next = nullptr, * _prev = nullptr;
//	public:		// variables
//		T data;
//	public:		// functions
//		Node() = default;
//
//		static inline Node construct(const T& s_data) {
//			Node ret;
//			ret.data = s_data;
//			return ret;
//		}
//
//		//template<typename OtherT=T>
//		//static inline Node construct(T&& s_data) {
//		//	Node ret;
//		//	ret.data = std::move(s_data);
//		//	return ret;
//		//}
//
//		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Node);
//
//		~Node() = default;
//
//		GEN_GETTER_BY_VAL(next)
//		GEN_GETTER_BY_VAL(prev)
//	};
//	//--------
//	template<bool _reverse> 
//	class Iterator final {
//		friend class PtrCircLinkList;
//	public:		// constants
//		static constexpr bool
//			REVERSE = _reverse;
//	private:		// variables
//		Node* _node = nullptr;
//	public:		// functions
//		Iterator() = default;
//		inline Iterator(Node* s_node)
//			: _node(s_node) {
//		}
//
//		//GEN_COPY_ONLY_CONSTRUCTORS_AND_ASSIGN(Iterator);
//		//GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Iterator);
//		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Iterator);
//
//		~Iterator() = default;
//
//		inline Iterator& operator ++ () {
//			_node = !REVERSE ? _node->next() : _node->prev();
//			return *this;
//		}
//		inline Iterator& operator -- () {
//			_node = !REVERSE ? _node->prev() : _node->next();
//			return *this;
//		}
//		//inline operator Node* () const {
//		//	return _node;
//		//}
//
//		//inline T& operator * () const
//		//inline Node& operator * () {
//		//	return *_node;
//		//}
//		inline T& operator * () const {
//			return _node->data;
//		}
//		inline T* operator -> () const {
//			return &_node->data;
//		}
//
//		inline bool operator == (const Iterator& other) const {
//			return (_node == other._node);
//		}
//		inline bool operator != (const Iterator& other) const {
//			//return (!((*this) == other));
//			return (_node != other._node);
//		}
//	};
//	//--------
//	//template<bool _reverse, typename OtherT>
//	//using UpdateByCopyEnIf = std::enable_if<std::is_copy_assignable
//	//	<OtherT>::value, Iterator<_reverse>>;
//	//template<bool _reverse, typename OtherT>
//	//using UpdateByMoveEnIf = std::enable_if<std::is_move_assignable
//	//	<OtherT>::value, Iterator<_reverse>>;
//	//--------
//private:		// variables
//	//--------
//	Node _head;
//	//--------
//public:		// functions
//	//--------
//	inline PtrCircLinkList() {
//		_head._next = &_head;
//		_head._prev = &_head;
//	}
//	//GEN_NO_CM_CONSTRUCTORS_AND_ASSIGN(PtrCircLinkList);
//	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(PtrCircLinkList)
//	virtual inline ~PtrCircLinkList() {
//		//for (auto iter=_head.next(); iter!=&_head; ) {
//		//	auto to_delete = iter;
//		//	iter = iter->next;
//		//	delete to_delete;
//		//}
//
//		//while (_head._prev != &_head) {
//		//	erase_after(&_head);
//		//}
//		while (!empty()) {
//			//erase(begin());
//			pop_front();
//		}
//	}
//	//--------
//	inline Node* head() {
//		return &_head;
//	}
//	inline const Node* head() const {
//		return &_head;
//	}
//	inline bool empty() const {
//		return (_head._next == &_head);
//	}
//	//--------
//	inline Iterator<false> begin() {
//		return Iterator<false>(head()->next());
//	}
//	inline const Iterator<false> begin() const {
//		return Iterator<false>(head()->next());
//	}
//	inline Iterator<false> end() {
//		return Iterator<false>(head());
//	}
//	inline const Iterator<false> end() const {
//		return Iterator<false>(head());
//	}
//
//	inline Iterator<true> rbegin() {
//		return Iterator<true>(_head._prev);
//	}
//	inline const Iterator<true> rbegin() const {
//		return Iterator<true>(_head._prev);
//	}
//	inline Iterator<true> rend() {
//		return Iterator<true>(_head._prev->_next);
//	}
//	inline const Iterator<true> rend() const {
//		return Iterator<true>(_head._prev->_next);
//	}
//
//	inline const Iterator<false> cbegin() const {
//		return Iterator<false>(_head._next);
//	}
//	inline const Iterator<false> cend() const {
//		return Iterator<false>(_head._next->_prev);
//	}
//	inline const Iterator<true> crbegin() const {
//		return Iterator<true>(_head._prev);
//	}
//	inline const Iterator<true> crend() const {
//		return Iterator<true>(_head._prev->_next);
//	}
//	//--------
//	bool contains(Node* where) const {
//		//for (auto iter : *this)
//		for (auto iter=cbegin(); iter!=cend(); ++iter) {
//			if (where == iter) {
//				return true;
//			}
//		}
//
//		return false;
//	}
//	size_t size() const {
//		size_t ret = 0;
//
//		//for (const auto& item: *this)
//		for (auto iter=cbegin(); iter!=cend(); ++iter) {
//			++ret;
//		}
//
//		return ret;
//	}
//	//--------
//	template<bool reverse=false>
//	inline Iterator<reverse> front() {
//		return Iterator<reverse>(_head._next);
//	}
//	template<bool reverse=false>
//	inline Iterator<reverse> back() {
//		return Iterator<reverse>(_head._prev);
//	}
//	//--------
//	//template<bool reverse=false>
//	//inline UpdateByCopyEnIf<reverse>::type push_front(const T& to_push)
//	template<bool reverse=false>
//	inline Iterator<reverse> push_front(const T& to_push) {
//		return insert_after<reverse>(head(), to_push);
//	}
//	//template<bool reverse=false>
//	//inline UpdateByMoveEnIf<reverse>::type push_front(T&& to_push)
//	template<bool reverse=false>
//	inline Iterator<reverse> push_front(T&& to_push) {
//		return insert_after<reverse>(head(), std::move(to_push));
//	}
//	template<bool reverse=false>
//	inline Iterator<reverse> push_back(const T& to_push) {
//		return insert_before<reverse>(head(), to_push);
//	}
//	template<bool reverse=false>
//	inline Iterator<reverse> push_back(T&& to_push) {
//		return insert_before<reverse, T>(head(), std::move(to_push));
//	}
//	inline void pop_front() {
//		erase_after(head());
//	}
//	inline void pop_back() {
//		erase_before(head());
//	}
//	//--------
//	template<bool reverse=false>
//	inline Iterator<reverse> insert_before(Node* where,
//		const T& to_insert) {
//		Node* node = new Node();
//		node->data = to_insert;
//		return _inner_insert_before<reverse>(where, node);
//	}
//	template<bool reverse=false>
//	inline Iterator<reverse> insert_before(Node* where, T&& to_insert) {
//		Node* node = new Node();
//		node->data = std::move(to_insert);
//		return _inner_insert_before<reverse>(where, node);
//	}
//
//	template<bool reverse=false>
//	inline Iterator<reverse> insert_after(
//		Node* where, const T& to_insert
//	) {
//		Node* node = new Node();
//		node->data = to_insert;
//		return _inner_insert_after<reverse>(where, node);
//	}
//	template<bool reverse=false>
//	inline Iterator<reverse> insert_after(Node* where, T&& to_insert) {
//		Node* node = new Node();
//		node->data = std::move(to_insert);
//		return _inner_insert_after<reverse>(where, node);
//	}
//	//--------
//	inline void erase_before(Node* where) {
//		auto old_prev = where->_prev;
//
//		auto old_prev_prev = old_prev->_prev;
//
//		old_prev_prev->_next = where;
//		where->_prev = old_prev_prev;
//
//		delete old_prev;
//	}
//	inline void erase_after(Node* where) {
//		auto old_next = where->_next;
//		auto old_next_next = old_next->_next;
//
//		old_next_next->_prev = where;
//		where->_next = old_next_next;
//
//		delete old_next;
//	}
//	inline void erase(Node* where) {
//		auto old_next = where->_next;
//		auto old_prev = where->_prev;
//
//		old_next->_prev = old_prev;
//		old_prev->_next = old_next;
//
//		delete where;
//	}
//	//--------
//private:		// functions
//	//--------
//	template<bool reverse=false>
//	inline Iterator<reverse> _inner_insert_before(
//		Node* where, Node* what
//	) {
//		auto old_prev = where->_prev;
//
//		old_prev->_next = what;
//		what->_prev = old_prev;
//
//		where->_prev = what;
//		what->_next = where;
//
//		return Iterator<reverse>(what);
//	}
//	template<bool reverse=false>
//	inline Iterator<reverse> _inner_insert_after(
//		Node* where, Node* what
//	) {
//		auto old_next = where->_next;
//
//		old_next->_prev = what;
//		what->_next = old_next;
//
//		where->_next = what;
//		what->_prev = where;
//
//		return Iterator<reverse>(what);
//	}
//	//--------
//};
//
//template<typename T>
//constexpr inline bool is_ptr_circ_link_list() {
//	return concepts::is_specialization<T, PtrCircLinkList>();
//}
//
//template<typename T>
//constexpr inline std::ostream& operator << (std::ostream& os,
//	const PtrCircLinkList<T>& to_print) {
//	os << "{";
//
//	for (auto iter=to_print.begin(); iter!=to_print.end(); ++iter) {
//		//os << iter->data;
//		os << *iter;
//
//		auto temp_iter = iter;
//		++temp_iter;
//
//		if (temp_iter != to_print.end()) {
//			os << ",";
//		}
//		//os << "\n";
//	}
//
//	os << "}";
//	return os;
//}
//
//template<typename T>
//PtrCircLinkList<T> make_ptr_cll(T&& first_arg,
//	std::same_as<T> auto&&... rem_args) {
//	PtrCircLinkList<T> ret;
//
//	ret.push_back(std::move(first_arg));
//
//	(ret.push_back(std::move(rem_args)), ...);
//
//	return ret;
//}
//--------
template<std::integral IndexTarg>
static constexpr IndexTarg IND_CLL_NULL_INDEX = -1;

template<typename T, std::integral IndexTarg, typename ArgIndexAllocT,
	typename NodeAllocTarg>
class IndCircLinkList;

template<typename T, std::integral IndexTarg>
class IndCllNode final {
	template<typename, std::integral, typename, typename>
	friend class IndCircLinkList;
public:		// types
	//template<typename OtherT>
	//using CopyConstructEnIf = std::enable_if<std::is_copy_assignable
	//	<OtherT>::value, IndCllNode>;

	//template<typename OtherT>
	//using MoveConstructEnIf = std::enable_if<std::is_move_assignable
	//	<OtherT>::value, IndCllNode>;
public:		// constants
	static constexpr IndexTarg
		NULL_INDEX = IND_CLL_NULL_INDEX<IndexTarg>;
private:		// variables
	IndexTarg _next = NULL_INDEX, _prev = NULL_INDEX;
public:		// variables
	T data;
public:		// functions
	IndCllNode() = default;

	static inline IndCllNode construct(const T& s_data) {
		IndCllNode ret;
		ret.data = s_data;
		return ret;
	}

	static inline IndCllNode construct(T&& s_data) {
		IndCllNode ret;
		ret.data = std::move(s_data);
		return ret;
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(IndCllNode);

	~IndCllNode() = default;

	GEN_GETTER_BY_VAL(next);
	GEN_GETTER_BY_VAL(prev);
};

template<typename T, std::integral IndexTarg=size_t,
	typename ArgIndexAllocT=std::allocator<IndexTarg>,
	typename NodeAllocTarg=std::allocator<IndCllNode<T, IndexTarg>>>
class IndCircLinkList {
public:		// types
	using ElemT = T;
	using IndexT = IndexTarg;
	using IndexAllocT = ArgIndexAllocT;
	using NodeAllocT = NodeAllocTarg;
	using Node = IndCllNode<T, IndexT>;
public:		// constants
	static constexpr IndexT
		//NULL_INDEX = -1;
		NULL_INDEX = IND_CLL_NULL_INDEX<IndexT>;
public:		// types
	template<bool _reverse> 
	class Iterator final {
		friend class IndCircLinkList;
	public:		// constants
		static constexpr bool REVERSE = _reverse;
	private:		// variables
		IndCircLinkList* _list = nullptr;
		IndexT _node_index = NULL_INDEX;
	public:		// functions
		Iterator() = default;
		inline Iterator(IndCircLinkList* s_list, IndexT s_node_index)
			: _list(s_list), _node_index(s_node_index) {
		}
		inline Iterator(const IndCircLinkList* s_list,
			IndexT s_node_index)
			: _list(const_cast<IndCircLinkList*>(s_list)),
			_node_index(s_node_index) {
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Iterator);
		~Iterator() = default;

		inline Node& node() {
			return _list->at(_node_index);
		}
		inline const Node& node() const {
			return _list->at(_node_index);
		}

		//inline operator Node* () const {
		//	return &node();
		//}
		inline T& operator * () const {
			return _list->at(_node_index).data;
		}
		inline T* operator -> () const {
			return &(_list->at(_node_index).data);
		}

		inline Iterator& operator ++ () {
			_node_index = !_reverse ? node().next() : node().prev();
			return *this;
		}
		inline Iterator& operator -- () {
			_node_index = !_reverse ? node().prev() : node().next();
			return *this;
		}

		inline bool operator == (const Iterator& other) const {
			return ((_list == other._list)
				&& (_node_index == other._node_index));
		}
		inline bool operator != (const Iterator& other) const {
			return ((_list != other._list)
				|| (_node_index != other._node_index));
		}
	};

	//template<bool _reverse, typename OtherT>
	//using UpdateByCopyEnIf = std::enable_if<std::is_copy_assignable
	//	<OtherT>::value, Iterator<_reverse>>;

	//template<bool _reverse, typename OtherT>
	//using UpdateByMoveEnIf = std::enable_if<std::is_move_assignable
	//	<OtherT>::value, Iterator<_reverse>>;
public:		// constants
	static constexpr IndexT
		HEAD_INDEX = 0;
private:		// variables
	std::vector<IndexT, IndexAllocT> _avail_index_stack;
	std::vector<Node, NodeAllocT> _node_darr;
public:		// functions
	inline IndCircLinkList() {
		_node_darr.push_back(Node());
		head()._next = HEAD_INDEX;
		head()._prev = HEAD_INDEX;
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(IndCircLinkList);

	virtual inline ~IndCircLinkList() = default;

	inline Node& head() {
		return at(HEAD_INDEX);
	}
	inline const Node& head() const {
		return at(HEAD_INDEX);
	}

	inline Node& at(IndexTarg index) {
		return _node_darr.at(index);
	}
	inline const Node& at(IndexTarg index) const {
		return _node_darr.at(index);
	}

	inline bool empty() const {
		return (head()._next == HEAD_INDEX);
	}

	inline Iterator<false> begin() {
		return Iterator<false>(this, head().next());
	}
	inline const Iterator<false> begin() const {
		return Iterator<false>(this, head().next());
	}
	inline Iterator<false> end() {
		return Iterator<false>(this, HEAD_INDEX);
	}
	inline const Iterator<false> end() const {
		return Iterator<false>(this, HEAD_INDEX);
	}

	inline Iterator<true> rbegin() {
		return Iterator<true>(this, head().prev());
	}
	inline const Iterator<true> rbegin() const {
		return Iterator<true>(this, head().prev());
	}
	inline Iterator<true> rend() {
		return Iterator<true>(this, HEAD_INDEX);
	}
	inline const Iterator<true> rend() const {
		return Iterator<true>(this, HEAD_INDEX);
	}

	inline const Iterator<false> cbegin() const {
		return Iterator<false>(this, head().next());
	}
	inline const Iterator<false> cend() const {
		return Iterator<false>(this, HEAD_INDEX);
	}
	inline const Iterator<true> crbegin() const {
		return Iterator<true>(this, head().prev());
	}
	inline const Iterator<true> crend() const {
		return Iterator<true>(this, HEAD_INDEX);
	}

	size_t size() const {
		size_t ret = 0;

		//for (const auto& item: *this)
		for (auto iter=cbegin(); iter!=cend(); ++iter) {
			++ret;
		}

		return ret;
	}

	template<bool reverse=false>
	inline Iterator<reverse> front() {
		return Iterator<reverse>(this, head().next());
	}
	template<bool reverse=false>
	inline Iterator<reverse> back() {
		return Iterator<reverse>(this, head().prev());
	}

	//template<bool reverse=false>
	//inline UpdateByCopyEnIf<reverse>::type push_front(const T& to_push)
	template<bool reverse=false>
	inline Iterator<reverse> push_front(const T& to_push) {
		return insert_after<reverse>(HEAD_INDEX, to_push);
	}
	//template<bool reverse=false>
	//inline UpdateByMoveEnIf<reverse>::type push_front(T&& to_push)
	template<bool reverse=false>
	inline Iterator<reverse> push_front(T&& to_push) {
		return insert_after<reverse>(HEAD_INDEX, std::move(to_push));
	}
	template<bool reverse=false>
	inline Iterator<reverse> push_back(const T& to_push) {
		return insert_before<reverse>(HEAD_INDEX, to_push);
	}
	template<bool reverse=false>
	inline Iterator<reverse> push_back(T&& to_push) {
		return insert_before<reverse>(HEAD_INDEX, std::move(to_push));
	}
	inline void pop_front() {
		erase_after(HEAD_INDEX);
	}
	inline void pop_back() {
		erase_before(HEAD_INDEX);
	}

	template<bool reverse=false>
	inline Iterator<reverse> insert_before(
		IndexT where, const T& to_insert
	) {
		return _inner_insert_before<reverse>(where,
			Node::construct(to_insert));
	}
	template<bool reverse=false>
	inline Iterator<reverse> insert_before(IndexT where, T&& to_insert) {
		return _inner_insert_before<reverse>(where,
			Node::construct(std::move(to_insert)));
	}

	template<bool reverse=false>
	inline Iterator<reverse> insert_after(
		IndexT where, const T& to_insert
	) {
		return _inner_insert_after<reverse>(where,
			Node::construct(to_insert));
	}
	template<bool reverse=false>
	inline Iterator<reverse> insert_after(IndexT where, T&& to_insert) {
		return _inner_insert_after<reverse>(where,
			Node::construct(std::move(to_insert)));
	}

	inline void erase_before(IndexT where) {
		const auto old_prev = at(where)._prev;
		const auto old_prev_prev = at(old_prev)._prev;

		at(old_prev_prev)._next = where;
		at(where)._prev = old_prev_prev;

		at(old_prev)._next = NULL_INDEX;
		at(old_prev)._prev = NULL_INDEX;
		at(old_prev).data = T();
		_avail_index_stack.push_back(old_prev);
	}
	inline void erase_after(IndexT where) {
		const auto old_next = at(where)._next;
		const auto old_next_next = at(old_next)._next;

		at(old_next_next)._next = where;
		at(where)._next = old_next_next;

		at(old_next)._next = NULL_INDEX;
		at(old_next)._prev = NULL_INDEX;
		at(old_next).data = T();
		_avail_index_stack.push_back(old_next);
	}
	inline void erase(IndexT where) {
		const auto old_next = at(where)._next;
		const auto old_prev = at(where)._prev;

		at(old_next)._prev = old_prev;
		at(old_prev)._next = old_next;

		at(where)._next = NULL_INDEX;
		at(where)._prev = NULL_INDEX;
		at(where).data = T();
		_avail_index_stack.push_back(where);
	}

private:		// functions
	template<bool reverse=false>
	inline Iterator<reverse> _inner_insert_before(
		IndexT where, Node&& what
	) {
		const auto what_index = _alloc_what_index(std::move(what));

		const auto old_prev = at(where)._prev;

		at(old_prev)._next = what_index;
		at(what_index)._prev = old_prev;

		at(where)._prev = what_index;
		at(what_index)._next = where;

		return Iterator<reverse>(this, what_index);
	}

	template<bool reverse=false>
	inline Iterator<reverse> _inner_insert_after(
		IndexT where, Node&& what
	) {
		const auto what_index = _alloc_what_index(std::move(what));

		const auto old_next = at(where)._next;

		at(old_next)._prev = what_index;
		at(what_index)._next = old_next;

		at(where)._next = what_index;
		at(what_index)._prev = where;

		return Iterator<reverse>(this, what_index);
	}

	inline IndexT _alloc_what_index(Node&& what) {
		if (_avail_index_stack.empty()) {
			const auto ret = _node_darr.size();
			_node_darr.push_back(std::move(what));
			return ret;
		} else { // if (!_avail_index_stack.empty())
			const auto ret = _avail_index_stack.back();
			_avail_index_stack.pop_back();
			_node_darr.at(ret) = std::move(what);
			return ret;
		}
	}
};

template<typename T>
constexpr inline bool is_ind_circ_link_list() {
	return concepts::is_specialization<T, IndCircLinkList>();
}

//template<typename T, std::integral IndexTarg,
//	template<typename...> typename Alloc,
//	typename... RemAllocTs>
//std::ostream& operator << (std::ostream& os,
//	const IndCircLinkList<T, IndexTarg, Alloc, RemAllocTs...>& to_print)
//std::ostream& operator << (std::ostream& os,
//	const concepts::IsSpecialization<IndCircLinkList> auto& to_print)
template<concepts::IsSpecialization<IndCircLinkList> ToPrintT>
constexpr std::ostream& operator << (std::ostream& os,
	const ToPrintT& to_print) {
	os << "{";

	for (auto iter=to_print.begin(); iter!=to_print.end(); ++iter) {
		//os << iter->data;
		os << *iter;

		auto temp_iter = iter;
		++temp_iter;

		if (temp_iter != to_print.end()) {
			os << ", ";
		}
		//os << "\n";
	}

	os << "}";
	return os;
}

template<typename T, std::integral IndexTarg=size_t,
	typename ArgIndexAllocT=std::allocator<IndexTarg>,
	typename NodeAllocTarg=std::allocator<IndCllNode<T, IndexTarg>>>
IndCircLinkList<T, IndexTarg, ArgIndexAllocT, NodeAllocTarg>
	make_ind_cll(T&& first_arg, std::same_as<T> auto&&... rem_args) {
	IndCircLinkList<T, IndexTarg, ArgIndexAllocT, NodeAllocTarg> ret;

	ret.push_back(std::move(first_arg));

	(ret.push_back(std::move(rem_args)), ...);

	return ret;
}
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_linked_list_classes_hpp
