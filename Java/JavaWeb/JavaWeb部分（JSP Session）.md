**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# JSP
**概念**： Java Server Pages： java服务器端页面
一个特殊的页面，其中既可以指定定义html标签，又可以定义java代码

```java
  // <%   %>内部为java代码
  <%
        System.out.println("hello jsp");
        int i = 5;

        String contextPath = request.getContextPath();
        out.print(contextPath);
      %>
// 以下为html  代码
      <h1>hi~ jsp!</h1>

      <% response.getWriter().write("response....."); %>
```
简化书写，避免如下图情形（页面html  代码占用数多行）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200801000910925.png)
## 原理
SP本质上就是一个Servlet
==JSP的脚本==：JSP定义Java代码的方式
	1. <%  代码 %>：定义的java代码，在service方法中。service方法中可以定义什么，该脚本中就可以定义什么。
	2. <%! 代码 %>：定义的java代码，在jsp转换后的java类的成员位置。
	3. <%= 代码 %>：定义的java代码，会输出到页面上。输出语句中可以定义什么，该脚本中就可以定义什么。



## 指令
**作用**：用于配置JSP页面，导入资源文件
**格式**：

```java
<%@ 指令名称 属性名1=属性值1 属性名2=属性值2 ... %>
```
### 分类：
一、==page==： 配置JSP页面的
contentType：等同于`response.setContentType()`
设置响应体的mime类型以及字符集，设置当前jsp页面的编码（只能是高级的IDE才能生效，如果使用低级工具，则需要设置pageEncoding属性设置当前页面的字符集）
import：导包
errorPage：当前页面发生异常后，会自动跳转到指定的错误页面
isErrorPage：标识当前也是是否是错误页面。
true：是，可以使用内置对象exception
false：否。默认值。不可以使用内置对象exception

二、==include==	： 页面包含的。导入页面的资源文件
<%@include file="top.jsp"%>
三、==taglib==	： 导入资源
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
prefix：前缀，自定义的
### 注释:
1. html注释：
		<!-- -->:只能注释html代码片段
2. jsp注释：推荐使用
		<%-- --%>：可以注释所有

## JSP的内置对象：
在jsp页面中不需要获取和创建，可以直接使用的对象
jsp一共有九大内置对象。
request
response
out：字符输出流对象。可以将数据输出到页面上,和response.getWriter()类似
==response.getWriter()和out.write()的区别：==
在tomcat服务器真正给客户端做出响应之前，会先找response缓冲区数据，再找out缓冲区数据。
`response.getWriter()`数据输出永远在out.write()之前
		

			变量名					真实类型						作用
		pageContext				PageContext					当前页面共享数据，还可以获取其他八个内置对象
	    request					HttpServletRequest			一次请求访问的多个资源(转发)
	    session					HttpSession					一次会话的多个请求间
	    application				ServletContext				所有用户间共享数据
	    response				HttpServletResponse			响应对象
	    page					Object						当前页面(Servlet)的对象  this
	    out						JspWriter					输出对象，数据输出到页面上
	    config					ServletConfig				Servlet的配置对象
	    exception				Throwable					异常对象
# Seesion 
 **概念**：服务器端会话技术，在一次会话的多次请求间共享数据，将数据保存在服务器端的对象中。HttpSession
## 使用方式
1. 获取HttpSession对象：

```java
HttpSession session = request.getSession();
```
2. 使用HttpSession对象：

```java
Object getAttribute(String name)  
void setAttribute(String name, Object value)
void removeAttribute(String name)  
```

原理：Session的实现是依赖于Cookie的。

## 注意事项
1. ==当客户端关闭后，服务器不关闭==，默认情况下两次获取session不为同一个

解决办法：可以创建Cookie,键为JSESSIONID，设置最大存活时间，让cookie持久化保存。

```java
Cookie c = new Cookie("JSESSIONID",session.getId());
c.setMaxAge(60*60);
response.addCookie(c);
```

2. ==客户端不关闭，服务器关闭后==，两次获取的session不是同一个
解决办法：要确保数据不丢失。tomcat自动完成以下工作
**session的钝化**：
在服务器正常关闭之前，将session对象系列化到硬盘上
**session的活化**：
在服务器启动后，将session文件转化为内存中的session对象即可。
			
3. session销毁时机：
		（1） 服务器关闭
		（2）session对象调用invalidate() 。
		（3） session默认失效时间 30分钟
选择性配置修改	
```java
<session-config>
		     <session-timeout>30</session-timeout>
</session-config>
```

## session的特点
1. session用于存储一次会话的多次请求的数据，存在服务器端
2. session可以存储任意类型，任意大小的数据
## session与Cookie的区别：
1.session存储数据在服务器端，Cookie在客户端
2. session没有数据大小限制（英译为主菜），Cookie有限制（英译为小饼干）
3. session数据安全，Cookie相对于不安全


# MVC 开发模式
## 引入
1. M：Model，模型。JavaBean，完成具体的业务操作，如：查询数据库，封装对象

2. V：View，视图。JSP，展示数据
3. C：Controller，控制器。Servlet获取用户的输入，调用模型，将数据交给视图进行展示

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200801193739498.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

> 基于实战中学习，学习快乐中成长
> 时间会回答成长，成长会回答梦想
