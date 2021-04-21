**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# 引入
## HTTP协议
### 请求消息：客户端发送给服务器端的数据
 数据格式：
		1. 请求行     2. 请求头    	3. 请求空行    	4. 请求体
		

### 响应消息：服务器端发送给客户端的数据
 数据格式：
一、==响应行== 组成：协议/版本 响应状态码 状态码描述
**响应状态码**：服务器告诉客户端浏览器本次请求和响应的一个状态，状态码都是3位数字 
**状态码分类**：
1. `1xx`：服务器就收客户端消息，但没有接受完成，等待一段时间后，发送1xx多状态码
2. `2xx`：成功。代表：200
3. `3xx`：重定向。代表：302(重定向)，304(访问缓存)
4. `4xx`：客户端错误。404（请求路径没有对应的资源） 405：请求方式没有对应的doXxx方法
5. `5xx`：服务器端错误。代表：500(服务器内部出现异常)

二、==响应头==：
格式：头名称： 值
**常见的响应头：**
1. `Content-Type`：服务器告诉客户端本次响应体数据格式以及编码格式
2. `Content-disposition`：服务器告诉客户端以什么格式打开响应体数据
值：
`in-line`:默认值,在当前页面内打开
`attachment;filename=xxx`：以附件形式打开响应体。文件下载
		3. 响应空行
		4. 响应体:传输的数据
	
eg:响应字符串格式

```css
HTTP/1.1 200 OK
Content-Type: text/html;charset=UTF-8
Content-Length: 101
Date: Wed, 06 Jun 2018 07:08:42 GMT

<html>
	 <head>
		    <title>$Title$</title>
		  </head>
		  <body>
		  hello , response
		  </body>
		</html>
```
# Response 对象
**功能**：设置响应消息
==设置响应行==
		1. 格式：HTTP/1.1 200 ok
		2. 设置状态码：setStatus(int sc) 
 ==设置响应头==：setHeader(String name, String value) 
		
==设置响应体==：

1. 获取输出流
	字符输出流：`PrintWriter getWriter()`

	字节输出流：`ServletOutputStream getOutputStream()`

	2. 使用输出流，将数据输出到客户端浏览器

## 重定向


```java
response.sendRedirect("/day15/responseDemo2");
```

##  redirect和 forward  区别
 **重定向的特点**:redirect
			1. 地址栏发生变化
			2. 重定向可以访问其他站点(服务器)的资源
			3. 重定向是两次请求。不能使用request对象来共享数据
**转发的特点**：forward
			1. 转发地址栏路径不变
			2. 转发只能访问当前服务器下的资源
			3. 转发是一次请求，可以使用request对象来共享数据
		

**路径写法：**
1. ==相对路径==：通过相对路径不可以确定唯一资源,				不以/开头，以.开头路径
如：./index.html
	规则：找到当前资源和目标资源之间的相对位置关系
						`./`：当前目录
						 `../`:后退一级目录
2. ==绝对路径==：通过绝对路径可以确定唯一资源,* 以/开头的路径
如：http://localhost/day15/responseDemo2		/day15/responseDemo2
					
规则：判断定义的路径是给谁用的？判断请求将来从哪儿发出
==给客户端浏览器使用：需要加虚拟目录(项目的访问路径)==
建议虚拟目录动态获取：request.getContextPath()

服务器输出字符数据到浏览器
			1. 获取字符输出流
			2. 输出数据

 **注意乱码问题：**

1. `PrintWriter pw = response.getWriter()`;获取的流的默认编码是ISO-8859-1
2. 设置该流的默认编码
3. 告诉浏览器响应体使用的编码
==简单的形式==，设置编码，是在获取流之前设置

```java
   response.setContentType("text/html;charset=utf-8");
```
3. 服务器输出字节数据到浏览器
步骤：1. 获取字节输出流    2. 输出数据

4. 验证码
		1. 本质：图片
		2. 目的：防止恶意表单注册


## ServletContext 对象
1. **概念**：代表整个web应用，可以和程序的容器(服务器)来通信
2. **获取**：
（1）通过request对象获取     `request.getServletContext();`
（2） 通过HttpServlet获取      th`is.getServletContext();`
		
### 功能：
1. ==获取MIME类型：==
MIME类型:在互联网通信过程中定义的一种文件数据类型
格式： 大类型/小类型   text/html		image/jpeg
获取：`String getMimeType(String file)`  
2. ==域对象：共享数据==
		1. setAttribute(String name,Object value)
		2. getAttribute(String name)
		3. removeAttribute(String name)

> ServletContext对象范围：所有用户所有请求的数据

3. ==获取文件的真实(服务器)路径==
 方法：`String getRealPath(String path)`  

```java
String b = context.getRealPath("/b.txt");//web目录下资源访问System.out.println(b);
String c = context.getRealPath("/WEB-INF/c.txt");//WEB-INF目录下的资源访问
System.out.println(c);
String a = context.getRealPath("/WEB-INF/classes/a.txt");//src目录下的资源访问
System.out.println(a);
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200731143459560.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200731142851417.png)
# 会话技术引入
1. **会话**：一次会话中包含多次请求和响应。==一次会话==：浏览器第一次给服务器资源发送请求，会话建立，直到有一方断开为止。
**功能**：在一次会话的范围内的多次请求间，共享数据
 ==方式==：
	1. 客户端会话技术：Cookie      	2. 服务器端会话技术：Session

# Cookie
**概念**：客户端会话技术，将数据保存到客户端
##  ==使用步骤==：
1. 创建Cookie对象，绑定数据
```java
new Cookie(String name, String value) 
```
2. 发送Cookie对象

```java
response.addCookie(Cookie cookie) 
```
3. 获取Cookie，拿到数据

```java
Cookie[]  request.getCookies() 
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020073121304011.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

**实现原理**：基于响应头set-cookie和请求头cookie实现

## Cookie的注意事项
==（1）== 一次可以发送多个cookie，可以创建多个Cookie对象，使用response调用多次`addCookie`方法发送cookie即可。
==（2）==  默认情况下，当浏览器关闭后，Cookie数据被销毁
持久化存储：`setMaxAge(int seconds)`
			
1. ==正数==：将Cookie数据写到硬盘的文件中。持久化存储。并指定cookie存活时间，时间到后，cookie文件自动失效
2. ==负数==：默认值
3. 零：删除cookie信息
. 
==(3）== 在tomcat 8 之前 cookie中不能直接存储中文数据。需要将中文数据转码---一般采用URL编码(%E3)。在tomcat 8 之后，cookie支持中文数据。特殊字符（空格等）还是不支持，建议使用URL编码存储，URL解码解析

```java
   SimpleDateFormat sdf = new SimpleDateFormat("yyyy年MM月dd日  HH:mm:ss");
   // 问题于次上的空格
   String str_date = sdf.format(date) ;
   System.out.println("编码前"+str_date);


    //URL编码
    str_date = URLEncoder.encode(str_date,"utf-8");
    System.out.println("编码后："+str_date);



 String value = c.getValue();
 System.out.println("解码前："+value);
  //URL解码：
 value = URLDecoder.decode(value,"utf-8");
 System.out.println("解码后："+value);

```

==(4)== cookie共享问题？
假设在一个tomcat服务器中，部署了多个web项目，web项目中cookie默认情况下cookie不能共享
`setPath(String path):`设置cookie的获取范围。默认情况下，设置当前的虚拟目录
如果要共享，则可以将path设置为"/"     

```java
// 创建cookie对象
Cookie c1 = new Cookie("msg","你好") ;
// 设置path ，让当前服务器下部署的所有项目共享Cookie数据
c1.setPath("/") ;
```

==(5)== 不同的tomcat服务器间cookie共享问题
`setDomain(String path):`如果设置一级域名相同，那么多个服务器之间cookie可以共享
`setDomain(".baidu.com"),`那么tieba.baidu.com和news.baidu.com中cookie可以共享

## Cookie的作用
1. cookie存储数据在客户端浏览器,英语译为小饼干，存储比较小的不太敏感数据
2. 浏览器对于单个cookie 的大小有限制(4kb) 以及 对同一个域名下的总cookie数量也有限制(20个)
3. 在不登录的情况下，完成服务器对客户端的身份识别



> 基于实战中学习，学习快乐中成长
> 时间会回答成长，成长会回答梦想
