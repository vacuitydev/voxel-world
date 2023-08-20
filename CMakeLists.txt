# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OpenGLProject")
set(CMAKE_CXX_STANDARD 20)
add_executable("OpenGlProject" "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_subdirectory(glad/)
target_link_libraries("OpenGlProject" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib"  glad)
target_include_directories("OpenGlProject" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/" "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/ucrt")

