namespace trees {
    namespace functor {
        template <typename T> struct max { T operator()(T a, T b) const { return std::max(a, b); } };
        template <typename T> struct min { T operator()(T a, T b) const { return std::min(a, b); } };
    }
    template <typename T = i64, typename Func = plus<T>>
    struct GenericSegmentTree {
        T identity = T();
        struct Node {
            T val;
            Node() = default;
            Node(T val) : val(val) {}
            Node operator + (Node other) {
                return Node( Func()(val, other.val) );
            }
        };
 
    public:
        i32 n; vector<Node> segtree;
        GenericSegmentTree(i32 n, T identity = T()) :
            identity(identity), n(n), segtree( 4 * n, Node( identity ) ) {}
        GenericSegmentTree(vector<T>& arr, T identity = T()) : 
            identity(identity), n(arr.size()), segtree( 4 * arr.size(), Node( identity ) ) { buildTree(arr, 0, 0, n - 1); }
 
    private:
        void buildTree(vector<T>& arr, i32 root, i32 left, i32 right) {
            if (left == right) {
                segtree[root] = Node( arr[left] );
                return;
            }
            i32 mid = left + (right - left) / 2;
            buildTree(arr, 2 * root + 1, left, mid);
            buildTree(arr, 2 * root + 2, mid + 1, right);
            segtree[root] = segtree[2 * root + 1] + segtree[2 * root + 2];
        }
 
        Node query(i32 root, i32 left, i32 right, i32 queryLeft, i32 queryRight) {
            if (queryLeft <= left && right <= queryRight)
                return segtree[root];
            i32 mid = left + (right - left) / 2;
            Node result = Node( identity );
            if (queryLeft <= mid)
                result = result + query(2 * root + 1, left, mid, queryLeft, queryRight);
            if (queryRight > mid)
                result = result + query(2 * root + 2, mid + 1, right, queryLeft, queryRight);
            return result;
        }
 
        void update(i32 root, i32 left, i32 right, i32 index, T value) {
            if (left == right) {
                segtree[root] = Node( value );
                return;
            }
            i32 mid = left + (right - left) / 2;
            if (index <= mid)
                update(2 * root + 1, left, mid, index, value);
            else
                update(2 * root + 2, mid + 1, right, index, value);
            segtree[root] = segtree[2 * root + 1] + segtree[2 * root + 2];
        }
 
    public:
        T query(i32 left, i32 right) {
            return query(0, 0, n - 1, left, right).val;
        }
 
        void update(i32 index, T value) {
            update(0, 0, n - 1, index, value);
        }
    };
 
} using namespace trees;