# cmake最低版本
cmake_minimum_required(VERSION 3.15)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 包括模板
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(common)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 項目名
project(CMakeTemplate)

set(project_list)
get_project_list(project_list src)
list(REMOVE_ITEM project_list main)
message("list:" ${project_list})

foreach(item ${project_list})
	add_library(${item} "")
	set(srcs)
	get_source_list(srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/${item})
	message(${item} ":" ${${srcs}})
	target_sources(${item} 
		PRIVATE ${srcs}
	)
	target_include_directories(${item} PRIVATE ${spdlog_easy})
endforeach()

# 生成執行文件
add_executable(main "")

target_sources(main 
        PRIVATE
        src/main.cpp
)

set_target_properties(main PROPERTIES DEBUG_POSTFIX "_debug")

add_definitions(/W4 /MP)

# 頭文件目錄
target_include_directories(main
        PRIVATE
        third/spdlog-easy/include
)

# target_link_directories(main
# )

target_link_libraries(main ${project_list})
