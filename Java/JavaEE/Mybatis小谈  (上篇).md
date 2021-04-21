**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~

> 编程路漫之远兮，运架构体之帷幄；
 劝君专注案前事，亦是杯酒敬苍生；

@[toc]
# 概述
MyBatis 是一款优秀的持久层框架，避免了几乎所有的==JDBC== 代码和手动设置参数以及获取结果集的过程， 可以使用简单的 ==XML 或注解==来配置和映射原生信息，将接口和 Java 的 实体类 【Plain Old Java Objects,普通的 Java对象】映射成数据库中的记录。

MyBatis 是一个半自动化的ORM框架 (Object Relationship Mapping) -->对象关系映射

Mybatis官方文档 : 

> http://www.mybatis.org/mybatis-3/zh/index.html

GitHub :

>  https://github.com/mybatis/mybatis-3

Maven 仓库

```java
<!-- https://mvnrepository.com/artifact/org.mybatis/mybatis -->
<dependency>
    <groupId>org.mybatis</groupId>
    <artifactId>mybatis</artifactId>
    <version>3.5.2</version>
</dependency>
```
## 持久化
持久化是将程序数据在==持久状态==和==瞬时状态==间转换的机制。即把数据（如==内存==中的对象）保存到可永久保存的存储设备中（如==磁盘==）。持久化的主要应用是将内存中的对象存储在数据库中，或者存储在磁盘文件中、XML数据文件中等等。

> 注意：JDBC就是一种持久化机制。文件IO也是一种持久化机制。


原因：
①内存断电后数据丢失
②内存过于昂贵。

## 持久层
其他层： Dao层，Service层，Controller层….

- 完成持久化工作的代码块
- 层界限十分明显。
完成持久化工作的代码块 .  ---->  dao层 【DAO (Data Access Object)  数据访问对象】





# MyBatis的优点
**本质**：Mybatis就是帮助我们将数据存入数据库中 , 和从数据库中取数据 .

==传统的jdbc操作== , 有很多重复代码块 .比如 : 数据取出时的封装 , 数据库的建立连接等等... , 通过框架可以减少重复代码,提高开发效率 .

①小巧简单，没有任何第三方依赖

②灵活：sql写在xml里，提供xml标签，支持编写动态sql便于统一管理和优化。解除sql与程序代码的耦合，提高了可维护性

③通过提供DAO层，将业务逻辑和数据访问逻辑分离，使系统的设计更清晰，更易维护，更易单元测试。

# 搭建环境
## 搭建数据库
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805222034344.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
**架构设计器**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805231536121.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# 新建项目
**maven开始**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806131028362.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
1. 新建一个普通的maven项目

2. 删除src目录

3. 导入maven依赖

效果示意图


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806131940603.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 在Idea 中连接数据库
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806134344819.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
连接成功图示如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806134712160.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
其中测试连接数据库失败的原因之一（时区问题）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806140040923.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```bash
show variables like'%time_zone';

 set global time_zone = '+8:00';
```

 【Idea 相关配置】
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805235500998.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 编写mybatis的核心配置文件
```css
 <dataSource type="POOLED">
                <property name="driver" value="com.mysql.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://localhost:3306/mybatistwo?useSSL=true&amp;useUnicode=true&amp;characterEncoding=UTF-8""/>
                <property name="username" value="root"/>
                <property name="password" value="${}"/>
            </dataSource>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806135814597.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
其中：
mybatistwo  为数据库名

### 编写mybatis工具类
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806154206304.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
**核心代码**
提升`sqlSessionFactory`作用域

```java
private static SqlSessionFactory sqlSessionFactory;
```
下为代码块 ，使用 Mybatis 第一步： 获取sqlessionFactory 对象

```java
static{
 
    try {
        String resource = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resource);
        sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
    } catch (IOException e) {
        e.printStackTrace();
    }

    }
```

    获得取SqlSession 实例，SqlSession 完全包含了面向数据库执行 SQL 命令所需的所有方法。
```java
public static SqlSession getSqlSession(){
    return sqlSessionFactory.openSession();
}
```
## 主要代码编写
### 实体类  
get，set 方法有参，空参构造，String等
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080615513194.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### Dao接口

```java
public interface UserDao {
    List<User> getUserList();
}
```
可以体现 Mybatis 的优越性

### Mapper配置文件
接口实现类由原来的UserDaoImpl转变为一个 Mapper配置文件.

```java
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">

<!--namespace=绑定一个对应的Dao/Mapper接口-->

    <mapper namespace="com.lzh.dao.UserDao">
    <select id="getUserList" resultType="com.lzh.pojo.User">
    select * from mybatistwo.user
  </select>
</mapper>
```
namespace=绑定一个对应的Dao/Mapper接口
### 其他拓展
【映射文件配置】（拓展）
创建 `User.xml` 文件

```css
<mapper namespace="user">
    <select id="findUserById" parameterType="int" resultType="com.lzh.model.User">
        SELECT * FROM user WHERE id = #{a}
    </select>
```
  
    [id]：statement的id，要求在命名空间内唯一
    [parameterType]：入参的java类型
    [resultType]：查询出的单条结果集对应的java类型
    [#{}]： 表示一个占位符?
    [#{id}]：表示该占位符待接收参数的名称为id。
    注意：如果参数为简单类型时，#{}里面的参数名称可以是任意定义


【配置加载映射文件】（拓展）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806003123224.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


## 测试
==注意==： test目录与src 目录结构一一对应

### junit 测试

```java
@Test
public void test(){
    //第一步：获得SqlSession对象
    SqlSession sqlSession = MybatisUtils.getSqlSession();


    //方式一：getMapper
    UserDao userDao = sqlSession.getMapper(UserDao.class);
    List<User> userList = userDao.getUserList();

    for (User user : userList) {
        System.out.println(user);
    }



    //关闭SqlSession
    sqlSession.close();
}

```



### 常见异常解析（关键）
①==异常一== 未绑定异常

```java
org.apache.ibatis.binding.BindingException: Type interface com.kuang.dao.UserDao is not known to the MapperRegistry.
```
解决：`mybatis-config.xml` 中优化配置
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806164536203.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
②==异常二==资源过滤问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806164812851.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806163819401.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
<!--在build中配置resources，来防止我们资源导出失败的问题-->
<build>
    <resources>
        <resource>
            <directory>src/main/resources</directory>
            <includes>
                <include>**/*.properties</include>
                <include>**/*.xml</include>
            </includes>
            <filtering>true</filtering>
        </resource>
        <resource>
            <directory>src/main/java</directory>
            <includes>
                <include>**/*.properties</include>
                <include>**/*.xml</include>
            </includes>
            <filtering>true</filtering>
        </resource>
    </resources>
</build>
```



③==异常三==jdk版本不兼容问题

```bash
Error:java: 不再支持源选项 5。请使用 6 或更高版本。
```

解法：在`pom.xml` 配置文件加上如下代码

```java
<properties>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
        <maven.compiler.encoding>UTF-8</maven.compiler.encoding>
        <java.version>11</java.version>
        <maven.compiler.source>11</maven.compiler.source>
        <maven.compiler.target>11</maven.compiler.target>
    </properties>
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806194912467.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806194932974.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

④==异常四== 编码问题
case1：
```bash
1 字节的 UTF-8 序列的字节 1 无效。
```
case2：
`org.xml.sax.SAXParseException:` 元素内容必须由格式正确的字符数据或标记组成,的错误问题
解法：
（1）配置文件不能有中文注释

（2）在 `mybatis-config.xml` ,样式如下图

```bash
useSSL=true   ---->  useSSL=false
characterEncoding=UTF-8   -->  characterEncoding=UTF8 
```
（3）clean Maven 的缓存
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806173706960.png)

### 常见问题
1. 配置文件没有注册
2. 绑定接口错误。
3. 方法名不对
4. 返回类型不对
5. Maven导出资源问题

注意 : 依赖的时候注意依赖版本与本地版本一致


### 七步曲
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806210511290.png)


> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

