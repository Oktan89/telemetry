cmake_minimum_required(VERSION 3.2)

set(PROJECT_VESRION 0.0.1)
set(MY_PROJECT_NAME telemetry)
project(${MY_PROJECT_NAME} VERSION ${PROJECT_VESRION})


add_executable(${MY_PROJECT_NAME} main.cpp)

set_target_properties(${MY_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(WIN32)
    target_link_libraries(${MY_PROJECT_NAME} wsock32 ws2_32)
endif()