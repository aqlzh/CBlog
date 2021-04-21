**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# 日志框架
前情提要：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827111154754.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

[跳转链接](https://blog.csdn.net/QuantumYou/article/details/107871365)

| 日志门面  （日志的抽象层）                                   | 日志实现                                             |
| ------------------------------------------------------------ | ---------------------------------------------------- |
| JCL（Jakarta  Commons Logging） 、  SLF4j（Simple  Logging Facade for Java）、    jboss-logging | Log4j  、JUL（java.util.logging）、  Log4j2、  Logback |



日志门面：  SLF4J；

日志实现：Logback；



SpringBoot：底层是Spring框架，Spring框架默认是用JCL；‘

​	==SpringBoot选用 SLF4j和logback；==

## SLF4j使用
日志记录方法的调用，不直接调用日志的实现类，而是调用日志抽象层里面的方法

每一个日志的实现框架都有自己的配置文件。使用slf4j以后，**配置文件还是做成日志实现框架自己本身的配置文件；**

给系统里面导入slf4j的jar和  logback的实现jar

```java
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class HelloWorld {
  public static void main(String[] args) {
    Logger logger = LoggerFactory.getLogger(HelloWorld.class);
    logger.info("Hello World");
  }
}
```

图示；

[官网寻址](http://www.slf4j.org/manual.html)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827111818365.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 统一日志记录
[官方文档参考](http://www.slf4j.org/legacy.html)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020082711334233.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

使用其他框架和本框架一起统一使用slf4j进行输出

让系统中所有的日志都统一到slf4j方法：

1、将系统中其他日志框架先排除出去
2、用中间包来替换原有的日志框架
3、导入slf4j其他的实现


## SpringBoot日志关系
右键如下图所示
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827115836408.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
分析底层依赖关系
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827120053963.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
底层核心依赖关系如下图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827120331600.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 总结

1、SpringBoot底层是使用slf4j+logback的方式进行日志记录

2、SpringBoot把其他的日志都替换成了slf4j；

​3、内部使用中间替换包

4、引入其他框架，一定要把这个框架的默认日志依赖移除掉

​注意：Spring框架用的是commons-logging；

```xml
		<dependency>
			<groupId>org.springframework</groupId>
			<artifactId>spring-core</artifactId>
			<exclusions>
				<exclusion>
					<groupId>commons-logging</groupId>
					<artifactId>commons-logging</artifactId>
				</exclusion>
			</exclusions>
		</dependency>
```

SpringBoot能自动适配所有的日志，而且底层使用slf4j+logback的方式记录日志，引入其他框架的时候，只需要把这个框架依赖的日志框架排除掉即可

## 日志框架的使用；
### 日志的级别
==由低到高   trace < debug <info（默认） < warn < error==
通过调整输出的日志级别，日志就只会在这个级别以以后的高级别生效

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827125915625.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


### SpringBoot修改日志的默认配置
在`application.properties` 文件下进行修改

1、修改日志的默认级别

```bash
logging.level.com.atguigu=trace
```
2、指定路径在当前项目下生成springboot.log日志也可指定完整的路径

```bash
logging.path=
logging.file=G:/springboot.log
```
 3、在控制台输出的日志的格式，指定文件中日志输出的格式

```bash
logging.pattern.console=%d{yyyy-MM-dd} [%thread] %-5level %logger{50} - %msg%n
```

```bash
logging.pattern.file=%d{yyyy-MM-dd} === [%thread] === %-5level === %logger{50} ==== %msg%n
```

| logging.file | logging.path | Example  | Description                        |
| ------------ | ------------ | -------- | ---------------------------------- |
| (none)       | (none)       |          | 只在控制台输出                     |
| 指定文件名   | (none)       | my.log   | 输出日志到my.log文件               |
| (none)       | 指定目录     | /var/log | 输出到指定目录的 spring.log 文件中 |


### 日志输出格式：
%d表示日期时间，
 %thread表示线程名，
 %-5level：级别从左显示5个字符宽度
  %logger{50} 表示logger名字最长50个字符，否则按照句点分割。 
  %msg：日志消息，
   %n是换行符
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827130717198.png#pic_center)

### 指定配置
[官方文档参考](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-logging)



| Logging System          | Customization                                                |
| ----------------------- | ------------------------------------------------------------ |
| Logback                 | `logback-spring.xml`, `logback-spring.groovy`, `logback.xml` or `logback.groovy` |
| Log4j2                  | `log4j2-spring.xml` or `log4j2.xml`                          |
| JDK (Java Util Logging) | `logging.properties`                                         |

==注意：==
1、logback.xml：日志框架直接识别

2、**logback-spring.xml**：由SpringBoot解析日志配置，可以使用SpringBoot的高级Profile功能（与下图相似）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827132309440.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
[链接导航](https://blog.csdn.net/QuantumYou/article/details/108244611)

可以指定某段配置只在某个环境下生效
```xml
<springProfile name="staging">
    <!-- configuration to be enabled when the "staging" profile is active -->
  	
</springProfile>

```

如：指定日期格式配置在开发环境下生效

```xml
<appender name="stdout" class="ch.qos.logback.core.ConsoleAppender">
        <layout class="ch.qos.logback.classic.PatternLayout">
            <springProfile name="dev">
                <pattern>%d{yyyy-MM-dd HH:mm:ss.SSS} ----> [%thread] ---> %-5level %logger{50} - %msg%n</pattern>
            </springProfile>
            <springProfile name="!dev">
                <pattern>%d{yyyy-MM-dd HH:mm:ss.SSS} ==== [%thread] ==== %-5level %logger{50} - %msg%n</pattern>
            </springProfile>
        </layout>
    </appender>
```




# 常见错误及其异常
## ①log4j中Logger.getLogger()提示错误
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827123137465.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
导入包错误

应该以下图格式导入正确包

```java
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.junit.jupiter.api.Test;

```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200827124113395.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)



