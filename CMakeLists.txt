cmake_minimum_required(VERSION 3.22)
project(demo)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()


find_package(Protobuf REQUIRED)

execute_process(
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I=${CMAKE_CURRENT_LIST_DIR} --cpp_out=${PROJECT_BINARY_DIR} person.proto
)

# include_directories(${Protobuf_INCLUDE_DIRS})
# include_directories(${CMAKE_CURRENT_BINARY_DIR})
# add_custom_command(protobuf_generate_cpp)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ./*.proto)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS EXPORT_MACRO DLL_EXPORT ./*.proto)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS PROTO_DESCS ./*.proto)

include_directories(${PROJECT_BINARY_DIR})

add_executable(demo main.cpp person.pb.cc)
target_link_libraries(demo  protobuf)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
