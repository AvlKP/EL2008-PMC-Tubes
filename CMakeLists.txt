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

list(TRANSFORM SOURCES PREPEND "src/")
list(TRANSFORM HEADERS PREPEND "include/")

set(nappgui_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/NAppGUI/cmake)
find_package(nappgui)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${NAPPGUI_INCLUDE_DIR}
)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${NAPPGUI_LIBRARIES})
# set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)