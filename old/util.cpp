namespace util {
    /* ============== Debug/Stress Test ============== */
    #ifndef ONLINE_JUDGE
        #include "__debug__.hpp"
    #else
        #define debug(...)
        #define DEBUG(...)
    #endif
    #ifdef STRESS_TEST
        #include "__test__.hpp"
    #else
        namespace test {
            void generate();
            void generator();
            void bruteforce();
            void validate();
            #define gout cerr // generator output stream 
            #define bout cerr // brute forcer output stream
        };
    #endif

    /* ============== Input-Output ============== */
    char _ostream_seperater = ' ';
    struct seperate { char _; seperate(char _ = '\n') : _(_) {} };
    ostream& operator << (ostream& os, seperate _ ) { _ostream_seperater = _._; return os; }
    template <typename K, typename V> istream& operator >> (istream& is, pair<K, V>& p) { return is >> p.first >> p.second; }
    template <typename K, typename V> ostream& operator << (ostream& os, pair<K, V> const& p) { return os << p.first << ' ' << p.second << ' '; }
    template <typename T> istream& operator >> (istream& is, vector<T>& v) { for (T& i : v) is >> i; return is; }
    template <typename T> ostream& operator << (ostream& os, vector<T> const& v) { for (T const& i : v) os << i << _ostream_seperater; return os; }

    /* ============== Common Utilities ============== */
    #define modulo(x, y) ((((x) % (y)) + (y)) % (y))
    #define MAX(x, y) (x < y ? y : x)
    #define MIN(x, y) (x < y ? x : y)
    #define MAXEQ(x, y) (x < y ? y = x, true : false)
    #define MINEQ(x, y) (x < y ? false : y = x, true)
    template <typename T> T max(vector<T> const& v) { return *max_element(v.begin(), v.end()); }
    template <typename T> T min(vector<T> const& v) { return *min_element(v.begin(), v.end()); }
    #define PrefixSum(ps, v) vector<i64> ps(v.size() + 1, 0); for (i32 i = 1; i <= v.size(); i++) ps[i] = ps[i-1] + v[i-1];
    #define FreqMap(mp, v) map<decltype(v)::value_type, i32> mp; for (auto i : v) mp[i]++;
    #define IndexMap(mp, v) map<decltype(v)::value_type, vector<i32>> mp; for (i32 i = 0; i < v.size(); i++) mp[v[i]].push_back(i);

    // Rolls random 32 bit unsigned integer
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    struct _xor {
        size_t operator()(uint64_t x) const {
            static const uint64_t LOCK = rng();
            return x ^ LOCK;
        }
    };

    // GNU PBDS -> methods: order_of_key, find_by_order
    template<class T, class CMP = less<T>> using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, CMP, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
    template<class T, class CMP = less_equal<T>> using ordered_multiset = __gnu_pbds::tree<T, __gnu_pbds::null_type, CMP, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
    #define multi_erase(s, i) s.erase(s.upper_bound(i));
    #define multi_lower_bound(s, i) s.upper_bound(i)
    #define multi_upper_bound(s, i) s.lower_bound(i)
    template<class T, class V, class CMP = less<T>> using ordered_map = __gnu_pbds::tree<T, V, CMP, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
    
    template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
    template<class T> using max_heap = priority_queue<T, vector<T>>;
} using namespace util;