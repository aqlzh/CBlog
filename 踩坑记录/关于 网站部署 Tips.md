@[toc]
# Jar  包
打包方式 ：`mvn package -Dmaven.test.skip=true`

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210325190443539.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


输出目录 ：`target`  

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210325190610723.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


运行 jar  包   `java  -jar  filename.jar`

# 网站管理
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210325183926731.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# 端口占用
- 查看端口占用： `lsof -i:端口号`


- 清除占用该端口的所有进程：  `sudo kill -9 $(lsof -i:端口号 -t)`


# 二级域名创建
1、首先找的 阿里云 域名解析
2、选择添加记录
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210328143709613.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
3、打开宝塔面板  新建站点
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210328144546379.png)


4、在站点下部署项目文件即可
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210328144631125.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

