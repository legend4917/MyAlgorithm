## LCS - Longest Common Substring

题目链接：[http://www.spoj.com/problems/LCS/](http://www.spoj.com/problems/LCS/)

### 描述
A string is finite sequence of characters over a non-empty finite set Σ.

In this problem, Σ is the set of lowercase letters.

Substring, also called factor, is a consecutive sequence of characters occurrences at least once in a string.

Now your task is simple, for two given strings, find the length of the longest common substring of them.

Here common substring means a substring of two or more strings.

### 输入
The input contains exactly two lines, each line consists of no more than 250000 lowercase letters, representing a string.

### 输出
The length of the longest common substring. If such string doesn't exist, print "0" instead.

### 例子
```
Input:
alsdfkjfjkdsal
fdjskalajfkdsla

Output:
3
```

### 分析
对其中一个字符串构造SAM，然后将另一个字符串在SAM上运行即可，每次读取一个字符x，若p->next[x]存在，则匹配长度len+1，否则，跳转到其父节点p=p->fa，直到p->next[x]存在，此时len=p->maxlen+1，重复此过程，直到待匹配串运行结束，最大的len即为所求。

### 代码
```C++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int CHAR = 27;    // 字符串中不同字符的数量
const int MAXN = 250010;

struct SAM_Node {
    SAM_Node *fa, *next[CHAR];
    int maxlen;     // 节点表示的字符串后缀的最大长度
    int id,pos;     // 节点编号
    bool flag;      // 节点是否包含最长后缀（根据题目需要确定是否保存此变量）
    SAM_Node(){}
    SAM_Node(int _maxlen) {
        fa = 0;
        maxlen = _maxlen;
        memset(next,0,sizeof(next));
    }
};

SAM_Node SAM_node[MAXN*2], *SAM_root, *SAM_last;
SAM_Node *topsam[MAXN*2];
int topocnt[MAXN];
int SAM_size;
int endpos[MAXN];

SAM_Node *newSAM_Node(int maxlen) {
    SAM_node[SAM_size] = SAM_Node(maxlen);
    SAM_node[SAM_size].id = SAM_size;
    SAM_node[SAM_size].flag = true;
    return &SAM_node[SAM_size++];
}

SAM_Node *newSAM_Node(SAM_Node *p) {
    SAM_node[SAM_size] = *p;
    SAM_node[SAM_size].id = SAM_size;
    SAM_node[SAM_size].flag = false;
    return &SAM_node[SAM_size++];
}

void SAM_init() {
    SAM_size = 0;
    SAM_root = SAM_last = newSAM_Node(0);
    SAM_node[0].pos = 0;
}

void SAM_add(int x, int maxlen) {
    SAM_Node *p = SAM_last, *np = newSAM_Node(p->maxlen+1); 
    np->pos = maxlen;
    SAM_last = np;
    for (; p && !p->next[x]; p = p->fa)
        p->next[x] = np;
    if (!p) {
        np->fa = SAM_root;
        return;
    }
    SAM_Node *q = p->next[x]; 
    if (q->maxlen == p->maxlen + 1) {
        np->fa = q; 
        return; 
    }
    SAM_Node *nq = newSAM_Node(q);
    nq->maxlen = p->maxlen + 1;
    q->fa = nq;
    np->fa = nq;
    for (; p && p->next[x] == q; p = p->fa)
        p->next[x] = nq;
}

// 单个串构造SAM
void SAM_build(string s) {
    SAM_init();
    int len = s.length(); 
    for (int i = 0; i < len; ++i)
        SAM_add(s[i]-'a', i+1);
}

int main() {
    string str, s;
    cin >> str >> s;
    SAM_build(str);
    int lcs = 0, ans = 0;
    SAM_Node *p = SAM_root;
    for (int i = 0; i < s.length(); ++i) {
    	int x = s[i] - 'a';
    	if (p->next[x]) {	// 匹配成功
    		++lcs;
    		p = p->next[x];
    	} else {
    		while (p && !p->next[x]) p = p->fa;
    		if (!p) {
    			p = SAM_root;
    			lcs = 0;
    		} else {
    			lcs = p->maxlen + 1;
    			p = p->next[x];
    		}
    	}
    	ans = max(ans, lcs);
    }
    cout << ans << endl;
    return 0;
}
```