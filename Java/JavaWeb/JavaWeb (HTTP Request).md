写在前面：分享技术，共同进步，有不足请见谅，相关意见可评论告知  
> 编程路漫漫，学习无止尽！

@[toc]
# HTTP
## 前言
**概念**:Hyper Text Transfer Protocol 超文本传输协议
	传输协议：定义了，客户端和服务器端通信时，发送数据的格式
	==特点：==
		1. 基于TCP/IP的高级协议
		2. 默认端口号:80
		3. 基于请求/响应模型的:一次请求对应一次响应
		4. 无状态的：每次请求之间相互独立，不能交互数据

	* 历史版本：
		* 1.0：每一次请求响应都会建立新的连接
		* 1.1：复用连接

## 请求消息数据格式
——
	1. 请求行
		请求方式 请求url 请求协议/版本
		GET /login.html	HTTP/1.1
——
		 请求方式：
			 HTTP协议有7中请求方式，常用的有2种
				**GET：**
					1. 请求参数在请求行中，在url后。
					2. 请求的url长度有限制的
					3. 不太安全
				**POST：**
					1. 请求参数在请求体中
					2. 请求的url长度没有限制的
					3. 相对安全
	      请求头：客户端浏览器告诉服务器一些信息
		请求头名称: 请求头值
		**构造post请求表单**
		![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072416152886.png)

		**常见的请求头**：
			1. User-Agent：浏览器告诉服务器，我访问你使用的浏览器版本信息
				* 可以在服务器端获取该头的信息，解决浏览器的兼容性问题

			2. Referer：http://localhost/login.html
				* 告诉服务器，我(当前请求)从哪里来？
					* 作用：
						1. 防盗链：
						2. 统计工作：
_ 盗链情形：
**![加粗样式](https://img-blog.csdnimg.cn/20200724164722461.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
**

**请求空行**
		空行，就是用于分割POST请求的请求头，和请求体的。
 **请求体(正文)：**
		封装POST请求消息的请求参数的（==get请求没有请求体==）

	字符串格式：
		POST /login.html	HTTP/1.1
		Host: localhost
		User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:60.0) Gecko/20100101 Firefox/60.0
		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
		Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
		Accept-Encoding: gzip, deflate
		Referer: http://localhost/login.html
		Connection: keep-alive
		Upgrade-Insecure-Requests: 1
		
		username=zhangsan	

# Request
## request对象和response对象的原理
-
	1. request和response对象是由服务器创建的。我们来使用它们
	2. request对象是来==获取请求==消息，response对象是来==设置响应消息==

2. request对象继承*体系结构*：	
	ServletRequest		--	接口
		|	继承
	HttpServletRequest	-- 接口
		|	实现
	org.apache.catalina.connector.RequestFacade 类(tomcat)

## request功能：
——
 获取请求消息数据， 获取请求行数据
		
==GET /day14/demo1?name=zhangsan HTTP/1.1==
day14   虚拟路径      后面请求资源（请求参数）
==方法：==
				1. 获取请求方式 ：GET
					

```css
String getMethod()  
```
==2. 获取虚拟目录：/day14==
					

```css
String getContextPath()
```
3. 获取Servlet路径: /demo1
					

```java
String getServletPath()
```
4.、获取get方式请求参数：name=zhangsan
					

```java
String getQueryString()
```
==5. 获取请求URI：/day14/demo1==
					

```java
String getRequestURI():		/day14/demo1
StringBuffer getRequestURL()  :http://localhost/day14/demo1
```

==URL==:统一资源定位符 ： http://localhost/day14/demo1	中华人民共和国
==URI==统一资源标识符 : /day14/demo1					共和国
**范围：  URI > URL**				
6. 获取协议及版本：HTTP/1.1
					
实列：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200725002027574.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


```java
String getProtocol()
```

7. 获取客户机的IP地址：

```java
String getRemoteAddr()
```
				
				
### 获取请求头数据
**方法：**
				

```java
String getHeader(String name):通过请求头的名称获取请求头的值
Enumeration<String> getHeaderNames():获取所有的请求头名称		
```
			
 获取请求体数据:
			请求体：只有POST请求方式，才有请求体，在请求体中封装了POST请求的请求参数
			步骤：
				1. 获取流对象
					

```java
BufferedReader getReader()：获取字符输入流，只能操作字符数据
ServletInputStream getInputStream()：获取字节输入流，可以操作所有类型数据
```
字符： read ,write
字节： stream
					

2. 再从流对象中拿数据
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072518335133.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


**小技巧**：在创建servlet时可以如下，
优点：如下注释，自动写访问注解路径
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200725001039950.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
·防盗链代码实现：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200725183843828.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 其他功能：
 **获取请求参数通用方式**：==不论get还是post请求方式==都可以使用下列方法来获取请求参数
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200725202458579.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

`String getParameter(String name):`根据参数名称获取参数值    username=zs&password=123
`String[] getParameterValues(String name):`根据参数名称获取参数值的数组  hobby=xx&hobby=game
`Enumeration<String> getParameterNames():`获取所有请求的参数名称
`Map<String,String[]> getParameterMap():`获取所有参数的map集合

**中文乱码问题：**
				get方式：tomcat 8 已经将get方式乱码问题解决了
				post方式：会乱码
				解决：在获取参数前，设置request的编码`request.setCharacterEncoding("utf-8");`

**请求转发**一种在服务器内部的==资源跳转方式==
			步骤：
				通过request对象获取请求转发器对象`：RequestDispatchergetRequestDispatcher(String path)`
				使用RequestDispatcher对象来进行转发：`forward(ServletRequest request, ServletResponse response)` 

 **特点：**
				1. 浏览器地址栏路径不发生变化
				2. 只能转发到当前服务器内部资源中。
				3. 转发是一次请求

#### 数据共享
**域对象**：一个有作用范围的对象，可以在范围内共享数据
**request域**：  代表一次请求的范围，一般用于请求转发的多个资源中共享数据

方法：

```java
void setAttribute(String name,Object obj);   储存数据
Object getAttribute(String name);   通过键获取取值
void removeAttribute(String name);  通过键移除键值对
```

#### 获取ServletContext

```java
ServletContext getServletContext()
```

