aux_source_directory(src src_e4)
add_executable(Experiment4 ${src_e4}) 
target_include_directories(Experiment4 PUBLIC include ) 

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Experiment4 PUBLIC /utf-8 /D_CRT_SECURE_NO_WARNINGS )  
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") 
endif()
