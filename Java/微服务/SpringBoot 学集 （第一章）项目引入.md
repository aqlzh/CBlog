**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
 

> 编程路漫之远兮，运架构式之简化；    
> 劝君专注案前事，亦是杯酒敬苍生

@[toc]
# SpringBoot概述
## 优点：
1、快速创建独立运行的Spring项目以及与主流框架集成
2、 使用嵌入式的Servlet容器，应用**无需打成WAR包** – starters自动依赖与版本控制
3、大量的自动配置，简化开发，也可修改默认值 – 无需配置XML，无代码生成，开箱即用
4、准生产环境的运行时应用监控 、与云计算的天然集成
![在这里插入图片描述](https://img-blog.csdnimg.cn/202008242241526.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 微服务引入
[微服务参考翻译文档](https://www.jianshu.com/p/d32b053e86e1)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200824234856500.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
**单体应用**：ALL IN ONE
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200824234913274.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
**微服务**：每一个功能元素最终都是一个可独立替换和独立升级的软件单元；

## 环境部署
应具备以下环境: jdk 、 maven、 IDEA、 SpringBoot 及其应用
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825102744985.png#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825103046113.png#pic_center)
# 开始项目工程
### 导入springboot 相关依赖
在`pom.xml` 中进行导入
```xml
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>1.5.9.RELEASE</version>
    </parent>
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
    </dependencies>
```
### 编写hello测试与编写相关的Controller、Service
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825153528640.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```java
public class hello {

    public static void main(String[] args) {

        // Spring应用启动起来
        SpringApplication.run(hello.class,args);
    }
}
```

```java
@Controller
public class HelloController {

    @ResponseBody
    @RequestMapping("/hello")
    public String hello(){
        return "Hello World!";
    }
}
```

**分别请求**`http://localhost:8080`与`http://localhost:8080/hello`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825153606118.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825153644329.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 简化部署
首先在`pom.xml`文件中进行配置
```xml
 <!-- 这个插件，可以将应用打包成一个可执行的jar包；-->
    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825155417560.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825155714697.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


将应用打成jar包，如上直接使用java -jar的命令进行执行


## 依赖原理探究
### 父项目
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825160238716.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
可以左键加ctrl查看源代码，其中父项目中还有父项目其为Spring Boot的版本仲裁中心（于dependencies中管理的依赖声明版本号）
### Starters  (启动器)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825155911207.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

[官网链接](https://docs.spring.io/spring-boot/docs/current/reference/html/using-spring-boot.html#using-boot-starter)

Spring Boot将所有的功能场景都抽取出来，做成一个个的starters（，根据项目需求引入相应starter场景，其相关依赖都会相应导入。

### 启动源码分析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825163239533.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825161818986.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
上图说明必须在相应目录结构下才能被扫包

**源码层层分析**：
@**SpringBootApplication**:  标注此说明此类为SpringBoot的主配置类
--->

@**SpringBootConfiguration**:Spring Boot的配置类；
--->
@**Configuration**:配置类上来标注这个注解；
--->
​			配置类 ----->  配置文件( ==本质==容器中的组件)`@Component`

@**EnableAutoConfiguration**：开启自动配置功能；

@**EnableAutoConfiguration**开启自动配置功能

​@**AutoConfigurationPackage**：自动配置包

​@**Import**(AutoConfigurationPackages.Registrar.class)：

==将主配置类（@SpringBootApplication标注的类）的所在包及下面所有子包里面的所有组件扫描到Spring容器；==

​	@**Import**(EnableAutoConfigurationImportSelector.class)；


​**EnableAutoConfigurationImportSelector**：导入组件的选择器；

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825162157118.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 快速创建
创建步骤如图示
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825164806146.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825164941469.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825181815775.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


### 默认目录结构介绍；

- resources文件夹中目录结构
  - static：保存所有的静态资源； js css  images；
  - templates：保存所有的模板页面；（Spring Boot默认jar包使用嵌入式的Tomcat，默认不支持JSP页面）；可以使用模板引擎（freemarker、thymeleaf）；
  - application.properties：Spring Boot应用的配置文件；可以修改一些默认设置；

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825181953859.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
# SpringBoot 配置
## 配置文件
YAML（YAML Ain't Markup Language）

SpringBoot使用全局的配置文件，配置文件名固定如下；

```bash
application.properties
```

```bash
application.yml
```

**配置文件的作用**：根据需求修改SpringBoot自动配置的默认值；


### 今昔对比：

​	以前XML配置文件：  **xxxx.xml**文件

​	现在YAML：**以数据为中心**，比json、xml等更适合做配置文件；

​	XML：

```xml
<server>
	<port>8081</port>
</server>
```
YAML:
```yaml
server:
  port: 8081
```


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200825190214999.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## YAML语法

### 基本语法

k:(空格)v：表示一对键值对；

yaml以**空格**的缩进来控制层级关系；只要是左对齐的一列数据，都是同一个层级的,属性和值也是大小写敏感；

```yaml
server:
    port: 8081
    path: /hello
```
### 值的写法

#### 字面量普通的值（数字，字符串，布尔）
​	k: v：字面直接来写；

​其中字符串默认不用加上单引号或者双引号；

==注意==：

​""：双引号；会**转义**字符串里面的特殊字符

```bash
​name:   "lzh \n qc"
输出: lzh
      qc
```
        
​''：单引号；**不会转义**特殊字符

```bash
​name:   ‘lzh \n qc’：
输出；lzh \n qc
```



#### 对象、Map（属性和值）（键值对）：
​k: v：在下一行来写对象的属性和值的关系,注意缩进表示层级关系

对象还是k: v的方式

```yaml
friends:
		lastName: lzh
		age: 18
```

行内写法：

```yaml
friends: {lastName: lzh,age: 18}
```



#### 数组（List、Set）：

用- 值表示数组中的一个元素

```yaml
pets:
 - cat
 - dog
 - pig
```

行内写法

```yaml
pets: [cat,dog,pig]
```

> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

