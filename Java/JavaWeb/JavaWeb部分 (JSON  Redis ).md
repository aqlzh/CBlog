**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# JSON
**概念**： JavaScript Object Notation		JavaScript对象表示法
Java体现

```java
Person p = new Person();
p.setName("高海千歌");
p.setAge(18);
p.setGender("女");
```

JavaScript   ->  JSON   体现
(1)普通格式

```javascript
var p = {"name":"高海千歌","age":18,"gender":"女"};
```
(2) 嵌套格式  [ ]   ->   { }		
```javascript
var ps = [
              {"name": "张三", "age": 23, "gender": true},
		      {"name": "李四", "age": 24, "gender": true},
		      {"name": "王五", "age": 25, "gender": false}
		      
		      ];
```
(3) 嵌套格式  { }	  ->   [ ]

```javascript
var pss = {
     "persons" : [
          {"name": "张三", "age": 23, "gender": true},
		  {"name": "李四", "age": 24, "gender": true},
		  {"name": "王五", "age": 25, "gender": false}
]
}
```

==优点==
json现在多用于存储和交换文本信息的语法
行数据的传输
JSON 比 XML 更小、更快，更易解析。

## 语法：
 **基本规则**
数据在名称/值对中：json数据是由键值对构成的
键用引号(单双都行)引起来，也可以不使用引号

==值得取值类型：==

				1. 数字（整数或浮点数）
				2. 字符串（在双引号中）
				3. 逻辑值（true 或 false）
				4. 数组（在方括号中）	{"persons":[{},{}]}
				5. 对象（在花括号中） {"address":{"province"："陕西"....}}
				6. null
**格式**：
数据由逗号分隔：多个键值对由逗号分隔，花括号保存对象：使用{}定义json 格式
方括号保存数组：[]
## 获取数据:
1. json对象.键名
2. json对象["键名"]
3. 数组对象[索引]
4. 遍历

**分别遍历**：
嵌套格式  [ ]   ->   { }	
嵌套格式  { }	  ->   [ ]		

```javascript
// 遍历对象
var person = {"name": "张三", age: 23, 'gender': true};

var ps = [{"name": "张三", "age": 23, "gender": true},
            {"name": "李四", "age": 24, "gender": true},
            {"name": "王五", "age": 25, "gender": false}];




        //获取person对象中所有的键和值
        //for in 循环
        for(var key in person){
            //这样的方式获取不行。因为相当于  person."name"
            //alert(key + ":" + person.key);
          
          //正解   
            alert(key+":"+person[key]);
        }

       //获取ps中的所有值
        for (var i = 0; i < ps.length; i++) {
            var p = ps[i];
            for(var key in p){
                alert(key+":"+p[key]);
            }
        }

```


## JSON数据和Java对象的互转
JSON解析器：常见的解析器：Jsonlib，Gson，fastjson，jackson
	
### JSON转为Java对象
1. 导入jackson的相关jar包
2. 创建Jackson核心对象 ObjectMapper
3. 调用ObjectMapper的相关方法进行转换

```java
 readValue(json字符串数据,Class)
```
  初始化JSON字符串

```java
  String json = "{\"gender\":\"男\",\"name\":\"张三\",\"age\":23}";
```
创建ObjectMapper对象
 

```java
ObjectMapper mapper = new ObjectMapper();
```
  转换为Java对象 Person对象

```java
  Person person = mapper.readValue(json, Person.class);
 System.out.println(person);
```

### Java对象转换JSON
使用步骤：
1. 导入jackson的相关jar包
2. 创建Jackson核心对象 ObjectMapper

```java
ObjectMapper mapper = new ObjectMapper();
```

3. 调用ObjectMapper的相关方法进行转换
#### 转换方法：

```java
writeValue(参数1，obj):
```

参数1：
File：将obj对象转换为JSON字符串，并保存到指定的文件中
Writer：将obj对象转换为JSON字符串，并将json数据填充到字符输出流中
OutputStream：将obj对象转换为JSON字符串，并将json数据填充到字节输出流中

`writeValueAsString(obj):`将对象转为json字符串

```java
String json = mapper.writeValueAsString(p);
System.out.println(json);//{"name":"张三","age":23,"gender":"男"}
```
writeValue，将数据写到d://a.txt文件中
```java
mapper.writeValue(new File("d://a.txt"),p);
```
writeValue.将数据关联到Writer中
```java
mapper.writeValue(new FileWriter("d://b.txt"),p);
```

#### 注解：
1. @JsonIgnore：排除属性。
在原始类定义时标注，eg: Person.java
2. @JsonFormat：属性值得格式化
在原始类定义时标注   eg:  `@JsonFormat(pattern = "yyyy-MM-dd")`

3. 复杂java对象转换
4. List：数组
5. Map：对象格式一致


#  Redis 
**概念**： redis是一款高性能的NOSQL系列的非关系型数据库
Redis是用C语言开发的一个开源的高性能键值对（key-value）数据库

菜鸟教程

> https://www.runoob.com/redis/redis-tutorial.html

	
## redis的应用场景
1.缓存（数据查询、短连接、新闻内容、商品内容等等）
2.聊天室的在线好友列表
3.任务队列。（秒杀、抢购、12306等等）
4.应用排行榜
5.网站访问统计
6.数据过期处理（可以精确到毫秒
7.分布式集群架构中的session分离

## NOSQL拓展
		•	键值(Key-Value)存储数据库
				相关产品： Tokyo Cabinet/Tyrant、Redis、Voldemort、Berkeley DB
				典型应用： 内容缓存，主要用于处理大量数据的高访问负载。 
				数据模型： 一系列键值对
				优势： 快速查询
				劣势： 存储的数据缺少结构化
		•	列存储数据库
				相关产品：Cassandra, HBase, Riak
				典型应用：分布式的文件系统
				数据模型：以列簇式存储，将同一列数据存在一起
				优势：查找速度快，可扩展性强，更容易进行分布式扩展
				劣势：功能相对局限
		•	文档型数据库
				相关产品：CouchDB、MongoDB
				典型应用：Web应用（与Key-Value类似，Value是结构化的）
				数据模型： 一系列键值对
				优势：数据结构要求不严格
				劣势： 查询性能不高，而且缺乏统一的查询语法
		•	图形(Graph)数据库
				相关数据库：Neo4J、InfoGrid、Infinite Graph
				典型应用：社交网络
				数据模型：图结构
				优势：利用图结构相关算法。
				劣势：需要对整个图做计算才能得出结果，不容易做分布式的集群方案。


## 配置介绍
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200803234906290.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 数据结构
键值数据类型如下：
			1) 字符串类型 string
			2) 哈希类型 hash
			3) 列表类型 list
			4) 集合类型 set
			5) 有序集合类型 sortedset
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200803235503323.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
修正：关于有序无序问题
## 命令操作
**前序**
（1）点击`redis-server.exe`
（2）点击`redis-cli.exe`

注意——解决无法连接的情况
cmd  redis 所在文件夹，输入`redis-server.exe redis.windows.conf`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804003618942.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 一、字符串类型 string
1. 存储： set key value

```bash
 set username zhangsan
 OK
```
2. 获取： get key

```bash
 get username
"zhangsan"
```
3. 删除： del key

```bash
 del age
(integer) 1
```
### 二、哈希类型 hash
1. 存储： hset key field value

```bash
hset myhash username lisi
(integer) 1
hset myhash password 123
(integer) 1
```
2. 获取： 
hget key field: 获取指定的field对应的值

```bash
hget myhash username
"lisi"
```

hgetall key：获取所有的field和value

```bash
hgetall myhash
1) "username"
2) "lisi"
3) "password"
4) "123"
```
				
3. 删除： hdel key field

```bash
hdel myhash username
(integer) 1
```
	
### 三、 列表类型 list
可以添加一个元素到列表的头部（左边）或者尾部（右边）
1. 添加：
	（1） lpush key value: 将元素加入列表左表
	（2） rpush key value：将元素加入列表右边
				
```bash
 lpush myList a
(integer) 1
lpush myList b
(integer) 2
rpush myList c
(integer) 3
```
2. 获取：
lrange key start end ：范围获取

```bash
lrange myList 0 -1
1) "b"
2) "a"
3) "c"
```
存储原理
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080400082735.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

3. 删除：
lpop key： 删除列表最左边的元素，并将元素返回
rpop key： 删除列表最右边的元素，并将元素返回

### 四、 集合类型 set 
不允许重复元素
1. 存储：sadd key value

```bash
sadd myset a
(integer) 1
sadd myset a
(integer) 0
```

2. 获取：smembers key:获取set集合中所有元素

```bash
smembers myset
1) "a"
```

3. 删除：srem key value:删除set集合中的某个元素	

```bash
srem myset a
(integer) 1
```
### 五、有序集合类型 sortedset
不允许重复元素，且元素有顺序.每个元素都会关联一个double类型的分数。redis正是通过分数来为集合中的成员进行从小到大的排序。

1. 存储：zadd key score value

```bash
 zadd mysort 60 zhangsan
(integer) 1
zadd mysort 50 lisi
(integer) 1
zadd mysort 80 wangwu
(integer) 1
```

2. 获取：zrange key start end [withscores]

```bash
zrange mysort 0 -1
1) "lisi"
2) "zhangsan"
3) "wangwu"
```
以排名的形式

```bash
 zrange mysort 0 -1 withscores
1) "zhangsan"
2) "60"
3) "wangwu"
4) "80"
5) "lisi"
6) "500"
```

3. 删除：zrem key value

```bash
zrem mysort lisi
(integer) 1
```

## 通用命令
1. keys * : 查询所有的键
2. type key ： 获取键对应的value的类型
3. del key：删除指定的key value


## 持久化
redis是一个内存数据库，当redis服务器重启，获取电脑重启，数据会丢失，我们可以将redis内存中的数据持久化保存到硬盘的文件中。

**redis持久化机制：**
### 一、 RDB：
默认方式，不需要进行配置，默认就使用这种机制，在一定的间隔时间中，检测key的变化情况，然后持久化数据
编辑redis.windwos.conf文件

save 900 1
```bash
after 900 sec (15 min) if at least 1 key changed
```
save 300 10	

```bash
after 300 sec (5 min) if at least 10 keys changed
```
save 60 10000	

```bash
after 60 sec if at least 10000 keys changed
```
				
				
2. 重新启动redis服务器，并指定配置文件名称，`redis-2.8.9>redis-server.exe redis.windows.conf`	

			
### 二、AOF：
日志记录的方式，可以记录每一条命令的操作。可以每一次命令操作后，持久化数据
1. 编辑`redis.windwos.conf`文件
				appendonly no（关闭aof） --> appendonly yes （开启aof）
				
				# appendfsync always ： 每一次操作都进行持久化
				appendfsync everysec ： 每隔一秒进行一次持久化
				# appendfsync no	 ： 不进行持久化


> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

