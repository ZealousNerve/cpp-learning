cmake_minimum_required(VERSION 3.20)
project(cpp-learning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags — matches your README: -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Debug = no optimization (debugger works properly)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

# Release = optimized (for testing as-if rule etc.)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# ── AUTO-DISCOVERY ──────────────────────────────────────────────
# Recursively finds every .cpp file in all chapter folders.
# When you add a new file tomorrow, CMake picks it up automatically.
file(GLOB_RECURSE ALL_SOURCES
        "0*/*.cpp"
        "1*/*.cpp"
        "2*/*.cpp"
        "_sandbox/*.cpp"
)

foreach(SOURCE_FILE ${ALL_SOURCES})
    # Build a unique target name from the file path
    # e.g. 05_constants_strings/optimization.cpp → 05_constants_strings__optimization
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}" "${SOURCE_FILE}")
    string(REPLACE "/" "__" TARGET_NAME "${REL_PATH}")
    string(REPLACE ".cpp" "" TARGET_NAME "${TARGET_NAME}")
    string(REPLACE " " "_" TARGET_NAME "${TARGET_NAME}")

    add_executable(${TARGET_NAME} ${SOURCE_FILE}
            05_constants_strings/constexpr.cpp
            05_constants_strings/strigns.cpp
            06_operators/precedence_associativity.cpp
            06_operators/other_operators.cpp
            06_operators/logical_XOR.cpp
            02_functions/namingCollison_namespace.cpp
            07_scope_linkage/namespace.cpp
            07_scope_linkage/variable.cpp
            07_scope_linkage/linkage.cpp
            07_scope_linkage/inline.cpp
            07_scope_linkage/Global_Constants.cpp
            07_scope_linkage/Extras.cpp
            08_control_flow/control_flow.cpp
            08_control_flow/switch.cpp
            08_control_flow/loops.cpp
            08_control_flow/halt.cpp
            08_control_flow/random_numbers.cpp
            09_error_handling/errrors.cpp)
endforeach()