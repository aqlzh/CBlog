**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# Vue 引入
**Soc** (Separation of concerns):  关注点分离原则  

HTML + CSS  + JS     视图：呈现给用户，刷新后台数据
[参考链接](https://www.cnblogs.com/wenhongyu/p/7992028.html)


网络通信： axios
页面跳转： vue-router
状态管理： vuex
Vue-UI : ICE


[跳转链接](https://ice.work/)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906164220595.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## CSS预处理
==拓展==
基本思想用一种专门的编程语言，为CSS增加编程的特性，将CSS作为目标生成文件，然后开发者就只要使用这种语言进行CSS的编码工作。用一种专门的编程语言，进行Web页面样式设计，再通过编译器转化为正常的CSS文件，以供项目使用。

**常用的CSS预处理器**：
1、**SASS**：基于Ruby，通过服务端处理，功能强大。解析效率高,需要Ruby语言基础

2、**LESS**：基于 Nodes，通过客户端处理，使用简单。功能比SASS简单，解析效率也低于SASS，但在实际开发中足够。


> 后端导包工具：Maven 
> 前端导包工具：Webpack

## JavaScript框架
1、`JQuery`: JavaScript框架，简化了DOM操作，缺点是DOM操作太频繁影晌前端性能；对于前端使用它仅仅是为了兼容IE6、7、8

2、`Angular`： Google收购的前端框架，由Java程序员开发，其特点是将后台的MVC模式迁至前端并增加了模块化开发的理念，与微软合作，采用 TypeScript语法开发；对后台程序员友好，对前端程序员不太友好；最大的缺点是版本迭代不合理（如：1代->2代，除了名字，就是两个东西）

3、`React`： Facebook出品，一款髙性能的JS前端框架；特点是提岀了新概念【虛拟DOM】用于减少真实DOM操作，在内存中模拟DOM操作，有效的提升了前端渲染效率；缺点是使用复杂，因为需要额外学习JSX语言

4、`Vue`：渐进式 Java Script框架，所谓渐进式就是逐步实现新特性的意思，如实现模块化开发、路由、状态管理等新特性。其特点是综合了 Angular（模块化）和 React（虚拟DOM）

5、`Axios`：前端通信框架；因为vue的边界很明确，就是为了处理DOM，所以并不具备通信能力，此时就需要额外使用一个通信框架与服务器交互；当然也可以直接选择使用 jQuery提供的AJAX通信功能


## 混合开发
主要目的是实现一套代码三端统一（PC、 Android：apk、ios：ipa）并能够调用到设备底层硬件（如：传感器、GPS、摄像头等），打包方式主要有以下两种
云打包： HBuild-> HBuildx， CLoud出品； API Cloud
本地打包： Cordova（前身是 PhoneGap）

### 后端
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906194753747.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 前端为主的MV* 时代
MVC（同步通信为主）： Model、View、 Controller
MVP（异步通信为主）： Model、View、 Presenter
MVVM（异步通信为主）： Model、View、 ViewModel


### 前后端分离
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906195119269.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
# Vue启航
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906195656780.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## MVVM模式的实现者
1、`Model`：模型层，在这里表示 JavaScript对象
2、`View`：视图层，在这里表示DOM（HTML操作的元素）
3、`View Model`：连接视图和数据的中间件， Vue js就是MVVM中的 ViewModel层的实现者

在MVVM架构中，是不允许数据和视图直接通信的，只能通过 ViewModel来通信而ViewModel就是定义了一个 Observer观察者ViewModel能够观察到数据的变化，并对视图对应的内容进行更新ViewModel能够监听到视图的变化并能够通知数据发生改变.。 Vue. js就是一个MVVM的实现者，他的核心就是实现了DOM监听与数据绑定


## Vue CDN

```bash
<script src=https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.js"></script>
```

```bash
<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js></script>
```
## Vue 程序

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello Vue</title>
</head>
<body>
<!--view 层 模板-->
<div id="app">
    {{message}}
</div>

<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js"></script>
<script>
    var vm = new Vue({
        // Model 数据
        el:"#app",
        data:{
            message:"hello Vue"
        }
    }) ;
</script>
</body>
</html>
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020090620544963.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

**体现MVVM** 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906204653889.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906210643611.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

**前端渲染**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906210523581.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

## 基本语法
[官网参考链接](https://cn.vuejs.org/v2/guide/#%E5%A3%B0%E6%98%8E%E5%BC%8F%E6%B8%B2%E6%9F%93)
### 绑定事件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906210213358.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
所见 `v-bind attribute` 被称为指令。指令带有前缀 `v-`，以表示它们是 Vue 提供的特殊 attribute。它们会在渲染的 DOM 上应用特殊的响应式行为。在这里，该指令的意思是：“将这个元素节点的 title attribute 和 Vue 实例的 message property 保持一致”。



![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906220613463.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 判断循环
v-if
v-else-if

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906215330121.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 双向绑定
[参考链接](https://cn.vuejs.org/v2/guide/components-custom-events.html#%E8%87%AA%E5%AE%9A%E4%B9%89%E7%BB%84%E4%BB%B6%E7%9A%84-v-model)

```bash
v-model
```
可以用v- model指令在表单< input>、< textarea〉及< select>元素上创建双向数据绑定。它会根据控件类型自动选取正确的方法来更新元素。，但v-mode本质是语法糖。它负责监听用户的输入事件以更新数据，并对一些极端场景进行一些特殊处理

==注意==：v-model会忽略所有表单元素的 value、 checked、 selected特性的初始值而总是将vue实例的数据作为数据来源。应该通过 JavaScript在组件的data选项中声明初始值(如下为 null)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906222004393.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906222030376.png#pic_center)
### Vue 组件
[参考链接](https://cn.vuejs.org/v2/guide/components.html)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Document</title>
</head>
<body>
<div id="app">
    <button-counter></button-counter>
    <button-counter></button-counter>
    <button-counter></button-counter>
</div>
<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js"></script>
<script type="text/javascript">
    /*
      组件注册
    */
    Vue.component('button-counter', {
        data: function(){
            return {
                count: 0
            }
        },
        template: '<button @click="handle">点击了{{count}}次</button>',
        methods: {
            handle: function(){
                this.count += 2;
            }
        }
    });
    var vm = new Vue({
        el: '#app',
        data: {

        }
    });
</script>
</body>
</html>

```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200906234717911.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

