> 学会克制    责任感    言行合一     行在言前一步

@[toc]
## 第八章（JavaEE 过滤器）
### 过滤器的主要功能
1、登入检验
2、权限审核
3、数据验证
4、日志登记
5、数据压缩、解压缩
6、数据加密、解密

### 过滤器配置
#### 过滤器声明
`<filter>`  用于声明过滤器
`<description>` 用于描述过滤器的用途
`<display-name>` 用于Web 配置的图形工具的名字，进行过滤器的定位 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210623144307871.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


#### 过滤器映射规则
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210623144340967.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
（1）精确地址映射
（2）目录匹配映射
（3）扩展名匹配地址映射
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210623144242812.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


## 第九章（JavaEE 监听器编程）
### 监听器的主要功能
1、网址访问人数或次数计数器
2、网址登录用户人数和在线用户检测
3、日志记录
4、会话超时后的清理工作


- 监听器编程   （如何编写）

## 第十章（JSP）
### JSP 与Servlet  的区别与比较
#### 相同点
1、都是符合 JavaEE 规范的Web组件
2、都是运行在Web 容器内
3、都可以接受HTTP  请求，并产生HTTP  响应
4、共用相同的会话对象和ServletContext 环境对象

#### 不同点
1、编程方式不同 ： Servlet  是纯Java  类
2、JSP 固有 生成的HTML  ，而Servlet  需要在的流输出语句中写入HTML
3、Servlet  类直接运行，JSP  文件需要经过解析，编译生成class  文件 。 
### JSP  的工作流程
1、解析阶段
2、编译阶段
3、运行阶段

### JSP 有哪几种以及格式
JSP  指令语法以及类型

```bash
<% @ 指令名 属性名 = “值”   属性名=“值” %>

```
1、page  : page 指令用于定义JSP  页面级的其他元素属性
2、include  ： 用于嵌入另一个文本文件的内容到本页面
3、taglib : 标记库指令 用于引入第三方扩展标记库
### JSP 内置对象
1、请求对象 request
2、响应对象 response 
3、会话对象  session  
4、服务器环境对象  application
5、页面对象 page
6、页面环境对象   pageContext
7、输出对象  out
8、异常对象   exception
9、配置对象  config

## 第十一章（EL与JSTL）
- EL 表达式 基本语法以及应用
- JSTL  基础和应用

[参考链接](https://blog.csdn.net/QuantumYou/article/details/107737415)
### JSTL   核心标记
1、通用标记
2、逻辑判定标记
3、循环遍历标记
4、URL 地址标记

## 第十二章（JNDI 命名服务编程）
  
- 什么是命名服务。什么是目录服务    
- 如何绑定、如何查找建立子目录

[推荐链接](https://blog.csdn.net/qq_38977097/article/details/81193954?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-2.baidujs&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-2.baidujs)

**命名服务**：作为一种基础设施出现在众多的计算机系统，其意义在于提供根据名称关联对象和通过对象匹配相应的命名服务。命名服务允许你通过名称找到一个与之对应的对象。例如在Internet上的域名服务（domain namingservice，DNS）就是提供将域名映射到IP地址的命名服务，在打开网站时一般都是在浏览器中输入名字，通过DNS找到相应的IP地址，然后打开。

**目录服务**：是一种特殊类型的数据库，与SQLServer、Access、Oracle等关系数据库管理系统相反，构造目录服务的目的是为了处理基于行为的事务，并且使用一种关系信息模型。

目录服务将命名服务的概念进一步引申为提供具有层次结构的信息库，这一信息库除了包含一对一的关系外，还有信息的层次结构。对目录服务而言，这种层次结构通常用于优化搜索操作，并且也可以按实际情况进行分布或者跨网络复制。

目录服务是命名服务，命名服务不需要是目录服务。

## 第十三章（JDBC 数据库连接编程）
### JDBC  驱动类型
JDBC  驱动类型分为四种，分别称为Ⅰ型，Ⅱ型，Ⅲ型，Ⅳ型。

- 加载驱动获取API

P273
- DML、SQL  编程步骤
- 数据库连接池

[关于JDBC  编程](https://blog.csdn.net/QuantumYou/article/details/107629739)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210623171059265.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210623171018622.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


## 第十五章 （MVC）
- 什么是MVC  模式 
**Model**（模型）是应用程序中用于处理应用程序数据逻辑的部分。通常模型对象负责在数据库中存取数据。
**View**（视图）是应用程序中处理数据显示的部分。通常视图是依据模型数据创建的。
**Controller**（控制器）是应用程序中处理用户交互的部分。通常控制器负责从视图读取数据，控制用户输入，并向模型发送数据。

[参考链接](https://blog.csdn.net/ricky73999/article/details/56683920)
