// https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html
/* Don't use [] to set values, possibly resulting in no pushup
 * No overlapping key value allowed
 * basics: begin(), end(), size(), empty(), clear(), find(const Key)
 *         lower_bound(const Key), upper_bound(const Key), erase(iterator)
 *         erase(const Key), insert(const pair<Key, Info>)
 * other:  void join(tree &other) move all elements in other to *this, key values overlapping not allowed
 *         void split(const_key_reference r_key, tree &other)
 *
 *         set the last parameter to tree_order_statistics_node_update to have the fonctonalities:
 *         find_by_order(size_type order) order counts from 0
 *         order_of_key(const_key_reference r_key)
 *
 *      	 set the second parameter to null_type so to get a set
 *
 *         b_tree_tag can be replaced by splay_tree_tag, ov_tree_tag
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> pii;
struct Info {
	int va, sm, si;
	Info(int va, int sm=0, int si=0): va(va), sm(sm), si(si) {}
};

template<class CIterator, class Iterator, class Cmp, class Alloc> struct MyUtil {
	typedef int metadata_type;
	virtual CIterator node_begin() const = 0;
	virtual CIterator node_end() const = 0;
	inline int GetSm(CIterator it) { return it == node_end()?0:(*it)->second.sm; }
	inline int GetSi(CIterator it) { return it == node_end()?0:(*it)->second.si; }
	void operator()(Iterator it, CIterator end_it) { // here is the pushup
		Info &no = (*it)->second;
		no.sm = no.va + GetSm(it.get_l_child()) + GetSm(it.get_r_child());
		no.si = 1 + GetSi(it.get_l_child()) + GetSi(it.get_r_child());
	}

	pii Query(int val) {
		CIterator it = node_begin();
		int sm = 0, si = 0;
		while(it != node_end()) {
			if ((*it)->first < val) {
				sm += GetSm(it.get_l_child())+(*it)->second.va;
				si += GetSi(it.get_l_child())+1;
				it = it.get_r_child();
			} else {
				it = it.get_l_child();
			}
		}
		return pii(sm, si);
	}
};
typedef tree<int, Info, less<int>, rb_tree_tag, MyUtil> RBT;
typedef pair<int, Info> piI;

int main(void) {
	RBT tr;
	int n;
	scanf("%d", &n);
	for(int i=1, x;i<=n;++i) {
		scanf("%d", &x);
		tr.insert(piI(x, Info(x)));
		printf("%d\n", tr.Query(1e9).first);
	}
	for(RBT::iterator it = tr.begin(); it!=tr.end(); ++it) {
		printf("%d %d\n", it->first, it->second.si);
	}
	return 0;
}
