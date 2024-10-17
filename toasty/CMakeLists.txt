cmake_minimum_required(VERSION 3.5)

file (GLOB_RECURSE SOURCES src/*.cpp)
add_library (Toasty ${SOURCES})

target_include_directories(Toasty
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

				// One directory up from ${CMAKE_CURRENT_SOURCE_DIR} is ${CMAKE_CURRENT_SOURCE_DIR}/..
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Toasty PRIVATE imgui)
