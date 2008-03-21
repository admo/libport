##
## ConfigureVersionInfo.cmake: This file is part of libport.
## Copyright (C) Gostai S.A.S., 2006-2008.
##
## This software is provided "as is" without warranty of any kind,
## either expressed or implied, including but not limited to the
## implied warranties of fitness for a particular purpose.
##
## See the LICENSE file for more information.
## For comments, bug reports and feedback: http://www.urbiforge.com
##

if(NOT COMMAND CONFIGURE_VERSION_INFO)

# Generate version information in 'output' file and add it to the 'sources'
# list variable.
macro(CONFIGURE_VERSION_INFO output deps)
  add_custom_command(
    OUTPUT ${output}.tmp
    COMMAND ${CMAKE_AUX_DIR}/revision
    ARGS ${output}.tmp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "${CMAKE_COMMAND} -E cmake_echo_color "
    "--switch=${CMAKE_MAKEFILE_COLOR} --cyan "
    "Generating version information time stamp" VERBATIM)
  add_custom_command(
    OUTPUT ${output}
    COMMAND ${CMAKE_AUX_DIR}/move-if-change
    ARGS ${output}.tmp ${output}
    DEPENDS ${output}.tmp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "${CMAKE_COMMAND} -E cmake_echo_color "
    "--switch=${CMAKE_MAKEFILE_COLOR} --cyan "
    "Generating version information" VERBATIM)
  set_source_files_properties(${deps}
    PROPERTIES OBJECT_DEPENDS ${output})
  set_directory_properties(PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES ${output}
    ADDITIONAL_MAKE_CLEAN_FILES ${output}.tmp)
endmacro(CONFIGURE_VERSION_INFO)

endif(NOT COMMAND CONFIGURE_VERSION_INFO)
