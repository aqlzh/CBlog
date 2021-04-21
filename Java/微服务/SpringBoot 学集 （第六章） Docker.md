**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# 引入
## 简介
**Docker**是一个开源的应用容器引擎；是一个轻量级容器技术；

Docker支持将软件编译成一个镜像；然后在镜像中各种软件做好配置，将镜像发布出去，其他使用者可以直接使用这个镜像（镜像称为容器，启动是非常快速）

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200902225532707.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 核心概念
docker主机(Host)：安装了Docker程序的机器（Docker直接安装在操作系统之上）；

docker客户端(Client)：连接docker主机进行操作；

docker仓库(Registry)：用来保存各种打包好的软件镜像；

docker镜像(Images)：软件打包好的镜像；放在docker仓库中；

docker容器(Container)：镜像启动后的实例称为一个容器；容器是独立运行的一个或一组应用

## 安装Docker
环境：Linux 系统

### 一、常规安装

1、检查内核版本，必须是3.10及以上

```bash
uname -r
```

2、安装docker

```bash
yum install docker
```
3、启动docker

```bash
systemctl start docker
```

4、停止docker

```bash
systemctl stop docker
```
### 二、宝塔面板安装
位于软件商店（如下图）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200902230236146.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
成功安装如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200902230206150.png#pic_center)
# Docker 常用命令
## 一、镜像操作

| 操作 | 命令                                            | 说明                                                     |
| ---- | ----------------------------------------------- | -------------------------------------------------------- |
| 检索 | docker  search 关键字  eg：docker  search redis | 我们经常去docker  hub上检索镜像的详细信息，如镜像的TAG。 |
| 拉取 | docker pull 镜像名:tag                          | :tag是可选的，tag表示标签，多为软件的版本，默认是latest  |
| 列表 | docker images                                   | 查看所有本地镜像                                         |
| 删除 | docker rmi image-id                             | 删除指定的本地镜像                                       |
### 修改镜像源
修改 /etc/docker/daemon.json ，写入如下内容（如果文件不存在新建该文件）

```bash
vim /etc/docker/daemon.json
```

内容：

```bash
{
"registry-mirrors":["http://hub-mirror.c.163.com"]
}
```

国内镜像源	地址
Docker 官方中国区	https://registry.docker-cn.com
阿里云	https://pee6w651.mirror.aliyuncs.com

---
[Docker官网网址](https://hub.docker.com/)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200903170040371.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200903170252918.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 1、检索：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200903000406783.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 2、拉取
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200903165624338.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 3、列表
见上图

## 二、容器操作
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200903170701748.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

1、搜索镜像

```bash
docker search tomcat
```

2、拉取镜像

```bash
docker pull tomcat
```

3、根据镜像启动容器

```bash
docker run --name mytomcat -d tomcat:latest
```
4、查看运行中的容器

```bash
docker ps  
```

5、 停止运行中的容器

```bash
docker stop  容器的id
```

6、查看所有的容器

```bash
docker ps -a
```

7、启动容器

```bash
docker start 容器id
```

8、删除一个容器

```bash
 docker rm 容器id
```

9、启动一个做了端口映射的tomcat

```bash
docker run -d -p 8888:8080 tomcat
```

`-d`：后台运行
`-p`: 将主机的端口映射到容器的一个端口    主机端口:容器内部的端口

10、linux的防火墙
`service firewalld status` 查看防火墙状态
`service firewalld stop` 关闭防火墙

11、查看容器的日志

```bash
docker logs container-name/container-id
```

[更多指令参考](https://docs.docker.com/engine/reference/commandline/docker/)

## 三、安装并使用Mysql
### 1、拉取镜像

```bash
docker pull mysql
```

### 2、启动

```shell
docker run --name mysql01 -e MYSQL_ROOT_PASSWORD=123456 -d mysql
```

```bash
docker ps

CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS               NAMES
b874c56bec49        mysql               "docker-entrypoint.sh"   4 seconds ago       Up 3 seconds        3306/tcp            mysql01
```


### 3、端口映射

```shell
docker run -p 3308:3306 --name mysql02 -e MYSQL_ROOT_PASSWORD=123456 -d mysql

docker ps
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS                    NAMES
ad10e4bc5c6a        mysql               "docker-entrypoint.sh"   4 seconds ago       Up 2 seconds        0.0.0.0:3306->3306/tcp   mysql02




docker run -p 3308:3306 --name mysql08 -e MYSQL_ROOT_PASSWORD=123456 -d mysql

```


# 常用Linux命令续
## 防火墙相关
1、查看所有开启的端口 `firewall-cmd --list-ports` （阿里云需要配置安全组规则）

2、查看firewall服务状态 `systemctl status firewalld` 
开启 `service firewalld start` 
重启 `service firewalld restart` 
关闭 `service firewalld stop` 

 3、查看防火墙规则 
 查看全部信息  `firewall-cmd --list-all` 
 只看端口信息   `firewall-cmd --list-ports` 

4、开启防火墙端口 `firewall-cmd --zone=public --add-port=9000/tcp --permanent` 

**命令含义**： 
`--zone` 作用域 
`--add-port=80/tcp`  添加端口，格式为：端口/通讯协议
`--permanent`  永久生效，没有此参数重启后失效

5、重启防火墙 `systemctl restart firewalld.service` 

## 安装相关
6、检测JDK 版本信息 `rpm -qa | grep jdk` 

7、卸载 jdk  `rpm -e --nodeps jdk`

8、安装 jdk `rpm -ivh rpm包`

# 常见异常
## ①docker search mysql 命令失效
```bash
Error response from daemon: Get https://index.docker.io/v1/search?q=mysql&n=25: net/http: TLS handshake timeout
```
[参考链接](https://blog.csdn.net/weixin_42119415/article/details/103268886)

## ②端口映射tomcat，访问报404
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200903212258138.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
linux 内置防火墙
阿里云安全组 是否开放端口

## ③Docker 连接数据库异常集
名称重用
```bash
docker: Error response from daemon: Conflict. The container name "/mysql04" is already in use by container "084b3101709d46ee70ab372f3ecf36a1db4fd8aff7c594c885e". You have to remove (or rename) that container to be able to reuse that name.
```
端口重用
```bash
docker: Error response from daemon: driver failed programming external connectivity on endpoint mysql04 (8653acd17133b5d948ac7a91c8eddd8a31a34ba88831b): Error starting userland proxy: listen tcp 0.0.0.0:3306: bind: address already in use.
```

```bash
docker: Error response from daemon: driver failed programming external connectivity on endpoint mysql03 (6b7379d2dba65865373362dba75b2c8d94e6c31a2b3ca0f898):  (iptables failed: iptables --wait -t nat -A DOCKER -p tcp -d 0/0 --dport 3306 -j DNAT --to-destination 172.17.0.4:3306 ! -i docker0: iptables: No chain/target/match by that name.
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200903231326175.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

