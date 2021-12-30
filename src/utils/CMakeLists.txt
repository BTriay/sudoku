if (MSVC)
	add_compile_options(/W4 /WX /MDd /EHsc /experimental:module)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(utils
            io.cpp
            io.ixx
            )

target_compile_features(utils PUBLIC cxx_std_20)
