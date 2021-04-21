@[toc]
# 重要常见层
## Dao 层
- `Dao层` :==DAO层主要是做数据持久层的工作==，负责与数据库进行联络的一些任务都封装在此，DAO层的设计首先是设计DAO的接口，然后在Spring的配置文件中定义此接口的实现类，然后就可在模块中调用此接口来进行数据业务的处理，而不用关心此接口的具体实现类是哪个类，显得结构非常清晰，DAO层的**数据源**配置，以及有关数据库连接的参数都在Spring的配置文件中进行配置。
## Service 层                                                                
- `Service层`：==Service层主要负责业务模块的逻辑应用设计==。同样是首先设计接口，再设计其实现的类，接着再Spring的配置文件中配置其实现的关联。这样我们就可以在应用中调用Service接口来进行业务处理。Service层的业务实现，具体要**调用到已定义的DAO层的接口**，封装Service层的业务逻辑有==利于通用的业务逻辑的独立性和重复利用性==，程序显得非常简洁。    

## Controller 层                                                                                                     
- `Controller层`:==Controller层负责具体的业务模块流程的控制==，在此层里面要**调用Serice层的接口**来==控制业务流程==，控制的配置也同样是在Spring的配置文件里面进行，针对具体的业务流程，会有不同的控制器，我们具体的设计过程中可以将流程进行抽象归纳，设计出可以重复利用的子单元流程模块，这样不仅使程序结构变得清晰，也大大减少了代码量。  
## View  层                                                                                                                       
- `View层` 此层与**控制层**结合比较紧密，需要二者结合起来协同工发。View层主要负责前台`jsp页面`的表示，


# 其他层
- `entiy`  实体层
- `exception`  异常层

```java
//HTTP状态码
@ResponseStatus(HttpStatus.NOT_FOUND)      //自定义NotFoundException异常,会跳转到404页面
public class NotFoundException extends RuntimeException {
    public NotFoundException() {
        super();
    }

    public NotFoundException(String message) {
        super(message);
    }

    public NotFoundException(String message, Throwable cause) {
        super(message, cause);
    }
}
```
- `mapper`  mapper  层
- `config`   配置层
- `utils`   工具层
- `interceptors`   拦截器

# 总结
                                                          
- `Dao`，`Service`层这两个层次都可以单独开发，互相的==耦合度很低==
- `Controller`，`View`层，要结合在一起开发，因为==耦合度比较高==                                    
- `Dao`设计的总体规划需要和设计的表，和实现类之间一一对应。                                                                                                                      
这是由我们在DAO层对数据库访问的操作来决定的，对数据库的操作，我们基本要用到的就是新增，更新，删除，查询等方法。因而DAO层里面基本上都应该要涵盖这些方法对应的操作。除此之外，可以定义一些自定义的特殊的对数据库访问的方法。                                                                                                                                                                                                                     
- `Service`层是建立在DAO层之上的，建立了`DAO`层后才可以建立Service层，而Service层又是在Controller层之下的，因而Service层应该==既调用DAO层的接口==，又要==提供接口给Controller层==的类来进行**调用**，它刚好处于一个中间层的位置。每个模型都有一个Service接口，每个接口分别封装各自的业务处理方法。                                                                                                                                                                         

