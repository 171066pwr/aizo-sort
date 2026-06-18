cmake_minimum_required(VERSION 3.30)
project(1_sort)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp
        model/SorTable.cpp
        model/SorTable.h
        model/generator/TableGenerator.h
        utils/NumberUtils.cpp utils/NumberUtils.h utils/Logger.h
        io/BasicIO.cpp
        io/BasicIO.h
        io/SorTableIO.h
        model/Table.h
        io/InvalidFileException.h
        model/sorters/BaseSorter.h
        model/sorters/QuickSorter.h
        model/sorters/InsertionSorter.h
        model/sorters/HeapSorter.h
        model/sorters/ShellSorter.h
        model/runner/Runner.cpp
        model/runner/Runner.h
        model/runner/BatchResult.h
        model/config/RunnerConfig.h
        model/config/PreSortMode.h
        model/sorters/SorterFactory.h
        model/config/SorterConfig.h
        model/config/DatasetConfig.h
        model/runner/Summary.h
        model/generator/BaseGenerator.h
        model/runner/RunResult.h
        model/config/DataTypeConfig.h
        io/Serializable.h
        io/Printable.h
        model/config/DisplayDataConfig.h
        model/config/GlobalConfig.h
        io/ConfigIO.cpp
        io/ConfigIO.h
)

add_executable(1_sort ${SOURCE_FILES})

# Static linking for MinGW/GCC
if (MINGW)
    # Static link all libraries
    target_link_options(${PROJECT_NAME} PRIVATE -static)
    target_link_options(${PROJECT_NAME} PRIVATE -static -lpthread)
endif()

# Increase stack size to 16MBs
if(MSVC)
    # MSVC: /STACK:size (size in bytes)
    # 16 MB = 16 * 1024 * 1024 = 16777216
    target_link_options(${PROJECT_NAME} PRIVATE "/STACK:16777216")

elseif(MINGW OR MSYS OR CYGWIN)
    # MinGW/GCC: -Wl,--stack,size (size in bytes)
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,--stack,16777216")

elseif(UNIX AND NOT APPLE)
    # Linux: -Wl,-z,stack-size=size (size in bytes)
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-z,stack-size=16777216")
endif()

project(Tests)

set(TEST_FILES test/MainTest.cpp
        model/SorTable.cpp
        model/SorTable.h
        model/generator/TableGenerator.h
        utils/NumberUtils.cpp utils/NumberUtils.h utils/Logger.h
        io/BasicIO.cpp
        io/BasicIO.h
        io/SorTableIO.h
        model/Table.h
        model/sorters/BaseSorter.h
        model/sorters/QuickSorter.h
        model/sorters/HeapSorter.h
        model/sorters/ShellSorter.h
        model/runner/Runner.cpp
        model/runner/Runner.h
        model/runner/BatchResult.h
        model/config/RunnerConfig.h
        model/sorters/SorterFactory.h
        model/config/SorterConfig.h
        model/config/DatasetConfig.h
        model/runner/Summary.h
        model/generator/BaseGenerator.h
        model/runner/RunResult.h
        model/config/DataTypeConfig.h
        io/Serializable.h
        io/Printable.h
        model/config/DisplayDataConfig.h
        model/config/GlobalConfig.h
        io/ConfigIO.cpp
        io/ConfigIO.h
)

add_executable(Tests ${TEST_FILES})

# Static linking for MinGW/GCC
if (MINGW)
    # Static link all libraries
    target_link_options(${PROJECT_NAME} PRIVATE -static)
    target_link_options(${PROJECT_NAME} PRIVATE -static -lpthread)
endif()