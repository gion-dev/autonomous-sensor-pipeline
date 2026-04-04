cmake_minimum_required(VERSION 3.16)
project(autonomous_sensor_pipeline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================
# 共通include
# ========================
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# ========================
# components
# ========================
add_library(components
    src/components/sensor.cpp
    src/components/processor.cpp
    src/components/raw_logger.cpp
    src/components/filtered_logger.cpp
    src/components/truth_logger.cpp
)

target_include_directories(components
    PUBLIC ${PROJECT_INCLUDE_DIR}
)

target_compile_options(components PRIVATE -Wall -Wextra)

# ========================
# config
# ========================
add_library(config
    src/config/config.cpp
)

target_include_directories(config
    PUBLIC ${PROJECT_INCLUDE_DIR}
)

# ========================
# pipeline
# ========================
add_library(pipeline
    src/pipeline/pipeline_manager.cpp
)

target_include_directories(pipeline
    PUBLIC ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(pipeline
    PUBLIC
        components
        config
)

# ========================
# main executable
# ========================
add_executable(main
    src/main.cpp
)

target_link_libraries(main
    PRIVATE
        pipeline
)

# メモ：main実行時に引数を指定したい場合は↓の例のように記載する
# ./main --duration 5 --interval 300 --noise 0.7 --alpha 0.3 --ax 0.5 --ay 0.2

# ========================
# Python utilities
# ========================
add_custom_target(py_analyze
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/analyze.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(py_plot
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/plot.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(py_alpha_sweep
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/run_alpha_sweep.py
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/plot_alpha_sweep.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(py_alpha_sweep_ave
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/run_alpha_sweep_avg.py
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/plot_alpha_sweep_avg.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


# ========================
# Run pipeline + analysis
# ========================
add_custom_target(run
    COMMAND main ${ARGS}
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/analyze.py
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/plot.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# メモ：make runで引数を指定したい場合はcmakeの際に↓の例のように記載する
# cmake .. -D ARGS="--duration;5;--interval;300;--noise;0.7;--alpha;0.3;--ax;0.5;--ay;0.2"

