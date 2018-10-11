转载自：`https://www.cnblogs.com/tangxin-blog/p/5698137.html`

原理:protobuf 是google的一个开源项目,其源代码在github上可以下载到,并且源码都采用cmake来构建,所以我们可以把源码下载到本地,然后了利用cmake构建本地工程,然后编译.

本文以当前最新的 protobuf_3.5.0 为例

复制以下代码,保存到  one_key_download_and_build_protobuf.bat  文件中,运行即可.(windows上的bat最好都以gbk编码来编辑,避免出现中文乱码)

``` bat
echo off & color 0A

rem 参考文章 https://github.com/google/protobuf/blob/master/cmake/README.md
rem 默认当前操作系统已安装 git 和 cmake,并配置好了环境变量

set "WORK_DIR=%cd%"
echo %WORK_DIR%

rem 设置所需要的Protobuf版本,最新版本可以在github上查到 https://github.com/google/protobuf
set "PROTOBUF_VESION=v3.5.0"
echo %PROTOBUF_VESION%
set "PROTOBUF_PATH=protobuf_%PROTOBUF_VESION%"
echo %PROTOBUF_PATH%

rem 从githug上拉取protobuf源代码
git clone -b %PROTOBUF_VESION% https://github.com/google/protobuf.git %PROTOBUF_PATH%

rem 从github上拉取gmock
cd %PROTOBUF_PATH%
git clone -b release-1.7.0 https://github.com/google/googlemock.git gmock

rem 从github上拉取gtest
cd gmock
git clone -b release-1.7.0 https://github.com/google/googletest.git gtest

cd %WORK_DIR%
rem 设置VS工具集,相当于指定VS版本,取决于VS的安装路径
set VS_DEV_CMD="D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"
rem 设置工程文件夹名字,用来区分不同的VS版本
set "BUILD_PATH=protobuf_%PROTOBUF_VESION%_vs2015_sln"
echo %BUILD_PATH%
if not exist %BUILD_PATH% md %BUILD_PATH%
cd %BUILD_PATH%
rem 设置编译版本 Debug Or Release
set "MODE=Release"
echo %MODE%
if not exist %MODE% md %MODE%
cd %MODE%
echo %cd%

set "CMAKELISTS_DIR=%WORK_DIR%\%PROTOBUF_PATH%\cmake"
echo %CMAKELISTS_DIR%

rem 开始构建和编译
call %VS_DEV_CMD%
cmake %CMAKELISTS_DIR% -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=%MODE%
call extract_includes.bat
nmake /f Makefile

echo %cd%
echo %PROTOBUF_VESION%
echo %BUILD_PATH%
echo %MODE%
pause

```

当然,你也可以的通过修改上面的的脚本来编译你所需要的版本,具体的参数注释的很详细

具体的版本可以在github上查到 https://github.com/google/protobuf

有如下脚本: generate.bat (windows上的bat最好都以gbk编码来编辑,避免出现中文乱码)

```
color 0A && echo off


rem protoc程序名
set "PROTOC_EXE=protoc.exe"
rem .proto文件名
set "PROTOCOL_FILE_NAME=protocol.proto"

%PROTOC_EXE% --version

set "WORK_DIR=%cd%"
rem cpp
set "CPP_OUT_PATH=%cd%\cpp"
if not exist %CPP_OUT_PATH% md %CPP_OUT_PATH%
rem cs
set "CS_OUT_PATH=%cd%\cs"
if not exist %CS_OUT_PATH% md %CS_OUT_PATH%
rem java
set "JAVA_OUT_PATH=%cd%\java"
if not exist %JAVA_OUT_PATH% md %JAVA_OUT_PATH%
rem java Nano
set "JAVANANO_OUT_PATH=%cd%\javanano"
if not exist %JAVANANO_OUT_PATH% md %JAVANANO_OUT_PATH%
rem js
set "JS_OUT_PATH=%cd%\js"
if not exist %JS_OUT_PATH% md %JS_OUT_PATH%
rem objc(Objective C)
set "OBJC_OUT_PATH=%cd%\objc"
if not exist %OBJC_OUT_PATH% md %OBJC_OUT_PATH%
rem php
set "PHP_OUT_PATH=%cd%\php"
if not exist %PHP_OUT_PATH% md %PHP_OUT_PATH%
rem python
set "PYTHON_OUT_PATH=%cd%\python"
if not exist %PYTHON_OUT_PATH% md %PYTHON_OUT_PATH%
rem ruby
set "RUBY_OUT_PATH=%cd%\ruby"
if not exist %RUBY_OUT_PATH% md %RUBY_OUT_PATH%

echo.generate cpp
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --cpp_out="%CPP_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate cs
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --csharp_out="%CS_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate java
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --java_out="%JAVA_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate java nano
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --javanano_out="%JAVANANO_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate js
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --js_out="%JS_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate objective c
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --objc_out="%OBJC_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate php
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --php_out="%PHP_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate python
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --python_out="%PYTHON_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
echo.generate ruby
"%WORK_DIR%\%PROTOC_EXE%" --proto_path="%WORK_DIR%" --ruby_out="%RUBY_OUT_PATH%" "%WORK_DIR%\%PROTOCOL_FILE_NAME%"
pause
```
