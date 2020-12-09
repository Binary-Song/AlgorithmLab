aux_source_directory(src src_e3)
add_executable(Experiment3 ${src_e3})
target_include_directories(Experiment3 PUBLIC include)
target_compile_options(Experiment3 PUBLIC /utf-8 /D_CRT_SECURE_NO_WARNINGS)