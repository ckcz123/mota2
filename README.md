可变加点单层 
================

### 游戏说明
此塔为一个可变加点单层塔，“可变”的意思是每打掉一个怪物，所有怪物的攻防都将发生变化。

本塔由C++编写而成，可以参照本人之前所写的[“21层魔塔复刻增强版”](https://github.com/ckcz123/mota)。

本塔有如下特性：

  * 新类型的加点塔：打掉怪物后除了能自己加点，所有剩余怪物的属性都会提升哟！
  * 有三种难度模式：简单、普通、困难。简单是针对新手的，基本乱撞可过；普通难度针对有一定经验的人，稍微思考可过；困难针对拆塔资深玩家的，难度较高。
  * 困难模式通关后会上传成绩到服务器，与大家进行比较。同时按P键可以查看当前MAX。
  * 更多的特性期待你来发掘~

下载地址：http://tieba.baidu.com/p/

### 编译运行

请使用VS2012及以上进行编译运行。  
如果使用VS2015进行编译，请将 `legacy_stdio_definitions.lib` 加入到项目库中，以免发生 `error LNK2019: unresolved external symbol _sscanf` 错误。  
**请将hge文件夹下的所有`dll`文件，以及源代码目录下的`Res`和`Save`文件夹，复制到生成文件夹中，才可以正常进行运行游戏。**   
如果有问题，请联系 `ckcz123@126.com`。  
