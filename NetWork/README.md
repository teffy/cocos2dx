如果使用VisualStudio的话，3.x使用Http会出现无法打开包含文件extensions/ExtensionExport.h 的错误，解决方案： 
1、在你自己的头文件中加入#include ”cocos-ext.h” 
2、使用命名空间USING_NS_CC_EXT; 
3、选中工程右键“属性”->”配置属性“->”c/c++”->”常规”->”附加包含目录”中添加“”$(EngineRoot)
参考[http://www.cocoachina.com/bbs/read.php?tid-238349.html]