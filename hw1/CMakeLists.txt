cmake_minimum_required(VERSION 3.20)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp )
add_library(helloworldLib lib.cpp)

set (ALL_SOURCES helloworld_cli helloworldLib)

if(WITH_BOOST_TEST)
    include(FetchContent)
    FetchContent_Declare(
 		 googletest
  		 URL https://github.com/google/googletest/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(googletest)
 
    add_executable(test_version test_version.cpp)

    list(APPEND $ALL_SOURCES test_version)

    target_link_libraries(test_version
        GTest::gtest_main
        helloworldLib
    )
endif()

set_target_properties(${ALL_SOURCES} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworldLib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworldLib
)

foreach(s ${ALL_SOURCES})
	if (MSVC)
		target_compile_options(${s} PRIVATE
			/W4
		)
		
	else ()
		target_compile_options(${s} PRIVATE
			-Wall -Wextra -pedantic -Werror
		)
	endif()
endforeach()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_version test_version)
endif()
