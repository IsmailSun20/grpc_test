# 介绍
本项目是基于C++ gRPC库实现的测试demo。
囊括以下部分：
- client_main & server_main: 基于 helloworld.proto 实现 RPC请求，一收一发模式。
- LogsClient & LogsServer: 基于 logs.proto 实现 流式RPC获取，发送一次请求，接收流式的高频消息。
- fb_grpc_server & fb_grpc_client: 基于 hello.fbs 实现 flatbuffer 的基本RPC。

已在ARM平台测试验证