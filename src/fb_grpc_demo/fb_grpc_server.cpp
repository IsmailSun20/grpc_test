#include <iostream>
#include <grpcpp/grpcpp.h>
#include "hello.grpc.fb.h"
#include "hello_generated.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class GreeterServiceImpl final : public mygrpc::Greeter::Service {
public:
    ::grpc::Status SayHello(ServerContext* context,
                            const flatbuffers::grpc::Message<mygrpc::HelloRequest>* request,
                            flatbuffers::grpc::Message<mygrpc::HelloReply>* response) override {

        // // 地址验证
        // auto buf = request->mutable_data();
        // auto size = request->size();

        // std::cout << "[Server] buffer addr=" << (const void*)buf
        //         << " size=" << size << std::endl;

        // ZeroCopy 读取请求
        auto req = request->GetRoot(); 
        std::string name = req->name()->str();
        // std::cout << "[Server] Received: " << name << std::endl;

        // ZeroCopy 构建响应
        flatbuffers::grpc::MessageBuilder mb;
        auto msg_offset = mb.CreateString("Hello " + name);
        auto reply_offset = mygrpc::CreateHelloReply(mb, msg_offset);
        mb.Finish(reply_offset);
        *response = mb.ReleaseMessage<mygrpc::HelloReply>();

        return Status::OK;
    }
};

int main(int argc, char** argv) {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}
