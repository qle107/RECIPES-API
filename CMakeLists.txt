cmake_minimum_required(VERSION 3.25)
project(CInterface C)

set(CMAKE_C_STANDARD 11)

# MySQL Connector/C library
find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQL REQUIRED mysqlclient)

# GTK3 library
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# curl library
find_package(CURL REQUIRED)

# cJSON library
find_package(cJSON REQUIRED)

include_directories(${MYSQL_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${CJSON_INCLUDE_DIRS})
link_directories(${MYSQL_LIBRARY_DIRS} ${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(CInterface main.c login_interface.c login_interface.h apiFood.h apiFood.c apiFood.c splitString.h splitString.c)
target_link_libraries(CInterface ${MYSQL_LIBRARIES} ${GTK3_LIBRARIES} ${CURL_LIBRARIES} ${CJSON_LIBRARIES})
