@[toc]
# URL   地址格式
## 传统形式

```bash
schema:// host:port / path ? query # fragment 
```

`schema` :  协议 http ftp
`host` : 域名或 IP  地址
`port` : 端口  默认为  80
`path` ：  路径 abc/lzh/   (虚拟 用于区分资源)
`query` : 查询参数 uname=list&age = 12
`fragment` : 锚点 （哈希 Hash）  用于定位页面位置


## Restful 形式
### Http 请求方式
`GET`     查询
`POST` 添加
`PUT`   修改
`DELETE`  删除

　

# 异步调用
常见异步： 定时任务、Ajax、事件函数

==注意==： 如果存在依赖，则必须嵌套，易引起回调地狱

# Promise

- 主要解决异步深层嵌套的问题
- promise 提供了简洁的API  使得异步操作更加容易
-  本质是函数（对象）
## 使用方法

1、使用new来构建一个`Promise`
2、 Promise的构造函数接收一个参数，是函数，并且传入两个参数：		   `resolve`，`reject`， 分别表示异步操作执行成功后的回调函数和异步操作执行失败后的回调函数
  

```javascript
 
  <script type="text/javascript">
    var p = new Promise(function(resolve, reject){
      //2. 这里用于实现异步任务  setTimeout
      setTimeout(function(){
        var flag = false;
        if(flag) {
          //3. 正常情况
          resolve('hello');
        }else{
          //4. 异常情况
          reject('出错了');
        }
      }, 100);
    });

    p.then(function(data){
      console.log(data)
    },function(info){
      console.log(info)
    });
  </script>
```
## 基于Promise 发送Ajax 请求

```javascript
<script type="text/javascript">
    function queryData(url) {
     #   1.1 创建一个Promise实例
      var p = new Promise(function(resolve, reject){
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function(){
          if(xhr.readyState != 4) return;
          if(xhr.readyState == 4 && xhr.status == 200) {
            # 1.2 处理正常的情况
            resolve(xhr.responseText);
          }else{
            # 1.3 处理异常情况
            reject('服务器错误');
          }
        };
        xhr.open('get', url);
        xhr.send(null);
      });
      return p;
    }
	# 注意：  这里需要开启一个服务 
    # 在then方法中，你也可以直接return数据而不是Promise对象，在后面的then中就可以接收到数据了
    queryData('http://localhost:3000/data')
      .then(function(data){
        console.log(data)
        #  1.4 想要继续链式编程下去 需要 return  
        return queryData('http://localhost:3000/data1');
      })
      .then(function(data){
        console.log(data);
        return queryData('http://localhost:3000/data2');
      })
      .then(function(data){
        console.log(data)
      });
  </script>
```
---
==注意==：利用then  链式编程

1、then 调用上一个 return 的promise对象,即为return queryData('http://localhost:3000/data1');
2、then()  内函数的data  为上return  的值

## then 参数中返回值
### 1、 返回 Promise  实例对象

返回的实例对象会调用下一个 then

如上例子

### 2、返回普通值
返回的普通值会直接传递给下一个then，通过then参数中函数的参数接收该值



# Promise 常用API
##  实例方法

### .then()

- 得到异步任务正确的结果

### .catch()

- 获取异常信息

### .finally()

- 成功与否都会执行（不是正式标准） 

**代码实例**

```javascript
  
  <script type="text/javascript">
    function foo() {
      return new Promise(function(resolve, reject){
        setTimeout(function(){
          // resolve(123);
          reject('error');
        }, 100);
      })
    }
    // foo()
    //   .then(function(data){
    //     console.log(data)
    //   })
    //   .catch(function(data){
    //     console.log(data)
    //   })
    //   .finally(function(){
    //     console.log('finished')
    //   });

    // --------------------------
    // 两种写法是等效的
    foo()
      .then(function(data){
        # 得到异步任务正确的结果
        console.log(data)
      },function(data){
        # 获取异常信息
        console.log(data)
      })
      # 成功与否都会执行（不是正式标准） 
      .finally(function(){
        console.log('finished')
      });
  </script>
```
## 对象方法
- `Promise.all()`   并发处理多个异步任务，所有任务都执行完成才能得到结果

- `Promise.race()`    并发处理多个异步任务，只要有一个任务完成就能得到结果

两者都为接受数组作为参数，数组的对象（p1,p2,p3） 均为promise 实例。
前者的状态由三个promise 实例决定 
后者的状态当其中有一个实例的状态发生改变，则p的状态跟着改变，并把第一个改变状态的 promise的返回值，传给p的**回调函数**

```javascript
  <script type="text/javascript">

    function queryData(url) {
      return new Promise(function(resolve, reject){
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function(){
          if(xhr.readyState != 4) return;
          if(xhr.readyState == 4 && xhr.status == 200) {
            // 处理正常的情况
            resolve(xhr.responseText);
          }else{
            // 处理异常情况
            reject('服务器错误');
          }
        };
        xhr.open('get', url);
        xhr.send(null);
      });
    }


// 以上为封装的代码
    var p1 = queryData('http://localhost:3000/a1');
    var p2 = queryData('http://localhost:3000/a2');
    var p3 = queryData('http://localhost:3000/a3');
     Promise.all([p1,p2,p3]).then(function(result){
       //   all 中的参数  [p1,p2,p3]   和 返回的结果一 一对应["HELLO TOM", "HELLO JERRY", "HELLO SPIKE"]
       console.log(result) //["HELLO TOM", "HELLO JERRY", "HELLO SPIKE"]
     })
    Promise.race([p1,p2,p3]).then(function(result){
      // 由于p1执行较快，Promise的then()将获得结果'P1'。p2,p3仍在继续执行，但执行结果将被丢弃。
      console.log(result) // "HELLO TOM"
    })
  </script>
```

