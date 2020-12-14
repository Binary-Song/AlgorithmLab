aux_source_directory(src src_e5)
add_executable(Experiment5 ${src_e5})
 
target_include_directories(Experiment5 PUBLIC include)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Experiment5 PUBLIC /utf-8 /D_CRT_SECURE_NO_WARNINGS )  
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

endif()
