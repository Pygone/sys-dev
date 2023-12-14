
add_library(common STATIC
        graphic.c
        image.c
        task.c
        touch.c
)

target_link_libraries(common
        jpeg
        png
        freetype
        z
        asound
)
