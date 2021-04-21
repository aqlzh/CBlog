**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# 配置文件
## 配置文件中值的获取
一、在`pom.xml`中导入配置文件处理器，配置文件进行绑定就会有提示
```xml
	
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-configuration-processor</artifactId>
	<optional>true</optional>
</dependency>
```
二、配置文件

法一：`application.yml`
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082618251689.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
法二：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826183330953.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

三、javaBean 文件（上侧）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826182746715.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


==注意==：在Test文件夹下执行
SpringBoot 单元测试  可以再测试期间类似于编码一样进行自动注入
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826181821755.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 各项配置详解
### 一、@Value获取值和@ConfigurationProperties获取值

|                      | @ConfigurationProperties | @Value     |
| -------------------- | ------------------------ | ---------- |
| 功能                 | 批量注入配置文件中的属性 | 一个个指定 |
| 松散绑定（松散语法） | 支持                     | 不支持     |
| SpEL                 | 不支持                   | 支持       |
| JSR303数据校验       | 支持                     | 不支持     |
| 复杂类型封装         | 支持                     | 不支持     |

==注意==：
（1）松散绑定规则如下图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826190837858.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
（2）其中`@Value()`,相当于以下Spring 中原生代码

```xml
<bean class="Person">
  <property name="lastName value="***"> 
</bean>
```
其中上述*** 可以代替为  
①字面量（数字，字符串，布尔值）
②${key}  从环境变量 、配置文件中获取的值
③#{SpEL}   Spring表达式

(3)配置文件yml还是properties他们都能获取到值；

(4)复杂类型  --->   eg:  map List 等

**使用情况**：
①简易，我们只是在某个业务逻辑中需要获取一下配置文件中的某项值，使用`@Value`；（如下图）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826190649410.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


②复杂，我们专门编写了一个javaBean来和配置文件进行映射，我们就直接使用`@ConfigurationProperties`；


### 二、@PropertySource&@ImportResource&@Bean
**前言**：@ConfigurationProperties(prefix="person") 默认从全局配置文件中获取值

@**PropertySource**：加载指定的配置文件；

```java
@PropertySource(value = {"classpath:person.properties"})
```



@**ImportResource**：导入Spring的配置文件，让配置文件里面的内容生效；标注在一个配置类上（位置如下图所示）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826203627288.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)




```java
@ImportResource(locations = {"classpath:beans.xml"})
```



之前方法：编写Spring的配置文件

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">


    <bean id="helloService" class="com.atguigu.springboot.service.HelloService"></bean>
</beans>
```
#### 推荐用法（重要）

1、配置类`@Configuration`------>Spring配置文件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826204102287.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
在之前bean配置中的id 默认为方法的返回值（关系如下图）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826204856397.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

2、使用@Bean给容器中添加组件

```java
/**
 * @Configuration：指明当前类是一个配置类；就是来替代之前的Spring配置文件
 *
 * 在配置文件中用<bean><bean/>标签添加组件
 *
 */
@Configuration
public class MyAppConfig {

    //将方法的返回值添加到容器中；容器中这个组件默认的id就是方法名
    @Bean
    public HelloService helloService02(){
        System.out.println("配置类@Bean给容器中添加组件了...");
        return new HelloService();
    }
}
```

3、在Test 文件夹下进行测试
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826204226237.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 随机占位符
1、 随机数

```java
${random.value}、${random.int}、${random.long}
${random.int(10)}、${random.int[1024,65536]}

```



==注意==：占位符获取之前配置的值，如果没有可以是用:指定默认值
${person.hello:hello}  中的hello就是默认值

```properties
person.last-name=张三${random.uuid}
person.age=${random.int}
person.birth=2017/12/15
person.boss=false
person.maps.k1=v1
person.maps.k2=14
person.lists=a,b,c
person.dog.name=${person.hello:hello}_dog
person.dog.age=15
```

## Profile（多文件配置）
### 普通方法
文件名命名规范：   `application-{profile}.properties/yml`

默认使用application.properties的配置；（激活方式见下）

### yml多文档块方式

```yml
server:
  port: 8081
spring:
  profiles:
    active: prod

---
server:
  port: 8083
spring:
  profiles: dev


---

server:
  port: 8084
spring:
  profiles: prod  #指定属于哪个环境
```


### 激活指定profile

​1、普通方式
在配置文件中指定  spring.profiles.active=dev

​2、命令行方式：

```bash
java -jar spring-boot-02-config-0.0.1-SNAPSHOT.jar --spring.profiles.active=dev；
```
可以直接在IDEA测试的时候，配置传入命令行参数
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826212438504.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


​	3、虚拟机参数；

```bash
​-Dspring.profiles.active=dev
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826212525522.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 配置文件加载位置

```bash
–file:./config/

–file:./

–classpath:/config/

–classpath:/
```

优先级由高到底，高优先级的配置会**覆盖**低优先级的配置且**互补配置**；

注意：==可以通过spring.config.location来改变默认的配置文件位置==

项目打包后，我们可以使用命令行参数的形式，启动项目的时候来指定配置文件的新位置；指定配置文件和默认加载的这些配置文件共同起作用形成互补配置（便于运维操作）

```bash
java -jar spring-boot-02-config-02-0.0.1-SNAPSHOT.jar --spring.config.location=G:/application.properties
```

## 外部配置加载顺序

**SpringBoot也可以从以下位置加载配置； 优先级从高到低；高优先级的配置覆盖低优先级的配置，所有的配置会形成互补配置（同上）**

**1.命令行参数形式**


```bash
java -jar spring-boot-02-config-02-0.0.1-SNAPSHOT.jar --server.port=8087  --server.context-path=/abc
```

多个配置用空格分开； --配置项=值

2、**其他形式**
**由jar包外向jar包内进行寻找，优先加载带profile**（如下）

jar包外部的application-{profile}.properties或application.yml(带spring.profile)配置文件

jar包内部的application-{profile}.properties或application.yml(带spring.profile)配置文件

**再来加载不带profile**

jar包外部的application.properties或application.yml(不带spring.profile)配置文件

jar包内部的application.properties或application.yml(不带spring.profile)配置文件

[官方文档参考](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-external-config)

## 自动配置再叙

[官方文档参考](https://docs.spring.io/spring-boot/docs/1.5.9.RELEASE/reference/htmlsingle/#common-application-properties)




`xxxxAutoConfigurartion`：自动配置类；

给容器中添加组件

`xxxxProperties`:封装配置文件中相关属性；




### @Conditional派生注解（Spring注解版原生的@Conditional作用）

作用：必须是`@Conditional`指定的条件成立，才给容器中添加组件，配置配里面的所有内容才生效；

| @Conditional扩展注解            | 作用（判断是否满足当前指定条件）                 |
| ------------------------------- | ------------------------------------------------ |
| @ConditionalOnJava              | 系统的java版本是否符合要求                       |
| @ConditionalOnBean              | 容器中存在指定Bean；                             |
| @ConditionalOnMissingBean       | 容器中不存在指定Bean；                           |
| @ConditionalOnExpression        | 满足SpEL表达式指定                               |
| @ConditionalOnClass             | 系统中有指定的类                                 |
| @ConditionalOnMissingClass      | 系统中没有指定的类                               |
| @ConditionalOnSingleCandidate   | 容器中只有一个指定的Bean，或者这个Bean是首选Bean |
| @ConditionalOnProperty          | 系统中指定的属性是否有指定的值                   |
| @ConditionalOnResource          | 类路径下是否存在指定资源文件                     |
| @ConditionalOnWebApplication    | 当前是web环境                                    |
| @ConditionalOnNotWebApplication | 当前不是web环境                                  |
| @ConditionalOnJndi              | JNDI存在指定项                                   |

**自动配置类必须在一定的条件下才能生效；**

判断自动配置类生效的方法：通过启用  debug=true属性，来让控制台打印自动配置报告
# 常见异常及其错误
## ①关于配置文件引起类型转换错误
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826181244448.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```bash
No converter found capable of converting from type [java.lang.String] to type [com.lzh.springboot03config.bean.Dog]

Action:

Update your application's configuration
```
解法：正确书写配置文件
本次错误--->  yam后缀文件语法格式错误
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200826181648975.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

