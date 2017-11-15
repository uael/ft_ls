cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(ft_ls C)
get_directory_property(ft_ls_PARENT PARENT_DIRECTORY)

set(BUILD_SHARED_LIBS OFF)

set(ft_ls_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(ft_ls_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(ft_ls_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

option(COVERAGE "Turn on COVERAGE support" OFF)
if (COVERAGE AND NOT MSVC)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif ()

if (NOT ft_ls_PARENT AND EXISTS ${ft_ls_TEST_DIR})
  enable_testing()
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
  set(ft_ls_ENABLE_TEST ON)
else ()
  set(ft_ls_ENABLE_TEST OFF)
endif ()

set(ft_ls_HDR ${ft_ls_INC_DIR}/ft_ls.h)
file(GLOB_RECURSE ft_ls_HDRS ${ft_ls_HDRS}
  ${ft_ls_INC_DIR}/ft_ls/*.h)
file(GLOB_RECURSE ft_ls_SRCS ${ft_ls_SRCS}
  ${ft_ls_SRC_DIR}/*.c)

add_executable(ft_ls ${ft_ls_HDR} ${ft_ls_HDRS} ${ft_ls_SRCS})
set_property(TARGET ft_ls PROPERTY C_STANDARD 90)
target_include_directories(ft_ls PUBLIC ${ft_ls_INC_DIR})
target_compile_definitions(ft_ls PRIVATE U_COMPILE)

target_compile_definitions(ft_ls
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>
  PRIVATE API_COMPILE)
if (MSVC)
  target_compile_options(ft_ls
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(ft_ls
    PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
    PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
