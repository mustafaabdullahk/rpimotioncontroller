project(proto LANGUAGES CXX)

set(protobuf_MODULE_COMPATIBLE ON CACHE BOOL "")

include(generate_grpc.cmake)

set(PROTOBUF_IMPORT_DIRS ${PROTOBUF_IMPORT_DIRS} ${CMAKE_CURRENT_LIST_DIR})

#find_package(protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

file(GLOB ProtoFiles "${CMAKE_CURRENT_LIST_DIR}/*.proto")
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtoFiles})
PROTOBUF_GENERATE_GRPC_CPP(GRPC_SRCS GRPC_HDRS ${ProtoFiles})

add_library(protos STATIC ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS} ${ProtoFiles})

target_link_libraries(protos PUBLIC gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)

message(${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(protos PUBLIC ${CMAKE_CURRENT_BINARY_DIR})