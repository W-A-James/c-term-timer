cmake_minimum_required(VERSION 3.16)

project(term-timer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wpedantic -Wextra)

if(DEFINED ENV{DEBUG})
  message("Building with debug")
  add_compile_options(-g -ggdb -O0)
else()
  add_compile_options(-O3)
endif()

set(SOUND_DIR "${PROJECT_SOURCE_DIR}/sounds")
set(SCRIPT_DIR "${PROJECT_SOURCE_DIR}/scripts")
set(SRC_DIR   "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR  "${PROJECT_SOURCE_DIR}/test")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add vendored libraries
add_subdirectory(vendored/CSFML-2.6.1 EXCLUDE_FROM_ALL)

file(GLOB SRC_FILES ${SRC_DIR}/*.c)


set(CLOCK_TEST_SRC 
  ${TEST_DIR}/clock.test.c
  ${TEST_DIR}/common.h
  ${SRC_DIR}/clock.c
  ${SRC_DIR}/common.c
  ${SRC_DIR}/raw_term.c
  ${SRC_DIR}/play_sound.c
)

set(DURATION_PARSER_TEST_SRC
   ${TEST_DIR}/duration-parser.test.c
   ${TEST_DIR}/common.h
   ${SRC_DIR}/duration-parser.c
)

set(REQUIRED_LIBS 
  Threads::Threads
  m
  csfml-audio
)

# Main
add_executable(term-timer 
  ${SRC_FILES}
  ${SRC_DIR}/sound.gen.h # need to list it directly because the glob won't find it
)
# Generate src/sound.gen.h
add_custom_command(
  PRE_BUILD
  OUTPUT ${SRC_DIR}/sound.gen.h
  COMMAND ${SCRIPT_DIR}/read_wav_to_bytes.py ${SOUND_DIR}/sfx_alarm_loop6.wav ${SRC_DIR}/sound.gen.h
  DEPENDS ${SOUND_DIR}/sfx_alarm_loop6.wav
)

target_link_libraries(term-timer PRIVATE ${REQUIRED_LIBS}) 

# TESTS
add_executable(duration-parser.test ${DURATION_PARSER_TEST_SRC})

add_executable(clock.test ${CLOCK_TEST_SRC})
target_link_libraries(clock.test PRIVATE ${REQUIRED_LIBS})

