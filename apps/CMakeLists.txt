link_directories(${CMAKE_SOURCE_DIR}/src)

find_package(clara REQUIRED)

set( EXCEUTABLE_NAME main)

add_executable(${EXCEUTABLE_NAME} main.cpp)
target_link_libraries(${EXCEUTABLE_NAME} game clara::clara)
target_include_directories(${EXCEUTABLE_NAME} PUBLIC ../src) 

add_executable(preflopstrength preflopstrengths.cpp)
target_link_libraries(preflopstrength game clara::clara)
target_include_directories(preflopstrength PUBLIC ../src) 