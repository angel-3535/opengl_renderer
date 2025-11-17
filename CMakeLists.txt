cmake_minimum_required(VERSION 4.0)

include(FetchContent)


project(OPENGL_RENDERER C)
set(CMAKE_C_STANDARD 23) # Requires C23 standard
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

find_package(OpenGL REQUIRED)

find_package(glfw3 3.4 QUIET)
if (NOT glfw3_FOUND)
  FetchContent_Declare(
    glfw3
    GIT_REPOSITORY https://github.com/glfw/glfw
  )
  FetchContent_GetProperties(glfw3)
  if (NOT glfw3_POPULATED)
      set(FETCHCONTENT_QUIET NO)
      FetchContent_MakeAvailable(glfw3)
  endif()
endif()

# GLAD
FetchContent_Declare(
    glad
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.8.zip
)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(glad)

    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(
      glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:compatibility=4.0
    )
endif()
set_target_properties(glad PROPERTIES FOLDER "Dependencies")

# STB
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
)
FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(stb)
endif()


# CGLM
FetchContent_Declare(
    cglm
    GIT_REPOSITORY https://github.com/recp/cglm
)
FetchContent_GetProperties(cglm)
if(NOT cglm_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(cglm)
endif()





# Source files
list(APPEND   SRC_FILES 
  src/main.c 
  src/gfx/window.c
  src/gfx/shader.c
  src/gfx/vbo.c
  src/gfx/vao.c
  src/gfx/texture.c
  src/gfx/renderer.c
  src/obj/quad2d.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)

list(
  APPEND EXTRA_INCLUDES 

  "${PROJECT_SOURCE_DIR}/src"
  "${glfw3_SOURCE_DIR}/include"
  "${stb_SOURCE_DIR}"
  "${cglm_SOURCE_DIR}/include"
  "${glad_SOURCE_DIR}/glad/include"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${EXTRA_INCLUDES})


