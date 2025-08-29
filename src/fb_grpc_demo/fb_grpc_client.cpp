#include <iostream>
#include <grpcpp/grpcpp.h>
#include "hello.grpc.fb.h"
#include "hello_generated.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel)
        : stub_(mygrpc::Greeter::NewStub(channel)) {}

    void SayHello(const std::string& name) {
        flatbuffers::grpc::MessageBuilder mb;

        auto name_offset = mb.CreateString(name);
        auto req_offset = mygrpc::CreateHelloRequest(mb, name_offset);
        mb.Finish(req_offset);

        auto request_msg = mb.ReleaseMessage<mygrpc::HelloRequest>();
        flatbuffers::grpc::Message<mygrpc::HelloReply> response_msg;

        ClientContext context;
        Status status = stub_->SayHello(&context, request_msg, &response_msg);

        // // 3. 获取底层 buffer 指针和尺寸
        // auto buf = request_msg.mutable_data();
        // size_t size = request_msg.size();

        // std::cout << "[Client] sending buffer addr=" << (const void*)buf
        //         << " size=" << size << " bytes" << std::endl;

        if (status.ok()) {
            auto reply = response_msg.GetRoot();
            // std::cout << "[Client] Server replied: " << reply->message()->str() << std::endl;
        } else {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<mygrpc::Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
    GreeterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    size_t size_kb = 100;
    size_t size_bytes = size_kb * 1024;
    std::string large_str(size_bytes, 'A');

    while (true)
    {
        sleep(0.001);
        client.SayHello(large_str);
    }
    
    return 0;
}
