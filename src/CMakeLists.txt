
add_compile_options(-Wextra -Wcast-qual -Wshadow -Werror
        -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-security -Wformat-signedness
)

set(DEBUG_SUPPORT_SRC
        common/internal/testing/sha256.c
        common/internal/testing/sha256.h
        common/internal/testing/sha3.c
        common/internal/testing/sha3.h
        )

set(COMMON_SRC
        common/sha256.c
        common/sha256.h
        common/keccak.c
        common/keccak.h
        common/base58.c
        common/base58.h
        common/bip32.c
        common/bip32.h
        common/buffer.c
        common/buffer.h
        common/error.c
        common/error.h
        common/error.h
        common/format.c
        common/format.h
        common/read.c
        common/read.h
        common/uint256.c
        common/uint256.h
        common/varint.c
        common/varint.h
        common/write.c
        common/write.h
        )

set(ENCODER_SRC
        common/encoding/uvarint.c
        common/encoding/uvarint.h
        common/encoding/varint.c
        common/encoding/varint.h
        common/encoding/marshaler.h
        common/encoding/marshaler.c
        common/encoding/bytes32.c
        common/encoding/bytes32.h
        common/encoding/bytes.c
        common/encoding/bytes.h
        common/encoding/bigint.c
        common/encoding/bigint.h
        common/encoding/bytes64.c
        common/encoding/bytes64.h
        common/encoding/encoding.h
        common/encoding/string.c
        common/encoding/string.h
        common/encoding/url.c
        common/encoding/url.h
        )

set(MAIN_SRC
        address.c
        address.h
        crypto.c
        crypto.h
        io.c
        io.h
        main.c
        constants.h
        globals.h
        offsets.h
        sw.h
        types.h
        )

add_library(accsup
        ${ENCODER_SRC}
        ${COMMON_SRC}
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
