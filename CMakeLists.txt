# cmake最低版本
cmake_minimum_required(VERSION 3.15)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 包括模板
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(common)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 項目名
project(CMakeTemplate)

# 可執行文件名
set(EXE main)

set(project_list)
get_project_list(project_list src)
list(REMOVE_ITEM project_list ${EXE})
message("src: " "${project_list}")

foreach(item ${project_list})
	add_library(${item} "")
	set(srcs)
	get_source_list(srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/${item})
	message(${item} ": " "${srcs}")
	target_sources(${item} 
		PRIVATE ${srcs}
	)
	target_include_directories(${item} PRIVATE third/spdlog-easy/include)
	# 工程分目錄
	set_property(TARGET ${item} PROPERTY FOLDER ${EXE})
endforeach()

# 生成執行文件
add_executable(${EXE} "")

target_sources(${EXE} 
        PRIVATE
        src/main.cpp
)

# 調試版本後綴名
# set_target_properties(${EXE} PROPERTIES DEBUG_POSTFIX "_debug")

add_definitions(/W4 /MP)

# 頭文件目錄
target_include_directories(${EXE}
        PRIVATE
        third/spdlog-easy/include
)

# target_link_directories(main
# )

# 項目依賴
target_link_libraries(${EXE} ${project_list})
