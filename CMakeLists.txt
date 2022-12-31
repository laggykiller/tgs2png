cmake_minimum_required(VERSION 3.3)

project(tgs2png VERSION 0.1.0 LANGUAGES C)

if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set(ZLIB_LIBRARY "${_VCPKG_INSTALLED_DIR}/x64-windows/lib/zlib.lib")
  set(ZLIB_INCLUDE_DIR "${_VCPKG_INSTALLED_DIR}/x64-windows/include/zlib.h")
  set(PNG_LIBRARY "${_VCPKG_INSTALLED_DIR}/x64-windows/lib/libpng.16.lib")
  set(PNG_PNG_INCLUDE_DIR "${_VCPKG_INSTALLED_DIR}/x64-windows/include/png.h")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  include_directories("${PROJECT_SOURCE_DIR}/winlibs")
  include_directories("${_VCPKG_INSTALLED_DIR}/x64-windows/include")
endif ()

find_package(PkgConfig REQUIRED)

if (MSVC)
  find_package(ZLIB REQUIRED)
  find_package(PNG REQUIRED)
  pkg_check_modules(RLOTTIE rlottie)
else ()
  pkg_check_modules(PNG REQUIRED libpng)
  pkg_check_modules(RLOTTIE rlottie)
endif ()

if (NOT RLOTTIE_FOUND)
  add_subdirectory("rlottie")

  set(RLOTTIE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/rlottie/inc")
  set(RLOTTIE_LIBRARY_DIRS "${PROJECT_BUILD_DIR}/rlottie")
  set(RLOTTIE_LIBRARIES "rlottie")
endif ()

option (USE_ASAN "build all executables with asan" OFF)
if (USE_ASAN)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libasan")
  endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
endif (USE_ASAN)

# binary
if (MSVC)
  add_compile_options(
      $<$<CONFIG:>:/MT> #---------|
      $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
      $<$<CONFIG:Release>:/MT> #--|
  )
  add_executable(tgs2png "tgs2png.c" "winlibs/getopt.c" "winlibs/nanosleep.c")
else ()
  add_compile_options(-Wall -Werror)
  add_executable(tgs2png "tgs2png.c")
endif ()

target_include_directories(tgs2png PUBLIC ${PNG_INCLUDE_DIRS})
target_link_directories(tgs2png PRIVATE ${PNG_LIBRARY_DIRS})

target_compile_options(tgs2png PRIVATE)
target_link_libraries(tgs2png ${RLOTTIE_LIBRARIES} ${PNG_LIBRARIES})
if (UNIX)
  target_link_libraries(tgs2png m)
endif ()

install(TARGETS tgs2png DESTINATION ${CMAKE_INSTALL_BINDIR})
