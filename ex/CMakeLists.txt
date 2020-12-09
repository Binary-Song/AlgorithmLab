aux_source_directory(src src_ex)
add_executable(ExperimentX ${src_ex})
target_include_directories(ExperimentX PUBLIC include)
target_compile_options(ExperimentX PUBLIC /utf-8 /D_CRT_SECURE_NO_WARNINGS)