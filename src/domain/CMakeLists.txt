if (MSVC)
	add_compile_options(/W4 /WX /MDd /EHsc /experimental:module)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(sudobjects
            GridEngine.cpp
            Grid.cpp
            Cell.cpp
            Cell.ixx
            Grid.ixx
            GridEngine.ixx
            )

target_compile_features(sudobjects PUBLIC cxx_std_20)
