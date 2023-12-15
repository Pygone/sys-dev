

file(GLOB SOURCES "*.c" )
set(common_sources ${SOURCES} PARENT_SCOPE)
add_library(common
        ${SOURCES}
)
