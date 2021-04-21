@[toc]
# 数据访问
[官网地址参考](https://docs.spring.io/spring-boot/docs/current/reference/html/using-spring-boot.html#using-boot-starter)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200904111933645.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 一、JDBC
1、`pom.xml` 中的相关配置如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200904112733817.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
2、在`applicatiom.yml`  进行连接配置
```bash
spring:
  datasource:
    username: root
    password: 1********
    url: jdbc:mysql://1*******08/jdbc
    driver-class-name: com.mysql.jdbc.Driver
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200904153320640.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

3、测试
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200904153451531.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
4、实际输出：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200904153540287.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

注意：

​	默认是用`org.apache.tomcat.jdbc.pool.DataSource`作为数据源；

​	数据源的相关配置都在DataSourceProperties里面；

### 自动配置原理：

```bash
org.springframework.boot.autoconfigure.jdbc
```

1、参考DataSourceConfiguration，根据配置创建数据源，默认使用Tomcat连接池；可以使用spring.datasource.type指定自定义的数据源类型；

2、SpringBoot默认可以支持；

```
org.apache.tomcat.jdbc.pool.DataSource、HikariDataSource、BasicDataSource、
```

3、自定义数据源类型

```java
/**
 * Generic DataSource configuration.
 */
@ConditionalOnMissingBean(DataSource.class)
@ConditionalOnProperty(name = "spring.datasource.type")
static class Generic {

   @Bean
   public DataSource dataSource(DataSourceProperties properties) {
       //使用DataSourceBuilder创建数据源，利用反射创建响应type的数据源，并且绑定相关属性
      return properties.initializeDataSourceBuilder().build();
   }

}
```

4、**DataSourceInitializer：ApplicationListener**；

​	作用：

​（1）runSchemaScripts();运行建表语句；

（2）runDataScripts();运行插入数据的sql语句；

默认只需要将文件命名为：

```properties
schema-*.sql、data-*.sql
默认规则：schema.sql，schema-all.sql；
可以使用   
	schema:
      - classpath:department.sql
      指定位置
```

5、操作数据库：自动配置了JdbcTemplate操作数据库

## 二、整合Druid数据源
### 1、导入Druid依赖
```xml
 <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>druid</artifactId>
            <version>1.1.8</version>
        </dependency>
```

```java
@Configuration
public class DruidConfig {

    @ConfigurationProperties(prefix = "spring.datasource")
    @Bean
    public DataSource druid(){
       return  new DruidDataSource();
    }

    //配置Druid的监控
    //1、配置一个管理后台的Servlet
    @Bean
    public ServletRegistrationBean statViewServlet(){
        ServletRegistrationBean bean = new ServletRegistrationBean(new StatViewServlet(), "/druid/*");
        Map<String,String> initParams = new HashMap<>();

        initParams.put("loginUsername","admin");
        initParams.put("loginPassword","123456");
        initParams.put("allow","");//默认就是允许所有访问
        initParams.put("deny","192.168.15.21");

        bean.setInitParameters(initParams);
        return bean;
    }


    //2、配置一个web监控的filter
    @Bean
    public FilterRegistrationBean webStatFilter(){
        FilterRegistrationBean bean = new FilterRegistrationBean();
        bean.setFilter(new WebStatFilter());

        Map<String,String> initParams = new HashMap<>();
        initParams.put("exclusions","*.js,*.css,/druid/*");

        bean.setInitParameters(initParams);

        bean.setUrlPatterns(Arrays.asList("/*"));

        return  bean;
    }
}

```
## 三、整合Mybatis
依赖关系图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020090423515037.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### （一）、Mybatis 增删改查
#### 1、创建mapper接口

```java
@Mapper
public interface DepartmentMapper {

    @Select("select * from department")
    public List<Department> selectAll();

    @Select("select * from department where id=#{id}")
    public Department selectById(Integer id);

    @Options(useGeneratedKeys = true, keyProperty = "id")
    @Insert("insert into department(departmentName) values(#{departmentName})")
    public int save(Department department);

    @Update("update department set departmentName=#{departmentName}")
    public int update(Department department);

    @Delete("delete from department where id =#{id}")
    public int delete(Integer id);
}

```

#### 2、创建Controller

```java
@RestController
public class DepartmentController {

    @Autowired
    private DepartmentMapper departmentMapper;

    @RequestMapping("/dep/{id}")
    public List<Department> getDepById(@PathVariable Integer id) {
        return departmentMapper.selectAll();
    }

    @RequestMapping("/dep")
    public Department getDepById(Department department) {
        departmentMapper.save(department);
        return department;
    }
}
```


访问：http://localhost:8080/dep?departmentName=PeppaPig 添加一条数据

访问：http://localhost:8080/dep/1获取数据

### （二）、Mybatis配置
##### 1、开启驼峰命名法
我们的实体类和表中的列名一致，把department表的departmentName列名改为department_name看看现象

访问：http://localhost:8080/dep/1获取数据

```bash
[{"id":1,"departmentName":null}]
Copy to clipboardErrorCopied
```

由于列表和属性名不一致，所以就没有封装进去，我们表中的列名和实体类属性名都是遵循驼峰命名规则的，可以开启mybatis的开启驼峰命名配置

在`application.yml`中进行学习

```bash
mybatis:
  configuration:
    map-underscore-to-camel-case: true
```

然后重启项目，重新插入数据，再查询就发现可以封装进去了

也可以通过向spring容器中注入org.mybatis.spring.boot.autoconfigure.ConfigurationCustomizer的方法设置mybatis参数

```java
@Configuration
public class MybatisConfig {

    @Bean
    public ConfigurationCustomizer mybatisConfigurationCustomizer() {
        return new ConfigurationCustomizer() {
            @Override
            public void customize(org.apache.ibatis.session.Configuration configuration) {
                configuration.setMapUnderscoreToCamelCase(true);
            }
        };
    }
}
```

##### 2、Mapper扫描
使用@mapper注解的类可以被扫描到容器中，但是每个Mapper都要加上这个注解就是一个繁琐的工作，能不能直接扫描某个包下的所有Mapper接口-->在springboot启动类上加上@MapperScan

```java
@MapperScan("cn.clboy.springbootmybatis.mapper")
@SpringBootApplication
public class SpringbootMybatisApplication {

    public static void main(String[] args) {
        SpringApplication.run(SpringbootMybatisApplication.class, args);
    }

}
```

**使用xml配置文件**
创建mybatis全局配置文件

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN" "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <typeAliases>
        <package name="cn.clboy.springbootmybatis.model"/>
    </typeAliases>
</configuration>
```
##### 3、业务代码编写
创建EmployeeMapper接口

```java
public interface EmployeeMapper {

    List<Employee> selectAll();

    int save(Employee employee);
}
```

创建EmployeeMapper.xml映射文件

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="cn.clboy.springbootmybatis.mapper.EmployeeMapper">
    <select id="selectAll" resultType="employee">
        SELECT * FROM employee
    </select>
    <insert id="save" parameterType="employee" useGeneratedKeys="true" keyProperty="id">
       INSERT INTO employee(lastName,email,gender,d_id) VALUES (#{lastName},#{email},#{gender},#{d_id})
    </insert>
</mapper>
```

配置文件(application.yaml)中指定配置文件和映射文件的位置

```bash
mybatis:
  config-location: classpath:mybatis/mybatis-config.xml
  mapper-locations: classpath:mybatis/mapper/*.xml
```


**创建EmployeeController**

```java
@RestController
public class EmployeeController {

    @Autowired
    private EmployeeMapper employeeMapper;

    @RequestMapping("/emp/list")
    public List<Employee> getALl() {
        return employeeMapper.selectAll();
    }

    @RequestMapping("/emp/{id}")
    public Employee save(Employee employee) {
        employeeMapper.save(employee);
        return employee;
    }
}
```

Copy to clipboardErrorCopiedJPA
访问：http://localhost:8080/emp/list

## 四、整合SpringData与JPA
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200905154620316.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 简介
Spring Data项目的目的是为了简化构建基于 Spring框架应用的数据访技术，包括非关系数据库、
Map- Reduce框架、云数据服务等等；另外也包含对关系数据厍的访问支持

JPA    ---->    Java持久化规范

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200905155123527.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200905155155546.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
依赖关系图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200905170440950.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
JPA:ORM（Object Relational Mapping）

层级关系图如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200905172147427.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 1、实体类

编写一个实体类（bean）和数据表进行映射，并且配置好映射关系；

```java
//使用JPA注解配置映射关系
@Entity //告诉JPA这是一个实体类（和数据表映射的类）
@Table(name = "tbl_user") //@Table来指定和哪个数据表对应;如果省略默认表名就是user；
public class User {

    @Id //这是一个主键
    @GeneratedValue(strategy = GenerationType.IDENTITY)//自增主键
    private Integer id;

    @Column(name = "last_name",length = 50) //这是和数据表对应的一个列
    private String lastName;
    @Column //省略默认列名就是属性名
    private String email;
```
### 2、Dao接口
编写一个Dao接口来操作实体类对应的数据表（Repository）

```java
//继承JpaRepository来完成对数据库的操作
public interface UserRepository extends JpaRepository<User,Integer> {
}

```
### 3、配置
基本的配置JpaProperties

```yaml
spring:  
 jpa:
    hibernate:
#     更新或者创建数据表结构
      ddl-auto: update
#    控制台显示SQL
    show-sql: true
```

### 4、Controller类



```java
@RestController
public class UserController {

    @Autowired
    UserRepository userRepository;

    @GetMapping("/user/{id}")
    public Optional<User> getUser(@PathVariable("id") Integer id){
        Optional<User> user = userRepository.findById(id);
        return user ;
    }

    @GetMapping("/user")
    public User insertUser(User user){
        User save = userRepository.save(user);
        return save;
    }

}
```

http://localhost:8080/user?lastName=zhangsan&email=123456@qq.com

http://localhost:8080/user?lastName=lisi&email=78215646@qq.com

查询用户访问：

http://localhost:8080/user/1，然后会发现抛出500错误，原因是getOne方法使用的懒加载，获取到的只是代理对象，转换为json时会报错

**解决方法：**

1、法一：关闭懒加载，在实体类上加@Proxy(lazy = false)注解

```java
@Entity
@Table(name = "tbl_user")
@Proxy(lazy = false)
public class User
```

2、法二：转json的时候忽略hibernateLazyInitializer和handler属性

```java
@Entity
@Table(name = "tbl_user")
@JsonIgnoreProperties(value = {"hibernateLazyInitializer", "handler"})
public class User 
```

# 常见异常及其原因
## ①JDBC 连接数据库出错
java.sql.SQLException: Access denied for user ''@'117.42.26.254' (using pass
1、没有权限、信息错误（密码，主机名等）
2、yml文件格式错误（下为正解）

```bash
spring:
  datasource:
    username: root
    password: 1********
    url: jdbc:mysql://1*******08/jdbc
    driver-class-name: com.mysql.jdbc.Driver
```

## ②引入SQL 文件报错
java.lang.IllegalStateException: Failed to load ApplicationContext

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200904154126972.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
解决：1、在resource 文件夹下新建 文件夹sql
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200904154436964.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
2、或者是yml 文件格式（内容）错误

3、数据库是否打开
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200905001048575.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
4、[参考链接](https://blog.csdn.net/qq_42815122/article/details/85395111)




