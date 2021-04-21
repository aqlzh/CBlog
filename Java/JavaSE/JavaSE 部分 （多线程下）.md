写在前面：分享技术，共同进步，把之前写的笔记搬运至博客，*有不足请见谅，相关意见可评论告知  (≧∇≦)ﾉ
> 编程路漫漫，学习无止尽！

@[toc]
# 线程同步

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717164047284.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717164154947.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 三大线程不安全案例
### 一、多人同时抢票问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717184919921.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

### 二、银行存款问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717214057234.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
package ThreadProcessStudy.ThreeSync;

public class UnsafeBank {
    public static void main(String[] args) {
       Account account = new Account(100,"结婚基金");

        Drawing you1 = new Drawing(account,50,"you1");
        Drawing you2 = new Drawing(account,100,"you2");

        you1.start();
        you2.start();
    }
}
class Drawing extends Thread{
    Account account ;
    int drawingMoney ;
    int nowMoney;

    public Drawing( Account account ,int drawingMoney,String name){
        super(name);
        this.account = account;
        this.drawingMoney = drawingMoney;

    }
    @Override
    public  void run(){
        if(account.money-drawingMoney<0){
            System.out.println(Thread.currentThread().getName()+"钱不够");
            return;
        }
        // sleep可以放大问题
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        account.money = account.money - drawingMoney;
        nowMoney = nowMoney + drawingMoney;
        System.out.println(account.name+"余额为"+account.money);
        System.out.println(this.getName()+"手里得钱"+nowMoney);
    }


}
// 账户
 class Account {
    int money ; // 余额
    String name ;

    public Account(int money, String name) {
        this.money = money;
        this.name = name;
    }


}

```

### 三、同时添加集合问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717214246507.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 同步方法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717213951603.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
# 同步块
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717214438682.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
银行取钱举例

# 死锁
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020071722440137.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
package ThreadProcessStudy;

public class DeadLock {
    public static void main(String[] args) {
        Makeup g1 = new Makeup(0,"灰姑娘");
        Makeup g2 = new Makeup(0,"白雪公主");

        g1.start();
        g2.start();

    }
}

class Lipstick{

}

class Mirror{

}

class Makeup extends Thread{
    static Lipstick  lipstick= new Lipstick();
    static Mirror mirror = new Mirror();

    int choice ;
    String girl ;

    public Makeup( int choice, String girl) {
        this.choice = choice;
        this.girl = girl;
    }

    @Override
    public void run(){
       // 化妆
        try {
            makeuo();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    // 化妆，互相持有对方的锁，级需要拿到对方的资源
    private void makeuo() throws InterruptedException {
        if(choice ==0){
            synchronized (lipstick){  // 获得口红的锁
                System.out.println(this.girl+"获得口红的锁");
                Thread.sleep(1000);

//                synchronized (mirror){  // 一秒后想获得镜子的锁
//                    System.out.println(this.girl+"获得镜子的锁");
//                        ****注意这样放在代码块里面就形成死锁
//                }
            }
            synchronized (mirror){  // 一秒后想获得镜子的锁
                System.out.println(this.girl+"获得镜子的锁");

            }
        }else{
            synchronized (mirror){  // 一秒后想获得镜子的锁
                System.out.println(this.girl+"获得镜子的锁");
                Thread.sleep(2000);
            }
            synchronized (lipstick){
                System.out.println(this.girl+"获得口红的锁");

            }
        }
    }
}

```

输出结果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717231706820.png)
## 死锁的避免方法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717231737344.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# Lock(锁)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717232027809.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717235911551.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

加锁前代码：

```java
package ThreadProcessStudy;

public class TestLock {
    public static void main(String[] args) {
        TestLock2 testLock2 = new TestLock2();

        // 模拟三个线程同时操作一个对象
        new Thread(testLock2).start();
        new Thread(testLock2).start();
        new Thread(testLock2).start();
    }
}

class TestLock2 implements  Runnable{

    int ticketNums = 10;
    @Override
    public void run() {
        while(true){
            if(ticketNums >= 0) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println(Thread.currentThread().getName()+"拿到"+ticketNums--);   //注意分割符的位置
            }else{
                break ;
            }

        }
    }
}

```
输出结果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717235151767.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717235633503.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

加锁后：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717235559434.png)
# synchronized 与Lock的对比
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717235741715.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

# 生产者消费者问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200718000823709.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
通信问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200718000907222.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

## 方法一：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200718001029126.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 方法二：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200718001114182.png)
# 线程池
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200718001331519.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200718001515738.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
代码实列
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200718002732393.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

 *写在最后：全栈方向，前端已经大部分学完，将会以复习的形式出现在博客，大家敬请期待哈~*
