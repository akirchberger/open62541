SET(SOURCE_GROUP ${SOURCE_GROUP}\\patmos)

ua_add_architecture("patmos")

if("${UA_ARCHITECTURE}" STREQUAL "patmos")

option(UA_PATMOS_WCET "Enable Patmos WCET" OFF)

ua_architecture_add_definitions(-Wno-error)

ua_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_clock.c)
ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_architecture_functions.c)

#
# Add here below all the things that are specific for your architecture
#

#You can use the following available CMake functions:

#ua_include_directories() include some directories specific to your architecture when compiling the open62541 stack
#ua_architecture_remove_definitions() remove compiler flags from the general ../../CMakeLists.txt file that won't work with your architecture
#ua_architecture_add_definitions() add compiler flags that your architecture needs
#ua_architecture_append_to_library() add libraries to be linked to the open62541 that are needed by your architecture
#ua_add_architecture_header() add header files to compilation (Don't add the file ua_architecture.h)
#ua_add_architecture_file() add .c files to compilation

endif()
