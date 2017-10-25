cmake_minimum_required(VERSION 3.8)
project(PNC_Engine)

set(CMAKE_CXX_STANDARD 11)

# Main Game Files
set(SOURCE_FILES
        src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Cursor.cpp
        src/Cursor.h
        src/Player.cpp
        src/Player.h
        src/Room.cpp
        src/Room.h
        src/Item.cpp
        src/Item.h
        src/Pathfinder.cpp
        src/Pathfinder.h
        src/Music.cpp
        src/Music.h

        # Character confs
        characters/ch2.conf
        characters/ch4.conf

        # Room confs
        rooms/studio.conf)

# Players
configure_file(images/sprite_full.png sprite_full.png COPYONLY)
configure_file(images/ch4_full.png ch4_full.png COPYONLY)

# Stuff
configure_file(images/cursor.png cursor.png COPYONLY)
configure_file(images/shop.png shop.png COPYONLY)
configure_file(images/bedroom.png bedroom.png COPYONLY)
configure_file(images/arcade.png arcade.png COPYONLY)

# Studio Room
configure_file(images/studio.png studio.png COPYONLY)
configure_file(images/studio_column1.png studio_column1.png COPYONLY)
configure_file(images/studio_column2.png studio_column2.png COPYONLY)
configure_file(images/studio_column3.png studio_column3.png COPYONLY)
configure_file(images/studio_column4.png studio_column4.png COPYONLY)
configure_file(images/studio_column5.png studio_column5.png COPYONLY)

# Music
configure_file(music/track1.ogg track1.ogg COPYONLY)
configure_file(music/track2.ogg track2.ogg COPYONLY)

add_executable(SFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SFML ${SFML_LIBRARIES})
endif()