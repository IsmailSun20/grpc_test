// server.cpp
#include <grpcpp/grpcpp.h>
#include "logs.grpc.pb.h"
#include <chrono>
#include <thread>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using logs::LogRequest;
using logs::LogMessage;
using logs::LogService;

class LogServiceImpl final : public LogService::Service {
    Status StreamLogs(ServerContext* context,
                      const LogRequest* request, 
                      ServerWriter<LogMessage>* writer) override {
        std::cout << "[LogsServer] [LogServiceImpl] recv request from client, service_name="
                  << request->service_name() << std::endl;

        std::string service_name = request->service_name();
        uint64_t i = 0;
        while (true) {
            i++;
            LogMessage message;
            message.set_content("Log entry #" + std::to_string(i) + " from " + service_name);
            message.set_timestamp(std::time(nullptr));

            // 发送一条日志消息到客户端
            writer->Write(message);

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    LogServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}