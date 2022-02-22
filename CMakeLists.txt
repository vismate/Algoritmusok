cmake_minimum_required(VERSION 3.14)
project(Algos)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow -Wunused")

#Itt válaszd ki, hogy melyik algoritmus main funkcióját szeretnéd fordítani.
#(Lehetne máshogy is, de ez van...)

#LENGYEL
#MERGE_SORT

add_compile_definitions(MERGE_SORT) # <- Írd ide

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/ *.cpp *.hpp *.h *.c)

add_executable(${PROJECT_NAME} ${SOURCES})