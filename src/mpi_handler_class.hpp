#ifndef liborangepower_mpi_handler_class_hpp
#define liborangepower_mpi_handler_class_hpp

#include "misc/misc_includes.hpp"
#include "misc/misc_output_funcs.hpp"
#include <mpi.h>


namespace liborangepower {
namespace mpi {
//--------
#define MPI_HANDLER_STATIC_ASSERT_0(type, func_name_str) \
	static_assert(!std::is_pointer<type>::value, "Can't " func_name_str \
		"() using a pointer to a pointer.")
#define MPI_HANDLER_STATIC_ASSERT_1(type, func_name_str) \
	static_assert(std::is_trivially_copyable<type>::value, \
		func_name_str "() requires the ability to trivially copy stuff.")

class MpiHandler {
public:		// enums
	enum class ErrorCode: int {
		FakeError,
		DidQuitWithMiscOutput,
		TooFewProcs,
		SizeTooBig,
	};

public:		// constants
	static constexpr int root = 0;

protected:		// variables
	int* _argc_ptr;
	char*** _argv_ptr;

	int _world_rank, _world_size;
	size_t _num_threads_per_proc, _min_world_size;


public:		// functions
	inline MpiHandler(
		int& s_argc, char** s_argv,
		size_t s_num_threads_per_proc=1, size_t s_min_world_size=1
	) : _argc_ptr(&s_argc), _argv_ptr(&s_argv) {
		static_assert(root == 0, "root must equal zero");

		_raw_init(*_argc_ptr, *_argv_ptr);

		set_world_rank(_raw_comm_rank(MPI_COMM_WORLD));
		set_world_size(_raw_comm_size(MPI_COMM_WORLD));
		set_num_threads_per_proc(s_num_threads_per_proc);
		set_min_world_size(s_min_world_size);

		if (world_size() < static_cast<int>(min_world_size())) {
			misc_output::printerr("World size must be at least ",
				min_world_size(), " for ", argv()[0], "\n");
			_regular_abort(ErrorCode::TooFewProcs);
		}
	}

	virtual inline ~MpiHandler() {
		_raw_finalize();
	}

	inline int argc() const {
		return *_argc_ptr;
	}
	inline char** argv() const {
		return *_argv_ptr;
	}


	// There are MPI wrappers from here on out
	template<typename T>
	inline int send(
		const T* buf, int num_instances, int dst,
		int tag=0, MPI_Comm comm=MPI_COMM_WORLD
	) const {
		MPI_HANDLER_STATIC_ASSERT_0(T, "send");
		MPI_HANDLER_STATIC_ASSERT_1(T, "send");

		return _wrapped_send(buf, num_instances, dst, tag, comm);
	}
	template<typename ArrT>
	inline int send(
		const ArrT& buf, int dst, int tag=0,
		MPI_Comm comm=MPI_COMM_WORLD
	) const {
		return send(buf.data(), buf.size(), dst, tag, comm);
	}


	//template<typename T>
	//inline int send(
	//	const DynArr<T>& buf, int dst, int tag=0,
	//	MPI_Comm comm=MPI_COMM_WORLD
	//) const {
	//	return send(buf.get_arr(), buf.get_size(), dst, tag, comm);
	//}
	//template<typename T>
	//inline int send_single(
	//	const T* non_buf, int dst, int tag=0,
	//	MPI_Comm comm=MPI_COMM_WORLD
	//) const {
	//	MPI_HANDLER_STATIC_ASSERT_0(T, "send_single");
	//	MPI_HANDLER_STATIC_ASSERT_1(T, "send_single");
	//
	//	return _wrapped_send(non_buf, 1, dst, tag, comm);
	//}
	template<typename T>
	inline int send_single(
		const T& some_var, int dst, int tag=0,
		MPI_Comm comm=MPI_COMM_WORLD
	) const {
		MPI_HANDLER_STATIC_ASSERT_0(T, "send_single");
		MPI_HANDLER_STATIC_ASSERT_1(T, "send_single");

		return _wrapped_send(&some_var, 1, dst, tag, comm);
	}


	template<typename T>
	inline int recv(
		T* buf, int num_instances, int src, int tag=MPI_ANY_TAG,
		MPI_Comm comm=MPI_COMM_WORLD, MPI_Status* status=MPI_STATUS_IGNORE
	) const {
		MPI_HANDLER_STATIC_ASSERT_0(T, "recv");
		MPI_HANDLER_STATIC_ASSERT_1(T, "recv");

		return _wrapped_recv(buf, num_instances, src, tag, comm, status);
	}
	template<typename ArrT>
	inline int recv(ArrT& buf, int src, int tag=MPI_ANY_TAG,
		MPI_Comm comm=MPI_COMM_WORLD, MPI_Status* status=MPI_STATUS_IGNORE
	) const {
		return recv(buf.data(), buf.size(), src, tag, comm, status);
	}
	//template<typename T>
	//inline int recv(
	//	DynArr<T>& buf, int src, int tag=MPI_ANY_TAG,
	//	MPI_Comm comm=MPI_COMM_WORLD,
	//	MPI_Status* status=MPI_STATUS_IGNORE
	//) {
	//	return recv(buf.get_arr(), buf.get_size(), src, tag, comm,
	//		status);
	//}
	template<typename T>
	inline int recv_single(
		T& some_var, int src, int tag=MPI_ANY_TAG,
		MPI_Comm comm=MPI_COMM_WORLD, MPI_Status* status=MPI_STATUS_IGNORE
	) const {
		MPI_HANDLER_STATIC_ASSERT_0(T, "recv_single");
		MPI_HANDLER_STATIC_ASSERT_1(T, "recv_single");

		return _wrapped_recv(&some_var, 1, src, tag, comm, status);
	}

	// This form of reduce() is not very much of a wrapper.  That is
	// intentional.
	inline int reduce(
		const void* send_buf, void* recv_buf, int count,
		MPI_Datatype data_type, MPI_Op op, int root,
		MPI_Comm comm=MPI_COMM_WORLD
	) const {
		return MPI_Reduce(send_buf, recv_buf, count, data_type, op, root,
			comm);
	}

	template<typename T>
	inline int send_recv(
		const T* send_buf, int num_send_instances, int dst, T* recv_buf,
		int num_recv_instances, int src, int send_tag=0,
		int recv_tag=MPI_ANY_TAG, MPI_Comm comm=MPI_COMM_WORLD,
		MPI_Status* status=MPI_STATUS_IGNORE
	) const {
		MPI_HANDLER_STATIC_ASSERT_0(T, "send_recv");
		MPI_HANDLER_STATIC_ASSERT_1(T, "send_recv");

		return _wrapped_send_recv(send_buf, num_send_instances, dst,
			send_tag, recv_buf, num_recv_instances, src, recv_tag, comm,
			status);
		//return raw_send_recv(send_buf, num_send_instances * sizeof(T),
		//	MPI_BYTE, dst, send_tag, recv_buf,
		//	num_recv_instances * sizeof(T), MPI_BYTE, src, recv_tag,
		//	comm, status);
	}
	template<typename T>
	inline int send_recv_single(
		const T& to_send, int dst, T& to_recv, int src, int send_tag=0,
		int recv_tag=MPI_ANY_TAG, MPI_Comm comm=MPI_COMM_WORLD,
		MPI_Status* status=MPI_STATUS_IGNORE
	) const {
		MPI_HANDLER_STATIC_ASSERT_0(T, "send_recv_single");
		MPI_HANDLER_STATIC_ASSERT_1(T, "send_recv_single");

		return _wrapped_send_recv(&to_send, 1, dst, send_tag,
			&to_recv, 1, src, recv_tag, comm, status);
	}
	template<typename T>
	inline int send_recv_single(
		const T& to_send, T& to_recv, int partner, int send_tag=0,
		int recv_tag=MPI_ANY_TAG, MPI_Comm comm=MPI_COMM_WORLD,
		MPI_Status* status=MPI_STATUS_IGNORE
	) const {
		return send_recv_single(to_send, partner, to_recv, send_tag,
			recv_tag, comm, status);
	}
	//template<typename T>
	//inline int send_recv_single(
	//	const T& to_send, T& to_recv, int send_tag=0,
	//	int recv_tag=MPI_ANY_TAG, MPI_Comm comm=MPI_COMM_WORLD,
	//	MPI_Status* status=MPI_STATUS_IGNORE
	//) {
	//	return send_recv_single(to_send, get_partner_old(), to_recv,
	//		send_tag, recv_tag, comm, status);
	//}

	inline size_t total_num_threads() const {
		return world_size() * num_threads_per_proc();
	}
	inline size_t starting_thread_num() const {
		return world_rank() * num_threads_per_proc();
	}

	GEN_GETTER_BY_VAL(world_rank)
	GEN_GETTER_BY_VAL(world_size)
	GEN_GETTER_BY_VAL(num_threads_per_proc)
	GEN_GETTER_BY_VAL(min_world_size)

protected:		// functions
	template<typename... arg_types>
	inline void _quit_with_misc_output(arg_types&&... args) const {
		if (world_rank() == root) {
			show_misc_output(args...);

			//static constexpr int dummy = 9'001;
			static constexpr int dummy = 9001;

			for (int i=root + 1; i<world_size(); ++i) {
				send_single(dummy, i);
			}
		} else { // if (world_rank() != root)
			int to_recv = -1;

			recv_single(to_recv, root);
		}

		_regular_abort(ErrorCode::DidQuitWithMiscOutput);
	}

	inline int _raw_init(int& argc, char**& argv) const {
		return MPI_Init(&argc, &argv);
	}

	inline int _raw_comm_rank(MPI_Comm comm) const {
		int temp_world_rank;
		MPI_Comm_rank(comm, &temp_world_rank);
		return temp_world_rank;
	}
	inline int _raw_comm_size(MPI_Comm comm) const {
		int temp_world_size;
		MPI_Comm_size(comm, &temp_world_size);
		return temp_world_size;
	}
	inline int _raw_abort(MPI_Comm comm, int ec) const {
		return MPI_Abort(comm, ec);
	}
	inline int _regular_abort(const ErrorCode& ec) const {
		return _raw_abort(MPI_COMM_WORLD, static_cast<int>(ec));
	}

	inline int _raw_finalize() const {
		return MPI_Finalize();
	}

	template<typename T>
	inline int _wrapped_send(
		const T* buf, int num_instances, int dst, int tag, MPI_Comm comm
	) const {
		return MPI_Send(buf, num_instances * sizeof(T), MPI_BYTE, dst,
			tag, comm);
	}
	template<typename T>
	inline int _wrapped_recv(
		T* buf, int num_instances, int src, int tag, MPI_Comm comm,
		MPI_Status* status
	) const {
		return MPI_Recv(buf, num_instances * sizeof(T), MPI_BYTE, src,
			tag, comm, status);
	}
	template<typename T>
	inline int _wrapped_send_recv(
		const T* send_buf, int num_send_instances, int dst, int send_tag,
		T* recv_buf, int num_recv_instances, int src, int recv_tag,
		MPI_Comm comm, MPI_Status* status
	) const {
		return MPI_Sendrecv(send_buf, num_send_instances * sizeof(T),
			MPI_BYTE, dst, send_tag, recv_buf,
			num_recv_instances * sizeof(T), MPI_BYTE, src, recv_tag,
			comm, status);
	}

	GEN_SETTER_BY_VAL(world_rank);
	GEN_SETTER_BY_VAL(world_size);
	GEN_SETTER_BY_VAL(num_threads_per_proc);
	GEN_SETTER_BY_VAL(min_world_size);
};

#undef MPI_HANDLER_STATIC_ASSERT_0
#undef MPI_HANDLER_STATIC_ASSERT_1

} // namespace mpi

} // namespace liborangepower


#endif		// liborangepower_mpi_handler_class_hpp
