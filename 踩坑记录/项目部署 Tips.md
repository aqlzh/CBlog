@[toc]
# Maven 打包
1、清除缓存  `mvn package clean -Dmaven.test.skip=true`
2、生成 jar 包   `mvn package -Dmaven.test.skip=true`

# 上传Jar
- 将 生成的 jar 包 放于 Linux 服务器上 
- 并且运行 `java -jar FileName.jar` 

#  上传数据库
- 在宝塔内数据库 上传 注意与生成的 jar 包 `name` `password` 相对应

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210427000634664.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
- 通过 Navicat   连接
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210427001131319.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


# 打开端口
- ==注意== 在宝塔以及阿里云**安全组**打开对应的端口

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210427001849445.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
- ==注意加入安全组的位置 下面多的==，

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210427003707428.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
 - ==一定要打开正确的安全组==

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210427003834913.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


# 杀进程
- 比如 杀死 8086 进程
- 1、首先查询进程 PID   `lsof -i:8086` 
- 2、然后 `kill -9` 查询的进程号

# 注意
- 还有一点需要注意  项目跑不起来 端口占用 ，代码问题
- 然后是数据库问题存在，项目也可能会跑起来

- 数据库名称与宝塔相对应
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210428002153706.png)

注意格式

# 运行
- 注意将后台挂起，否则关掉 Xshell 会自动关闭进程
 - ==重要==  后台挂起命令  `nohup java -jar question-brushing-system-0.0.1-SNAPSHOT.jar >/dev/null 2>&1 &` 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210427164035362.png)


