## 求模的和

题目链接：[http://acm.seu.edu.cn/oj/problem.php?cid=1047&pid=2](http://acm.seu.edu.cn/oj/problem.php?cid=1047&pid=2)

### 描述
沈学姐写了一个神奇的计算器程序，其中只有一种运算，即输入n,m，输出m%1+m%2+...+m%n。但学姐并不确定程序是否正确，她想让你帮她对拍。注意结果可能很大，输出其对10^9+7取模即可。

### 输入
第一行一个整数T，表示有T组数据。

接下来T行：

每行为两个整数n,m。(1<=n,m<=10^9)

### 输出
对每组数据输出一行，形如”Case #i: ans”(不含引号)

ans为m%1+m%2+...+m%n的值。

### 分析
首先直接暴力求解肯定会超时，将原式转化为 **m % i = m - m / i \* i，其中 m/i\*i 是存在一定规律的**，以sqrt(m)为分界点，则有：

- 当 j < sqrt(m)，能将i划分为几个区间，每个区间分别对应 m / i == j；
- 当 j > sqrt(m)，直接暴力求解即可。

例如当 m = 100， n = 100时：

```
   i		  m / i
51 ~ 100		1
34 ~ 50			2
26 ~ 33			3
21 ~ 25			4
17 ~ 20			5
15 ~ 16			6
13 ~ 14			7
  12			8
  11			9
  10			10
\-------------------
  9				11
  8				12
  7				14
  6				16
  5				20
  4				25
  3				33
  2				50
  1				100
```

对于上面的例子，每一段都有相同的 m/i，因此可用求和公式快速求出对应段的和，加速计算过程。

### 代码
```C++
#include <iostream>
#include <cmath>
using namespace std;

typedef long long LL;
const LL MOD = 1e9 + 7;

int main() {
	LL m, n;
	cin >> m >> n;
	LL sum = 0, ans = m * n;
	LL sqrt_m = sqrt(m);
	LL j = m / n;
	LL high = n, low;
	for (; j <= sqrt_m; ++j) {
		low = m / (j + 1) + 1;
		cout << low << " " << high << endl;
		LL temp = (low + high) * (high - low + 1);
		sum = (sum + temp / 2 * j % MOD) % MOD;
		high = low - 1;
	}
	j = low == j - 1 ? sqrt_m - 1 : sqrt_m;
	for (; j > 0; --j) {
		cout << j << " " << m / j << endl;
		sum = (sum + j * (m / j) % MOD) % MOD;
	}
	ans = (ans - sum) % MOD;
	cout << ans << endl;
	return 0;
}
```