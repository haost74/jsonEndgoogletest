# Install script for directory: C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/app")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/json" TYPE FILE FILES
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/allocator.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/assertions.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/config.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/forwards.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/json.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/json_features.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/reader.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/value.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/version.h"
    "C:/Users/rcif7/OneDrive/Рабочий стол/C++/wj/lib/json/jsoncpp/include/json/writer.h"
    )
endif()

