本仓库下所有程序仅供参考, 大家最好独立完成

所有程序都在"程序/"文件夹中. 报告在"报告/"文件夹中.

程序的构建方法(需要 cmake):

进入相应的文件夹中, 然后输入以下命令:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

执行:

```bash
$ cd build
$ ./main
```

(windows 系统下可能略有不同)

目前已知所有程序的多表管理中, 删除操作都有问题, 只有顺序线性表目前已修复, 其他的懒得修了, 谁来帮我修一修(逃
