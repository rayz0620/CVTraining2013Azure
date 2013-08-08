project(RunTest)
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
	add_executable(runtest ${src_dir}/main.cpp)
	target_link_libraries(runtest Retrieval SemanticDatabase RetrievalDatabase FeatureItem SCC SparseCoding IOUtils MatrixUtils SIFT ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${OpenCV_LIBS} )
	install (TARGETS runtest DESTINATION /usr/bin)
endif()


