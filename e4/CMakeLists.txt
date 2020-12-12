aux_source_directory(src src_e4)
add_executable(Experiment4 ${src_e4})

find_package(Boost REQUIRED)
target_include_directories(Experiment4 PUBLIC include ${Boost_INCLUDE_DIRS})
target_link_directories(Experiment4 PUBLIC ${Boost_LIBRARY_DIRS})
target_compile_options(Experiment4 PUBLIC /utf-8 /D_CRT_SECURE_NO_WARNINGS )  
