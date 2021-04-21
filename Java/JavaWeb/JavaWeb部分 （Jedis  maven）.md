**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# Jedis
Jedis: 一款java操作redis数据库的工具.Java客户端
 **使用步骤**：
	1. 下载jedis的jar包
	2. 使用方法

 获取连接

```bash
 Jedis jedis = new Jedis("localhost",6379);
```
操作

```bash
jedis.set("username","zhangsan");
```
关闭连接

```bash
jedis.close();
```

## 回顾数据结构，数据类型
==数据结构==

1. List：可存储相同的值（确切讲是a.equals(b)时，二者都可存储）

2. Set：不可存储相同值

3. Map：存储key-value形式的数据。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804161700246.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

==数据类型==
1、四种整数类型(byte、short、int、long)

2、两种浮点数类型(float、double)

3、一种字符类型(char)

4、一种布尔类型(boolean)


## 操作各种redis中的数据结构
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804154557983.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 一、 字符串类型 string
1. 获取连接
```java
Jedis jedis = new Jedis();//如果使用空参构造，默认值 "localhost",6379端口
```
2. 操作存储  set

```java
jedis.set("username","zhangsan");
```
3.获取   get

```java
String username = jedis.get("username");
System.out.println(username);
```
	
特殊：使用setex()方法存储可以指定过期时间的 key value

```java
jedis.setex("activecode",20,"hehe");
```

将activecode：hehe键值对存入redis，并且20秒后自动删除该键值对

4.关闭连接

```java
jedis.close();
```
### 二、哈希类型 hash ： map格式  
1. 获取连接

```java
Jedis jedis = new Jedis();//如果使用空参构造，默认值 "localhost",6379端口
```
2. 操作存储hash

```java
jedis.hset("user","name","lisi");
jedis.hset("user","age","23");
jedis.hset("user","gender","female");
```
	
3.获取hash

```java
String name = jedis.hget("user", "name");
System.out.println(name);
```


 ==获取hash的所有map中的数据==

```java
Map<String, String> user = jedis.hgetAll("user");
// keyset
Set<String> keySet = user.keySet();
for (String key : keySet) {
	   //获取value
String value = user.get(key);
System.out.println(key + ":" + value);
	        }
```

	
3. 关闭连接

```java
jedis.close();
```
### 三、列表类型 list
linkedlist格式。支持重复元素

```java
lpush / rpush
lpop / rpop
lrange start end : 范围获取
```
			
操作，list 存储

```java
jedis.lpush("mylist","a","b","c");//从左边存
jedis.rpush("mylist","a","b","c");//从右边存
	
```
list 范围获取

```java
List<String> mylist = jedis.lrange("mylist", 0, -1);
System.out.println(mylist);
```
list 弹出

```java
String element1 = jedis.lpop("mylist");//c
System.out.println(element1);
```
	
### 四、集合类型 set  ： 不允许重复元素
sadd
smembers:获取所有元素

set 集合存储

```java
jedis.sadd("myset","java","php","c++");
```
set集合 获取

```java
Set<String> myset = jedis.smembers("myset");
System.out.println(myset);
```
	

### 五、有序集合类型 sortedset
不允许重复元素，且元素有顺序
			zadd
			zrange


操作 sortedset 存储

```java
jedis.zadd("mysortedset",3,"亚瑟");
jedis.zadd("mysortedset",30,"后裔");
jedis.zadd("mysortedset",55,"孙悟空");
```
sortedset 获取

```java
Set<String> mysortedset = jedis.zrange("mysortedset", 0, -1);
System.out.println(mysortedset);
```

## Jedis连接池
JedisPool使用：
1.创建一个配置对象
```java
JedisPoolConfig config = new JedisPoolConfig();
config.setMaxTotal(50);
config.setMaxIdle(10);
```
		
2. 创建JedisPool连接池对象

```java
JedisPool jedisPool = new JedisPool(config,"localhost",6379);
```

3. 调用方法 getResource()方法获取Jedis

```java
  //2.获取连接
Jedis jedis = jedisPool.getResource();
 //3. 使用
jedis.set("hehe","heihei");
```



### 连接池工具类

```java

public class JedisPoolUtils {

private static JedisPool jedisPool;
	 static{
			    //读取配置文件，类加载器
	 InputStream is = JedisPoolUtils.class.getClassLoader().getResourceAsStream("jedis.properties");
//创建Properties对象
 Properties pro = new Properties();
	  //关联文件
	try {
	   pro.load(is);
	    } catch (IOException e) {
	        e.printStackTrace();
			        }
	 //获取数据，设置到JedisPoolConfig中
JedisPoolConfig config = new JedisPoolConfig();
			        config.setMaxTotal(Integer.parseInt(pro.getProperty("maxTotal")));
			        config.setMaxIdle(Integer.parseInt(pro.getProperty("maxIdle")));
			
//初始化JedisPool
jedisPool = new JedisPool(config,pro.getProperty("host"),Integer.parseInt(pro.getProperty("port")));

}

 public static Jedis getJedis(){
			        return jedisPool.getResource();
			    }
			}
```

**使用连接池工具类**

```java
public void test(){
// 通过数据池工具类获取
Jedis jedis + JedisPoolUtils.getJedis() ;

// 使用
jedis.set("key","value") ;

// 关闭，归还至数据池
jedis.close() ;
}
```
		     
**回顾将list序列化为json**
		
```java
ObjectMapper mapper list = service.findAll() ;
String json = mapper.writeValueAsString(list) ;
```
# Maven
## 解压目录
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804220520812.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

		      

配置环境变量（此电脑右键属性）

配置完成如图
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080422121994.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 中央仓库
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804221759955.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804221726405.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 标准目录结构
src/main/java目录  核心代码部分
src/main/resources  配置文件部分   
src/test/java目录    测试代码部分
src/test/resources   测试配置文件
src/main/webapp   页面资源，js，css,img

**项目介绍**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804225428263.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804225135288.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804225141278.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## Maven 常用命令
==**clean**==
clean是 maven工程的清理命令，执行 clean会删除 target目录及内容
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080423120290.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


==**compile**==

compile是 maven工程的编译命令，作用是将src/main/java下的文件编译为class文件输出到 target目录下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804231238147.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

==**test**==
test是 maven工程的测试命令 mvn test，会执行 src/test/java下的单元测试类
cmd执行 mvn test执行src/test/java下单元测试类，下图为测试结果，运行1个测试用例，全部成功

==**package**==
package是 maven工程的打包命令，对于java工程执行 package打成jar包，对于web工程打成war包

==**install**==
instal是 maven工程的安装命令，执行install将 maven打成jar包或war包发布到本地仓库。从运行结果中，可以看出当后面的命令执行时，前面的操作过程也都会自动执行


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804231718677.png)
## 生命周期
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804233431540.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## Maven概念图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804233326245.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## Idea配置
注意：首页 -> setting -> 搜索Maven -> Runner ->  VM Options 设置为`-DarchetypeCatalog=internal`

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804234907381.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
开始Maven

### 使用骨架创建maven的java工程
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200804235410946.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
解决开始项目导入仓库缓慢问题
问题原因:Maven服务器在国外
解法：使用阿里镜像，在`Setting.xml`文件中编辑
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805001909549.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

一段时间后 -> 配置完成图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805134309576.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
有些目录需要手动配置  eg: resource   （add as library  -> 作为根目录（可以在其中台添加文件））

### 使用骨架创建maven的web工程
![-](https://img-blog.csdnimg.cn/20200805135223638.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/202008051409036.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 坐标
在`pom.xml` 中配置项目运行所依赖的jar包
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805141503352.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
==注意==：作用域的填写，否则报错
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080514193491.png)


```css
<scope>provided</scope>
<scope>test</scope>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805143616363.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 定制模板
为tomcat7 ，jdk  插件定制模板
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200805143331709.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想

