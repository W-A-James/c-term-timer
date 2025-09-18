cmake_minimum_required(VERSION 3.16)

project(term-timer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_custom_command(
  PRE_BUILD
  OUTPUT src/sound.gen.h
  COMMAND ${PROJECT_SOURCE_DIR}/scripts/read_wav_to_bytes.py
  ${PROJECT_SOURCE_DIR}/src/sfx_alarm_loop6.wav ${PROJECT_SOURCE_DIR}/src/sound.gen.h
  DEPENDS src/sfx_alarm_loop6.wav
)

add_subdirectory(vendored/CSFML-2.6.1 EXCLUDE_FROM_ALL)

add_executable(term-timer 
  src/main.c
  src/common.c
  src/clock.c
  src/duration-parser.c
  src/raw_term.c
  src/play_sound.c
  src/sound.gen.h
)

add_executable(duration-parser.test
   src/duration-parser.c
   test/duration-parser.test.c
   test/common.h
)

add_executable(clock.test
  src/clock.c
  src/common.c
  src/raw_term.c
  src/play_sound.c
  test/clock.test.c
  test/common.h
)

target_link_libraries(clock.test PRIVATE
  m
  csfml-audio
)

target_link_libraries(term-timer PRIVATE
                      Threads::Threads
                      m
                      csfml-audio)
