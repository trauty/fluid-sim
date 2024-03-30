cmake_minimum_required(VERSION 3.13)

set(CMAKE_GENERATOR "Ninja")

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project("fluid-sim")

file(GLOB_RECURSE sources 
    "${CMAKE_SOURCE_DIR}/src/*.c" 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/lib/glad/*.c"
)

add_executable(fluid-sim ${sources})

target_link_options(fluid-sim PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})

target_link_libraries(fluid-sim
    ${CMAKE_SOURCE_DIR}/lib/libSDL2.dll.a
)

set_property(TARGET fluid-sim PROPERTY CXX_STANDARD 17)

target_include_directories(fluid-sim PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/shaders
        ${PROJECT_BINARY_DIR}/shaders
        COMMENT "Copying shaders..."
)

add_dependencies(fluid-sim copy_resources)