@[toc]
> 须知少年凌云志，曾许人间第一流

# axios 介绍
[Github跳转地址](https://github.com/axios/axios)
- 基于promise用于浏览器和node.js的http客户端
- 支持浏览器和node.js
- 支持promise
- 能拦截请求和响应
- 自动转换JSON数据
- 能转换请求和响应数据

==注意==：拿到 ret 是一个对象      所有的对象都存在 ret 的data 属性里面
```javascript
	axios.get('http://localhost:3000/adata').then(function(ret){   
      // 注意data属性是固定的用法，用于获取后台的实际数据
      // console.log(ret.data)
      console.log(ret)
    })
```

index.js  后台
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210205235232930.png)

# axios基础用法
**axios常用API**  
- get : 查询数据
- post : 添加数据
- put :  修改数据
- delete 删除数据 

## get和 delete请求传递参数
  - 通过传统的url  以 ? 的形式传递参数
  - restful 形式传递参数 
  - 通过params  形式传递参数 

###  get 请求传递参数
```javascript
1、 传统的url  以 ? 的形式传递参数
axios.get('http://localhost:3000/axios?id=123').then(function(ret){
      console.log(ret.data)
    })
    
2、通过restful 形式传递参数 
    axios.get('http://localhost:3000/axios/123').then(function(ret){
      console.log(ret.data)
    })
    
3、 通过params  形式传递参数 
    axios.get('http://localhost:3000/axios', {
      params: {
        id: 789
      }
    }).then(function(ret){
      console.log(ret.data)
    })
```
分别对应的  index.js   后台

1、传统 URL  
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210205235315950.png)
2、 Restful   ,注意：其 `res.send ()`  后加的参数 `req.params.id`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210205235328801.png)
3、params  形式
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210205235344774.png)
###  delete 请求传递参数
axios delete 请求传参     传参的形式和 get 请求一样
```javascript

    axios.delete('http://localhost:3000/axios', {
      params: {
        id: 111
      }
    }).then(function(ret){
      console.log(ret.data)
    })

```

index.js   后台

```javascript
app.delete('/axios',(req,res) = > {
  res.send ('axios get  传递参数' + req.query.id) ;
})
```

## post  和 put  请求传递参数
==POST==
### 通过选项传递参数

```javascript
    axios.post('http://localhost:3000/axios', {
      uname: 'lisi',
      pwd: 123
    }).then(function(ret){
      console.log(ret.data)
    })
```
浏览器 响应头 显示的格式  JSON
### 通过 URLSearchParams  传递参数 

```javascript
var params = new URLSearchParams();
params.append('uname', 'zhangsan');
params.append('pwd', '111');
axios.post('http://localhost:3000/axios', params).then(function(ret){
  console.log(ret.data)
})
```

后台代码  index.js

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210207001201830.png)

浏览器 响应头 显示的格式  字符串

==PUT==

axios put 请求传参   和 post 请求一样 

```javascript
    axios.put('http://localhost:3000/axios/123', {
      uname: 'lisi',
      pwd: 123
    }).then(function(ret){
      console.log(ret.data)
    })
后台代码  i
```

ndex.js
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210207001221220.png)
## axios  响应结果
### 响应结果的基础属性
`data`   实际响应回来的数据
`headers`  响应头信息 
`status`   响应状态码
`statusText`  响应状态信息

### axios  全局配置
1、配置公共的请求头 

```javascript
axios.defaults.baseURL = 'https://api.example.com';

```

2、配置 超时时间

```bash
axios.defaults.timeout = 2500;
```

3、配置公共的请求头

```bash
axios.defaults.headers.common['Authorization'] = AUTH_TOKEN;
```

4、配置公共的 post 的 Content-Type

```bash
axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';
```


```javascript
axios.get('axios-json').then(function(ret){
  console.log(ret.data.uname)
})
```
## axios  拦截器
###  1. 请求拦截器 
对发送请求前做配置信息


```javascript
axios.interceptors.request.use(function(config) {
     console.log(config.url)
   // 1.1  任何请求都会经过这一步   在发送请求之前做些什么   
  config.headers.mytoken = 'nihao';
    // 1.2  这里一定要return   否则配置不成功  
      return config;
    }, function(err){
       //1.3 对请求错误做点什么    
      console.log(err)
    })
	
   ```

### 2、响应拦截器
获取数据前对数据做加工处理
```javascript
    axios.interceptors.response.use(function(res) {
      #2.1  在接收响应做些什么  
      var data = res.data;
      return data;
    }, function(err){
      #2.2 对响应错误做点什么  
      console.log(err)
    })
```
# async/await
`async/await` 是ES7引入的新语法，可以更加方便的进行异步操作
`async` 关键字用于函数上（async函数的返回值是 Promise实例对象）
`await`  关键字用于 async函数当中（ await可以得到异步的結果）


**async/await 让异步代码看起来、表现起来更像同步代码**
```javascript
# 1.  async 基础用法
    # 1.1 async作为一个关键字放到函数前面
	async function queryData() {
      # 1.2 await关键字只能在使用async定义的函数中使用      await后面可以直接跟一个 Promise实例对象
      var ret = await new Promise(function(resolve, reject){
        setTimeout(function(){
          resolve('nihao')
        },1000);
      })
      // console.log(ret.data)
      return ret;
    }
	# 1.3 任何一个async函数都会隐式返回一个promise   我们可以使用then 进行链式编程
    queryData().then(function(data){
      console.log(data)
    })

	#2.  async    函数处理多个异步函数
    axios.defaults.baseURL = 'http://localhost:3000';

    async function queryData() {
      # 2.1  添加await之后 当前的await 返回结果之后才会执行后面的代码   
      
      var info = await axios.get('async1');
      #2.2  让异步代码看起来、表现起来更像同步代码
      var ret = await axios.get('async2?info=' + info.data);
      return ret.data;
    }

    queryData().then(function(data){
      console.log(data)
    })
```

