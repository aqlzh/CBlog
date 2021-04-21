写在前面：分享技术，共同进步,有不足请见谅，相关意见可评论告知
> 编程路漫漫，学习无止尽！

@[toc]
# 前序
 ## 资源分类
 --
	1. 静态资源：所有用户访问后，得到的结果都是一样的，称为静态资源.静态资源可以直接被浏览器解析，	如： html,css,JavaScript
	-
	2. 动态资源:每个用户访问相同资源后，得到的结果可能不一样。称为动态资源。动态资源被访问后，需要先转换为静态资源，在返回给浏览器，如：servlet/jsp,php,asp...
		.
3. 网络通信三要素
	1. IP：电子设备(计算机)在网络中的唯一标识。
	2. 端口：应用程序在计算机中的唯一标识。 ==0~65535==
	3. 传输协议：规定了数据传输的规则
	 **基础协议**：
			1. tcp:安全协议，三次握手。 速度稍慢
			2. udp：不安全协议。 速度快

## web服务器软件

* 服务器软件：接收用户的请求，处理请求，做出响应
* web服务器软件：接收用户的请求，处理请求，做出响应。
	* 在web服务器软件中，可以部署web项目，让用户通过浏览器来访问这些项目
	* web容器
JavaEE：Java语言在企业级开发中使用的技术规范的总和，一共规定了13项大的规范
	
# Tomcat
## 再叙
启动：
		bin/startup.bat ,双击运行该文件即可
		访问：浏览器输入：http://localhost:8080 回车访问自己
						  http://别人的ip:8080 访问别人
			查看IP的方法
			![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072323013537.png)、
					1. 正常关闭：
			bin/shutdown.bat   ||   	ctrl+c
		2. 强制关闭：
			点击启动窗口的×



## 配置:
_
### 部署项目的方式：
==方法一==
			 直接将项目放到webapps目录下即可。
				/hello：项目的访问路径-->虚拟目录      (常见)
				**简化部署**:将项目打成一个war包，再将war包放置到webapps目录下。
					war包会自动解压缩
_
==方法二== 配置conf/server.xml文件
				在<Host>标签体中配置
				

```java
<Context docBase="D:\hello" path="/hehe" />
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200723232040403.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

				* docBase:项目存放的路径
				* path：虚拟目录

==方法三：== 在conf\Catalina\localhost创建任意名称的xml文件。在文件中编写
				<Context docBase="D:\hello" />
				* 虚拟目录：xml文件的名称，如果取消可以直接在  `.xml后加_bak`
		
### 静态项目和动态项目：
_
			目录结构
				java动态项目的目录结构：
					-- 项目的根目录
						-- WEB-INF目录：
							-- web.xml：web项目的==核心配置==文件
							-- classes目录：放置==字节码==文件的目录
							-- lib目录：放置==依赖==的jar包

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200723233224832.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 在IDEA中使用
在配置Tomcat web服务器软件时，注意启用相应插件（前提是已经旗舰版）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724004607358.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724004623235.png)
优化操作
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724005043526.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
1. IDEA会为每一个tomcat部署的项目单独建立一份配置文件
	 ==查看控制台的log：Using CATALINA_BASE:==  "C:\Users\Administrator\.IntelliJIdea2019.3\system\tomcat\_JavaIdeaWebCode"
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724132801719.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724132831351.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

2. 工作空间项目    和     tomcat部署的web项目
	* tomcat真正访问的是“tomcat部署的web项目”，"tomcat部署的web项目"对应着"工作空间项目" 的web目录下的所有资源
	* WEB-INF目录下的资源不能被浏览器直接访问。
3. 断点调试：使用"小虫子"启动 dubug 启动
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724133243611.png)


# Servlet
**概念**：运行在服务器端的小程序
	* Servlet就是一个接口，定义了Java类被浏览器访问到(tomcat识别)的规则。
	* 将来我们自定义一个类，实现Servlet接口，复写方法。

**实现：**
	1. 创建JavaEE项目
	2. 定义一个类，实现Servlet接口
		

```css
public class ServletDemo1 implements Servlet
```

	3. 实现接口中的抽象方法
	4. 配置Servlet
		 在web.xml中配置：
    <!--配置Servlet -->
    <servlet>
        <servlet-name>demo1</servlet-name>
        <servlet-class>cn.itcast.web.servlet.ServletDemo1</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>demo1</servlet-name>
        <url-pattern>/demo1</url-pattern>
    </servlet-mapping>

## 执行原理：
	1. 当服务器接受到客户端浏览器的请求后，会解析请求URL路径，获取访问的Servlet的资源路径
	2. 查找web.xml文件，是否有对应的<url-pattern>标签体内容。
	3. 如果有，则在找到对应的<servlet-class>全类名
	4. tomcat会将字节码文件加载进内存，并且创建其对象
	5. 调用其方法

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724114746329.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## Servlet中的生命周期方法：

		Servlet创建时机：
			 默认情况下，第一次被访问时，Servlet被创建
			 可以配置执行Servlet的创建时机。
				 在<servlet>标签下配置
					1. 第一次被访问时，创建
                		<load-on-startup>的值为负数
		            2. 在服务器启动时，创建
		                 <load-on-startup>的值为0或正整数

Servlet的init方法，只执行一次，说明一个Servlet在内存中只存在一个对象，Servlet是单例的
			==注意==：多个用户同时访问时，可能存在线程安全问题。
			解决：尽量不要在Servlet中定义成员变量。（定义局部变量）即使定义了成员变量，也不要对修改值
——
	 ==提供服务==执行service方法，执行多次
		每次访问Servlet时，Service方法都会被调用一次。
	3. 被销毁：执行destroy方法，只执行一次
		==Servlet==被销毁时执行。服务器关闭时，Servlet被销毁
		只有服务器正常关闭时，才会执行destroy方法。
		destroy方法在Servlet被销毁之前执行，一般用于释放资源

## Servlet3.0：
	* 好处：
		* 支持注解配置。可以不需要web.xml了。

	* 步骤：
		1. 创建JavaEE项目，选择Servlet的版本3.0以上，可以不创建web.xml
		2. 定义一个类，实现Servlet接口
		3. 复写方法
		4. 在类上使用@WebServlet注解，进行配置
			* @WebServlet("资源路径")

http://localhost:8080/虚拟目录/资源路径
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200724134100172.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## Servlet体系结构



	Servlet -- 接口
		|
	GenericServlet -- 抽象类
		|
	HttpServlet  -- 抽象类
——
 ==GenericServlet==：将Servlet接口中其他的方法做了默认空实现，==只将service()方法==作为抽象
 将来定义Servlet类时，可以继承GenericServlet，实现service()方法即可
——
	==HttpServlet==::对http协议的一种封装，简化操作
		1. 定义类继承HttpServlet
		2. 复写doGet/doPost方法

### Servlet相关配置
_
	**urlpartten:Servlet**访问路径
		一个Servlet可以定义多个访问路径 ： @WebServlet({"/d4","/dd4","/ddd4"})
		![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072414361498.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
——
	 **路径定义规则：**
			1. /xxx：路径匹配
			2. /xxx/xxx:多层路径，目录结构
			3. *.do：扩展名匹配
