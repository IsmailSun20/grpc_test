// client.cpp
#include <grpcpp/grpcpp.h>
#include "logs.grpc.pb.h"
#include <memory>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using logs::LogRequest;
using logs::LogMessage;
using logs::LogService;

class LogClient {
public:
    LogClient(std::shared_ptr<Channel> channel) 
      : stub_(LogService::NewStub(channel)) {}

    void StreamLogs(const std::string& service_name) {
        LogRequest request;
        request.set_service_name(service_name);

        ClientContext context;
        LogMessage message;
        std::unique_ptr<grpc::ClientReader<LogMessage>> reader(
            stub_->StreamLogs(&context, request));

        while (reader->Read(&message)) {
            std::cout << "[LogsClient] Received log: " << message.content() 
                    << " (Timestamp: " << message.timestamp() << ")" << std::endl;
        }

        Status status = reader->Finish();
        if (status.ok()) {
            std::cout << "Stream completed successfully." << std::endl;
        } else {
            std::cout << "Stream failed: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<LogService::Stub> stub_;
};

int main() {
    std::string target("localhost:50051");
    LogClient client(
        grpc::CreateChannel(target, grpc::InsecureChannelCredentials()));
    
    std::cout << "Requesting logs for service 'my_app'..." << std::endl;
    client.StreamLogs("my_app");
    
    return 0;
}