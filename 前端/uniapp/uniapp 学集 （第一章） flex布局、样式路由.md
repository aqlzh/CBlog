**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 有道无术，术尚可求；
> 有术无道，终止于术!
> 
> 多端运行，架式简化；
> 编程路漫，学无止尽！

@[toc]
[官方参考文档](https://uniapp.dcloud.io/)
# flex  布局回顾
## 引言
uniapp支持 `.vue` 和 `.nvue` 两种后缀类型的代码文件。使用 vue 时，页面 **使用WebView渲染**，而使用 nvue 时，页面 **采用原生渲染**。nvue支持的css样式特别少，其中在布局上，nvue **仅支持flex布局**

## 基本概念

意为“弹性布局”，任何一个容器都可以指定为flex布局。


容器默认存在两根轴，==主轴==和==交叉轴==。主轴的开始位置叫做 `main start`，结束位置叫做 `main end`。交叉轴的开始位置叫做 `cross start` ，结束位置叫做 `cross end` 

Flex布局允许嵌套，即一个元素既可以是Flex容器，也可以是Flex项目 。

![image-20200814235245475](https://img-blog.csdnimg.cn/img_convert/5452727350207c175252c66db7d04f4f.png)



## 容器的属性

以下6个属性设置在容器上

- flex-direction
- flex-wrap
- flex-flow
- justify-content
- align-items
- align-content

### flex-direction

`flex-direction` 属性决定了主轴的方向

```css
.box {
    flex-direction: row | row-reverse | column | column-reverse
}
```

> * row（默认值）：主轴为水平方向，起点在左端
> * row-reverse：主轴视为水平方向，起点在右端
> * column：主轴为垂直方向，起点在上沿
> * column-reverse：主轴为垂直方向，起点在下沿

reverse   译为翻转

![image-20200814235318124](https://img-blog.csdnimg.cn/img_convert/3ea302fa21f3330f890b212fbcd8c19f.png)


### flex-wrap

默认情况下，项目都排在一条轴线上。`flex-wrap` 定义如果一条轴线排不下，换行。

```css
.box {
    flex-wrap: nowrap | wrap | wrap-reverse
}
```

> nowrap（默认）：不换行
>
> wrap：换行，第一行在上方
>
> wrap-reverse：换行，第一行在下方

### flex-flow

`flex-flow` 属性是 `flex-direction` 和 `flex-wrap` 属性的简写，默认为 `row nowrap`

```css
.box {
    flex-flow: <flex-direction> <flex-wrap>
}
```

### justify-content（重要）

`justify-content` 属性定义了项目在主轴上的对齐方式

```css
.box {
  justify-content: flex-start | flex-end | center | space-between | space-around;
}
```

> - `flex-start`（默认值）：左对齐
> - `flex-end`：右对齐
> - `center`： 居中
> - `space-between`：两端对齐，项目之间的间隔都相等。
> - `space-around`：每个项目两侧的间隔相等。所以，项目之间的间隔比项目与边框的间隔大一倍。

![image-20200815000424615](https://img-blog.csdnimg.cn/img_convert/006c5620f7d622a5ca53c52e1226d4f5.png)

### align-items  （不常用）

`align-items`属性定义项目在交叉轴上如何对齐。

```css
.box {
   align-items: flex-start | flex-end | center | baseline | stretch;
}
```

> - `flex-start`：交叉轴的起点对齐。
> - `flex-end`：交叉轴的终点对齐。
> - `center`：交叉轴的中点对齐。
> - `baseline`: 项目的第一行文字的基线对齐。
> - `stretch`（默认值）：如果项目未设置高度或设为auto，将占满整个容器的高度。

![image-20200815000545460](https://img-blog.csdnimg.cn/img_convert/8b697bed59c651ea784ca352919648ab.png)

### align-content

`align-content`属性定义了多根轴线的对齐方式。如果项目只有一根轴线，该属性不起作用。

```css
.box {
  align-content: flex-start | flex-end | center | space-between | space-around | stretch;
}
```

> - `flex-start`：与交叉轴的起点对齐。
> - `flex-end`：与交叉轴的终点对齐。
> - `center`：与交叉轴的中点对齐。
> - `space-between`：与交叉轴两端对齐，轴线之间的间隔平均分布。
> - `space-around`：每根轴线两侧的间隔都相等。所以，轴线之间的间隔比轴线与边框的间隔大一倍。
> - `stretch`（默认值）：轴线占满整个交叉轴。


### align-items

`align-items`属性定义项目在交叉轴上如何对齐。

```css
.box {
   align-items: flex-start | flex-end | center | baseline | stretch;
}
```

> - `flex-start`：交叉轴的起点对齐。
> - `flex-end`：交叉轴的终点对齐。
> - `center`：交叉轴的中点对齐。
> - `baseline`: 项目的第一行文字的基线对齐。
> - `stretch`（默认值）：如果项目未设置高度或设为auto，将占满整个容器的高度。

![image-20200815000545460](https://img-blog.csdnimg.cn/img_convert/8b697bed59c651ea784ca352919648ab.png)

### align-content

`align-content`属性定义了多根轴线的对齐方式。如果项目只有一根轴线，该属性不起作用。

```css
.box {
  align-content: flex-start | flex-end | center | space-between | space-around | stretch;
}
```

> - `flex-start`：与交叉轴的起点对齐。
> - `flex-end`：与交叉轴的终点对齐。
> - `center`：与交叉轴的中点对齐。
> - `space-between`：与交叉轴两端对齐，轴线之间的间隔平均分布。
> - `space-around`：每根轴线两侧的间隔都相等。所以，轴线之间的间隔比轴线与边框的间隔大一倍。
> - `stretch`（默认值）：轴线占满整个交叉轴。

#  样式与路由
## 尺寸单位

uniapp支持 `px` 和 `rpx` 两种通用的尺寸单位

px：屏幕像素，web开发最常见的单位

rpx：响应式px。一种根据屏幕宽度自适应的动态单位，以750rpx为基准，750rpx刚好是100%宽度。

**nvue中不支持 rem、vh、vw、百分比这几种尺寸单位，因此在开发中极不建议使用这几种单位**

## 选择器

| 选择器           | 样例           | 样例描述                                            |
| :--------------- | :------------- | :-------------------------------------------------- |
| .class           | .intro         | 选择所有拥有 class="intro" 的组件                   |
| #id              | #firstname     | 选择拥有 id="firstname" 的组件                      |
| element          | view           | 选择所有 view 组件                                  |
| element, element | view, checkbox | 选择所有文档的 view 组件和所有的 checkbox 组件      |
| ::after          | view::after    | 在 view 组件后边插入内容，**仅微信小程序和App生效** |
| ::before         | view::before   | 在 view 组件前边插入内容，**仅微信小程序和App生效** |

> uniapp中不能使用 `*` 选择器
>
> uniapp中 `page`  就相当于 `body`
>
> nvue 中只支持 class 选择器，因此开发中应当尽可能只使用class选择器

## 路由

uniapp 路由通过框架去统一管理，只需要在 `pages.json` 中配置每个路由页面的路径以及页面的样式。路由的管理方式与 `VueRouter` 不同，如果习惯VueRouter的风格，可以去插件市场搜索。

```vue
	"pages": [ //pages数组中第一项表示应用启动页，参考：https://uniapp.dcloud.io/collocation/pages
		{
			"path": "pages/index/index",
			"style": {
				"navigationBarTitleText": "uni-app"
			}
		}
	    ,{
            "path" : "pages/test/test",
            "style" : {}
        }
    ],
```


