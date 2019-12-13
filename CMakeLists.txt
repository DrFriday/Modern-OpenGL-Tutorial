cmake_minimum_required(VERSION 3.10)

project(modern-opengl-tutorial CXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (CreateTreeVS)
include (CTest)

#set(CMAKE_DEBUG_POSTFIX "_d")

set(targetDir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${targetDir})

option (BUILD_TESTS "tests" OFF)

# ==========================================================================================================
# Configuring external library downloads
# ==========================================================================================================
configure_file(CMakeLists.txt.in external-libs-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/external-libs-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/external-libs-download" )

# ==========================================================================================================
# glew lib
# ==========================================================================================================
add_subdirectory("${CMAKE_BINARY_DIR}/glew-src/build/cmake"
                 "${CMAKE_BINARY_DIR}/glew-build")

# ==========================================================================================================
# OpenGL Mathematics (GLM) 
# ==========================================================================================================
add_subdirectory("${CMAKE_BINARY_DIR}/glm-src"
                 "${CMAKE_BINARY_DIR}/glm-build")

# ==========================================================================================================
# SDL 2
# ==========================================================================================================
add_subdirectory("${CMAKE_BINARY_DIR}/sdl2-src"
                 "${CMAKE_BINARY_DIR}/sdl2-build")

# ==========================================================================================================
# Main Program
# ==========================================================================================================

set (SOURCES
)

set (HEADERS
)

set (MAIN
    src/main.cpp
)

if (MSVC)
    assign_source_group(${SOURCES} ${HEADERS} ${MAIN})
endif ()

set(EXEC_NAME myopengl)

add_executable(${EXEC_NAME} WIN32
    ${SOURCES}
    ${HEADERS}
    ${MAIN}
)

target_include_directories(${EXEC_NAME} PRIVATE
    include
	${CMAKE_BINARY_DIR}/glew-src/include
)

target_link_libraries(${EXEC_NAME}
	SDL2main
	SDL2
	glm
	glew
)

set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 17)

if (MSVC)
    # https://stackoverflow.com/questions/7304625/how-do-i-change-the-startup-project-of-a-visual-studio-solution-via-cmake/37994396#37994396
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXEC_NAME})
endif ()

# ==========================================================================================================
# Google Test
# ==========================================================================================================
if (BUILD_TESTS)
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) 

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

set(UNIT_TEST_SOURCES
    test/TestProject.cpp
)

if (MSVC)
    assign_source_group(${UNIT_TEST_SOURCES})
endif ()

set(TEST_EXEC_NAME UnitTestRunner)
add_executable(${TEST_EXEC_NAME}
	${SOURCES}
	${HEADERS}
	${UNIT_TEST_SOURCES}
)

target_include_directories(${TEST_EXEC_NAME} PRIVATE
	include
)

target_link_libraries(${TEST_EXEC_NAME}
	gtest_main
)

set_property(TARGET ${TEST_EXEC_NAME} PROPERTY CXX_STANDARD 17)
add_test(NAME TestProject COMMAND ${TEST_EXEC_NAME})

endif()
# ==========================================================================================================
# Clang Format
# ==========================================================================================================

find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("Found clang-format at " ${CLANG_FORMAT})

    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${SOURCES} ${HEADERS} ${MAIN} ${UNIT_TEST_SOURCES})
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS}
    )

    # Comment this out so every time I build it doesn't touch all the files
    # add_dependencies(${EXEC_NAME} ClangFormat)
else()
    message("Couldn't find clang-format")
endif()
