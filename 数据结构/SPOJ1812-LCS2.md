## SPOJ1812-LCS2

题目链接：[http://www.spoj.com/problems/LCS2/](http://www.spoj.com/problems/LCS2/)

### 描述
A string is finite sequence of characters over a non-empty finite set Σ.

In this problem, Σ is the set of lowercase letters.

Substring, also called factor, is a consecutive sequence of characters occurrences at least once in a string.

Now your task is a bit harder, for some given strings, find the length of the longest common substring of them.

Here common substring means a substring of two or more strings.

### 输入
The input contains at most 10 lines, each line consists of no more than 100000 lowercase letters, representing a string.

### 输出
The length of the longest common substring. If such string doesn't exist, print "0" instead.

### 样例
```
Input:
alsdfkjfjkdsal
fdjskalajfkdsla
aaaajfaaaa

Output:
2
```

### 分析
这题是求两个串的公共子串的扩展，需要求多个长的最长公共子串，同样我们对其中一个串建立SAM，然后分别将其它所有的串都在该SAM上运行，不同的是，在构造SAM的过程中，我们在每个节点出添加了两个数据成员：

- ma：保存对接下来运行的某一个串，该节点所能匹配的当前串的最大长度的子串；
- mi：保存对接下来运行的所有的串，该节点所能匹配的最小的公共子串。

有了上面的两个数据成员，我们在每次运行完一个串后，需要对每个节点所能匹配的最大长度的子串长度向其父节点更新，因为每次匹配的时候只更新了当前状态的ma，而实际上其父节点也能匹配该子串（最长不能大于该父节点的最大子串长度），但是并未更新，后面在匹配其它串时，可能在该父节点处需要更新ma值，这样就无法保存更新后的ma值了，因此我们需要在每个串运行结束后，都要对SAM的节点向上更新ma值。更新后在对每个节点求mi值，即匹配到当前串后，每个节点所能匹配的最长公共子串。

所有串运行结束后，所有节点中的mi最大值即为所求。

### 代码
```C++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int CHAR = 26;    // 字符串中不同字符的数量
const int MAXN = 100010;

struct SAM_Node {
    SAM_Node *fa, *next[CHAR];
    int maxlen;     // 节点表示的字符串后缀的最大长度
    int id, pos;     // 节点编号
    int mi, ma;		// 添加两个数据成员
    bool flag;      // 节点是否包含最长后缀（根据题目需要确定是否保存此变量）
    SAM_Node(){}
    SAM_Node(int _maxlen) {
        fa = 0;
        ma = 0;
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
    np->mi = maxlen;
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
    nq->mi = nq->maxlen;
    q->fa = nq;
    np->fa = nq;
    for (; p && p->next[x] == q; p = p->fa)
        p->next[x] = nq;
}

void SAM_topoSort(int n) {  // 拓扑排序
    memset(topocnt, 0, sizeof(topocnt));
    for (int i = 0; i < SAM_size; ++i)
        ++topocnt[SAM_node[i].maxlen];
    for (int i = 1; i <= n; ++i)
        topocnt[i] += topocnt[i-1];
    for (int i = 0; i<SAM_size; ++i)
        topsam[--topocnt[SAM_node[i].maxlen]] = &SAM_node[i];
}

// 单个串构造SAM
void SAM_build(char s[]) {
    SAM_init();
    int len = strlen(s); 
    for (int i = 0; i < len; ++i)
        SAM_add(s[i]-'a', i+1);
}

int main() {
    char str[MAXN];
    char s[MAXN];
    scanf("%s", str);
    SAM_build(str);
    SAM_topoSort(strlen(str));
    while (~scanf("%s",s)) {
        int lcs = 0, len = strlen(s);
        SAM_Node *p = SAM_root;
        for (int i = 0; i < len; ++i) {
            int x = s[i] - 'a';
            if (p->next[x]) {
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
            if (p->ma < lcs)
                p->ma = lcs;
        }
        for (int i = SAM_size - 1; i >= 0; --i) {  // 向上更新
            p = topsam[i];
            if (p->ma < p->mi)
                p->mi = p->ma;
            if (p->fa && p->fa->ma < p->ma)
                p->fa->ma = min(p->fa->maxlen, p->ma); // 更新时注意该节点最长匹配长度不能超过本身的maxlen
            p->ma = 0;
        }
    }
    int ans = 0;
    for (int i = 0; i < SAM_size; ++i)
        ans = max(ans, SAM_node[i].mi);
    cout << ans << endl;
    return 0;
}
```