@[toc]
# JWT 引入

-  `jsonwebtoken`（JWT）是一个开放标准（rfc7519），它定义了一种紧凑的、自包含的方式，用于在各方之间以JSON对象安全地传输信息。


-  [官网地址:]( https://jwt.io/introduction/)

## JWT  常见用途
- `Authorization` (授权) : 用户登录，后续每个请求都将包含JWT，允许用户访问该令牌允许的路由、服务和资源。单点登录是现在广泛使用的JWT的一个特性，因为它的开销很小，并且可以轻松地跨域使用。

- `Information Exchange` (信息交换) : 对于安全的在各方之间传输信息而言，JSON Web Tokens无疑是一种很好的方式。因为JWT可以被签名，例如，用公钥/私钥对，可以确定发送人就是它们所说的那个人。另外，由于签名是使用头和有效负载计算的，还可以验证内容没有被篡改。


  ## JWT  介绍
  
  ###  认证方式与流程
  
 #### 基于session认证
  - `http`协议本身是一种无状态的协议，这意味着如果用户向我们的应用提供用户名和密码来进行用户认证，那么下一次请求时，用户还要再一次进行用户认证才行，因为根据http协议，我们并不能知道是哪个用户发出的请求，所以为了让我们的应用能识别是哪个用户发出的请求，我们只能在服务器存储一份用户登录的信息，这份登录信息会在响应时传递给浏览器，告诉其保存为cookie,以便下次请求时发送给我们的应用，这样我们的应用就能识别请求来自哪个用户,

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210226220836189.png)
#### 基于JWT 认证
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210226221317244.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
- 首先，前端通过Web表单将自己的用户名和密码发送到后端的接口。这一过程一般是一个HTTP `POST`请求。建议的方式是通过SSL加密的传输（https协议），从而避免敏感信息被嗅探。
- 后端核对用户名和密码成功后，将用户的id等其他信息作为JWT Payload（负载），将其与头部分别进行`Base64`编码拼接后签名，形成一个JWT(Token)。形成的JWT就是一个形同`lll.zzz.xxx`的字符串。 `token head.payload.singurater`

- 后端将JWT字符串作为登录成功的返回结果返回给前端。前端可以将返回的结果保存在`localStorage`或`sessionStorage`上，退出登录时前端删除保存的JWT即可。

- 前端在每次请求时将JWT放入HTTP Header中的`Authorization`位。(解决XSS和XSRF问题) HEADER

- 后端检查是否存在，如存在验证JWT的有效性。例如，检查签名是否正确；检查Token是否过期；检查Token的接收方是否是自己（可选）。
- 验证通过后后端使用JWT中包含的用户信息进行其他逻辑操作，返回相应结果。

### JWT优势

- 简洁(Compact): 可以通过URL，POST参数或者在HTTP header发送，因为数据量小，传输速度也很快

- 自包含(Self-contained)：负载中包含了所有用户所需要的信息，避免了多次查询数据库

- 因为Token是以JSON加密的形式保存在客户端的，所以JWT是跨语言的，原则上任何web形式都支持。

- 不需要在服务端保存会话信息，特别适用于分布式微服务。

- 输出是三个由点分隔的Base64-URL字符串，可以在HTML和HTTP环境中轻松传递这些字符串，与基于XML的标准（例如SAML）相比，它更紧凑。



## JWT  结构
### 令牌组成

```bash
token   string  ====>  header.payload.singnature   token   
```

- 1.标头(Header)
- 2.有效载荷(Payload)
- 3.签名(Signature)
- 因此，JWT通常如下所示:xxxxx.yyyyy.zzzzz   `Header.Payload.Signature`

#### Header

- 标头通常由两部分组成：令牌的类型（即JWT）和所使用的签名算法，例如HMAC SHA256或RSA。它会使用 Base64 编码组成 JWT 结构的第一部分。

- 注意:Base64是一种编码，也就是说，它是可以被翻译回原来的样子来的。它并不是一种加密过程。

常用格式如下
```bash
{
  "alg": "HS256",
  "typ": "JWT"
}
```

#### Payload
- 令牌的第二部分是有效负载，其中包含声明。声明是有关实体（通常是用户）和其他数据的声明。同样的，它会使用 Base64 编码组成 JWT 结构的第二部分

```bash
{
  "sub": "1234567890",
  "name": "John Doe",
  "admin": true
}
```

==注意== ：在负载中不能放置敏感信息（Password）


#### Signature
- 前面两部分都是使用 `Base64 `进行编码的，即前端可以解开知道里面的信息。Signature 需要使用编码后的 header 和 payload 以及我们提供的一个密钥，然后使用 header 中指定的签名算法（HS256）进行签名。签名的作用是保证 JWT 没有被篡改过
- 如:

```bash
HMACSHA256(base64UrlEncode(header)
 + "." + 
 + base64UrlEncode(payload),secret);
```

### 签名目的
- 最后一步签名的过程，实际上是对头部以及负载内容进行签名，防止内容被窜改。如果有人对头部以及负载的内容解码之后进行修改，再进行编码，最后加上之前的签名组合形成新的JWT的话，那么服务器端会判断出新的头部和负载形成的签名和JWT附带上的签名是不一样的。如果要对新的头部和负载进行签名，在不知道服务器加密时用的密钥的话，得出来的签名也是不一样的。

## 拓展——盐值
[参考链接](https://blog.csdn.net/codeslin/article/details/103560657?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-2&spm=1001.2101.3001.4242)

**密码学**： 通过盐值生成密文

[参考链接](https://blog.csdn.net/u012877396/article/details/103742632?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-0&spm=1001.2101.3001.4242)
# JWT  程序编写

## JWT  依赖库介绍

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210228190036167.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
依赖仓库（github）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210228185927704.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

[官方网站](https://github.com/auth0/java-jwt)

## JWT 使用
### Token  令牌的获取
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210228201535123.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
    @Test
    void contextLoads() {
        Calendar instance = Calendar.getInstance();
        instance.add(Calendar.SECOND,100);   //100 秒后令牌过期

        String token = JWT.create()
                .withClaim("userid",12)
                .withClaim("username", "xiaochen")//payload
                .withExpiresAt(instance.getTime())//指定令牌过期时间
                .sign(Algorithm.HMAC256("!Q@W#E$R"));//签名
        System.out.println(token);
    }
```

==注意== ：   令牌时间的设置，以及签名算法的设置，`withClaim()`的运用
### Token  令牌的解析
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210228203739103.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)

```java
   public void test(){
        //创建验证对象
        JWTVerifier jwtVerifier = JWT.require(Algorithm.HMAC384("!Q@W#E$R")).build();

        DecodedJWT verify = jwtVerifier.verify("eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJleHAiOjE1OTY3OTI1MzMsInVzZXJpZCI6MTIsInVzZXJuYW1lIjoieGlhb2NoZW4ifQ.pfGxzorMbjrZtEEm4sbstySiWsJoMkRQfPcwOOo-fkM");

        System.out.println(verify.getClaim("userid").asInt());
        System.out.println(verify.getClaim("username").asString());
        System.out.println("过期时间: "+verify.getExpiresAt());

        //System.out.println(verify.getClaims().get("userid").asInt());
        //System.out.println(verify.getClaims().get("username").asString());
    }
```

#### 常见异常信息
- `SignatureVerificationException`:				签名不一致异常
- `TokenExpiredException`:    						令牌过期异常
- `AlgorithmMismatchException`:						算法不匹配异常
- `InvalidClaimException`:								失效的payload异常


## JWT 工具类封装

```java
package com.baizhi.utils;

import com.auth0.jwt.JWT;
import com.auth0.jwt.JWTCreator;
import com.auth0.jwt.JWTVerifier;
import com.auth0.jwt.algorithms.Algorithm;
import com.auth0.jwt.interfaces.DecodedJWT;

import java.util.Calendar;
import java.util.Map;

public class JWTUtils {


    private static final String  SING = "!Q@W3e4r%T^Y";

    /**
     * 生成token  header.payload.sing
     */
    public static String getToken(Map<String,String> map){

        Calendar instance = Calendar.getInstance();
        instance.add(Calendar.DATE,7);//默认7天过期

        //创建jwt builder
        JWTCreator.Builder builder = JWT.create();

        //payload
        map.forEach((k,v)->{
            builder.withClaim(k,v);
        });

        String token = builder.withExpiresAt(instance.getTime())//指定令牌过期时间
                .sign(Algorithm.HMAC256(SING));//sign
        return token;
    }

    /**
     * 验证token 合法性
     *
     */
    public static DecodedJWT verify(String token){
        return JWT.require(Algorithm.HMAC256(SING)).build().verify(token);
    }

//    /**
//     * 获取token信息方法
//     */
//    public static DecodedJWT getTokenInfo(String token){
//        DecodedJWT verify = JWT.require(Algorithm.HMAC256(SING)).build().verify(token);
//        return verify;
//    }
}

```

==拓展==：
后端 拦截器、网关
拦截器/过滤器  配合 shiro/secyrity    结合实现操作


# 参考代码
[跳转链接](https://github.com/aqlzh/JavaEE-Next/tree/main/springbootjwt)




