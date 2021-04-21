**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 有道无术，术尚可求；
> 有术无道，终止于术!
> 
> 多端运行，架式简化；
> 编程路漫，学无止尽！

@[toc]
# NVUE
## 介绍
`uni-app` App端内置了一个基于 weex 改进的原生渲染引擎，提供了原生渲染能力。(native vue的缩写)

在App端，如果使用vue页面，则使用webview渲染；如果使用nvue页面，则使用原生渲染。一个App中可以同时使用两种页面，比如首页使用nvue，二级页使用vue页面，hello uni-app示例就是如此。

虽然nvue也可以多端编译，输出H5和小程序，但nvue的css写法受限，所以如果你不开发App，那么不需要使用nvue。

## 区别
[官方文档引址](https://uniapp.dcloud.io/use-weex?id=nvue%e5%bc%80%e5%8f%91%e4%b8%8evue%e5%bc%80%e5%8f%91%e7%9a%84%e5%b8%b8%e8%a7%81%e5%8c%ba%e5%88%ab)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201003133544756.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70#pic_center)

# 组件
## 视图容器
[官方文档参考](https://uniapp.dcloud.io/component/view)
### 视图容器（view）

视图容器，类似于html中的 `div`，用来包裹各种元素内容。

如果使用nvue，需要注意不能用该组件包裹文字，否则文字样式将不生效。

| 属性名                 | 类型    | 默认值 | 说明                                                         |
| :--------------------- | :------ | :----- | :----------------------------------------------------------- |
| hover-class            | String  | none   | 指定按下去的样式类。当 hover-class="none" 时，没有点击态效果 |
| hover-stop-propagation | Boolean | false  | 指定是否阻止本节点的祖先节点出现点击态 (冒泡)                      |
| hover-start-time       | Number  | 50     | 按住后多久出现点击态，单位毫秒                               |
| hover-stay-time        | Number  | 400    | 手指松开后点击态保留时间，单位毫秒                           |

> 如果使用 `<div>` 标签，编译时会被转换为 `<view>` ，但是不建议使用div

代码演示

```html
<template>
	<view>
		<view>我是view</view>
		<view class="view-container">
			<view class="view-item" hover-class="click-view">1</view>
			<view class="view-item" hover-class="click-view">2</view>
			<view class="view-item" hover-class="click-view">3</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			
		}
	}
</script>

<style>
.view-container {
	width: 750rpx;
	height: 300rpx;
	background-color: #007AFF;
	display: flex;
	flex-direction: row;
	align-items: center;
	justify-content: center;
}
.view-item {
	width: 200rpx;
	height: 200rpx;
	background-color: #F0AD4E;
}
.click-view {
	background-color: #DD524D;
}
</style>

```

### 可滚动视图（scroll-view）

可滚动视图区域，用于区域滚动。

该组件性能较差，建议只用于导航栏横向滚动场景，竖向滚动请不要使用。

| 属性名           | 类型        | 默认值 | 说明                                                         | 平台差异说明 |
| :--------------- | :---------- | :----- | :----------------------------------------------------------- | :----------- |
| scroll-x         | Boolean     | false  | 允许横向滚动                                                 |              |
| scroll-y         | Boolean     | false  | 允许纵向滚动                                                 |              |
| upper-threshold  | Number      | 50     | 距顶部/左边多远时（单位px），触发 scrolltoupper 事件         |              |
| lower-threshold  | Number      | 50     | 距底部/右边多远时（单位px），触发 scrolltolower 事件         |              |
| scroll-top       | Number      |        | 设置竖向滚动条位置                                           |              |
| scroll-left      | Number      |        | 设置横向滚动条位置                                           |              |
| scroll-into-view | String      |        | 值应为某子元素id（id不能以数字开头）。设置哪个方向可滚动，则在哪个方向滚动到该元素 |              |
| @scrolltoupper   | EventHandle |        | 滚动到顶部/左边，会触发 scrolltoupper 事件                   |              |
| @scrolltolower   | EventHandle |        | 滚动到底部/右边，会触发 scrolltolower 事件                   |              |
| @scroll          | EventHandle |        | 滚动时触发，event.detail = {scrollLeft, scrollTop, scrollHeight, scrollWidth, deltaX, deltaY} |              |

代码演示

```html
<template>
	<view>
		<scroll-view scroll-x="true" >
			<view class="scroll-container">
				<view class="scroll-item">首页</view>
				<view class="scroll-item">Java</view>
				<view class="scroll-item">数据结构</view>
				<view class="scroll-item">Vue</view>
				<view class="scroll-item">PHP</view>
				<view class="scroll-item">C++</view>
				<view class="scroll-item">Golang</view>
				<view class="scroll-item">MySQL</view>
			</view>
		</scroll-view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			
		}
	}
</script>

<style>
.scroll-container {
	width: 750rpx;
	white-space: nowrap;
}

.scroll-item {
	display: inline-block;
	width: 150rpx;
	margin-right: 20rpx;
	background-color: #007AFF;
}
</style>

```

### 滑块视图（swiper）

一般用于左右滑动或上下滑动，比如banner轮播图。

> 注意：动切换和滚动的区别，滑动切换是一屏一屏的切换。swiper下的每个swiper-item是一个滑动切换区域，不能停留在2个滑动区域之间。(不存在中间态)

**swiper-item** 是swiper组件的子组件，只能用到swiper中，只有一个 `item-id` 属性，标识一个 swiper-item 的唯一性

| 属性名                 | 类型        | 默认值            | 说明                                                         | 平台差异说明                                                |
| :--------------------- | :---------- | :---------------- | :----------------------------------------------------------- | :---------------------------------------------------------- |
| indicator-dots         | Boolean     | false             | 是否显示面板指示点                                           |                                                             |
| indicator-color        | Color       | rgba(0, 0, 0, .3) | 指示点颜色                                                   |                                                             |
| indicator-active-color | Color       | #000000           | 当前选中的指示点颜色                                         |                                                             |
| active-class           | String      |                   | swiper-item 可见时的 class                                   | 支付宝小程序                                                |
| autoplay               | Boolean     | false             | 是否自动切换                                                 |                                                             |
| current                | Number      | 0                 | 当前所在滑块的 index                                         |                                                             |
| current-item-id        | String      |                   | 当前所在滑块的 item-id ，不能与 current 被同时指定           | 支付宝小程序不支持                                          |
| interval               | Number      | 5000              | 自动切换时间间隔                                             |                                                             |
| duration               | Number      | 500               | 滑动动画时长                                                 | app-nvue不支持                                              |
| circular               | Boolean     | false             | 是否采用衔接滑动，即播放到末尾后重新回到开头                 |                                                             |
| vertical               | Boolean     | false             | 滑动方向是否为纵向                                           |                                                             |
| previous-margin        | String      | 0px               | 前边距，可用于露出前一项的一小部分，接受 px 和 rpx 值        | app-nvue、字节跳动小程序不支持                              |
| next-margin            | String      | 0px               | 后边距，可用于露出后一项的一小部分，接受 px 和 rpx 值        | app-nvue、字节跳动小程序不支持                              |
| display-multiple-items | Number      | 1                 | 同时显示的滑块数量                                           | app-nvue、支付宝小程序不支持                                |
| @change                | EventHandle |                   | current 改变时会触发 change 事件，event.detail = {current: current, source: source} |                                                             |
| @transition            | EventHandle |                   | swiper-item 的位置发生改变时会触发 transition 事件，event.detail = {dx: dx, dy: dy}，支付宝小程序暂不支持dx, dy | App、H5、微信小程序、支付宝小程序、字节跳动小程序、QQ小程序 |
| @animationfinish       | EventHandle |                   | 动画结束时会触发 animationfinish 事件，event.detail = {current: current, source: source} | 字节跳动小程序不支持         



> 快捷键：uswi   +   回车


```html
<template>
	<view>
		<swiper :indicator-dots="true" :autoplay="true" :interval="3000" :duration="1000">
			<swiper-item>
				<view class="swiper-item1">1</view>
			</swiper-item>
			<swiper-item>
				<view class="swiper-item2">2</view>
			</swiper-item>
			<swiper-item>
				<view class="swiper-item3">3</view>
			</swiper-item>
		</swiper>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			
		}
	}
</script>

<style>
.swiper-item1 {
	background-color: #007AFF;
	height: 300rpx;
}
.swiper-item2 {
	background-color: #4CD964;
	height: 300rpx;
}
.swiper-item3 {
	background-color: #F0AD4E;
	height: 300rpx;
}
</style>

```

### 可拖动区域（movable）
#### movable-area

`movable-area` 指代可拖动的范围，在其中内嵌 `movable-view` 组件用于指示可拖动的区域。

即手指/鼠标按住 `movable-view` 拖动或双指缩放，但拖不出 `movable-area` 规定的范围。

| 属性名     | 类型    | 默认值 | 说明                                                         |
| :--------- | :------ | :----- | :----------------------------------------------------------- |
| scale-area | Boolean | false  | 当里面的 movable-view 设置为支持双指缩放时，设置此值可将缩放手势生效区域修改为整个 movable-area |

> movable-area 必须设置 width 和 height 属性，不设置默认为 10px
>
> movable-area app-nvue平台 暂不支持手势缩放，并且和滚动冲突。

#### movable-view

可移动的视图容器，在页面中可以拖拽滑动或双指缩放。

`movable-view`必须在`movable-area`组件中，并且必须是直接子节点，否则不能移动。

| 属性名        | 类型            | 默认值 | 说明                                                         | 平台差异说明                                  |
| :------------ | :-------------- | :----- | :----------------------------------------------------------- | :-------------------------------------------- |
| direction     | String          | none   | movable-view的移动方向，属性值有all、vertical、horizontal、none |                                               |
| inertia       | Boolean         | false  | movable-view是否带有惯性                                     | 微信小程序、支付宝小程序、App、H5、百度小程序 |
| out-of-bounds | Boolean         | false  | 超过可移动区域后，movable-view是否还可以移动                 | 微信小程序、支付宝小程序、App、H5、百度小程序 |
| x             | Number / String |        | 定义x轴方向的偏移，如果x的值不在可移动范围内，会自动移动到可移动范围；改变x的值会触发动画 |                                               |
| y             | Number / String |        | 定义y轴方向的偏移，如果y的值不在可移动范围内，会自动移动到可移动范围；改变y的值会触发动画 |                                               |
| damping       | Number          | 20     | 阻尼系数，用于控制x或y改变时的动画和过界回弹的动画，值越大移动越快 | 微信小程序、支付宝小程序、App、H5、百度小程序 |
| friction      | Number          | 2      | 摩擦系数，用于控制惯性滑动的动画，值越大摩擦力越大，滑动越快停止；必须大于0，否则会被设置成默认值 | 微信小程序、支付宝小程序、App、H5、百度小程序 |
| disabled      | Boolean         | false  | 是否禁用                                                     |                                               |
| scale         | Boolean         | false  | 是否支持双指缩放，默认缩放手势生效区域是在movable-view内     | 微信小程序、支付宝小程序、App、H5             |
| scale-min     | Number          | 0.5    | 定义缩放倍数最小值                                           | 微信小程序、支付宝小程序、App、H5             |
| scale-max     | Number          | 10     | 定义缩放倍数最大值                                           | 微信小程序、支付宝小程序、App、H5             |
| scale-value   | Number          | 1      | 定义缩放倍数，取值范围为 0.5 - 10                            | 微信小程序、支付宝小程序、App、H5             |
| animation     | Boolean         | true   | 是否使用动画                                                 | 微信小程序、支付宝小程序、App、H5、百度小程序 |
| @change       | EventHandle     |        | 拖动过程中触发的事件，event.detail = {x: x, y: y,  source:  source}，其中source表示产生移动的原因，值可为touch（拖动）、touch-out-of-bounds（超出移动范围）、out-of-bounds（超出移动范围后的回弹）、friction（惯性）和空字符串（setData） |                                               |
| @scale        | EventHandle     |        | 缩放过程中触发的事件，event.detail = {x: x, y: y, scale: scale}， | 微信小程序、App、H5、百度小程序               |

> movable-view 必须设置width和height属性，不设置默认为10px
>
> movable-view 默认为绝对定位，top和left属性为0px
>
> 当movable-view小于movable-area时，movable-view的移动范围是在movable-area内；当movable-view大于movable-area时，movable-view的移动范围必须包含movable-area（x轴方向和y轴方向分开考虑）

代码演示

```html
<template>
	<view>
		<movable-area class="movable-area">
			<movable-view direction="all" inertia="true" class="movable-view" scale="true">
				拖我
			</movable-view>
		</movable-area>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			
		}
	}
</script>

<style>
.movable-area {
	width: 750rpx;
	height: 400rpx;
	background-color: #007AFF;
}
.movable-view {
	width: 200rpx;
	height: 200rpx;
	background-color: #4CD964;
}
</style>

```
# 基础内容
[官方文档](https://uniapp.dcloud.io/component/icon)
### 图标（icon）

| 属性名 | 类型   | 默认值 | 说明                     |
| ------ | ------ | ------ | ------------------------ |
| type   | String |        | icon的类型               |
| size   | Number | 23     | icon的大小，单位px       |
| color  | Color  |        | icon的颜色，同css的color |



代码演示

```html
<template>
	<view>
		<view v-for="item in icons" :key="item">
			<icon :type="item"></icon>
			<text>{{item}}</text>
		</view>
		<view class="">
			以下是iconfont
		</view>
		<text class="icon success">&#xe600;</text>
		<text class="icon info">&#xe60f;</text>
		<text class="icon warning">&#xe658;</text>
		<text class="icon danger">&#xe6e6;</text>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				icons: [
					"success", "success_no_circle", "info", "warn", "waiting", "cancel", "download", "search", "clear"
				]
			}
		},
		methods: {

		}
	}
</script>

<style>
/* 以下配置最好在App.vue中设置 */
@font-face {
      font-family: 'iconfont';  /* project id 2032489 */
      src: url('https://at.alicdn.com/t/font_2032489_e9daxwhbrpi.eot');
      src: url('https://at.alicdn.com/t/font_2032489_e9daxwhbrpi.eot?#iefix') format('embedded-opentype'),
      url('https://at.alicdn.com/t/font_2032489_e9daxwhbrpi.woff2') format('woff2'),
      url('https://at.alicdn.com/t/font_2032489_e9daxwhbrpi.woff') format('woff'),
      url('https://at.alicdn.com/t/font_2032489_e9daxwhbrpi.ttf') format('truetype'),
      url('https://at.alicdn.com/t/font_2032489_e9daxwhbrpi.svg#iconfont') format('svg');
 }

.icon {
    font-family: iconfont;
    margin-left: 20rpx;
}
.success {
	color: #4CD964;
}
.info {
	color: #999999;
}
.warning {
	color: #F0AD4E;
}

.danger {
	color: #DD524D;
}
</style>

```

### 使用iconfont

`uni-app` 支持使用字体图标，使用方式与普通 `web` 项目相同，需要注意以下几点：

- 支持 base64 格式字体图标。

- 支持网络路径字体图标。

- 小程序不支持在css中使用本地文件，包括本地的背景图和字体文件。需以base64方式方可使用。App端在v3模式以前，也有相同限制。v3编译模式起支持直接使用本地背景图和字体。

- 网络路径必须加协议头 `https`。

- 从 http://www.iconfont.cn 上拷贝的代码，默认是没加协议头的。 

- 从 http://www.iconfont.cn 上下载的字体文件，都是同名字体（字体名都叫iconfont，安装字体文件时可以看到），在nvue内使用时需要注意，此字体名重复可能会显示不正常，可以使用工具修改。

- 使用本地路径图标字体需注意：

  1. 为方便开发者，在字体文件小于 40kb 时，`uni-app` 会自动将其转化为 base64 格式；
  2. 字体文件大于等于 40kb，仍转换为 base64 方式使用的话可能有性能问题，如开发者必须使用，则需自己将其转换为 base64 格式使用，或将其挪到服务器上，从网络地址引用；

- 字体文件的引用路径推荐使用以 ~@ 开头的绝对路径。

  ```css
  @font-face {
       font-family: 'iconfont';
       src: url('https://...') format('truetype');
   }
  
  .icon {
      font-family: iconfont;
      margin-left: 20rpx;
  }
  
  <text class="icon">&#xe600;</text>
  ```

`nvue`中不可直接使用css的方式引入字体文件，需要使用以下方式在js内引入。nvue内不支持本地路径引入字体，请使用网络链接或者`base64`形式。**`src`字段的`url`的括号内一定要使用单引号。**

```js
var domModule = weex.requireModule('dom');
domModule.addRule('fontFace', {
  'fontFamily': "iconfont",
  'src': "url('https://...')"
})
```

### 文本组件（text）

用于包裹文本。

| 属性名     | 类型    | 默认值 | 说明         | 平台差异说明 |
| :--------- | :------ | :----- | :----------- | :----------- |
| selectable | Boolean | false  | 文本是否可选 |              |

> - `<text>` 组件内只支持嵌套 `<text>`，不支持其它组件或自定义组件，否则会引发在不同平台的渲染差异。
> - 在app-nvue下，只有`<text>`才能包裹文本内容。无法在`<view>`组件包裹文本。
> - 除了文本节点以外的其他节点都无法长按选中。
> - 支持 `\n` 方式换行。
> - 如果使用 `<span>` 组件编译时会被转换为 `<text>`。

# 地图
[官方文档](https://uniapp.dcloud.io/component/map)

| 属性名             | 类型              | 默认值 | 说明                                                  | 平台差异说明                                              |
| :----------------- | :---------------- | :----- | :---------------------------------------------------- | :-------------------------------------------------------- |
| longitude          | Number            |        | 中心经度                                              |                                                           |
| latitude           | Number            |        | 中心纬度                                              |                                                           |
| scale              | Number            | 16     | 缩放级别，取值范围为5-18                              |                                                           |
| markers            | Array             |        | 标记点                                                |                                                           |
| polyline           | Array             |        | 路线                                                  |                                                           |
| circles            | Array             |        | 圆                                                    |                                                           |
| controls           | Array             |        | 控件                                                  |                                                           |
| include-points     | Array             |        | 缩放视野以包含所有给定的坐标点                        | App-nvue 2.1.5+、微信小程序、H5、百度小程序、支付宝小程序 |
| enable-3D          | Boolean           | false  | 是否显示3D楼块                                        | App-nvue 2.1.5+、微信小程序2.3.0                          |
| show-compass       | Boolean           | false  | 是否显示指南针                                        | App-nvue 2.1.5+、微信小程序2.3.0                          |
| enable-overlooking | Boolean           | false  | 是否开启俯视                                          | App-nvue 2.1.5+、微信小程序2.3.0                          |
| enable-satellite   | Boolean           | false  | 是否开启卫星图                                        | App-nvue 2.1.5+、微信小程序2.7.0                          |
| enable-traffic     | Boolean           | false  | 是否开启实时路况                                      | App-nvue 2.1.5+、微信小程序2.7.0                          |
| show-location      | Boolean           |        | 显示带有方向的当前定位点                              | 微信小程序、H5、百度小程序、支付宝小程序                  |
| polygons           | Array.`<polygon>` |        | 多边形                                                | App-nvue 2.1.5+、微信小程序、百度小程序、支付宝小程序     |
| @markertap         | EventHandle       |        | 点击标记点时触发，e.detail = {markerId}               | App-nvue 2.3.3+, App平台需要指定 marker 对象属性 id       |
| @labeltap          | EventHandle       |        | 点击label时触发，e.detail = {markerId}                | 微信小程序2.9.0                                           |
| @callouttap        | EventHandle       |        | 点击标记点对应的气泡时触发，e.detail = {markerId}     |                                                           |
| @controltap        | EventHandle       |        | 点击控件时触发，e.detail = {controlId}                |                                                           |
| @regionchange      | EventHandle       |        | 视野发生变化时触发                                    | 微信小程序、H5、百度小程序、支付宝小程序                  |
| @tap               | EventHandle       |        | 点击地图时触发; App-nuve、微信小程序2.9支持返回经纬度 |                                                           |
| @updated           | EventHandle       |        | 在地图渲染更新完成时触发                              | 微信小程序、H5、百度小程序                                |



地图组件的经纬度必填，如果不填经纬度则默认值是北京的经纬度。

> 小程序和app-vue中，map组件是由引擎创建的原生组件，级别最高，无法使用z-index设置层级。如果想有在map上显式的元素，可以使用marker、controls设置，也可以使用 `cover-view` 组件
>
> APP端地图组件使用的时候需要上高德或者百度等三方服务商申请地图SDK资质，获取AppKey，打包时在mainfest勾选相应的模块，填写AppKey。

代码演示

```html
<template>
	<view>
		<map :polyline="polyline" :markers="markers" class="mymap" :latitude="39.56" :longitude="117.30"></map>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				markers: [ // 标记点
					{
						id: 1,
						latitude: 39.56,
						longitude: 117.30
					},
					{
						id: 2,
						latitude: 40.56,
						longitude: 118.30
					},
					{
						id: 3,
						latitude: 39.86,
						longitude: 119.30
					}
				],
				polyline: [ // 路线，每条线是一个对象里包含一个坐标点数组，地图中可以有多条线
					{
						color: "#a55310",
						points: [
							{
								latitude: 39.56,
								longitude: 117.30
							},
							{
								latitude: 40.56,
								longitude: 118.30
							},
							{
								latitude: 39.86,
								longitude: 119.30
							}
						]
					},
					{
						color: "#3b64a5",
						points: [
							{
								latitude: 42.56,
								longitude: 127.30
							},
							{
								latitude: 42.56,
								longitude: 128.30
							},
							{
								latitude: 42.86,
								longitude: 129.30
							}
						]
					}
				]
			}
		},
		methods: {
			
		}
	}
</script>

<style>
.mymap {
	width: 750rpx;
}
</style>

```



# 小程序开放能力
[官方文档参考](https://uniapp.dcloud.io/component/official-account)

# AppNvue专用组件

## 扫码组件（Barcode）

app-nvue专用的扫码组件，其他端请使用扫码API `uni.scanCode`

| 属性         | 类型          | 默认值  | 必填 | 说明                                                         |
| :----------- | :------------ | :------ | :--- | :----------------------------------------------------------- |
| autostart    | boolean       | false   | 否   | 是否自动开始扫码                                             |
| background   | string        |         | 否   | 条码识别控件背景颜色,颜色值支持(参考CSS颜色规范)：颜色名称(参考CSS Color Names)/十六进制值/rgb值，默认值为黑色。 |
| frameColor   | string        |         | 否   | 扫码框颜色,颜色值支持(参考CSS颜色规范)：颜色名称(参考CSS Color Names)/十六进制值/rgb值/rgba值，默认值为红色。 |
| scanbarColor | string        |         | 否   | 扫码条颜色,颜色值支持(参考CSS颜色规范)：颜色名称(参考CSS Color Names)/十六进制值/rgb值/rgba值，默认值为红色。 |
| filters      | Array[Number] | [0,1,2] | 否   | 条码类型过滤器，条码类型常量数组，默认情况支持QR、EAN13、EAN8类型。 通过此参数可设置扫码识别支持的条码类型（注意：设置支持的条码类型越多，扫描识别速度可能将会降低）。 |

## 组件方法

以下方法是组件内部的方法，需要通过 `this.$refs` 去调用

##### 开始扫码——start(object)

| 属性     | 说明                       | 类型    | 必填 | 备注                                                         |
| :------- | :------------------------- | :------ | :--- | :----------------------------------------------------------- |
| conserve | 是否保存扫码成功时的截图   | Boolean | 否   | 如果设置为true则在扫码成功时将图片保存，并通过onmarked回调函数的file参数返回保存文件的路径。 默认值为false，不保存截图。 |
| filename | 保存扫码成功时图片保存路径 | String  | 否   | 可通过此参数设置保存截图的路径和名称，如果设置图片文件名称则必须指定文件的后缀名（必须是.png），否则认为是指定目录，文件名称则自动生成。 |
| vibrate  | 扫码成功时是否需要震动提醒 | Boolean | 否   | 如果设置为true则在扫码成功时震动设备，false则不震动。 默认值为true。 |
| sound    | 扫码成功时播放的提示音     | String  | 否   | 可取值： "none" - 不播放提示音； "default" - 播放默认提示音（5+引擎内置）。 默认值为"default"。 |

##### 取消扫码——cancel()

字面意思

##### 操作闪光灯——setFlash(boolean)

| 类型    | 必填 | 说明           | 备注                                                         |
| :------ | :--- | :------------- | :----------------------------------------------------------- |
| Boolean | 是   | 是否开启闪光灯 | 可取值true或false，true表示打开闪光灯，false表示关闭闪光灯。 |

#### 组件事件

##### 识别成功——marked(e)

| 参数    | 类型   | 说明                                                         |
| :------ | :----- | :----------------------------------------------------------- |
| type    | string | "success" 表示成功                                           |
| message | string | 识别到的条码数据，扫码识别出的数据内容，字符串类型，采用UTF8编码格式。 |
| code    | Number | 识别到的条码类型，与Barcode组件的条码类型常量一致。          |
| file    | string | 扫码成功的截图文件路径，扫码识别到的截图，png格式文件，如果设置为不保存截图，则返回undefined。 |

##### 识别错误——error(e)

| 参数    | 类型   | 说明            |
| :------ | :----- | :-------------- |
| type    | string | "fail" 表示失败 |
| code    | number | 相应 code 码    |
| message | string | 失败描述        |

代码演示

```html
<template>
	<view>
		<barcode autostart="true" class="barcode" ref="barcode" @marked="success" @error="error"></barcode>
		<button type="default" @click="barcode">点我扫码</button>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			success(e) {
				console.log("扫码成功", e)
				this.$refs.barcode.cancel()
			},
			error(e) {
				console.log("扫码失败", e)
				this.$refs.barcode.cancel()
			},
			barcode() {
				this.$refs.barcode.start({
					vibrate: true,
					sound: true
				})
			}
		}
	}
</script>

<style>
.barcode {
	width: 750rpx;
	height: 500rpx;
}
</style>

```


