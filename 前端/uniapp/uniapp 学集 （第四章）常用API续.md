
**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 有道无术，术尚可求；
> 有术无道，终止于术!
> 
> 多端运行，架式简化；
> 编程路漫，学无止尽！

@[toc]
# 数据缓存
[官方文档参考](https://uniapp.dcloud.io/api/storage/storage?id=setstorage)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020100419223610.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004192514289.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
代码编写
```javascript
<template>
	<view>
		<button type="default" @click="setData">异步set</button>
		<button type="default" @click="setDataSync">同步set</button>
		<button type="default" @click="getData">异步get</button>
		<button type="default" @click="getDataSync">同步get</button>
		<button type="default" @click="removeData">异步remove</button>
		<button type="default" @click="removeDataSync">同步remove</button>
	</view>
</template>

<script>
	export default {
		data() {
			return {

			}
		},
		methods: {
			setData() {
				console.log("调用前")
				uni.setStorage({
					key: "token",
					data: "56678484113483212",
					success(e) {
						console.log("set成功", e)
					}
				})
				console.log("调用后")
			},
			setDataSync() {
				console.log("调用前")
				uni.setStorageSync("username", "张三")
				console.log("调用后")
			},
			getData() {
				console.log("调用前")
				uni.getStorage({
					key: "token",
					success(e) {
						console.log("get成功", e)
					}
				})
				console.log("调用后")
			},
			getDataSync() {
				const data = uni.getStorageSync("username", "")
				console.log(data)
			},
			removeData() {
				console.log("调用前")
				uni.removeStorage({
					key:"username",
					success(e) {
						console.log("删除成功！", e)
					}
				})
				console.log("调用后")
			},
			removeDataSync() {
				uni.removeStorageSync("token")
			}
		}
	}
</script>

<style>

</style>

```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004204150139.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
# 位置
[官方文档参考](https://uniapp.dcloud.io/api/location/location)
## uni.getLocation

## uni.chooseLocation
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201004213926796.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
# 视频组件控制
[官方文档参考]()
#### uni.createVideoContext
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201005100632540.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

创建并返回 video 上下文 videoContext 对象。在自定义组件下，第二个参数传入组件实例this，以操作组件内 `<video>` 组件。

**平台差异说明**

| App  |  H5  | 微信小程序 |    支付宝小程序    | 百度小程序 | 字节跳动小程序 | QQ小程序 |
| :--: | :--: | :--------: | :----------------: | :--------: | :------------: | :------: |
|  √   |  √   |     √      | 基础库版本>=1.10.0 |     √      |       √        |    √     |

**videoContext 对象的方法列表**

| 方法              | 参数     | 说明                                                         | 平台差异说明                     |
| :---------------- | :------- | :----------------------------------------------------------- | :------------------------------- |
| play              | 无       | 播放                                                         |                                  |
| pause             | 无       | 暂停                                                         |                                  |
| seek              | position | 跳转到指定位置，单位 s                                       |                                  |
| stop              |          | 停止视频                                                     | 微信小程序                       |
| sendDanmu         | danmu    | 发送弹幕，danmu 包含两个属性 text, color                     |                                  |
| playbackRate      | rate     | 设置倍速播放，支持的倍率有 0.5/0.8/1.0/1.25/1.5。微信基础库2.6.3 起支持 2.0 倍速 |                                  |
| requestFullScreen | 无       | 进入全屏，可传入{direction}参数，详见 video 组件文档         |                                  |
| exitFullScreen    | 无       | 退出全屏                                                     |                                  |
| showStatusBar     | 无       | 显示状态栏，仅在iOS全屏下有效                                | 微信小程序、百度小程序、QQ小程序 |
| hideStatusBar     | 无       | 隐藏状态栏，仅在iOS全屏下有效                                | 微信小程序、百度小程序、QQ小程序 |



danmu-list 对象属性

| 字段  | 说明     |
| ----- | -------- |
| text  | 弹幕文本 |
| color | 弹幕颜色 |
| time  | 弹幕时间 |


> - app-nvue 平台 2.2.5+ 支持 uni.createVideoContext(videoId, this)
> - app-nvue 平台 2.2.5以下使用本API，需同时设置组件属性id和ref `<video id="video1" ref="video1"></video>`，或者直接使用 ref，例如 `this.$refs.video1`

```html
<template>
	<view>
		<video class="video" @play="play" id="myVideo" :enable-danmu="true" :danmu-list="danmu" :src="url" controls></video>
		<input type="text" v-model="content" placeholder="请输入弹幕内容" />
		<button type="default" @click="sendDanmu">点我发送弹幕</button>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				content: '',
				video: null,
				danmu: [{
						text: "尽志无悔",
						color: "#063ea5",
						time: 1
					},
					{

						text: "深思慎取",
						color: "#FFF",
						time: 4
					}
				],
				url: "https://ydsmarkdown.oss-cn-beijing.aliyuncs.com/video/a88711e041b5492ba2d1609723e6c008.mp4"
			}
		},
		methods: {
			play() {
				this.video = uni.createVideoContext("myVideo")
			},
			sendDanmu() {
				this.video.sendDanmu({
					text: this.content,
					color: "#FFF"
				})
				// 清除内容
				this.content = ''
				console.log(this.danmu)
			}
		}
	}
</script>

<style>
	.video {
		width: 750rpx;
	}
</style>

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020100510525158.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)



# 交互
[官方文档参考](https://uniapp.dcloud.io/api/ui/prompt)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201005155057193.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 交互反馈
代码实操

```javascript
<template>
	<view>
		<button type="default" @click="showToast">消息提示框</button>
		<button type="default" @click="showLoad">显示加载框</button>
		<button type="default" @click="showModal">显示模态框</button>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			showToast() {
				uni.showToast({
					title:"操作成功"
				})
			},
			showLoad() {
				uni.showLoading({
					title:"加载中..."
				})
				setTimeout(()=>{
					uni.hideLoading()
				}, 2000)
			},
			showModal() {
				uni.showModal({
					title:"提示",
					content:"冲冲冲！！",
					success(e) {
						if(e.confirm) {
							uni.showToast({
								title:"操作成功"
							})
						}
						if(e.cancel) {
							uni.showToast({
								title:"用户已取消"
							})
						}
					}
				})
			}
		}
	}
</script>

<style>

</style>

```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201005160746316.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201005160839361.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
## 页面通讯
组件交互
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201005163232709.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)
==注意==：nvue中不能同上述操作与vue进行交互
解法：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201005165558268.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

### uni.$on(eventName, callback)

**监听全局的自定义事件**。事件可以由 uni.$emit 触发，回调函数会接收所有传入事件触发函数的额外参数。

| 属性      | 类型     | 描述           |
| --------- | -------- | -------------- |
| eventName | String   | 事件名         |
| callback  | Function | 事件的回调函数 |

```javascript
		onLoad(e) {
			uni.$on("method2", () => {
				console.log("事件被调用了")
			})
		},
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201005170113111.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)


