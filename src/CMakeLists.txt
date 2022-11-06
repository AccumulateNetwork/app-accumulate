
add_compile_options(-Wextra -Wcast-qual -Wshadow -Werror
        -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-security -Wformat-signedness
)

set(DEBUG_SUPPORT_SRC
        common/internal/testing/sha256.c
        common/internal/testing/sha256.h
        common/internal/testing/sha3.c
        common/internal/testing/sha3.h
        )

file(GLOB_RECURSE ACC_SOURCE *.c *.h)
file(GLOB_RECURSE ACC_HEADER ../include/*.h)
list(REMOVE_ITEM ACC_SOURCE common/internal/*)

add_library(accsup
        ${ACC_SOURCE}
        ${ACC_HEADER}
        ${DEBUG_SUPPORT_SRC}
        )

add_executable(accumulate
        ${MAIN_SRC}
        ${ENCODER_SRC}
        ${COMMON_SRC}
        ${DEBUG_SUPPORT_SRC}
 )

# ensure the loader .text section doesn't mess with cxlib
if (CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
  # Option for clang
  if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0")
    set_property(TARGET launcher APPEND PROPERTY LINK_OPTIONS "LINKER:--image-base=0xf0000000")
  else()
    set_property(TARGET launcher APPEND PROPERTY LINK_FLAGS "-Xlinker --image-base=0xf0000000")
  endif ()
elseif (CMAKE_C_COMPILER_ID MATCHES "GNU")
  # Option for gcc
  if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0")
#    set_property(TARGET launcher APPEND PROPERTY LINK_OPTIONS "LINKER:-Ttext-segment=0xf0000000")
  else()
#    set_property(TARGET launcher APPEND PROPERTY LINK_FLAGS "-Wl,-Ttext-segment=0xf0000000")
  endif ()
else ()
  message(FATAL_ERROR "Unable to identify the compiler!")
endif ()
#target_link_libraries(launcher PRIVATE emu)
