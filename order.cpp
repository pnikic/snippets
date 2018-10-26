#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T, class Key>
using ordered_map = tree<T, Key, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  ordered_set<int> s;
  s.find_by_order(4); // vrati iterator na 4. element ili s.end() ako nema
  s.order_of_key(5); // vrati index lower_bounda od vrijednosti 5
}
