> 永远相信美好的事即将发生 !

@[toc]
# Webpack
 
 webpack  打包示意图
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209153657471.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
[往期参考](https://blog.csdn.net/QuantumYou/article/details/108467732)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209154833540.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## webpack  基本使用
### 创建项目目录并初始化
创建项目，并打开项目所在目录的终端，输入命令：

```css
npm init -y
```
### 创建首页及js文件
在项目目录中创建index.html页面
在项目目录中创建js文件夹，并在文件夹中创建`index.js`文件
### 安装jQuery
打开项目目录终端，输入命令:

```bash
 npm install jQuery -S
```

### 导入jQuery
打开index.js文件，编写代码导入jQuery并实现功能：

```bash
import $ from "jquery";
$(function(){
    $("li:odd").css("background","cyan");
    $("li:odd").css("background","pink");
})
```
==运行发现==：
报错 因为import $ from "jquery";这句代码属于ES6的新语法代码，在浏览器中可能会存在兼容性问题。

## 安装配置webpack
1、输入如下代码

```bash
 npm install webpack webpack-cli -D
```
2、在项目根目录中，创建一个 `webpack.config.js` 的配置文件
在 `webpack.config.js` 文件中编写代码进行webpack配置，如下：

```javascript
module.exports = {
    mode:"development"//可以设置为development(开发模式)，production(发布模式)
}
```
3、修改项目中的`package.json`文件添加运行脚本dev，如下：

```javascript
"scripts":{
    "dev":"webpack"
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209164432866.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)



  4、运行 `npm run dev` 命令进行项目打包，并在页面中引入项目打包生成的js文件（即为在 `dist` 路径下生成的 `main.js`）
    
## 配置打包的入口与出口
### 默认打包方式
将`src/index.js` 作为默认的**打包入口**js文件
将`dist/main.js` 作为默认的**打包输出**js文件

### 配置打包方式
`--dirname` 表示当前文件的绝对路径

```javascript
    const path = require("path");
    module.exports = {
        mode:"development",
        //设置入口文件路径
        entry: path.join(__dirname,"./src/xx.js"),
        //设置出口文件
        output:{
            //设置路径
            path:path.join(__dirname,"./dist"),
            //设置文件名
            filename:"res.js"
        }
    }
```
### 配置自动打包功能
原因： 在修改代码后需要 重新运行 `npm run dev`
1、安装自动打包的包

```css
 npm install webpack-dev-server -D
```
2、修改`package.json`中的dev指令如下：

```javascript
    "scripts":{
      "dev":"webpack-dev-server"
            }
```
  3、将引入的js文件路径更改为：`<script src="/bundle.js"></script>`
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209184824121.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

  4、运行npm run dev，进行打包
   5、打开网址查看效果：http://localhost:8080
   ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209184846785.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

   ==注意==：
1、webpack-dev-server会启动个实时打包的http服务器
2、webpack-dev- server打包生成的输出文件，默认放到了项目根目录中，而且是虚拟的、看不见的

## 配置html-webpack-plugin  
此为预览插件

使用  `npm install html-webpack-plugin -D`   安装预览功能包


 1、安装默认预览功能的包:`html-webpack-plugin`

```javascript
  npm install html-webpack-plugin -D
```

   2、修改`webpack.config.js`文件，如下：

```javascript
     //导入包
  const HtmlWebpackPlugin = require("html-webpack-plugin");
      //创建对象
     const htmlPlugin = new HtmlWebpackPlugin({
                //设置生成预览页面的模板文件
                template:"./src/index.html",
                //设置生成的预览页面名称
                filename:"index.html"
            })
```
   3、继续修改`webpack.config.js`文件，添加plugins信息：

```javascript
            module.exports = {
                ......
                plugins:[ htmlPlugin ]
            }
```
## 配置自动打开浏览器页面
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209220321343.png)
```javascript
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "dev": "webpack-dev-server --open --host 127.0.0.1 --port 8888",
    "build": "webpack -p"
  },
```
## Webpack  加载器
loader  调用过程图示
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209220533120.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### css 打包器
1、 安装 style-loader 安装包处理样式文件

```bash
npm  install style-loader css-loader -D
```
2、 在`webpack.config.js`  的module  的rules  数组中配置
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209221215159.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```javascript
 plugins: [htmlPlguin, new VueLoaderPlugin()],
  module: {
    rules: [
      { test: /\.css$/, use: ['style-loader', 'css-loader', 'postcss-loader'] },
      { test: /\.less$/, use: ['style-loader', 'css-loader', 'less-loader'] },
      { test: /\.scss$/, use: ['style-loader', 'css-loader', 'sass-loader'] },
      { test: /\.jpg|png|gif|bmp|ttf|eot|svg|woff|woff2$/, use: 'url-loader?limit=16941' },
      { test: /\.js$/, use: 'babel-loader', exclude: /node_modules/ },
      { test: /\.vue$/, use: 'vue-loader' }
    ]
  }
```
3、  在  index.js    导入相应配置

```javascript
import './css/1.css'
```

==注意==：
1、 use   数组中指定的  loader 顺序是固定的
2、 多个loader  的调用顺序是从后往前调


### less 打包器
1、运行如下命令

```bash
npm i less-loader less  -D
```
2、 在`webpack.config.js`  的module  的rules  数组中配置
```javascript
 { test: /\.less$/, use: ['style-loader', 'css-loader', 'less-loader'] },
```
3、  在  index.js    导入相应配置

### 配置 postCSS  自动添加 css  的兼容前缀

==目的==： 解决各个浏览器的兼容问题

1、运行 `npm  i  postcss-loader autoprefixer  -D`   命令 
2、在项目根目录中创建 postcss 的配置文件 `postcss.config.js`   并初始化如下配置
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209224834929.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```javascript
const autoprefixer = require('autoprefixer')

module.exports = {
  plugins: [autoprefixer]
}

```
3、在`webpack.config.js`  修改css  的loader  的规则如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209223949690.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```clike
 { test: /\.css$/, use: ['style-loader', 'css-loader', 'postcss-loader'] },
```
###  打包样式表中的图片和字体文件
 1、运行  `npm install url-loader file-loader -D`
2、更改`webpack.config.js`的module中的rules数组

```javascript
module.exports = {
    ......
    plugins:[ htmlPlugin ],
    module : {
        rules:[
            {
                //test设置需要匹配的文件类型，支持正则
                test:/\.css$/,
                //use表示该文件类型需要调用的loader
                use:['style-loader','css-loader']
            },
            {
                test:/\.less$/,
                use:['style-loader','css-loader','less-loader']
            },
            {
                test:/\.scss$/,
                use:['style-loader','css-loader','sass-loader']
            },{
                test:/\.jpg|png|gif|bmp|ttf|eot|svg|woff|woff2$/,
                //limit用来设置字节数，只有小于limit值的图片，才会转换
                //为base64图片
                use:"url-loader?limit=16940"
            }
        ]
    }
}
```
==注意==：

> 1、其中 ？  之后的是 loader  的参数项 
> 2、limit   用来指定图片的大小，单位是字节（byte），只有limit
> 大小的图片，才能被转换为 base64  图片

### 打包处理JS中高级语法

我们需要安装babel系列的包
1、安装babel转换器
  

```css
  npm install babel-loader @babel/core @babel/runtime -D
```

2、安装babel语法插件包

```css
npm install @babel/preset-env @babel/plugin-transform-runtime @babel/plugin-proposal-class-properties -D
```

3、在项目根目录创建并配置`babel.config.js`文件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210209230840394.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

    
```javascript
    module.exports = {
        presets:["@babel/preset-env"],
        plugins:[ "@babel/plugin-transform-runtime", "@babel/plugin-proposal-class-properties" ]
    }
```

4、配置规则：更改`webpack.config.js`的module中的rules数组

```javascript
module.exports = {
    ......
    plugins:[ htmlPlugin ],
    module : {
        rules:[
            {
                //test设置需要匹配的文件类型，支持正则
                test:/\.css$/,
                //use表示该文件类型需要调用的loader
                use:['style-loader','css-loader',exclude : /node_modules/]
            },
```

## Vue 单文件组件

==传统组件存在的问题 ：==
1、全局定义的组件不能重名
2、字符串模板缺乏语法高亮，在HTML多行时需要 `\`
3、不支持css(当html和js组件化时，css没有参与其中
4、没有构建步骤限制，只能使用H5和ES5，不能使用预处理器（babel）


### 单文件的组成结构
`template`    组件的模板区域
`script`    业务逻辑区域
`style`    样式区域 


代码：

```html
<template>

    //组件代码区域
 <div>
  <h1>这是App.vue  根组件</h1>
 </div>
 
</template>

<script>

    //js代码区域
    export 

</script>

<style scoped>

    样式代码区域

</style>
```
导入单文件组件

```javascript
import App Vue from ' ./components/App.vue' 
```

### webpack配置vue 组件加载器
1、安装vue组件的加载器
 

```bash
   npm install vue-loader vue-template-compiler -D
```

2、配置规则：更改`webpack.config.js`的module中的rules数组

```javascript
    const VueLoaderPlugin = require("vue-loader/lib/plugin");
    const vuePlugin = new VueLoaderPlugin();
    module.exports = {
        ......
        plugins:[ htmlPlugin, vuePlugin  ],
        module : {
            rules:[
                ...//其他规则
                { 
                    test:/\.vue$/,
                    loader:"vue-loader",
                    
                }
            ]
        }
    }

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210210145945334.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### 在webpack项目中使用 vue
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210210150635892.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

将vue单文件组件能够使用，我们必须要安装vue，并使用vue来引用vue单文件组件。
1、安装Vue    `npm install vue -S`
2、在index.js中引入`vue：import Vue from "vue"`
3、创建Vue实例对象并指定el，最后使用`render`函数渲染单文件组件

==注意==：

> 建议使用 render 函数 ，而不是template 等模块等，因为导入的是Vue 的简化版，有可能不支持

```javascript
    const vm = new Vue({
        el:"#first",
        render:h=>h(app)
    })

```

## webpack打包发布项目
在项目上线之前，我们需要将整个项目打包并发布。
1、 配置`package.json`

```javascript
    "scripts":{
        "dev":"webpack-dev-server",
        "build":"webpack -p"
    }
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210210150914942.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

2、在项目打包之前，可以将dist目录删除，生成全新的dist目录
3、在终端运行 `npm  run build`   ,进行打包
