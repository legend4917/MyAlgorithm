### 字符串shift操作

#### 题目
假设字符串为x为byebyebye，对字符串的shift操作定义如下：
shift(x,0) = byebyebye

shift(x,1) = yebyebyeb

shift(x,2) = byebyebye

现在给一个长度为n的字符串，不断进行上述shift操作，求shift操作前后字符串相等的次数，即：
shift(x,i) = shift(x, i+1)

#### 分析
需要求解对字符串进行最小粒度的划分，使得划分后的所有子串都相等，则shift操作前后字符串相等的次数就是字符串的长度除以这个子串的长度。
