cmake_minimum_required(VERSION 3.20)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

option(USE_GTEST ON)
option(USE_BOOST_TEST OFF)

project(helloworld VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp )
add_library(helloworldLib lib.cpp)

set (ALL_SOURCES helloworld_cli helloworldLib)

if(USE_GTEST)
    include(FetchContent)
    FetchContent_Declare(
 		 googletest
  		 URL https://github.com/google/googletest/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(googletest)
 
   add_executable(test_version test_version.cpp)

    target_link_libraries(test_version
        GTest::gtest_main
        helloworldLib
    )

elseif(USE_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_version test_version.cpp)


    set_target_properties(test_version PROPERTIES
		COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
		INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
	)

    target_link_libraries(test_version
        ${Boost_LIBRARIES}
        helloworldLib
	)

endif()

list(APPEND $ALL_SOURCES test_version)

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


if(USE_BOOST_TEST OR USE_GTEST)
    enable_testing()
    add_test(test_version test_version)
endif()
