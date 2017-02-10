cmake_minimum_required(VERSION 3.6)

project(server)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp CNServer.cpp CNServer.h CNSocket.cpp CNSocket.h User.cpp User.h File.cpp File.h FilesManager.cpp FilesManager.h Helper.cpp Helper.h)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads)
find_package(Soci)
find_package(SQLite3)

add_executable(server ${SOURCE_FILES})
link_directories(/usr/local/lib64/)
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT} -lsoci_core -lglog -lsoci_sqlite3 -lsqlite3 -Wl,-rpath=/usr/local/lib64/)
