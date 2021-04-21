
**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫之远兮，简犹春天之临兮；
   劝君专注案前事，亦是杯酒敬苍生；

@[toc]
# Bean自动装配
**概述**：自动装配是使用spring满足bean依赖的一种方法，spring会在应用上下文中为某个bean寻找其依赖的bean。

==bean的三种装配机制==：

①在xml中显式配置；

②在java中显式配置；

③隐式的bean发现机制和自动装配。

## 装配bean自动化

**组件扫描**(component scanning)：spring会自动发现应用上下文中所创建的bean；

**自动装配**(autowiring)：spring自动满足bean之间的依赖，也就是我们说的IoC/DI；



推荐不使用自动装配xml配置 , 而使用注解 .



### 测试环境搭建
1、新建一个项目

2、新建两个实体类，Cat   Dog  都有一个叫的方法

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816145109622.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
3、新建一个用户类
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816145301879.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)



4、编写Spring配置文件

```css
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd">

<bean id="cat" class="com.lzh.pojo.Cat"/>
<bean id="dog" class="com.lzh.pojo.Dog"/>
<bean id="person" class="com.lzh.pojo.Person">
    <property name="name" value="倾城"/>
    <property name="dog" ref="dog"/>
    <property name="cat" ref="cat"/>

</bean>


</beans>
```

5、测试

```css
public class MyTest {
   @Test
   public void testMethodAutowire() {
       ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
       User user = (User) context.getBean("user");
       user.getCat().shout();
       user.getDog().shout();
  }
}
```


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816144904602.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


结果正常输出，环境OK
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816145500550.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### ByName自动装配
autowire byName (按名称自动装配)

**应用**：手动配置xml过程中，常常发生字母缺漏和大小写等错误，采用自动装配将避免这些错误，并且使配置简单化。

==测试==：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816151403639.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

1、修改bean配置，增加一个属性  autowire="byName"

```css
<bean id="person" class="com.lzh.pojo.Person"  autowire="byName">
    <property name="name" value="倾城"/>
</bean>
```

2、再次测试，结果依旧成功输出！



3、我们将 cat 的bean id修改为 catXXX，再次测试， 执行时报空指针`java.lang.NullPointerException`。因为按byName规则找不对应set方法，真正的setCat就没执行，对象就没有初始化，所以调用时就会报空指针错误。

**小结**：

1.当一个bean节点带有 autowire byName的属性时。将查找其类中所有的set方法名，例如setCat，获得将set去掉并且首字母小写的字符串，即cat。

2.去spring容器中寻找是否有此字符串名称id的对象。如果有，就取出注入；如果没有，就报空指针异常。

### ByType自动装配
autowire byType (按类型自动装配)

使用autowire byType首先需要保证：同一类型的对象，在spring容器中唯一。如果不唯一，会报不唯一的异常。`NoUniqueBeanDefinitionException`
测试：

1、将user的bean配置修改一下 ： autowire="byType"

2、测试，正常输出

3、模拟异常，在注册一个cat 的bean对象！

```css
<bean id="dog" class="com.kuang.pojo.Dog"/>
<bean id="cat" class="com.kuang.pojo.Cat"/>
<bean id="cat2" class="com.kuang.pojo.Cat"/>

<bean id="user" class="com.kuang.pojo.User" autowire="byType">
   <property name="str" value="倾城/>
</bean>
```

4、测试，报错：`NoUniqueBeanDefinitionException`

5、删掉cat2，将cat的bean名称改掉！测试！因为是按类型装配，所以并不会报异常，也不影响最后的结果。甚至将id属性去掉，也不影响结果。

这就是按照类型自动装配！


### 以上两者方式总结：
byName :  会自动在容器上下文中查找，和自己对象set方法后面的至对应的beanid
bgyType : 会自动在容器上下文中查找，和自己对象属性类型相同的bean



## 使用注解实现自动装配（核心）
[官方文档参考](https://docs.spring.io/spring/docs/current/spring-framework-reference/core.html#beans-annotation-config)

**前言**：jdk1.5开始支持注解，spring2.5开始全面支持注解。


### 使用步骤
1、导入约束。context 约束，在spring配置文件中引入context文件头
2、配置注解的支持  `<context:annotation-config/>`

```css
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:context="http://www.springframework.org/schema/context"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd">

    <context:annotation-config/>

</beans>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816170432897.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

3、开启属性注解支持！`@Autowired`，`@Autowired`是按类型自动转配的，不支持id匹配。

需要导入 spring-aop的包！


4、将User类中的set方法去掉，使用@Autowired注解

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816170738928.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)



### 注解拓展
1、`@Autowired(required=false)`  说明：false，对象可以为null；true，对象必须存对象，不能为null。

2、`@Autowired`是根据类型自动装配的，加上`@Qualifier`则可以根据byName的方式自动装配，`@Qualifier`不能单独使用。

3、`@Resource`如有指定的name属性，先按该属性进行byName方式查找装配；其次再进行默认的byName方式进行装配；如果以上都不成功，则按byType的方式自动装配。

### @Autowired与@Resource异同总结：
（拓展）
1、@Autowired与@Resource都可以用来装配bean。都可以写在字段上，或写在setter方法上。
2、@Autowired默认按类型装配（属于spring规范），默认情况下必须要求依赖对象必须存在，如果要允许null 值，可以设置它的required属性为false，如：@Autowired(required=false) ，如果我们想使用名称装配可以结合@Qualifier注解进行使用
3、@Resource（属于J2EE复返），默认按照名称进行装配，名称可以通过name属性进行指定。如果没有指定name属性，当注解写在字段上时，默认取字段名进行按照名称查找，如果注解写在setter方法上默认取属性名进行装配。当找不到与名称匹配的bean时才按照类型进行装配。但是需要注意的是，如果name属性一旦指定，就只会按照名称进行装配。
它们的作用相同都是用注解方式注入对象，但执行顺序不同。@Autowired先byType，@Resource先byName。


# 使用注解开发（重要）
## 基本使用步骤前序
在spring4之后，想要使用注解形式，必须得要引入aop的包

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816175612680.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


在配置文件当中，还需引入一个context约束

```css
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xmlns:context="http://www.springframework.org/schema/context"
      xsi:schemaLocation="http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd
       http://www.springframework.org/schema/context
       http://www.springframework.org/schema/context/spring-context.xsd">

</beans>
```

## Bean的实现
之前使用 bean 的标签进行bean注入，但是实际开发中，一般都会使用注解！

1、==配置扫描哪些包下的注解==
指定注解扫描包

```css
<context:component-scan base-package="com.kuang.pojo"/>
```

2、==在指定包下编写类，增加注解==
相当于配置文件中 `<bean id="user" class="当前注解的类"/>`
```java
@Component("user")
public class User {
   public String name = "倾城";
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081618350478.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

3、测试

```css
@Test
public void test(){
   ApplicationContext applicationContext =
       new ClassPathXmlApplicationContext("beans.xml");
   User user = (User) applicationContext.getBean("user");
   System.out.println(user.name);
}
```
### 衍生的注解
@Component  有以下衍生注解，在web开发中，按照mvc三层架构分层

dao `@Repository`
service  `@Service`
controller `@Controller`

此四个注解功能相同，代表将某个类注册到Spring中，装配Bean
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816193333897.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)



@Component三个衍生注解


@Controller：web层

@Service：service层

@Repository：dao层

写上这些注解，就相当于将这个类交给Spring管理装配了！
### 属性注入
使用注解注入属性

1、可以不用提供set方法，直接在直接名上添加@value("值")
```java
@Component("user")
// 相当于配置文件中 <bean id="user" class="当前注解的类"/>
public class User {
   @Value("LZH")
   // 相当于配置文件中 <property name="name" value="LZH"/>
   public String name;
}
```

2、如果提供了set方法，在set方法上添加@value("值");

```java
@Component("user")
public class User {

   public String name;

   @Value("LZH")
   public void setName(String name) {
       this.name = name;
  }
}
```



### 作用域

```bash
@scope
```

`singleton`：默认的，Spring会采用单例模式创建这个对象。关闭工厂 ，所有的对象都会销毁。

`prototype`：多例模式。关闭工厂 ，所有的对象不会销毁。内部的垃圾回收机制会回收

```java
@Controller("user")
@Scope("prototype")
public class User {
   @Value("LZH")
   public String name;
}
```

## XML与注解比较

1、XML可以适用任何场景 ，结构清晰，维护方便

2、注解不是自己提供的类使用不了，开发简单方便

3、xml管理Bean，注解完成属性注入



## 基于Java类进行配置
JavaConfig 通过 Java 类的方式提供 Bean 的定义信息，在 Spring4 的版本， JavaConfig 已正式成为 Spring4 的核心功能 。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816232538688.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

测试：

1、编写一个实体类，Dog

```java
@Component  //将这个类标注为Spring的一个组件，放到容器中！
public class Dog {
   public String name = "dog";
}
```

2、新建一个config配置包，编写一个MyConfig配置类

```java
@Configuration  //代表这是一个配置类
public class MyConfig {

   @Bean //通过方法注册一个bean，这里的返回值就Bean的类型，方法名就是bean的id！
   public Dog dog(){
       return new Dog();
  }

}
```

3、测试

```java
@Test
public void test2(){
   ApplicationContext applicationContext =
           new AnnotationConfigApplicationContext(MyConfig.class);
   Dog dog = (Dog) applicationContext.getBean("dog");
   System.out.println(dog.name);
}

```

功输出结果！
**再续实际实现**：

实体类与配置：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816233852169.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
测试代码：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816233758448.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 导入其他配置
==对应之前多个Bean的情况==

1、我们再编写一个配置类

```java
@Configuration  //代表这是一个配置类
public class MyConfig2 {
}
```

2、在之前的配置类中我们来选择导入这个配置类

```java
@Configuration
@Import(MyConfig2.class)  //导入合并其他配置类，类似于配置文件中的 inculde 标签
public class MyConfig {

   @Bean
   public Dog dog(){
       return new Dog();
  }

}
```

关于这种Java类的配置方式，SpringBoot 和 SpringCloud中经常使用
# 常见异常总结
## ①Bean未定义异常

```bash
Exception in thread "main" org.springframework.beans.factory.NoSuchBeanDefinitionException: No bean named 'user' available
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816182819389.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


## ②关于类导入异常

```bash
Configuration problem: A circular @Import has been detected: Illegal attempt by @Configuration class 'Appconfig' to import class 'Appconfig' as 'Appconfig' is already present in the current import stack [Appconfig]
Offending resource: com.lzh.config.Appconfig......
```
原因如下图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816234656136.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)



> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

