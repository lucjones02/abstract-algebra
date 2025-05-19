set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/abstract_algebra.cpp
)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
add_library(abstract_algebra ${SOURCES} ${HEADER_LIST})
target_include_directories(abstract_algebra PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_sources(abstract_algebra PRIVATE ${SOURCES})

add_executable(test ${SOURCES})
target_link_libraries(test abstract_algebra)
