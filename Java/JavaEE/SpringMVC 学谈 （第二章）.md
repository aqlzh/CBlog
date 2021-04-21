**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~

> 编程路漫之远兮，运架构式之简化
>  劝君专注案前事，亦是杯酒敬苍生；

@[toc]
# 控制器Controller
**概述**：控制器负责提供访问应用程序的行为，通常通过==接口定义==或==注解定义==两种方法实现。

**作用**：控制器负责解析用户的请求并将其转换为一个模型。在Spring MVC中一个控制器类可以包含多个方法，对于Controller的配置方式有很多种


## 实现Controller接口

Controller是一个接口，在`org.springframework.web.servlet.mvc`包下，接口中只有以下一个方法；

```java
//实现该接口的类获得控制器功能
public interface Controller {
   //处理请求且返回一个模型与视图对象
   ModelAndView handleRequest(HttpServletRequest var1, HttpServletResponse var2) throws Exception;
}
```
测试



```java
//定义控制器
//注意点：不要导错包，实现Controller接口，重写方法；
public class ControllerTest1 implements Controller {

   public ModelAndView handleRequest(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse) throws Exception {
       //返回一个模型视图对象
       ModelAndView mv = new ModelAndView();
       mv.addObject("msg","Test1Controller");
       mv.setViewName("test");
       return mv;
  }
}
```


编写完毕后，去Spring配置文件中注册请求的`bean`，`name`对应请求路径，`class`对应处理请求的类

```java
<bean name="/t1" class="com.kuang.controller.ControllerTest1"/>
编写前端test.jsp，注意在WEB-INF/jsp目录下编写，对应我们的视图解析器

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


**注意**：实现接口Controller定义控制器是较老的办法

**缺点**：一个控制器中只有一个方法，如果要多个方法则需要定义多个Controller；定义的方式比较麻烦；

> Tips: 
> @Component   组件
>  @Service     service 
>  @Controller    controller
> @Repository    dao
> 
> 
> MVVM:    M  V   VM(ViewModel双向绑定)

类上标注@Controller  且方法上没有标注@ResponseBody,return的值会被视图解析器处理----->  被此注解标注的类，所有方法，如果返回值式String ,并且有具体的夜面可以跳转，那么就会被视图解析器解析
## 使用注解编写（重要）
### @Controller操作
可见Spring学记 （第二章）
[跳转](https://blog.csdn.net/QuantumYou/article/details/108034299)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821102726844.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

`@Controller`注解类型用于声明Spring类的实例是一个控制器（IOC还有另外3个注解）；

1、Spring可以使用扫描机制来找到应用程序中所有基于注解的控制器类，为了保证Spring能找到控制器，需要在配置文件中声明组件扫描。

```xml
<!-- 自动扫描指定的包，下面所有注解类交给IOC容器管理 -->
<context:component-scan base-package="com.kuang.controller"/>
```

2、增加一个ControllerTest2类，使用注解实现；

```java
//@Controller注解的类会自动添加到Spring上下文中
@Controller
public class ControllerTest2{

   //映射访问路径
   @RequestMapping("/t2")
   public String index(Model model){
       //Spring MVC会自动实例化一个Model对象用于向视图中传值
       model.addAttribute("msg", "ControllerTest2");
       //返回视图位置
       return "test";
  }

}
```

3、运行tomcat测试

**总结**：我们的两个请求都可以指向一个视图，但是页面结果的结果是不一样的，从这里可以看出视图是被复用的，而控制器与视图之间是==弱偶合关系==。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821112124466.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821112509536.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821111847965.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### @RequestMapping操作
`@RequestMapping`注解用于映射url到控制器类或一个特定的处理程序方法。可用于类或方法上。用于类上，表示类中的所有响应请求的方法都是以该地址作为父路径。

①**只注解在方法上面情况**

```java
@Controller
public class TestController {
   @RequestMapping("/h1")
   public String test(){
       return "test";
  }
}
```

访问路径：http://localhost:8080 / 项目名 / h1

==项目名==  --->   ==Application.context==
②**同时注解类与方法**

```java
@Controller
@RequestMapping("/admin")
public class TestController {
   @RequestMapping("/h1")
   public String test(){
       return "test";
  }
}
```

访问路径：http://localhost:8080 / 项目名/ admin /h1  , 需要先指定**类的路径**再指定方法的路径；
# RestFul 风格
**概念**:Restful就是一个资源定位及资源操作的风格。基于这个风格设计的软件可以**更简洁，更有层次，更易于实现缓存**等机制。


**资源操作**：使用POST、DELETE、PUT、GET，使用不同方法对资源进行操作。

## 传统方式
操作资源  ：通过不同的参数（post 和 get）来实现不同的效果

	http://127.0.0.1/item/queryItem.action?id=1 查询,GET

	http://127.0.0.1/item/saveItem.action 新增,POST

	http://127.0.0.1/item/updateItem.action 更新,POST

	http://127.0.0.1/item/deleteItem.action?id=1 删除,GET或POST
	
	
实际代码：	
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821125200368.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

实际效果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821125029908.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## 使用RestFul
使用RESTful操作资源 ：可以通过不同的请求方式来实现不同的效果

	http://127.0.0.1/item/1 查询,GET

	http://127.0.0.1/item 新增,POST

	http://127.0.0.1/item 更新,PUT

	http://127.0.0.1/item/1 删除,DELETE

实际测试：

代码：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821130742132.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
实际效果图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821130706945.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082113341970.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

**路径变量的优点**：

（1）使路径变得更加简洁；

（2）获得参数更加方便，框架会自动进行类型转换。

（3）通过路径变量的类型可以约束访问参数，如果类型不一样，则访问不到对应的请求方法，


**深入测试**：
```java
//映射访问路径
@RequestMapping("/commit/{p1}/{p2}")
public String index(@PathVariable int p1, @PathVariable String p2, Model model){

   String result = p1+p2;
   //Spring MVC会自动实例化一个Model对象用于向视图中传值
   model.addAttribute("msg", "结果："+result);
   //返回视图位置
   return "test";

}
```

使用method属性指定请求类型

用于**约束请求**的类型，可以收窄请求范围。指定请求谓词的类型如GET, POST, HEAD, OPTIONS, PUT, PATCH, DELETE, TRACE等


```java
//映射访问路径,必须是POST请求
@RequestMapping(value = "/hello",method = {RequestMethod.POST})
public String index2(Model model){
   model.addAttribute("msg", "hello!");
   return "test";
}
```

如果使用浏览器地址栏进行访问默认是Get请求，会报错405：


解法：将POST修改为GET则正常了；

```java
//映射访问路径,必须是Get请求
@RequestMapping(value = "/hello",method = {RequestMethod.GET})
public String index2(Model model){
   model.addAttribute("msg", "hello!");
   return "test";
}
```

### 总结
（1）Spring MVC 的 `@RequestMapping` 注解能够处理 HTTP 请求的方法（GET, PUT, POST, DELETE ,PATCH）。所有的地址栏请求默认都会是 HTTP GET 类型的。

（2）方法级别的注解变体有如下几个：组合注解

@GetMapping
@PostMapping
@PutMapping
@DeleteMapping
@PatchMapping

@GetMapping 是一个组合注解，常用，实质 @RequestMapping(method =RequestMethod.GET) 的一个快捷方式。

# 结果跳转方式

## ModelAndView

设置`ModelAndView`对象 , 根据view的名称 , 和视图解析器跳到指定的页面 .

**页面** : {视图解析器前缀} + viewName +{视图解析器后缀}

```xml
<!-- 视图解析器 -->
<bean class="org.springframework.web.servlet.view.InternalResourceViewResolver"
     id="internalResourceViewResolver">
   <!-- 前缀 -->
   <property name="prefix" value="/WEB-INF/jsp/" />
   <!-- 后缀 -->
   <property name="suffix" value=".jsp" />
</bean>
```

对应的controller类

```java
public class ControllerTest1 implements Controller {

   public ModelAndView handleRequest(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse) throws Exception {
       //返回一个模型视图对象
       ModelAndView mv = new ModelAndView();
       mv.addObject("msg","ControllerTest1");
       mv.setViewName("test");
       return mv;
  }
}
```


## ServletAPI

通过设置ServletAPI , **不需要视图解析器** .

1、通过HttpServletResponse进行输出

2、通过HttpServletResponse实现重定向

3、通过HttpServletResponse实现转发

```java
@Controller
public class ResultGo {

   @RequestMapping("/result/t1")
   public void test1(HttpServletRequest req, HttpServletResponse rsp) throws IOException {
       rsp.getWriter().println("Hello,Spring BY servlet API");
  }

   @RequestMapping("/result/t2")
   public void test2(HttpServletRequest req, HttpServletResponse rsp) throws IOException {
       rsp.sendRedirect("/index.jsp");
  }

   @RequestMapping("/result/t3")
   public void test3(HttpServletRequest req, HttpServletResponse rsp) throws Exception {
       //转发
       req.setAttribute("msg","/result/t3");
       req.getRequestDispatcher("/WEB-INF/jsp/test.jsp").forward(req,rsp);
  }

}
```


## SpringMVC（重要）

通过SpringMVC来实现转发和重定向 - 无需视图解析器；

测试前，需要将视图解析器注释掉
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821172506691.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 注意区分转发与重定向

```java
@Controller
public class ResultSpringMVC {
   @RequestMapping("/rsm/t1")
   public String test1(){
       //转发
       return "/index.jsp";
  }

   @RequestMapping("/rsm/t2")
   public String test2(){
       //转发二
       return "forward:/index.jsp";
  }

   @RequestMapping("/rsm/t3")
   public String test3(){
       //重定向
       return "redirect:/index.jsp";
  }
}
```

通过SpringMVC来实现转发和重定向 - 有视图解析器；

**重定向**不需要视图解析器 , 本质就是重新请求一个新地方 , 所以注意路径问题.

可以重定向到另外一个请求实现 .

> Tips:
> 
> 重定向不能访问WEB-INF下的资源 
> 转发才会触发视图解析器拼接，重定向不会触发

```java
@Controller
public class ResultSpringMVC2 {
   @RequestMapping("/rsm2/t1")
   public String test1(){
       //转发
       return "test";
  }

   @RequestMapping("/rsm2/t2")
   public String test2(){
       //重定向
       return "redirect:/index.jsp";
       //return "redirect:hello.do"; //hello.do为另一个请求/
  }

}
```


# 数据处理
## 处理提交数据

### 1、提交的域名称和处理方法的参数名一致

提交数据 : http://localhost:8080/hello?name=lzh

处理方法 :

```java
@RequestMapping("/hello")
public String hello(String name){
   System.out.println(name);
   return "hello";
}
```
实际代码：

后台输出 : lzh

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821183423295.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


### 2、提交的域名称和处理方法的参数名不一致
username提交的域的名称 
name处理方法的参数名

提交数据 : http://localhost:8080/hello?username=lzhCreate

处理方法 :

```java
//@RequestParam("username") : username提交的域的名称 .
@RequestMapping("/hello")
public String hello(@RequestParam("username") String name){
   System.out.println(name);
   return "hello";
}
```

后台输出 : lzhCreate


### 3、提交的是一个对象

要求提交的表单域和对象的属性名一致  , 参数使用对象即可

==关于lombok再述==
@Data 只有get post toString()
所以常在下补充

```bash
@AllArgsConstructor
@NoArgsConstructor
```
1、实体类

```java
public class User {
   private int id;
   private String name;
   private int age;
   //构造
   //get/set
   //tostring()
}
```

2、提交数据 : http://localhost:8080/mvc04/user?name=lzh&id=1&age=15

3、处理方法 :

```java
@RequestMapping("/user")
public String user(User user){
   System.out.println(user);
   return "hello";
}
```

后台输出 : User { id=1, name='lzh', age=15 }

> 注意i：如果使用对象的话，前端传递的参数名和对象名必须一致，否则就是null。

## 数据显示到前端

### 第一种 : 通过ModelAndView


```java
public class ControllerTest1 implements Controller {

   public ModelAndView handleRequest(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse) throws Exception {
       //返回一个模型视图对象
       ModelAndView mv = new ModelAndView();
       mv.addObject("msg","ControllerTest1");
       mv.setViewName("test");
       return mv;
  }
}
```


### 第二种 : 通过ModelMap


```java
@RequestMapping("/hello")
public String hello(@RequestParam("username") String name, ModelMap model){
   //封装要显示到视图中的数据
   //相当于req.setAttribute("name",name);
   model.addAttribute("name",name);
   System.out.println(name);
   return "hello";
}
```
加上参数`@RequestParam("username")`代表一定从前端所接收
第三种 : 通过Model

### 第三种：Model

```java
@RequestMapping("/ct2/hello")
public String hello(@RequestParam("username") String name, Model model){
   //封装要显示到视图中的数据
   //相当于req.setAttribute("name",name);
   model.addAttribute("msg",name);
   System.out.println(name);
   return "test";
}
```

### 三者对比总结


`Model`只有几个方法只适合用于储存数据，简化了对于Model对象的操作和理解；

`ModelMap` 继承了 LinkedMap ，除了实现了自身的一些方法，同样的继承 LinkedMap 的方法和特性；

`ModelAndView` 可以在储存数据的同时，可以进行设置返回的逻辑视图，进行控制展示层的跳转。（不常用）




# 常见异常即错误分析
## ①页面无报错但不显示数据
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820232610704.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200820232946943.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821112923106.png#pic_center)
## ②tomcat 输出控制台乱码问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821130853792.png#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821184514791.png#pic_center)

解决：在tomcat的VM配置加上`-Dfile.encoding=UTF-8`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821131011928.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082118443029.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

结果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200821184124526.png#pic_center)



> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想


