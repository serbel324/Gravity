cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)

set(INCPATH ${PROJECT_SOURCE_DIR}/include)

project(App)

set(SOURCES
    main.cpp
    world.cpp
    continuous_world.cpp
    single_threaded_world.cpp
    multi_threaded_world.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${INCPATH}
)

target_link_libraries(${PROJECT_NAME}
    REngineDriver
    REngineCore
    Library
)