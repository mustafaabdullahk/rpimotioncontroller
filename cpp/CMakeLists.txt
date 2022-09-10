#project(untitled LANGUAGES CXX)

add_subdirectory(3rdparty)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(Protobuf REQUIRED)
find_package(Threads)
find_package(gRPC CONFIG REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rpimotioncontroller/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rpimotioncontroller/*.cpp")
message(${headers})
add_executable(pirmc
	${headers}
	${sources}
)
target_link_libraries(pirmc Qt${QT_VERSION_MAJOR}::Core -lprotobuf -lgrpc++ -labsl_synchronization protos -lpthread -ldl loguru)
