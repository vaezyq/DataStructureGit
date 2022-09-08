cmake_minimum_required(VERSION 2.8)
project(DataStructureGit)

set(CMAKE_CXX_STANDARD 17)

# vector测试
add_executable(VectorTest Vector/Vector.cpp Vector/Fib.cpp Vector/vectorTest.cpp)
# bitmap测试
add_executable(bitMapTest BitMap/bitMapTest.cpp BitMap/Bitmap.cpp BinarySearchTree/BST.cpp BinarySearchTree/BST.h BinarySearchTree/AVL.cpp BinarySearchTree/AVL.h)
# list测试
add_executable(listTest List/listTest.cpp List/List.cpp List/ListNode.cpp)
# stack测试
#add_executable(stackTest Stack/stackTest.cpp Stack/Stack.cpp Vector/Vector.cpp Vector/Fib.cpp)
add_executable(stackTest Stack/stackTest.cpp)
add_executable(some_function Introduction/some_function.cpp)
add_executable(Hailstone Introduction/Hailstone.cpp)
add_executable(maxAndNextBig Vector/maxAndNextBig.cpp)
add_executable(treeTest Tree/treeTest.cpp Tree/BinNode.cpp Tree/BinTree.cpp)

