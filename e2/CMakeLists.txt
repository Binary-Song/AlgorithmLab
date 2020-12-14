aux_source_directory(src src_e2)
add_executable(Experiment2 ${src_e2})
target_include_directories(Experiment2 PUBLIC include)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
target_compile_options(Experiment2 PUBLIC /utf-8 /D_CRT_SECURE_NO_WARNINGS )  
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

endif()
