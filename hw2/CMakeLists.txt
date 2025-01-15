cmake_minimum_required(VERSION 3.20)

project(ip_filter)

add_executable(ip_filter ip_filter.cpp)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
