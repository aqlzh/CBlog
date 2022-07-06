> 一研为定  !

@[toc]

# 高级第三次 直播  补码 浮点型IEEE754
## 补码
- 5   `0000 0101`   原码
- -5  `1111 1011`   补码   用补码来表示负数   `ff ff ff fb`


intel   CPU   是小端存储 （与我们人类习惯不相同）

- 关于原码反码补码的介绍  [请移步这里~](https://blog.csdn.net/QuantumYou/article/details/115084048)
##  整型型变量

- 整型变量的 6 种类型如下图
![在这里插入图片描述](https://img-blog.csdnimg.cn/8f82a568701f4bf29b7e95634e56a348.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUXVhbnR1bVlvdQ==,size_14,color_FFFFFF,t_70,g_se,x_16)

-  有符号基本整型与无符号基本整型的最高位所代表的意义如下图

![在这里插入图片描述](https://img-blog.csdnimg.cn/1ad6bd3de353407c9c1dd05d718c1029.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUXVhbnR1bVlvdQ==,size_20,color_FFFFFF,t_70,g_se,x_16)
- 不同整型变量表示的整型数的范围
![在这里插入图片描述](https://img-blog.csdnimg.cn/c4752576b1b549fbab17db99200d5ae9.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUXVhbnR1bVlvdQ==,size_20,color_FFFFFF,t_70,g_se,x_16)
2^31^ 的原因    `0111 1111 1111 1111 1111 1111 1111 1111`   的等比数列的求和  (2^0^ 加到 2^30^)    
$S_n$ = $a_1(1-q^n)/1-q$   


![在这里插入图片描述](https://img-blog.csdnimg.cn/51dbe2fef50c4842b6cfbd8193a2dbce.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUXVhbnR1bVlvdQ==,size_20,color_FFFFFF,t_70,g_se,x_16)

```cpp
#include <stdio.h>
#include <stdlib.h>


// long long  32bit 系统 8字节 ； 64 bit 系统 8字节 
int main() {

	int i=0;
	short a = 32767;
	short b = 0;
	long c=0;
	short d = 0;
	b = a + 1; // 发生溢出
	d = a + 2;
	printf("%d\n", b);
	printf("%d\n", d);
	return 0;
}
```

关于==无符号数==的使用

```cpp
unsigned short n = 0x8056 ;
short m =  0x8056 ; 
printf("%d\n",m) ;  //  32854  
printf("%d\n",b) ;  //  -32682
printf("%u\n",b) ;  // 32854
```

## 浮点型变量
- 浮点型数据的组成如下图  （SEM）

![在这里插入图片描述](https://img-blog.csdnimg.cn/a1cccdec2cae4c8a900f1ecc6898e4bd.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUXVhbnR1bVlvdQ==,size_13,color_FFFFFF,t_70,g_se,x_16)
- 浮点数的数值范围与有效数字
![在这里插入图片描述](https://img-blog.csdnimg.cn/2e479c8de12d4f9e8667d74c099c81e2.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUXVhbnR1bVlvdQ==,size_20,color_FFFFFF,t_70,g_se,x_16)
数值范围与有效数字的来源

2^8^ = 256  => 0--255   => -127 ~ 128 

=> 2 -127 次方    (5.8e-37)
=> 2  128 次方   （3.4e+38）


2^23^  =  8,388,608  (可以用6个9表示 ，但是不能使用7个9表示)


## 浮点数的原理解析
- IEEE 754  标准 浮点型变量存储标准

![在这里插入图片描述](https://img-blog.csdnimg.cn/85ae70db8bd74410a9117dba2b117f12.png)


  

# 高级第四次 直播   位运算

## 内存  精度  

- 自己手动实现，封装输出内存函数


```cpp
在这里插入代码片
```

精度丢失的情况

```cpp
#include  <stdio.h>

int main(){
   
   float a = 1.23456789e10 ; // 在赋值的一瞬间发生精度丢失
   flaot b ; 
   b = a+20 ; 
   printf("b=%f\n",b) ;
   return 0 ;
}
```

各种转义字符及其作用

![在这里插入图片描述](https://img-blog.csdnimg.cn/e172bacca27148a28333b917083a88d9.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUXVhbnR1bVlvdQ==,size_20,color_FFFFFF,t_70,g_se,x_16)

- 位运算符`<<、>>、~、|、^、&`依次是左移、右移、按位取反、按位或、按位异或、按位与。


**注意**：
- 关于移位操作，正数可能会移动成为负数，负数也可能移动成为正数（不是直接乘2 的场景）
- 被移位的数的值不发生改变



```cpp
#include  <stdio.h>

int main(){
   short i = 0x8011;
   short j ;
   j = i << 1;
   printf("j=%d\n",j) ;
   return 0 ;

}
```

## 位运算
<font color=red size=4>**左移**</font>：高位丢弃，低位补0,相当于乘以2。工作中很多时候申请内存时会用左移，例如要申请1GB大小的空间，可以使用 malloc(1<<30)   

<font color=red size=4>**右移**</font>：低位丢弃，正数的高位补0（无符号数我们认为是正数），负数的高位补1,相当于除以2。移位比乘法和除法的效率要高，负数右移，对偶数来说是除以2,但对奇数来说是先减1后除以2。例如，-8>>1,得到的是-4,但-7>>1得到的并不是-3而是-4。另外，对于-1来说，无论右移多少位，值永远为-1。

- 看内存显示 补 ffff  的原因 ： %x  ，默认按4个字节，全为 1的情况


