**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# 错误处理机制
## SpringBoot默认的错误处理机制
### 一、浏览器端
1、返回一个默认的错误页面
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200829154622866.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
  2、浏览器发送请求的请求头：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200829154748643.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 二、其他客户端
1、默认响应一个json数据

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200829155220465.png#pic_center)

  2、请求的请求头：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200829155225888.png#pic_center)

### 原理分析

​可以参照`ErrorMvcAutoConfiguration.java`中错误处理的自动配置以下为容器中组件
 
#### 1、DefaultErrorAttributes
页面共享信息；
```java
@Override
	public Map<String, Object> getErrorAttributes(RequestAttributes requestAttributes,
			boolean includeStackTrace) {
		Map<String, Object> errorAttributes = new LinkedHashMap<String, Object>();
		errorAttributes.put("timestamp", new Date());
		addStatus(errorAttributes, requestAttributes);
		addErrorDetails(errorAttributes, requestAttributes, includeStackTrace);
		addPath(errorAttributes, requestAttributes);
		return errorAttributes;
	}
```


#### 2、BasicErrorController
处理默认/error请求
```java
@Controller
@RequestMapping("${server.error.path:${error.path:/error}}")
public class BasicErrorController extends AbstractErrorController {
    
    @RequestMapping(produces = "text/html")//产生html类型的数据；浏览器发送的请求来到这个方法处理
	public ModelAndView errorHtml(HttpServletRequest request,
			HttpServletResponse response) {
		HttpStatus status = getStatus(request);
		Map<String, Object> model = Collections.unmodifiableMap(getErrorAttributes(
				request, isIncludeStackTrace(request, MediaType.TEXT_HTML)));
		response.setStatus(status.value());
        
        //去哪个页面作为错误页面；包含页面地址和页面内容
		ModelAndView modelAndView = resolveErrorView(request, response, status, model);
		return (modelAndView == null ? new ModelAndView("error", model) : modelAndView);
	}


	@RequestMapping
	@ResponseBody    //产生json数据，其他客户端来到这个方法处理；
	public ResponseEntity<Map<String, Object>> error(HttpServletRequest request) {
		Map<String, Object> body = getErrorAttributes(request,
				isIncludeStackTrace(request, MediaType.ALL));
		HttpStatus status = getStatus(request);
		return new ResponseEntity<Map<String, Object>>(body, status);
	}
```

此部分代码与上浏览器端与其他客户端信息处理相对应

#### 3、ErrorPageCustomizer

```java
	@Value("${error.path:/error}")
	private String path = "/error";  
```
系统出现错误后到error请求进行处理；（web.xml注册的错误页面规则）

#### 4、DefaultErrorViewResolver
关于是否模板引擎
```java
@Override
	public ModelAndView resolveErrorView(HttpServletRequest request, HttpStatus status,
			Map<String, Object> model) {
		ModelAndView modelAndView = resolve(String.valueOf(status), model);
		if (modelAndView == null && SERIES_VIEWS.containsKey(status.series())) {
			modelAndView = resolve(SERIES_VIEWS.get(status.series()), model);
		}
		return modelAndView;
	}

	private ModelAndView resolve(String viewName, Map<String, Object> model) {
        //默认SpringBoot可以去找到一个页面？  error/404
		String errorViewName = "error/" + viewName;
        
        //模板引擎可以解析这个页面地址就用模板引擎解析
		TemplateAvailabilityProvider provider = this.templateAvailabilityProviders
				.getProvider(errorViewName, this.applicationContext);
		if (provider != null) {
            //模板引擎可用的情况下返回到errorViewName指定的视图地址
			return new ModelAndView(errorViewName, model);
		}
        //模板引擎不可用，就在静态资源文件夹下找errorViewName对应的页面   error/404.html
		return resolveResource(errorViewName, model);
	}
```

​实现步骤：

​系统出现4xx或者5xx之类的错误，导致ErrorPageCustomizer生效（定制错误的响应规则，到/error请求，被**BasicErrorController**处理，然后响应页面，所去页面是由**DefaultErrorViewResolver**解析得到的；

```java
protected ModelAndView resolveErrorView(HttpServletRequest request,
      HttpServletResponse response, HttpStatus status, Map<String, Object> model) {
    //所有的ErrorViewResolver得到ModelAndView
   for (ErrorViewResolver resolver : this.errorViewResolvers) {
      ModelAndView modelAndView = resolver.resolveErrorView(request, status, model);
      if (modelAndView != null) {
         return modelAndView;
      }
   }
   return null;
}
```

### 定制错误响应
#### 	定制错误的页面
##### 1、有模板引擎的情况下
error/状态码;【将错误页面命名为  错误状态码.html 放在模板引擎文件夹（templates）里面的 error文件夹下】，发生此状态码的错误就会来到  对应的页面；

​可以使用4xx和5xx作为错误页面的文件名来匹配这种类型的所有错误（优先寻找精确的状态码.html）

**页面能获取的信息**

​timestamp：时间戳

​status：状态码

​error：错误提示

​exception：异常对象

​message：异常消息

​errors：JSR303数据校验的错误都在这里

##### ​2、没有模板引擎
（模板引擎找不到这个错误页面），静态资源文件夹下找；

##### ​3、以上都没有错误页面
就是默认来到SpringBoot默认的错误提示页面

# 配置嵌入式Servlet容器

SpringBoot默认使用Tomcat作为嵌入式的Servlet容器；

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082917493027.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## 定制和修改Servlet容器的相关配置；

1、修改和server有关的配置（ServerProperties【也是EmbeddedServletContainerCustomizer】）；

在`application.properties` 中进行配置·
```properties
server.port=8081
server.context-path=/crud

server.tomcat.uri-encoding=UTF-8

//通用的Servlet容器设置
server.xxx
//Tomcat的设置
server.tomcat.xxx
```


2、编写一个~~EmbeddedServletContainerCustomizer~~ ，2.0后改为`WebServerFactoryCustomizer`：嵌入式的Servlet容器的定制器；来修改Servlet容器的配置

```java
@Configuration
public class MyMvcConfig implements WebMvcConfigurer {
    @Bean
    public WebServerFactoryCustomizer webServerFactoryCustomizer() {
        return new WebServerFactoryCustomizer<ConfigurableWebServerFactory>() {
            @Override
            public void customize(ConfigurableWebServerFactory factory) {
                factory.setPort(8088);
            }
        };
    }
```
## Web三大组件
注册Servlet三大组件【Servlet、Filter、Listener】

由于SpringBoot默认是以jar包的方式启动嵌入式的Servlet容器来启动SpringBoot的web应用，没有web.xml文件。

之前在JavaWeb 是以 `webapp/WEB-INF/web.xml`  的形式

注册三大组件用以下方式

### 1、Servlet
向容器中添加ServletRegistrationBean

```java
@Configuration
public class MyMvcConfig implements WebMvcConfigurer {

    @Bean
    public ServletRegistrationBean myServlet() {
        ServletRegistrationBean register = new ServletRegistrationBean(new MyServlet(), "/myServlet");
        register.setLoadOnStartup(1);
        return register;
    }
    ......
```



### 2、Filter
向容器中添加FilterRegistrationBean

```java
@Configuration
public class MyMvcConfig implements WebMvcConfigurer {


    @Bean
    public FilterRegistrationBean myFilter() {
        FilterRegistrationBean register = new FilterRegistrationBean(new MyFilter());
        register.setUrlPatterns(Arrays.asList("/myServlet","/"));
        return register;
    }
```


### 3、Listener
向容器中注入ServletListenerRegistrationBean

```java
@Configuration
public class MyMvcConfig implements WebMvcConfigurer {

    @Bean
    public ServletListenerRegistrationBean myServletContextListener(){
        return new ServletListenerRegistrationBean(new MyServletContextListener());
    }
```

 
## 替换为其他嵌入式Servlet容器

默认支持：

### 1、Tomcat（默认使用）

```xml
<dependency>
   <groupId>org.springframework.boot</groupId>
   <artifactId>spring-boot-starter-web</artifactId>
   引入web模块默认就是使用嵌入式的Tomcat作为Servlet容器；
</dependency>
```

### 2、Jetty

```xml
<!-- 引入web模块 -->
<dependency>
   <groupId>org.springframework.boot</groupId>
   <artifactId>spring-boot-starter-web</artifactId>
   <exclusions>
      <exclusion>
         <artifactId>spring-boot-starter-tomcat</artifactId>
         <groupId>org.springframework.boot</groupId>
      </exclusion>
   </exclusions>
</dependency>

<!--引入其他的Servlet容器-->
<dependency>
   <artifactId>spring-boot-starter-jetty</artifactId>
   <groupId>org.springframework.boot</groupId>
</dependency>
```

### 3、Undertow

```xml
<!-- 引入web模块 -->
<dependency>
   <groupId>org.springframework.boot</groupId>
   <artifactId>spring-boot-starter-web</artifactId>
   <exclusions>
      <exclusion>
         <artifactId>spring-boot-starter-tomcat</artifactId>
         <groupId>org.springframework.boot</groupId>
      </exclusion>
   </exclusions>
</dependency>

<!--引入其他的Servlet容器-->
<dependency>
   <artifactId>spring-boot-starter-undertow</artifactId>
   <groupId>org.springframework.boot</groupId>
</dependency>
```





