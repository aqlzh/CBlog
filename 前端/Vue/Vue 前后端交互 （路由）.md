@[toc]

> 保持热爱，奔赴山海

# 路由
## 概念基知介绍
1、路由的本质就是一种==对应关系==，url地址和真实的资源之间就有一种对应的关系，就是**路由**。

2、路由分为**前端路由**与**后端路由**

3、Ajax前端渲染（前端渲染提高性能，但是不支持浏览器的前进后退操作）

4、`SPA`（ Single Page Application）单页面应用程序：整个网站只有一个页面，内容的变化通过Ajax局部更新实现、同时支持浏览器地址栏的前进和后退操作。

5、SPA实现原理之一：基于URL地址的hash（hash的变化会导致浏览器记录访问历史的变化、但是hash的变化不会触发新的URL请求，在实现SPA过程中，最核心的技术点就是前端路由。

## 前后端路由的区别
1).后端路由是由服务器端进行实现，并完成资源的分发。
2).前端路由是依靠hash值(锚链接)的变化进行实现 ，主要用于监听事件并分发执行事件处理函数。

# Vue Router
路由管理器

[跳转链接](https://router.vuejs.org/zh/)
![在这里插入图片描述](https://img-blog.csdnimg.cn/202102072233125.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 基本使用步骤
1.引入相关的库文件
2.添加路由链接
3.添加路由填充位
4.定义路由组件
5.==配置路由规则并创建路由实例==
6.把路由挂载到vue根实例中

> Tips:  VSCode自定义快捷键生成Vue实例模板——附模板代码

[跳转链接](https://blog.csdn.net/qq_32755875/article/details/105844443)



添加路由链接`:<router-link>`是路由中提供的标签，默认会被渲染为a标签，to属性默认被渲染为`href`属性，to属性的值会被渲染为#开头的hash地址
```javascript
<script src="lib/vue_2.5.22.js"></script>
<script src="lib/vue-router_3.0.2.js"></script>


<router-link to="/user">User</router-link>
<router-link to="/login">Login</router-link>
//添加路由填充位（路由占位符）
<router-view></router-view>
//定义路由组件
var User = { template:"<div>This is User</div>" }
var Login = { template:"<div>This is Login</div>" }
//配置路由规则并创建路由实例
var myRouter = new VueRouter({
    //routes是路由规则数组
    routes:[
        //每一个路由规则都是一个对象，对象中至少包含path和component两个属性
        //path表示  路由匹配的hash地址，component表示路由规则对应要展示的组件对象
        {path:"/user",component:User},
        {path:"/login",component:Login}
    ]
})
//将路由挂载到Vue实例中
new Vue({
    el:"#app",
    //通过router属性挂载路由对象(下为简写)
    router:myRouter
})
```
## 路由重定向
可以通过路由重定向为页面设置默认展示的组件

```javascript
var myRouter = new VueRouter({
    //routes是路由规则数组
    routes: [
        //path设置为/表示页面最初始的地址 / ,redirect表示要被重定向的新地址，设置为一个路由即可
        { path:"/",redirect:"/user"},     // 核心
        { path: "/user", component: User },
        { path: "/login", component: Login }
    ]
})
```
## 路由嵌套

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta http-equiv="X-UA-Compatible" content="ie=edge" />
    <title>Document</title>
    <!-- 导入 vue 文件 -->
    <script src="./lib/vue_2.5.22.js"></script>
    <script src="./lib/vue-router_3.0.2.js"></script>
  </head>
  <body>
    <!-- 被 vm 实例所控制的区域 -->
    <div id="app">
      <router-link to="/user">User</router-link>
      <router-link to="/register">Register</router-link>

      <!-- 路由占位符 -->
      <router-view></router-view>
    </div>

    <script>
      const User = {
        template: '<h1>User 组件</h1>'
      }

      const Register = {
        template: `<div>
          <h1>Register 组件</h1>
          <hr/>

          <!-- 子路由链接 -->
          <router-link to="/register/tab1">tab1</router-link>
          <router-link to="/register/tab2">tab2</router-link>

          <!-- 子路由的占位符 -->
          <router-view />
        <div>`
      }

      const Tab1 = {
        template: '<h3>tab1 子组件</h3>'
      }

      const Tab2 = {
        template: '<h3>tab2 子组件</h3>'
      }

      // 创建路由实例对象
      const router = new VueRouter({
        // 所有的路由规则
        routes: [
          { path: '/', redirect: '/user'},
          { path: '/user', component: User },
          // children 数组表示子路由规则
          { path: '/register', component: Register, children: [
            { path: '/register/tab1', component: Tab1 },
            { path: '/register/tab2', component: Tab2 }
          ] }
        ]
      })

      // 创建 vm 实例对象
      const vm = new Vue({
        // 指定控制的区域
        el: '#app',
        data: {},
        // 挂载路由实例对象
        // router: router
        router
      })
    </script>
  </body>
</html>

```
###  页面效果
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210208172349909.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 动态路由匹配
通过动态路由参数的模式进行路由匹配

```javascript

var myRouter = new VueRouter({
    //routes是路由规则数组
    routes: [
        //通过/:参数名  的形式传递参数 
        { path: "/user/:id", component: User },
    ]
})


var User = { 
template:"<div>用户：{{$route.params.id}}</div>"
}
```
## 路由组件传递参数
### 情况一
为解决使用`$route.params.id`来获取路径传参的数据不够灵活。
运用  `props`  数组传参
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210208193921433.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 情况二
静态数组对象，将`props`设置为对象，直接将对象的数据传递给
组件进行使用

```javascript
var User = { 
    props:["username","pwd"],
    template:"<div>用户：{{username}}---{{pwd}}</div>"
    }

var myRouter = new VueRouter({
    //routes是路由规则数组
    routes: [
        //通过/:参数名  的形式传递参数 
        //如果props设置为对象，则传递的是对象中的数据给组件
        { path: "/user/:id", component: User,props:{username:"jack",pwd:123} },
        
    ]
})
```
### 情况三
实现获取传递的参数值和传递的对象数据，那么`props`应该设置为
**函数形式**。

```javascript
var User = { 
    props:["username","pwd","id"],
    template:"<div>用户：{{id}} -> {{username}}---{{pwd}}</div>"
    }

var myRouter = new VueRouter({
    //routes是路由规则数组
    routes: [
        //通过/:参数名  的形式传递参数 
        //如果props设置为函数，则通过函数的第一个参数获取路由对象
        //并可以通过路由对象的params属性获取传递的参数
        //   箭头函数
        { path: "/user/:id", component: User,props:(route)=>{
            return {username:"jack",pwd:123,id:route.params.id}
            } 
        },
    ]
})
```
## 命名路由
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210208200228688.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 编程式导航
### 页面导航的两种方式
- 声明式导航：通过点击链接实现导航的方式，叫做声明式导航
例如：普通网页中的`<a></a>`链接或Vue中的`< router-link></ router-link>`
- 编程式导航：通过调用 JavaScript形式的API实现导航的方式，叫做编程式导航
例如：普通网页中的 `location.href`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210208203718707.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

`@click="goRegister"`为注册点击事件，后在 method  中体现

