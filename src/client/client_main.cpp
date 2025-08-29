#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
// #include "proto/gen_pb/helloworld.grpc.pb.h"
#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloRequest;
using helloworld::HelloReply;

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel)
        : stub_(Greeter::NewStub(channel)) {}

    std::string SayHello(const std::string& user, const std::string& id) {
        HelloRequest request;
        request.set_name(user);
        request.set_id(id);

        HelloReply reply;
        ClientContext context;

        Status status = stub_->SayHello(&context, request, &reply);

        if (status.ok()) {
            return reply.message();
        } else {
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
    std::string target_str = "localhost:50052";
    GreeterClient greeter(grpc::CreateChannel(
        target_str, grpc::InsecureChannelCredentials()));
    std::string user("<<< hello world request (call from client)");

    size_t size_kb = 100;
    size_t size_bytes = size_kb * 1024;
    std::string large_str(size_bytes, 'A');

    uint64_t times = 0;
    while (true) {
        sleep(0.001);
        times++;
        std::string id = std::to_string(times);
        std::string reply = greeter.SayHello(large_str, id);
        // std::cout << "[Client] Greeter received: " << reply << std::endl;
    }

    return 0;
}
