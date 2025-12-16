cmake_minimum_required(VERSION 3.15)
project(TerrainGen VERSION 1.0 LANGUAGES CXX C)
set(CMAKE_BUILD_TYPE Debug)

#2. FIND DEPENDENCIES: 
find_package(glfw3 3.3 REQUIRED) 
find_package(glm REQUIRED)

file(GLOB SOURCES "*.cpp" "*.c")

add_executable(terrain ${SOURCES})


target_include_directories(terrain PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 3. DEFINE EXECUTABLE: (Name your app + list source files)


# 4. CONFIGURATION: (C++ Standard)
set_target_properties(terrain PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# 5. LINKING: 
target_link_libraries(terrain PRIVATE
    glfw
    glm::glm
    ${CMAKE_DL_LIBS}
)

# 6. ASSETS: 
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
