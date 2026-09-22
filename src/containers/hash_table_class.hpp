#ifndef liborangepower_containers_hash_table_class_hpp
#define liborangepower_containers_hash_table_class_hpp

#include "std_hash_stuff.hpp"

//namespace liborangepower {
//namespace containers {
////--------
//template<typename KeyT, typename ValueT>
//class HashTable final {
//public:     // types
//    class Elem final {
//    public:     // variables
//        KeyT key;
//        ValueT v;
//    };
//public:     // constants
//    static constexpr size_t INITIAL_BUF_SIZE_LOG2 = size_t(
//        //8ul
//        //4ul
//        6ul
//    );
//private:     // variables
//    std::vector<std::vector<Elem>> _data_v2d;
//    size_t _most_inner_size = 0;
//public:     // functions
//    HashTable() {
//        _maybe_rehash();
//    }
//    HashTable(const HashTable& to_copy) {
//    }
//    //HashTable(HashTable&& to_move) {
//    //    
//    //}
//    ~HashTable() = default;
//
//    void insert(const KeyT& key, const ValueT& v) {
//    }
//
//private:        // functions
//    std::vector<Elem>& _vec_search_shared(
//        //const char* key
//        const KeyT& key
//    ) {
//        //if (some_htab == NULL) {
//        //    return NULL;
//        //}
//        if (_data_v2d.size() == 0) {
//            return nullptr;
//        }
//
//        //const size_t hash = _tiny_fs_str_hash(
//        //    key,
//        //    some_htab->vec_size_log2
//        //);
//        //tiny_fs_htab_vec_t* ret = some_htab->vec + hash;
//        const auto hash = std::hash(key)();
//        std::vector<Elem>* ret = &_data_v2d.at(
//            hash & (_data_v2d.size() - 1ull)
//        );
//        return ret;
//
//        //return ret;
//    }
//    ValueT* _search_shared(
//        //tiny_fs_htab_t* some_htab, const char* key
//        const KeyT& key
//    ) {
//        //if (some_htab == NULL) {
//        //    return NULL;
//        //}
//        if (_data_v2d.size() == 0) {
//            return nullptr;
//        }
//        //tiny_fs_htab_vec_t* vec = _tiny_fs_htab_vec_search_shared(
//        //    some_htab,
//        //    key
//        //);
//
//        std::vector<Elem>& vec = _vec_search_shared(key);
//
//        //for (size_t i=0; i<vec->buf_size; ++i) {
//        //    tiny_fs_htab_elem_t* item = vec->buf + i;
//        //    if (
//        //        item->key != NULL
//        //        && strcmp(item->key, key) == 0
//        //    ) {
//        //        return item->v;
//        //    }
//        //}
//        for (size_t i=0; i<vec.size(); ++i) {
//            Elem& item = vec.at(i);
//            if (item.key == key) {
//                return &item.v;
//            }
//        }
//        //return NULL;
//        return nullptr;
//    }
//    void _insert_shared(
//        //tiny_fs_htab_t* some_htab,
//        const KeyT& key,
//        const ValueT& v
//    ) {
//        //const size_t hash = _tiny_fs_str_hash
//        //tiny_fs_htab_vec_t* vec = _tiny_fs_htab_vec_search_shared(
//        //    some_htab,
//        //    key//,
//        //    //to_insert->filename
//        //);
//        auto& vec = _vec_search_shared(key);
//        //const size_t old_last_idx = vec->buf_size;
//        const size_t old_last_idx = vec.size();
//        //++vec->buf_size;
//        //if (vec->buf == NULL) {
//        //    vec->buf = calloc(
//        //        vec->buf_size,
//        //        sizeof(tiny_fs_htab_elem_t)
//        //    );
//        //} else {
//        //    vec->buf = realloc(
//        //        vec->buf,
//        //        sizeof(tiny_fs_htab_elem_t) * vec->buf_size
//        //    );
//        //}
//
//        vec.push_back(Elem{.key=key, .v=v});
//
//        if (_most_inner_size < vec.size()) {
//            _most_inner_size = vec.size();
//        }
//
//        //tiny_fs_htab_elem_t* temp = vec->buf + old_last_idx;
//        //temp->key = key;
//        //temp->v = to_insert;
//        //if (some_htab->most_inner_size < vec->buf_size) {
//        //    some_htab->most_inner_size = vec->buf_size;
//        //}
//    }
//    //void _insert_shared(const KeyT& key, const ValueT& v) {
//    //    
//    //}
//    void _maybe_rehash() {
//        if (
//            //tiny_fs_htab == NULL
//            _data_v2d.size() == size_t(0ul)
//        ) {
//            //tiny_fs_htab = (tiny_fs_htab_t*)calloc(
//            //    1ul,
//            //    sizeof(tiny_fs_htab_t)
//            //);
//            //tiny_fs_htab->vec_size_log2 = TINY_FS_HTAB_INITIAL_SIZE_LOG2;
//            //tiny_fs_htab->most_inner_size = (size_t)0u;
//
//            //tiny_fs_htab->vec = (
//            //    (tiny_fs_htab_vec_t*)calloc(
//            //        ((size_t)1ul) << tiny_fs_htab->vec_size_log2,
//            //        sizeof(tiny_fs_htab_vec_t)
//            //    )
//            //);
//            //_data_v2d.resize(size_t(1ul) << INITIAL_BUF_SIZE_LOG2);
//            _most_inner_size = 0ul;
//            static constexpr size_t my_new_buf_size = (
//                size_t(1ul) << INITIAL_BUF_SIZE_LOG2
//            );
//            for (size_t i=0ul; i<my_new_buf_size; ++i) {
//                _data_v2d.push_back(std::vector<Elem>());
//            }
//            return;
//        }
//
//        //const size_t prev_buf_size_log2 = tiny_fs_htab->vec_size_log2;
//        //const size_t prev_buf_size = ((size_t)1u) << prev_buf_size_log2;
//        const size_t prev_buf_size = _data_v2d.size();
//
//        if (
//            //tiny_fs_htab->most_inner_size > (prev_buf_size >> 1)
//            _most_inner_size > (prev_buf_size >> size_t(1ul))
//        ) {
//            // at this point we decide to rehash...
//            // maybe having (prev_buf_size / 2)
//            // is enough of a size to rehash the hash table?
//            // I don't know how well this will work in practice.
//            // It's admittedly an estimated guess as to something
//            // that might work somewhat well.
//
//            //const size_t next_buf_size_log2 = prev_buf_size_log2 + 1;
//            //const size_t next_buf_size = ((size_t)1u) << next_buf_size_log2;
//            const size_t next_buf_size = prev_buf_size << size_t(1ul);
//
//            //tiny_fs_htab_t* temp_htab = (tiny_fs_htab_t*)malloc(
//            //    // No need to zero-initialize the bytes this time.
//            //    // (i.e. no need for `calloc()` here.)
//            //    sizeof(tiny_fs_htab_t)
//            //);
//            //temp_htab->vec = (tiny_fs_htab_vec_t*)calloc(
//            //    next_buf_size,
//            //    sizeof(tiny_fs_htab_vec_t)
//            //);
//
//            HashTable temp_htab;
//            //temp_htab->vec_size_log2 = next_buf_size_log2;
//            ////temp_htab->most_inner_size = tiny_fs_htab->most_inner_size;
//            //temp_htab->most_inner_size = 0u;
//            for (size_t i=prev_buf_size; i<next_buf_size; ++i) {
//                temp_htab._data_v2d.push_back(std::vector<Elem>());
//            }
//
//            //for (size_t j=0; j<prev_buf_size; ++j) {
//            //    tiny_fs_htab_vec_t* temp_prev_vec = tiny_fs_htab->vec + j;
//            //    if (temp_prev_vec->buf_size > 0) {
//            //        for (size_t i=0; i<temp_prev_vec->buf_size; ++i) {
//            //            tiny_fs_htab_elem_t* item = temp_prev_vec->buf + i;
//            //            const char* key = item->key;
//            //            tiny_fs_file_t* to_insert = item->v;
//            //            _tiny_fs_htab_insert_shared(temp_htab, key, to_insert);
//            //        }
//            //        free(temp_prev_vec); 
//            //    }
//            //}
//            for (size_t j=0; j<prev_buf_size; ++j) {
//                std::vector<Elem>& temp_prev_vec = _data_v2d.at(j);
//                if (temp_prev_vec.size() > 0) {
//                    for (size_t i=0; i<temp_prev_vec.size(); ++i) {
//                        const Elem& item = temp_prev_vec.at(i);
//                        const KeyT& key = item.key;
//                        const ValueT& v = item.v;
//                        _insert_shared(key, v);
//                    }
//                    temp_prev_vec.resize(0);
//                }
//            }
//
//            //free(tiny_fs_htab);
//            //tiny_fs_htab = temp_htab;
//            *this = std::move(temp_htab);
//        }
//    }
//};
////--------
//} // namespace containers
//} // namespace liborangepower

#endif      // liborangepower_containers_hash_table_class_hpp
