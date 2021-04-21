**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# Filter 过滤器
## 概念：
当访问服务器的资源时，过滤器可以将请求拦截下来，完成一些特殊的功能。
==过滤器的作用：==
 一般用于完成通用的操作。如：登录验证、统一编码处理、敏感字符过滤...


## 使用方法：
1. 定义一个类，实现接口Filter
2. 复写方法
3. 配置拦截路径
	① web.xml
	![在这里插入图片描述](https://img-blog.csdnimg.cn/20200802185105791.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
代码为：

```java
  <filter-name>demo1</filter-name>
        <filter-class>cn.you.web.filter.FilterDemo1</filter-class>
    </filter>
    <filter-mapping>
        <filter-name>demo1</filter-name>
        <!-- 拦截路径 -->
        <url-pattern>/*</url-pattern>
    </filter-mapping>
```

②注解   `@WebFilter("/*")`  访问所有资源之前，都会执行该过滤器
	上面两者选其一即可（与Servlet 配置类似）

总概如下图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200802183807926.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 过滤器执行流程
1. 执行过滤器
2. 执行放行后的资源
3. 回来执行过滤器放行代码下边的代码
## 过滤器生命周期方法
与Servlet生命周期类似
1. init:在服务器启动后，会创建Filter对象，然后调用init方法。只执行一次。用于加载资源
2. doFilter:每一次请求被拦截资源时，会执行。执行多次
3. destroy:在服务器关闭后，Filter对象被销毁。如果服务器是正常关闭，则会执行destroy方法。只执行一次。用于释放资源
## 过滤器配置
### 拦截路径配置：
1. 具体资源路径： /index.jsp   只有访问index.jsp资源时，过滤器才会被执行
2. 拦截目录： /user/*	访问/user下的所有资源时，过滤器都会被执行
3. 后缀名拦截： *.jsp		访问所有后缀名为jsp资源时，过滤器都会被执行
4. 拦截所有资源：/*		访问所有资源时，过滤器都会被执行
### 拦截方式配置：
————资源被访问的方式
**①注解配置：**
设置dispatcherTypes属性
1. ==REQUEST==：默认值。浏览器直接请求资源

```java
 //转发到index.jsp
request.getRequestDispatcher("/index.jsp").forward(request,response);
```

```java
//浏览器直接请求index.jsp资源时，该过滤器会被执行
@WebFilter(value="/index.jsp",dispatcherTypes = DispatcherType.REQUEST)
```

2. ==FORWARD==：转发访问资源

以下为1.2兼得的情况，原因其源码以数组的形式传递
```java
//浏览器直接请求index.jsp或者转发访问index.jsp。该过滤器才会被执行
@WebFilter(value="/*",dispatcherTypes ={ DispatcherType.FORWARD,DispatcherType.REQUEST})
```

3. ==INCLUDE==：包含访问资源
4. ERROR：错误跳转资源
5. ASYNC：异步访问资源‘

**②web.xml配置**
	设置`<dispatcher></dispatcher>`标签即可
## 过滤器链(配置多个过滤器)
**过滤器先后顺序问题**：
1. ==注解配置==：按照类名的字符串比较规则比较，值小的先执行
				eg： AFilter 和 BFilter，AFilter就先执行了。
2. ==web.xml配置==： <filter-mapping>谁定义在上边，谁先执行

**执行顺序**：如果有两个过滤器：过滤器1和过滤器2
			1. 过滤器1
			2. 过滤器2
			3. 资源执行
			4. 过滤器2
			5. 过滤器1 



# 增强对象的功能：
## 设计模式：
一些通用的解决固定问题的方式
百度百科：
> https://baike.baidu.com/item/%E8%BD%AF%E4%BB%B6%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/2117635?fromtitle=%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F&fromid=1212549&fr=aladdin

==代理模式介绍==
概念：
					1. 真实对象：被代理的对象
					2. 代理对象：
					3. 代理模式：代理对象代理真实对象，达到增强真实对象功能的目的
**实现方式**：
				 	1. 静态代理：有一个类文件描述代理模式
				 	2. 动态代理：在内存中形成代理类
**实现步骤**：
1. 代理对象和真实对象实现相同的接口
2. 代理对象 = Proxy.newProxyInstance();
3. 使用代理对象调用方法。
4. 增强方法

总概如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200803001240535.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 具体实现
  1.创建真实对象

```java
   Lenovo lenovo = new Lenovo();
```
        
  2.动态代理增强lenovo对象（模板）
==三个参数分别为==：
   1. 类加载器：真实对象.getClass().getClassLoader()
    2. 接口数组：真实对象.getClass().getInterfaces()
    3. 处理器：new InvocationHandler()
```java
 SaleComputer proxy_lenovo = (SaleComputer) Proxy.newProxyInstance(lenovo.getClass().getClassLoader(), lenovo.getClass().getInterfaces(), new InvocationHandler() {
```
——————————————————————————————————————
代理逻辑编写的方法：代理对象调用的所有方法都会触发该方法执行
 ==参数：==
                        1. proxy:代理对象
                        2. method：代理对象调用的方法，被封装为的对象
                        3. args:代理对象调用的方法时，传递的实际参数
                        
以下部分为核心所写：
```java
 @Override
   public Object invoke(Object proxy, Method method, Object[] args) throws Throwable{
            }
```

增强方式：
							1. 增强参数列表
							2. 增强返回值类型
							3. 增强方法体执行逻辑	
# 应用
### 登入验证
需求：
			1. 访问资源。验证其是否登录
			2. 如果登录了，则直接放行。
			3. 如果没有登录，则跳转到登录页面，提示"您尚未登录，请先登录"。
```java
@WebFilter("/*")
public class LoginFilter implements Filter {


    public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain) throws ServletException, IOException {
        System.out.println(req);
        ////////0.强制转换，才能使用getRequestURI();方法
        HttpServletRequest request = (HttpServletRequest) req;

        ///////1.获取资源请求路径
        String uri = request.getRequestURI();
        /////2.判断是否包含登录相关资源路径,要注意排除掉 css/js/图片/验证码等资源
        if(uri.contains("/login.jsp") || uri.contains("/loginServlet") || uri.contains("/css/") || uri.contains("/js/") || uri.contains("/fonts/") || uri.contains("/checkCodeServlet")  ){
            //包含，用户就是想登录。放行
            chain.doFilter(req, resp);
        }else{
            //不包含，需要验证用户是否登录
            //////3.从获取session中获取user
            Object user = request.getSession().getAttribute("user");
            if(user != null){
                //登录了。放行
                chain.doFilter(req, resp);
            }else{
                //没有登录。跳转登录页面

                request.setAttribute("login_msg","您尚未登录，请登录");
                request.getRequestDispatcher("/login.jsp").forward(request,resp);
            }
        }


        // chain.doFilter(req, resp);
    }

    public void init(FilterConfig config) throws ServletException {

    }

    public void destroy() {
    }

}
```
### 过滤敏感词
 需求：

1. 对request对象进行增强。增强获取参数相关方法
2. 放行。传递代理对象

```java
@WebFilter("/*")
public class SensitiveWordsFilter implements Filter {


    public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain) throws ServletException, IOException {
        //1.创建代理对象，增强getParameter方法
// 下为模板
 ServletRequest proxy_req = (ServletRequest) Proxy.newProxyInstance(req.getClass().getClassLoader(), req.getClass().getInterfaces(), new InvocationHandler() {
            @Override
            public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                //增强getParameter方法
                //判断是否是getParameter方法
                if(method.getName().equals("getParameter")){
                    //增强返回值
                    //获取返回值
                    String value = (String) method.invoke(req,args);
                    if(value != null){
                        for (String str : list) {
                            if(value.contains(str)){
                                value = value.replaceAll(str,"***");
                            }
                        }
                    }
                    
                    return  value;
                }

            
                return method.invoke(req,args);
            }
        });

        //2.放行
        chain.doFilter(proxy_req, resp);
    }
    private List<String> list = new ArrayList<String>();//敏感词汇集合
    public void init(FilterConfig config) throws ServletException {


// IO 流相关操作
        try{
            //1.获取文件真实路径
            ServletContext servletContext = config.getServletContext();
            String realPath = servletContext.getRealPath("/WEB-INF/classes/敏感词汇.txt");
            //2.读取文件
            BufferedReader br = new BufferedReader(new FileReader(realPath));
            //3.将文件的每一行数据添加到list中
            String line = null;
            while((line = br.readLine())!=null){
                list.add(line);
            }

            br.close();

            System.out.println(list);

        }catch (Exception e){
            e.printStackTrace();
        }

    }

    public void destroy() {
    }

}

```

# Listener 监听器
**概念**：web的三大组件之一（Servlet, Filter, Listener）。
## 事件监听机制
（1）事件	：一件事情  (点击)
（2）事件源 ：事件发生的地方    （按钮）
（3）监听器 ：一个对象
（4）注册监听：将事件、事件源、监听器绑定在一起。 当事件源上发生某个事件后，执行监听器代码

### ServletContextListener:
监听ServletContext对象的创建和销毁
方法：

```java
void contextInitialized(ServletContextEvent sce) ：ServletContext对象创建后会调用该方法
```

```java
void contextDestroyed(ServletContextEvent sce) ：ServletContext对象被销毁之前会调用该方法
```
### 步骤：
1. 定义一个类，实现ServletContextListener接口
2. 复写方法
3. 配置（web三大组件配置方式类似）

（1） web.xml
```java
<listener>
 	<listener-class>cn.itcast.web.listener.ContextLoaderListener</listener-class>
</listener>
```
指定初始化参数`<context-param>`

```java
 <context-param>
      <param-name>contextConfigLocation</param-name>
      <param-value>/WEB-INF/classes/applicationContext.xml</param-value>
 </context-param>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200803135640629.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


（2）注解配置：

```java
@WebListener
```
没有路径参数



实列：
```java
@WebListener
public class ContextLoaderListener implements ServletContextListener {

    /**
     * 监听ServletContext对象创建的。ServletContext对象服务器启动后自动创建。
     *
     * 在服务器启动后自动调用
     * @param servletContextEvent
     */
    @Override
    public void contextInitialized(ServletContextEvent servletContextEvent) {
        //加载资源文件
        //1.获取ServletContext对象
        ServletContext servletContext = servletContextEvent.getServletContext();

        //2.加载资源文件
        String contextConfigLocation = servletContext.getInitParameter("contextConfigLocation");

        //3.获取真实路径
        String realPath = servletContext.getRealPath(contextConfigLocation);

        //4.加载进内存
        try{
            FileInputStream fis = new FileInputStream(realPath);
            System.out.println(fis);
        }catch (Exception e){
            e.printStackTrace();
        }
        System.out.println("ServletContext对象被创建了。。。");
    }

    /**
     * 在服务器关闭后，ServletContext对象被销毁。当服务器正常关闭后该方法被调用
     * @param servletContextEvent
     */
    @Override
    public void contextDestroyed(ServletContextEvent servletContextEvent) {
        System.out.println("ServletContext对象被销毁了。。。");
    }
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200803140131278.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

