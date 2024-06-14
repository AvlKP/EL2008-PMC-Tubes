cmake_minimum_required(VERSION 3.29)

set(SOURCES
  main.c
  types.c
  files.c
  gui.c
  pasienTab.c
)

set(HEADERS
  types.h
  files.h
  gui.h
  pasienTab.h
)

project(
  KlinikX
  VERSION 0.1
  LANGUAGES C  
)

add_executable(${PROJECT_NAME})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED IMPORTED_TARGET gtk4)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::GTK)

find_program(GLIB_COMPILE_RESOURCES glib-compile-resources REQUIRED)
set(GRESOURCE_C klinikx.gresource.c)
set(GRESOURCE_XML klinikx.gresource.xml)

add_custom_command(
  OUTPUT ${GRESOURCE_C}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res
  COMMAND ${GLIB_COMPILE_RESOURCES}
  ARGS
    ${CMAKE_SOURCE_DIR}/res/${GRESOURCE_XML}
    --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C} 
    --generate-source
  VERBATIM
  MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/res/${GRESOURCE_XML}
)

add_custom_target(
  ${PROJECT_NAME}-resource
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)

list(TRANSFORM SOURCES PREPEND "src/")
list(TRANSFORM HEADERS PREPEND "include/")

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)
target_sources(${PROJECT_NAME} 
  PRIVATE ${SOURCES} 
  PRIVATE ${HEADERS}
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})
set_source_files_properties(
  ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
  PROPERTIES GENERATED TRUE)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-resource)