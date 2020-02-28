# HZOJ(海贼ＯＪ)    
#### - 1.火车进站------()
#### - ２.最大矩形面积------(单调栈)　　
#### - ３.括号画家------()　　
#### - 4.表达式计算------()  
#### - 5.数据结构------(对顶栈)(前缀和)
---
#### 1.火车进站
##### 题目描述
​ 有 n 列火车按 1 到 n 的顺序从东方左转进站，这个车站是南北方向的，它虽然无限长，只可惜是一个死胡同，而且站台只有一条股道，火车只能倒着从西方出去，而且每列火车必须进站，先进后出。

​ 现在请你按字典序输出前 20 种可能的出栈方案。  
  
##### 输入  
​ 输入一行一个整数 n。（n≤20）  
##### 输出  
​ 按字典序输出前 20 种答案，每行一种，不要空格。  

##### 样例输入  
3  
##### 样例输出  
123  
132  
213  
231  
321  

```
#include<iostream>
using namespace std;
#include<stack>
#include<algorithm>
#define MAX_N 20

int arr[MAX_N+5];

bool val_stack(int *arr,int n){
	stack<int >s;
	int temp=0;
	for(int i=0;i<n;i++){
		while(temp<arr[i]) s.push(++temp);
		if(s.top()-arr[i]) return false;
		s.pop();
	}
	return true;
}

int main(){
	int n,cnt=20;
	cin>>n;
	for(int i=0;i<n;i++){
		arr[i]=i+1;
	}
	do{
		if(val_stack(arr,n)){
			for(int i=0;i<n;i++){
				cout<<arr[i];
			}
			cout<<endl;
			cnt--;
		}
	}while(next_permutation(arr,arr+n) && cnt);
	return 0;
}

```

----  
#### ２.最大矩形面积
##### 题目描述
​ 给定从左到右多个矩形，已知这此矩形的宽度都为 1，长度不完全相等。这些矩形相连排成一排，求在这些矩形包括的范围内能得到的面积最大的矩形，打印出该面积。所求矩形可以横跨多个矩形，但不能超出原有矩形所确定的范围。  

##### 输入  
​ 输入共一行，第一个数表示矩形的个数 NN。接下来 NN 个数表示矩形的大小.（1≤N≤100000）    
##### 输出  
​ 输出最大矩形面积 。  

##### 样例输入  
7  
2 1 4 5 1 3 3  
##### 样例输出  
8  

```
/* o(n) ----单调栈维护ｎ个元素　　每个循环ｏ(n)  3  O(n)
 　　维护单调递增
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;
#define MAX_N 100000

long long arr[MAX_N + 5];
long long l[MAX_N + 5], r[MAX_N + 5];

int main() {
    int n;

    stack<int> s;//声明了1个存储int型元素的栈，栈名是s。

    cin >> n;
    arr[0] = arr[n + 1] = -1;//添加收尾
    for (int i = 1; i <= n; i++) cin >> arr[i];
	//------------zuo
    s.push(0);
    for (int i = 1; i <= n; i++) {
        while (arr[s.top()] >= arr[i]) s.pop();
        l[i] = i - s.top();//zuoqie
        s.push(i);
    }
	//-------------qingkong zhan
    while (!s.empty()) s.pop();
	//------------you
    s.push(n + 1);
    for (int i = n; i >= 1; i--) {
        while (arr[s.top()] >= arr[i]) s.pop();
        r[i] = s.top() - i;//youqie
        s.push(i);
    }
//-----------
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, arr[i] * (r[i] + l[i] - 1));//  ====
    }
    cout << ans << endl;
    return 0;
}

```

----

####  ３.括号画家　　

##### 题目描述
​ Candela 是一名漫画家，她有一个奇特的爱好，就是在纸上画括号。这一天，刚刚起床的 Candela 画了一排括号序列，其中包含小括号 ()、中括号 [] 和大括号 {}，总长度为 N。这排随意绘制的括号序列显得杂乱无章，于是 Candela 定义了什么样的括号序列是美观的：

 1. 空的括号序列是美观的；  
 2. 若括号序列 `A` 是美观的，则括号序列 `(A)、[A]、{A}` 也是美观的；  
 3. 若括号序列 `A、B` 都是美观的，则括号序列 `AB` 也是美观的；  
例如 [(){}]() 是美观的括号序列，而 )({)[}]( 则不是。  

现在 CandelaCandela 想在她绘制的括号序列中，找出其中连续的一段，满足这段子序列是美观的，并且长度尽量大。你能帮帮她吗？  

##### 输入  
​ 1 个长度为 N的括号序列。(5≤N≤10000)  
##### 输出  
​ 一个整数，表示最长的美观的连续子序列的长度。  

##### 样例输入  
[[[[]]{}]]  
##### 样例输出  
10  

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAX_N 100000

int pos[MAX_N +5];
char s[MAX_N+5], f[MAX_N+5]; 
int ans=0;
int main() {
	scanf("%s", s);
	int n = strlen(s);
	int p = 0;
	int h_data;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(')
			f[++p] = ')', pos[p] = i;
		else if (s[i] == '[')
			f[++p] = ']', pos[p] = i;
		else if (s[i] == '{')
			f[++p] = '}', pos[p] = i;
		else {
			if (p && s[i] == f[p]) {
				int c_data = i - pos[p] + 1;
				if (p == 1) {
					ans = max(ans, h_data + c_data);
					h_data += c_data; 
				}
				else
					ans = max(ans, c_data);
				p--;
			}
			else h_data = p = 0;
		}
	}
	cout << ans << endl;
}
```

----

　
####  4.表达式计算 
##### 题目描述
​ 给出一个表达式,其中运算符仅包含 +,-,*,/,^ 要求求出表达式的最终值。  

​ 数据可能会出现括号情况，还有可能出现多余括号情况；  

​ 数据保证不会出现大于 max long int 的数据；  

​ 数据可能会出现负数情况，幂次不可能为负数，除法采用向 00 取整。  

​ 注意：−9 和 +9 分别代表负数和正数的 9  
##### 输入
​ 共一行，即为表达式。表达式长度不会超过1000.  

##### 输出  
​ 共一行，既为表达式算出的结果。  

##### 样例输入  
(2+2)^(1+1)  
##### 样例输出  
16  


```
// Author: ShakeCloud
// 递归法求值
#include <cstdio>
#include <cctype>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
stack<char> opt;stack<int> num;
string s;
int stat,i,cnt;

// inline bool isopt(char c)
// {
// 	return !('0'<=c&&c<='9')&&c!='('&&c!=')';
// }

int solve(int l,int r)
{
	if(l>r) return 0;
	stat=0;
	for(int i=r;i>=l;--i) 
	{
		if(s[i]=='(') --stat;if(s[i]==')') ++stat;
		if(!stat&&(s[i]=='+'||s[i]=='-'))
		{
			int v1=solve(l,i-1),v2=solve(i+1,r);
			if(s[i]=='-') v2*=-1;
			return v1+v2;
		};
	};
	stat=0;
	for(int i=r;i>=l;--i) 
	{
		if(s[i]=='(') --stat;if(s[i]==')') ++stat;
		if(!stat&&(s[i]=='*'||s[i]=='/'))
		{
			int v1=solve(l,i-1),v2=solve(i+1,r);
			if(s[i]=='*') v1*=v2; else v1/=v2;
			return v1;
		};
	};
	stat=0;
	for(int i=r;i>=l;--i) 
	{
		if(s[i]=='(') --stat;if(s[i]==')') ++stat;
		if(!stat&&s[i]=='^')
		{
			int v1=solve(l,i-1),v2=solve(i+1,r);
			int ret=1;while(v2--) ret*=v1;
			return ret;
		};
	};
	if(s[l]=='('&&s[r]==')') return solve(l+1,r-1);
	int ret=0;
	for(int i=l;i<=r;++i) {ret=ret*10+s[i]-'0';};
	return ret;
}
int main()
{
	cin >> s;
	for(i=0;i<=s.length()&&s[i]==')';++i);s.erase(s.begin(),s.begin()+i);
	for(i=s.length()-1;i>=0&&s[i]=='(';--i);s.erase(s.begin()+i+1,s.end());
	for(i=0;i<s.length();++i) 
		{if(s[i]=='(') ++stat;if(s[i]==')') --stat;};
	// printf("stat=%d\n",stat);
	if(stat>0) 
		for(i=0,cnt=0;cnt<stat&&i<s.length();++i) 
			if(s[i]=='(') {s.erase(s.begin()+i);--i;++cnt;};
	if(stat<0)
	{
		stat*=-1;
		for(i=0,cnt=0;cnt<stat&&i<s.length();++i) 
			if(s[s.length()-i-1]==')') {s.erase(s.length()-i-1);++cnt;--i;};
	};
	printf("%d\n",solve(0,s.length()-1));
	return 0;
}

```

---  
#### 5.数据结构
#####  题目描述
创建一种结构，完成下列五种功能：  

I x在当前位置插入 x 元素；    
D 删除当前位置的元素；  
L 将当前位置左移一位，除非它已经是第一个元素；  
R 将当前位置右移一位，除非它已经是最后一个元素；  
Q k 在当前位置之前，找到一个最大的 Si(1≤i≤k,Si=a1+a2+...+ai)  
##### 输入  
​ 输入第一行为操作数 N。  

​ 接下来每行一种操作，当操作为 Q 时，输出 Si。  

​ 计算过程中所有数字不会超过 long long 表示范围  

##### 输出  
​ 对于每次 Q 操作，输出一行一个数 Si。

样例输入  
8  
I 2  
I -1  
I 1  
Q 3  
L  
D  
R  
Q 2  
样例输出  
2  
3  

```
#include<iostream>
using namespace std;
#include<algorithm>
#include<climits>
#define MAX_N 1000000
#include<stack>
#include<cstdio>

int stack_l[MAX_N+5],top_l;
int stack_r[MAX_N+5],top_r;
int sum_l[MAX_N+5],MAX_i[MAX_N+5];

void push_left(int x){
	stack_l[++top_l]=x;
	sum_l[top_l]=sum_l[top_l-1]+x;
	MAX_i[top_l]=max(MAX_i[top_l-1],sum_l[top_l]);
}


int main(){
	int n;
	scanf("%d",&n);
	MAX_i[0]=INT_MIN;
	while(n--){
		char str[2];
		int x;
		scanf("%s",str);
		if(str[0]=='I'){
			scanf("%d",&x);
			push_left(x);
			}
		else if(str[0]=='D'){
			if(top_l>0)
				top_l--;
		}
		else if(str[0]=='L'){
			if(top_l>0)
				stack_r[++top_r]=stack_l[top_l--];
		}
		else if(str[0]=='R'){
			if(top_r>0) 
				push_left(stack_r[top_r--]);
		}
		else{
			scanf("%d",&x);
			printf("%d\n",MAX_i[x]);
		}
	}
	return 0;
}
```

----
