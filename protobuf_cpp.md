[转载自](https://blog.csdn.net/hp_cpp/article/details/81561310#commentBox)
0 准备工作：

（1）下载protobuf 
https://github.com/google/protobuf/releases 
 
下载的是cpp版本，选择当前最新版本即可 
（2）安装cmake 
https://cmake.org/download/ 
 
根据系统选择安装的cmake版本，我这里选择的是64位版本安装。



1 编译protocol

解压刚才下载的protobuf包，打开cmake 
 
按图所示，1选择protobuf中的cmake目录，2是选择目标目录（生成的工程存放位置），3的点击左下角的configure按钮： 
 
以vs2015工程为例，上面的一个框是32位版本，下面的Win64是64位版本。以生成32位版本为例，生成64位版本工程操作相同。 
 
点击finish 
 
没有错误，generate按钮变为可用，默认的选项如图，这里就默认生成静态包。 
点击generate按钮后，几秒后，Open Project按钮变为可用，打开工程 
 
这里可以选择生成Debug版本32位的lib，只生成libprotobuf和protoc即可。 

---------------------
作者：hp_cpp 
来源：CSDN 
原文：https://blog.csdn.net/hp_cpp/article/details/81561310?utm_source=copy 
版权声明：本文为博主原创文章，转载请附上博文链接！

这3个是我们需要的。



3 测试生成的lib库和protoc.exe工具

(1)新建一个person.proto的文本文件



package tutorial;

message Person {
  required int32 id = 1;
  required string name = 2;
  optional string email = 3;
}1234567

tutorial是包名（也可以说是命名空间），没有第一行的话，就是没有命令空间的。 
将protoc.exe和person.proto放在同一个文件夹下，再添加一个批处理文件build.bat，内容为：



protoc --cpp_out=./ person.proto1

双击批处理文件build.bat，会在当前目录下生成：person.pb.h和person.pb.cc文件，将其添加到下面的vs工程中。 
（2）建立一个win32控制台程序的工程 
把protobuf-3.6.1\src\google\protobuf这个目录中的头文件(其余的文件可以删除，也可以保留，不影响)，都拷贝过来，放在当前工程下，建立一个include文件夹，把这些.h头文件放进去（文件夹名自己定）。 
生成的libprotobufd.lib也拷贝过来，放在当前目录下的lib文件夹（自己新建的文件夹）中。 
设置工程： 
 
 
 
 
main.cpp代码：



#include <iostream>
#include <fstream>
#include <string>
#include "person.pb.h"

using namespace std;

int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Person person;

    //将数据写到person.pb文件
    person.set_id(123456);
    person.set_name("Mark");
    person.set_email("mark@example.com");

    fstream out("person.pb", ios::out | ios::binary | ios::trunc);
    person.SerializeToOstream(&out);
    out.close();


    //从person.pb文件读取数据
    fstream in("person.pb", ios::in | ios::binary);
    if (!person.ParseFromIstream(&in)) {
        cerr << "Failed to parse person.pb." << endl;
        exit(1);
    }

    cout << "ID: " << person.id() << endl;
    cout << "name: " << person.name() << endl;
    if (person.has_email()) {
        cout << "e-mail: " << person.email() << endl;
    }

    getchar();
    return 0;
}


这两个生成的文件要记得添加到工程中 
 
编译过程：



1>------ 已启动全部重新生成: 项目: pbDemo, 配置: Debug Win32 ------
1>  person.pb.cc
1>  main.cpp
1>  正在生成代码...
1>  pbDemo.vcxproj -> D:\VS2015_Project\pbDemo\Debug\pbDemo.exe
1>  pbDemo.vcxproj -> D:\VS2015_Project\pbDemo\Debug\pbDemo.pdb (Full PDB)
========== 全部重新生成: 成功 1 个，失败 0 个，跳过 0 个 ==========
12345678

运行结果： 
 
参考： 
https://blog.csdn.net/program_anywhere/article/details/77365876 
https://blog.csdn.net/lifeng_math/article/details/51993698 
https://blog.csdn.net/qing666888/article/details/79137963 
VS2013编译错误：-D_SCL_SECURE_NO_WARNINGS解决方案： 
https://blog.csdn.net/Apollon_krj/article/details/68923683 
warning LNK4099: PDB 原因及解决方案： 
http://www.cnblogs.com/fqucuo/p/4887083.html

---------------------
作者：hp_cpp 
来源：CSDN 
原文：https://blog.csdn.net/hp_cpp/article/details/81561310?utm_source=copy 
版权声明：本文为博主原创文章，转载请附上博文链接！
