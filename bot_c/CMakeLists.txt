cmake_minimum_required(VERSION 3.17)
project(bot_c C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/curl/8.0.1/include)

add_executable(bot_c main.c)

target_link_libraries(bot_c /usr/local/Cellar/curl/8.0.1/lib/libcurl.dylib)
