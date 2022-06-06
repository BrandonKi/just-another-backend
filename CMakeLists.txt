cmake_minimum_required(VERSION 3.0.0)
project(jab VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 23)

cmake_policy(SET CMP0069 NEW)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_library(jab_lib OBJECT
    ${CMAKE_CURRENT_SOURCE_DIR}/src/jab.cpp	
    ${CMAKE_CURRENT_SOURCE_DIR}/src/module_builder.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/jit_env.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/context.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/arch/x86_64/mdir.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/arch/x86_64/mdir_gen.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/arch/x86_64/encode.cpp
	
)

target_include_directories(jab_lib
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

set(cmd_driver_src
	$<TARGET_OBJECTS:jab_lib>
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(jab ${cmd_driver_src})

target_include_directories(jab
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

set(test_driver_src
	$<TARGET_OBJECTS:jab_lib>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_tests.cpp
) 

add_executable(jab_tests ${test_driver_src})

target_include_directories(jab_tests
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

if(${LTO})
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result)
    if(result)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endif()

if(MSVC)
    target_compile_options(jab PRIVATE /W3)
    target_compile_options(jab_tests PRIVATE /W3)
else()
    target_compile_options(jab PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(jab_tests PRIVATE -Wall -Wextra -pedantic)
endif()
