# cmake最低版本
cmake_minimum_required(VERSION 3.15)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 包括模板
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(common)
include(map)
include(CMakePrintHelpers)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 項目名
project(CMakeTemplate)

# 源目錄
set(MAIN_DIR src)

# 可執行文件名
set(MAIN_FILE main)

find_package(SPDLOG_EASY)
if(SPDLOG_EASY_FOUND)
	cmake_print_variables(SPDLOG_EASY_FOUND)	
endif()

set(CMAKE_FIND_LIBRARY_PREFIXES lib)
set(BOOST_ROOT C:/local/boost_1_71_0)
find_package(Boost COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
	cmake_print_variables(Boost_INCLUDE_DIRS)	
	cmake_print_variables(Boost_LIBRARIES)	
	cmake_print_variables(Boost_LIB_VERSION)	
endif()

# 引用目錄
set(inc_dir
	${SPDLOG_EASY_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
)

set(target_list)
get_target_list(target_list ${MAIN_DIR} ${MAIN_FILE})

foreach(item ${target_list})
	cmake_print_variables(item)

	get_target_property(src ${item} SRC)
	cmake_print_variables(src)
	target_sources(${item} PRIVATE ${src})

	target_include_directories(${item} PRIVATE ${inc_dir})

	get_target_property(lib ${item} LIB)
	if(lib)
		cmake_print_variables(lib)
		target_link_libraries(${item} ${lib})
	endif()

	get_target_property(folder ${item} FOLDER)
	if(folder)
		cmake_print_variables(folder)
	endif()

	message("")
endforeach()

# 調試版本後綴名
# set_target_properties(${EXE} PROPERTIES DEBUG_POSTFIX "_debug")

if(${MSVC})
	add_definitions(/W4 /MP)
endif()
