 #编译要求核验
 #==============================

 cmake_minimum_required(VERSION 3.10)

 #==============================
 # 项目设定
 #==============================

 set(TARGET_NAME "UnityTest")

 #==============================
 # 编译命令行设定
 #==============================

 set(CMAKE_CXX_STANDARD 17)

 #==============================
 # 源
 #==============================

 # 查找项目目录下所有源文件，记录入 TARGET_SOURCE 中
 file(GLOB_RECURSE TARGET_SOURCE "*.cpp")
 # 查找项目目录下所有头文件，记录入 TARGET_HEADER 中
 file(GLOB_RECURSE TARGET_HEADER "*.hpp")

 #==============================
 # 编译目标
 #==============================

 # 编译可执行文件
 add_executable(${TARGET_NAME} ${TARGET_SOURCE} ${TARGET_HEADER})

 target_include_directories(${TARGET_NAME} PRIVATE "../")
 target_link_libraries(${TARGET_NAME} PRIVATE GaiaThreadNest)

 #==============================
 # 第三方库
 #==============================

 # 在Linux系统下，多线程模块并非自动链接的，需要额外链接。
 if(CMAKE_SYSTEM_NAME MATCHES "Linux")
 find_package(Threads)
 target_link_libraries(${TARGET_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
 endif()