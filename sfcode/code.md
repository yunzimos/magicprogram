[TOC]

# 代码

## 最大字段和之分治算法

#### Problem Description

 给定n(1<=n<=50000)个整数（可能为负数）组成的序列a[1],a[2],a[3],…,a[n],求该序列如a[i]+a[i+1]+…+a[j]的子段和的最大值。**当所给的整数均为[负数](http://baike.baidu.com/view/71543.htm)时定义子段和为0**，依此定义，所求的最优值为： Max{0,a[i]+a[i+1]+…+a[j]},1<=i<=j<=n。 例如，当（a[1],a[2],a[3],a[4],a[5],a[6]）=(-2,11,-4,13,-5,-2)时，最大子段和为20。

 

**注意：**本题目要求用分治递归法求解，除了需要输出最大子段和的值之外，还需要输出求得该结果所需的递归调用总次数。

#### Input

第一行输入整数n(1<=n<=50000)，表示整数序列中的数据元素个数；

第二行依次输入n个整数，对应顺序表中存放的每个数据元素值。

#### Output

一行输出两个整数，之间以空格间隔输出：

第一个整数为所求的最大子段和；

第二个整数为用分治递归法求解最大子段和时，递归函数被调用的总次数。

#### Sample Input

```
6
-2 11 -4 13 -5 -2
```

#### Sample Output

```
20 11
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int a[5000005]={0},c=0,sum=0;

int maxx(int l,int r)
{
    c++;
    if(l>r)return 0;
    if(l==r)
    {
        if(a[l]>0)return a[l];
        else return 0;
    }
    else
    {
        int mid=(l+r)/2;
        int lmax=maxx(l,mid);
        int rmax=maxx(mid+1,r);
        int s=0;
        for(int i=l;i<=r;i++)
        {
            if(s+a[i]>0)
            {
                s+=a[i];
                sum=max(sum,s);
            }
            else s=0;//！！！！！
        }
        sum=max(lmax,sum);
        sum=max(rmax,sum);
    }
    return sum;
}


int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<maxx(0,n-1)<<" "<<c<<endl;
    return 0;
}

```



## 骨牌铺方格

Problem Description
在2×n的一个长方形方格中,用一个1× 2的骨牌铺满方格,输入n ,输出铺放方案的总数.
例如n=3时,为2× 3方格，骨牌的铺放方案有三种,如下图：

![](/home/yunzimo/我的坚果云/notes/imagin/C40-1003-1.jpg)

Input
输入数据由多行组成，每行包含一个整数n,表示该测试实例的长方形方格的规格是2×n (0<n<=50)。


Output
对于每个测试实例，请输出铺放方案的总数，每个实例的输出占一行。


Sample Input
1 3 2

Sample Output
1 3 2

   只要简单的推断即可~
   假设用arr[i]表示2*i的方格一共有组成的方法数，我们知道arr[1]=1;arr[2]=2;
   现在假设我们已经知道了arr[i-1]和arr[i-2],求arr[i],所谓arr[i],不过是在2*（i-1）的格子后边加上一格2*1的方格罢了，骨牌在这一格上横着放，竖着放，如果前面i-1块已经铺好，则第i块只有一种铺法，就是竖着放，如果要横着放，也只有一种铺法，不过要求前面i-2块已经铺好！
 因此arr[i]=arr[i-1]+arr[i-2];

![](/home/yunzimo/我的坚果云/notes/imagin/1358854787_7564-1574426766895.png)

## 哈士奇

#### Problem Description

由于高数巨养的喵星人太傲娇了，要天天吃新鲜猫粮而且还经常欺负高数巨，所以高数巨决定买几条哈士奇尝尝鲜。这天高数巨来到了二手狗市场买哈士奇，高数巨看完了所有的哈士奇，记下了每条哈士奇的价格，并根据对它们的好感程度给它们每只都赋予了一个萌值。高数现在手里有X元，她想通过购买若干条哈士奇来获得尽可能多的萌值。现在给定高数巨手里的钱X以及N条哈士奇的价格和萌值，求高数巨最多可获得多少萌值

#### Input

 多组输入。

对于每组输入，第一行有两个整数N，X（1 < = N < = 100，1 < = X < = 1000），分别表示哈士奇的数量和高数巨的钱数

接下来的N行每行有两个整数Pi，Mi（1 < = Pi,Mi < = 100），分别表示第i条哈士奇的价格和萌值

#### Output

对于每组数据，输出一个整数，表示高数巨最多可以获得的萌值，每组输出占一行

#### Sample Input

```
2 100
50 20
60 40
3 100
20 55
20 35
90 95
1 10
20 50
```

#### Sample Output

```
40
95
0
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int main()
{
    int a[102];
    int b[102];
    int val[101][1001];
    int n,x;
    while(cin>>n>>x)
    {
        for(int i=1;i<=n;i++)
            cin>>a[i]>>b[i];
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=x;j++)
            {
                if(j>=a[i])//！！！注意限制条件
                {
                    val[i][j]=max(val[i-1][j],val[i-1][j-a[i]]+b[i]);
                }
                else val[i][j]=val[i-1][j];
            }
        }
        cout<<val[n][x]<<endl;
    }

    return 0;
}
```



## 01背包

#### 理解

| i（物品编号） |  1   |  2   |  3   |  4   |
| :-----------: | :--: | :--: | :--: | :--: |
|   w（体积）   |  2   |  3   |  4   |  5   |
|   v（价值）   |  3   |  4   |  5   |  6   |

**经过动态规划后建成的表如下图：**

![image-20191122224707073](/home/yunzimo/我的坚果云/notes/imagin/image-20191122224707073.png)

n表示物品个数，x表示容积，j表示列，i表示行。当容积达不到当前物品的体积时，val和上一个物品相同，当容积>=当前体积时，两个值，当前容积减去此物体的体积后加上他的价值，和不减体积和 不加价值的上一个物品的情况相比（箭头所指的是减去体积的val，加上本身的val如果大于上一个物品的情况就装）

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int val[101][1111]={0};
    int a[101],b[1111];
    int n,x;
    while(~scanf("%d %d",&n,&x))
    {
        for(int i=1;i<=n;i++)
        {
            cin>>a[i]>>b[i];
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<=x;j++)
            {
                if(j>=a[i])
                {
                    val[i][j]=max(val[i-1][j],val[i-1][j-a[i]]+b[i]);
                }
                else val[i][j]=val[i-1][j];
            }
        }
        cout<<val[n][x]<<endl;
    }



    return 0;
}

```

## 最少硬币问题

#### Problem Description

 			设有n种不同面值的硬币，各硬币的面值存于数组T[1:n]中。现要用这些面值的硬币来找钱。可以使用的各种面值的硬币个数存于数组Coins[1:n]中。
 对任意钱数0≤m≤20001，设计一个用最少硬币找钱m的方法。
 对于给定的1≤n≤10，硬币面值数组T和可以使用的各种面值的硬币个数数组Coins，以及钱数m，0≤m≤20001，计算找钱m的最少硬币数。				

#### Input

 			输入数据第一行中只有1个整数给出n的值,第2行起每行2个数，分别是T[j]和Coins[j]。最后1行是要找的钱数m。				

#### Output

 			输出数据只有一个整数，表示计算出的最少硬币数。问题无解时输出-1。				

#### Sample Input

```
3
1 3
2 3
5 3
18
```

#### Sample Output

```
5
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
int dp[20020];

int main()
{
    int n,m;
    int t[20],coin[20020];
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>t[i]>>coin[i];//t=value  coin=num
    }
    cin>>m;
    for(int i=1;i<=m;i++)dp[i]=INF;//initconfig
    for(int i=1;i<=n;i++)//coin kind
    {
        for(int j=1;j<=coin[i];j++)//coin num
        {
            for(int k=m;k>=t[i];k--)//coin value
                dp[k]=min(dp[k],dp[k-t[i]]+1);
        }
    }
    cout<<(dp[m]<m?dp[m]:-1)<<endl;
    return 0;
}

```

## 数字三角问题

#### Problem Description

给定一个由n行数字组成的数字三角形如下图所示。试设计一个算法，计算出从三角形的顶至底的一条路径，使该路径经过的数字总和最大。
![](/home/yunzimo/我的坚果云/notes/imagin/1730.png)
对于给定的由n行数字组成的数字三角形，计算从三角形的顶至底的路径经过的数字和的最大值。

#### Input

输入数据的第1行是数字三角形的行数n，1≤n≤100。接下来n行是数字三角形各行中的数字。所有数字在0..99之间。

#### Output

输出数据只有一个整数，表示计算出的最大值。

#### Sample Input

```
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
```

#### Sample Output

```
30
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f


int main()
{
    int n,a[101][101],pre[101][101];
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
            cin>>a[i][j];
    }
    for(int i=1;i<=n;i++)pre[n][i]=a[n][i];
    for(int i=n-1;i>=1;i--)
    {
        for(int j=1;j<=i;j++)
        {
            pre[i][j]=a[i][j]+max(pre[i+1][j],pre[i+1][j+1]);
        }
    }
    cout<<pre[1][1]<<endl;
    return 0;
}
```



## 石子合并问题

#### Problem Description

在一个圆形操场的四周摆放着n堆石子。现要将石子有次序地合并成一堆。规定每次只能选相邻的2 堆石子合并成新的一堆，并将新的一堆石子数记为该次合并的得分。试设计一个算法，计算出将n堆石子合并成一堆的最小得分和最大得分。
对于给定n堆石子,计算合并成一堆的最小得分和最大得分。

#### Input

输入数据的第1行是正整数n，1≤n≤100，表示有n堆石子。第二行有n个数，分别表示每堆石子的个数。

#### Output

输出数据有两行，第1行中的数是最小得分，第2行中的数是最大得分。

#### Sample Input

```
4
4 4 5 9
```

#### Sample Output

```
43
54
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
int n,m;
int a[110];
int sum[110];
int dp_min[110][110],dp_max[110][110];
int main()
{

    cin>>n;
    //initconfig
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=n+1;i<=n*2;i++)
    {
        a[i]=a[i-n];
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=n*2-1;i>0;i--)
    {
        for(int j=i+1;j<=i+n;j++)
        {
            dp_min[i][j]=INF;
            for(int k=i;k<=j-1;k++)
            {
                dp_min[i][j]=min(dp_min[i][j],dp_min[i][k]+dp_min[k+1][j]+sum[j]-sum[i-1]);
                dp_max[i][j]=max(dp_max[i][j],dp_max[i][k]+dp_max[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    int ans_min=INF;
    int ans_max=0;
    for(int i=1;i<=n;i++)
    {
        ans_max=max(dp_max[i][i+n-1],ans_max);
        ans_min=min(dp_min[i][i+n-1],ans_min);

    }
    cout<<ans_min<<endl;
    cout<<ans_max<<endl;
    return 0;
}


```

## 最长公共子序列

#### Problem Description

给定两个序列 X={x1,x2,…,xm} 和 Y={y1,y2,…,yn}，找出X和Y的最长公共子序列。

#### Input

输入数据有多组，每组有两行 ，每行为一个长度不超过500的字符串（输入全是大写英文字母（A,Z）），表示序列X和Y。

#### Output

每组输出一行，表示所求得的最长公共子序列的长度，若不存在公共子序列，则输出0。

#### Sample Input

```
ABCBDAB
BDCABA
```

#### Sample Output

```
4
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int dp[510][510];

int gg(char *a,char *b,int len1,int len2)
{
    for(int i=1;i<=len1;i++)
    {
        for(int j=1;j<=len2;j++)
        {
            if(a[i-1]==b[j-1])dp[i][j]=dp[i-1][j-1]+1;//不能做预先操作，只能对现有数据进行操作
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[len1][len2];
}

int main()
{
    char a[510],b[510];
    while(~scanf("%s %s",a,b))
    {
        int len1=strlen(a);
        int len2=strlen(b);
        dp[510][510]={0};
        int tmp=gg(a,b,len1,len2);
        cout<<tmp<<endl;
    }
    return 0;
}
```

## 子集和问题

#### Problem Description

子集和问题的一个实例为〈S,t〉。其中，S={ x1 ， x2 ，…，xn }是一个正整数的集合，c是一个正整数。子集和问题判定是否存在S的一个子集S1，使得：
![img](https://acm.sdut.edu.cn/image/1764.png)。
试设计一个解子集和问题的回溯法。
对于给定的正整数的集合S={ x1 ， x2 ，…，xn }和正整数c，计算S 的一个子集S1，使得：
![img](https://acm.sdut.edu.cn/image/1764.png)。

#### Input

输入数据的第1 行有2 个正整数n 和c（n≤10000，c≤10000000），n 表示S 的大小，c是子集和的目标值。接下来的1 行中，有n个正整数，表示集合S中的元素。

#### Output

将子集和问题的解输出。当问题无解时，输出“No Solution!”。

#### Sample Input

```
5 10
2 2 6 5 4
```

#### Sample Output

```
2 2 6
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int n,c,a[10050],x[10050],rest,sum=0;

bool track(int t)
{
    rest-=a[t];
    if(sum==c)return true;
    if(t>n)return false;
    if(sum+a[t]<=c)
    {
        x[t]=1;
        sum+=a[t];
        if(track(t+1))return true;
        sum-=a[t];
    }
    if(sum+rest>=c)
    {
        x[t]=0;
        if(track(t+1))return true;
    }
    rest+=a[t];
    return false;

}

int main()
{
    cin>>n>>c;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        rest+=a[i];
    }
    if(!track(1))cout<<"No Solution!"<<endl;
    else
    {
        for(int i=1;i<=n;i++)
        {
            if(x[i]==1)cout<<a[i]<<" ";

        }
        cout<<endl;
    }
    return 0;
}
```



## 工作分配问题

#### Problem Description

设有n件工作分配给n个人。将工作i分配给第j个人所需的费用为 cij。试设计一个算法，为每一个人都分配1 件不同的工作，并使总费用达到最小。
设计一个算法，对于给定的工作费用，计算最佳工作分配方案，使总费用达到最小。

#### Input

输入数据的第一行有1 个正整数n (1≤n≤20)。接下来的n行，每行n个数，表示工作费用。

#### Output

将计算出的最小总费用输出。

#### Sample Input

```
3
10 2 3
2 3 4
3 4 5
```

#### Sample Output

```
9
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

int n,a[22][22],ans,vis[22];

void dfs(int i,int s)
{
//    if(s>ans)return;
//    if(i==n+1&&s<ans)
//    {
//        ans=s;
//        return;
//    }
    if(s>ans)return;
    if(i>n)
    {
        ans=min(ans,s);
        return;
    }
    for(int j=1;j<=n;j++)
    {
        if(!vis[j])
        {
            vis[j]=1;
            dfs(i+1,s+a[i][j]);
            vis[j]=0;
        }
    }
}


int main()
{
    //ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    }
    ans=INF;
    dfs(1,0);
    cout<<ans<<endl;
    return 0;
}

```

## 运动员最佳匹配

#### Problem Description

羽毛球队有男女运动员各n 人。给定2 个n×n 矩阵P 和Q。P[i][j]是男运动员i 和女运动员j配对组成混合双打的男运动员竞赛优势；Q[i][j]是女运动员i和男运动员j配合的女运动员竞赛优势。由于技术配合和心理状态等各种因素影响，P[i][j]不一定等于Q[j][i]。男运动员i和女运动员j配对组成混合双打的男女双方竞赛优势为P[i][j]*Q[j][i]。
设计一个算法，计算男女运动员最佳配对法，使各组男女双方竞赛优势的总和达到最大。
设计一个算法，对于给定的男女运动员竞赛优势，计算男女运动员最佳配对法，使各组男女双方竞赛优势的总和达到最大。

#### Input

输入数据的第一行有1 个正整数n (1≤n≤20)。接下来的2n 行，每行n个数。前n行是p，后n行是q。

#### Output

将计算出的男女双方竞赛优势的总和的最大值输出。

#### Sample Input

```
3
10 2 3
2 3 4
3 4 5
2 2 2
3 5 3
4 5 1
```

#### Sample Output

```
52
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//#define INF 0x3f3f3f3f

int n,a[22][22],b[22][22],ans,vis[22],c[22][22],pre[22];

void dfs(int i,int s)
{
    if(i>n)
    {
        ans=max(ans,s);
        return;
    }
    if(s+pre[n]-pre[i-1]<ans)return;//必须加这一行不然超时
    for(int j=1;j<=n;j++)
    {
        if(!vis[j])
        {
            vis[j]=1;
            dfs(i+1,s+c[i][j]);
            vis[j]=0;
        }
    }
}


int main()
{

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cin>>b[i][j];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            {
                c[i][j]=a[i][j]*b[j][i];
                pre[i]=max(pre[i],c[i][j]);
            }
            pre[i]+=pre[i-1];
    }
    ans=0;
    dfs(1,0);
    cout<<ans<<endl;
    return 0;
}


```

## 整数变换问题

#### Problem Description

整数变换问题。关于整数i的变换f和g定义如下：f(i)=3i；![img](https://acm.sdut.edu.cn/image/1771.png)
试设计一个算法，对于给定的2 个整数n和m，用最少的f和g变换次数将n变换为m。例如，可以将整数15用4 次变换将它变换为整数4：4=gfgg(15)。当整数n不可能变换为整数m时，算法应如何处理?
对任意给定的整数n和m，计算将整数n变换为整数m所需要的最少变换次数。

#### Input

输入数据的第一行有2 个正整数n和m。n≤100000，m≤1000000000。

#### Output

将计算出的最少变换次数以及相应的变换序列输出。第一行是最少变换次数。第2 行是相应的变换序列。

#### Sample Input

```
15 4
```

#### Sample Output

```
4
gfgg
```

#### code

```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int n,m,k;
int x[55],bestx[55];
bool found=false;
int f(int i,int n)
{
    if(i==1)return n*3;
    else return n/2;
}

bool track(int dep,int n)
{
    if(dep>k)return false;
    else
    {
        for(int i=1;i<=2;i++)
        {
            int tmp=f(i,n);
            x[dep]=i;
            if(tmp==m||track(dep+1,tmp))
            {
                found=true;
                for(int j=1;j<=k;j++)
                {
                    bestx[j]=x[j];
                }
                return true;
            }
            x[dep]=0;//回溯
        }

    }
    return false;//没找到返回false
}


void search()
{
    k=1;
    while(!track(1,n))
    {
        k++;
        memset(x,0,sizeof(x));
        memset(bestx,0,sizeof(bestx));
    }
}


int main()
{
    cin>>n>>m;
    search();
    if(found)
    {
        cout<<k<<endl;
        for(int i=k;i>=1;i--)
        {
            if(bestx[i]==1)cout<<'f';
            else cout<<'g';
        }
    }
    else cout<<"Failed!"<<endl;
    return 0;
}


```

