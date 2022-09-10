
add_library(
	loguru STATIC
	${CMAKE_CURRENT_LIST_DIR}/loguru.cpp
	${CMAKE_CURRENT_LIST_DIR}/loguru.hpp
	${CMAKE_CURRENT_LIST_DIR}/debug.h
	${CMAKE_CURRENT_LIST_DIR}/debug.cpp
	)
target_compile_definitions(loguru PUBLIC -DLOGURU_WITH_STREAMS) 
