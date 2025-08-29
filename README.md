# 介绍
本项目是基于C++ gRPC库实现的测试demo。
囊括以下部分：
- client_main & server_main: 基于 helloworld.proto 实现 RPC请求，一收一发模式。
- LogsClient & LogsServer: 基于 logs.proto 实现 流式RPC获取，发送一次请求，接收流式的高频消息。
- fb_grpc_server & fb_grpc_client: 基于 hello.fbs 实现 flatbuffer 的基本RPC。

已在ARM平台测试验证

## 项目结构

~~~
.项目根目录
├── CMakeLists.txt
├── README.md
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   ├── 3.16.3
│   │   ├── CMakeDirectoryInformation.cmake
│   │   ├── CMakeOutput.log
│   │   ├── CMakeRuleHashes.txt
│   │   ├── CMakeTmp
│   │   ├── Makefile.cmake
│   │   ├── Makefile2
│   │   ├── TargetDirectories.txt
│   │   ├── cmake.check_cache
│   │   ├── progress.marks
│   │   └── proto.dir
│   ├── Makefile
│   ├── cmake_install.cmake
│   ├── libproto.a
│   └── src
│       ├── client
│       ├── fb_grpc_demo
│       └── server
├── fb
│   ├── fb_files
│   │   └── hello.fbs
│   └── gen_fb
│       ├── hello.grpc.fb.cc
│       ├── hello.grpc.fb.h
│       └── hello_generated.h
├── proto
│   ├── CMakeLists.txt
│   ├── gen_pb
│   │   ├── helloworld.grpc.pb.cc
│   │   ├── helloworld.grpc.pb.h
│   │   ├── helloworld.pb.cc
│   │   ├── helloworld.pb.h
│   │   ├── logs.grpc.pb.cc
│   │   ├── logs.grpc.pb.h
│   │   ├── logs.pb.cc
│   │   └── logs.pb.h
│   └── proto_files
│       ├── helloworld.proto
│       └── logs.proto
├── src
│   ├── client
│   │   ├── CMakeLists.txt
│   │   ├── LogsClient.cpp
│   │   └── client_main.cpp
│   ├── fb_grpc_demo
│   │   ├── CMakeLists.txt
│   │   ├── fb_grpc_client.cpp
│   │   └── fb_grpc_server.cpp
│   └── server
│       ├── CMakeLists.txt
│       ├── LogsServer.cpp
│       └── server_main.cpp
└── thirdparty
    ├── grpc-1.54.x
    │   ├── bin
    │   ├── include
    │   └── lib
    ├── shm_sdk
    │   ├── include
    │   └── lib
    └── unitree_sdk2
        ├── CMakeLists.txt
        ├── README.md
        ├── bin
        ├── example
        ├── example_internal
        ├── include
        ├── install.sh
        ├── lib
        └── thirdparty
~~~

kkk
