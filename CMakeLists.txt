cmake_minimum_required(VERSION 3.14)
project(Algos)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow -Wunused")

#Itt válaszd ki, hogy melyik algoritmus main funkcióját szeretnéd fordítani.
#(Lehetne máshogy is, de ez van...)

#LENGYEL
#MERGE_SORT
#QUICK_SORT

add_compile_definitions(QUICK_SORT) # <- Írd ide

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp *.hpp *.h *.c)
message(${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})