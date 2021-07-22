> 编程路漫之远兮，集数据库之大体； 
> 劝君专注案前事，亦是杯酒敬苍生；


@[toc]
# DCL  管理用户 授权（了解）
==SQL分类==：
	1. DDL：操作数据库和表
	2. DML：增删改表中数据
	3. DQL：查询表中数据
	4. DCL：管理用户，授权
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200728131215240.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)



 DBA：数据库管理员

##  管理用户
### 添加用户：
语法：`CREATE USER '用户名'@'主机名' IDENTIFIED BY '密码';`
### 删除用户：
语法：`DROP USER '用户名'@'主机名';`
### 修改用户密码：

```sql
UPDATE USER SET PASSWORD = PASSWORD('新密码') WHERE USER = '用户名';
UPDATE USER SET PASSWORD = PASSWORD('abc') WHERE USER = 'lisi';
```

或者

```sql
SET PASSWORD FOR '用户名'@'主机名' = PASSWORD('新密码');
SET PASSWORD FOR 'root'@'localhost' = PASSWORD('123');
```
==mysql中忘记了root用户的密码？==
1. cmd -- > net stop mysql 停止mysql服务
需要管理员运行该cmd

2. 使用无验证方式启动mysql服务： mysqld --skip-grant-tables
3. 打开新的cmd窗口,直接输入mysql命令，敲回车。就可以登录成功
4. use mysql;
5. update user set password = password('你的新密码') where user = 'root';
6. 关闭两个窗口
7. 打开任务管理器，手动结束mysqld.exe 的进程
8. 启动mysql服务
9. 使用新密码登录。
### 查询用户：

```sql
-- 1. 切换到mysql数据库
USE myql;
-- 2. 查询user表
SELECT * FROM USER;
```
			
== 通配符==： % 表示可以在任意主机使用用户登录数据库

#### 权限管理：
1. 查询权限：

```sql
-- 查询权限
SHOW GRANTS FOR '用户名'@'主机名';
SHOW GRANTS FOR 'lisi'@'%';
```

2. 授予权限：

```sql
-- 授予权限
grant 权限列表 on 数据库名.表名 to '用户名'@'主机名';
-- 给张三用户授予所有权限，在任意数据库任意表上
GRANT ALL ON *.* TO 'zhangsan'@'localhost';
```

3. 撤销权限：

```sql
-- 撤销权限：
revoke 权限列表 on 数据库名.表名 from '用户名'@'主机名';
REVOKE UPDATE ON db3.`account` FROM 'lisi'@'%';
```

# JDBC
**概念**：Java DataBase Connectivity  Java 数据库连接， Java语言操作数据库
**JDBC本质**：其实是官方（sun公司）定义的一套操作所有关系型数据库的规则，即==接口==。各个数据库厂商去实现这套接口，提供数据库驱动jar包。我们可以使用这套接口（JDBC）编程，真正执行的代码是驱动jar包中的实现类。
## 起始步骤：
1. 导入驱动jar包 mysql-connector-java-5.1.37-bin.jar
		 复制mysql-connector-java-5.1.37-bin.jar到项目的libs目录下
		 右键-->Add As Library
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200728221734839.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200728223410708.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

2. 注册驱动
3. 获取数据库连接对象 Connection
4. 定义sql
5. 获取执行sql语句的对象 Statement
6. 执行sql，接受返回结果
7. 处理结果
8. 释放资源
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072822442271.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
其中输出的1为影响行数
## JDBC各个对象：
### DriverManager：驱动管理对象
功能：
			1. ==注册驱动==：告诉程序该使用哪一个数据库驱动jar
`static void registerDriver(Driver driver)` :注册与给定的驱动程序 DriverManager 。 
写代码使用：  `Class.forName("com.mysql.jdbc.Driver");`
				通过查看源码发现：在com.mysql.jdbc.Driver类中存在静态代码块
```sql
static {
try {
     java.sql.DriverManager.registerDriver(new Driver());
				        } catch (SQLException E) {
 throw new RuntimeException("Can't register driver!");
				        }
					}
```

> 注意：mysql5之后的驱动jar包可以省略注册驱动的步骤。

2.==获取数据库连接==
方法：`static Connection getConnection(String url, String user, String password)` 
**参数**：
**url**：指定连接的路径
语法：jdbc:mysql://ip地址(域名):端口号/数据库名称
jdbc:mysql://localhost:3306/db

> 注意：如果连接的是本机mysql服务器，并且mysql服务默认端口是3306，则url可以简写为：jdbc:mysql:///数据库名称

**user**：用户名
**password**：密码 
### Connection：数据库连接对象
功能：
1. 获取执行sql 的对象

```sql
Statement createStatement()
PreparedStatement prepareStatement(String sql)  
```

2. 管理事务：
开启事务：`setAutoCommit(boolean autoCommit)` ：调用该方法设置参数为false，即开启事务
提交事务：`commit()` 
回滚事务：`rollback()` 
### Statement：执行sql的对象
1. ==执行sql==
 `boolean execute(String sql)` ：可以执行任意的sql 了解 
 `int executeUpdate(String sql)` ：执行DML（insert、update、delete）语句、DDL(create，alter、drop)语句
2. 返回值：影响的行数，可以通过这个影响的行数判断DML语句是否执行成功 返回值>0的则执行成功，反之，则失败。
3. `ResultSet executeQuery(String sql)`  ：执行DQL（select)语句，返回的的是执行结果对象（表）

### ResultSet：结果集对象,封装查询结果
 `boolean next():` 游标向下移动一行，判断当前行是否是最后一行末尾(是否有数据)，如果是，则返回false，如果不是则返回true，注意游标默认是在第一行（表头）然后下一行是数据。
`getXxx`(参数):获取数据
Xxx：代表数据类型   如： int getInt() ,	String getString()
==参数==：
				1. int：代表列的编号,从1开始   如： getString(1)
				2. String：代表列名称。 如： getDouble("balance")
		
注意：
				1. 游标向下移动一行
				2. 判断是否有数据
				3. 获取数据

```sql
 //循环判断游标是否是最后一行末尾。
	            while(rs.next()){
	                //获取数据
	                //6.2 获取数据
	                int id = rs.getInt(1);
	                String name = rs.getString("name");
	                double balance = rs.getDouble(3);
	
	                System.out.println(id + "---" + name + "---" + balance);
	            }
```

### PreparedStatement：执行sql的对象

1. SQL注入问题：在拼接sql时，有一些sql的特殊关键字参与字符串的拼接（如逻辑短路，恒等式问题）。会造成安全性问题
2. 解决sql注入问题：使用PreparedStatement对象来解决
3.  预编译的SQL：参数使用?作为占位符
4. 步骤：
			1. 导入驱动jar包 mysql-connector-java-5.1.37-bin.jar
			2. 注册驱动
			3. 获取数据库连接对象 Connection
			4. 定义sql

> 注意：sql的参数使用？作为占位符。 如：select * from user where username = ? and password = ?;

5. 获取执行sql语句的对象 PreparedStatement  `Connection.prepareStatement(String sql)` 
6. 给？赋值：
==方法==： setXxx(参数1,参数2)
参数1：？的位置编号 从1 开始
参数2：？的值
7. 执行sql，接受返回结果，不需要传递sql语句
8. 处理结果
9. 释放资源

> 注意：后期都会使用PreparedStatement来完成增删改查的所有操作
> 			1. 可以防止SQL注入
> 			2. 效率更高


## 抽取JDBC工具类 JDBCUtils
目的：简化书写，抽取共用方法
分析：
	1. 注册驱动也抽取
	2. 抽取一个方法获取连接对象
		==需求==：不想传递参数（麻烦），还得保证工具类的通用性。
		解决：配置文件
			jdbc.properties
				url=
				user=
				password=
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072913381630.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
# 事务
1.**概念**： 如果一个包含多个步骤的业务操作，被事务管理，那么这些操作要么同时成功，要么同时失败。
2. ==操作==：
开启事务： `start transaction;`
回滚：`rollback`;
提交：`commit`;
例子：

```sql
CREATE TABLE account (
       id INT PRIMARY KEY AUTO_INCREMENT,
       NAME VARCHAR(10),
       balance DOUBLE
		);
-- 添加数据
INSERT INTO account (NAME, balance) VALUES ('zhangsan', 1000), ('lisi', 1000);
		SELECT * FROM account;
		UPDATE account SET balance = 1000;
-- 张三给李四转账 500 元
		
		-- 0. 开启事务
		START TRANSACTION;
		-- 1. 张三账户 -500
		
UPDATE account SET balance = balance - 500 WHERE NAME = 'zhangsan';
		-- 2. 李四账户 +500
		-- 出错了...
UPDATE account SET balance = balance + 500 WHERE NAME = 'lisi';
		
		-- 发现执行没有问题，提交事务
		COMMIT;
		
		-- 发现出问题了，回滚事务
		ROLLBACK;
```

==MySQL数据库中事务默认自动提交==
		
## 事务提交的两种方式
1. 自动提交：
mysql就是自动提交的
一条DML(增删改)语句会自动提交一次事务。
2. 手动提交：
 Oracle 数据库默认是手动提交事务
需要先开启事务，再提交
**修改事务的默认提交方式**：
查看事务的默认提交方式：`SELECT @@autocommit; -- 1 代表自动提交  0 代表手动提交`
修改默认提交方式： `set @@autocommit = 0;`


## 事务的四大特征：
	1. 原子性：是不可分割的最小操作单位，要么同时成功，要么同时失败。
	2. 持久性：当事务提交或回滚后，数据库会持久化的保存数据。
	3. 隔离性：多个事务之间。相互独立。
	4. 一致性：事务操作前后，数据总量不变
## 事务的隔离级别（了解）
**概念**：多个事务之间隔离的，相互独立的。但是如果多个事务操作同一批数据，则会引发一些问题，设置不同的隔离级别就可以解决这些问题。
==存在问题==：
		1. **脏读**：一个事务，读取到另一个事务中没有提交的数据
		2. **不可重复读(虚读)**：在同一个事务中，两次读取到的数据不一样。
		3. **幻读**：一个事务操作(DML)数据表中所有记录，另一个事务添加了一条数据，则第一个事务查询不到自己的修改。
==隔离级别==：
		1. `read uncommitted`：读未提交
产生的问题：脏读、不可重复读、幻读
		2. `read committed`：读已提交 （Oracle默认）
产生的问题：不可重复读、幻读
		3. `repeatable read`：可重复读 （MySQL默认）
产生的问题：幻读
		4. `serializable`：串行化(类似于多线程中锁的操作)
可以解决所有的问题

>  注意：隔离级别从小到大安全性越来越高，但是效率越来越低

==数据库查询隔离级别：==

```sql
select @@tx_isolation;
```
==数据库设置隔离级别：==


```sql
set global transaction isolation level  级别字符串;
```

## JDBC 控制事务
1. **事务**：一个包含多个步骤的业务操作。如果这个业务操作被事务管理，则这多个步骤要么同时成功，要么同时失败。
2. 操作：
	1. 开启事务
	2. 提交事务
	3. 回滚事务
3. 使用==Connection==对象来管理事务
	* 开启事务：`setAutoCommit(boolean autoCommit)` ：调用该方法设置参数为false，即开启事务
		* 在执行sql之前开启事务
	* 提交事务：commit() 
		* 当所有sql都执行完提交事务
	* 回滚事务：rollback() 
		* 在catch中回滚事务
	

图示如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200729145517292.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
# 数据库连接池
1. **概念**：其实就是一个容器(集合)，存放数据库连接的容器。
	    当系统初始化好后，容器被创建，容器中会申请一些连接对象，当用户来访问数据库时，从容器中获取连接对象，用户访问完之后，会将连接对象归还给容器。==好处==：1. 节约资源 2. 用户访问高效

3. **实现**：
	1. 标准接口：DataSource   javax.sql包下的
	方法：
			1）获取连接：getConnection()
		    2）归还连接：Connection.close()。如果连接对象Connection是从连接池中获取的，那么调用Connection.close()方法，则不会再关闭连接了。而是归还连接

	2. 一般不实现它，由数据库厂商来实现
		1. C3P0：数据库连接池技术
		2. Druid：数据库连接池实现技术，由阿里巴巴提供的

## C3P0：数据库连接池技术
使用步骤：
		1. 导入jar包 (两个) c3p0-0.9.5.2.jar mchange-commons-java-0.2.12.jar ，
		2. 2. 定义配置文件：
		名称： c3p0.properties 或者 c3p0-config.xml
		路径：直接将文件放在src目录下即可。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200729171426971.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

3. 创建核心对象 数据库连接池对象 ComboPooledDataSource
4. 获取连接： getConnection

## Druid：数据库连接池技术（常用）
###  使用步骤：
1. 导入jar包 druid-1.0.9.jar
2. 定义配置文件：
			是properties形式的
			可以叫任意名称，可以放在任意目录下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200729205234348.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

3. 加载配置文件。Properties
4. 获取数据库连接池对象：通过工厂来来获取  DruidDataSourceFactory
5. 获取连接：getConnection

### 定义工具类 JDBCUtils
1. 定义一个类 JDBCUtils
2. 提供静态代码块加载配置文件，初始化连接池对象
3. 提供方法
			1. 获取连接方法：通过数据库连接池获取连接
			2. 释放资源
			3. 获取连接池的方法

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200729210305677.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# Spring JDBC(重要)
Spring框架对JDBC的简单封装。提供了一个JDBCTemplate对象==简化==JDBC的开发
## JDBCTemplate
==步骤==：
	1. 导入jar包
	2. 创建JdbcTemplate对象。依赖于数据源DataSource
```sql
JdbcTemplate template = new JdbcTemplate(ds);
```
3. 调用JdbcTemplate的方法来完成CRUD的操作
		 `update():`执行DML语句。增、删、改语句
		`queryForMap()`:查询结果将结果集封装为map集合，将列名作为key，将值作为value 将这条记录封装为一个map集合

> 注意：这个方法查询的结果集长度只能是1

`queryForList():`查询结果将结果集封装为list集合

> 注意：将每一条记录封装为一个Map集合，再将Map集合装载到List集合中

`query():`查询结果，将结果封装为JavaBean对象
query的参数：RowMapper
一般我们使用`BeanPropertyRowMappe`r实现类。可以完成数据到JavaBean的自动封装

```sql
 new BeanPropertyRowMapper<类型>(类型.class)
```

`queryForObject`：查询结果，将结果封装为对象
一般用于聚合函数的查询

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200729211835248.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

