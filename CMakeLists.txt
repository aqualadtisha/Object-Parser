cmake_minimum_required(VERSION 3.25)
project(Object_Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(Object_Parser src/main.cc
        src/model/facade_model.cc src/model/model.h src/controller.h src/model/model.cc src/model/facade_model.h src/front.h
        )

find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(Object_Parser PRIVATE Qt6::Core)

