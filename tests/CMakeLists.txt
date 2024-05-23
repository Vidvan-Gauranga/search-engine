include (FetchContent)
FetchContent_Declare (
	googletest
	DOWNLOAD_EXTRACT_TIMESTAMP ON
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable (googletest)

enable_testing()

add_executable (
	search_engine_test
	search_engine_test.cc
	../src/converterJSON.cpp
	../src/InvertedIndex.cpp
	../src/searchServer.cpp
)

target_include_directories	(search_engine_test PUBLIC ${MY_INCLUDE_PATH})
target_link_libraries 		(search_engine_test PRIVATE 
	nlohmann_json::nlohmann_json
	GTest::gtest_main 
)

include(GoogleTest)
gtest_discover_tests(search_engine_test)


