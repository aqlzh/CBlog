**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# 缩写
## v-bind 

```html
<a v-bind:href="url">...</a>
<a :href="url">...</a>
```

## v-on 

```html
<a v-on:click="doSomething">...</a>
<a @click="doSomething">...</a>
```

# 网络通信
`Axios`是一个开源的可以用在浏览器端和`Node.js`的异步通信框架，主要作用就是实现AJAⅩ异步通信。
## 功能特点：
（1）从浏览器中创建 XmlHttpRequests
（2）从node.js创建http请求
（3）支持 Promise API (JS中链式编程)
（4）拦截请求和响应
（5）转换请求数据和响应数据
（6）取消请求
（7）自动转换JSON数据
（8）客户端支持防御XSRF（跨站请求伪造）

Github：https：//github.com/axios/axios
中文文档：http：//www.axiosjs.com/

核心 :`axios.get()`
之前:`$.get()`  `Jquery.ajax()`
```html
<!DOCTYPE html>
<html lang="en" >
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<style>
    [v-clock]{
        display: none;
    }
</style>
<body>
<div id="app" v-clock>
    <div>{{info.name}}</div>
    <div>{{info.address.street}}</div>
</div>

<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js"></script>
<script src="https://unpkg.com/axios/dist/axios.min.js"></script>
<script>
    var vm = new Vue({
        // Model 数据
        el:"#app",
        // data:{         // vm 属性
        //     message:"null"
        // },
        data(){    // 方法
            return{  //请求返回参数须和json 字符串一致
              info:{
                  name : null,
                  address: {
                      street : null,
                      city:null,
                      county :null
                  },
                  url : null
              }
            }
        },
        mounted(){   //钩子函数
            axios.get('../data.json').then(response=>(this.info=response.data)) ;

        }
    }) ;
</script>
</body>
</html>
```
## 注意
`v-clock` 防止页面闪烁指令
`mounted(){}`  钩子函数
`data()  {}`  传递数据方法 与 `data:  vm` 属性相异

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200907125253311.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200907125246888.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

# 生命周期
Vue实例有一个完整的生命周期，也就是从开始创建、初始化数据、编译模板、挂载DOM、渲染→更新→渲染、卸载等一系列过程，我们称这是Vue的生命周期。通俗说就是vue实例从创建到销毁的过程，就是生命周期。

[官网跳转](https://cn.vuejs.org/v2/guide/instance.html)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200907121819177.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
# 计算属性
调用方法时，每次都需要进行计算，有计算过程则必定产生系统开销，如果这个结果是不经常变化的呢，此时就可以考虑将数个结果**缓存**起来，采用计算属性可以很方便的做到，计算属性的主要特性就是为了将不经常变化的计算结果进行缓存，以节约我们的系统开销。

实质为属性，区别于方法。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200907144731975.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

```html
<!DOCTYPE html>
<html lang="en" xmlns:v-bind="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<div id="app">
    <p>currentTime1: {{currentTime1()}}</p>
    <p>currentTime2: {{currentTime2}}</p>
</div>

<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js"></script>
<script>
    var vm = new Vue({
        // Model 数据
        el:"#app",
        data: {
            message: "LZH_Hello"
        },
        methods :{
            currentTime1 : function(){
                return Date.now() ;
            }
        },
        computed :{
            currentTime2: function(){
                return Date.now() ;
            }

        }
    }) ;
</script>
</body>
</html>
```
# Vue 插槽
[官网链接](https://cn.vuejs.org/v2/guide/components-slots.html#ad)
## 前序代码

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>solt</title>
</head>
<body>
<div id="app">
<!--    <ul>-->
<!--        <li>Java</li>-->
<!--        <li>C</li>-->
<!--        <li>Python</li>-->
<!--    </ul>-->
    <todo>
        <todo-title></todo-title>
        <todo-items></todo-items>
    </todo>
</div>
<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js"></script>
<script>

    Vue.component("todo",{
        template:
            '<div>' +
              '<slot></slot>'+
                  '<ul>'+
                    '<slot></slot>'+
                  '</ul>'+
            '</div>'
    });
    Vue.component("todo-title",{
        template: '<div>标题</div>'
    });

    Vue.component("todo-items",{
        template:'<li>Java</li>'
    }) ;
    var vm = new Vue({
        // Model 数据
        el:"#app",
        data:{
        }
    }) ;
</script>
</body>
</html>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908110618880.png#pic_center)
## 优化代码

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>solt</title>
</head>
<body>
<div id="app">
<!--    <ul>-->
<!--        <li>Java</li>-->
<!--        <li>C</li>-->
<!--        <li>Python</li>-->
<!--    </ul>-->
    <todo>
        <todo-title slot="todo-title" :title="title"></todo-title>
        <todo-items slot="todo-items" v-for="item in todoItems" :item="item"></todo-items>
    </todo>
</div>
<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js"></script>
<script>

    Vue.component("todo",{
        template:
            '<div>' +
              '<slot name="todo-title"></slot>'+
                  '<ul>'+
                    '<slot name="todo-items"></slot>'+
                  '</ul>'+
            '</div>'
    });
    Vue.component("todo-title",{
        props:['title'],
        template: '<div>{{title}}</div>'
    });

    Vue.component("todo-items",{
        props:['item'],
        template:'<li>{{item}}</li>'
    }) ;
    var vm = new Vue({
        // Model 数据
        el:"#app",
        data:{
            title:"学习内容",
            todoItems:["Java","C","Linux","Python"]
        }
    }) ;
</script>
</body>
</html>
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020090811201731.png#pic_center)
# 自定义事件

[JavaScript 使用参考链接](https://www.runoob.com/jsref/jsref-splice.html)
通过代码发现，数据项在vue的实例中，但删除操作要在组件中完成，那么组件如何才能删除vue实例中的数据？此时就涉及到==参数传递与事件分发==，Vue为我们提供了自定义事件的功能，使用`this.$emit`（自定义事件名，参数），操作过程如下

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>solt</title>
</head>
<body>
<div id="app">
<!--    <ul>-->
<!--        <li>Java</li>-->
<!--        <li>C</li>-->
<!--        <li>Python</li>-->
<!--    </ul>-->
    <todo>
        <todo-title slot="todo-title" :title="title"></todo-title>
        <todo-items slot="todo-items" v-for="(item,index) in todoItems"
                    :item="item" v-bind:index="index" v-on:remove="removeItems(index)" :key="index"></todo-items>
    </todo>
</div>
<script src="https://cdn.jsdelivr.net/npm/vue@2.5.21/dist/vue.min.js"></script>
<script>

    Vue.component("todo",{
        template:
            '<div>' +
              '<slot name="todo-title"></slot>'+
                  '<ul>'+
                    '<slot name="todo-items"></slot>'+
                  '</ul>'+
            '</div>'
    });
    Vue.component("todo-title",{
        props:['title'],
        template: '<div>{{title}}</div>'
    });

    Vue.component("todo-items",{
        props:['item','index'],
        template:'<li>{{index}}----{{item}}<button @click="remove">删除</button></li>',
        methods :{
            remove : function(index){
                // 自定义事件分发
                this.$emit('remove',index) ;
            }
        }
    }) ;
    var vm = new Vue({
        // Model 数据
        el:"#app",
        data:{
            title:"学习内容",
            todoItems:["Java","C","Linux","Python"]
        },
        methods:{
            removeItems : function(index){
                console.log("删除了"+this.todoItems[index]+"OK");
                this.todoItems.splice(index,1) ;
            }
        }
    }) ;
</script>
</body>
</html>
```

