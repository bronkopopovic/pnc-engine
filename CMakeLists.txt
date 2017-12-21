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
        src/hud.cpp
        src/hud.h

        assets/assets.lib
        configs/game.conf
        configs/test_room.conf

        # Character confs
        assets/characters/ch2.conf
        assets/characters/ch4.conf
        assets/characters/chef.conf

        # Room confs
        assets/rooms/studio.conf
        assets/rooms/studio.navmesh
        assets/rooms/test.conf
        assets/rooms/test.navmesh
        )

# Players
configure_file(assets/images/sprite_full.png sprite_full.png COPYONLY)
configure_file(assets/images/ch2_ico.png ch2_ico.png COPYONLY)
configure_file(assets/images/ch4_full.png ch4_full.png COPYONLY)
configure_file(assets/images/ch4_ico.png ch4_ico.png COPYONLY)
configure_file(assets/images/chef_full.png chef_full.png COPYONLY)


# Stuff
configure_file(assets/images/cursor.png cursor.png COPYONLY)
configure_file(assets/images/shop.png shop.png COPYONLY)
configure_file(assets/images/bedroom.png bedroom.png COPYONLY)
configure_file(assets/images/arcade.png arcade.png COPYONLY)

# Studio Room
configure_file(assets/images/studio.png studio.png COPYONLY)
configure_file(assets/images/studio_door1.png studio_door1.png COPYONLY)
configure_file(assets/images/studio_pillar1.png studio_pillar1.png COPYONLY)
configure_file(assets/images/studio_pillar2.png studio_pillar2.png COPYONLY)
configure_file(assets/images/studio_pillar3.png studio_pillar3.png COPYONLY)
configure_file(assets/images/studio_pillar4.png studio_pillar4.png COPYONLY)
configure_file(assets/images/studio_pillar5.png studio_pillar5.png COPYONLY)
configure_file(assets/images/studio_foreground1.png studio_foreground1.png COPYONLY)

# Test Room
configure_file(assets/images/svg_test.png svg_test.png COPYONLY)

# Fonts
configure_file(assets/fonts/menu.ttf menu.ttf COPYONLY)
configure_file(assets/fonts/verbs.ttf verbs.ttf COPYONLY)

# Music
configure_file(assets/music/track1.ogg track1.ogg COPYONLY)
configure_file(assets/music/track2.ogg track2.ogg COPYONLY)

add_executable(SFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SFML ${SFML_LIBRARIES})
endif()