cmake_minimum_required(VERSION 3.10)

if(${CMAKE_VERSION} VERSION_LESS 3.10)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# project information
project(unit_tests
        VERSION 0.1
	      DESCRIPTION "Unit tests for Ledger Nano application"
        LANGUAGES C)

set(CMOCKA_LIBRARY cmocka)

if (WIN32 OR MINGW OR CYGWIN)
    set(CMOCKA_LIBRARY libcmocka.dll.a)
    link_directories("C:\\Program Files (x86)\\cmocka\\lib")
    include_directories("C:\\Program Files (x86)\\cmocka\\include")
endif (WIN32 OR MINGW OR CYGWIN)

# guard against bad build-type strings
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

include(CTest)
ENABLE_TESTING()

# specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pedantic -g -O0 --coverage -DUNIT_TEST")

set(GCC_COVERAGE_LINK_FLAGS "--coverage -lgcov")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

add_compile_definitions(TEST)

include_directories(../include ../src ${CMOCKA_INCLUDE_DIR})

add_executable(test_base58 test_base58.c)
add_executable(test_bip32 test_bip32.c)
add_executable(test_buffer test_buffer.c)
add_executable(test_format test_format.c)
add_executable(test_write test_write.c)
add_executable(test_apdu_parser test_apdu_parser.c)
add_executable(test_encoding test_encoding.c)
add_executable(test_hasher test_hasher.c)

add_library(hasher STATIC ../src/common/hasher.c)
add_library(base58 STATIC ../src/common/base58.c)
add_library(bip32 STATIC ../src/common/bip32.c)
add_library(buffer STATIC ../src/common/buffer.c)
add_library(read STATIC ../src/common/read.c)
add_library(write STATIC ../src/common/write.c)
add_library(format STATIC ../src/common/format.c)
add_library(varint STATIC ../src/common/varint.c ../src/common/uvarint.c)
add_library(apdu_parser STATIC ../src/apdu/parser.c)
add_library(transaction_utils ../src/transaction/utils.c ../src/protocol/unions.c ../src/protocol/enum.c ../src/protocol/envelope.c)
add_library(uint256 STATIC ../src/common/uint256.c)
add_library(encoding STATIC ../src/encoding/bytes32.c ../src/encoding/bytes64.c
        ../src/encoding/string_enc.c ../src/encoding/varint_enc.c ../src/encoding/bigint.c
        ../src/encoding/marshaler.c ../src/encoding/url.c ../src/encoding/uvarint_enc.c
        ../src/encoding/rawjson.c ../src/encoding/bool.c
        ../src/encoding/bytes.c  ../src/protocol/enum.c ../src/transaction/utils.c
        ../src/transaction/signer.c ../src/transaction/header.c ../src/transaction/send_tokens.c
        ../src/transaction/add_credits.c ../src/transaction/token_recipient.c ../src/transaction/transaction.c)

add_library(error STATIC ../src/common/error.c)
add_library(sha256 STATIC ../src/common/sha256.c internal/sha256.c)

target_link_libraries(test_base58 PUBLIC ${CMOCKA_LIBRARY} gcov base58)
target_link_libraries(test_bip32 PUBLIC ${CMOCKA_LIBRARY} gcov bip32 read)
target_link_libraries(test_buffer PUBLIC ${CMOCKA_LIBRARY} gcov buffer bip32 varint write read encoding)
target_link_libraries(test_format PUBLIC ${CMOCKA_LIBRARY} gcov format)
target_link_libraries(test_write PUBLIC ${CMOCKA_LIBRARY} gcov write)
target_link_libraries(test_apdu_parser PUBLIC ${CMOCKA_LIBRARY} gcov apdu_parser)

target_link_libraries(test_encoding sha256  uint256
        buffer varint error transaction_utils gcov
        ${CMOCKA_LIBRARY} read write format bip32 encoding hasher)

target_link_libraries(test_hasher PUBLIC sha256 encoding uint256
        buffer varint error transaction_utils gcov
        ${CMOCKA_LIBRARY} hasher read write format bip32 )

add_test(test_base58 test_base58)
add_test(test_bip32 test_bip32)
add_test(test_buffer test_buffer)
add_test(test_format test_format)
add_test(test_write test_write)
add_test(test_apdu_parser test_apdu_parser)
add_test(test_encoding test_encoding)
add_test(test_hasher test_hasher)
