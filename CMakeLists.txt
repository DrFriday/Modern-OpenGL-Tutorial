cmake_minimum_required(VERSION 3.14)

project(modern-opengl-tutorial CXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (CreateTreeVS)
include (CTest)
include (FetchContent)

set(targetDir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${targetDir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${targetDir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${targetDir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${targetDir})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${targetDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${targetDir})

option (BUILD_TESTS "tests" OFF)

# ==========================================================================================================
# glew lib
# ==========================================================================================================
FetchContent_Declare(
    glew
    URL               https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.zip
)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_Populate(glew)
    add_subdirectory(
        ${glew_SOURCE_DIR}/build/cmake
        ${glew_BINARY_DIR}
    )
endif()

# ==========================================================================================================
# OpenGL Mathematics (GLM)
# ==========================================================================================================
FetchContent_Declare(
    glm
    GIT_REPOSITORY    https://github.com/g-truc/glm
    GIT_TAG           0.9.9.7
)

# ==========================================================================================================
# SDL 2
# ==========================================================================================================
FetchContent_Declare(
    sdl2
    URL               https://www.libsdl.org/release/SDL2-2.0.10.zip
)

# ==========================================================================================================
# Downloading Content
# ==========================================================================================================
FetchContent_MakeAvailable(glm sdl2)

# ==========================================================================================================
# Header only libraries
# ==========================================================================================================
set(HEADER_ONLY_LIBS
    "dep/stb_image.h" # stb image loading
)

# ==========================================================================================================
# Main Program
# ==========================================================================================================

set (SOURCES
    "src/Display.cpp"
    "src/Shader.cpp"
    "src/Mesh.cpp"
    "src/Texture.cpp"
    "src/Transform.cpp"
)

set (HEADERS
    "include/Display.hpp"
    "include/Shader.hpp"
    "include/Mesh.hpp"
    "include/Texture.hpp"
    "include/Transform.hpp"
)

set (MAIN
    "src/main.cpp"
)

if (MSVC)
    assign_source_group(${SOURCES} ${HEADERS} ${MAIN} ${HEADER_ONLY_LIBS})
endif ()

set(EXEC_NAME myopengl)

add_executable(${EXEC_NAME} WIN32
    ${SOURCES}
    ${HEADERS}
    ${HEADER_ONLY_LIBS}
    ${MAIN}
)

target_include_directories(${EXEC_NAME} PRIVATE
    "include"
    ${CMAKE_BINARY_DIR}/_deps/glew-src/include
    "dep"
)

target_link_libraries(${EXEC_NAME}
    SDL2main
    SDL2
    glm
    glew
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET ${EXEC_NAME} PROPERTY USE_FOLDERS ON)
set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 17)

if (MSVC)
    # https://stackoverflow.com/questions/7304625/how-do-i-change-the-startup-project-of-a-visual-studio-solution-via-cmake/37994396#37994396
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXEC_NAME})
endif ()

# ==========================================================================================================
# Google Test
# ==========================================================================================================
if (BUILD_TESTS)
# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

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

