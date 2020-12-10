## string
### input
* scanf
  ```cpp
  #include <iostream>
  using namespace std;
  main ()
  {
    string s;
    s.resize(3);//the length of buffer
    scanf("%s",&s[0]);
    cout<<s<<1;
    /*
    input1: abcde
    output1: abc1

    input2: a bcde
    output2: a  1
    */
  }
  ```
* cin
  * input a number
  ```cpp
  #include <iostream>
  using namespace std;
  main ()
  {
    int a,b;
    cin>>a>>b;
    cout<<a+b<<endl;
  }
  ```
  * input a string, stop with a space or CR
  ```cpp
  #include <iostream>
  using namespace std;
  main ()
  {
    char a[20];
    cin>>a;
    cout<<a<<endl;
  }
  /*
  input:abc de
  output:abc
  */
  ```
* cin.get()
  * input a character
  ```cpp
  #include <iostream>
  using namespace std;
  main ()
  {
    char ch;
    ch=cin.get(); //or cin.get(ch)
    cout<<ch<<endl;
  }
  /*
  input：jljkljkl
  output：j
  */
  ```
  * input certain number of characters
  ```cpp
  #include <iostream>
  using namespace std;
  main ()
  {
    char a[20];
    cin.get(a,20); //有些类似getline。可以输入多个单词，中间空格隔开。
    cout<<a<<endl;
  }
  /*
  input1：jkl jkl jkl
  output1：jkl jkl jkl

  input2：abcdeabcdeabcdeabcdeabcde （输入25个字符）
  output2：abcdeabcdeabcdeabcd （接收19个字符+1个'\0'）
  */
  ```
* cin.getline(), it can get space
  ```cpp
  #include <iostream>
  using namespace std;
  main ()
  {
  char m[20];
  cin.getline(m,5); //与上面基本相同。
  cout<<m<<endl;
  }
  /*
  输入：jkljkljkl
  输出：jklj

  接受5个字符到m中，其中最后一个为'\0'，所以只看到4个字符输出；

  如果把5改成20：
  输入：jkljkljkl
  输出：jkljkljkl

  输入：jklf fjlsjf fjsdklf
  输出：jklf fjlsjf fjsdklf

  延伸：
  cin.getline()实际上有三个参数，cin.getline(接受字符串到m,接受个数5,结束字符)
  当第三个参数省略时，系统默认为'\0' 是‘/n’吧。
  如果将例子中cin.getline()改为cin.getline(m,5,'a');当输入jlkjkljkl时输出jklj，输入jkaljkljkl时，输出jk
  */
  ```

* getline(); it takes a string as input including space
  ```cpp
  #include<iostream>
  #include<string>
  using namespace std;
  main ()
  {
    string str;
    getline(cin,str);
    cout<<str<<endl;
  }
  ```
* get();it takes a string as input including space
  ```cpp
  #include<iostream>
  #include<string>
  using namespace std;
  main ()
  {
  char m[20];
  gets(m); //wrong:m=gets();
  cout<<m<<endl;
  }
  ```
  [Reference](https://blog.csdn.net/ahzz123/article/details/70495617)

### output
* printf; a time-saving way
  ```cpp
  #include<iostream>
  using namespce std;
  main(){
    string s="asdf";
    printf("%s",s.c_str());
  }
  ```

### int2string string2int
* int2string:
  ```cpp
  string str=to_string(12);
  ```
* string2int 
  ```cpp
    int stoi (const string&  str, size_t* idx = 0, int base = 10)//base:radix
    int dec=stoi("10",nullptr,10);//#include<string>
  ```
  [Reference](https://blog.csdn.net/u010510020/article/details/73799996)

### find()
```cpp
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s1 = "first second third";
    string s2 = "second";
    int index = s1.find(s2,5);//s2 is the substring we want to find, 5 means it starts at 5. The default value is 0.
    if(index < s1.length())
        cout<<"Found at index : "<< index <<endl;
    else
        cout<<"Not found"<<endl;
    return 0;
}
// output Found at index 6, if not found, the index will be very big(4294967295)
```

### lower and upper the case of characters
* tolower(char c),toupper(char c)
  ```cpp
  main(){
    char a='a';
    char b='B';
    a=toupper(a);//a='A'
    b=tolower(b);//b='b'
  }
  ```
* transform
  ```cpp
  #include<iostream>
  #include<algorithm> //transform
  #include<string>
  using namespace std;
  main(){
    string s="ABCDE";
    transform(s.begin(),s.end(),s.begin(),::tolower);
    // s="abcde";
  }
  ```

### substr()
```cpp
#include<iostream>
using namespace std;
int main(){
  string s="abcdefg";
  s=s.substr(1);//s="bcdefg"
  s=s.substr(2,3);//s="def"
  //2 is the start index, 3 is the length of substr we want
}
```
### reverse()
```cpp
#include<algorithm>//reverse
main{
  string s="hello";
  reverse(s.begin(),s.end());//s="olleh"
}
```
### push_back(char c)
```cpp
#include<iostream>
using namespace std;
int main()
{
	string s1 = "1";
	s1.push_back('2');
	cout<<s1<<endl;
}//12
```

## STL
### vector
```cpp
  #include <iostream>
  #include <vector>  //使用vector需要包含此头文件
  using namespace std;
  template <class T>
  void PrintVector(const vector <T> & v)
  {  //用于输出vector容器的全部元素的函数模板
      typename vector <T>::const_iterator i;
      //typename 用来说明 vector <T>::const_iterator 是一个类型，在 Visual Studio 中不写也可以
      for (i = v.begin(); i != v.end(); ++i)
          cout << *i << " ";
      cout << endl;
  }
  int main()
  {
      int a[5] = { 1, 2, 3, 4, 5 };
      vector <int> v(a, a + 5);  //将数组a的内容放入v
      cout << "1) " << v.end() - v.begin() << endl;  //两个随机迭代器可以相减，输出：1)5
      cout << "2)"; PrintVector(v);  //输出：2)1 2 3 4 5
      v.insert(v.begin() + 2, 13);  //在 begin()+2 位置插人 13
      cout << "3)"; PrintVector(v);  //输出：3)1 2 13 3 4 5
      v.erase(v.begin() + 2);  //删除位于 begin()+2 位置的元素
      cout << "4)"; PrintVector(v);  //输出：4)1 2 3 4 5
      vector<int> v2(4, 100);  //v2 有 4 个元素，都是 100
      v2.insert(v2.begin(), v.begin() + 1, v.begin() + 3);  //将v的一段插入v2开头
      cout << "5)v2:"; PrintVector(v2);  //输出：5)v2:2 3 100 100 100 100
      v.erase(v.begin() + 1, v.begin() + 3);  //删除 v 上的一个区间，即 [2,3)
      cout << "6)"; PrintVector(v);  //输出：6)1 4 5
      int len=10;
      vector<int> vv[len]//长度为10的vector数组，每个元素是一个存储int的vector
      return 0;
  }
```
* push_back
  ```cpp
  #include<vector>
  vector<int> v1,v2;
  v1.push_back(10);
  v2.push_back(100);
  ```
* insert
  ```cpp
  a.insert(v1.end(),v2.begin(),v2.end());//concat v1 and v2
  ```
* size,capacity
  ```cpp
  vector<int> primes {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
  cout<<"The size is "<<primes.size()<<endl;
  cout<<"The capacity is "<<primes.capacity()<<endl;
  //The size and capacity of ***primes*** are both 15
  ```
  ```cpp
  primes.push_back(53);
  //the size of primes is 16,and the capacity might be 30 depending on the algorithm implementation, which may double the capacity.
  ```

* clear
  ```cpp
  primes.clear();
  //size=0,capacity=30
  ```
* swap
  ```cpp
  vector<int> ().swap(primes);
  //size=0,capacity=0
  ```
  [Reference](http://c.biancheng.net/view/348.html)
* find
  
  vector dones't have find() itself, but we can use the find() in algorithm
  ```cpp
  #include<algorithm>
  using namespace std;
  int main(){
    vector<int> v;
    v.push_back(1);
    if(find(v.begin(),v.end(),1)==v.end()) printf("no 1 in vector");
  }
  ```
  
### set //元素自动升序排序存储
* insert
  ```cpp
  #include<set>
  using namespace std;
  main(){
    set<int> st {1,2,3,4};
    st.insert(5);
    //st.size()=5
    st.insert(1);
    //st.size()=5
  }
  ```
* clear and erase
  ```cpp
  #include<set>
  using namespace std;
  main(){
    set<int> st {1,2,3,4};
    st.erase(1);
    //st.size=3
    st.clear();
    //st.size=0
  }
  ```
* find
  ```cpp
  #include<set>
  #include<iostream>
  using namespace std;
  main(){
    set<int> st {1,2,3,4};
    st.find(3);//会返回指向3的迭代器
    st.find(100);//会返回st.end()
    //判断一个元素是否在set中
    if(st.find(x)!=st.end()) printf("x is in set");
    else printf("x is not in set");
  }
  ```

### map
* iterator find(key)
    ```cpp
    #include<map>
    using namespace std;
    int main(){
      map<string,int> mymap {{"aa",1},{"bb",2}};
      if(mymap.find("cc")==mymap.end()) printf("Not Found");
    }
    ```
* count
  ```cpp
    #include<map>
    using namespace std;
    int main(){
      map<string,int> mymap {{"aa",1},{"bb",2}};
      if(mymap.count("cc")==0) printf("Not Found");
    }
    ```
* iterate
```cpp
    #include<map>
    using namespace std;
    int main(){
      map<string,int> mymap {{"aa",1},{"bb",2}};
      map<string,int>::iterator it=mymap.begin();// auto it=mymap.begin()
      while(it!=mymap.end()){
        printf("%d ",it->second);
        it++;
      }
    }
```

### stack
```cpp
#include<iostream>
#include<stack>
using namespace std;
int main(){
  stack<int> s;
  s.push(1);
  s.pop();
  if(!s.empty()) cout<<s.top();
}
```
### queue
```cpp
#include<iostream>
#include<queue>
using namespace std;
main(){
  queue<int> q;
  q.push(1);
  int a=q.front();//the first element
  a=q.back();//the last element
  q.pop();//pop out the first element
  int len = q.size();//the number of element in queue
  bool is_empty=q.empty();
}
```



## algorithm
### count
```cpp
#include<iostream>  
#include<vector>
#include<algorithm>  
using namespace std;  

int main()  
{  
    string s="1 2 3 4";
    cout<<count(s.begin(),s.end(),' ');// count=3
    vector<int> v={1,2,3,4,5};
    cout<<count(v.begin(),v.end(),1);// count=1
    return 0;  
}  
```
### fill()
```cpp
#include<algorithm>
using namespace std;
int main(){
  int a[10];
  fill(a,a+10,1);// a={1,1,1,1,1,1,1,1,1,1}
  int b[10][10];
  fill(b[0],b[0]+10*10,1);
  vector<int> v(8);// 0 0 0 0 0 0 0 0 
  fill(v.begin(),v.begin()+3,5);// 5 5 5 0 0 0 0 0 
}
```
### upper_bound() and lower_bound()
```cpp
#include<algorithm>
#include<iostream>
using namespace std;
int main(){
  int a[10]={0,1,3,3,4,4,4,5,6,7};
  int p=upper_bound(a,a+10,4)-a;//p=7,a[p]=5
  p=lower_bound(a,a+10,4)-a;//p=4,a[p]=4

  p=upper_bound(a,a+10,2)-a;//p=2,a[p]=3
  p=lower_bound(a,a+10,2)-a;//p=2,a[p]=3

  p=upper_bound(a,a+10,-1)-a;//p=0,a[p]=0
  p=lower_bound(a,a+10,-1)-a;//p=0,a[p]=0

  p=upper_bound(a,a+10,20)-a;//p=10
  p=lower_bound(a,a+10,20)-a;//p=10

  // upper_bound and lower_bound are both for inserting a number into a orderly sequence and still keep it in order. 
  //The difference is lower_bound find the smallest index to insert, the upper_bound find the biggest.

  // if we want to insert into sequence in reversed order, we can still use these two functions
  int b[5]={5,4,3,2,1};
  p=upper_bound(b,b+5,4,greater<int>())-b;//p=2
  p=lower_bound(b,b+5,4,greater<int>())-b;//p=1
}
```

## other tips
### isalnum(char c)
>judge whether ***c*** is a alphabet or number

### 左边补0
```cpp
#include<iostream>//setw,setfill
#include<iomanip>
using namespace std;
int main(){
int a=6;
cout << setw(3) << setfill('0') << a << endl;//006
cout << a << endl;//6
printf("%03d",a)//006
return 0;
}
```
### default value
* The default values of a boolean array in c++ are undefined. Depending on the compiler, it may be set to *false*.

### accumulate()
```cpp
#include<numeric>//accumulate
using namespace std;

int main(){
  int a={1,2,3,4,5}
  int sum=accumulate(a,a+5,0);//sum=1+2+3+4+5+0
  vector<int> v={1,2,3,4,5};
  sum=accumulate(v.begin(),v.end(),0);//sum=1+2+3+4+5+0
}
```