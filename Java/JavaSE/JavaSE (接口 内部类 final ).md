# JavaSE (接口  final 内部类)
---
*写在前面：分享技术，共同进步，把之前写的笔记搬运至博客，*有不足请见谅*，相关意见可评论告知 (。・∀・)ノ
> 编程路漫漫，学习无止尽！

@[toc]

## 接口
interface       n. 界面；<计>接口；交界面

接口就是多个类的公共规范。
接口是一种引用数据类型，最重要的内容就是其中的：抽象方法。

如何定义一个接口的格式：
public interface 接口名称 {
    // 接口内容
}

备注：换成了关键字interface之后，编译生成的字节码文件仍然是：.java --> .class。

如果是Java 7，那么接口中可以包含的内容有：
1. 常量
2. 抽象方法

如果是Java 8，还可以额外包含有：
3. 默认方法
4. 静态方法

如果是Java 9，还可以额外包含有：
5. 私有方法

### 接口使用步骤：
1. 接口不能直接使用，必须有一个“实现类”来“实现”该接口。
==格式：==
public class 实现类名称 implements 接口名称 {
    // ...
}
2. 接口的实现类必须覆盖重写（实现）接口中所有的抽象方法。
实现：去掉abstract关键字，加上方法体大括号。
3. 创建实现类的对象，进行使用。

### 注意事项：
1. 接口当中的抽象方法，修饰符必须是两个固定的关键字：public abstract
2. 这两个关键字修饰符，**可以选择性地省略**。
3. 方法的三要素，可以随意定义。
4. 如果实现类并没有覆盖重写接口中所有的抽象方法，那么这个实现类自己就必须是抽象类。

在任何版本的Java中，接口都能定义抽象方法。
格式：
public abstract 返回值类型 方法名称(参数列表);

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200708203242646.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


### 接口默认方法
解决接口升级，仍要覆盖重写所有类的问题

1. 接口的默认方法，可以通过接口实现类对象，直接调用。
2. 接口的默认方法，也可以被接口实现类进行覆盖重写。

从Java 8开始，接口里允许定义默认方法。
格式：
public default 返回值类型 方法名称(参数列表) {
    方法体
}

备注：接口当中的默认方法，可以解决接口升级的问题。

代码体现

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200709105121628.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/2020070910511144.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 接口的静态方法
静态与类有关系，与对象无关系

注意事项：不能通过接口实现类的对象来调用接口当中的静态方法。
正确用法：通过接口名称，直接调用其中的静态方法。
格式：
接口名称.静态方法名(参数);


```java
package cn.itcast.day10.demo01;

public class Demo03Interface {

    public static void main(String[] args) {
        // 创建了实现类对象
        MyInterfaceStaticImpl impl = new MyInterfaceStaticImpl();

        // 错误写法！
//        impl.methodStatic();

        // 直接通过接口名称调用静态方法
        MyInterfaceStatic.methodStatic();
    }

}

__________________________________________________________________________________________________
package cn.itcast.day10.demo01;

public interface MyInterfaceStatic {

    public static void methodStatic() {
        System.out.println("这是接口的静态方法！");
    }

}

```

### 接口的私有方法
引言：
我们需要抽取一个共有方法，用来解决两个默认方法之间重复代码的问题。
==但是这个共有方法不应该让实现类使用，应该是私有化的。==

解决方案：
从Java 9开始，接口当中允许定义私有方法。
1. 普通私有方法，解决多个默认方法之间重复代码问题
==格式：==
private 返回值类型 方法名称(参数列表) {
    方法体
}

2. 静态私有方法，解决多个静态方法之间重复代码问题
格式：
private static 返回值类型 方法名称(参数列表) {
    方法体
}

```java
package cn.itcast.day10.demo01;


public interface MyInterfacePrivateA {

    public default void methodDefault1() {
        System.out.println("默认方法1");
        methodCommon();
    }

    public default void methodDefault2() {
        System.out.println("默认方法2");
        methodCommon();
    }

    private void methodCommon() {
        System.out.println("AAA");
        System.out.println("BBB");
        System.out.println("CCC");
    }

}

```

### 接口中常量使用

接口当中也可以定义“成员变量”，但是必须使用public static final三个关键字进行修饰。
从效果上看，这其实就是接口的【常量】。
==格式：==
public static final 数据类型 常量名称 = 数据值;
备注：
一旦使用final关键字进行修饰，说明不可改变。

注意事项：
1. 接口当中的常量，可以==省略==public static final，注意：不写也照样是这样。
2. 接口当中的常量，必须进行赋值；不能不赋值。
3. 接口中常量的名称，使用完全大写的字母，用下划线进行分隔。（推荐命名规则）

```java
package cn.itcast.day10.demo01;

public interface MyInterfaceConst {

    // 这其实就是一个常量，一旦赋值，不可以修改
    public static final int NUM_OF_MY_CLASS = 12;

}
```
### 接口小结
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200709125005483.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

 使用接口的时候，需要注意：

1. 接口是没有静态代码块或者构造方法的。
2. 一个类的直接父类是唯一的，但是一个类可以同时实现多个接口。
格式：
public class MyInterfaceImpl implements MyInterfaceA, MyInterfaceB {
    // 覆盖重写所有抽象方法
}
3. 如果实现类所实现的多个接口当中，存在重复的抽象方法，那么只需要覆盖重写一次即可。
4. 如果实现类没有覆盖重写所有接口当中的所有抽象方法，那么实现类就必须是一个抽象类。
5. 如果实现类实现的多个接口当中，存在重复的默认方法，那么实现类一定要对冲突的默认方法进行覆盖重写。
6. 一个类如果直接父类当中的方法，和接口当中的默认方法产生了冲突，优先用父类当中的方法。（优先继承，然后接口）

7. 类与类之间是单继承的。直接父类只有一个。
8. 类与接口之间是多实现的。一个类可以实现多个接口。
9. 接口与接口之间是多继承的。

注意事项：
10. 多个父接口当中的==抽象方法==如果重复，没关系。
11. 多个父接口当中的==默认方法==如果重复，那么子接口必须进行默认方法的覆盖重写，【而且带着default关键字】。


## final关键字
final关键字代表最终、不可改变的。

常见四种用法：
1. 可以用来修饰一个类
2. 可以用来修饰一个方法
3. 还可以用来修饰一个局部变量
4. 还可以用来修饰一个成员变量


当final关键字用来修饰一个类的时候，
==格式：==
public final class 类名称 {
    // ...
}

含义：当前这个类不能有任何的子类。
注意：一个类如果是final的，那么其中所有的成员方法都无法进行覆盖重写（因为没儿子。）

注意事项：对于类，方法来说，abstract关键字（一定覆盖重写）和final关键字（不能覆盖重写）不能同时使用因为矛盾。


 对于**基本类型**来说，不可变说的是变量当中的**数据**不可改变
 对于**引用类型**来说，不可变说的是变量当中的**地址值**不可改变（但是地址值指向的内容可以改变）



对于成员变量来说，如果使用final关键字修饰，那么这个变量也照样是不可变。

1. 由于成员变量具有默认值，所以用了final之后必须手动赋值，不会再给默认值了。
2. 对于final的成员变量，要么使用直接赋值，要么通过构造方法赋值。二者选其一。
3. 必须保证类当中所有重载的构造方法，都最终会对final的成员变量进行赋值。



## java中四种权限修饰符
==重要==
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020070921502237.png)

**结合内部类小结：**
public > protected > (default) > private
定义一个类的时候，权限修饰符规则：
1. 外部类：public / (default)
2. 成员内部类：public / protected / (default) / private
3. 局部内部类：什么都不能写
## 内部类
如果一个事物的内部包含另一个事物，那么这就是一个类内部包含另一个类。
例如：身体和心脏的关系。又如：汽车和发动机的关系。

分类：
1. 成员内部类
2. 局部内部类（包含匿名内部类）

成员内部类的==定义格式==：
修饰符 class 外部类名称 {
    修饰符 class 内部类名称 {
        // ...
    }
    // ...
}

**注意：内用外，随意访问；外用内，需要内部类对象。**


### 使用成员内部类的方式
如何使用成员内部类？有两种方式：
1. 间接方式：在外部类的方法当中，使用内部类；然后main只是调用外部类的方法。
2. 直接方式，==公式：==
类名称 对象名 = new 类名称();
【外部类名称.内部类名称 对象名 = new 外部类名称().new 内部类名称();】

代码体现
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200709224718995.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
输出结果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200709224751400.png)

### 内部类重名变量访问
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200709225120471.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


### 局部内部类final问题
局部内部类，如果希望访问所在方法的局部变量，那么这个局部变量必须是【有效final的】。

备注：从Java 8+开始，只要局部变量事实不变，那么final关键字可以省略。

原因：
1. new出来的对象在堆内存当中。
2. 局部变量是跟着方法走的，在栈内存当中。
3. 方法运行结束之后，立刻出栈，局部变量就会立刻消失。
4. 但是new出来的对象会在堆当中持续存在，直到垃圾回收消失。


### 匿名内部类（重要）
如果接口的==实现类==（或者是父类的子类）只需要使用唯一的一次，
那么这种情况下就可以省略掉该类的定义，而改为使用【匿名内部类】。

匿名内部类的定义==格式==：
**接口名称 对象名 = new 接口名称() {
    // 覆盖重写所有抽象方法
};**

对格式“new 接口名称() {...}”进行解析：
1. new代表创建对象的动作
2. 接口名称就是匿名内部类需要实现哪个接口
3. {...}这才是匿名内部类的内容

另外还要注意几点问题：
1. 匿名内部类，在【创建对象】的时候，只能使用唯一一次。
如果希望多次创建对象，而且类的内容一样的话，那么就需要使用单独定义的实现类了。
2. 匿名对象，在【调用方法】的时候，只能调用唯一一次。
如果希望同一个对象，调用多次方法，那么必须给对象起个名字。
3. 匿名内部类是省略了【实现类/子类名称】，但是匿名对象是省略了【对象名称】
**强调：匿名内部类和匿名对象不是一回事！！！**


类和接口都可以作为成员变量的类型


----
 *写在最后：全栈方向，前端已经大部分学完，将会以复习的形式出现在博客，大家敬请期待哈~*
