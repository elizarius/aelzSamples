cmake_minimum_required(VERSION 3.10)
project(domProcessor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../include)
include_directories(08_dom)

# BinarySearchTree only configuration
set(SOURCES
  main.cpp
  DomWorker.cpp
  08_dom/BinarySearchTree.cpp
)

add_executable(domProcessor ${SOURCES})

# Optional: All available tasks configuration (commented out)
# set(ALL_SOURCES
#   main.cpp
#   DomWorker.cpp
#   08_dom/BinarySearchTree.cpp
#   08_dom/counters.cpp
#   08_dom/FrogTime.cpp
#   08_dom/MissingInteger.cpp
#   08_dom/palindrom.cpp
#   08_dom/path.cpp
#   08_dom/sortedSearchAlgo.cpp
#   08_dom/sortedSearch.cpp
#   08_dom/two_sums.cpp
# )
# add_executable(domProcessor_full ${ALL_SOURCES})
