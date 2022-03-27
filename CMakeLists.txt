cmake_minimum_required(VERSION 3.2)

set(PROJECT_VESRION 0.0.1)
set(MY_PROJECT_NAME telemetry)
project(${MY_PROJECT_NAME} VERSION ${PROJECT_VESRION})


add_executable(${MY_PROJECT_NAME} main.cpp
                                client.cpp 
                                ProtocolView.cpp
                                DataView.cpp
                                telemetry.cpp
                                type_traits_frame.cpp
)

set_target_properties(${MY_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(WIN32)
    target_link_libraries(${MY_PROJECT_NAME} wsock32 ws2_32)
endif()

if (MSVC)
    target_compile_options(${MY_PROJECT_NAME} PRIVATE
        /W4
    )
else ()
    target_compile_options(${MY_PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ${MY_PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT r.zhigalenko@mail.ru)
include(CPack)
