**写在前面**：分享技术，共同进步，有不足请见谅，相关意见可评论告知  ~
> 编程路漫漫，学习无止尽！

@[toc]
# EL
**概念**：Expression Language 表达式语言
 作用：替换和简化jsp页面中java代码的编写
语法：`${表达式}`
==注意==：
jsp默认支持el表达式的。如果要忽略el表达式
		1. 设置jsp中page指令中：`isELIgnored="true"` 忽略当前jsp页面中所有的el表达式
		2. `\${表达式}` ：忽略当前这个el表达式


## 运算符：
			1. 算数运算符： + - * /(div) %(mod)             
			2. 比较运算符： > < >= <= == !=
			3. 逻辑运算符： &&(and) ||(or) !(not)
			4. 空运算符： empty

> 注意： empty用于判断字符串、集合、数组对象是否为null或者长度是否为0 ${empty
> list}:判断字符串、集合、数组对象是否为null或者长度为0 ${not empty
> str}:表示判断字符串、集合、数组对象是否不为null 并且 长度>0

## 获取值
el表达式只能从域对象中获取值
语法： `${域名称.键名}：`从指定域中获取指定键的值
域名称：(域的范围依次递增)
					1. pageScope		--> pageContext
					2. requestScope 	--> request
					3. sessionScope 	--> session
					4. applicationScope --> application（ServletContext）

${键名}：表示依次从最小的域中查找是否有该键对应的值，直到找到为止。


## 获取对象、List集合、Map集合的值
1. **对象**：`${域名称.键名.属性名}` ，本质上会去调用对象的getter方法
获取对象的属性
setter或getter方法，去掉set或get，在将剩余部分，首字母变为小写。
eg：setName --> Name --> name

2. **List集合**：${域名称.键名[索引]}

3. **Map集合**：
${域名称.键名.key名称}
${域名称.键名["key名称"]}

> List集合是存储单列数据bai的集合,且数据是有顺序的，允许重复
> Map是存储键和值这样的双列数的集合，没有顺序的，其键是不能重复的，但其值可重复

## 隐式对象：
 el表达式中有11个隐式对象
pageContext：获取jsp其他八个内置对象
 `${pageContext.request.contextPath}：`动态获取虚拟目录

# JSTL
1. **概念**：JavaServer Pages Tag Library  JSP标准标签库，实质为开源的免费的jsp标签		<标签>   用于简化和替换jsp页面上的java代码		

## 使用
	1. 导入jstl相关jar包
	2. 引入标签库：taglib指令：  <%@ taglib %>
	3. 使用标签
**JSTL标签库使用步骤**

引入对应的 taglib
使用其中的方法
**在Tomcat 也需要引入 jstl的包，否则会报错：JSTL解析错误**
## 常用的JSTL标签
预备工作：

```java
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020080214520450.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

==一、== if:相当于java代码的if语句
属性： test 必须属性，接受boolean表达式
如果表达式为true，则显示if标签体内容，如果为false，则不显示标签体内容
test属性值常会结合el表达式一起使用

```java
<c:if test ="${not empty list}" >
遍历集合
</c:if>
```

>  注意： c:if标签没有else情况，想要else情况，则可以在定义一个c:if标签

==二==、choose:相当于java代码的switch语句
        1. 使用choose标签声明         			相当于switch声明
        2. 使用when标签做判断         			相当于case
        3. 使用otherwise标签做其他情况的声明    	相当于defaul
```java
    <c:choose>
        <c:when test="${number == 1}">星期一</c:when>
        <c:when test="${number == 2}">星期二</c:when>
        <c:when test="${number == 3}">星期三</c:when>
        <c:when test="${number == 4}">星期四</c:when>
        <c:when test="${number == 5}">星期五</c:when>
        <c:when test="${number == 6}">星期六</c:when>
        <c:when test="${number == 7}">星期天</c:when>

        <c:otherwise>数字输入有误</c:otherwise>
    </c:choose>
```

         

==三、== foreach:相当于java代码的for语句
1.常规
属性：   **begin**：开始值 ，  **end**：结束值，   **var**：临时变量，     **step**：步长
    **varStatus**:循环状态对象 ，  **index**:容器中元素的索引，从0开始     ，   **count**：循环次数，从1开始      

```java
<c:forEach begin="1" end="10" var="i" step="2" varStatus="s">
    ${i} <h3>${s.index}<h3> <h4> ${s.count} </h4><br>

</c:forEach>
```
              
2. 遍历容器
属性： **items**:容器对象，**var**:容器中元素的临时变量，  **varStatus**:循环状态对象， **index**:容器中元素的索引，从0开始  ，  **count**:循环次数，从1开始             
 

```java
 <c:forEach items="${list}" var="str" varStatus="s">

            ${s.index} ${s.count} ${str}<br>

    </c:forEach>
```

> 基于实战中学习，学习快乐中成长
>                                                 .
> 时间会回答成长，成长会回答梦想
              
                   
          






