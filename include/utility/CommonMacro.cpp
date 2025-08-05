#define all(v) begin(v),end(v)
#define sz(v) (static_cast<int>((v).size()))

#define modulo(x, y) ((((x) % (y)) + (y)) % (y))

#define MAX(x, y) (x < y ? y : x)
#define MIN(x, y) (x < y ? x : y)
#define MAXEQ(x, y) (x < y ? y = x, true : false)
#define MINEQ(x, y) (x < y ? false : y = x, true)
template <typename T> T max(vector<T> const& v) { return *max_element(v.begin(), v.end()); }
template <typename T> T min(vector<T> const& v) { return *min_element(v.begin(), v.end()); }

#define PrefixSum(ps, v) vector<long long> ps(v.size() + 1, 0); for (int i = 1; i <= v.size(); i++) ps[i] = ps[i-1] + v[i-1];
#define FreqMap(mp, v) map<decltype(v)::value_type, int> mp; for (auto i : v) mp[i]++;
#define IndexMap(mp, v) map<decltype(v)::value_type, vector<int>> mp; for (int i = 0; i < v.size(); i++) mp[v[i]].push_back(i);

;