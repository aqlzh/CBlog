**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~

> 编程路漫之远兮，运架构体之帷幄；  
> 劝君专注案前事，亦是杯酒敬苍生；

@[toc]
# CRUD
## 前序
namespace ： namespace中的包名要和 Dao/mapper 接口的包名一致，id对应其中的方法。
如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806220253411.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

  
习惯：`UserDao.java`  ---> `UserMapper.java`


## Select

选择，查询语句;

- id : 就是对应的namespace中的方法名；
- resultType：Sql语句执行的返回值！
- parameterType ： 参数类型！



1. 编写接口

   ```java
   //根据ID查询用户
   User getUserById(int id);
   ```

2. 编写对应的mapper中的sql语句

   ```java
   <select id="getUserById" parameterType="int" resultType="com.kuang.pojo.User">
           select * from mybatis.user where id = #{id}
   </select>
   
   ```

3. 测试

   ```java
       @Test
       public void getUserById() {
           SqlSession sqlSession = MybatisUtils.getSqlSession();
   
           UserMapper mapper = sqlSession.getMapper(UserMapper.class);
   
           User user = mapper.getUserById(1);
           System.out.println(user);
   
           sqlSession.close();
       }
   
   ```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806222756991.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## Insert

```java
  <!--对象中的属性，可以直接取出来-->
   <insert id="addUser" parameterType="com.kuang.pojo.User">
    insert into mybatis.user (id, name, pwd) values (#{id},#{name},#{pwd});
</insert>
```


## Update

```xml
    <update id="updateUser" parameterType="com.kuang.pojo.User">
        update mybatis.user set name=#{name},pwd=#{pwd}  where id = #{id} ;
    </update>

```

## Delete

```xml
    <delete id="deleteUser" parameterType="int">
        delete from mybatis.user where id = #{id};
    </delete>
```
## 模糊查询
1. Java代码执行的时候，传递通配符 % %
UserDaoTest.java
   ```java
   List<User> userList = mapper.getUserLike("%李%");
   ```

2. 在sql拼接中使用通配符！
UserMapper.xml
   ```java
   select * from mybatis.user where name like "%"#{value}"%"
   ```

> 注意：字符串拼接sql注入问题


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807141058444.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### CRUD常见错误分析

- 标签不要匹配错
- resource 绑定mapper，需要使用路径！
- 程序配置文件必须符合规范！
- NullPointerException，没有注册到资源!
- 输出的xml文件中存在中文乱码问题！
- maven资源没有导出问题！

## 万能Map构造器
假设，我们的实体类，或者数据库中的表，字段或者参数过多，我们应当考虑使用Map！

UserDao.java

```java
    //万能的Map
    int addUser2(Map<String,Object> map);

```
UserMapper.xml
```xml
    <!--对象中的属性，可以直接取出来    传递map的key-->
    <insert id="addUser" parameterType="map">     //核心
        insert into mybatis.user (id, pwd) values (#{userid},#{passWord});
    </insert>
```
UserDaoTest.java
```xml
    @Test
    public void addUser2(){
        SqlSession sqlSession = MybatisUtils.getSqlSession();

        UserMapper mapper = sqlSession.getMapper(UserMapper.class); 


        Map<String, Object> map = new HashMap<String, Object>();   //核心

        map.put("userid",5);
        map.put("passWord","2222333");

        mapper.addUser2(map);

        sqlSession.close();
    }

```



Map传递参数，直接在sql中取出key即可！    【parameterType="map"】

对象传递参数，直接在sql中取对象的属性即可！【parameterType="Object"】

只有一个基本类型参数的情况下，可以直接在sql中取到！

多个参数用Map，**或者注解！**


# 配置分析
## 核心配置文件
 `mybatis-config.xml` MyBatis 的配置文件包含了会深深影响 MyBatis 行为的设置和属性信息。 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807141250818.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 环境配置（environments）

MyBatis 可以配置成适应多种环境

**不过要记住：尽管可以配置多个环境，但每个 SqlSessionFactory 实例只能选择一种环境。**

学会使用配置多套运行环境！

Mybatis默认的事务管理器就是 JDBC  ， 连接池 ： POOLED
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807143100579.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807143702139.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## xml标签顺序
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807144657739.png)
==在xml 标签中各标签的顺序==，不能颠倒，xml语法严格

## 属性
### 配置文件db.properties
编写配置文件`db.properties`


```bash
driver=com.mysql.jdbc.Driver
url=jdbc:mysql://localhost:3306/mybatis?useSSL=true&useUnicode=true&characterEncoding=UTF-8
username=root
password=
```
在核心配置文件中映入

```xml
    <!--引入外部配置文件-->
    <properties resource="db.properties">
        <property name="username" value="root"/>
        <property name="pwd" value="11111"/>
    </properties>

```

- 可以直接引入外部文件
- 可以在其中增加一些属性配置
- 如果两个文件有同一个字段，优先使用外部配置文件的！

 
### 类型别名（typeAliases）

- 类型别名是为 Java 类型设置一个短的名字。‘
- 存在的意义仅在于用来减少类完全限定名的冗余。

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080718133553.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

==法一==：可以给实体类起别名
```xml
    
    <typeAliases>
        <typeAlias type="com.kuang.pojo.User" alias="User"/>
    </typeAliases>
```

==法二==：指定一个包名，MyBatis 会在包名下面搜索需要的 Java Bean，比如：

扫描实体类的包，它的默认别名就为这个类的 类名，首字母小写！

```xml
<!--可以给实体类起别名-->
<typeAliases>
    <package name="com.kuang.pojo"/>
</typeAliases>
```



在实体类比较少的时候，使用第一种方式。

如果实体类十分多，建议使用第二种。

第一种可以DIY别名（自定义），第二种则·不行·，如果非要改，需要在实体上增加注解

```java
@Alias("user")
public class User {}
```

### 设置

这是 MyBatis 中极为重要的调整设置，它们会改变 MyBatis 的运行时行为。 
一个配置完整的 settings 元素的示例如下：
```java
<settings>
  <setting name="cacheEnabled" value="true"/>
  <setting name="lazyLoadingEnabled" value="true"/>
  <setting name="multipleResultSetsEnabled" value="true"/>
  <setting name="useColumnLabel" value="true"/>
  <setting name="useGeneratedKeys" value="false"/>
  <setting name="autoMappingBehavior" value="PARTIAL"/>
  <setting name="autoMappingUnknownColumnBehavior" value="WARNING"/>
  <setting name="defaultExecutorType" value="SIMPLE"/>
  <setting name="defaultStatementTimeout" value="25"/>
  <setting name="defaultFetchSize" value="100"/>
  <setting name="safeRowBoundsEnabled" value="false"/>
  <setting name="mapUnderscoreToCamelCase" value="false"/>
  <setting name="localCacheScope" value="SESSION"/>
  <setting name="jdbcTypeForNull" value="OTHER"/>
  <setting name="lazyLoadTriggerMethods" value="equals,clone,hashCode,toString"/>
</settings>
```

下图为重要掌握：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807181753826.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080718181683.png)


### 其他配置
了解即可
（1）[typeHandlers（类型处理器）](https://mybatis.org/mybatis-3/zh/configuration.html#typeHandlers)
（2）[objectFactory（对象工厂）](https://mybatis.org/mybatis-3/zh/configuration.html#objectFactory)
（3）plugins插件
  - mybatis-generator-core
  - mybatis-plus
  - 通用mapper

### 映射器（mappers）

MapperRegistry：注册绑定我们的Mapper文件；
每一个Mapper.XML都需要在Mybatis核心配置文件中注册

方式一： 【推荐使用】

```xml
<!--每一个Mapper.XML都需要在Mybatis核心配置文件中注册！-->
<mappers>
    <mapper resource="com/kuang/dao/UserMapper.xml"/>
</mappers>
```

方式二：使用class文件绑定注册

```xml
<!--每一个Mapper.XML都需要在Mybatis核心配置文件中注册！-->
<mappers>
    <mapper class="com.kuang.dao.UserMapper"/>
</mappers>
```

注意点：

- 接口和他的Mapper配置文件必须同名！
- 接口和他的Mapper配置文件必须在同一个包下！



方式三：使用扫描包进行注入绑定

```xml
<!--每一个Mapper.XML都需要在Mybatis核心配置文件中注册！-->
<mappers>
    <package name="com.kuang.dao"/>
</mappers>
```

注意点：

- 接口和他的Mapper配置文件必须同名！
- 接口和他的Mapper配置文件必须在同一个包下！
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807183749590.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)







### 生命周期和作用域

生命周期和作用域，是至关重要的，因为错误的使用会导致非常严重的**并发问题**。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807184055820.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


**SqlSessionFactoryBuilder：**

- 一旦创建了 SqlSessionFactory，就不再需要它了
- 局部变量

**SqlSessionFactory：**

- 类似于：数据库连接池
- SqlSessionFactory 一旦被创建就应该在应用的运行期间一直存在，**没有任何理由丢弃它或重新创建另一个实例。** 
- 因此 SqlSessionFactory 的最佳作用域是应用作用域。 
- 最简单的就是使用**单例模式**或者静态单例模式。

**SqlSession**

- 连接到连接池的一个请求！
- SqlSession 的实例不是线程安全的，因此是不能被共享的，所以它的最佳的作用域是请求或方法作用域。
- 用完之后需要赶紧关闭，否则资源被占用！

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807185147505.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


这里面的每一个Mapper，就代表一个具体的业务

### ResultMap
**解决属性名和字段名不一致的问题**

**Q1**:

数据库中的字段

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807190026450.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

新建一个项目，拷贝之前的，测试实体类字段不一致的情况

```java
public class User {
    
    private int id;
    private String name;
    private String password;
}
```

测试出现问题

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807190111296.png)



```xml
//    select * from mybatis.user where id = #{id}
//类型处理器
//    select id,name,pwd from mybatis.user where id = #{id}
```



==解决方法==：

- 起别名

  ```xml
  <select id="getUserById" resultType="com.kuang.pojo.User">
      select id,name,pwd as password from mybatis.user where id = #{id}
  </select>
  ```



**resultMap**

结果集映射

```
id   name   pwd
id   name   password
```

```xml
<!--结果集映射-->
<resultMap id="UserMap" type="User">
    <!--column数据库中的字段，property实体类中的属性-->
    <result column="id" property="id"/>
    <result column="name" property="name"/>
    <result column="pwd" property="password"/>
</resultMap>

<select id="getUserById" resultMap="UserMap">
    select * from mybatis.user where id = #{id}
</select>
```



- `resultMap` 元素是 MyBatis 中最重要最强大的元素
- ResultMap 的设计思想是，对于简单的语句根本不需要配置显式的结果映射，而对于复杂一点的语句只需要描述它们的关系就行了。

[官方文档](https://mybatis.org/mybatis-3/zh/sqlmap-xml.html)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200807191346101.png)

# 常见异常总结
## ①mapper.xml 文件参数问题
```bash
org.apache.ibatis.builder.IncompleteElementException
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806223312250.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
注意：增删改查需要提交事务
## ②添加参数异常
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080623141578.png)
原因：User.java 缺少方法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806231519834.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
 public User(int id, String name, String pwd) {
        this.id = id;
        this.name = name;
        this.pwd = pwd;
    }
```
## ③ 返回Null

```bash
org.apache.ibatis.binding.BindingException: Mapper method 'com.lzh.dao.UserDao.addUser attempted to return null from a method with a primitive return type (int).
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200806231707886.png)
原因：UserMapper.xml  中sql 部分标签未改

```css
<select></select>    --->  <insert></insert>
```
## ④没有参数

```bash
Error:(86, 37) java: 无法将接口 com.lzh.dao.UserDao中的方法 getUserLike应用到给定类型;
  需要: 没有参数
  找到: java.lang.String
  原因: 实际参数列表和形式参数列表长度不同
```
原因：
（1）`User.java`  set,get,toString 方法缺少
（2） UserDao.java   没有传入值  
```bash
List<User> getUserLike()    --->  List<User> getUserLike(String name) 
```

> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

