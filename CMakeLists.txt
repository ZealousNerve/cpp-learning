cmake_minimum_required(VERSION 3.20)
project(cpp-learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# ── AUTO-DISCOVERY ──────────────────────────────────────────────
file(GLOB_RECURSE ALL_SOURCES
        "0*/*.cpp"
        "1*/*.cpp"
        "2*/*.cpp"
        "_sandbox/*.cpp"
)

foreach(SOURCE_FILE ${ALL_SOURCES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}" "${SOURCE_FILE}")
    string(REPLACE "/" "__" TARGET_NAME "${REL_PATH}")
    string(REPLACE ".cpp" "" TARGET_NAME "${TARGET_NAME}")
    string(REPLACE " " "_" TARGET_NAME "${TARGET_NAME}")

    add_executable(${TARGET_NAME} ${SOURCE_FILE})
endforeach()