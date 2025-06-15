cmake_minimum_required(VERSION 3.15)
project(UniversityLibraryGRPC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GRPC REQUIRED grpc++)
pkg_check_modules(PROTOBUF REQUIRED protobuf)

# Find protoc and grpc_cpp_plugin
find_program(PROTOC protoc)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)

# Generate protobuf and gRPC sources
set(PROTO_FILES university.proto)
set(PROTO_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto)
file(MAKE_DIRECTORY ${PROTO_OUT_DIR})

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
    set(PROTO_SRCS ${PROTO_OUT_DIR}/${PROTO_NAME}.pb.cc)
    set(PROTO_HDRS ${PROTO_OUT_DIR}/${PROTO_NAME}.pb.h)
    set(GRPC_SRCS ${PROTO_OUT_DIR}/${PROTO_NAME}.grpc.pb.cc)
    set(GRPC_HDRS ${PROTO_OUT_DIR}/${PROTO_NAME}.grpc.pb.h)
    
    add_custom_command(
        OUTPUT ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS}
        COMMAND ${PROTOC}
        ARGS --grpc_out=${PROTO_OUT_DIR}
             --cpp_out=${PROTO_OUT_DIR}
             --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
             -I${CMAKE_CURRENT_SOURCE_DIR}
             ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating protobuf and gRPC sources for ${PROTO_FILE}"
    )
    
    list(APPEND ALL_PROTO_SRCS ${PROTO_SRCS} ${GRPC_SRCS})
    list(APPEND ALL_PROTO_HDRS ${PROTO_HDRS} ${GRPC_HDRS})
endforeach()

# Include directories
include_directories(${PROTO_OUT_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Server executable
add_executable(server
    src/server/server.cpp
    ${ALL_PROTO_SRCS}
)

target_link_libraries(server
    ${GRPC_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    Threads::Threads
    grpc++_reflection
)

target_include_directories(server PRIVATE
    ${GRPC_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
)

# Client executable
add_executable(client
    src/client/client.cpp
    ${ALL_PROTO_SRCS}
)

target_link_libraries(client
    ${GRPC_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    Threads::Threads
)

target_include_directories(client PRIVATE
    ${GRPC_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
)

# Custom target to generate proto files
add_custom_target(generate_protos DEPENDS ${ALL_PROTO_SRCS} ${ALL_PROTO_HDRS})
