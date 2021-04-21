**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫之远兮，简犹春天之临兮；
   劝君专注案前事，亦是杯酒敬苍生；

@[toc]
# 引入
## 概述
**Spring概念**：是一个轻量级的控制反转(IOC)和面向切面(AOP)的容器（框架）。
**Spring理念** : 使现有技术更加实用 , 整合现有的框架技术。

官网 : http://spring.io/
官方下载地址 : https://repo.spring.io/libs-release-local/org/springframework/spring/
GitHub : https://github.com/spring-projects

==优点==
1、Spring是一个开源免费的框架 , 容器  .
2、Spring是一个轻量级的框架 , 非侵入式的 .
3、控制反转 IoC  , 面向切面 Aop
4、对事物的支持 , 对框架的支持

##  组成模块
模块分为核心容器、数据访问/集成、Web、AOP（面向切面编程）、检测、消息传递和测试，如下图所示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081416072585.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


==核心容器==：提供 Spring 框架的基本功能。主要组件是 BeanFactory，它是工厂模式的实现。BeanFactory 使用控制反转（IOC） 模式将应用程序的配置和依赖性规范与实际的应用程序代码分开。

==Spring 上下文==：此为一个配置文件，向 Spring 框架提供上下文信息。Spring 上下文包括企业服务，例如 JNDI、EJB、电子邮件、国际化、校验和调度功能。

==Spring AOP==：通过配置管理特性，此模块直接将面向切面的编程功能 , 集成到了 Spring 框架中。可以很容易地使 Spring 框架管理任何支持 AOP的对象。Spring AOP 模块为基于 Spring 的应用程序中的对象提供了事务管理服务。通过使用 Spring AOP，不用依赖组件，就可以将声明性事务管理集成到应用程序中。

==Spring DAO==：JDBC DAO 抽象层提供了有意义的异常层次结构，可用该结构来管理异常处理和不同数据库供应商抛出的错误消息。异常层次结构简化了错误处理，并且极大地降低了需要编写的异常代码数量（例如打开和关闭连接）。Spring DAO 的面向 JDBC 的异常遵从通用的 DAO 异常层次结构。

==Spring ORM==：Spring 框架插入了若干个 ORM 框架，从而提供了 ORM 的对象关系工具，其中包括 JDO、Hibernate 和 iBatis SQL Map。所有这些都遵从 Spring 的通用事务和 DAO 异常层次结构。

==Spring Web 模块==：Web 上下文模块建立在应用程序上下文模块之上，为基于 Web 的应用程序提供了上下文。所以，Spring 框架支持与 Jakarta Struts 的集成。Web 模块还简化了处理多部分请求以及将请求参数绑定到域对象的工作。

==Spring MVC 框架==：MVC 框架是一个全功能的构建 Web 应用程序的 MVC 实现。通过策略接口，MVC 框架变成为高度可配置的，MVC 容纳了大量视图技术，其中包括 JSP、Velocity、Tiles、iText 和 POI。


## IoC基础
**控制翻转引入**

分析实现：

原来的方式代码 .
1、UserDao接口

```java
public interface UserDao {
   public void getUser();
}
```

2、Dao的实现类

```java
public class UserDaoImpl implements UserDao {
   @Override
   public void getUser() {
       System.out.println("获取用户数据");
  }
}
```

3、UserService的接口

```java
public interface UserService {
   public void getUser();
}
```

4、Service的实现类

```java
public class UserServiceImpl implements UserService {
   private UserDao userDao = new UserDaoImpl();

   @Override
   public void getUser() {
       userDao.getUser();
  }
}
```

5、测试

```java
@Test
public void test(){
   UserService service = new UserServiceImpl();
   service.getUser();
}
```
---
                                        变更

---


```java
public class UserServiceImpl implements UserService {
   private UserDao userDao;
// 利用set实现         核心部分
   public void setUserDao(UserDao userDao) {
       this.userDao = userDao;
  }

   @Override
   public void getUser() {
       userDao.getUser();
  }
}
```

使用测试类进行测试 ;

```java
@Test
public void test(){
   UserServiceImpl service = new UserServiceImpl();
   service.setUserDao( new UserDaoMySqlImpl() );
   service.getUser();
   //那我们现在又想用Oracle去实现呢
   service.setUserDao( new UserDaoOracleImpl() );
   service.getUser();
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200814181142969.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

思想解说：降低耦合性，IOC的原型



![在这里插入图片描述](https://img-blog.csdnimg.cn/20200814180759329.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
==设计思想：==
**控制反转**是一种通过描述（XML或注解）并通过第三方去生产或获取特定对象的方式。在Spring中实现控制反转的是IoC容器，其实现方法是依赖注入（Dependency Injection,DI）。

可使用多种方式实现IoC，可以使用XML配置，也可以使用注解，新版本的Spring也可以零配置实现IoC。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200814194033237.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200814195737986.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

# 启航
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200814195835804.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 关于bean 概述
使用Spring 创建对象，在Spring 这些称为Bean

```css
![<bean id="hello" class="com.lzh.pojo.Hello">
    <constructor-arg value=""/>
    <property name="str" value="Spring"/>
</bean>](https://img-blog.csdnimg.cn/20200814200131812.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```

==之前==：
类型   变量名  =  new  类型（） ；
Hello  hello     =   new   Hello()   ;


==现在==：
bean  =   对象  new Hello()   ; 

id  =  变量名 
class  =  new 的对象 ；
property  给对象的属性设置值


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815110830619.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

ref标签：用来引用另一个bean：
ref属性：用来给一个对象的属性设置值
在bean的内部引用另一个bean对象：(引用Spring容器中创建好的对象)

通俗解释：
之前：写好菜单买好菜，客人来了自己把菜炒好招待
现在：把炒菜交给第三方餐厅来做

解耦：后续需求更改，对应程序更改方便


## IOC创建对象方式
一、==通过无参构造方法来创建==
User.java
```java

public class User {

   private String name;

   public User() {
       System.out.println("user无参构造方法");
  }

   public void setName(String name) {
       this.name = name;
  }

   public void show(){
       System.out.println("name="+ name );
  }

}
```

2、beans.xml

```css
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
               xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
               xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd">

<bean id="user" class="com.lzh.pojo.User">
    <property name="name" value="倾城"/>
</bean>

</beans>
```

3、测试类

```java
@Test
public void test(){
   ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
   //在执行getBean的时候, user已经创建好了 , 通过无参构造
   User user = (User) context.getBean("user");
   //调用对象的方法 .
   user.show();
}
```

结果可以发现，在调用show方法之前，User对象已经通过无参构造初始化了！



二、==通过有参构造方法来创建==
1、UserT . java

```java
public class UserT {

   private String name;

   public UserT(String name) {        // 此处改为有参
       this.name = name;
  }

   public void setName(String name) {
       this.name = name;
  }

   public void show(){
       System.out.println("name="+ name );
  }

}
```

2、beans.xml 有三种方式编写
下标、参数名、参数类型

第一种根据index参数下标设置 
```css
<bean id="userT" class="com.kuang.pojo.UserT">
   <!-- index指构造方法 , 下标从0开始 -->
   <constructor-arg index="0" value="lzh"/>
</bean>
```

第二种根据参数名字设置

```css
<bean id="userT" class="com.kuang.pojo.UserT">
   <!-- name指参数名 -->
   <constructor-arg name="name" value="lzh2"/>
</bean>
```

第三种根据参数类型设置    ==(推荐使用)==

```java
<bean id="userT" class="com.kuang.pojo.UserT">
   <constructor-arg type="java.lang.String" value="lzh3"/>
</bean>
```

3、测试

```java
@Test
public void testT(){
   ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
   UserT user = (UserT) context.getBean("userT");
   user.show();
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815125636919.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

结论：在配置文件加载的时候。其中管理的对象都已经初始化了，在getBean的时候即已经把容器里面的对象都创建。


## Spring配置
1、==别名==
alias 设置别名 , 为bean设置别名 , 可以设置多个别名，：在获取Bean的时候可以使用别名获取

```java
<alias name="userT" alias="userNew"/>
```

2、==Bean的配置==
bean就是java对象,由Spring创建和管理

（1）id 是bean的标识符,要唯一,如果没有配置id,name就是默认标识符
   如果配置id,又配置了name**,那么name是别名**
（2）   name可以设置多个别名,可以用逗号,分号,空格隔开
   如果不配置id和name,可以根据applicationContext.getBean(.class)获取对象;

class是bean的全限定名=包名+类名


```css
<bean id="hello" name="hello2 h2,h3;h4" class="com.kuang.pojo.Hello">
   <property name="name" value="Spring"/>
</bean>
import
```

3、==团队的合作通过import来实现 .==

```css
<import resource="{path}/beans.xml"/>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815131824828.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
# 依赖注入
**概念**依赖注入（Dependency Injection,DI），**依赖** : 指Bean对象的创建依赖于容器 . Bean对象的依赖资源 .**注入** : 指Bean对象所依赖的资源 , 由容器来设置和装配 .

## 一、构造器注入
详见上述IOC 部分

## 二、Set 注入 （重点）
要求被注入的属性 , 必须有set方法 , set方法的方法名由set + 属性首字母大写 , 如果属性是boolean类型 , 没有set方法 , 是 is .

测试pojo类 :

```java
Address.java

 public class Address {
 
     private String address;
 
     public String getAddress() {
         return address;
    }
 
     public void setAddress(String address) {
         this.address = address;
    }
 }
```

Student.java

```java
 package com.kuang.pojo;
 
 import java.util.List;
 import java.util.Map;
 import java.util.Properties;
 import java.util.Set;
 
 public class Student {
 
     private String name;
     private Address address;
     private String[] books;
     private List<String> hobbys;
     private Map<String,String> card;
     private Set<String> games;
     private String wife;
     private Properties info;
 
     public void setName(String name) {
         this.name = name;
    }
 
     public void setAddress(Address address) {
         this.address = address;
    }
 
     public void setBooks(String[] books) {
         this.books = books;
    }
 
     public void setHobbys(List<String> hobbys) {
         this.hobbys = hobbys;
    }
 
     public void setCard(Map<String, String> card) {
         this.card = card;
    }
 
     public void setGames(Set<String> games) {
         this.games = games;
    }
 
     public void setWife(String wife) {
         this.wife = wife;
    }
 
     public void setInfo(Properties info) {
         this.info = info;
    }
 
     public void show(){
         System.out.println("name="+ name
                 + ",address="+ address.getAddress()
                 + ",books="
        );
         for (String book:books){
             System.out.print("<<"+book+">>\t");
        }
         System.out.println("\n爱好:"+hobbys);
 
         System.out.println("card:"+card);
 
         System.out.println("games:"+games);
 
         System.out.println("wife:"+wife);
 
         System.out.println("info:"+info);
 
    }
 }
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815183308187.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


1、==常量注入==

```java
 <bean id="student" class="com.kuang.pojo.Student">
     <property name="name" value="小明"/>
 </bean>

```
测试：

```java
 @Test
 public void test01(){
     ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
 
     Student student = (Student) context.getBean("student");
 
     System.out.println(student.getName());
 
 }
```

2、==Bean注入== 

注意：这里的值是一个引用，ref

```css
 <bean id="addr" class="com.kuang.pojo.Address">
     <property name="address" value="重庆"/>
 </bean>
 
 <bean id="student" class="com.kuang.pojo.Student">
     <property name="name" value="小明"/>
     <property name="address" ref="addr"/>
 </bean>
```

3、数组注入

```css
 <bean id="student" class="com.kuang.pojo.Student">
     <property name="name" value="小明"/>
     <property name="address" ref="addr"/>
     <property name="books">
         <array>
             <value>西游记</value>
             <value>红楼梦</value>
             <value>水浒传</value>
         </array>
     </property>
 </bean>
```

4、List注入

```css
 <property name="hobbys">
     <list>
         <value>听歌</value>
         <value>看电影</value>
         <value>爬山</value>
     </list>
 </property>
```

5、Map注入

```css
 <property name="card">
     <map>
         <entry key="中国邮政" value="456456456465456"/>
         <entry key="建设" value="1456682255511"/>
     </map>
 </property>
```

6、set注入

```css
 <property name="games">
     <set>
         <value>LOL</value>
         <value>BOB</value>
         <value>COC</value>
     </set>
 </property>
```

7、Null注入

```css
 <property name="wife"><null/></property>
```

8、Properties注入

```css
 <property name="info">
     <props>
         <prop key="学号">20190604</prop>
         <prop key="性别">男</prop>
         <prop key="姓名">小明</prop>
     </props>
 </property>
```

测试结果：

```bash
Student{name='倾城', address=Address{address='吉安'}, 
books=[红楼梦, 西游记, 水浒传, 三国演义], 
hobbies=[听歌, 跳舞, 篮球], 
card={身份证=12345678, 手机号=1234567890},
 games=[LOL, CR, COC], 
 wife='null', 
 info={password=123456, driver=2020815, url=男, username=root}}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815214001821.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
##  三、拓展方式注入


### p命名和c命名注入
[官方文档地址](https://docs.spring.io/spring/docs/current/spring-framework-reference/core.html#beans-p-namespace)

User.java ：【注意：这里没有有参构造器！】

```java
 public class User {
     private String name;
     private int age;
 
     public void setName(String name) {
         this.name = name;
    }
 
     public void setAge(int age) {
         this.age = age;
    }
 
     @Override
     public String toString() {
         return "User{" +
                 "name='" + name + '\'' +
                 ", age=" + age +
                 '}';
    }
 }
```

1、P命名空间注入 : 需要在头文件中加入约束文件
 导入约束 : `xmlns:p="http://www.springframework.org/schema/p"`
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815214954640.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
 P(属性: properties)命名空间 , 属性依然要设置set方法

```bash
 <bean id="user" class="com.kuang.pojo.User" p:name="狂神" p:age="18"/>
```

2、c 命名空间注入 : 需要在头文件中加入约束文件

 导入约束 : `xmlns:c="http://www.springframework.org/schema/c"`
 C(构造: Constructor)命名空间 , 属性依然要设置set方法

```bash
 <bean id="user" class="com.kuang.pojo.User" c:name="狂神" c:age="18"/>
```

> 注意：爆红问题，原因：刚才我们没有写有参构造！
> 
> 解决：把有参构造器加上，这里也能知道，c 就是所谓的构造器注入！

总结： 设置有参构造后默认无参构造消失，set注入必须无参构造

测试代码：

```java
 @Test
 public void test02(){
     ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
     User user = (User) context.getBean("user");
     System.out.println(user);
 }
```
# Bean 的作用域
[官方文档](https://docs.spring.io/spring/docs/current/spring-framework-reference/core.html#beans-factory-scopes)

bean就是由IoC容器初始化、装配及管理的对象 

Bean 的作用域如下图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081522370055.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## 单例模式（Spring 默认）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815224031262.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```css
<bean id="user2" class="com.lzh.pojo.User" c:name="小熊" c:age="10" scope="singleton"/>
```

实际测试
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815224440787.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 原型模式
每一次从容器get的时候，都会产生一个新对象

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815225233418.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

实际测试
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815225217596.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```css
<bean id="user2" class="com.lzh.pojo.User" c:name="小熊" c:age="10" scope="prototype"/>
```

# 常见异常总结
## ①beans.xml  IO加载找不到
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815115058305.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
原因：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815115126522.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## ②路径报红
如下图红线所示
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815221410422.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
原因一、缺少`constructor-arg` 
原因二、实体类 User.java 缺少构造器

## ③加载Bean异常

```bash
 Exception encountered during context initialization - cancelling refresh attempt: org.springframework.beans.factory.UnsatisfiedDependencyException: Error creating bean with name 'user2' defined in class path resource [userbeans.xml]: Unsatisfied dependency expressed through constructor parameter 1: Ambiguous argument values for parameter of type [int] - did you specify the correct bean ref......
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815222905954.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
原因分析：在配置文件中bean 的参数错误

> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

