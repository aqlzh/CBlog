

> 编程路漫之远兮，集数据库之大体 ；
> 劝君专注案前事，亦是杯酒敬苍生 ；
> 
@[toc]
#  数据库基本概念
数据库： DataBase 简称 ： DB，用于存储和管理数据的仓库。
**特点：**
	1. 持久化存储数据的。其实数据库就是一个文件系统
	2. 方便存储和管理数据
	3. 使用了统一的方式操作数据库 -- SQL

# MySQL使用
## MySQL服务启动
1. 手动。
2. `cmd--> services.msc` 打开服务的窗口
3. 使用管理员打开cmd
			`net start mysql` : 启动mysql的服务
			`net stop mysql`:关闭mysql服务
## MySQL登录退出
1. mysql -uroot -p密码
2. mysql -hip -uroot -p连接目标的密码
3. mysql --host=ip --user=root --password=连接目标的密码
	* MySQL退出
		1. exit
		2. quit
## MySQL目录结构
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200726004123803.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


1. MySQL安装目录：basedir="D:/develop/MySQL/"
		 配置文件 my.ini
2. MySQL数据目录：datadir="C:/ProgramData/MySQL/MySQL Server 5.5/Data/"
**相关概念**
				数据库：文件夹
				表：文件
				数据：文件内数据
				
==对应关系如下图示==
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200726004448948.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## SQL
**SQL** ： Structured Query Language：结构化查询语言，其实就是定义了操作所有关系型数据库的规则。每一种数据库操作的方式存在不一样的地方，称为“方言”。
	
### SQL通用语法
1. SQL 语句可以单行或多行书写，以分号结尾。
2. 可使用空格和缩进来增强语句的可读性。
3. MySQL 数据库的 SQL 语句不区分大小写，关键字建议使用大写。
4. ==3 种注释==
		单行注释: -- 注释内容 或 # 注释内容(mysql 特有) 
		多行注释: /* 注释 */
	
### SQL分类
1) DDL(Data Definition Language)数据定义语言
		用来定义数据库对象：数据库，表，列等。关键字：create, drop,alter 等
2) DML(Data Manipulation Language)数据操作语言
		用来对数据库中表的数据进行增删改。关键字：insert, delete, update 等
3) DQL(Data Query Language)数据查询语言
		用来查询数据库中表的记录(数据)。关键字：select, where 等
4) DCL(Data Control Language)数据控制语言(了解)
		用来定义数据库的访问权限和安全级别，及创建用户。关键字：GRANT， REVOKE 等

图解如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072600571149.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### DDL:操作数据库、表

#### 操作数据库：CRUD
1. ==C(Create):创建==
创建数据库：

```sql
create database 数据库名称;
```
创建数据库，判断不存在，再创建：


```sql
create database if not exists 数据库名称;
```
创建数据库，并指定字符集

```sql
create database 数据库名称 character set 字符集名;
```


3. ==R(Retrieve)：查询==
查询所有数据库的名称:

```sql
show databases;
```
查询某个数据库的字符集:查询某个数据库的创建语句

```sql
show create database 数据库名称;
```

4. ==U(Update):修改==
修改数据库的字符集

```sql
alter database 数据库名称 character set 字符集名称;
```

5. ==D(Delete):删除==
删除数据库

```sql
drop database 数据库名称;
```
判断数据库存在，存在再删除

```sql
drop database if exists 数据库名称;
```

6. ==使用数据库==
查询当前正在使用的数据库名称

```sql
select database();
```
使用数据库

```sql
use 数据库名称;
```
#### 操作表
一、 ==C(Create):创建==
		1. 语法：
```sql
create table 表名(
列名1 数据类型1,
列名2 数据类型2,
		....
列名n 数据类型n
			);
```
 **注意**：最后一列，不需要加逗号（,）
##### 数据库类型：
| int        | 整数类型                       | age int,                                                     |
| ---------- | ------------------------------ | ------------------------------------------------------------ |
| double:    | 小数类型                       | score double(5,2)                                            |
| date       | 日期，只包含年月日             | yyyy-MM-dd                                                   |
| datetime   | 日期，包含年月日时分秒         | yyyy-MM-dd HH:mm:ss                                          |
| timestamp: | 时间戳类型	包含年月日时分秒 | yyyy-MM-dd HH:mm:ss                                          |
| varchar    | 字符串                         | name varchar(20):姓名最大20个字符<br/>zhangsan 8个字符  张三 2个字符 |


创建表

		create table student(
			id int,
			name varchar(32),
			age int ,
			score double(4,1),
			birthday date,
			insert_time timestamp
		);

**复制表**：

```sql
create table 表名 like 被复制的表名;	
```

二、==R(Retrieve)：查询==
查询某个数据库中所有的表名称

```sql
show tables;
```
查询表结构

```sql
desc 表名;
```
三、 ==U(Update):修改==
		1. 修改表名
```sql
alter table 表名 rename to 新的表名;
```
2. 修改表的字符集

```sql
alter table 表名 character set 字符集名称;
```
3. 添加一列

```sql
alter table 表名 add 列名 数据类型;
```
4. 修改列名称 类型
			

```sql
alter table 表名 change 列名 新列别 新数据类型;
alter table 表名 modify 列名 新数据类型;
```

5. 删除列

```sql
alter table 表名 drop 列名;
```

四、 ==D(Delete):删除==

```sql
drop table 表名;
drop table  if exists 表名 ;
```

### DML：增删改表中数据

1. ==添加数据：==
		语法：
```sql
insert into 表名(列名1,列名2,...列名n) values(值1,值2,...值n);
```
注意：
			1. 列名和值要一一对应。
			2. 如果表名后，不定义列名，则默认给所有列添加值
```sql
insert into 表名 values(值1,值2,...值n);
```
除了数字类型，其他类型需要使用引号(单双都可以)引起来
	2. ==删除数据：==
语法：

```sql
delete from 表名 [where 条件]
```
注意：
			1. 如果不加条件，则删除表中所有记录。
			2. 如果要删除所有记录
				1. delete from 表名; -- 不推荐使用。有多少条记录就会执行多少次删除操作
				2. TRUNCATE TABLE 表名; -- 推荐使用，效率更高 先删除表，然后再创建一张一样的空表。
	3. ==修改数据：==
语法：

```sql
update 表名 set 列名1 = 值1, 列名2 = 值2,... [where 条件];
```
	
注意：
			1. 如果不加任何条件，则会将表中所有记录全部修改。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200726203754744.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
记录：好像不支持中文，而且在图形化界面不支持查看，建议在命令行中用

```sql
select * from student ;
```

更新数据实况：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200726205410255.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### DQL：查询表中的记录

```sql
select * from 表名;
```

#### 语法：
	

```sql
select
		字段列表
	from
		表名列表
	where
		条件列表
	group by
		分组字段
	having
		分组之后的条件
	order by
		排序
	limit
		分页限定
```
#### 基础查询
1. 多个字段的查询
		

```sql
select 字段名1，字段名2... from 表名；
```
注意：
如果查询所有字段，则可以使用*来替代字段列表。
	2. 去除重复：（distinct）
```sql
select distinct address from student ;
```	 
3. 计算列
		一般可以使用四则运算计算一些列的值。（一般只会进行数值型的计算）
		if null(表达式1,表达式2)：null参与的运算，计算结果都为null
		表达式1：哪个字段需要判断是否为null
		如果该字段为null后的替换值。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200726210756675.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

	5. 起别名：
 as：as也可以省略
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200726210901286.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
#### 条件查询
1. **where子句后跟条件**
2. **运算符**
		==> 、< 、<= 、>= 、= 、<>==
		BETWEEN...AND  
		IN( 集合) 
		**LIKE**：模糊查询（注意也是复制关键字）
3. **占位符：**
				 _:单个任意字符
				%：多个任意字符
		IS NULL  
		and  或 &&
		or  或 || 
		not  或 !
		
	

```sql
-- 查询年龄大于20岁

SELECT * FROM student WHERE age > 20;
			
SELECT * FROM student WHERE age >= 20;
			
-- 查询年龄等于20岁
SELECT * FROM student WHERE age = 20;
			
-- 查询年龄不等于20岁
SELECT * FROM student WHERE age != 20;
SELECT * FROM student WHERE age <> 20;
- 查询年龄大于等于20 小于等于30
			
SELECT * FROM student WHERE age >= 20 &&  age <=30;
SELECT * FROM student WHERE age >= 20 AND  age <=30;
SELECT * FROM student WHERE age BETWEEN 20 AND 30;
			
-- 查询年龄22岁，18岁，25岁的信息
SELECT * FROM student WHERE age = 22 OR age = 18 OR age = 25
SELECT * FROM student WHERE age IN (22,18,25);
			
-- 查询英语成绩为null
SELECT * FROM student WHERE english = NULL; -- 不对的。null值不能使用 = （!=） 判断
			
SELECT * FROM student WHERE english IS NULL;
			
-- 查询英语成绩不为null
SELECT * FROM student WHERE english  IS NOT NULL;

-- 查询姓马的有哪些？ like
SELECT * FROM student WHERE NAME LIKE '马%';
-- 查询姓名第二个字是化的人
			
SELECT * FROM student WHERE NAME LIKE "_化%";
			
-- 查询姓名是3个字的人
SELECT * FROM student WHERE NAME LIKE '___';
-- 查询姓名中包含德的人
SELECT * FROM student WHERE NAME LIKE '%德%';
```

### DQL:查询语句
#### 排序查询
语法：order by 子句

```sql
order by 排序字段1 排序方式1 ，  排序字段2 排序方式2...
select * from student order by math desc ;
```
 排序方式：
		ASC：升序，默认的。
	  DESC：降序。


		注意：如果有多个排序条件，则当前边的条件值一样时，才会判断第二条件。

#### 聚合函数：
将一列数据作为一个整体，进行纵向的计算。
	1. ==count==：计算个数
一般选择非空的列：主键
		2. ==count(*)==
	3. ==max==：计算最大值
	4. ==min==：计算最小值
	5. ==sum==：计算和
	6. ==avg==：计算平均值

```sql
select count(id) from student ;
select count(ifnull(english,0)) from student ;
```

>  注意：聚合函数的计算，排除null值。 		解决方案：
> 			1. 选择不包含非空的列进行计算
> 			2. IFNULL函数

#### 分组查询:
1. 语法：

```sql
group by 分组字段；
```
2. 注意：
		1. 分组之后查询的字段：分组字段、聚合函数
		2. where 和 having 的区别？
			1. where 在分组之前进行限定，如果不满足条件，则不参与分组。having在分组之后进行限定，如果不满足结果，则不会被查询出来
			2. where 后不可以跟聚合函数，==having可以进行聚合函数的判断==。

```sql
-- 按照性别分组。分别查询男、女同学的平均分

SELECT sex , AVG(math) FROM student GROUP BY sex;
	
-- 按照性别分组。分别查询男、女同学的平均分,人数
	
SELECT sex , AVG(math),COUNT(id) FROM student GROUP BY sex;
	
--  按照性别分组。分别查询男、女同学的平均分,人数 要求：分数低于70分的人，不参与分组
SELECT sex , AVG(math),COUNT(id) FROM student WHERE math > 70 GROUP BY sex;
	
--  按照性别分组。分别查询男、女同学的平均分,人数 要求：分数低于70分的人，不参与分组,分组之后。人数要大于2个人
SELECT sex , AVG(math),COUNT(id) FROM student WHERE math > 70 GROUP BY sex HAVING COUNT(id) > 2;
	
SELECT sex , AVG(math),COUNT(id) 人数 FROM student WHERE math > 70 GROUP BY sex HAVING 人数 > 2;
```

#### 分页查询
1. 语法：limit 开始的索引,每页查询的条数;
2. 公式：开始的索引 = （当前的页码 - 1） * 每页显示的条数
-- 每页显示3条记录 

```sql
SELECT * FROM student LIMIT 0,3; -- 第1页
		
SELECT * FROM student LIMIT 3,3; -- 第2页
		
SELECT * FROM student LIMIT 6,3; -- 第3页
```

3. limit 是一个MySQL的一种"方言"，相比于Oracle等其他数据库
