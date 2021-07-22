@[toc]
# 运行时 Console 消失
解法：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210312142543661.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
 # Debug
 右键
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210312142623567.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
[Debug  操作参考链接](https://blog.csdn.net/QuantumYou/article/details/114482862?spm=1001.2014.3001.5502)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210312142717571.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
- `Resume(F8)`   跳至下一个断点  
- `Terminate（CTRL+ F2）`  结束断点
- `Step Into (F5)`  等待断点的过程中  ==进入方法==
- `Step Return （F7）` 从方法中==跳出==
- `Step Over (F6)`  执行下一行可执行代码


# 运行的不是预期程序

因为你运行的Java  程序不止一层
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210312142910281.png)
需要在 `主函数`下才能操作

# Eclipse 报错延迟解决
需要  `Ctrl + S`    保存下


