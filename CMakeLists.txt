cmake_minimum_required(VERSION 3.14)
project(LightFileSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LightFileSystem
        #msgq.c
        #philosophers.c
        SuperBlock.cpp
        SuperBlock.h
        #test.c
        iNode.cpp iNode.h LightFileSystem.cpp LightFileSystem.h dir.cpp dir.h)
add_executable(test
        test.cpp
        SuperBlock.cpp
        SuperBlock.h
        #test.c
        iNode.cpp iNode.h )
add_executable(server
        server.cpp  comm.h comm.c iNode.cpp iNode.h
        LightFileSystem.cpp LightFileSystem.h
        dir.cpp dir.h
        SuperBlock.cpp
        SuperBlock.h
        )
add_executable(client
        client.cpp comm.h comm.c
        )
add_executable(ser
        server.c comm.c comm.h
        )
add_executable(cli
        client.c comm.c comm.h
        )
