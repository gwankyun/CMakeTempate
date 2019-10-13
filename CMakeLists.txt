# cmake最低版本
cmake_minimum_required(VERSION 3.15)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 包括模板
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(common)
include(map)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 項目名
project(CMakeTemplate)

map_create(m)
map_add(m a 1)
message("map_add: " "${m_key}")
map_get(m a r)
message("map_get: " ${r})
map_size(m r)
message("map_size: " ${r})
map_contain(m a r)
message("map_contain: " ${r})
map_contain(m b r)
message("map_contain: " ${r})
map_remove(m a)
message("map_remove: " "${m_key}")
map_add(m a 1)
map_add(m b 2)
map_add(m c 3)
map_clear(m)
message("map_clear: " "${m_key}")

# 可執行文件名
set(EXE main)

set(MAIN_DIR src)
set(MAIN_FILE main)

function(get_library _src _out)
	file(GLOB srcs ${_src}/*)
	set(out)
	foreach(item ${srcs})
		get_filename_component(name_we ${item} NAME_WE)
		list(APPEND out ${name_we})
	endforeach()
	list(REMOVE_DUPLICATES out)
	set(${_out} ${out} PARENT_SCOPE)
endfunction()

set(project_list)

file(GLOB_RECURSE srcs src/*.cpp)
foreach(item ${srcs})
	get_filename_component(dir ${item} DIRECTORY)
	get_filename_component(name_we ${item} NAME_WE)
	get_filename_component(dir_name ${dir} NAME)
	list(APPEND project_list ${dir})
	string(COMPARE NOTEQUAL ${dir_name} ${name_we} a)
	string(COMPARE NOTEQUAL ${MAIN_FILE} ${name_we} b)
	if(a AND b)
		list(APPEND project_list ${dir}/${name_we})		
	endif()
endforeach()

function(get_folder _src _name _out)
	string(REGEX MATCH "(${MAIN_DIR}/.*)${_name}.*$" m ${_src})
	set(out ${CMAKE_MATCH_1})
	string(REGEX REPLACE "/([a-z]+)/" "/\\1_/" out ${out})
	set(${_out} ${out} PARENT_SCOPE)
endfunction()

list(REMOVE_DUPLICATES project_list)
message("project_list: ${project_list}")
foreach(item ${project_list})
	get_filename_component(name ${item} NAME)
	get_filename_component(dir ${item} DIRECTORY)
	get_filename_component(dir_name ${dir} NAME)
	set(proj)
	set(src)
	set(lib)
	if(${name} STREQUAL ${MAIN_DIR})
		set(proj ${EXE})
		add_executable(${proj} "")
		set(src ${MAIN_DIR}/${MAIN_FILE}.cpp)
		get_library(${item} lib)
		list(REMOVE_ITEM lib ${MAIN_FILE})
	else()
		add_library(${name} "")
		set(proj ${name})
		if(IS_DIRECTORY ${item})
			file(GLOB src ${item}/${name}.*)
			get_library(${item} lib)
			list(REMOVE_ITEM lib ${name})
		else()
			file(GLOB src ${item}.*)
		endif()
		get_folder(${item} ${name} folder)
		set_property(TARGET ${name} PROPERTY FOLDER ${folder})
	endif()
	message("proj:" ${proj})
	message("src: ${src}")
	message("lib: ${lib}")
	target_sources(${proj}
		PRIVATE ${src}
	)
	target_include_directories(${proj} 
		PRIVATE
			third/spdlog-easy/third/spdlog/include
			third/spdlog-easy/include
	)
	target_link_libraries(${proj} ${lib})
endforeach()

# 調試版本後綴名
# set_target_properties(${EXE} PROPERTIES DEBUG_POSTFIX "_debug")

add_definitions(/W4 /MP)
