**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫之远兮，运架构体之帷幄；
劝君专注案前事，亦是杯酒敬苍生；


@[toc]
# 日志
## 日志工厂

解决数据库操作异常，用于排错

曾经的排错工具：sout 、debug        现在：日志工厂



![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808000342269.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
常见的日志工厂：

- SLF4J 
- LOG4J【掌握】
- LOG4J2
- JDK_LOGGING
- COMMONS_LOGGING
- STDOUT_LOGGING   【掌握】
- NO_LOGGING



在Mybatis中具体使用那个一日志实现，在设置中进行设定

**STDOUT_LOGGING标准日志输出**

在mybatis核心配置文件中，配置我们的日志！

```xml
<settings>
    <setting name="logImpl" value="STDOUT_LOGGING"/>
</settings>
```


## Log4j
**Log4j概念**：

- Log4j是[Apache](https://baike.baidu.com/item/Apache/8512995)的一个开源项目，通过使用Log4j，我们可以控制日志信息输送的目的地是[控制台](https://baike.baidu.com/item/控制台/2438626)、文件、[GUI](https://baike.baidu.com/item/GUI)组件，我们也可以控制每一条日志的输出格式；
- 通过定义每一条日志信息的级别，我们能够更加细致地控制日志的生成过程。
- 通过一个[配置文件](https://baike.baidu.com/item/配置文件/286550)来灵活地进行配置，而不需要修改应用的代码。



1. 先在`pom.xml`pom.xml导入log4j的包

   ```xml
   <!-- https://mvnrepository.com/artifact/log4j/log4j -->
     <dependencies>
        <dependency>
            <groupId>log4j</groupId>
            <artifactId>log4j</artifactId>
            <version>1.2.17</version>
        </dependency>
    </dependencies>
   ```


2. 在resources 文件夹下 配置`log4j.properties`

```bash
   #将等级为DEBUG的日志信息输出到console和file这两个目的地，console和file的定义在下面的代码
   log4j.rootLogger=DEBUG,console,file
   
   #控制台输出的相关设置
   log4j.appender.console = org.apache.log4j.ConsoleAppender
   log4j.appender.console.Target = System.out
   log4j.appender.console.Threshold=DEBUG
   log4j.appender.console.layout = org.apache.log4j.PatternLayout
   log4j.appender.console.layout.ConversionPattern=[%c]-%m%n
   
   #文件输出的相关设置
   log4j.appender.file = org.apache.log4j.RollingFileAppender
   log4j.appender.file.File=./log/lzh.log
   log4j.appender.file.MaxFileSize=10mb
   log4j.appender.file.Threshold=DEBUG
   log4j.appender.file.layout=org.apache.log4j.PatternLayout
   log4j.appender.file.layout.ConversionPattern=[%p][%d{yy-MM-dd}][%c]%m%n
   
   #日志输出级别
   log4j.logger.org.mybatis=DEBUG
   log4j.logger.java.sql=DEBUG
   log4j.logger.java.sql.Statement=DEBUG
   log4j.logger.java.sql.ResultSet=DEBUG
   log4j.logger.java.sql.PreparedStatement=DEBUG
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808102318496.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


3. 在`mybatis-config.xm`l配置log4j为日志的实现

   ```xml
   <settings>
       <setting name="logImpl" value="LOG4J"/>
   </settings>
   ```

4. Log4j的使用！，直接测试运行刚才的查询,结果如下图

 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808105042951.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


**使用方法**

1. 在要使用Log4j 的类中，导入包  import org.apache.log4j.Logger;

3. 日志对象，参数为当前类的class

   ```java
   static Logger logger = Logger.getLogger(UserDaoTest.class);
   ```


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808110919101.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

3. 日志级别

   ```java
   logger.info("info:进入了testLog4j");
   logger.debug("debug:进入了testLog4j");
   logger.error("error:进入了testLog4j");
   ```

效果示意图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808112129807.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# 分页
**分页的原因**：节约资源优化查询性能，避免依次查询大量数据，减少数据的处理量


## 使用Limit分页
普通语法：
```sql
SELECT * from user limit startIndex,pageSize;
SELECT * from user limit 3;  #[0,n]
```
选中运行左上角绿色执行键，效果如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808122434430.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)



使用Mybatis实现分页，核心SQL

1. 接口  `UserDao.java`

   ```java
   //分页
   List<User> getUserByLimit(Map<String,Integer> map);
   ```

2. 在`UserMapper.xml`编写SQL语句

   ```xml
   <!--//分页-->
   <select id="getUserByLimit" parameterType="map" resultMap="UserMap">
       select * from  mybatis.user limit #{startIndex},#{pageSize}
   </select>
   ```

3. 在`UserDaoTest.java`中测试

   ```java
   @Test
   public void getUserByLimit(){
   SqlSession sqlSession = MybatisUtils.getSqlSession();
   UserMapper mapper = sqlSession.getMapper(UserMapper.class);
   
   HashMap<String, Integer> map = new HashMap<String, Integer>();
       map.put("startIndex",1);
       map.put("pageSize",2);
   
       List<User> userList =  mapper.getUserByLimit(map);
       for (User user : userList) {
       System.out.println(user);
       }
   
       sqlSession.close();
       }
   
   ```

   

## RowBounds分页（了解）

不再使用SQL实现分页

1. 接口

   ```java
   //分页2
   List<User> getUserByRowBounds();
   ```

2. mapper.xml

   ```xml
   <!--分页2-->
   <select id="getUserByRowBounds" resultMap="UserMap">
       select * from  mybatis.user
   </select>
   ```

3. 测试

   ```java
   @Test
   public void getUserByRowBounds(){
   SqlSession sqlSession = MybatisUtils.getSqlSession();
   
   //RowBounds实现
   RowBounds rowBounds = new RowBounds(1, 2);
   
   //通过Java代码层面实现分页
   List<User> userList = sqlSession.selectList("com.kuang.dao.UserMapper.getUserByRowBounds",null,rowBounds);
   
       for (User user : userList) {
       System.out.println(user);
       }
   
       sqlSession.close();
       }
   ```

   

## 分页插件

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808132803207.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)



[网址链接](https://pagehelper.github.io/)
https://pagehelper.github.io/

# 使用注解开发

## 面向接口编程

 **根本原因 :  ==解耦== , 可拓展 , 提高复用 , 分层开发中 , 上层不用管具体的实现 , 大家都遵守共同的标准 , 使得开发变得容易 , 规范性更好**




**接口理解**

接口从更深层次的理解，应是定义（规范，约束）与实现（名实分离的原则）的分离。
接口的本身反映了系统设计人员对系统的抽象理解。
==接口应有两类==：
 第一类是对一个个体的抽象，它可对应为一个抽象体(abstract class)；
 第二类是对一个个体某一方面的抽象，即形成一个抽象面（interface）； 
  一个体有可能有多个抽象面。抽象体与抽象面是有区别的。



## 三个面向区别

\- 面向对象是指，我们考虑问题时，以对象为单位，考虑它的属性及方法 .
\- 面向过程是指，我们考虑问题时，以一个具体的流程（事务过程）为单位，考虑它的实现 .
\- 接口设计与非接口设计是针对复用技术而言的，与面向对象（过程）不是一个问题.更多的体现就是对系统整体的架构

## 使用注解开发
建议在SQL不复杂的情况下使用

1. 注解在接口上实现

   ```java
   @Select("select * from user")
   List<User> getUsers();
   ```

2. 需要再核心配置文件`mybatis-config.xml`中绑定接口！

   ```xml
   <!--绑定接口-->
   <mappers>
       <mapper class="com.lzh.dao.UserMapper"/>
   </mappers>
   ```
   

   
   注意以下对应关系
---
---
---
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808172253919.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808172301806.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

---
---
---
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808164602141.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
取消之前的方式



==提示==：造成值为空的情况  `null`
==使用注解没有设置别名，用户属性和数据库字段不一致==



3. **测试**



本质：反射机制实现

底层：动态代理！


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808165832919.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

==**Mybatis详细的执行流程！**==
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808165535170.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 使用注解操作CRUD
==使用情形==： 在少量SQL的情况下


我们可以在工具类创建的时候实现自动提交事务！

```java
public static SqlSession  getSqlSession(){
    return sqlSessionFactory.openSession(true);
}
```
简便原因：不用涉及操作`UserMapper.xml`,直接在UserDao.java中编写




编写接口，增加注解

```java
public interface UserMapper {

    @Select("select * from user")
    List<User> getUsers();

 // 方法存在多个参数，所有的参数前面必须加上 @Param("id) 注解
    @Select("select * from user where id = #{id}")
    User getUserById(@Param("id") int id) ;

    @Insert("insert into user(id,name,pwd) value(#{id),#{name},#{password}")
    int addUser (User user) ;

    @Update("update user set name=#{name},pwd=#{password} where id=#{id}")
    int updateUser(User user) ;


    @Delete("delete from user where id=#{id}")
    int deleteUser(@Param("id") int id) ;
}
```
==注意==：方法存在多个参数，所有的参数前面必须加上 @Param("id) 注解


测试类


操作结果图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808192049756.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
【==注意==：我们必须要讲接口注册绑定到我们的核心配置文件中！】如下图
使用接口只能使用一个
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808193522294.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


**关于@Param() 注解**

- 基本类型的参数或者String类型，需要加上
- 引用类型不需要加
- 如果只有一个基本类型的话，可以忽略，但是建议大家都加上！
- 我们在SQL中引用的就是我们这里的 @Param() 中设定的属性名！



**#{}     ${} 区别**
前者可以防止SQL注入问题


# Lombok
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808194809366.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
网址：https://projectlombok.org/
```java
Project Lombok is a java library that automatically plugs into your editor and build tools, spicing up your java.
Never write another getter or equals method again, with one annotation your class has a fully featured builder, Automate your logging variables, and much more.
```





## 使用步骤：

1. 在IDEA中安装Lombok插件

2. 在项目中的`pom.xml`导入lombok的jar包

   ```xml
   <dependency>
       <groupId>org.projectlombok</groupId>
       <artifactId>lombok</artifactId>
       <version>1.18.10</version>
   </dependency>
   ```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808195756567.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

3. 在实体类上加注解即可！

   ```java
   @Data
   @AllArgsConstructor
   @NoArgsConstructor
   ```



```java
@Getter and @Setter
@FieldNameConstants
@ToString
@EqualsAndHashCode
@AllArgsConstructor, @RequiredArgsConstructor and @NoArgsConstructor
@Log, @Log4j, @Log4j2, @Slf4j, @XSlf4j, @CommonsLog, @JBossLog, @Flogger
@Data
@Builder
@Singular
@Delegate
@Value
@Accessors
@Wither
@SneakyThrows
```

重点说明：

```
@Data：无参构造，get、set、tostring、hashcode，equals
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@ToString
@Getter
```
**使用插件前**：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808203434748.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
**使用插件后**：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808203717809.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 优缺点
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808200656735.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# 常见异常
## ①数据库语句错误

```bash
Caused by: com.mysql.jdbc.exceptions.jdbc4.MySQLSyntaxErrorException: You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'null' at line 1
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808124135105.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## ②类找不到异常

```bash
Caused by: java.lang.ClassNotFoundException: Cannot find class: com.lzh.dao.UserMapper
```

原因：`mybatis-config.xml` 文件中的mappers 部分的路径引用错误
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808171709304.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

