
cmake_minimum_required(VERSION 3.5)

project(allocator )

add_executable(allocator main.cpp )

set (ALL_SOURCES allocator)

set_target_properties(${ALL_SOURCES} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
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

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

