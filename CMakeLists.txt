cmake_minimum_required(VERSION 3.7)
project(rtype)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/Server/includes")
include_directories("${PROJECT_SOURCE_DIR}/Client/includes/Core")
include_directories("${PROJECT_SOURCE_DIR}/Client/includes/Games")
include_directories("${PROJECT_SOURCE_DIR}/Client/includes/Graph")
include_directories("${PROJECT_SOURCE_DIR}/Commons/includes")

file(GLOB_RECURSE SERVER_SRCS RELATIVE ${PROJECT_SOURCE_DIR} "Server/sources/*.cpp")
file(GLOB_RECURSE SERVER_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Server/includes/*.hpp")

file(GLOB_RECURSE CLIENT_SRCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/sources/*.cpp")
file(GLOB_RECURSE CLIENT_SRCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/sources/Core/*.cpp")
file(GLOB_RECURSE CLIENT_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/includes/*.hpp")
file(GLOB_RECURSE CLIENT_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/includes/Core/*.hpp")
file(GLOB_RECURSE CLIENT_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/includes/Games/*.hpp")
file(GLOB_RECURSE CLIENT_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/includes/Graph/*.hpp")

file(GLOB_RECURSE LIBGAME_SRCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/sources/Games/*.cpp")
file(GLOB_RECURSE LIBSFML_SRCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/sources/Graph/*.cpp")
file(GLOB_RECURSE LIBGAME_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/includes/Games/*.hpp")
file(GLOB_RECURSE LIBSFML_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Client/includes/Graph/*.hpp")

file(GLOB_RECURSE COMMONS_SRCS RELATIVE ${PROJECT_SOURCE_DIR} "Commons/sources/*.cpp")
file(GLOB_RECURSE COMMONS_INCS RELATIVE ${PROJECT_SOURCE_DIR} "Commons/includes/*.hpp")

add_library(r-type_sfml SHARED ${LIBSFML_SRCS} ${LIBSFML_INCS})
target_link_libraries(r-type_sfml ${CONAN_LIBS})
add_library(r-type_game SHARED ${LIBGAME_SRCS} ${LIBGAME_INCS})

add_executable(r-type_server Server/main.cpp ${SERVER_SRCS} ${SERVER_INCS} ${COMMONS_SRCS} ${COMMONS_INCS})
add_executable(r-type_client Client/main.cpp ${CLIENT_SRCS} ${CLIENT_INCS} ${COMMONS_SRCS} ${COMMONS_INCS})

target_link_libraries(r-type_server ${Boost_LIBRARIES})
target_link_libraries(r-type_server Threads::Threads)

target_link_libraries(r-type_client ${CONAN_LIBS})
target_link_libraries(r-type_client Threads::Threads)