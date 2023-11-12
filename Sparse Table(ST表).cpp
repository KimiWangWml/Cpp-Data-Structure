//st表，即sparse table，稀疏表。作用是：解决静态RMQ(Range Min/Max Query)问题，即区间最值的查询。

//1.暴力遍历：
int m, l, r;
int find(int l, int r){
     int mx = -INF;
     for (int i = l; i <= r; ++ i) mx = max(mx, a[i]);
     return mx;
}
while (m --){//m次查询
    cin >> l >> r;//每次查询给出区间范围
    cout << find(l, r) << '\n';//输出区间范围内的最值
}
//会TLE

//2.动态规划(Dynamic Programming)
//任何一个x∈N  由于任意一个正整数x都可以表示为：
//∵x =2^a0 + 2^a1 +......+2^ak
/*∴重新定义f[i] [j]，新的f[i] [j]数组表示
f[i] [j] 表示从 i 开始，长度为2 j 2^j2 
j的区间最大值。
这个区间为 [i, i + 2^j - 1]
*//*给定任意区间[l, r]都有，len = r - l + 1;
假设len的长度为 ：[——————————]
核心：我们需要算出最大的、2的指数长度的、能将区间完全覆盖的两段
这里不加证明地给出，每一段长度 k = log2len; 有
len[-——————————]
 k [——————]
​      k [———————]
​因为2的指数长度的每一段我们都算了一遍，所以st表中存了这两段的最值，所以，将这两段最值再取一个最值即可得到[l, r]区间的最值,
​即max{a[l]~a[ r]} = max(f[l] [k], f[r-(2 k 2^k2 k)+1] [k]), 其中第二项f[r-(2 k 2^k2 k)+1] [k]，r-2 k 2^k2 
k+1是从末尾r往前数2 k 2^k2k位得到的起点.*/

//ST模板：
const int N = 100010;
int f[N][17];
int a[N], n, m;//n个数，存于a[N]中，m个询问
void ST_init(){
    for (int i = 1; i <= n; ++ i;) f[i][0] = a[i];
    for (int j = 1; (1<<j) <= n; ++ j){
        for (int i = 1; i + (1<<j) - 1 <= n; ++ i)
            f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
    }
    return;
}
int find_ST(int l, int r){
    int k = log(r-l+1)/log2;
    return max(f[l][k], f[r-(1<<k)+1][k]);
}
int main(){
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    ST_init();
    int l, r;
    while (n --){
        cin >> l >> r;
        cout << find_ST(l, r) << '\n';
    } 
    system("pause");
    return 0;
}
//luogu p3865
