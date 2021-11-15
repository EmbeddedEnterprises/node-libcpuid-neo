#required because of CMP0076 (target_sources behaviour), might be necessary in the future
cmake_minimum_required(VERSION 3.13)

# This needs to be set prior to any project calls
if (DEFINED APPLE AND APPLE)
    #Important linker flags!!
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")

    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14" CACHE STRING "Minimum OS X deployment version")

    add_definitions(-DMAC_OS_X_VERSION_MIN_REQUIRED=101400)
endif()


# Name of the project (will be the name of the plugin)
project(addon LANGUAGES C CXX)

if(MSVC)
  message(FATAL_ERROR "Building with MSVC (or a compiler emulating its command line syntax) is not supported!")
endif()

add_compile_options("-march=x86-64") #make sure clang doesn't use march=native or whatever

add_library(
    addon SHARED
    src/addon.cpp
    src/win32-link-hook.cc
)

target_compile_definitions(addon PUBLIC V8_COMPRESS_POINTERS)
target_compile_definitions(addon PUBLIC V8_31BIT_SMIS_ON_64BIT_ARCH)
target_compile_definitions(addon PUBLIC V8_REVERSE_JSARGS)
target_compile_definitions(addon PUBLIC NAPI_CPP_EXCEPTIONS)
target_compile_definitions(addon PUBLIC BUILDING_NODE_EXTENSION)
#Mickeysoft macros...
if(WIN32)
  target_compile_definitions(addon PUBLIC "NOMINMAX")
  target_compile_definitions(addon PUBLIC "NOGDI")
  target_compile_definitions(addon PUBLIC "WIN32_LEAN_AND_MEAN")
endif()

target_include_directories(addon PRIVATE include/node-libcpuid-neo)
target_include_directories(addon PRIVATE ${CMAKE_JS_INC})

target_link_libraries(addon ${CMAKE_JS_LIB})


#the libcpuid CMake file is rather terrible and doesn't really work for our case
add_library(
    libcpuid STATIC
    external/libcpuid/libcpuid/cpuid_main.c
    external/libcpuid/libcpuid/recog_intel.c
    external/libcpuid/libcpuid/recog_amd.c
    external/libcpuid/libcpuid/rdtsc.c
    external/libcpuid/libcpuid/libcpuid_util.c
    external/libcpuid/libcpuid/rdmsr.c
    external/libcpuid/libcpuid/msrdriver.c
    external/libcpuid/libcpuid/asm-bits.c
)
set_target_properties(libcpuid PROPERTIES POSITION_INDEPENDENT_CODE ON) #necessary so that we can link it into our shared lib
set(LIBCPUID_VERSION "0.5.1")
target_compile_definitions(libcpuid PRIVATE VERSION="${LIBCPUID_VERSION}")
target_link_libraries(addon libcpuid)
target_include_directories(addon PRIVATE external/libcpuid/libcpuid)

# Gives our library file a .node extension without any "lib" prefix
set_target_properties(
  addon PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS NO
  PREFIX ""
  SUFFIX ".node"
  POSITION_INDEPENDENT_CODE ON
)

# Windows workaround
if(WIN32)
  set_property(TARGET addon PROPERTY LINK_FLAGS "-Xlinker /DELAYLOAD:NODE.EXE")
  target_link_libraries(addon "ShLwApi.lib" "delayimp.lib")
endif()