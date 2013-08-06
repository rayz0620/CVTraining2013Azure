project(GenerateMainDatabase)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS thread filesystem system)
find_package(OpenCV REQUIRED)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(src_dir src)
add_definitions(-std=c++11)
add_definitions(-fPIC)
include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
include_directories(include)
include_directories(../include)
if (OpenCV_FOUND)
	add_executable(maindb ${src_dir}/main.cpp)
	target_link_libraries(maindb RetrievalDatabase FeatureItem IOUtils MatrixUtils SIFT ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${OpenCV_LIBS} )
	install (TARGETS maindb DESTINATION /usr/bin)
endif()


