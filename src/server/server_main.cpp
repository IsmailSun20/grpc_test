#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
// #include "proto/gen_pb/helloworld.grpc.pb.h"
#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloRequest;
using helloworld::HelloReply;

// 实现服务
class GreeterServiceImpl final : public Greeter::Service {
public:
    Status SayHello(ServerContext* context, const HelloRequest* request,
                    HelloReply* reply) override {
        // std::cout << "[Server] [GreeterServiceImpl] "
        //           << request->name() << " " << request->id() << std::endl;

        std::string reply_message(">>> hello world reply (reply from server) ");
        reply->set_message(reply_message + request->id());
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50052");
    GreeterServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
