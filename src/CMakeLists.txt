add_library(chess_lib chess.cpp)
target_link_libraries(chess_lib common)
add_library(show_lib show.cpp)
target_link_libraries(show_lib common)