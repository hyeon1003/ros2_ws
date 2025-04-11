# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_pub1-1_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED pub1-1_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(pub1-1_FOUND FALSE)
  elseif(NOT pub1-1_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(pub1-1_FOUND FALSE)
  endif()
  return()
endif()
set(_pub1-1_CONFIG_INCLUDED TRUE)

# output package information
if(NOT pub1-1_FIND_QUIETLY)
  message(STATUS "Found pub1-1: 0.0.0 (${pub1-1_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'pub1-1' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${pub1-1_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(pub1-1_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${pub1-1_DIR}/${_extra}")
endforeach()
