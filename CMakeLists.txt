cmake_minimum_required(VERSION 2.8.6)

project(CmdOptionTest)

include ("${PROJECT_SOURCE_DIR}/CompilerOption.cmake")
include ("${PROJECT_SOURCE_DIR}/TargetOption.cmake")

# ���ɿ��ļ�
add_subdirectory (src)
add_subdirectory (test)
