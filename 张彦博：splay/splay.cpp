#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define ll long long
#define N 100005
using namespace std;
int t , opt;
int sz = 0 , root = 0;
int ch[N][2] , f[N] , cnt[N] , key[N] , siz[N];
inline void clear( int x ) {
	ch[x][0] = ch[x][1] = f[x] = cnt[x] = key[x] = siz[x] = 0;
}
inline int get( int x ) {
	return ch[f[x]][1] == x;//0左1右 
}
inline void update( int x ) {
	if( x ) {
		siz[x] = cnt[x];
		if( ch[x][0] ) {
			siz[x] += siz[ch[x][0]];
		}
		if( ch[x][1] ) {
			siz[x] += siz[ch[x][1]];
		}
	}
	return;
}
inline void rotate( int x ) {
	int old = f[x] , oldf = f[old] , which = get( x );
	ch[old][which] = ch[x][which ^ 1];
	f[ch[old][which]] = old;
	ch[x][which ^ 1] = old;
	f[old] = x;
	f[x] = oldf;
	if( oldf ) {
		ch[oldf][ch[oldf][1] == old] = x;
	}
	update( old );
	update( x );
	return; 
}
inline void splay( int x ) {
	for ( int fa ; ( fa = f[x] ) ; rotate(x) ) {
		if( f[fa] ) {
			rotate( ( get( x ) == get( fa ) ? fa : x ) );
		}
	}
	root = x;
	return;
}
inline void insert( int v ) {
	if( root == 0 ) {
		++sz;
		root = sz;
		ch[root][0] = ch[root][1] = f[root] = 0;
		key[root] = v;
		cnt[root] = siz[root] = 1;
		return;
	}
	int cur = root , fa = 0;
	while ( true ) {
		if( key[cur] == v ) {
			++cnt[cur];
			update( cur );
			update( fa );
			splay( cur );//一边rotate，一边往上传值
			return; 
		}
		fa = cur;
		cur = ch[cur][key[cur] < v];
		if( cur == 0 ) {
			++sz;
			ch[sz][0] = ch[sz][1] = 0;
			key[sz] = v;
			siz[sz] = 1;
			cnt[sz] = 1;
			f[sz] = fa;
			ch[fa][key[fa] < v] = sz;
			update( fa );
			splay( sz );
			return;
		} 
	}
}
inline int find( int v ) {
	int ans = 0 , cur = root;
	while ( true ) {
		if( v < key[cur] ) {
			cur = ch[cur][0];
		} else {
			ans += ( ch[cur][0] ? siz[ch[cur][0]] : 0 );
			if( v == key[cur] ) {
				splay( cur );
				return ans + 1;
			}
			ans += cnt[cur];
			cur = ch[cur][1];
		}
	}
}
inline int findth( int k ) {
	int cur = root;
	while ( true ) {
		if( ch[cur][0] && k <= siz[ch[cur][0]] ) {
			cur = ch[cur][0];
		} else {
			int tem = ( ch[cur][0] ? siz[ch[cur][0]] : 0 ) + cnt[cur];
			if( k <= tem ) {
				return key[cur];
			}
			k -= tem;
			cur = ch[cur][1];
		}
	}
}
inline int pre() {
	int cur = ch[root][0];
	while ( ch[cur][1] ) {
		cur = ch[cur][1];
	}
	return cur;
}
inline int nxt() {
	int cur = ch[root][1];
	while ( ch[cur][0] ) {
		cur = ch[cur][0];
	}
	return cur;
}
inline void del( int v ) {
	find( v );
	if( cnt[root] > 1 ) {
		--cnt[root];
		update( root );
		return;
	}
	if( !ch[root][0] && !ch[root][1] ) {
		clear( root );
		root = 0;
		return;
	}
	if( !ch[root][0] ) {
		int oldroot = root;
		root = ch[root][1];
		f[root] = 0;
		clear( oldroot );
		return;
	} else if( !ch[root][1] ) {
		int oldroot = root;
		root = ch[root][0];
		f[root] = 0;
		clear( oldroot );
		return;
	}
	int lpre = pre() , oldroot = root;
	splay( lpre );
	f[ch[oldroot][1]] = root;
	ch[root][1] = ch[oldroot][1];
	clear( oldroot );
	update( root );
	return;
}
int main() {
    scanf("%d",&t);
    int x;
    while ( t-- ) {
    	scanf("%d",&opt);
    	switch( opt ) {
    		case 1 : {
    			scanf("%d",&x);
    			insert( x );
				break;
			}
			case 2 : {
				scanf("%d",&x);
    			del( x );
				break;
			}
			case 3 : {
				scanf("%d",&x);
				printf("%d\n",find( x ));
				break;
			}
			case 4 : {
				scanf("%d",&x);
				printf("%d\n",findth( x ));
				break;
			}
			case 5 : {
				scanf("%d",&x);
				insert( x );
				printf("%d\n",key[pre()]);
				del( x );
				break;
			}
			case 6 : {
				scanf("%d",&x);
				insert( x );
				printf("%d\n",key[nxt()]);
				del( x );
				break;
			}
		}
	}
    return 0;
}
