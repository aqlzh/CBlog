> Life will get much better when you stop caring about what everyone thinks, and  start to actually live for yourself.
 当你不再关心别人的想法，而是开始真正为自己生活时，生活会变得更好

@[toc]
# 题型分配
- 1、   填空题   5x3  = 15  
- 2、   选择题  10x2  = 20
- 3、  判断题   5 x1 = 5
- 4、  简答题   4x 5 = 20
- 5、  程序填空题  2x10 = 20
- 6、编程题  1x20 = 20
 
==重点==： Servlet 、JSP 、JDBC

# 章节叙述
## 第一章(JavaEE 体系结构)
- ==软件开发现状（P1）==（面向Internet应用、面向对象方法和编程、采用标准的体系结构和平台、组件化和工厂流水开发方式、可视化建模、框架技术的全面使用） 

- ==JavaEE 组件（P7）==  (Applet组件、Web组件（Servlet组件、JSP组件）、EJB组件）

- ==JavaEE  角色（P13）== (JavaEE  产品提供者、JavaEE开发者工具提供者、JavaEE应用组件提供者、JavaEE应用组装者、JavaEE应用部署者和管理者)  

- ==JavaEE 体系架构（P14）== (客户层、Web表示层、业务处理层、资源数据层)

## 第三章(Servlet 编程)
### Servlet 概念
Servlet  是运行在Web 容器的Java 类，它能处理Web 客户端的HTTP 请求、并产生HTTP  响应 .(客户不能直接调用 Servlet  方法，只能通过服务器 发送HTTP 请求，间接调用，这是与Java  类的最大区别 )

### Servlet 功能
（1） 接受HTTP  请求
（2）获取请求信息、包括请求头和请求参数数据
（3）调用其他类方法、完成具体的业务功能
（4）生成HTTP 响应，包括HTML 响应和非HTML  响应
（5）实现到其他 Web 组件的跳转 , 包括  重定向与转发

### Servlet 编程
导入包
```java
import javax.io.*
import javax,servlet.*
import javax.servlet.http.*
```

#### 重写doGet 、doPost 方法

```java
public void doGet (HttpServletRequest request , 
HttpServletResponse response) throws 
ServletException,IOException {}
```



#### 重写init 方法
`init()` 方法在 Web 容器创建Servlet 类对象后立即执行，且执行一次.

```java
public void init(ServletConfig config) throws
 ServletException {
  super.init(config) ;
 }
```

#### 重写 destroy 方法

```java
public void destory ()
{
    try{
   cn.close() ;
} catch(Exception e){
  application.Log("登入处理数据库关闭错误" + e.getMessage()) ;
}
    }
```
### Servlet  ==生命周期==
- Servlet  生命周期完全由 Web 容器掌管，Servlet 的所有方法由Web 容器调用，==加载实例化==，==初始化==、==处理请求阶段==、==服务和销毁==

### Servlet  ==配置==
Servlet  必须在Web 配置文件/ WEB-INF / web,xml  中进行配置和映射才能响应HTTP  请求

```java
<servlet>
   <servlet-name>action</servlet-name>
   <servlet-class>org.apache.struts.action.ActionServlet
   </servlet-class>
   <init-param>
       <param-name>config</param-name>
       <param-value>/WEB-INF/struts-config.xml<param-value>
   </init-param>
   <load-on-startup>2</load-on-startup>
</servlet>
```
`<load-on-startup>2</load-on-startup>` 表示启动的顺序，数字越小越先启动
###  Servlet 映射
**映射地址方式：**
- 1、绝对地址方式映射
```java
<servlet-mapping>
    <servlet-name>LoginAction<servlet-name>
    <url-pattern>/login.action<url-pattern>
</servlet-mapping>
```
- 2、匹配目录模式映射方式
URL 格式 ： `/ 目录 / 目录 / *` 
```java
<url-pattern>/main/* <url-pattern>
```

- 3、匹配扩展名格式映射方式

```java
<url-pattern>*.action<url-pattern>
```

==注意== ： 不能混合使用以上两种匹配方式，否则会在Web 项目部署运行时报错.
### 基本知识
 
- URL格式： 协议：// IP地址：端口 / 站点名 / 目录 / 文件名 
- 客户端一般为浏览器
- Web 的请求方式有 ==GET== 、==POST== 、PUT 、DELETE、HEAD  
- Web 请求基本使用 GET 、 提交表单为 POST ，将传递到Web 服务器中的数据保存到数据流中

HTTP  响应类型 : `文本类型`、`二进制原始类型` （P35）



##  第四章（HTTP 请求处理编程）
### HTTP 请求头
用于通知Web 容器请求中信息类型，请求方式，信息的大小、客户的IP   地址 .

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210623112200246.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### HTTP 请求体
请求中包含的提交给服务器的数据，如表单提交中的数据、上传的文件 .


##   第五章（HTTP 响应处理编程）
- MIME(Multipurpose Internet Mail Extensions)多用途互联网邮件扩展类型   
### 响应头 响应体   （内含方法）

实际编程常用的响应头如下 ：
1、`Accept` ： 指示HTTP 响应可以接受的文档类型，即MIME  类型
2、`Accept- Charset` : 告知用户可以接受的子集 
3、`Accept-Encoding` 所有可以响应的字符编码集
4、 `Content-Type` 响应体的  MIME 类型
5、`Content- Language`   响应体的语言类型  
6、`Content- Length` 响应体的长度与字节数
7、`Expires`   通知客户端的过期时间，防止客户端使用本地缓存副本
8、`Cookie`  保存到客户端的Cookie  集
9、`Redirect`  重定向

#### 设置响应头 功能方法

```java
public void setHeader(String name , String value){
    response.setHeader("Content-Type","text/html")
}
```
###  二进制响应 与文本响应的区别 
文本类型字符输出流  ： `PrintWriter` 
二进制类型  `OutputStream`



## 第六章（HTTP会话跟踪编程）
会话跟踪方法 ： 
1、重写 URL
2、隐藏表单字段
3、Cookie
4、HttpSession  对象API 
### 会话跟踪方法的优缺点 


#### URL 重写的缺点
- URL 重写 ：将客户端的信息附加在请求URL地址参数中，Web 服务器获得参数信息，完成客户端的信息保存
 - 缺点 ： URL  地址过长， 不同浏览器对URL 传递参数的限制， 安全性缺陷，编程繁杂  

#### 隐藏表单的缺点
1、安全性差
2、编程复杂
3、无法在超链接模式下工作
#### ==Cookie==  的知识点
**Cookie 的缺点** :
1、Cookie 存储方式单一
2、存储位置限制
3、Cookie   大小受浏览器限制
4、Cookie  可用性限制
5、安全性限制

#### 会话对象的==生命周期==
1、创建
2、活动
3、销毁（客户端关闭浏览器、服务器端执行会话对象invalidate() 方法、客户端请求间隔超时）
## 第七章（ServletContext和web配置）
### 转发与重定向的区别
1、 ==发生的地点不同==（重定向在客户端，转发在服务器）
2、==请求响应的次数不同==（重定向两次创建请求对象与响应对象，而转发只有一次，重定向无法共享请求/响应对象  而转发可以）
3、==目标位置不同== 重定向可以转发到Web 应用之外的文档，而转发只能在Web 内部文件之间进行 。

### 服务器环境对象==生命周期==包括以下：
ServletContext 对象创建
ServletContext 对象销毁



