cmake_minimum_required(VERSION 3.14)
project(Algos)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow -Wunused")

#Itt válaszd ki, hogy melyik algoritmus main funkcióját szeretnéd fordítani.
#(Lehetne máshogy is, de ez van...)

#LENGYEL
#MERGE_SORT
#QUICK_SORT
#S1L

add_compile_definitions(S1L) # <- Írd ide

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp *.hpp)
message(${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})