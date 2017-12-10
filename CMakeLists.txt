cmake_minimum_required(VERSION 3.8)
project(CtCI_6th_cpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        catch.hpp
        main.cpp
        backup.cpp
        BinarySearchTree.cpp BinarySearchTree.h
        Graph.cpp Graph.h
        ex_04_01.cpp
        ex_04_02.cpp
        ex_04_03.cpp
        ex_04_04.cpp
        ex_04_05.cpp
        ex_04_06.cpp
        ex_04_07.cpp
        ex_04_08.cpp
        ex_04_09.cpp
        ex_04_10.cpp
        ex_04_11.cpp
        ex_04_12.cpp
        ex_05_01.cpp
        ex_05_02.cpp
        ex_05_03.cpp
        ex_05_04.cpp
        ex_05_05.cpp
        ex_05_06.cpp
        ex_05_07.cpp
        ex_05_08.cpp
        ex_06_01.cpp
        ex_06_07.cpp
        ex_06_08.cpp
        ex_08_01.cpp
        ex_08_02.cpp
        ex_08_03.cpp
        ex_08_04.cpp
        ex_08_05.cpp
        ex_08_06.cpp
        ex_08_07.cpp
        ex_08_09.cpp
        ex_08_10.cpp
        ex_08_11.cpp
        ex_08_13.cpp ex_09_02.cpp ex_09_05.cpp ex_10_01.cpp ex_10_02.cpp ex_10_03.cpp ex_10_04.cpp ex_10_05.cpp ex_10_07.cpp ex_10_11.cpp ex_10_10.cpp ex_10_08.cpp ex_10_09.cpp ex_12_01.cpp ex_12_02.cpp ex_12_06.cpp ex_12_08.cpp ex_12_09.cpp ex_12_10.cpp ex_12_11.cpp ex_16_01.cpp ex_16_01.cpp ex_16_02.cpp ex_16_03.cpp ex_16_04.cpp ex_16_05.cpp ex_16_06.cpp ex_16_07.cpp ex_16_08.cpp ex_16_09.cpp ex_16_10.cpp ex_16_11.cpp ex_16_12.cpp ex_16_13.cpp ex_16_14.cpp ex_16_15.cpp ex_16_16.cpp ex_16_17.cpp ex_16_18.cpp ex_16_19.cpp ex_16_20.cpp ex_16_21.cpp ex_16_22.cpp ex_16_23.cpp ex_16_24.cpp ex_16_25.cpp ex_16_26.cpp ex_17_01.cpp ex_17_02.cpp ex_17_03.cpp ex_17_04.cpp ex_17_05.cpp ex_17_06.cpp ex_17_07.cpp)

add_executable(CtCI_6th_cpp ${SOURCE_FILES})