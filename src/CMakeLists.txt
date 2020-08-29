cmake_minimum_required (VERSION 3.8)

add_executable (DataTransmitter "TrasmitTask.cpp" "DataTransmitter.cpp" "main.cpp" "TestCase.cpp")
target_compile_definitions(DataTransmitter PUBLIC ASIO_STANDALONE)
target_include_directories(DataTransmitter PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/thirdparty/asio/include)
