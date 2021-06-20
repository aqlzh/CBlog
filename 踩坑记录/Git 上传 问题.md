# Push 代码

```bash
$ git push origin master
To https://gitee.com/lzh_create/minprogram_shop.git
 ! [rejected]        master -> master (non-fast-forward)
error: failed to push some refs to 'https://gitee.com/lzh_create/minprogram_shop.git'
hint: Updates were rejected because the tip of your current branch is behind
hint: its remote counterpart. Integrate the remote changes (e.g.
hint: 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```
## 报错：
==To https://gitee.com/lzh_create/minprogram_shop.git
 ! [rejected]        master -> master (non-fast-forward)
error: failed to push some refs to==


## 解法一：
1、将远程库和本地库同步，
```bash
git pull origin master --allow-unrelated-histories
```
2、添加到队列

```bash
git add .  
```
3、将队列提交到本地缓存

```bash
git commit -m “提交描述” 
```
4、将本地库文件同步到远程库

```bash
git push origin master 
```

## 解法二
根目录拉取 `pull` 代码然后提交推送 `push` 
# Tips
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210203160320681.png)

提交时的用户名为： 红色标注 而不是 `aqlzh`
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210203160443712.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
## 解法三
因为提交的代码分支存在差异

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308110958177.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1F1YW50dW1Zb3U=,size_16,color_FFFFFF,t_70)
==解法==

首先将远程仓库的代码`拉取`下来然后再`推送`
