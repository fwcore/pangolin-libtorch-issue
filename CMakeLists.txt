cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# 3.18 for CUDA17, however, select 3.18 will give "CUDA_ARCHITECTURES is empty" error.
# https://stackoverflow.com/questions/68223398/how-can-i-get-cmake-to-automatically-detect-the-value-for-cuda-architectures

project(pangolin_libtorch_test)

# use FetchContent instead of ExternalProject_Add (build-time downloading) for following find_package
# https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html#guide:Using%20Dependencies%20Guide
include(FetchContent)

FetchContent_Declare(Torch
  URL https://download.pytorch.org/libtorch/cu117/libtorch-cxx11-abi-shared-with-deps-2.0.1%2Bcu117.zip
  URL_HASH SHA256=262f723ee5a2caac977e089bc06e9d840ca33d70706fbd4a2fca04995bb94eb4
)

# FetchContent_MakeAvailable(Torch)
message("${CMAKE_BINARY_DIR}")

# set(CMAKE_CUDA_COMPILER /usr/local/cuda-12.0/bin/nvcc)

find_package(Torch REQUIRED
  PATHS ${CMAKE_BINARY_DIR}/_deps/torch-src
  NO_DEFAULT_PATH
)
find_package(Pangolin REQUIRED)

########################
# pangolin_alone_test
add_executable(pangolin_alone_test  
    ${CMAKE_CURRENT_LIST_DIR}/pangolin_alone.cpp)
target_link_libraries(pangolin_alone_test PRIVATE ${Pangolin_LIBRARIES})
set_property(TARGET pangolin_alone_test PROPERTY CXX_STANDARD 17)
add_executable(pangolin_libtorch_test 
    ${CMAKE_CURRENT_LIST_DIR}/pangolin_libtorch.cpp)

########################
# pangolin_libtorch_test
target_link_libraries(pangolin_libtorch_test PRIVATE ${Pangolin_LIBRARIES} "${TORCH_LIBRARIES}"
)
set_property(TARGET pangolin_libtorch_test PROPERTY CXX_STANDARD 17)

# The following code block is suggested to be used on Windows.
# According to https://github.com/pytorch/pytorch/issues/25457,
# the DLLs need to be copied to avoid memory errors.
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET pangolin_libtorch_test
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:CSLAM_superpoint>)
endif (MSVC)


########################
# opengl_libtorch_test
add_executable(opengl_libtorch_test 
    ${CMAKE_CURRENT_LIST_DIR}/opengl_libtorch.cpp)
target_link_libraries(opengl_libtorch_test PRIVATE GL GLU glut glfw "${TORCH_LIBRARIES}")
set_property(TARGET opengl_libtorch_test PROPERTY CXX_STANDARD 17)
