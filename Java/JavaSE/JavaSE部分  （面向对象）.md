# JavaSE部分 （面向对象）

*写在前面：分享技术，共同进步，把之前写的笔记搬运至博客，*有不足请见谅*，相关意见可评论告知  ╰(￣ω￣ｏ)
> 编程路漫漫，学习无止尽！

面向对象三大特性： 封装，继承，多态
@[toc]
## 封装
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200708130658813.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

**封装的优点**
  1.提高程序的安全性，保护数据
   2.隐藏代码的实现细节
   3.统一接口
   4.增加系统的可维护性


```java
public class application {

    public static void main(String[] args) {
        final student s1 = new student();   //?
        s1.money=1.0 ;
//        s1.String ="" ;      报红因为私有

        String name = s1.getName();

        s1.setName("LZH");
        System.out.println(s1.getName());

        s1.setAge(12)  ;  // 不合法
        System.out.println(s1.getAge());

    }
}

//————————————————————————————————————————————————————————————————————————————————————————————
         
public class student {
                 // 封装一般对属性进行封装，方法也可，但一般不

                 // 属性私有
                 private String name;
                 private int id;
                 private char sex;
                 private int age;

                 public double money;


                 //但提供一些可以操作这个属性的方法
                 // 提供一些public 的get,set 方法

                 // get 获得这个数据
                 public String getName() {
                     return this.name;
                 }


                 // set 给这个数据设置值
                 public void setName(String name) {
                     this.name = name;

                 }

                 // 方法封装的应用
                 public int getAge() {
                     return age;
                 }

                 // 对其进行内部操作
                 public void setAge(int age) {
                     if (age > 120 || age < 0) {
                         this.age = 3;
                     } else {
                         this.age = age;
                     }

                 }
             }

```




## 继承
### 继承图解
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707132143232.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 继承中成员变量的访问特点
在父子类的继承关系当中，如果成员变量重名，则创建子类对象时，访问有两种方式：

==重要==
1. 直接通过子类对象访问成员变量：
    等号左边是谁，就优先用谁，没有则向上找。
2. 间接通过成员方法访问成员变量：
    该方法属于谁（再哪里定义），就优先用谁，没有则向上找。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707133324222.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

==注意==子类中三种成员变量重名的情况
局部变量    直接写成员变量名
本类的成员变量    this.成员变量名
父类的成员变量名     super.成员变量名



### 继承方法中的覆盖重写
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707134209449.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
方法覆盖重写的==注意事项==：

1. 必须保证父子类之间方法的名称相同，参数列表也相同。
@Override：写在方法前面，用来检测是不是有效的正确覆盖重写。
这个注解就算不写，只要满足要求，也是正确的方法覆盖重写。

2. 子类方法的返回值必须【小于等于】父类方法的返回值范围。
小扩展提示：java.lang.Object类是所有类的公共最高父类（祖宗类），java.lang.String就是Object的子类。

3. 子类方法的权限必须【大于等于】父类方法的权限修饰符。
小扩展提示：public > protected > (default) > private
备注：(default)不是关键字default，而是什么都不写，留空。

4. 成员变量是不能覆盖重写( @override  )的     int  num = 10 ;


==设计原则==
对于已经投入使用的类，尽量不要进行修改，推荐定义一个新的类，来重复利用其中的共性内容，并添加改动新内容。

在IDAE中查看树的快捷键 ctrl +H


### 值传递与引用传递
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707193810410.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 构造器
快捷键  alt  + insert    (生成构造器)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200708142454675.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
package oop.objectClass;

public class constructor_04 {
    // 一个类即使什么都不写，他也会存在一个方法
    // 显示定义的构造类

    String name ;

    // 实列化初始值
    // 1.使用new关键字，本质是调用构造器

    // 显化  无参构造
    public constructor_04() {
        this.name = "Qy";
    }

    // 有参构造      注意一旦定义了有参构造，无参就必须显示定义
    public  constructor_04(String name){
        this.name = name ;        // 前者name 为7行 String name  后者name为传进来name 18

    }


}

//___________________________________________________________________________


package oop.objectClass;

//   一个项目中因该只有一个方法
public class Application_02 {
    public static void main(String[] args) {
        // 类  抽象的   实例化
        // 类实列化后会返回一个自己的对象
        // 以下第二个单词（student）就是一个Student 类的具体实列

//        Student student = new Student() ;
//        Student xiaoming  = new Student() ;
//        Student xiaohong = new Student() ;    // 由于第一个单词报错
          // 原因与类名相同    第二个单词  对象名可以不同

        classAndObject_03 student = new  classAndObject_03() ;
        classAndObject_03 xiaoming  = new  classAndObject_03() ;
        classAndObject_03 xiaohong = new  classAndObject_03() ;

        xiaoming.name ="小明" ;
        xiaoming.age = 3 ;

        System.out.println(xiaoming.name);
        System.out.println(xiaoming.age);

        System.out.println(xiaohong.name);



        //   constructor_04 部分·
        constructor_04 constructor_04 = new constructor_04();
        System.out.println(constructor_04.name);


    }
}
```

### Super
   （一）继承关系中，父子类构造方法的访问特点：

1. 子类构造方法当中有一个默认隐含的“super()”调用，所以一定是先调用的父类构造，后执行的子类构造。
2. 子类构造可以通过super关键字来调用父类重载构造。
3. super的父类构造调用，必须是子类构造方法的第一个语句。不能一个子类构造调用多次super构造。
总结：
（二）子类必须调用父类构造方法，不写则赠送super()；写了则用写的指定的super调用，super只能有一个，还必须是第一个。


（三）super关键字用来访问父类内容，而this关键字用来访问本类内容。用法也有三种：

1. 在本类的成员方法中，访问本类的成员变量。
2. 在本类的成员方法中，访问本类的另一个成员方法。
3. 在本类的构造方法中，访问本类的另一个构造方法。
在第三种用法当中要注意：
A. this(...)调用也必须是构造方法的第一个语句，唯一一个 ※
B. super和this两种构造调用，不能同时使用。

※  详细见图分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707195912541.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### super  注意点

1.super 调用父类的构造方法，必须在构造方法的第一个

2.super 必须只能出现在子类的方法或构造方法中

3.super 和 this 不能同时调用构造方法   （同为第一优先级矛盾）

### super 与 this 的区别

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707174400251.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

两者关系图解
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707201703644.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


### 抽象方法与抽象类
抽象方法：就是加上==abstract==关键字，然后去掉大括号，直接分号结束。
抽象类：抽象方法所在的类，必须是抽象类才行。在class之前写上abstract即可。

如何使用抽象类和抽象方法：
1. 不能直接创建new抽象类对象。
2. 必须用一个子类来继承抽象父类。
3. 子类必须覆盖重写抽象父类当中所有的抽象方法。
覆盖重写（实现）：子类去掉抽象方法的abstract关键字，然后补上方法体大括号。
4. 创建子类对象进行使用。


![在这里插入图片描述](https://img-blog.csdnimg.cn/202007072159384.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
public abstract class Fu{
   public abstract void eat() ; 
}
```

#### 使用注意事项

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707220532252.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707220859915.png)
**代码体现如下**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707225639385.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707225648846.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707225701373.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
j![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707225708328.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200707225716377.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 多态
体现形式，父类引用指向子类对象。
**格式：**
父类名称  对象名  = new 子类名称（）
接口名称  对象名  = new  实现类名称（）

访问成员变量的两种方式：

1. 直接通过对象名称访问成员变量：看等号左边是谁，优先用谁，没有则向上找。
2. 间接通过成员方法访问成员变量：看该方法属于谁，优先用谁，没有则向上找。


**多态方法的访问规则是：**
    看new的是谁，就优先用谁，没有则向上找。

口诀：编译看左边，运行看右边。

==对比一下：==
成员变量：编译看左边，运行看左边。
成员方法：编译看左边，运行看右边。


*多态好处的实列体现：*
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200708101627880.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)



### 对象的向上转型与向下转型
*类比数据类型的转化：*
     低 ------------->  高
 **byte,short,char -> int -> long -> float -> double**

```java
package base;

public class typeCast_03 {
    public static void main(String[] args) {

        int i =128 ;
        byte b = (byte)i ; // 内存溢出    // 强制转换
        double c = i ;   // 自动转换
        // 强制转换   （类型）变量名   高 - 低
        // 直动转换   低 - 高
        System.out.println(i);
        System.out.println(b);
        System.out.println(c);

        System.out.println("______");

        // 例子2
        char d = 'a' ;
        int e =d+1  ;  // 自动转换   低 - 高
        System.out.println(e);
        System.out.println((int)e);  //  强制转换

        int money = 10_0000_0000 ;  // jdk7 新特性
        int years = 20 ;
        int total = money*years ;    // 数据溢出
        long  total2 =  money*years ;  // 默认int 在转换之前已存在问题
        // 正解
        long total3 = money*((long)years)  ;
        System.out.println(total);
        System.out.println(total2);
        System.out.println(total3);

    }
}

```

方法图解：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200708122343793.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)



### Instanceof
引言： 如何才能知道一个父类引用的对象，本来是什么类？如果希望调用子类特有方法，则需要向下转型。

instanceof 是 Java 的保留关键字。它的作用是测试它左边的对象是否是它右边的类的实例，返回 boolean 的数据类型。

==格式==
对象  instanceof 类名称

eg:
![在这里插入图片描述](https://img-blog.csdnimg.cn/202007081305086.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

图解分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200708141519990.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


## 面向对象小结

1.类与对象： 类是一个模板，抽象的，对象是一个具体的实列（先有对象再有类）

2.方法  ：  定义，调用

3.对象的引用   

   引用类型，除八大基本类型外，对象是通过引用来操作的：栈 -> 堆

4.属性： 字符field 成员变量

==默认初始化== 
 数字0   0.0 

​                      char    u0000

​                      boolean   false

​                      引用   null

属性格式：    修饰符   属性类型  属性名  = 属性值

5、对象的创建和使用

   必须使用new  关键字创造对象，  构造器  Person Qy new Qy() ;

  对象的属性   Qy.name

  对象的方法   Qy.sleep()

6.类：   静态的属性   属性       动态的行为   方法

 *写在最后：全栈方向，前端已经大部分学完，将会以复习的形式出现在博客，大家敬请期待哈~*


