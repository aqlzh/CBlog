**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# Vue-cli
`vue-cli`官方提供脚手架，用于快速生成一个vue的项目模板，预先定义好的目录结构及基础代码。类比创建 Maven项目时可以选择创建一个骨架项目（脚手架）

[官方网址](https://cli.vuejs.org/zh/)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210210152250410.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 主要的功能
（1）统一的目录结构
（2）本地调试
（3）热部署
（4）单元测试
（5）集成打包上线

## 安装环境
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908212935928.png#pic_center)
### 优化
安装 Node. js淘宝镜像加速器（cnpm）
全局安装

```bash
npm install cnpm
```

或使用如下语句解决npm速度慢的问题

```bash
npm  install  --registry=https//registry.npm.taobao.org
```
安装成功示意
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908213211178.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 安装vue-cli
安装vue-ci   (3.x)

```bash
npm install -g @vue/cli   
```
测试是否安装成功

```bash
vue  -V
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908213809201.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908220413798.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

查看可以基于哪些模板创建vue应用程序，通常我们选择 webpack
刚开始安装的需要重启才有如下命令
```bash
vue list
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908220446259.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 创建项目
### 使用命令创建Vue项目
  命令：`vue create my-project`
 1、 选择Manually select features(选择特性以创建项目)
  2、勾选特性可以用空格进行勾选。
  3、是否选用历史模式的路由：n
  4、ESLint选择：ESLint + Standard config
  5、何时进行ESLint语法校验：Lint on save
  6、babel，postcss等配置文件如何放置：In dedicated config files(单独使用文件进行配置)
 7、是否保存为模板：n
  8、使用哪个工具安装包：npm
 ### 基于ui界面创建Vue项目
 命令：`vue ui`
  在自动打开的创建项目网页中配置项目信息。
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210210153530555.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

 ### 基于2.x的旧模板，创建Vue项目
 

```bash
 npm install -g @vue/cli-init
 vue init webpack my-project
```

## 开始编写
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908223234997.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```bash
cd myvue
```
初始化所依赖的环境

```bash
cnpm install
```
启动运行

```bash
npm run dev
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/202009082240199.png#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908224121174.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
使用IDEA 打开
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908224436269.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## vue 脚手架配置
通过单独的配置文件进行配置，在根目录创建`vue.config.js`

```javascript
        module.exports = {
            devServer:{
                port:8888,
                open:true
            }
        }
```

# Webpack
**介绍**： webpack是一个现代 Javascript应用程序的静态模块打包器（ module bundler）,当webpack处理应用程序时，会递归地构建一个依赖关系 dependency graph），其中包含应用程序需要的毎个模块，然后将所有这些模块打包成一个或多个 bundle。可以将许多**松散耦合**的模块按照依赖和规则打包成符合生产环境部署的前端资源。还可以将按需加载的模块进行代码分离，等到实际需要时再异步加载。通过 loader转换，任何形式的资源都可以当做模块，比如 CommonsJS、AMD、ES6、CSS、JSON、CoffeeScript、LESS等。
 WebApp通常是一个SPA（单页面应用），每一个视图通过异步的方式加载，这导致页面初始化和使用过程中会加载越来越多的JS代码，这给前端的开发流程和资源组织带来了巨大挑战。

## CommonsJS
服务器端的 NodeJS遵循 CommonsJS规范，该规范核心思想是允许模块通过 require方法来同步加载所需依赖的其它模块，然后通过 exports或 module .exports来导出需要暴露的接口

```bash
require（"module) ;
require（"./module. js"）;
export.doStuff function() {} ;
module.exports = someValue ;
```
###  优缺点
优点：
(1)服务器端模块便于重
(2)NPM中已经有超过45万个可以使用的模块包
(3)简单易用
缺点
(1)同步的模块加载方式不适合在浏览器环境中，同步意味着阻塞加载，浏览器资源是异步加载的
(2)不能非阻塞的并行加载多个模块

## AMD
`Asynchronous Module Definition`规范,其实主要一个主要接口 define（id？
dependencies？， factory）；它要在声明模块的时候指定所有的依赖 dependencies，并且还要当做形参传到 factory中，对于依赖的模块提前执行。

```bash
define （" module ,["dep1","dep2"]，function（d1,d2）{
return someExportedValue ;
}) ;
require（["module" ,"../file.js"]，function（module,file）{} );
```
### 优缺点
优点
(1)适合在浏览器环境中异步加载模块
(2)可以并行加载多个模块
缺点
(2)提高了开发成本，代码的阅读和书写比较困难，模块定义方式的语义不畅
(2)不符合诵用的模块化思维方式，是一种妥协的实现

## CMD
Commons module definition规范和AMD很相似，尽量保持简单，并与 CommonJS和
NodeJS的 Modules 规范保持了很大的兼容性。

```bash
define（ function （require，exports，module）{
var $ = require（"jquery") ;
var Spinning = require（"./spinning"）
exports.doSomething =... ;
module.exports  = ... ;
}) ;
```

### 优缺点
优点：
(1)依赖就近，延迟执行
(2)可以很容易在 NodeJS中运行
缺点
(1)依赖SPM打包，模块的加载逻辑偏重

## ES6
EcmaScript6标准增加了 Javascript语言层面的模块体系定义。ES6模块的设计思想，是尽量静态化，使编译时就能确定模块的依赖关系，以输入和输出的变量。 CommonsJS和AMD模块，都只能在运行时确定这些东西。

```bash
import "jquery" ;
export function doStuff() {}
module "localModule" {}
```

### 优缺点
优点
(1)容易进行静态分析
(2)面向未来的 EcmaScript标准
缺点
(1)原生浏览器端还没有实现该标准,需要转化为ES5

# 安装Webpack
Webpack是一款模块加载器兼打包工具，它能把各种资源，如JS、JSX、ES6、SASS、LESS、图片等都作为模块来处理和使用
**安装**

```bash
npm install webpack -g
npm install webpack-cli -g
```

**测试安装成功**

```bash
webpack -v
webpack-cli -v
```
## 配置
创建 `webpack.config.js`配置文件

entry：入口文件，指定 WebPack用哪个文件作为项目的入口
output：输出，指定 WebPack把处理完成的文件放置到指定路径
module：模块，用于处理各种类型的文件
plugins：插件，如：热更新、代码重用等
resolve：设置路径指向
watch：监听，用于设置文件改动后直接打包
## 使用
打包`webpack.config.js` 代码

```javascript
module.exports ={
    entry: './module/main.js',
    output:{
        filename:"./js/bundle.js"
    }
};
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200909150857799.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
暴露，导出 `hello.js`

```javascript
// 暴露出一个方法
exports.sayHi = function(){
    document.write("<h1>ES6_Study</h1>")
} ;

```

导入 `main.js`代码

```javascript
var hello = require("./hello") ;
hello.sayHi() ;
```
实际效果
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020090915261727.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

