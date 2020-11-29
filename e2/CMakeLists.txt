aux_source_directory(src src_e2)
add_executable(Experiment2 ${src_e2})
target_include_directories(Experiment2 PUBLIC include)
target_compile_options(Experiment2 PUBLIC /utf-8 /D_CRT_SECURE_NO_WARNINGS)