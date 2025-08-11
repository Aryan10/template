#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T, typename CMP = less<void>>
using ordered_set = tree<T, null_type, CMP, rb_tree_tag, tree_order_statistics_node_update>;
