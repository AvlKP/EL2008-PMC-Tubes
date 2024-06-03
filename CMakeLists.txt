cmake_minimum_required(VERSION 3.29)

set(SOURCES
  main.c
  types.c
  files.c
)

set(HEADERS
  types.h
  files.h
)

project(
  KlinikX
  VERSION 0.1
  LANGUAGES C  
)

add_executable(${PROJECT_NAME})

find_library(RAYLIB raylib ${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib/lib)
find_path(RAYLIB_INCLUDES raylib.h ${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib/include)
if (${RAYLIB} STREQUAL RAYLIB-NOTFOUND)
  message(FATAL_ERROR "raylib tidak ditemukan.")
else()
  message(STATUS "raylib berhasil ditemukan sebagai ${RAYLIB}")
endif()

list(TRANSFORM SOURCES PREPEND "src/")
list(TRANSFORM HEADERS PREPEND "include/")

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${RAYLIB_INCLUDES}
)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${RAYLIB})