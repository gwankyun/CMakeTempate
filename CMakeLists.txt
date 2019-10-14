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

# 可執行文件名
set(EXE main)

set(MAIN_DIR src)
set(MAIN_FILE main)

function(get_filename_component_list _var _FileNameList _mode)
	set(out)
	foreach(item ${_FileNameList})
		get_filename_component(result ${item} ${_mode})
		list(APPEND out ${result})
	endforeach()
	set(${_var} ${out} PARENT_SCOPE)
endfunction()

function(string_regex_replace_all _regular _replace _output _input)
	string(REGEX REPLACE ${_regular} ${_replace} out ${_input})
	string(COMPARE NOTEQUAL ${_input} ${out} r)
	while(${r})
		set(_input ${out})
		string(REGEX REPLACE ${_regular} ${_replace} out ${input})
		string(COMPARE NOTEQUAL ${_input} ${out} r)
	endwhile()
	set(${_output} ${out} PARENT_SCOPE)
endfunction()

function(update_folder _folder _var)
	if(${MSVC_VERSION} GREATER_EQUAL 1920)
		set(${_var} ${_folder} PARENT_SCOPE)
	else()
		string(REGEX REPLACE "^([a-z]+)/" "\\1_/" _folder ${_folder})
		string(REGEX REPLACE "/([a-z]+)$" "/\\1_" _folder ${_folder})
		string_regex_replace_all("/([a-z]+)/" "/\\1_/" out ${_folder})
		set(_folder ${out})
		set(${_var} ${_folder} PARENT_SCOPE)
	endif()
endfunction()

set(project_list)
file(GLOB_RECURSE project_list src/*)
get_filename_component_list(dir_list "${project_list}" DIRECTORY)
list(REMOVE_DUPLICATES dir_list)

set(inc_dir
	third/spdlog-easy/third/spdlog/include
	third/spdlog-easy/include
)

foreach(item ${dir_list})
	message(${item})
	file(GLOB current ${item}/* ${item}/*.cpp)
	set(name)
	get_filename_component(name ${item} NAME)
	message("name: " ${name})
	message(" ${current}")
	set(lib)
	get_filename_component_list(lib " ${current}" NAME_WE)
	list(REMOVE_DUPLICATES lib)
	set(proj)
	set(src)
	list(FIND lib main out)
	if(NOT (${out} EQUAL -1))
		set(proj main)
		message(" main")
		add_executable(${proj} "")
	else()
		set(proj ${name})
		message(" sub")
		add_library(${proj} "")

		string(REGEX MATCH "(${MAIN_DIR}/.*)${proj}.*$" _ ${item})
		set(folder ${CMAKE_MATCH_1})
		update_folder(${folder} folder)
		message(" folder: " ${folder})
		set_property(TARGET ${proj} PROPERTY FOLDER ${folder})
	endif()

	list(REMOVE_ITEM lib ${proj})
	file(GLOB src ${item}/${proj}.*)
	list(REMOVE_ITEM lib ${proj})

	target_link_libraries(${proj} ${lib})
	target_sources(${proj} PRIVATE ${src})
	target_include_directories(${proj} PRIVATE ${inc_dir})

	message(" lib: ${lib}")

	foreach(i ${lib})
		if(NOT (IS_DIRECTORY ${item}/${i}))
			set(proj ${i})
			message(" standone lib: " ${i})
			add_library(${proj} "")
			file(GLOB src ${item}/${proj}.*)

			set(folder)
			if(${name} STREQUAL src)
				set(folder ${name}_)
			else()
				string(REGEX MATCH "(${MAIN_DIR}/.*)$" _ ${item})
				set(folder ${CMAKE_MATCH_1})
				update_folder(${folder} folder)
			endif()

			target_sources(${proj} PRIVATE ${src})
			target_include_directories(${proj} PRIVATE ${inc_dir})
			set_property(TARGET ${proj} PROPERTY FOLDER ${folder})
		endif()
	endforeach()
endforeach()

# 調試版本後綴名
# set_target_properties(${EXE} PROPERTIES DEBUG_POSTFIX "_debug")

if(${MSVC})
	add_definitions(/W4 /MP)
endif()
