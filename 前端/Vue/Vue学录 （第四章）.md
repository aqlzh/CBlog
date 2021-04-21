**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# Vue router
Vue router是Vue.js官方的路由管理器。它和Vue.js的核心深度集成,使构建单页面应用简化。
## 功能：
（1）嵌套的路由/视图表
（2）模块化的、基于组件的路由配置
（3）路由参数、查询、通配符
（4）基于Vues过渡系统的视图过渡效果
（5）细粒度的导航控制
（6）带有自动激活的 CSS class的链接
（7）HTML5历史模式或hash模式，在IE9中自动降级
（8）自定义的滚动条行为

## 安装

```bash
cnpm install vue-router --save-dev
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200909154258820.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
导入并声明使用 vue-router

```bash
import VueRouter from 'vue-router'
Vue.use(VueRouter) ;
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200909162638236.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 使用
此命令前必须有安装
```bash
cnpm run  dev
```
### 1、编写router下index.js
安装路由，在src目录下，新建文件夹：router ，专门存放路由

```javascript
import Vue from  'vue'
import VueRouter from 'vue-router'

import Content from '../components/Content'
import Main from '../components/Main'

//安装路由
Vue.use(VueRouter) ;

// 配置导出路由
export default  new VueRouter({
  routes :[
    {
      // 路由路径  类似于 RequestMapping
      path : '/content' ,
      name : 'content' ,
      // 跳转组件

      component: Content
    },
    {
      // 路由路径
      path : '/main' ,
      name : 'main' ,
      // 跳转组件
      component: Main
    }
  ]
})

```
### 2、编写main.js

```javascript
// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import App from './App'
import router from './router'  // 自动扫描里面的路由配置



Vue.config.productionTip = false ;

/* eslint-disable no-new */
new Vue({
  el: '#app',
  // 配置路由
  router ,
  components: { App },
  template: '<App/>'
}) ;

```
### 3、编写app.vue，并使用路由

```javascript
<template>
  <div id="app">
<!--    <img src="./assets/logo.png">-->
<!--    <HelloWorld/>-->
    <h1>LZH_Create</h1>
    <router-link to="/main">首页</router-link>
    <router-link to="/content">内容页</router-link>

  </div>
</template>

<script>
import HelloWorld from './components/HelloWorld'
import VueRouter from 'vue-router'

// Vue.use(VueRouter) ;
// export default {
//   name: 'App',
//   components: {
//     HelloWorld
//   }
// }
export default{
  name :  'App'
} ;
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>

```

 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200909222700705.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020090922255530.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 4、添加新组建
步骤：
（1）在components文件夹下新建
（2）在`index.js`中导入导出
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200909224130950.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
（3）在`App.vue` 中编写注册渲染
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200909224015471.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
新组件`lzh.vue` 注册成功如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200909224302738.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
# 创建工程
注意：命令行都要使用管理员模式运行
1、进入代码目录创建一个名为 hello-vue的工程 `vue init webpack hello-vue`
2、安装依赖，安装Vue- router、 element-ui、sass- loader和node-saaa四个插件

```bash
#进入工程目录
cd hello-vue
#安装vue- router
npm install vue-router --save-dev
#安装e1ement-ui
npm i element-ui -S
#安装依赖
npm install
#安装SASS加载器
cnpm install sass-loader node-sass --save-dev
# 启动测试
npm run dev
```
## npm 解释
(1)`npm install moduleName`：安装模块到项目目录下
(2)`npm install -g moduleName`：-g的意思是将模块安装到全局，具体安装到磁盘哪个位置
要看 npm config prefix的位置
(3)`npm install- save moduleName`：--save的意思是将模块安装到项目目录下，并在
package文件的 dependencies节点写入依赖，-S为该命令的缩写
(4)`npm install -save- dey modulename`：--save-dev的意思是将模块安装到项目目录下，并
在 package文件的 devDependencies节点写入依赖，-D为该命令的缩写

## Element UI 使用
[官方参考](https://element.eleme.cn/#/zh-CN/component/quickstart)
## 路由嵌套
嵌套路由又称子路由，在实际应用中，通常由多层嵌套的组件组合而成。同样地，∪RL中各段动态路径也按某种结构对应嵌套的各层组件，例如
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910163538372.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910164835717.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```javascript
import Vue from 'vue'
import Router from  'vue-router'

import Main from '../views/Main'
import Login from '../views/Login'


import UserList from '../views/user/list'
import UserProfile from '../views/user/Profile'
Vue.use(Router) ;

export default new Router ({

  routes :[
    {
      path:'/main' ,
      component : Main,
      children:[
        {path: '/user/profile',component:UserProfile},
        {path: '/user/list',component:UserList},
      ]
    },{
      path:'/login' ,
      component : Login
    }

  ]

})

```
# 传递参数与重定向
###  传递参数
`index.js` 页面
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910171840105.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```javascript
import Vue from 'vue'
import Router from  'vue-router'

import Main from '../views/Main'
import Login from '../views/Login'


import UserList from '../views/user/list'
import UserProfile from '../views/user/Profile'
Vue.use(Router) ;

export default new Router ({

  routes :[
    {
      path:'/main' ,
      component : Main,
      children:[
        {path: '/user/profile/:id',name:'UserProfile',component:UserProfile},
        {path: '/user/list',component:UserList},
      ]
    },{
      path:'/login' ,
      component : Login
    }

  ]

})

```

展示页面`Login.vue`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910171712328.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### 重定向
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910172209836.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```javascript
import Vue from 'vue'
import Router from  'vue-router'

import Main from '../views/Main'
import Login from '../views/Login'


import UserList from '../views/user/list'
import UserProfile from '../views/user/Profile'
Vue.use(Router) ;

export default new Router ({

  routes :[
    {
      path:'/main' ,
      component : Main,
      children:[
        {path: '/user/profile/:id',name:'UserProfile',component:UserProfile},
        {path: '/user/list',component:UserList},
      ]
    },{
      path:'/login' ,
      component : Login
    },{
    path:'/goHome',
    redirect :'/main'
    }

  ]

})

```
# 路由模式与404
路由模式有两种
hash：路径带#符号，如`http//localhost/#/login`
history：路径不带#符号，如`http://localhost/login`

在`index.js`修改路由配置，代码如下

```bash
export default new Router ({
mode : 'history',
routes：[
]
}) ；
```
## 处理404

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910174037214.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


## 路由钩子与异步请求

[往期链接参考](https://blog.csdn.net/QuantumYou/article/details/108445348)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910174153330.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
beforeRouteEnter在进入路由前执行
beforeRouteLeave：在离开路由前执行

### 参数说明
to：路由将要跳转的路径信息
from：路径跳转前的路径信息
next：路由的控制参数
next（）跳入下一个页面
next（'/path）改变路由的跳转方向，使其跳到另一个路由
next（ false）返回原来的页面
next（vm）=>{}）仅在 beforeRouteEnter中可用，vm是组件实例

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910185523660.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```javascript
    export default {
      props:['id'],
      name: "UserProfile",
      beforeRouteEnter:(to,from,next)=>{
        console.log("进入路由之前");
        next() ;
      },
      beforeRouteLeave:(to,from,next)=>{
        console.log("进入路由之后");
        next() ;
      }
    }
```
### 在钩子函数中使用异步请求
1、安装Axios `cnpm install axios -s`
2、在main.js 中进行导入

```javascript

import axios from 'axios'
import VueAxios from 'vue-axios'

Vue.use(VueAxios, axios) ;
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200910191242466.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```javascript
  export default {
      props:['id'],
      name: "UserProfile",
      beforeRouteEnter:(to,from,next)=>{
        console.log("进入路由之前");
        next(vm =>{
          vm.getData() ; // 进入如有之前执行getData
        }) ;
      },
      beforeRouteLeave:(to,from,next)=>{
        console.log("进入路由之后");
        next() ;
      },
      methods:{
        getData: function(){
          this.axios({
            method:'get',
            url :'http://localhost:8080/static/mock/data.json'
          }).then(function(response){
            console.log(response)
          })
        }
      }
    }
```

# 常见异常及其错误
## ①webpack-dev-server不是内部或外部命令
[参考链接](https://blog.csdn.net/yanmuchen/article/details/90544477)

