写在前面：分享技术，共同进步，把笔记搬运至博客，有不足请见谅，相关意见可评论告知 （。＾▽＾）
> 编程路漫漫，学习无止尽！
> 
@[toc]
# 概述
## 并发与并行

* **并发**：指两个或多个事件在**同一个时间段内**发生。
* **并行**：指两个或多个事件在**同一时刻**发生（同时发生）。


> 拓展：单核处理器的计算机肯定是不能并行的处理多个任务的，只能是多个任务在单个CPU上并发运行。同理,线程也是一样的，从宏观角度上理解线程是并行运行的，但是从微观角度上分析却是串行运行的，即一个线程一个线程的去运行，当系统只有一个CPU时，线程会以某种顺序执行多个线程，我们把这种情况称之为线程调度。

##  线程与进程
* **进程**：是指一个内存中运行的应用程序，每个进程都有一个独立的内存空间，一个应用程序可以同时运行多个进程；进程也是程序的一次执行过程，是**系统运行程序的基本单位**；系统运行一个程序即是一个进程从创建、运行到消亡的过程。

* **线程**：**线程是进程中的一个执行单元**，负责当前进程中程序的执行，一个进程中至少有一个线程。一个进程中是可以有多个线程的，这个应用程序也可以称之为多线程程序。 
       *程序、线程、进程*
  ==简而言之==：一个程序运行后至少有一个进程，一个进程中可以包含多个线程 


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715223422847.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
# Process Thread
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715223631766.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 创建线程类

Java使用`java.lang.Thread`类代表**线程**，所有的线程对象都必须是Thread类或其子类的实例。每个线程的作用是完成一定的任务，实际上就是执行一段程序流即一段顺序执行的代码。Java使用线程执行体来代表这段程序流。Java中通过继承Thread类来**创建**并**启动多线程**的步骤如下：

1. 定义Thread类的子类，并重写该类的run()方法，该run()方法的方法体就代表了线程需要完成的任务,因此把run()方法称为线程执行体。
2. 创建Thread子类的实例，即创建了线程对象
3. 调用线程对象的start()方法来启动该线程

测试类
```java
public class Demo01 {
	public static void main(String[] args) {
		//创建自定义线程对象
		MyThread mt = new MyThread("新的线程！");
		//开启新线程
		mt.start();
		//在主方法中执行for循环
		for (int i = 0; i < 10; i++) {
			System.out.println("main线程！"+i);
		}
	}
}
```
自定义实现类
```java
public class MyThread extends Thread {
	//定义指定线程名称的构造方法
	public MyThread(String name) {
		//调用父类的String参数的构造方法，指定线程的名称
		super(name);
	}
	/**
	 * 重写run方法，完成该线程执行的逻辑
	 */
	@Override
	public void run() {
		for (int i = 0; i < 10; i++) {
			System.out.println(getName()+"：正在执行！"+i);
		}
	}
}
```

### 创建线程的三种方式
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715234510320.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
### Thread
==法一：==
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200715234744498.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

==法二：==
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020071614103862.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# Lamba表达式
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200716182830670.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
类似于javascript 中ES6的匿名函数

```java
public class TestLambda2 {
    public static void main(String[] args) {
        ILove love = null;

        love = a -> System.out.println("i love you"+a);
        //调用
        love.love(520);
    }

}

// 定义一个接口
interface ILove{
    void love(int a);
}
```
# 线程状态
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200716212900178.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020071621292289.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 停止线程
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200716213058410.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 线程休眠
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200716225054272.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
**try .. catch          ctrl + alt +T 异常相关操作**  

## 线程礼让
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717141545305.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## Join
Join 合并线程，待此线程执行完成后，在执行其他线程，其他线程阻塞
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020071714281992.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 线程状态观测
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717142835946.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020071714400910.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

测试代码

```java
package ThreadProcessStudy;

public class TestState {
    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(()->{       // lambda表达式
            for (int i = 0; i < 5; i++) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("===");
        });
        // 观察线程状态
       Thread.State state = thread.getState();
        System.out.println(state);    //NEW

        // 观察启动后
        thread.start();
        state = thread.getState();
        System.out.println(state);

        while(state != Thread.State.TERMINATED){  //只要线程不停止
            Thread.sleep(100);
            state = thread.getState();  // 更新线程状态
            System.out.println(state);

        }

    }
}

```
# 线程优先级
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717155412788.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
注意：优先级低只是意味着获得调度的概率低，并不是优先级的就不会被调用，这源于cpu的调度，默认优先级为5

# 守护线程
线程分为**用户线程**和**守护线程**，虚拟机必须确保用户线程(main)执行完毕，不用等待守护线程执行完毕（gc）

```java
package ThreadProcessStudy;

public class TestDaemon {
    public static void main(String[] args) {
        God god = new God();
        You you = new You();

        Thread thread = new Thread(god);
        thread.setDaemon(true);   // 默认false是用户线程，

        thread.start();  // 上帝守护线程启动

        new Thread(you).start();  //你线程启动
    }
}

//god
class God implements  Runnable{

    @Override
    public void run() {
        while(true){
            System.out.println("上帝保佑你");
        }
    }
}

// you
class You implements  Runnable{

    @Override
    public void run() {
        for (int i = 0; i < 1000; i++) {
            System.out.println("你开心得活着");
        }
        System.out.println("goodbye~world");
    }
}

```
输出结果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717162722188.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
上面中间是交替得结果


 *写在最后：全栈方向，前端已经大部分学完，将会以复习的形式出现在博客，大家敬请期待哈~*

