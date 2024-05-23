set (JSON_BuildTests OFF CACHE INTERNAL "")

add_executable (${PROJECT_NAME} 
				main.cpp
				converterJSON.cpp
				InvertedIndex.cpp
				searchServer.cpp
)

target_include_directories	(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_PATH})
target_link_libraries 		(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
