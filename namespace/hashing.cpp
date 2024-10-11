namespace hashing {
    constexpr i64 default_capacity = 512;
    constexpr double default_load_factor = 0.25;

    template<typename T> struct is_hash_struct : false_type {};
    template<typename K> struct is_hash_struct<unordered_set<K>> : true_type {};
    template<typename K> struct is_hash_struct<unordered_multiset<K>> : true_type {};
    template<typename K, typename V> struct is_hash_struct<unordered_map<K, V>> : true_type {};
    template<typename K, typename V> struct is_hash_struct<unordered_multimap<K, V>> : true_type {};
    template<typename K, typename H> struct is_hash_struct<unordered_set<K, H>> : true_type {};
    template<typename K, typename H> struct is_hash_struct<unordered_multiset<K, H>> : true_type {};
    template<typename K, typename V, typename H> struct is_hash_struct<unordered_map<K, V, H>> : true_type {};
    template<typename K, typename V, typename H> struct is_hash_struct<unordered_multimap<K, V, H>> : true_type {};

    template<typename HashStruct>
    typename enable_if<is_hash_struct<HashStruct>::value>::type 
    operator * (HashStruct& hashstruct) {
        hashstruct.reserve(default_capacity);
        hashstruct.max_load_factor(default_load_factor);
    }
    // Usage: unordered_map<i64, i64, _xor> hashmap; *hashmap;
} using namespace hashing;