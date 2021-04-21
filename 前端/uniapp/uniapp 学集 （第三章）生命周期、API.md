
**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 有道无术，术尚可求；
> 有术无道，终止于术!
> 
> 多端运行，架式简化；
> 编程路漫，学无止尽！

@[toc]
# 条件编译
[官方文档参考](https://uniapp.dcloud.io/platform?id=%e6%9d%a1%e4%bb%b6%e7%bc%96%e8%af%91)
可以使用 `process.env.NODE_ENV` 来获取运行环境
运行编译---> 开发环境
发行编译--->生产环境

`development` 是开发环境
`production`    是生产环境


```javascript
#ifdef ：只在某平台出现
#ifndef ：  除了某平台以外都出现
#endif ： 结尾标识符
```
# 生命周期
[官方文档参考](https://uniapp.dcloud.io/frame?id=%e7%94%9f%e5%91%bd%e5%91%a8%e6%9c%9f)
往期参考
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004115321730.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
[跳转链接](https://blog.csdn.net/QuantumYou/article/details/108445348)
## 应用生命周期

应用生命周期是针对一整个应用去触发的，如应用启动、初始化、报错等。

应用生命周期只能在 `App.vue` 中监听，其他页面无法监听

| 函数名               | 说明                                                         |
| :------------------- | :----------------------------------------------------------- |
| onLaunch             | 当`uni-app` 初始化完成时触发（全局只触发一次）               |
| onShow               | 当 `uni-app` 启动，或从后台进入前台显示                      |
| onHide               | 当 `uni-app` 从前台进入后台                                  |
| onError              | 当 `uni-app` 报错时触发                                      |
| onUniNViewMessage    | 对 `nvue` 页面发送的数据进行监听，可参考 [nvue 向 vue 通讯](https://uniapp.dcloud.io/use-weex?id=nvue-向-vue-通讯) |
| onUnhandledRejection | 对未处理的 Promise 拒绝事件监听函数（2.8.1+）                |
| onPageNotFound       | 页面不存在监听函数                                           |
| onThemeChange        | 监听系统主题变化                                             |

代码演示

```javascript
<script>
	export default {
		onLaunch() {
			console.log("app初始化完成")
		},
		onShow() {
			console.log("app启动")
		},
		onHide() {
			console.log("App进入后台")
		}
	}
</script>

<style>
	/*每个页面公共css */
</style>

```

## 页面生命周期

页面生命周期就类似于Vue中的生命周期，在每个页面加载、进入、渲染、销毁等场景触发

| 函数名                              | 说明                                                         | 平台差异说明                                         | 最低版本 |
| :---------------------------------- | :----------------------------------------------------------- | :--------------------------------------------------- | :------- |
| onLoad                              | 监听页面加载，其参数为上个页面传递的数据，参数类型为Object（用于页面传参），参考[示例](https://uniapp.dcloud.io/api/router?id=navigateto) |                                                      |          |
| onShow                              | 监听页面显示。页面每次出现在屏幕上都触发，包括从下级页面点返回露出当前页面 |                                                      |          |
| onReady                             | 监听页面初次渲染完成。注意如果渲染速度快，会在页面进入动画完成前触发 |                                                      |          |
| onHide                              | 监听页面隐藏                                                 |                                                      |          |
| onUnload                            | 监听页面卸载                                                 |                                                      |          |
| onResize                            | 监听窗口尺寸变化                                             | App、微信小程序                                      |          |
| onPullDownRefresh                   | 监听用户下拉动作，一般用于下拉刷新，参考[示例](https://uniapp.dcloud.io/api/ui/pulldown) |                                                      |          |
| onReachBottom                       | 页面上拉触底事件的处理函数                                   |                                                      |          |
| onTabItemTap                        | 点击 tab 时触发，参数为Object，具体见下方注意事项            | 微信小程序、百度小程序、H5、App（自定义组件模式）    |          |
| onShareAppMessage                   | 用户点击右上角分享                                           | 微信小程序、百度小程序、字节跳动小程序、支付宝小程序 |          |
| onPageScroll                        | 监听页面滚动，参数为Object                                   |                                                      |          |
| onNavigationBarButtonTap            | 监听原生标题栏按钮点击事件，参数为Object                     | 5+ App、H5                                           |          |
| onBackPress                         | 监听页面返回，返回 event = {from:backbutton、  navigateBack} ，backbutton 表示来源是左上角返回按钮或 android 返回键；navigateBack表示来源是  uni.navigateBack ；详细说明及使用：[onBackPress 详解](http://ask.dcloud.net.cn/article/35120) | App、H5                                              |          |
| onNavigationBarSearchInputChanged   | 监听原生标题栏搜索输入框输入内容变化事件                     | App、H5                                              | 1.6.0    |
| onNavigationBarSearchInputConfirmed | 监听原生标题栏搜索输入框搜索事件，用户点击软键盘上的“搜索”按钮时触发。 | App、H5                                              | 1.6.0    |
| onNavigationBarSearchInputClicked   | 监听原生标题栏搜索输入框点击事件                             | App、H5                                              | 1.6.0    |
| onShareTimeline                     | 监听用户点击右上角转发到朋友圈                               | 微信小程序                                           | 2.8.1+   |
| onAddToFavorites                    | 监听用户点击右上角收藏                                       | 微信小程序                                           | 2.8.1+   |

`onPageScroll` 参数说明：

| 属性      | 类型   | 说明                                 |
| --------- | ------ | ------------------------------------ |
| scrollTop | Number | 页面在垂直方向已滚动的距离（单位px） |

`onTabItemTap` 参数说明：

| 属性     | 类型   | 说明                         |
| -------- | ------ | ---------------------------- |
| index    | String | 被点击tabItem的序号，从0开始 |
| pagePath | String | 被点击tabItem的页面路径      |
| text     | String | 被点击tabItem的按钮文字      |

`onNavigationBarButtonTap` 参数说明：

| 属性  | 类型   | 说明                     |
| ----- | ------ | ------------------------ |
| index | Number | 原生标题栏按钮数组的下标 |

`onBackPress` 回调参数对象说明：

| 属性 | 类型   | 说明                                                         |
| ---- | ------ | ------------------------------------------------------------ |
| from | String | 触发返回行为的来源：'backbutton'——左上角导航栏按钮及安卓返回键；'navigateBack'——uni.navigateBack() 方法。 |

代码演示

```javascript
<template>
	<view>
		<view v-for="item in arr">
			{{item}}
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				arr: [
				// 模拟下拉情况
					1,2,3,4,5,6,7,12312,5413,423,213,14,235,23,412,312,3125,8,9,10,11,12,12,131,41,123,412,412,321,5123,41,12,312,154,3,4312,32
				]
			}
		},
		onLoad(e) {
			console.log("页面加载", e)
		},
		onShow() {
			console.log("页面显示")
		},
		onPullDownRefresh() {
			this.arr = [
					1,2,3,4,5,6,7,12312,5413,423,213,14,235,23,412,312,3125,8,9,10,11,12,12,131,41,123,412,412,321,5123,41,12,312,154,3,4312,32
				]
			console.log("下拉刷新")
			setTimeout(()=>{
				uni.stopPullDownRefresh()
			}, 2000)
		},
		onReachBottom() {
			this.arr.push(...[
				1,2,34,4,5,6
			])
			console.log("触底加载")
		},
		onShareAppMessage() {
			console.log("点击了分享")
		},
		methods: {
			
		}
	}
</script>

<style>

</style>

```

# API
[官方文档参考](https://uniapp.dcloud.io/api/README)
## 网络请求
### 发起请求
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004125228212.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004125548685.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
### 文件下载
文件上传与下载对比学习
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004135607904.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

**OBJECT 参数说明**

| 参数名   | 类型     | 必填 | 说明                                                         |
| :------- | :------- | :--- | :----------------------------------------------------------- |
| url      | String   | 是   | 下载资源的 url                                               |
| header   | Object   | 否   | HTTP 请求 Header, header 中不能设置 Referer。                |
| success  | Function | 否   | 下载成功后以 tempFilePath 的形式传给页面，res = {tempFilePath: '文件的临时路径'} |
| fail     | Function | 否   | 接口调用失败的回调函数                                       |
| complete | Function | 否   | 接口调用结束的回调函数（调用成功、失败都会执行）             |

**注：文件的临时路径，在应用本次启动期间可以正常使用，如需持久保存，需在主动调用 [uni.saveFile](https://uniapp.dcloud.io/api/file/file?id=savefile)，才能在应用下次启动时访问得到。**

**success 返回参数说明**

| 参数         | 类型   | 说明                                           |
| :----------- | :----- | :--------------------------------------------- |
| tempFilePath | String | 临时文件路径，下载后的文件会存储到一个临时文件 |
| statusCode   | Number | 开发者服务器返回的 HTTP 状态码                 |


#### 监听的用法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004140728625.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004140825501.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

代码演示

```javascript
<template>
	<view>
		<button type="default" @click="getData()">点我发送请求</button>
		<button type="default" @click="download()">点我下载</button>
		 <progress :percent="percent" show-info />
	</view>
</template>

<script>
	export default {
		data() {
			return {
				percent: 0
			}
		},
		methods: {
			getData() {
				uni.request({
					url:"http://47.102.115.146:8080/department/departmentList",
					method:"GET",
					success(e) {
						console.log("请求成功", e)
					},
					fail(e) {
						console.log("请求失败", e)
					}
				})
			},
			download() {
				const task = uni.downloadFile({
					url:"https://ydsmarkdown.oss-cn-beijing.aliyuncs.com/audio/%E6%99%AF%E5%B2%97%E5%B1%B1%20-%20%E5%AE%88%E4%B8%9A%E6%9B%B4%E6%AF%94%E5%88%9B%E4%B8%9A%E9%9A%BE.mp3",
					success(e) {
						console.log("下载成功！", e)
					},
					fail(e) {
						console.log("下载失败！", e)
					}
				})
				task.onProgressUpdate((e) => {
					this.percent = e.progress
				})
			}
		}
	}
</script>

<style>

</style>

```

> 文件下载同样可以监听，用法和上传一样。

## 路由跳转
[官方文档参考](https://uniapp.dcloud.io/api/router?id=navigateto)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020100414540424.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

> ==重点==： navigateTo   ,redirectTo,    reLaunch


### 窗口动画

本API仅App支持

窗口的显示/关闭动画效果，支持在 API、组件、pages.json 中配置，优先级为：`API = 组件 > pages.json`。

#### API

有效的路由 API

- navigateTo
- navigateBack

```javascript
uni.navigateTo({
    url: '../test/test',
    animationType: 'pop-in',
    animationDuration: 200
});
uni.navigateBack({
    delta: 1,
    animationType: 'pop-out',
    animationDuration: 200
});
```

#### 组件

open-type 有效值

- navigateTo
- navigateBack

```html
<navigator animation-type="pop-in" animation-duration="300" url="../test/test">navigator</navigator>
<navigator animation-type="pop-out" animation-duration="300" open-type="navigateBack" >navigator</navigator>
```

#### pages.json

pages.json 中配置的是窗口显示的动画

```javascript
"style": {
    "app-plus": {
        "animationType": "fade-in",
        "animationDuration": 300
    }
}
```

显示动画与关闭动画，会有默认的对应规则。但是如果通过 API 或组件配置了窗口关闭的动画类型，则不会使用默认的类型。

| 显示动画        | 关闭动画         | 显示动画描述（关闭动画与之相反）                 |
| :-------------- | :--------------- | :----------------------------------------------- |
| slide-in-right  | slide-out-right  | 新窗体从右侧进入                                 |
| slide-in-left   | slide-out-left   | 新窗体从左侧进入                                 |
| slide-in-top    | slide-out-top    | 新窗体从顶部进入                                 |
| slide-in-bottom | slide-out-bottom | 新窗体从底部进入                                 |
| pop-in          | pop-out          | 新窗体从左侧进入，且老窗体被挤压而出             |
| fade-in         | fade-out         | 新窗体从透明到不透明逐渐显示                     |
| zoom-out        | zoom-in          | 新窗体从小到大缩放显示                           |
| zoom-fade-out   | zoom-fade-in     | 新窗体从小到大逐渐放大并且从透明到不透明逐渐显示 |
| none            | none             | 无动画                                           |
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004150116797.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

