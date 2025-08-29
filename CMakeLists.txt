cmake_minimum_required(VERSION 3.5)
project(grpc_helloworld_example C CXX)

set(CMAKE_CXX_STANDARD 17)

set(ARCH ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "CPU architecture: ${ARCH}")

set(GRPC_VERSION 1.54.x)
include_directories(thirdparty/grpc-${GRPC_VERSION}/include)
link_directories(thirdparty/grpc-${GRPC_VERSION}/lib/${ARCH})

# 配置路径
set(PROTO_SRC_DIR ${PROJECT_SOURCE_DIR}/proto/proto_files)
set(PROTO_GEN_DIR ${PROJECT_SOURCE_DIR}/proto/gen_pb)

set(GRPC_BIN_DIR ${PROJECT_SOURCE_DIR}/thirdparty/grpc-${GRPC_VERSION}/bin/${ARCH})
message(STATUS "GRPC_BIN_DIR: ${GRPC_BIN_DIR}")

# 找proto文件
file(GLOB PROTO_FILES "${PROTO_SRC_DIR}/*.proto")

# 自动生成pb文件
foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_FILENAME_WE ${PROTO_FILE} NAME_WE)

    set(GENERATED_SRCS
        ${PROTO_GEN_DIR}/${PROTO_FILENAME_WE}.pb.cc
        ${PROTO_GEN_DIR}/${PROTO_FILENAME_WE}.grpc.pb.cc
    )
    set(GENERATED_HDRS
        ${PROTO_GEN_DIR}/${PROTO_FILENAME_WE}.pb.h
        ${PROTO_GEN_DIR}/${PROTO_FILENAME_WE}.grpc.pb.h
    )

    add_custom_command(
        OUTPUT ${GENERATED_SRCS} ${GENERATED_HDRS}
        COMMAND ${GRPC_BIN_DIR}/protoc
            --proto_path=${PROTO_SRC_DIR}
            --cpp_out=${PROTO_GEN_DIR}
            --grpc_out=${PROTO_GEN_DIR}
            --plugin=protoc-gen-grpc=${GRPC_BIN_DIR}/grpc_cpp_plugin
            ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating gRPC and Protobuf files for ${PROTO_FILENAME_WE}.proto"
    )

    list(APPEND ALL_GENERATED_SRCS ${GENERATED_SRCS})
endforeach()

# # proto静态库
add_library(proto
    ${ALL_GENERATED_SRCS}
)

target_include_directories(proto
    PUBLIC
        ${PROTO_GEN_DIR}
)


find_package(Flatbuffers CONFIG REQUIRED)


# 添加子目录
# add_subdirectory(proto)
add_subdirectory(src/server)
add_subdirectory(src/client)

add_subdirectory(src/fb_grpc_demo)
