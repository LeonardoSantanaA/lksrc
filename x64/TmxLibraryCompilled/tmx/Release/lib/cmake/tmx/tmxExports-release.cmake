#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tmx" for configuration "Release"
set_property(TARGET tmx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(tmx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/tmx.lib"
  )

list(APPEND _cmake_import_check_targets tmx )
list(APPEND _cmake_import_check_files_for_tmx "${_IMPORT_PREFIX}/lib/tmx.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
