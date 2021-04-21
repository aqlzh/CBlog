**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# Web开发 
## 静态资源的映射规则；
**一**、相关配置代码在`ResourceProperties.java`下

 设置和静态资源有关的参数，缓存时间等
```java
@ConfigurationProperties(prefix = "spring.resources", ignoreUnknownFields = false)
public class ResourceProperties implements ResourceLoaderAware {
}
```


**二**、相关配置代码在`WebMvcAuotConfiguration.java`下

有以下三大主要功能：
```java
		@Override
		public void addResourceHandlers(ResourceHandlerRegistry registry) {
			if (!this.resourceProperties.isAddMappings()) {
				logger.debug("Default resource handling disabled");
				return;
			}
			Integer cachePeriod = this.resourceProperties.getCachePeriod();
			if (!registry.hasMappingForPattern("/webjars/**")) {
				customizeResourceHandlerRegistration(
						registry.addResourceHandler("/webjars/**")
								.addResourceLocations(
										"classpath:/META-INF/resources/webjars/")
						.setCachePeriod(cachePeriod));
			}
			String staticPathPattern = this.mvcProperties.getStaticPathPattern();
          	//静态资源文件夹映射
			if (!registry.hasMappingForPattern(staticPathPattern)) {
				customizeResourceHandlerRegistration(
						registry.addResourceHandler(staticPathPattern)
								.addResourceLocations(
										this.resourceProperties.getStaticLocations())
						.setCachePeriod(cachePeriod));
			}
		}

```
### 外部资源访问
（1）所有 /webjars/** ，都去 classpath:/META-INF/resources/webjars/ 找资源


​webjars：以jar包的方式引入静态资源(==类似于之前的WEB-INF==)

[官方文档参考](http://www.webjars.org/)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827190956407.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
localhost:8080/webjars/jquery/3.3.1/jquery.js

访问结构如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082719120246.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


  （2）配置欢迎页映射

```java
@Bean
public WelcomePageHandlerMapping welcomePageHandlerMapping(
		ResourceProperties resourceProperties) {
	return new WelcomePageHandlerMapping(resourceProperties.getWelcomePage(),
			this.mvcProperties.getStaticPathPattern());
}
```

欢迎页； 静态资源文件夹下的所有index.html页面；被"/**"映射；

localhost:8080/   找index页面

（3）配置喜欢的图标
```java
@Configuration
@ConditionalOnProperty(value = "spring.mvc.favicon.enabled", matchIfMissing = true)
public static class FaviconConfiguration {

	private final ResourceProperties resourceProperties;

	public FaviconConfiguration(ResourceProperties resourceProperties) {
		this.resourceProperties = resourceProperties;
	}

	@Bean
	public SimpleUrlHandlerMapping faviconHandlerMapping() {
		SimpleUrlHandlerMapping mapping = new SimpleUrlHandlerMapping();
		mapping.setOrder(Ordered.HIGHEST_PRECEDENCE + 1);
      	//所有  **/favicon.ico 
		mapping.setUrlMap(Collections.singletonMap("**/favicon.ico",
				faviconRequestHandler()));
		return mapping;
	}

	@Bean
	public ResourceHttpRequestHandler faviconRequestHandler() {
		ResourceHttpRequestHandler requestHandler = new ResourceHttpRequestHandler();
		requestHandler
				.setLocations(this.resourceProperties.getFaviconLocations());
		return requestHandler;
	}

}
```
所有的 **/favicon.ico  都是在静态资源文件下找
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082719435596.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

注意：应该统一命名规范（`favicon.ico`），如上图则加载不到

也有可能因为浏览器相异导致加载不到

### 内部资源访问
1、"/**" 访问当前项目的任何资源，都去（静态资源的文件夹）找映射

```
"classpath:/META-INF/resources/", 
"classpath:/resources/",
"classpath:/static/", 
"classpath:/public/" 
"/"：当前项目的根路径
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827193021359.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

==注意==：可以在application.properties文件下修改默认配置
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827194924673.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
eg：
```bash
spring.resources.static-locations=classpath:/hello,classpath:/lzh
```

## 模板引擎
引入：因为SpringBoot 默认不支持jsp 而且tomcat 嵌入式植入

**常见的模板引擎**：JSP、Velocity、Freemarker、Thymeleaf（SpringBoot推荐）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827203505648.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 引入thymeleaf；
1、在`pom.xml`中引入依赖
```xml
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-thymeleaf</artifactId>
		</dependency>
```
2、切换thymeleaf版本

```xml
<properties>
		<thymeleaf.version>3.0.9.RELEASE</thymeleaf.version>
		<!-- 布局功能的支持程序  thymeleaf3主程序  layout2以上版本 -->
		<!-- thymeleaf2   layout1-->
		<thymeleaf-layout-dialect.version>2.2.2</thymeleaf-layout-dialect.version>
  </properties>
```


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827204659539.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


### Thymeleaf使用
1、在`ThymeleafProperties.java`源码分析
```java
@ConfigurationProperties(prefix = "spring.thymeleaf")
public class ThymeleafProperties {

	private static final Charset DEFAULT_ENCODING = Charset.forName("UTF-8");

	private static final MimeType DEFAULT_CONTENT_TYPE = MimeType.valueOf("text/html");

	public static final String DEFAULT_PREFIX = "classpath:/templates/";

	public static final String DEFAULT_SUFFIX = ".html";
  	//
```

将HTML页面放在classpath:/templates/，thymeleaf就能自动渲染；

使用：

1、导入thymeleaf的名称空间

```xml
<html lang="en" xmlns:th="http://www.thymeleaf.org">
```

2、使用thymeleaf语法；在`rescource/templates`  目录下编写

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
    <h1>成功！</h1>
    <!--th:text 将div里面的文本内容设置为 -->
    <div th:text="${hello}">这是显示欢迎信息</div>
</body>
</html>
```
3、在`HelloController.java`中编写java核心代码
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827211554623.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
==注意==：
（1）没有方法上`@ResponseBody`
（2）是`@Controller`而不是`@RestController`
（3）加上`@ResponseBody` 不解析（SpringMVC内容）
### 语法规则
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200828155822469.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
官方文档---> 第十章
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082815591985.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 表达式
**一**、Simple expressions:（表达式语法）

   Variable Expressions: `${...}：`获取变量值；OGNL；
（1）获取对象的属性、调用方法
（2）使用内置的基本对象：
  

```bash
#ctx : the context object.
#vars: the context variables.
#locale : the context locale.
#request : (only in Web Contexts) the HttpServletRequest object.
#response : (only in Web Contexts) the HttpServletResponse object.
#session : (only in Web Contexts) the HttpSession object.
#servletContext : (only in Web Contexts) the ServletContext object.          
```
 ${session.foo}
（3）内置的一些工具对象：

```bash
#execInfo : information about the template being processed.
#messages : methods for obtaining externalized messages inside variables expressions, in the same way as they would be obtained using #{…} syntax.
#uris : methods for escaping parts of URLs/URIs
#conversions : methods for executing the configured conversion service (if any).
#dates : methods for java.util.Date objects: formatting, component extraction, etc.
#calendars : analogous to #dates , but for java.util.Calendar objects.
#numbers : methods for formatting numeric objects.
#strings : methods for String objects: contains, startsWith, prepending/appending, etc.
#objects : methods for objects in general.
#bools : methods for boolean evaluation.
#arrays : methods for arrays.
#lists : methods for lists.
#sets : methods for sets.
#maps : methods for maps.
#aggregates : methods for creating aggregates on arrays or collections.
#ids : methods for dealing with id attributes that might be repeated (for example, as a result of an iteration).
```

 **二**、Selection Variable Expressions: `*{...}`：选择表达式：和`${}`在功能上是一样作为补充：配合 `th:object="${session.user}：`

```html
   <div th:object="${session.user}">
    <p>Name: <span th:text="*{firstName}">Sebastian</span>.</p>
    <p>Surname: <span th:text="*{lastName}">Pepper</span>.</p>
    <p>Nationality: <span th:text="*{nationality}">Saturn</span>.</p>
    </div>
```
    
 **三**、Message Expressions: `#{...}`：获取国际化内容
  **四**、Link URL Expressions: `@{...}`：定义URL；

```bash
   @{/order/process(execId=${execId},execType='FAST')}
```
 **五**、Fragment Expressions: `~{...}`：片段引用表达式

```bash
  <div th:insert="~{commons :: main}">...</div>
```
    
---		
①**Literals**（字面量）
      Text literals: 'one text' , 'Another one!' ,…
      Number literals: 0 , 34 , 3.0 , 12.3 ,…
      Boolean literals: true , false
      Null literal: null
      Literal tokens: one , sometext , main ,…
      
②**Text operations**:（文本操作）
    String concatenation: +
    Literal substitutions: |The name is ${name}|
    
③**Arithmetic operations**:（数学运算）
    Binary operators: + , - , * , / , %
    Minus sign (unary operator): -
    
④**Boolean operations**:（布尔运算）
    Binary operators: and , or
    Boolean negation (unary operator): ! , not
    
⑤**Comparisons and equality**:（比较运算）
    Comparators: > , < , >= , <= ( gt , lt , ge , le )
    Equality operators: == , != ( eq , ne )
    
⑥**Conditional operators**:条件运算（三元运算符）
    If-then: (if) ? (then)
    If-then-else: (if) ? (then) : (else)
    Default: (value) ?: (defaultvalue)
    
⑦**Special tokens**:
    No-Operation: _ 


## SpringMVC自动配置
[官方文档参考](https://docs.spring.io/spring-boot/docs/1.5.10.RELEASE/reference/htmlsingle/#boot-features-developing-web-applications)


Spring MVC auto-configuration   ,Spring Boot 自动配置好了SpringMVC


**原理**：

(1) WebMvcAutoConfiguration是SpringMVC的自动配置类

​(2) 在做其他自动配置时会导入；@Import(**EnableWebMvcConfiguration**.class)

### 全面接管SpringMVC；

SpringBoot对SpringMVC的自动配置不需要了，所有都是我们自己配置；所有的SpringMVC的自动配置都失效了

**我们需要在配置类中添加@EnableWebMvc即可；**

```java
//使用WebMvcConfigurerAdapter可以来扩展SpringMVC的功能
@EnableWebMvc
@Configuration
public class MyMvcConfig extends WebMvcConfigurerAdapter {

    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
       // super.addViewControllers(registry);
        //浏览器发送 /atguigu 请求来到 success
        registry.addViewController("/atguigu").setViewName("success");
    }
}
```

注意：方法接口可能存在过时
### 修改SpringBoot的默认配置
模式流程：

​（1）SpringBoot在自动配置很多组件的时候，先看容器中有没有用户自己配置的（@Bean、@Component）如果有就用用户配置的，如果没有，才自动配置；如果有些组件可以有多个（ViewResolver）将用户配置的和自己默认的组合起来；
（2）在SpringBoot中会有非常多的`xxxConfigurer`帮助我们进行扩展配置

​（3）在SpringBoot中会有很多的`xxxCustomizer`帮助我们进行定制配置

## 国际化
关于i8n 的来源：
i18n（其来源是英文单词 internationalization的首末字符i和n，18为中间的字符数）是“国际化”的简称
[百度百科参考](https://baike.baidu.com/item/I18N/6771940?fr=aladdin)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082822192680.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
上述修改好之后，需在相关静态资源中进行修改才可以显示
eg:  `th:text="#{login.password}"` 运用前面所学表达式语法
国际化语言转化源码参考`MessageSourceAutoConfiguration.java`

### 总结
1.首页配置：注意将所有页面的静态资源使用 thymeleaf接管；`@{}`
2.页面国际化
（1）需要配置i18n文件
（2）需求在项目中进行按钮自动切换，需要自定义一个组件 `LocaleResolver`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200829002714572.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
`MyLocaleResolver.java`代码
```java

public class MyLocaleResolver implements LocaleResolver {

    // 解析请求
    @Override
    public Locale resolveLocale(HttpServletRequest httpServletRequest) {
//获取请求中语言参数
        String language = httpServletRequest.getParameter("1") ;
        Locale locale = Locale.getDefault();  // 如果没有使用默认

        // 如果请求链接带有国际化参数
        if(!StringUtils.isEmpty(language)){
            //zh_CN
            String[] split = language.split("_") ;
            // 国家 地区
            locale = new Locale(split[0],split[1]) ;
        }
        return   locale;
    }

    @Override
    public void setLocale(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Locale locale) {

    }
}
```

（3）注意将自己写的组件配置到 spring容器 `@Bean`(如下图)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200829002636784.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


## 同时编写可视化操作
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200828222416547.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

# 常见异常及其错误

## ①Thymeleaf版本错误
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827210811844.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


```bash
Action:

Correct the classpath of your application so that it contains a single, compatible version of org.thymeleaf.spring5.SpringTemplateEngine
```
原因：Thymeleaf版本错误，将其改为如下版本
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827211326699.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

