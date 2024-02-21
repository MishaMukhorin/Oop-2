cmake_minimum_required(VERSION 3.20)

project(Oop-2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_subdirectory(lib/googletest)

## Add include directories
INCLUDE_DIRECTORIES(lib/googletest/googletest/include)

# Add executable
add_executable(HTMLEncodeTests 2-5/tests/HTMLEncodeTests.cpp 2-5/HTMLEncode.cpp)
add_executable(HTMLDecodeTests 2-5/tests/HTMLDecodeTests.cpp 2-5/HTMLDecode.cpp)
add_executable(HTMLDecodeOut 2-5/HTMLDecodeOut.cpp 2-5/HTMLDecode.cpp)

add_executable(VectorProcessorTests 1-7/tests/VectorProcessorTests.cpp 1-7/VectorProcessor.cpp)

add_executable(Dictionary 3-2/DictionaryOut.cpp 3-2/Dictionary.cpp)
add_executable(DictionaryTests 3-2/DictionaryTests/DictionaryTests.cpp 3-2/Dictionary.cpp)

add_executable(PrimeSetTests 4-4/tests/PrimeNumsSetTests.cpp 4-4/PrimeNumsSet.cpp)
add_executable(PrimeSetOut 4-4/PrimesOut.cpp 4-4/PrimeNumsSet.cpp)

add_executable(ParseURLTests 5-1/tests/ParseURLTests.cpp 5-1/ParseURL.cpp)
add_executable(ParseURLOut 5-1/ParseURLOut.cpp 5-1/ParseURL.cpp)

add_executable(ExpandTemplateTests 6-1/tests/ExpandTemplateTests.cpp 6-1/ExpandTemplate.cpp 6-1/Trie.cpp)
add_executable(ExpandTemplate 6-1/ExpandTemplateOut.cpp 6-1/ExpandTemplate.cpp 6-1/Trie.cpp)


target_link_libraries(HTMLEncodeTests gtest_main)
target_link_libraries(HTMLDecodeTests gtest_main)
target_link_libraries(VectorProcessorTests gtest_main)
target_link_libraries(PrimeSetTests gtest_main)
target_link_libraries(DictionaryTests gtest_main)
target_link_libraries(ParseURLTests gtest_main)
target_link_libraries(ExpandTemplateTests gtest_main)










