# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# # Enable Hot Reload for MSVC compilers if supported.
# if (POLICY CMP0141)
#   cmake_policy(SET CMP0141 NEW)
#   set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
# endif()

project ("OpenGLProject")
set(CMAKE_CXX_STANDARD 23)
set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/shaders")
if(MSVC)
    set(SHADER_BINARY_DIR "${CMAKE_BINARY_DIR}/Debug/shaders")
else()
    set(SHADER_BINARY_DIR "${CMAKE_BINARY_DIR}/shaders")
endif()
set(IMAGES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/images")
if(MSVC)
    set(IMAGES_BINARY_DIR "${CMAKE_BINARY_DIR}/Debug/images")
else()
    set(IMAGES_BINARY_DIR "${CMAKE_BINARY_DIR}/images")
endif()
SET(OPENGL_LINK_FLAGS "-lglfw3 -lGL -lopengl -lopengl32 -lX11 -lpthread -lXrandr -lXi -ldl")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${OPENGL_LINK_FLAGS}")
add_subdirectory(glad/)
file(CREATE_LINK "${SHADER_SOURCE_DIR}" "${SHADER_BINARY_DIR}" SYMBOLIC)
file(CREATE_LINK "${IMAGES_SOURCE_DIR}" "${IMAGES_BINARY_DIR}" SYMBOLIC)

add_executable("OpenGlProject" "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" ${SHADER_SOURCE_DIR})
add_link_options(${OPENGL_LINK_FLAGS})
target_link_libraries("OpenGlProject" PRIVATE "${CMAKE_SOURCE_DIR}/lib/glfw3.lib"  glad)
target_include_directories("OpenGlProject" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/" shaders)