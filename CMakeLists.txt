cmake_minimum_required(VERSION 3.10)
project(MPIJNIBridge CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(JNI REQUIRED)
if (JNI_FOUND)
    message(STATUS "Found JNI at: ${JNI_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Could not find JNI.")
endif()

find_package(MPI REQUIRED)
if (MPI_FOUND)
    message(STATUS "Found MPI: ${MPI_CXX_LIBRARIES}")
else()
    message(FATAL_ERROR "Could not find MPI.")
endif()

include_directories(
        ${JNI_INCLUDE_DIRS}
        ${MPI_CXX_INCLUDE_PATH}
)

add_library(${PROJECT_NAME} SHARED
        MPIJavaWrapper.c
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        MPI::MPI_CXX         # or ${MPI_CXX_LIBRARIES}
        ${JNI_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "MPIJNIBridge"
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)
