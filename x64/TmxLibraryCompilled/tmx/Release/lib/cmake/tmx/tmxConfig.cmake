include(CMakeFindDependencyMacro)
find_dependency(LibXml2)

if(ON AND NOT False)
  find_dependency(ZLIB)
endif()

if(OFF)
  find_dependency(zstd)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/tmxExports.cmake")
