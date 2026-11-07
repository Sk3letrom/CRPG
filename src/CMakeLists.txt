# CRPG Game Executable

# Collect all source files
set(SOURCES
    main.cpp
    core/Game.cpp
    core/Time.cpp
    input/Input.cpp
    player/Player.cpp
    rendering/Camera.cpp
    rendering/Renderer.cpp
    resources/AssetManager.cpp
    world/Map.cpp
    world/TileMap.cpp
)

# Create executable
add_executable(CRPG ${SOURCES})

# Include directories
target_include_directories(CRPG PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../third\ part/tileson
    ${CMAKE_CURRENT_SOURCE_DIR}/../third\ part/tileson/include
)

# Link libraries
target_link_libraries(CRPG PRIVATE
    raylib
    nlohmann_json::nlohmann_json
)

# Platform specific settings
if(APPLE)
    target_link_libraries(CRPG PRIVATE "-framework CoreVideo")
    target_link_libraries(CRPG PRIVATE "-framework IOKit")
elseif(UNIX)
    target_link_libraries(CRPG PRIVATE m)
endif()
