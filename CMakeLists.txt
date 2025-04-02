cmake_minimum_required(VERSION 3.8)
project(Formalizer)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Paths

set(PATH_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# get full path to existing file with symlinks resolved
get_filename_component(PATH_ROOT ${PATH_ROOT} REALPATH)

set(PATH_FORMALIZER ${PATH_ROOT}/Formalizer)
set(PATH_THIRD_PARTY ${PATH_ROOT}/third-party)
set(PATH_STREAMABLE ${PATH_THIRD_PARTY}/Streamable)
set(PATH_JSON ${PATH_THIRD_PARTY}/JSON)

# Flags

if(MSVC)
    set(CPPFLAGS
        /W4 # warning level 4
        /WX # treat warnings as errors
        /MP # multi-processor compilation
        # /GL # whole program optimization
        /Zi # debug information format
        /fsanitize=address # address sanitizer
        /fsanitize=fuzzer # fuzzer sanitizer
        /MTd # static runtime library debug
        /EHsc # exception handling
        /GR # RTTI
        /std:c++latest # C++ standard
    )
else()
    set(CPPFLAGS
        # -Werror # treat warnings as errors
        -fexceptions # exception handling
        -frtti # RTTI
        -std=c++2b # C++ standard
        -stdlib=libstdc++ # C++ standard library
        -fexperimental-library # experimental library
    )
endif()

add_compile_options(${CPPFLAGS})

set(HEADERS_THIRD_PARTY
    ${PATH_THIRD_PARTY}
)

set(SOURCES_STREAMABLE
    ${PATH_STREAMABLE}/Streamable.hpp
)

set(SOURCES_JSON
    ${PATH_JSON}/json.hpp
)

set(HEADERS_FORMALIZER
    ${PATH_FORMALIZER}
)

file(GLOB_RECURSE SOURCES_FORMALIZER
    "${PATH_FORMALIZER}/*.cpp"
)

add_executable(formalizer-app
    ${SOURCES_JSON}
    ${SOURCES_STREAMABLE}
    ${SOURCES_FORMALIZER}
)

target_include_directories(formalizer-app
    PRIVATE
    ${HEADERS_THIRD_PARTY}
    ${HEADERS_FORMALIZER}
)
