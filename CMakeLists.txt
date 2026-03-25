cmake_minimum_required(VERSION 3.16)
project(autonomous_sensor_pipeline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# includeディレクトリ
include_directories(include)

# ------------------------
# componentsライブラリ
# ------------------------
add_library(components
    components/sensor.cpp
    components/processor.cpp
    components/logger.cpp
)

# ------------------------
# pipelineライブラリ
# ------------------------
add_library(pipeline
    pipeline/pipeline_manager.cpp
)

# pipelineはcomponentsに依存するのでPUBLICでリンクしておく
target_link_libraries(pipeline PUBLIC components)

# ------------------------
# main実行
# ------------------------
add_executable(main src/main.cpp)
# main実行時に引数を指定したい場合は↓の例のように記載する
# ./main --duration 7 --interval 300 --noise 0.2

# mainはpipelineのみリンク（componentsはPUBLICでリンク済み）
target_link_libraries(main pipeline)

# ------------------------
# Python実行
# ------------------------
add_custom_target(analyze
    COMMAND python3 scripts/analyze.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_custom_target(plot
    COMMAND python3 scripts/plot.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# ------------------------
# main & Python 実行
# ------------------------
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/main ${ARGS}
    COMMAND python3 scripts/analyze.py
    COMMAND python3 scripts/plot.py
    #DEPENDS main
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
# make runで引数を指定したい場合はcmakeの際に↓の例のように記載する
# cmake .. -D ARGS="--duration;10;--interval;500;--noise;0.8"
