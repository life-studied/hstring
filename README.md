# hstring

## 介绍

​	一个使用kmp算法和内存池来代替C++string类。在大量长字符串的程序中使用，性能有显著提升。

## 接口

### 函数接口

* `find()`：从一个hstring中查找另一个hstring，返回开始下标。
* `swap()`：交换两个hstring。
* `size()`: 返回字符的数量。
* `empty()`: 检查字符串是否为空。
* `clear()`: 清除字符串中的所有字符。
* `c_str()`: 返回以C风格的字符串表示的`const char*`指针。

### 符号重载

* `[]`运算符
* `+`运算符
* `==`运算符
* `!=`运算符
* `>`运算符
* `<`运算符
* `<<`运算符（标准输出流）
* `>>`运算符（标准输入流）

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
	const char* ptr = "f";

	size_t res{};
	if ((res = hstr.find(ptr)) != hstring::npos)
		cout <<"index is: " << res << endl;
	else
		cout << "could not find the index" << endl;
	return 0;
}
```

