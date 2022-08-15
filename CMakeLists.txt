cmake_minimum_required(VERSION 3.2...3.5)

project(app LANGUAGES CXX)

# ----------------------------------------------------------------------

find_package(Threads)

# ----------------------------------------------------------------------

# add_subdirectory(src)
add_subdirectory(lib/server)

# ----------------------------------------------------------------------

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(JSONCPP_WITH_TESTS OFF CACHE BOOL "")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/json/jsoncpp/ EXCLUDE_FROM_ALL)
get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})

set(JSONCPP_INCLUDE_DIRS
	"${CMAKE_CURRENT_SOURCE_DIR}/lib/json/jsoncpp/include")
set(JSONCPP_LIBRARIES jsoncpp_lib)

# ----------------------------------------------------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/test/googletest/ EXCLUDE_FROM_ALL)
get_target_property(GOOGLETEST_INC_PATH gtest INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${GOOGLETEST_INC_PATH})

set(GOOGLETEST_INCLUDE_DIRS
	"${CMAKE_CURRENT_SOURCE_DIR}/lib/test/googletest/googletest/include")

set(GOOGLETEST_LIBRARIES gtest)

# ----------------------------------------------------------------------

add_executable(${PROJECT_NAME} main.cpp)
# target_include_directories(${PROJECT_NAME} PRIVATE "${JSONCPP_INCLUDE_DIRS}" "${GOOGLETEST_INCLUDE_DIRS}")
# target_link_libraries(${PROJECT_NAME}  ${JSONCPP_LIBRARIES} ${GOOGLETEST_LIBRARIES} server Threads::Threads)

target_link_libraries(${PROJECT_NAME} 
Threads::Threads 
${JSONCPP_LIBRARIES} 
${GOOGLETEST_LIBRARIES}
server)

# ${CMAKE_SOURCE_DIR}/build/src/Debug/server.lib