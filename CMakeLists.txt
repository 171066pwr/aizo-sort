cmake_minimum_required(VERSION 3.30)
project(1_sort)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp
        model/SorTable.cpp
        model/SorTable.h
        model/generator/TableGenerator.cpp
        model/generator/TableGenerator.h
        utils/NumberUtils.cpp utils/NumberUtils.h utils/Logger.h
        io/BasicIO.cpp
        io/BasicIO.h
        io/SorTableIO.h
        model/Table.h
        io/InvalidFileException.h
        model/sorters/BaseSorter.h
        model/runner/SingleResult.h
        model/sorters/QuickSorter.h
        model/sorters/InsertionSorter.h
        model/sorters/HeapSorter.h
        model/sorters/ShellSorter.h
        model/runner/Runner.cpp
        model/runner/Runner.h
        model/runner/BatchResult.h
        model/config/RunnerConfig.h
        model/DataType.h
        model/config/PreSortMode.h
        model/sorters/SorterFactory.h
        model/config/SorterConfig.h
        model/config/DatasetConfig.h
        model/runner/Summary.h
        model/runner/BaseRunner.h
        model/runner/FileRunner.cpp
        model/runner/FileRunner.h
        model/runner/SorterArray.h
        model/generator/BaseGenerator.h
        model/generator/BaseGenerator.cpp
)

add_executable(1_sort ${SOURCE_FILES})

project(Tests)

set(TEST_FILES test/MainTest.cpp
        model/SorTable.cpp
        model/SorTable.h
        model/generator/TableGenerator.cpp
        model/generator/TableGenerator.h
        utils/NumberUtils.cpp utils/NumberUtils.h utils/Logger.h
        io/BasicIO.cpp
        io/BasicIO.h
        io/SorTableIO.h
        model/Table.h
        model/sorters/BaseSorter.h
        model/runner/SingleResult.h
        model/sorters/QuickSorter.h
        model/sorters/HeapSorter.h
        model/sorters/ShellSorter.h
        model/runner/Runner.cpp
        model/runner/Runner.h
        model/runner/BatchResult.h
        model/config/RunnerConfig.h
        model/DataType.h
        model/sorters/SorterFactory.h
        model/config/SorterConfig.h
        model/config/DatasetConfig.h
        model/runner/Summary.h
        model/runner/BaseRunner.h
        model/runner/FileRunner.cpp
        model/runner/FileRunner.h
        model/runner/SorterArray.h
        model/generator/BaseGenerator.h
        model/generator/BaseGenerator.cpp
)

add_executable(Tests ${TEST_FILES})