**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~

> 编程路漫之远兮，运架构式之简化；
劝君专注案前事，亦是杯酒敬苍生；



@[toc]
# MVC概述：
## MVC概念
MVC是**模型**(Model)、**视图**(View)、**控制器**(Controller)的简写，是一种软件设计规范（架构模式）。是将业务逻辑、数据、显示分离的方法来组织代码。主要作用是降低了视图与业务逻辑间的==双向偶合==。


1、**Model**（模型）：数据模型，提供要展示的数据，因此包含数据和行为，类比于领域模型或JavaBean组件（包含数据和行为），现在分为Value Object（数据Dao） 和 服务层（行为Service）。主要作用提供了模型数据查询和模型数据的状态更新等功能，包括数据和业务。

2、**View**（视图）：负责进行模型的展示，即为可视的用户界面


3、**Controller**（控制器）：接收用户请求，委托给模型进行处理（状态改变），处理完毕后把返回的模型数据返回给视图，由视图负责展示。也就是说控制器做了个调度员的工作。

==典型的MVC为JSP + servlet + javabean的模式==

## 执行流程与职责分析
**用户**发请求 --> **Servlet**接收请求数据 --> 调用对应的**业务逻辑**方法

业务处理完毕 --> 返回更新后的数据给**servlet**  --> servlet转向到**JSP**由JSP来渲染页面  ---> 响应给**前端**更新后的页面


---
Model：模型，业务逻辑，保存数据的状态

View：视图，显示页面


Controller：控制器 ，取得表单数据，调用业务逻辑，转向指定的页面

---
# Servlet回顾
## 导入pom依赖

```xml
<dependencies>
   <dependency>
       <groupId>junit</groupId>
       <artifactId>junit</artifactId>
       <version>4.12</version>
   </dependency>
   <dependency>
       <groupId>org.springframework</groupId>
       <artifactId>spring-webmvc</artifactId>
       <version>5.1.9.RELEASE</version>
   </dependency>
   <dependency>
       <groupId>javax.servlet</groupId>
       <artifactId>servlet-api</artifactId>
       <version>2.5</version>
   </dependency>
   <dependency>
       <groupId>javax.servlet.jsp</groupId>
       <artifactId>jsp-api</artifactId>
       <version>2.2</version>
   </dependency>
   <dependency>
       <groupId>javax.servlet</groupId>
       <artifactId>jstl</artifactId>
       <version>1.2</version>
   </dependency>
</dependencies>
```
## 常规构建项目
父项目：新建普通maven项目（无添加模板）
子项目：建立一个Moudle：SpringMVC01-servlet ， 并添加Web app的支持（添加框架支持）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819184408167.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819184506946.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

1、导入servlet 和 jsp 的 jar 依赖

```xml
<dependency>
   <groupId>javax.servlet</groupId>
   <artifactId>servlet-api</artifactId>
   <version>2.5</version>
</dependency>
<dependency>
   <groupId>javax.servlet.jsp</groupId>
   <artifactId>jsp-api</artifactId>
   <version>2.2</version>
</dependency>
```

2、编写一个Servlet类，用来处理用户的请求

```java
package com.kuang.servlet;

//实现Servlet接口
public class HelloServlet extends HttpServlet {
   @Override
   protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
       //取得参数
       String method = req.getParameter("method");
       if (method.equals("add")){
           req.getSession().setAttribute("msg","执行了add方法");
      }
       if (method.equals("delete")){
           req.getSession().setAttribute("msg","执行了delete方法");
      }
       //业务逻辑
       //视图跳转
       req.getRequestDispatcher("/WEB-INF/jsp/hello.jsp").forward(req,resp);
  }

   @Override
   protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
       doGet(req,resp);
  }
}
```

3、编写test.jsp，在WEB-INF目录下新建一个jsp的文件夹，新建test.jsp

```jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
   <title>Kuangshen</title>
</head>
<body>
${msg}
</body>
</html>
```
4、在web.xml中注册Servlet

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
        version="4.0">
   <servlet>
       <servlet-name>HelloServlet</servlet-name>
       <servlet-class>com.kuang.servlet.HelloServlet</servlet-class>
   </servlet>
   <servlet-mapping>
       <servlet-name>HelloServlet</servlet-name>
       <url-pattern>/user</url-pattern>
   </servlet-mapping>

</web-app>
```


配置Tomcat，并启动测试

localhost:8080/user?method=add

localhost:8080/user?method=delete


# SpringMVC启航
## 概述
**概念**：Spring MVC是Spring Framework的一部分，是基于Java实现MVC的轻量级Web框架。

官方文档：

> https://docs.spring.io/spring/docs/5.2.0.RELEASE/spring-framework-reference/web.html#spring-web


 ### 特点：

（1）轻量级，简单易学，简洁灵活

（2）高效 , 基于请求响应的MVC框架,与Spring无缝集成(使用SpringIoC和Aop) 

（3）与Spring兼容性好，无缝结合

（4）约定优于配置

（5）功能强大：RESTful、数据验证、格式化、本地化、主题等

---

Spring的web框架围绕`DispatcherServlet` [ 调度Servlet ] 设计。

`DispatcherServlet`的作用是将请求分发到不同的处理器。从Spring 2.5开始，使用Java 5或者以上版本的用户可以采用基于注解形式进行开发


## 中心控制器
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082011034994.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820145235422.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820145319624.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

**与其他框架类比**：
Spring MVC框架像许多其他MVC框架一样, 以请求为驱动 , 围绕一个中心Servlet分派请求及提供其他功能，`DispatcherServlet`是一个实际的Servlet (它继承自HttpServlet 基类)。



## SpringMVC执行原理
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820150614875.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

实线表示SpringMVC框架提供的技术，虚线表示需要开发者实现。

当发起请求时被前置的控制器拦截到请求，根据请求参数生成代理请求，找到请求对应的实际控制器，控制器处理请求，创建数据模型，访问数据库，将模型响应给中心控制器，控制器使用模型与视图渲染视图结果，将结果返回给中心控制器，再将结果返回给请求者。`DispatcherServlet`表示前置控制器，是整个SpringMVC的控制中心。用户发出请求，DispatcherServlet接收请求并拦截请求。

**实列**：若请求的url为 : http://localhost:8080/SpringMVC/hello
**分解**：

http://localhost:8080服务器域名

SpringMVC部署在服务器上的web站点

hello表示控制器

**结果**：通过分析，如上url表示为：请求位于服务器localhost:8080上的SpringMVC站点的hello控制器。

**流程**：
`HandlerMapping`为处理器映射。`DispatcherServlet`调用`HandlerMapping`,HandlerMapping根据请求url查找Handler。

`HandlerExecution`表示具体的Handler,其主要作用是根据url查找控制器，如上url被查找控制器为：hello。

`HandlerExecution`将解析后的信息传递给`DispatcherServlet`,如解析控制器映射等。

`HandlerAdapter`表示处理器适配器，其按照特定的规则去执行Handler。

Handler让具体的Controller执行。

Controller将具体的执行信息返回给`HandlerAdapter`,如`ModelAndView`。

`HandlerAdapter`将视图逻辑名或模型传递给`DispatcherServlet`。

`DispatcherServlet`调用视图解析器(ViewResolver)来解析HandlerAdapter传递的逻辑视图名。

视图解析器将解析的逻辑视图名传给`DispatcherServlet`。

`DispatcherServlet`根据视图解析器解析的视图结果，调用具体的视图。

最终视图呈现给用户。


# SpringMVC编写
## 配置版
1、配置web.xml  ， 注册DispatcherServlet

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
        version="4.0">

   <!--1.注册DispatcherServlet-->
   <servlet>
       <servlet-name>springmvc</servlet-name>
       <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
       <!--关联一个springmvc的配置文件:【servlet-name】-servlet.xml-->
       <init-param>
           <param-name>contextConfigLocation</param-name>
           <param-value>classpath:springmvc-servlet.xml</param-value>
       </init-param>
       <!--启动级别-1-->
       <load-on-startup>1</load-on-startup>
   </servlet>

   <!--/ 匹配所有的请求；（不包括.jsp）-->
   <!--/* 匹配所有的请求；（包括.jsp）-->
   <servlet-mapping>
       <servlet-name>springmvc</servlet-name>
       <url-pattern>/</url-pattern>
   </servlet-mapping>

</web-app>
```

2、编写SpringMVC 的 配置文件！名称：`springmvc-servlet.xml`  : `[servletname]-servlet.xml`
说明，这里的名称要求是按照官方来的

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd">

</beans>
```

5、添加 处理映射器

```xml
<bean class="org.springframework.web.servlet.handler.BeanNameUrlHandlerMapping"/>
```

6、添加 处理器适配器

```xml
<bean class="org.springframework.web.servlet.mvc.SimpleControllerHandlerAdapter"/>
```

7、添加 视图解析器

```xml
<!--视图解析器:DispatcherServlet给他的ModelAndView-->
<bean class="org.springframework.web.servlet.view.InternalResourceViewResolver" id="InternalResourceViewResolver">
   <!--前缀-->
   <property name="prefix" value="/WEB-INF/jsp/"/>
   <!--后缀-->
   <property name="suffix" value=".jsp"/>
</bean>
```

8、编写我们要操作业务Controller ，要么实现Controller接口，要么增加注解；需要返回一个ModelAndView，装数据，封视图；

```java
package com.kuang.controller;

import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.Controller;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

//注意：这里我们先导入Controller接口
public class HelloController implements Controller {

   public ModelAndView handleRequest(HttpServletRequest request, HttpServletResponse response) throws Exception {
       //ModelAndView 模型和视图
       ModelAndView mv = new ModelAndView();

       //封装对象，放在ModelAndView中。Model
       mv.addObject("msg","HelloSpringMVC!");
       //封装要跳转的视图，放在ModelAndView中
       mv.setViewName("hello"); //: /WEB-INF/jsp/hello.jsp
       return mv;
  }
   
}
```

9、将自己的类交给SpringIOC容器，注册bean

```css
<!--Handler-->
<bean id="/hello" class="com.kuang.controller.HelloController"/>
10、写要跳转的jsp页面，显示ModelandView存放的数据，以及我们的正常页面；
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
   <title>lzh</title>
</head>
<body>
${msg}
</body>
</html>
```


## 注解版（重要）
### 一、三大区域配置
pom.xml  
springmvc-servlet.xml
 web.xml
 
1、在`pom.xml`完善配置，防止Maven可能存在资源过滤的问题(==固定==)

```xml
<build>
   <resources>
       <resource>
           <directory>src/main/java</directory>
           <includes>
               <include>**/*.properties</include>
               <include>**/*.xml</include>
           </includes>
           <filtering>false</filtering>
       </resource>
       <resource>
           <directory>src/main/resources</directory>
           <includes>
               <include>**/*.properties</include>
               <include>**/*.xml</include>
           </includes>
           <filtering>false</filtering>
       </resource>
   </resources>
</build>
```

2、在`pom.xml`文件引入相关的依赖：主要有Spring框架核心库、Spring MVC、servlet , JSTL等。(已经在父依赖中)(==固定==)
3、配置`web.xml`(==固定==)

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
        version="4.0">

   <!--1.注册servlet-->
   <servlet>
       <servlet-name>SpringMVC</servlet-name>
       <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
       <!--通过初始化参数指定SpringMVC配置文件的位置，进行关联-->
       <init-param>
           <param-name>contextConfigLocation</param-name>
           <param-value>classpath:springmvc-servlet.xml</param-value>
       </init-param>
       <!-- 启动顺序，数字越小，启动越早 -->
       <load-on-startup>1</load-on-startup>
   </servlet>

   <!--所有请求都会被springmvc拦截 -->
   <servlet-mapping>
       <servlet-name>SpringMVC</servlet-name>
       <url-pattern>/</url-pattern>
   </servlet-mapping>

</web-app>
```
**总结**：
/ 和 /* 的区别：`< url-pattern > / </ url-pattern >` 不会匹配到.jsp， 只针对我们编写的请求；即：.jsp 不会进入spring的 DispatcherServlet类 。`< url-pattern > /* </ url-pattern >` 会匹配 *.jsp，会出现返回 jsp视图 时再次进入spring的DispatcherServlet 类，导致找不到对应的controller所以报404错。
**注意事项**：
(1)注意web.xml版本问题，要最新版！
(2)注册DispatcherServlet
(3)关联SpringMVC的配置文件
(4)启动级别为1
(5)映射路径为 / 【不要用/*，会404】



4、添加Spring MVC配置文件
在resource目录下添加`springmvc-servlet.xml`配置文件，配置的形式与Spring容器配置基本类似，为了支持基于注解的IOC，设置了自动扫描包的功能，具体配置信息如下：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xmlns:context="http://www.springframework.org/schema/context"
      xmlns:mvc="http://www.springframework.org/schema/mvc"
      xsi:schemaLocation="http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd
       http://www.springframework.org/schema/context
       https://www.springframework.org/schema/context/spring-context.xsd
       http://www.springframework.org/schema/mvc
       https://www.springframework.org/schema/mvc/spring-mvc.xsd">

   <!-- 自动扫描包，让指定包下的注解生效,由IOC容器统一管理 -->
   <context:component-scan base-package="com.kuang.controller"/>
   <!-- 让Spring MVC不处理静态资源 -->
   <mvc:default-servlet-handler />
   <!--
   支持mvc注解驱动
       在spring中一般采用@RequestMapping注解来完成映射关系
       要想使@RequestMapping注解生效
       必须向上下文中注册DefaultAnnotationHandlerMapping
       和一个AnnotationMethodHandlerAdapter实例
       这两个实例分别在类级别和方法级别处理。
       而annotation-driven配置帮助我们自动完成上述两个实例的注入。
    -->
   <mvc:annotation-driven />

   <!-- 视图解析器 -->
   <bean class="org.springframework.web.servlet.view.InternalResourceViewResolver"
         id="internalResourceViewResolver">
       <!-- 前缀 -->
       <property name="prefix" value="/WEB-INF/jsp/" />
       <!-- 后缀 -->
       <property name="suffix" value=".jsp" />
   </bean>

</beans>
```
**关键点再叙**：
（1）自动扫描包
（2）过滤静态资源（css,html,mp3）
（3）支持mvc注解驱动
（4）视图解析器
在视图解析器中我们把所有的视图都存放在/WEB-INF/目录下，这样可以保证视图安全，因为这个目录下的文件，客户端不能直接访问。


### 二、创建Controller

1、编写一个Java控制类：com.kuang.controller.HelloController , 注意编码规范

```java
package com.kuang.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;



@Controller
@RequestMapping("/HelloController")
public class HelloController {

   //真实访问地址 : 项目名/HelloController/hello
   @RequestMapping("/hello")
   public String sayHello(Model model){
       //向模型中添加属性msg与值，可以在JSP页面中取出并渲染
       model.addAttribute("msg","hello,SpringMVC");
       //web-inf/jsp/hello.jsp
       return "hello";
  }
}
```

`@Controller`是为了让Spring IOC容器初始化时自动扫描到；

`@RequestMapping`是为了映射请求路径，这里因为类与方法上都有映射所以访问时应该是/HelloController/hello；

```bash
真实访问地址 : 项目名/HelloController/hello
```

方法中声明Model类型的参数是为了把Action中的数据带到视图中；

方法返回的结果是视图的名称hello，加上配置文件中的前后缀变成WEB-INF/jsp/hello.jsp。

2、创建视图层

在WEB-INF/ jsp目录中创建hello.jsp ， 视图可以直接取出并展示从Controller带回的信息；

可以通过EL表示取出Model中存放的值，或者对象；

```bash
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
   <title>SpringMVC</title>
</head>
<body>
${msg}
</body>
</html>
```

8、配置Tomcat运行
配置Tomcat ，  开启服务器 ， 访问 对应的请求路径！
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820215845433.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

# 常见错误与异常
## ①右键无法创建java类
解决在目录结构中进行设置
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819221956414.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## ②servlet-class 中路径报红问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200819231613578.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


`<servlet-name >` 可以自定义，但是要唯一

`<servlet-class>`servlet的完全限定名=包名+类名，用来找到class，生成需要的对象；检查是否写错的方法，按住Ctrl+鼠标放于限定名上，如果连接说明可以找到；

`<servlet-name>`和servlet标签中的servlet-name要一致；

`<url-pattern>`这个名称是用来访问名称，请求路径；

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820000555313.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
==解法==：直接重新新建一个模板

## ③ artifact deployment 错误
Artifact Springmvc02-mvc:war exploded: Error during artifact deployment. See server log for details.

（1）`web.xml` 等配置文件，配置错误
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820153442663.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

（2）编辑tomcat 配置
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820153529356.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
（3）项目结构
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820153626324.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
##  ④代码未出错，访问出现404
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820180644459.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
（1）查看控制台输出，是否缺少了jar包。

（2）如果jar包存在，显示无法输出，就在IDEA的项目发布中，添加lib依赖！
以下为步骤：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820180848681.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820181042899.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
（3）重启Tomcat 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820181142659.png#pic_center)


> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想


