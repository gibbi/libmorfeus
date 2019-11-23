add_executable(morfeus morfeus-client.cpp morfeus.cpp)
target_link_libraries(morfeus ${HIDAPI_LIBRARIES})