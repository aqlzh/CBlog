# javaSE部分(流程 方法)
*写在前面：第一次把之前写的笔记搬运至博客，有不足请见谅*，*相关意见可评论告知,分享技术，共同进步*   (●ˇ∀ˇ●)

> 编程路漫漫，学习无止尽！

@[toc]
## Scanner 对象

注意:Scanner  是一个类，关键字都为小写的
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704154911438.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
java.util.Scanner 是java5的新特性，我们可以通过Scanner类来获取用户的输入。

==注意：==通过Scanner类的next（）与nextLine()方法获取输入的字符串，在读取前我们一般使用hasNext()与hasNextLine()判断是否还有输入的数据。

代码

```java
package base;

import java.util.Scanner;

public class Scannner_07 {
    public static void main(String[] args) {
        // 创建一个扫描对象，用于接受键盘数据
        Scanner scanner = new Scanner(System.in) ;

        System.out.println("请输入数据将使用next接收");

        // 判断用户有没有输入字符
        if(scanner.hasNext()){
            // 输入数字
            int num = scanner.nextInt() ;
            System.out.println("输入的数字是"+num);
            // 使用next接受(输入字符串)
            String str = scanner.next() ;
            System.out.println("输入的字符串内容为"+str);
        }

        System.out.println("_______");

        int i=0;
        float f = 0.0f ;

        System.out.println("请输入整数");

        if(scanner.hasNextInt()){
            i =scanner.nextInt() ;
            System.out.println("整数数据"+i);
        }else{
            System.out.println("输入的不是整数数据");
        }

        System.out.println("请输入小数");

        if(scanner.hasNextFloat()){
            f=scanner.nextFloat();
            System.out.println("小数数据"+f);
        }else{
            System.out.println("输入的不是小数数据");
        }


        // 凡是属于IO流，要及时关闭，否则占用资源
        scanner.close() ;
    }
}

```

## next()与nextLine() 区别
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155017747.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

模块


```java
 Scanner scanner = new Scanner(System.in) ;

   scanner.close() ;
```
案列
```java
package fill;

import java.util.Scanner;

public class ScannerSum {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in) ;

        System.out.println("这是一个比较三个数大小的程序");
        System.out.println("请输入第一个数");
        int a = sc.nextInt() ;
        System.out.println("请输入第二个数");
        int b = sc.nextInt() ;
        System.out.println("请输入第三个数");
        int c = sc.nextInt() ;

        int temp = a>b ? a : b ;
        int max = c >temp ? c:temp ;
        System.out.println("比较结果"+max);
    }
}

```

###  控制流程
### 顺序结构
### 选择结构

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155035430.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155055446.png)
反编译  java  --   class (字符码文件)    -- 反编译（IDEA）
### 循环结构
while      do.... while     
==for==
在  Idea 中  for的==快捷键==为  
注意其在一定的区间内
100.for
fori
相关参考链接

> https://www.cnblogs.com/wtjqs/p/10486747.html

==println 输出完会换行==
==print 输出完不会换行==

#### 练习 打印九九乘法表
(javascript)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020070415515976.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
(java)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155207807.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
#### 增强for循环
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155221690.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
用于优化数组与集合的
#### break continue
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155235626.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### goto 实列
在java 中用于for循环
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155323590.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
相关参考
> https://blog.csdn.net/Crazypokerk_/article/details/93359970


 System.out.println()     分别为 类 对象 方法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155358811.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 方法的定义
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155425886.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 方法调用
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155441159.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
java  为值传递
### 方法的重载
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155503575.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 命令行传参
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155516870.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
注意执行路径（关于包）
### 可变参数
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155528866.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 递归
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155540781.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 数组

### 数组声明创建
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155604207.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 内存分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155617309.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155643552.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
数组在没有new 的时候是在栈中
### 三种初始化状态
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155702591.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 数组的特点
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155717799.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 数组边界
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155727719.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 数组进阶
for ==高级快捷键==

```java
 arrays.for
```

此处arrays 与要遍历的元素相同
普通数组快捷键

```java
 fori
```

### 多维数组
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155804532.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
==二维数组==
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155816329.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### Arrays 类
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155828896.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 冒泡排序
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200704155836413.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
代码
```java
package base;

import java.util.Arrays ;

public class arrayAdvanceTwo_13 {
    public static void main(String[] args) {

        // //二维数组
        int[][] array = {{1,2},{2,3},{3,4},{4,4}} ;

        System.out.println(array[0][1]);

        printArray(array[0]);
        System.out.println(" ");
        System.out.println(array[0]);


        System.out.println("_______");
        int[] a ={1,34,5,2,67,3,45,89,23} ;

        // 打印数组元素方法
        System.out.println(Arrays.toString(a));

        System.out.println("_________");
        // //升序
        Arrays.sort(a) ;
        System.out.println(Arrays.toString(a));

        System.out.println("__________");
        // //填充
        Arrays.fill(a,2,4,0);
        System.out.println(Arrays.toString(a));


        System.out.println("___________");
        // //冒泡排序
        int[] sort = sort(a) ;
        System.out.println(Arrays.toString(sort));



    }

   public static int[] sort(int[] a){
        int temp = 0 ;
       // 冒泡排序  两个for循环 外层冒泡数  里层依次比较
       for (int i = 0; i <a.length ; i++) {
           // 内层循环判断两个数
           for (int j = 0; j <a.length-1 ; j++) {
               if(a[j+1] < a[j]){
                   temp = a[j] ;
                   a[j] = a[j+1] ;
                   a[j+1] = temp ;
                }
           }
       }
       return a ;
   }



    public static void printArray(int[] arrays){
        for (int i = 0; i <arrays.length ; i++) {
            System.out.print(arrays[i]);
        }
    }
}

```

### 稀疏数组

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020070415584497.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
代码
```java
package base;

public class sparseArray_14 {
    public static void main(String[] args) {
        // 1. 创建一个二维数组 11*11
        int[][] array1 = new int[11][11];
        array1[1][2] = 1;
        array1[2][3] = 2;

        System.out.println("输出原始数组");
        // 普通数组形式
        for (int[] ints : array1) {
//            for (int[] ints1 : array1) {
//                System.out.print(ints1+"\t");
//            }        此为输出地址
            for (int anInt : ints) {
                System.out.print(anInt + "\t");
            }
            System.out.println();
        }

        System.out.println("____________");
        //转化为稀疏数组进行保存
        int sum = 0;
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (array1[i][j] != 0) {
                    sum++;
                }
            }
        }
        System.out.println("有效值的个数为" + sum);

        // 创建一个稀疏数组的数组
        int[][] array2 = new int[sum + 1][3];

        array2[0][0] = 11;
        array2[0][1] = 11;
        array2[0][2] = sum;

        // 遍历二维数组   将非零的值放在稀疏数组中
        int count = 0;
        for (int i = 0; i < array1.length; i++) {
            for (int j = 0; j < array1[i].length; j++) {
                if (array1[i][j] != 0) {
                    count++;
                    array2[count][0] = i;
                    array2[count][1] = j;
                    array2[count][2] = array1[i][j];
                }
            }
        }
        System.out.println("稀疏数组");

        for (int i = 0; i < array2.length; i++) {
            System.out.println(array2[i][0] + "\t"
                    + array2[i][1] + "\t"
                    + array2[i][2] + "\t"
            );
        }
        System.out.println("________");
        System.out.println("还原");
        // 读取稀疏数组
        int[][] array3 = new int[array2[0][0]][array2[0][1]];

        // 给元素还原值
        for (int i = 1; i < array2.length; i++) {
            array3[array2[i][0]][array2[i][1]] = array2[i][2];
        }
        System.out.println("输出还原的数组");

        for (int[] ints : array1) {
//            for (int[] ints1 : array1) {
//                System.out.print(ints1+"\t");
//            }        此为输出地址
            for (int anInt : ints) {
                System.out.print(anInt + "\t");
            }
            System.out.println();
        }
    }


}

```
 *写在最后：全栈方向，前端已经大部分学完，将会以复习的形式出现在博客，大家敬请期待哈~*
