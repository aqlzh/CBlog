写在前面：分享技术，共同进步，把写的笔记搬运至博客，有不足请见谅，相关意见可评论告知  ╰(￣ω￣ｏ)
> 编程路漫漫，学习无止尽！

@[toc]
 # File概述
   java.io.File类， 文件和目录路径名的抽象表示形式。
   常见方法：
      1.  创建一个文件/文件夹
       2.  删除文件/文件夹
        3. 获取文件/文件夹
        4. 判断文件/文件夹是否存在
        5. 对文件夹进行遍历
        6. 获取文件的大小
    File类是一个与系统无关的类,任何的操作系统都可以使用这个类中的方法
* **绝对路径**：从盘符开始的路径，这是一个完整的路径。
* **相对路径**：相对于项目目录的路径，这是一个便捷的路径，开发中经常使用。

==路径分隔符== windows:分号;   ||     linux:冒号:
    static String pathSeparator 与系统有关的路径分隔符，它被表示为一个字符串。
            static char pathSeparatorChar 与系统有关的路径分隔符。
==文件名称分隔符== windows:反斜杠\    ||  linux:正斜杠/
            static String separator 与系统有关的默认名称分隔符，它被表示为一个字符串。
            static char separatorChar 与系统有关的默认名称分隔符。
  **注意:**
            1.路径是不区分大小写
            2.路径中的文件名称分隔符windows使用反斜杠,反斜杠是转义字符,两个反斜杠代表一个普通的反斜杠

# 方法
## 构造方法
* `public File(String pathname) ` ：通过将给定的**路径名字符串**转换为抽象路径名来创建新的 File实例。  
* `public File(String parent, String child) ` ：从**父路径名字符串和子路径名字符串**创建新的 File实例。
* `public File(File parent, String child)` ：从**父抽象路径名和子路径名字符串**创建新的 File实例

## 获取功能方法
* `public String getAbsolutePath() ` ：返回此File的绝对路径名字符串。

* ` public String getPath() ` ：将此File转换为路径名字符串。 

* `public String getName()`  ：返回由此File表示的文件或目录的名称。  

* `public long length()`  ：返回由此File表示的文件的长度。   

## 判断功能的方法
- `public boolean exists()` ：此File表示的文件或目录是否实际存在。
- `public boolean isDirectory()` ：此File表示的是否为目录。
- `public boolean isFile()` ：此File表示的是否为文件。

## 创建删除功能的方法

- `public boolean createNewFile()` ：当且仅当具有该名称的文件尚不存在时，创建一个新的空文件。 
- `public boolean delete()` ：删除由此File表示的文件或目录。  
- `public boolean mkdir()` ：创建由此File表示的目录。
- `public boolean mkdirs()` ：创建由此File表示的目录，包括任何必需但不存在的父目录。


## 目录的遍历

* `public String[] list()` ：返回一个String数组，表示该File目录中的所有子文件或目录。


* `public File[] listFiles()` ：返回一个File数组，表示该File目录中的所有的子文件或目录。 


### 应用（递归打印多级目录）

```java
public class Demo04Recurison {
    public static void main(String[] args) {
        File file = new File("c:\\abc");
        getAllFile(file);
    }

    /*
        定义一个方法,参数传递File类型的目录
        方法中对目录进行遍历
     */
    public static void getAllFile(File dir){
        System.out.println(dir);//打印被遍历的目录名称
        File[] files = dir.listFiles();
        for (File f : files) {
            //对遍历得到的File对象f进行判断,判断是否是文件夹
            if(f.isDirectory()){
                //f是一个文件夹,则继续遍历这个文件夹
                //我们发现getAllFile方法就是传递文件夹,遍历文件夹的方法
                //所以直接调用getAllFile方法即可:递归(自己调用自己)
                getAllFile(f);
            }else{
                //f是一个文件,直接打印即可
                System.out.println(f);          //*****
            }
        }
    }
}
```
优化：搜索指定文件结尾的文件
将***** 部分改为  

```java
if(f.getName().toLowerCase().endWith(".java"){
     
}
```
### FileFilter 过滤器

```java
package FileIo;

import java.io.File;
import java.io.FileFilter;
import java.io.FilenameFilter;

public class FileFilter2 {
    public static void main(String[] args) {
        File file=new File("D:\\GitFile");
        getAllFileName2(file);
    }

    public static void getAllFileName(File file){
        //FileFilter
        File[] files = file.listFiles(new FileFilter() {//过滤器匿名内部类 实现accept方法
            @Override
            public boolean accept(File pathname) {
                //过滤规则,pathname是文件夹或者是.java结尾的文件返回true
                return pathname.isDirectory() || pathname.getName().toLowerCase().endsWith(".java");
            }
        });
        for (File f1 : files) {
            //System.out.println("B==="+f1);
            if(f1.isDirectory()){
                getAllFileName(f1);//递归
                //System.out.println("C==="+f1);
            }else {
                System.out.println(f1);
            }
        }
    }

    public static void getAllFileName2(File file){
        //FilenameFilter
        File[] files = file.listFiles(new FilenameFilter() {//过滤器匿名内部类 实现accept方法
            @Override
            public boolean accept(File dir, String name) {
                //过滤规则,dir+name是文件夹或者是.java结尾的文件返回true
                return new File(dir,name).isDirectory() || name.toLowerCase().endsWith(".java");
            }
        });
        for (File f1 : files) {
            //System.out.println("B==="+f1);
            if(f1.isDirectory()){
                getAllFileName(f1);//递归
                //System.out.println("C==="+f1);
            }else {
                System.out.println(f1);
            }
        }
    }
}

```

