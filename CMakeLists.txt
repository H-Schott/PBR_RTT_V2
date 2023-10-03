cmake_minimum_required (VERSION 3.1)

project(PBR_RTT_V2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS_RELEASE "-Ox")
endif()

# set path to dependencies
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(ZLIB_LIBRARIES zlibstatic)
set(BUILD_STATIC_LIB ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
set(USE_STATIC_CRT ON)
set(BUILD_SHARED_LIBS OFF)
add_definitions(-DGLEW_STATIC)
add_subdirectory(dependency/assimp EXCLUDE_FROM_ALL)
add_subdirectory(dependency/GeometryTools EXCLUDE_FROM_ALL)
include_directories(dependency/GeometryTools/code)
include_directories(dependency/eigen)

# Add dependencies
find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# ------------------------------------------------------------------------------
set(DEMO PBR_RTT_V2)
set(SRC_DIR code)
include_directories(${SRC_DIR})
aux_source_directory(${SRC_DIR} SRC_FILES)
if (WIN32)
	add_executable(${DEMO} 
		${IMGUI_SRC_FILES} 
		${SRC_FILES}
		${SRC_DIR}/color.hpp
		${SRC_DIR}/image.hpp
		${SRC_DIR}/mesh.hpp
		${SRC_DIR}/ray.hpp
		${SRC_DIR}/stb_image_write.h
		${SRC_DIR}/stb_image.h
	)
else()
	add_executable(${DEMO} 
		${IMGUI_SRC_FILES} 
		${SRC_FILES}
		${SRC_DIR}/color.hpp
		${SRC_DIR}/image.hpp
		${SRC_DIR}/mesh.hpp
		${SRC_DIR}/ray.hpp
		${SRC_DIR}/stb_image_write.h
		${SRC_DIR}/stb_image.h
	)
endif()

# data folder copy on post build
set(DATA_DIR data)
add_custom_command(
	TARGET ${DEMO} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/${DATA_DIR}
			${CMAKE_CURRENT_BINARY_DIR}/${DATA_DIR}
)
target_link_libraries(${DEMO}
	assimp
	GeometryTools
)
if (!WIN32)
	target_link_libraries(${DEMO} "stdc++fs")
endif()
target_compile_definitions(
    ${DEMO} PRIVATE
    -DPATH_TO_SRC_DIRECTORY="${CMAKE_SOURCE_DIR}/"
)
