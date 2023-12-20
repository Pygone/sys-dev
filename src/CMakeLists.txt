
add_library(chess_lib chess.cpp message.cpp bluetooth.cpp show.cpp controller.cpp
        beginer.cpp moveTrial.cpp)

target_link_libraries(chess_lib
        common
        jpeg
        png
        freetype
        z
        asound
)
