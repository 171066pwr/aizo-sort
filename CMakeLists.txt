cmake_minimum_required(VERSION 3.30)
project(1_sort)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp
        model/SorTable.cpp
        model/SorTable.h
        model/TableGenerator.cpp
        model/TableGenerator.h
        utils/NumberUtils.cpp utils/NumberUtils.h utils/Logger.h
        io/BasicIO.cpp
        io/BasicIO.h
        io/SorTableIO.cpp
        io/SorTableIO.h
        model/Table.h
        io/InvalidFileException.h
        model/sorters/BaseSorter.h
        model/SingleResult.cpp
        model/SingleResult.h
        model/sorters/QuickSorter.cpp
        model/sorters/QuickSorter.h
)

add_executable(1_sort ${SOURCE_FILES})

project(Tests)

set(TEST_FILES test/MainTest.cpp
        model/SorTable.cpp
        model/SorTable.h
        model/TableGenerator.cpp
        model/TableGenerator.h
        utils/NumberUtils.cpp utils/NumberUtils.h utils/Logger.h
        io/BasicIO.cpp
        io/BasicIO.h
        io/SorTableIO.cpp
        io/SorTableIO.h
        model/Table.h
        model/sorters/BaseSorter.h
        model/SingleResult.cpp
        model/SingleResult.h
        model/sorters/QuickSorter.cpp
        model/sorters/QuickSorter.h
)

add_executable(Tests ${TEST_FILES})