if (MSVC)
	add_compile_options(/W4 /WX /MDd /EHsc /experimental:module)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(Sudobjects
            Grid.cpp
            Cell.cpp
            Cell.ixx
            )

target_compile_features(Sudobjects PUBLIC cxx_std_20)
