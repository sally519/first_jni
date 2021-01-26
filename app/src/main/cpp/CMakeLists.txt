# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
#第一句话，指定CMake最小支持版本的方法
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#第一个参数：最终会生成so的名字
#第二个参数：库的类型：SHARED动态库，STATIC静态库
#第三个参数：需要生成so的源文件
add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )

#第一个参数：最终会生成so的名字
#第二个参数：库的类型：SHARED动态库，STATIC静态库
#第三个参数：IMPORTED 表示我们这个静态库是以导入的形式添加的（预编译静态库）
#add_library( # Sets the name of the library.
#        native-lib
#
#        # Sets the library as a shared library.
#        STATIC
#
#        # Provides a relative path to your source file(s).
#        IMPORTED )
#怎么导入？设置导入路径
#设置目标方法
#设置Test的导入路径  属性
#CMAKE_SOURCE_DIR 当前cmake文件路径
#ANDROID_ABI 安卓gradle里配置的CPU架构
#set_target_properties(Test PROPERTIES IMPORTED_LOCATION XXX.a ${CMAKE_SOURCE_DIR}/xxx/${ANDROID_ABI}/xxx.a) #以.a结尾的是静态编译链接库

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#CMAKE_CXX_FLAGS C++的参数 会传给编译器
#CMAKE_C_FLAGS C的参数 会传给编译器
#重新定义 CMAKE_CXX_FLAGS 变量 + -L
#CMAKE_CXX_FLAGS表面是C++写的  CMAKE_C_FLAGS的话就是c语言，如果混合的既有c又有c++那还是用CMAKE_CXX_FLAGS
#CMAKE_SOURCE_DIR 指的是当前这个文件的位置
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -LD:/AndroidStudioProject/FirstJNIProject/app/libs/armeabi-v7a")#把libs里面的库链接到.cpp文件

#链接  不能换位置
#第一个参数：要生成的目标so
#第二个参数：编译so需要依赖的模块、方法
target_link_libraries( # Specifies the target library.
                       native-lib
                       #设置文件
                       main
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )