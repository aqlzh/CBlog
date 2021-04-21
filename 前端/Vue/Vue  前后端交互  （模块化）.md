@[toc]
# 模块化的分类
## 浏览器端的模块化
  1.`AMD`(Asynchronous Module Definition,异步模块定义)
        代表产品为：Require.js
  2.`CMD`(Common Module Definition,通用模块定义)
        代表产品为：Sea.js
## 服务器端的模块化
  服务器端的模块化规范是使用`CommonJS`规范：
  
 1、使用require引入其他模块或者包
 2、使用exports或者module.exports导出模块成员
  3、一个文件就是一个模块，都拥有独立的作用域
### ES6模块化
ES6模块化规范中定义：
1、每一个js文件都是独立的模块
 2、导入模块成员使用import关键字
 3、暴露模块成员使用export关键字

## NodeJS中安装babel
1、打开终端首先
```bash
npm install --save-dev @babel/core @babel/cli @babel/preset-env @babel/node
```
2、其次再输入配置

```bash
npm install --save @babel/polyfill
```
3、配置  `babel.config.js`

```javascript
const presets = [
  [
    '@babel/env',
    {
      targets: {
        edge: '17',
        firefox: '60',
        chrome: '67',
        safari: '11.1'
      }
    }
  ]
]

module.exports = { presets }

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209133425500.png)
# ES6  模块化基本语法
## 默认导入与导出

==注意==：在一个模块中，只允许使用`export default`向外默认暴露**一次**成员。

导出：
```javascript
    let num = 100;
    export default{
        num
    }
```
导入：

```javascript
  import test from "./test.js"
```
## 按需导入与导出
==注意==：一个模块中既可以**按需导入**也可以**默认导入**，且按需导入不限次数可以取别名。

导出：
```javascript
    export let num = 998;
    export let myName = "jack";
    export function fn = function(){ console.log("fn") }
```
导入：

```javascript
mport { num,fn as printFn ,myName } from "./test.js"
```


