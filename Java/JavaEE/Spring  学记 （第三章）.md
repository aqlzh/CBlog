**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫之远兮，运架构体之帷幄；
劝君专注案前事，亦是杯酒敬苍生；


@[toc]
# 代理模式
**前序**：AOP的底层机制就是动态代理

==代理模式分类==：

①静态代理    ②动态代理


## 静态代理
（1）抽象角色 : 一般使用接口或者抽象类来实现

（2）真实角色 : 被代理的角色

（3）代理角色 : 代理真实角色 ; 代理真实角色后 , 一般会做一些附属的操作 .

（4）客户  :  使用代理角色来进行一些操作 .

平常方式实现：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817115730543.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

静态代理实现：

`Rent . java` 即抽象角色

```java
//抽象角色：租房
public interface Rent {
   public void rent();
}
```

`Host . java` 即真实角色
```java
//真实角色: 房东，房东要出租房子
public class Host implements Rent{
   public void rent() {
       System.out.println("房屋出租");
  }
}
```

`Proxy . java` 即代理角色

```java
//代理角色：中介
public class Proxy implements Rent {

   private Host host;
   public Proxy() { }
   public Proxy(Host host) {
       this.host = host;
  }

   //租房
   public void rent(){
       seeHouse();
       host.rent();
       fare();
  }
   //看房
   public void seeHouse(){
       System.out.println("带房客看房");
  }
   //收中介费
   public void fare(){
       System.out.println("收中介费");
  }
}
```
`Client . java` 即客户

```java
//客户类，一般客户都会去找代理！
public class Client {
   public static void main(String[] args) {
       //房东要租房
       Host host = new Host();
       //中介帮助房东
       Proxy proxy = new Proxy(host);

       //你去找中介！
       proxy.rent();
  }
}
```
实际代码效果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817121917363.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


### 静态代理的好处与缺点:

（1）可以使得我们的真实角色更加纯粹 . 不再去关注一些公共的事情 .

（2）公共的业务由代理来完成 . 实现了业务的分工 ,

（3）公共业务发生扩展时变得更加集中和方便 .

缺点 :

类多了 , 多了代理类 , 工作量变大了 . 开发效率降低 .

---> 解决上述问题： 动态代理



### 代理模式的实际运用
1、创建一个抽象角色，，抽象-->==增删改查==

```java
//抽象角色：增删改查业务
public interface UserService {
   void add();
   void delete();
   void update();
   void query();
}
```

2、真实对象来完成这些增删改查操作

```java
//真实对象，完成增删改查操作的人
public class UserServiceImpl implements UserService {

   public void add() {
       System.out.println("增加了一个用户");
  }

   public void delete() {
       System.out.println("删除了一个用户");
  }

   public void update() {
       System.out.println("更新了一个用户");
  }

   public void query() {
       System.out.println("查询了一个用户");
  }
}
```

3、增加一个日志功能，怎么实现！

原来方法 ：在实现类上增加代码 【麻烦！】

==现在方法==：使用代理，具体如下
4、设置一个代理类来处理日志！代理角色

```java
//代理角色，在这里面增加日志的实现
public class UserServiceProxy implements UserService {
   private UserServiceImpl userService;

   public void setUserService(UserServiceImpl userService) {
       this.userService = userService;
  }

   public void add() {
       log("add");
       userService.add();
  }

   public void delete() {
       log("delete");
       userService.delete();
  }

   public void update() {
       log("update");
       userService.update();
  }

   public void query() {
       log("query");
       userService.query();
  }

   public void log(String msg){
       System.out.println("执行了"+msg+"方法");
  }

}
```

5、测试访问类：

```java
public class Client {
   public static void main(String[] args) {
       //真实业务
       UserServiceImpl userService = new UserServiceImpl();
       //代理类
       UserServiceProxy proxy = new UserServiceProxy();
       //使用代理类实现日志功能！
       proxy.setUserService(userService);

       proxy.add();
  }
}
```
**总结**：在不破坏原有代码的基础上，利用”织入“的模式实现代码的动态配置
### AOP：纵向开发，横向开发（图示）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817135020858.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## 动态代理
### 与静态代理的异同
**同**：
动态代理的角色和静态代理一样 
（1）抽象角色 : 一般使用接口或者抽象类来实现

（2）真实角色 : 被代理的角色

（3）代理角色 : 代理真实角色 ; 代理真实角色后 , 一般会做一些附属的操作 .

（4）客户  :  使用代理角色来进行一些操作 .


**异**：
（1）动态代理的代理类是动态生成的 . 静态代理的代理类是我们提前写好的

（2）==动态代理分为两类== : 一类是基于**接口**动态代理（JDK动态代理） , 一类是基于**类**的动态代理（cglib）

### JDK动态代理
 其他需了解：javasist 动态代理 (基于字节码)

>  https://baike.baidu.com/item/JAVAssist/6039181

JDK的动态代理需要了解两个类

核心 : InvocationHandler     和     Proxy   ， 参考JDK帮助文档
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817140833735.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

【InvocationHandler：调用处理程序】



```bash
Object invoke(Object proxy, 方法 method, Object[] args)；
```
上述方法参数分析：
`proxy` - 调用该方法的代理实例
`method` -所述方法对应于调用代理实例上的接口方法的实例。方法对象的声明类将是该方法声明的接口，它可以是代理类继承该方法的代理接口的超级接口。
`args` -包含的方法调用传递代理实例的参数值的对象的阵列，或null如果接口方法没有参数。原始类型的参数包含在适当的原始包装器类的实例中，例如java.lang.Integer或java.lang.Boolean 。
#### Proxy 代理方式

```java
//生成代理类
public Object getProxy(){
   return Proxy.newProxyInstance(this.getClass().getClassLoader(),
                                 rent.getClass().getInterfaces(),this);
}
```

代码实现 


Rent . java 即抽象角色

```java
//抽象角色：租房
public interface Rent {
   public void rent();
}
```

Host . java 即真实角色

```java
//真实角色: 房东，房东要出租房子
public class Host implements Rent{
   public void rent() {
       System.out.println("房屋出租");
  }
}
```

ProxyInvocationHandler. java 即代理角色

```java
public class ProxyInvocationHandler implements InvocationHandler {
   private Rent rent;

   public void setRent(Rent rent) {
       this.rent = rent;
  }

   //生成代理类，重点是第二个参数，获取要代理的抽象角色！之前都是一个角色，现在可以代理一类角色
   public Object getProxy(){
       return Proxy.newProxyInstance(this.getClass().getClassLoader(),
               rent.getClass().getInterfaces(),this);
  }
     // proxy : 代理类 method : 代理类的调用处理程序的方法对象.
   // 处理代理实例上的方法调用并返回结果
   @Override
   public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
       seeHouse();
       //核心：本质利用反射实现！
       Object result = method.invoke(rent, args);
       fare();
       return result;
  }

```

Client . java

```java
//租客
public class Client {

   public static void main(String[] args) {
       //真实角色
       Host host = new Host();
       //代理实例的调用处理程序
       ProxyInvocationHandler pih = new ProxyInvocationHandler();
       pih.setRent(host); //将真实角色放置进去！
       Rent proxy = (Rent)pih.getProxy(); //动态生成对应的代理类！
       proxy.rent();
  }

}
```

**总结**：一个动态代理 , 一般代理某一类业务 , 一个动态代理可以代理多个类，代理的是接口！、

==代码优化==
使用动态代理实现代理后面的UserService！

编写一个通用的动态代理实现的类！所有的代理对象设置为Object即可！

```java
public class ProxyInvocationHandler implements InvocationHandler {
   private Object target;

   public void setTarget(Object target) {
       this.target = target;
  }

   //生成代理类
   public Object getProxy(){
       return Proxy.newProxyInstance(this.getClass().getClassLoader(),
               target.getClass().getInterfaces(),this);
  }

   // proxy : 代理类
   // method : 代理类的调用处理程序的方法对象.
   public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
       log(method.getName());
       Object result = method.invoke(target, args);
       return result;
  }

   public void log(String methodName){
       System.out.println("执行了"+methodName+"方法");
  }

}
```

测试！

```java
public class Test {
   public static void main(String[] args) {
       //真实对象
       UserServiceImpl userService = new UserServiceImpl();
       //代理对象的调用处理程序
       ProxyInvocationHandler pih = new ProxyInvocationHandler();
       pih.setTarget(userService); //设置要代理的对象
       UserService proxy = (UserService)pih.getProxy(); //动态生成代理类！
       proxy.delete();
  }
}
```
实体类与接口：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081716120953.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

实际体现：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817160806311.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


### 动态代理优点

（1）可以使得我们的真实角色更加纯粹 . 不再去关注一些公共的事情 .

（2）公共的业务由代理来完成 . 实现了业务的分工 ,

（3）公共业务发生扩展时变得更加集中和方便 .

（4）一个动态代理 , 一般代理某一类业务

（5）一个动态代理可以代理多个类，代理的是接口！

# AOP技术
AOP（Aspect Oriented Programming）意为：==面向切面编程==，通过预编译方式和运行期**动态代理**实现程序功能的统一维护的一种技术。AOP是OOP的延续，是软件开发中的一个热点，也是Spring框架中的一个重要内容，是**函数式编程的一种衍生范型**。利用AOP可以对业务逻辑的各个部分进行隔离，从而使得业务逻辑各部分之间的耦合度降低，提高程序的可重用性，同时提高了开发的效率。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817175848699.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## AOP 在Spring中的作用
提供声明式事务；允许用户自定义切面
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817181506197.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

Before  
After
AfterRunning
 AfterThorwing
  Around
#### 重要名词

==横切关注点==：跨越应用程序多个模块的方法或功能。即是，与我们业务逻辑无关的，但是我们需要关注的部分，就是横切关注点。如日志 , 安全 , 缓存 , 事务等等 ....

==切面==（ASPECT）：横切关注点 被模块化 的特殊对象。即，它是一个类。

==通知==（Advice）：切面必须要完成的工作。即，它是类中的一个方法。

==目标==（Target）：被通知对象。

==代理==（Proxy）：向目标对象应用通知之后创建的对象。

==切入点==（PointCut）：切面通知 执行的 “地点”的定义。

==连接点==（JointPoint）：与切入点匹配的执行点。

SpringAOP中，通过Advice定义横切逻辑，Spring中支持5种类型的Advice:
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817181623390.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817184242119.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## 使用Spring实现AOP
### 法一：通过 Spring API 实现
业务接口

```java
public interface UserService {

   public void add();

   public void delete();

   public void update();

   public void search();

}
```
实现类

```java
public class UserServiceImpl implements UserService{

   @Override
   public void add() {
       System.out.println("增加用户");
  }

   @Override
   public void delete() {
       System.out.println("删除用户");
  }

   @Override
   public void update() {
       System.out.println("更新用户");
  }

   @Override
   public void search() {
       System.out.println("查询用户");
  }
}
```

==编写两个增强类 , , 一个前置增强 一个后置增强==

```java
public class Log implements MethodBeforeAdvice {

   //method : 要执行的目标对象的方法
   //objects : 被调用的方法的参数
   //Object : 目标对象
   @Override
   public void before(Method method, Object[] objects, Object o) throws Throwable {
       System.out.println( o.getClass().getName() + "的" + method.getName() + "方法被执行了");
  }
}
```

```java
public class AfterLog implements AfterReturningAdvice {
   //returnValue 返回值
   //method被调用的方法
   //args 被调用的方法的对象的参数
   //target 被调用的目标对象
   @Override
   public void afterReturning(Object returnValue, Method method, Object[] args, Object target) throws Throwable {
       System.out.println("执行了" + target.getClass().getName()
       +"的"+method.getName()+"方法,"
       +"返回值："+returnValue);
  }
}
```

在spring中注册 , 并实现aop切入实现 , 注意导入约束 .

```css
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd
       http://www.springframework.org/schema/aop
       http://www.springframework.org/schema/aop/spring-aop.xsd">

    <!--注册bean-->
    <bean id="userService" class="com.lzh.service.UserServiceImpl"/>
    <bean id="log" class="com.lzh.log.Log"/>
    <bean id="afterLog" class="com.lzh.log.AfterLog"/>

    <!--aop的配置-->
    <aop:config>
        <!--切入点 expression:表达式匹配要执行的方法-->
        <aop:pointcut id="pointcut" expression="execution(* com.lzh.service.UserServiceImpl.*(..))"/>
        <!--执行环绕; advice-ref执行方法 . pointcut-ref切入点-->
        <aop:advisor advice-ref="log" pointcut-ref="pointcut"/>
        <aop:advisor advice-ref="afterLog" pointcut-ref="pointcut"/>
    </aop:config>

</beans>
```

测试类

```java
public class MyTest {
   @Test
   public void test(){
       ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
       UserService userService = (UserService) context.getBean("userService");
       userService.search();
  }
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817210828823.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 法二、通过自定义类来实现Aop
目标业务类不变为`userServiceImpl。java`

第一步 : 写我们自己的一个切入类

```java
public class DiyPointcut {

   public void before(){
       System.out.println("---------方法执行前---------");
  }
   public void after(){
       System.out.println("---------方法执行后---------");
  }
   
}
```

去spring中配置

```css
    <!--第二种方式自定义实现-->
    <!--注册bean-->
    <bean id="diy" class="com.lzh.config.DiyPointcut"/>

    <!--aop的配置-->
    <aop:config>
        <!--第二种方式：使用AOP的标签实现-->
        <aop:aspect ref="diy">
            <aop:pointcut id="diyPonitcut" expression="execution(* com.lzh.service.UserServiceImpl.*(..))"/>
            <aop:before pointcut-ref="diyPonitcut" method="before"/>
            <aop:after pointcut-ref="diyPonitcut" method="after"/>
        </aop:aspect>
    </aop:config>
</beans>
```

测试：

```java
public class MyTest {
   @Test
   public void test(){
       ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
       UserService userService = (UserService) context.getBean("userService");
       userService.add();
  }
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818000715554.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


### 法三、使用注解实现

1、第一步：编写一个注解实现的增强类

```java
package com.kuang.config;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;

@Aspect
public class AnnotationPointcut {
   @Before("execution(* com.kuang.service.UserServiceImpl.*(..))")
   public void before(){
       System.out.println("---------方法执行前---------");
  }

   @After("execution(* com.kuang.service.UserServiceImpl.*(..))")
   public void after(){
       System.out.println("---------方法执行后---------");
  }

   @Around("execution(* com.kuang.service.UserServiceImpl.*(..))")
   public void around(ProceedingJoinPoint jp) throws Throwable {
       System.out.println("环绕前");
       System.out.println("签名:"+jp.getSignature());


       //执行目标方法proceed
       Object proceed = jp.proceed();
       System.out.println("环绕后");
       System.out.println(proceed);
  }
}
```

第二步：在Spring配置文件中，注册bean，并增加支持注解的配置

```css
  <!--第三种方式:注解实现-->
    <bean id="annotationPointcut" class="com.lzh.config.AnnotationPointCut"/>
<!--    开启注解支持  JDK(默认 proxy-target-class="false" cglib( proxy-target-class="true"))-->
    <aop:aspectj-autoproxy proxy-target-class="false"/>
```

**注意**：这里没有执行方法（输出结果没有显示前两个方法）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818110428894.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
==注意==：在配置文件中还有注册bean

```css
  <!--注册bean-->
    <bean id="userService" class="com.lzh.service.UserServiceImpl"/>
    <bean id="log" class="com.lzh.log.Log"/>
    <bean id="afterLog" class="com.lzh.log.AfterLog"/>
```
**后续**：添加执行方法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818111613402.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


**详解**：
通过aop命名空间的`<aop:aspectj-autoproxy />`声明自动为spring容器中那些配置`@aspectJ`切面的bean创建代理，织入切面。spring 在内部依旧采用`AnnotationAwareAspectJAutoProxyCreator`进行自动代理的创建工作，但具体实现的细节已经被`<aop:aspectj-autoproxy />`隐藏起来了

`<aop:aspectj-autoproxy />`有一个proxy-target-class属性，默认为false，表示使用jdk动态代理织入增强，当配为`<aop:aspectj-autoproxy  poxy-target-class="true"/>`时，表示使用CGLib动态代理技术织入增强。不过即使proxy-target-class设置为false，如果目标类没有声明接口，则spring将自动使用CGLib动态代理。



**总述**：Spring的Aop就是将公共的业务 (日志 , 安全等) 和领域业务结合起来 , 当执行领域业务时 , 将会把公共业务加进来 . 实现公共业务的重复利用 . 领域业务更纯粹 , 是我们专注领域业务 , 其本质还是动态代理 . 


# 整合Mybatis 技术
## 一、导入相关jar包

junit

```css
<dependency>
   <groupId>junit</groupId>
   <artifactId>junit</artifactId>
   <version>4.12</version>
</dependency>
```

mybatis

```css
<dependency>
   <groupId>org.mybatis</groupId>
   <artifactId>mybatis</artifactId>
   <version>3.5.2</version>
</dependency>
```

mysql-connector-java

```css
<dependency>
   <groupId>mysql</groupId>
   <artifactId>mysql-connector-java</artifactId>
   <version>5.1.47</version>
</dependency>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818120201554.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

spring相关

```css
<dependency>
   <groupId>org.springframework</groupId>
   <artifactId>spring-webmvc</artifactId>
   <version>5.1.10.RELEASE</version>
</dependency>
<dependency>
   <groupId>org.springframework</groupId>
   <artifactId>spring-jdbc</artifactId>
   <version>5.1.10.RELEASE</version>
</dependency>
```

aspectJ AOP 织入器

```css
<!-- https://mvnrepository.com/artifact/org.aspectj/aspectjweaver -->
<dependency>
   <groupId>org.aspectj</groupId>
   <artifactId>aspectjweaver</artifactId>
   <version>1.9.4</version>
</dependency>
```

mybatis-spring整合包 【重点】

```css
<dependency>
   <groupId>org.mybatis</groupId>
   <artifactId>mybatis-spring</artifactId>
   <version>2.0.2</version>
</dependency>
```

==配置Maven静态资源过滤问题==

```css
<build>
   <resources>
       <resource>
           <directory>src/main/java</directory>
           <includes>
               <include>**/*.properties</include>
               <include>**/*.xml</include>
           </includes>
           <filtering>true</filtering>
       </resource>
   </resources>
</build>
```
lombok

```css
   <!-- https://mvnrepository.com/artifact/org.projectlombok/lombok -->
    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <version>1.18.2</version>
        <scope>provided</scope>

    </dependency>
```

## 二、编写Mybatis 具体内容
1、编写实体类
2、编写核心配置文件
3、编写接口
4、编写Mapper.xml
5、测试T'lo'm'bo'k
S
## Mybatis-Spring 技术
作用：MyBatis-Spring 将 MyBatis 代码无缝地整合到 Spring 中。

mybatis-spring包中的一些重要类；

> http://www.mybatis.org/spring/zh/index.html


==MyBatis-Spring 需要以下版本：==

| Mybatis-Spring | Mybatis | Spring | Spring Batch | Java    |
| -------------- | ------- | ------ | ------------ | ------- |
| 2.0            | 3.5+    | 5.0+   | 4.0+         | Java 8+ |
| 1.3            | 3.4+    | 3.2.2+ | 2.1+         | Java 6+ |

使用 Maven 作为构建工具，仅需要在 pom.xml 导入以下代码：

```css
<dependency>
   <groupId>org.mybatis</groupId>
   <artifactId>mybatis-spring</artifactId>
   <version>2.0.2</version>
</dependency>
```
将Mybatis整合至Spring前提:
一个 SqlSessionFactory 和至少一个数据映射器类。

在 MyBatis-Spring 中，可使用SqlSessionFactoryBean来创建 SqlSessionFactory。要配置这个工厂 bean代码如下：
```css
<bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
 <property name="dataSource" ref="dataSource" />
</bean>
```

### 注意异同比较：
（1）`SqlSessionFactory`需要一个 DataSource（数据源）。
（2）MyBatis 中，是通过 `SqlSessionFactoryBuilder` 来创建 SqlSessionFactory 的。而在 MyBatis-Spring 中，则使用 `SqlSessionFactoryBean` 来创建。
（3）在 MyBatis 中，使用 SqlSessionFactory 来创建 SqlSession。一旦获得一个 session 之后，可以使用它来执行映射了的语句，提交或回滚连接，最后，当不再需要它的时候，可以关闭 session。
（4）SqlSessionFactory**唯一必要**的属性：用于 JDBC 的 DataSource。这可以是任意的 DataSource 对象，它的配置方法和其它 Spring 数据库连接是一样的。
（5）属性 `configLocation`，它用来指定 MyBatis 的 XML 配置文件路径。它在需要修改 MyBatis 的基础配置非常有用。通常，基础配置指的是 < settings> 或 < typeAliases>元素。

**注意**：配置文件并不需要是一个完整的 MyBatis 配置。确切地说，任何环境配置（`<environments>`），数据源（`<DataSource>`）和 MyBatis 的事务管理器（`<transactionManager>`）都会被忽略。`SqlSessionFactoryBean` 会创建它自有的 MyBatis 环境配置（Environment），并按要求设置自定义环境的值。

`SqlSessionTemplate` 是 MyBatis-Spring 的核心。作为 SqlSession 的一个实现，这意味着可以使用它无缝代替你代码中已经在使用的 SqlSession。


```css
<bean id="sqlSession" class="org.mybatis.spring.SqlSessionTemplate">
 <constructor-arg index="0" ref="sqlSessionFactory" />
</bean>
```

 bean 已经直接注入到的 DAO bean 中了。 bean 中添加一个 SqlSession 属性，如下：

```java
public class UserDaoImpl implements UserDao {

 private SqlSession sqlSession;

 public void setSqlSession(SqlSession sqlSession) {
   this.sqlSession = sqlSession;
}

 public User getUser(String userId) {
   return sqlSession.getMapper...;
}
}
```

注入 SqlSessionTemplate：

<bean id="userDao" class="org.mybatis.spring.sample.dao.UserDaoImpl">
 <property name="sqlSession" ref="sqlSession" />
</bean>


### 整合实现一
1、引入Spring配置文件beans.xml

```css
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd">
```

2、配置数据源替换mybaits的数据源

```css
<!--配置数据源：数据源有非常多，可以使用第三方的，也可使使用Spring的-->
<bean id="dataSource" class="org.springframework.jdbc.datasource.DriverManagerDataSource">
   <property name="driverClassName" value="com.mysql.jdbc.Driver"/>
   <property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=true&amp;useUnicode=true&amp;characterEncoding=utf8"/>
   <property name="username" value="root"/>
   <property name="password" value="123456"/>
</bean>
```

3、配置SqlSessionFactory，关联MyBatis

```css
<!--配置SqlSessionFactory-->
<bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
   <property name="dataSource" ref="dataSource"/>
   <!--关联Mybatis-->
   <property name="configLocation" value="classpath:mybatis-config.xml"/>
   <property name="mapperLocations" value="classpath:com/kuang/dao/*.xml"/>
</bean>
```

4、注册sqlSessionTemplate，关联sqlSessionFactory；

```css
<!--注册sqlSessionTemplate , 关联sqlSessionFactory-->
<bean id="sqlSession" class="org.mybatis.spring.SqlSessionTemplate">
   <!--利用构造器注入-->
   <constructor-arg index="0" ref="sqlSessionFactory"/>
</bean>
```

5、增加Dao接口的实现类；私有化sqlSessionTemplate

```css
public class UserDaoImpl implements UserMapper {

   //sqlSession不用我们自己创建了，Spring来管理
   private SqlSessionTemplate sqlSession;

   public void setSqlSession(SqlSessionTemplate sqlSession) {
       this.sqlSession = sqlSession;
  }

   public List<User> selectUser() {
       UserMapper mapper = sqlSession.getMapper(UserMapper.class);
       return mapper.selectUser();
  }
   
}
```

6、注册bean实现

```css
<bean id="userDao" class="com.kuang.dao.UserDaoImpl">
   <property name="sqlSession" ref="sqlSession"/>
</bean>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818204900583.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

7、测试

```css
   @Test
   public void test2(){
       ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
       UserMapper mapper = (UserMapper) context.getBean("userDao");
       List<User> user = mapper.selectUser();
       System.out.println(user);
  }
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818204747696.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

现在我们的Mybatis配置文件的状态，被Spring整合

```css
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
       PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
       "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
   <typeAliases>
       <package name="com.kuang.pojo"/>
   </typeAliases>
</configuration>
```

### 整合实现二
支持mybatis-spring1.2.3以上版本


dao继承Support类 , 直接利用 `getSqlSession()` 获得 , 然后直接注入`SqlSessionFactory` . 比起方式1 , 不需要管理`SqlSessionTemplate` , 而且对事务的支持更加友好 . 可跟踪源码查看


1、修改上面写的UserDaoImpl

```java
public class UserDaoImpl extends SqlSessionDaoSupport implements UserMapper {
   public List<User> selectUser() {
       UserMapper mapper = getSqlSession().getMapper(UserMapper.class);
       return mapper.selectUser();
  }
}
```

2、修改bean的配置

```java
<bean id="userDao" class="com.kuang.dao.UserDaoImpl">
   <property name="sqlSessionFactory" ref="sqlSessionFactory" />
</bean>
3、测试
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818210347797.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

@Test

```java
public void test2(){
   ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
   UserMapper mapper = (UserMapper) context.getBean("userDao");
   List<User> user = mapper.selectUser();
   System.out.println(user);
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818210315323.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

**总结** : 整合到spring以后可以完全不要mybatis的配置文件

# Spring与事务
**概述**：事务管理是企业级应用程序开发中必备技术，用来确保数据的完整性和一致性。事务就是把一系列的动作当成一个独立的工作单元，这些动作要么全部完成，要么全部不起作用。

## 事务四个属性ACID

==原子性==（atomicity）事务是原子性操作，由一系列动作组成，事务的原子性确保动作要么全部完成，要么完全不起作用

==一致性==（consistency）一旦所有事务动作完成，事务就要被提交。数据和资源处于一种满足业务规则的一致性状态中

==隔离性==（isolation）可能多个事务会同时处理相同的数据，因此每个事务都应该与其他事务隔离开来，防止数据损坏

==持久性==（durability）事务一旦完成，无论系统发生什么错误，结果都不会受到影响。通常情况下，事务的结果被写到持久化存储器中

在之前的案例中，我们给userDao接口新增两个方法，删除和增加用户；

```java
//添加一个用户
int addUser(User user);

//根据id删除用户
int deleteUser(int id);
mapper文件，我们故意把 deletes 写错，测试！

<insert id="addUser" parameterType="com.kuang.pojo.User">
insert into user (id,name,pwd) values (#{id},#{name},#{pwd})
</insert>

<delete id="deleteUser" parameterType="int">
deletes from user where id = #{id}
</delete>
```

编写接口的实现类

```java
public class UserDaoImpl extends SqlSessionDaoSupport implements UserMapper {

   //增加一些操作
   public List<User> selectUser() {
       User user = new User(4,"小明","123456");
       UserMapper mapper = getSqlSession().getMapper(UserMapper.class);
       mapper.addUser(user);
       mapper.deleteUser(4);
       return mapper.selectUser();
  }

   //新增
   public int addUser(User user) {
       UserMapper mapper = getSqlSession().getMapper(UserMapper.class);
       return mapper.addUser(user);
  }
   //删除
   public int deleteUser(int id) {
       UserMapper mapper = getSqlSession().getMapper(UserMapper.class);
       return mapper.deleteUser(id);
  }

}
```

测试类

```java
@Test
public void test2(){
   ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
   UserMapper mapper = (UserMapper) context.getBean("userDao");
   List<User> user = mapper.selectUser();
   System.out.println(user);
}
```
配置图示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081913131438.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819131724826.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
接口图示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/202008191318164.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## Spring中的事务管理
Spring在不同的事务管理API之上定义了一个抽象层，使得开发人员不必了解底层的事务管理API就可以使用Spring的事务管理机制。**Spring支持编程式事务管理和声明式的事务管理。**

### 编程式事务管理

将事务管理代码嵌到业务方法中来控制事务的==提交==和==回滚==

缺点：必须在每个事务操作业务逻辑中包含额外的事务管理代码

### 声明式事务管理（常用）

将事务管理代码从业务方法中分离出来，以声明的方式来实现事务管理。

将事务管理作为横切关注点，通过aop方法模块化。Spring中通过Spring AOP框架支持声明式事务管理。

使用Spring管理事务，注意头文件的约束导入 : `tx`

```css
xmlns:tx="http://www.springframework.org/schema/tx"

http://www.springframework.org/schema/tx
http://www.springframework.org/schema/tx/spring-tx.xsd">
```

### 事务管理器

无论使用Spring的哪种事务管理策略（编程式或者声明式）事务管理器都是必须的。

就是 Spring的核心事务管理抽象，管理封装了一组独立于技术的方法。

JDBC事务

```css
<bean id="transactionManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
       <property name="dataSource" ref="dataSource" />
</bean>
```

配置好事务管理器后我们需要去配置事务的通知

```css
<!--配置事务通知-->
<tx:advice id="txAdvice" transaction-manager="transactionManager">
   <tx:attributes>
       <!--配置哪些方法使用什么样的事务,配置事务的传播特性-->
       <tx:method name="add" propagation="REQUIRED"/>
       <tx:method name="delete" propagation="REQUIRED"/>
       <tx:method name="update" propagation="REQUIRED"/>
       <tx:method name="search*" propagation="REQUIRED"/>
       <tx:method name="get" read-only="true"/>
       <tx:method name="*" propagation="REQUIRED"/>
   </tx:attributes>
</tx:advice>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081913415520.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### spring事务传播特性：

事务传播行为就是多个事务方法相互调用时，事务如何在这些方法间传播。spring支持7种事务传播行为：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819132255378.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

`propagation_requierd`：如果当前没有事务，就新建一个事务，如果已存在一个事务中，加入到这个事务中，这是最常见的选择。（==默认的事务传播行为==）

`propagation_supports`：支持当前事务，如果没有当前事务，就以非事务方法执行。

`propagation_mandatory`：使用当前事务，如果没有当前事务，就抛出异常。

`propagation_required_new`：新建事务，如果当前存在事务，把当前事务挂起。

`propagation_not_supported`：以非事务方式执行操作，如果当前存在事务，就把当前事务挂起。

`propagation_never`：以非事务方式执行操作，如果当前事务存在则抛出异常。

`propagation_nested`：如果当前存在事务，则在嵌套事务内执行。如果当前没有事务，则执行与propagation_required类似的操作



### 配置AOP

在`spring-dao.xml`导入aop的头文件！

```css
<!--配置aop织入事务-->
<aop:config>
   <aop:pointcut id="txPointcut" expression="execution(* com.lzh.dao.*.*(..))"/>
   <aop:advisor advice-ref="txAdvice" pointcut-ref="txPointcut"/>
</aop:config>
```

进行测试

删掉刚才插入的数据，再次测试！

```css
@Test
public void test2(){
   ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
   UserMapper mapper = (UserMapper) context.getBean("userDao");
   List<User> user = mapper.selectUser();
   System.out.println(user);
}
```

# 常见异常与错误总结
## ①未有输出结果
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817134042813.png#pic_center)
原因：①在测试类中关键语句缺失
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817134222625.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
②在代理类中核心方法缺失
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200817134327275.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## ②未找到方法调用Resource资源...报错
未找到方法调用Resource.getResourceAsStream（资源）的候选人
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818135710485.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
解法：在其中添加一个`class`
## ③已声明但未找到模块
Error:(3, 20) java: 程序包 jdk.internal.loader 不可见
  (程序包 jdk.internal.loader 已在模块 java.base 中声明, 但该模块未将它导出到未命名模块)
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818140621426.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200818140609149.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## ④transaction-manager报红

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819133928295.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
解决如下：忘记导入相应文件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819133959463.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

