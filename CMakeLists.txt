cmake_minimum_required(VERSION 3.13)
project(kNN)

set(CMAKE_CXX_STANDARD 17)

add_executable(kNN main.cpp KDTreePreparation.h KDTreePreparation.cpp KDTree.h KDTree.cpp Geometry.cpp Geometry.h Statistics.h CSVReader.cpp CSVReader.h Statistics.cpp KFold.cpp KFold.h CrossValidation.cpp CrossValidation.h)

add_executable(Tests KDTreePreparation.h KDTreePreparation.cpp KDTreeTest.cpp KDTree.h KDTree.cpp Geometry.cpp Geometry.h Statistics.h CSVReader.cpp CSVReader.h Statistics.cpp KFold.cpp KFold.h)