写在前面：分享技术，共同进步，把笔记搬运至博客，有不足请见谅，相关意见可评论告知  
> 编程路漫漫，学习无止尽！

@[toc]
# Bootstrap
. **概念：** 一个前端开发的框架，Bootstrap，来自 Twitter，是目前很受欢迎的前端框架。Bootstrap 是基于 HTML、CSS、JavaScript 的，它简洁灵活，使得 Web 开发更加快捷。
 **框架** 一个半成品软件，开发人员可以在框架基础上，在进行开发，简化编码。
==好处==
		1. 定义了很多的css样式和js插件。我们开发人员直接可以使用这些样式和插件得到丰富的页面效果。
		2. 响应式布局。


##  响应式布局
* 同一套页面可以兼容不同分辨率的设备。
* 实现：依赖于**栅格系统**：将一行平均分成12个格子，可以指定元素占几个格子
* 栅格系统介绍栅格系统

> https://v3.bootcss.com/css/#grid

* 步骤：
	1. 定义容器。相当于之前的table、
		* 容器分类：
			1. container：两边留白
			2. container-fluid：每一种设备都是100%宽度
	2. 定义行。相当于之前的tr   样式：row
	3. 定义元素。指定该元素在不同的设备上，所占的格子数目。样式：col-设备代号-格子数目
		* 设备代号：
			1. xs：超小屏幕 手机 (<768px)：col-xs-12
			2. sm：小屏幕 平板 (≥768px)
			3. md：中等屏幕 桌面显示器 (≥992px)
			4. lg：大屏幕 大桌面显示器 (≥1200px)

> 
> 		1. 一行中如果格子数目超过12，则超出部分自动换行。
> 		2. 栅格类属性可以向上兼容。栅格类适用于与屏幕宽度大于或等于分界点大小的设备。
> 		3. 如果真实设备宽度小于了设置栅格类属性的设备代码的最小值，会一个元素沾满一整行。


# XML
**概念**：Extensible Markup Language 可扩展标记语言,可扩展：标签都是自定义的。 <user>  <student>
==**功能**== 存储数据,配置文件, 在网络中传输

	 xml与html的区别
		1. xml标签都是自定义的，html标签是预定义。
		2. xml的语法严格，html语法松散
		3. xml是存储数据的，html是展示数据

2. 语法：
	* 基本语法：
		1. xml文档的后缀名 .xml
		2. xml第一行必须定义为文档声明
		3. xml文档中有且仅有一个根标签
		4. 属性值必须使用引号(单双都可)引起来
		5. 标签必须正确关闭
		6. xml标签名称区分大小写

		
	## 组成部分：
		1. 文档声明
			1. 格式：<?xml 属性列表 ?>
			2. 属性列表：
				* version：版本号，必须的属性
				* encoding：编码方式。告知解析引擎当前文档使用的字符集，默认值：ISO-8859-1
				* standalone：是否独立
					* 取值：
						* yes：不依赖其他文件
						* no：依赖其他文件
		2. 指令(了解)：结合css的
			* <?xml-stylesheet type="text/css" href="a.css" ?>
		3. 标签：标签名称自定义的
			* 规则：
				* 名称可以包含字母、数字以及其他的字符 
				* 名称不能以数字或者标点符号开始 
				* 名称不能以字母 xml（或者 XML、Xml 等等）开始 
				* 名称不能包含空格 

		4. 属性：
			id属性值唯一
		5. 文本：
			* CDATA区：在该区域中的数据会被原样展示
				* 格式：  <![CDATA[ 数据 ]]>

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020072223572696.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## xml语法
**约束**：规定xml文档的书写规则
作为框架的使用者(程序员)， 能够在xml中引入约束文档，能够简单的读懂约束文档
				**分类**
			1. ==DTD:一种简单的约束技术==
				内部dtd：将约束规则定义在xml文档中
				外部dtd：将约束的规则定义在外部的dtd文件中
				本地：`<!DOCTYPE 根标签名 SYSTEM "dtd文件的位置">`
			  网络：`<!DOCTYPE 根标签名 PUBLIC "dtd文件名字" "dtd文件的位置URL">`
			2  ==Schema:一种复杂的约束技术==
				1.填写xml文档的根元素
				2.引入xsi前缀.  `xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"`
				3.引入xsd文件命名空间.  `xsi:schemaLocation="http://www.it.cn/xml  student.xsd"`
				4.为每一个xsd约束声明一个前缀,作为标识  `xmlns="http://www.it.cn/xml"` 

			<students   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
				xmlns="http://www.it.cn/xml"
				xsi:schemaLocation="http://www.it.cn/xml  student.xsd">

## xml解析
操作xml文档，将文档中的数据读取到内存中
		1. **解析(读取)**：将文档中的数据读取到内存中
		2. **写入**：将内存中的数据保存到xml文档中。持久化的存储

	* 解析xml的方式：
		1. DOM：将标记语言文档一次性加载进内存，在内存中形成一颗dom树   (服务器端)
			* 优点：操作方便，可以对文档进行CRUD的所有操作
			* 缺点：占内存
		2. SAX：逐行读取，基于事件驱动的。      （移动端）
			* 优点：不占内存。
			* 缺点：只能读取，不能增删改
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200723002319539.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

###  xml常见的解析器：
     	1. JAXP：sun公司提供的解析器，支持dom和sax两种思想  （不用）
		2. DOM4J：一款非常优秀的解析器
		3. Jsoup：jsoup 是一款Java 的HTML解析器，可直接解析某个URL地址、HTML文本内容。它提供了一套非常省力的API，可通过DOM，CSS以及类似于jQuery的操作方法来取出和操作数据。
		4. PULL：Android操作系统内置的解析器，sax方式的。

	

#### Jsoup

	使用步骤：
				1. 导入jar包
				2. 获取Document对象
				3. 获取对应的标签Element对象
				4. 获取数据
——————————————————————————————————————
	 对象的使用：
		1. Jsoup：工具类，可以解析html或xml文档，返回Document 			
		2. parse：解析html或xml文档，返回Document
     				 `parse​(File in, String charsetName`)，解析xml或html文件的。    //*   ==（常用）==
				`parse​(String html)：`解析xml或html字符串
				 `parse​(URL url, int timeoutMillis)：`通过网络路径获取指定的html或xml的文档对象
		3. Document：文档对象。代表内存中的dom树 			* 获取Element对象
				`getElementById​(String id)：`根据id属性值获取唯一的element对象
				`getElementsByTag​(String tagName)`：根据标签名称获取元素对象集合
				`getElementsByAttribute​(String key)：`根据属性名称获取元素对象集合
				`getElementsByAttributeValue​(String key, String value)：`根据对应的属性名和属性值获取元素对象集合
		4. Elements：元素Element对象的集合。可以当做 ArrayList<Element>来使用
		5. Element：元素对象
			1. **获取子元素对象**
				`getElementById​(String id)：`根据id属性值获取唯一的element对象
				`getElementsByTag​(String tagName)：`根据标签名称获取元素对象集合
				`getElementsByAttribute​(String key)`：根据属性名称获取元素对象集合
				`getElementsByAttributeValue​(String key, String value)`：根据对应的属性名和属性值获取元素对象集合

`
			2. **获取属性值**
				String attr(String key)：根据属性名称获取属性值
			3. **获取文本内容**
				String text():获取文本内容
				String html():获取标签体的所有内容(包括字标签的字符串内容)
		6. Node：节点对象 			* 是Document和Element的父类


//*   示意图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200723151733321.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
—

##### 快捷查询方式

		1. **selector:选择器**
			 使用的方法：Elements	select​(String cssQuery)
			语法：参考Selector类中定义的语法   (与css选择器语法相似)
		2. **XPath**：XPath即为XML路径语言，它是一种用确定XML（标准通用标记语言的子集）文档中某部分位置的语言
			使用Jsoup的Xpath需要额外导入jar包。
	
		

> https://www.runoob.com/xpath/xpath-syntax.html

		

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200723223148508.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

