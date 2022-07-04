cmake_minimum_required(VERSION 3.0)
project(DataStructureGit)

set(CMAKE_CXX_STANDARD 17)

add_executable(VectorTest Vector/Vector.cpp Vector/Fib.cpp Vector/vectorTest.cpp List/listTest.cpp)
add_executable(listTest List/listTest.cpp List/List.cpp List/ListNode.cpp Tree/BinNode.cpp Tree/BinNode.h Tree/BinTree.cpp Tree/BinTree.h Introduction/some_function.cpp Introduction/Hailstone.cpp Introduction/shift.cpp)
add_executable(some_function Introduction/some_function.cpp)
add_executable(Hailstone Introduction/Hailstone.cpp)