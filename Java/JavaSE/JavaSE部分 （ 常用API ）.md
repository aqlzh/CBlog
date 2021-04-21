# JavaSE部分 （ 常用API ）
*写在前面：分享技术，共同进步，把之前写的笔记搬运至博客，*有不足请见谅*，*相关意见可评论告知***ヾ(•ω•`)o
> 编程路漫漫，学习无止尽！

、
@[toc]
## 匿名对象
### 概念
匿名对象就是只有右边的对象，没有左边的名字和赋值运算符。
eg ：new 类名称();

 - 注意事项：匿名对象只能使用唯一的一次，下次再用不得不再创建一个新对象。
 - 使用建议：如果确定有一个对象只需要使用唯一的一次，就可以用匿名对象。
 
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200705163631981.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 应用

 1. 匿名对象与Scanner
 2. 匿名对象传参
 3. 匿名对象作为返回值
 

```java
package fill;

import java.util.Scanner;

public class Anonymous_02 {
    public static void main(String[] args) {
        // 常规Scanner使用
//        Scanner sc = new Scanner(System.in);
//        System.out.println("请输入数字");
//        int num = sc.nextInt();
//        System.out.println("输入的数字是"+num);
        // 匿名对象
//        int num = new Scanner(System.in).nextInt();
//       System.out.println("输入的数字是"+num);


      //常规写法传参
//        Scanner sc = new Scanner(System.in);
//        methodParam(sc);
        //匿名传参
//        methodParam(new Scanner(System.in));


        // 匿名对象作为返回值
        Scanner sc = methodReturn();
        int num = sc.nextInt() ;
        System.out.println("输入的是"+num);

    }

    public static void methodParam(Scanner sc){
        int num = sc.nextInt();
        System.out.println("输入的数字是"+num);
    }

    public static Scanner methodReturn(){
        // 常规
//        Scanner sc = new Scanner(System.in);
//        return  sc ;

        // 匿名对象作为返回值
        return  new Scanner(System.in) ;
    }

}

```
## 常用API
### Random(生成随机数)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200705200601485.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
注意：可以带参数，带参数代表范围，其为左闭右开区间（类似于数组）

```java
int num = r.nextInt(10);  //0~9
```
变式：输出1~n的随机数

```java
int num = r.nextInt(10)+1;
```
### 对象数组
数组有一个缺点：一旦创建，程序运行期间长度不可以发生改变。
```java
package cn.itcast.day07.demo04;

/*
题目：
定义一个数组，用来存储3个Person对象。

数组有一个缺点：一旦创建，程序运行期间长度不可以发生改变。
 */
public class Demo01Array {

    public static void main(String[] args) {
        // 首先创建一个长度为3的数组，里面用来存放Person类型的对象
        Person[] array = new Person[3];

        Person one = new Person("迪丽热巴", 18);
        Person two = new Person("古力娜扎", 28);
        Person three = new Person("玛尔扎哈", 38);

        // 将one当中的地址值赋值到数组的0号元素位置
        array[0] = one;
        array[1] = two;
        array[2] = three;

        System.out.println(array[0]); // 地址值
        System.out.println(array[1]); // 地址值
        System.out.println(array[2]); // 地址值

        System.out.println(array[1].getName()); // 古力娜扎
    }

}


```
### ArrayList集合
ArrayList当中的常用方法有：

1)public boolean add(E e)：向集合当中添加元素，参数的类型和泛型一致。返回值代表添加是否成功。
备注：对于ArrayList集合来说，add添加动作一定是成功的，所以返回值可用可不用。但是对于其他集合（今后学习）来说，add添加动作不一定成功。

2)public E get(int index)：从集合当中获取元素，参数是索引编号，返回值就是对应位置的元素。

3)public E remove(int index)：从集合当中删除元素，参数是索引编号，返回值就是被删除掉的元素。

public int size()：获取集合的尺寸长度，返回值是集合中包含的元素个数。

```java
package fill;

import java.util.ArrayList;

public class ArrayListTest {
    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<>();
        // 添加元素
        list.add("小泉花阳");
        list.add("黑泽露比");
        list.add("高海千歌");
        System.out.println(list);
        //遍历元素
        for (int i = 0; i <list.size() ; i++) {
            System.out.println(list.get(i));
        }
        //获取元素
        String name = list.get(2);
        System.out.println("第3个元素为"+name);
        //删除元素
        String whoRemoved = list.remove(3);
        System.out.println("删除的是"+whoRemoved);
        System.out.println(list);

    }
}

```
==注意==：如果希望向集合ArrayList当中存储基本类型数据，必须使用基本类型对应的“包装类”。
位于java.lang 包下

| 基本类型 | 包装类        |
| -------- | ------------- |
| short    | Short         |
| int      | ==Integer==   |
| long     | Long          |
| float    | Float         |
| double   | Double        |
| char     | ==Character== |
| boolean  | Boolean       |
| byte     | Byte          |


```java
public class Demo05ArrayListBasic {

    public static void main(String[] args) {
        ArrayList<String> listA = new ArrayList<>();
        // 错误写法！泛型只能是引用类型，不能是基本类型
//        ArrayList<int> listB = new ArrayList<>();

        ArrayList<Integer> listC = new ArrayList<>();
        listC.add(100);
        listC.add(200);
        System.out.println(listC); // [100, 200]

        int num = listC.get(1);
        System.out.println("第1号元素是：" + num);
    }

}

```
==应用案例==
题目：自定义4个学生对象，添加到集合，并遍历。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706001712842.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## Array
（1）java.util.Arrays是一个与数组相关的工具类，里面提供了大量静态方法，用来实现数组常见的操作。

（2）public static String toString(数组)：将参数数组变成字符串（按照默认格式：[元素1, 元素2, 元素3...]）
（3）public static void sort(数组)：按照默认升序（从小到大）对数组的元素进行排序。

备注：
1. 如果是数值，sort默认按照升序从小到大
2. 如果是字符串，sort默认按照字母升序
3. 如果是自定义的类型，那么这个自定义的类需要有Comparable或者Comparator接口的支持。（今后分析）

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706232925914.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

必须是数组才能使用Arrays.sort(array1)方法（字符串不行）
倒序排序  for循环 快捷键

```java
chars.forr
```

## String字符串
java.lang.String类代表字符串。

API当中说：Java 程序中的所有字符串字面值（如 "abc" ）都作为此类的实例实现。
其实就是说：程序当中所有的双引号字符串，都是String类的对象。（就算没有new，也照样是。）

==字符串的特点：==
 1. 字符串的内容永不可变。【重点】
 2. 正是因为字符串不可改变，所以字符串是可以共享使用的。
 3. 字符串效果上相当于是char[]字符数组，但是底层原理是byte[]字节数组。
### 字符串的构造方法
创建字符串的常见3+1种方式。
==三种构造方法：==
 1. 根据字符数组创建字符串
 2. 根据字节数组创建字符串
 3. 直接创建

public String()：创建一个空白字符串，不含有任何内容。
public String(char[] array)：根据字符数组的内容，来创建对应的字符串。
public String(byte[] array)：根据字节数组的内容，来创建对应的字符串。
一种直接创建：
String str = "Hello"; // 右边直接用双引号

注意：直接写上双引号，就是字符串对象。


```java
package fill;

public class StringTest {
    public static void main(String[] args) {
        // 使用空参构造
        String str1 = new String();
        System.out.println("第一个字符串"+str1);
        // 根据字符数组创建字符串
        char[] charArray ={'A','B','C'};
        String str2 = new String(charArray);
        System.out.println("第二个字符串"+str2);
        // 根据字节数组创建字符串
        byte[] byteArray = {97,98,99} ;
        String str3 = new String(byteArray);
        System.out.println("第三个字符串为"+str3);
        // 直接创建
        String str4 = "Hello";
        System.out.println("第四个字符串"+str4);

    }
}

```
### 字符串常量池
字符串常量池：程序当中直接写上的双引号字符串，就在字符串常量池中。

对于基本类型来说，==  是进行数值的比较。
对于引用类型来说，== 是进行【地址值】的比较。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706125646614.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 字符串相关方法
##### 比较方法
如上述 == 是进行对象的地址值比较，如果确实需要字符串的内容比较，可以使用两个方法：

（一）public boolean equals(Object obj)：参数可以是任何对象，只有参数是一个字符串并且内容相同的才会给true；否则返回false。
注意事项：
1. 任何对象都能用Object进行接收。
2. equals方法具有对称性，也就是a.equals(b)和b.equals(a)效果一样。
3. 如果比较双方一个常量一个变量，推荐把常量字符串写在前面。
推荐："abc".equals(str)    不推荐：str.equals("abc")

（二）public boolean equalsIgnoreCase(String str)：忽略大小写，进行内容比较。

```java
String strA = "Java"'
String strB = "java ;
System.out.println(strA.equals(strB)); // false，严格区分大小写
System.out.println(strA.equalsIgnoreCase(strB)); // true，忽略大小写
 ```
#### 常用方法
1. public int length()：获取字符串当中含有的字符个数，拿到字符串长度。
2. public String concat(String str)：将当前字符串和参数字符串拼接成为返回值新的字符串。
3. public char charAt(int index)：获取指定索引位置的单个字符。（索引从0开始。）
4. public int indexOf(String str)：查找参数字符串在本字符串当中首次出现的索引位置，如果没有返回-1值。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706141440660.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

#### 截取方法
字符串的截取方法：
1. public String substring(int index)：截取从参数位置一直到字符串末尾，返回新字符串。
2. public String substring(int begin, int end)：截取从begin开始，一直到end结束，中间的字符串。
备注：[begin,end)，包含左边，不包含右边。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706202526235.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

#### 转化方法
1. public char[] toCharArray()：将当前字符串拆分成为字符数组作为返回值。
2. public byte[] getBytes()：获得当前字符串底层的字节数组。
3. public String replace(CharSequence oldString, CharSequence newString)：
将所有出现的老字符串替换成为新的字符串，返回替换之后的结果新字符串。
备注：CharSequence意思就是说可以接受字符串类型。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706203010291.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


#### 截取方法
分割字符串的方法：
public String[] split(String regex)：按照参数的规则，将字符串切分成为若干部分。

==注意事项==：
split方法的参数其实是一个“正则表达式”，今后学习。
今天要注意：如果按照英文句点“.”进行切分，必须写"\\."（两个反斜杠）

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706204409514.png)

## Static 
一旦使用了static关键字，那么这样的内容不在属于对象自己，而是属于类的，所以凡是本类的对象都共享同一份。


如果没有static关键字，那么必须首先创建对象，然后通过对象才能使用它。
如果有了static关键字，那么不需要创建对象，直接就能通过类名称来使用它。

无论是成员变量，还是成员方法。如果有了static，都推荐使用类名称进行调用。
静态变量：类名称.静态变量
静态方法：类名称.静态方法()

注意事项：
1. 静态不能直接访问非静态。
原因：因为在内存当中是【先】有的静态内容，【后】有的非静态内容。
“先人不知道后人，但是后人知道先人。”
2. 静态方法当中不能用this。
原因：this代表当前对象，通过谁调用的方法，谁就是当前对象。、

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706230648881.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

静态代码块分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200706231259810.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 数学方法
java.util.Math类是数学相关的工具类，里面提供了大量的静态方法，完成与数学运算相关的操作。

public static double abs(double num)：获取绝对值。有多种重载。
public static double ceil(double num)：向上取整。
public static double floor(double num)：向下取整。
public static long round(double num)：四舍五入。（与上述不同此不带小数点）

Math.PI代表近似的圆周率常量（double）。

实际运用案例：
计算在-10.8到5.9之间，绝对值大于6或者小于2.1的整数有多少个？
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020070623443421.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020070623434992.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
 *写在最后：全栈方向，前端已经大部分学完，将会以复习的形式出现在博客，大家敬请期待哈~*

