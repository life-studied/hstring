# hstring

## 介绍

​	一个使用kmp算法和内存池来代替C++string类。在大量长字符串的程序中使用，性能有显著提升。

## 接口

### 函数接口

* c_str：返回原始C-style字符串
* find：从一个hstring中查找另一个hstring，返回开始下标
* swap：交换两个hstring

### 符号重载

* 加号：允许两个hstring相加
* 左移：允许使用标准输出，打印hstring
* 右移：允许使用标准输入，输入字符串
* 等于：拷贝构造函数

## 使用案例

```C++
#include"hstring.h"
#include<string>
using namespace m_hstring;
using namespace std;
int main()
{
	
	hstring hstr = "fhdskljagfhaslkfdjvbnapoisrefhasd;lnvcsfd;jghk12432uy4132947895y3wqieuh980723qy54rhure3w";
	cout << hstr << endl;
	const char* ptr = "12432";
	cout<<hstr.find(ptr);
	//
	return 0;
}
```

