cmake_minimum_required(VERSION 3.10)
project(dbview LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Useful warnings (already good, but make it stricter)
add_compile_options(-Wall -Wextra -Werror -pedantic)

# Debug/Release flags
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Default to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Main executable
add_executable(dbview
    src/main.c
    src/file.c
    src/parse.c
)

target_include_directories(dbview PRIVATE include)

# Custom test target (delete old DB, create new, add records, list)
add_custom_target(test
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_SOURCE_DIR}/mynewdb.db
    COMMAND ${CMAKE_COMMAND} -E echo "========================================="
    COMMAND ${CMAKE_COMMAND} -E echo "Creating new database..."
    COMMAND $<TARGET_FILE:dbview> -f mynewdb.db -n
    COMMAND ${CMAKE_COMMAND} -E echo "Adding Timmy..."
    COMMAND $<TARGET_FILE:dbview> -f mynewdb.db -a "Timmy H.,123 Sheshire Ln.,120"
    COMMAND ${CMAKE_COMMAND} -E echo "Adding Alice..."
    COMMAND $<TARGET_FILE:dbview> -f mynewdb.db -a "Alice Wonder,456 Fairy Tale Rd,160"
    COMMAND ${CMAKE_COMMAND} -E echo "========================================="
    COMMAND ${CMAKE_COMMAND} -E echo "Final list:"
    COMMAND $<TARGET_FILE:dbview> -f mynewdb.db -l
    COMMAND ${CMAKE_COMMAND} -E echo "========================================="
    COMMAND ${CMAKE_COMMAND} -E echo "Test complete!"
    DEPENDS dbview
    COMMENT "Running dbview test sequence"
    USES_TERMINAL   # <-- nicer output in terminal
)

# Clean target that also deletes the test database
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_SOURCE_DIR}/mynewdb.db
    COMMENT "Full clean (including database file)"
)