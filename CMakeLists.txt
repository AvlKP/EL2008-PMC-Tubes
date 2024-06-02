cmake_minimum_required(VERSION 3.29)

set(SOURCES
  main.c
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

find_library(XLSXIO_READ xlsxio_read ${CMAKE_CURRENT_SOURCE_DIR}/lib/xlsxio)
find_path(XLSXIO_READ_INCLUDES xlsxio_read.h ${CMAKE_CURRENT_SOURCE_DIR}/lib/xlsxio)
if (${XLSXIO_READ} STREQUAL XLSXIO_READ-NOTFOUND)
  message(FATAL_ERROR "xlsxio tidak ditemukan.")
else()
  message(STATUS "xlsxio berhasil ditemukan sebagai ${XLSXIO_READ}")
endif()

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
  PRIVATE ${XLSXIO_READ_INCLUDES}
  PRIVATE ${RAYLIB_INCLUDES}
)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${XLSXIO_READ} ${RAYLIB})