#All rights reserved to pastafarians from ETI
message("\n\nThe fantasy program given by God")
message("Come now, one, two, three! Overlap")
message("Come now, one, two, three! Escape death\n")

cmake_minimum_required(VERSION 2.8)

#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")

Find_Package(SFML REQUIRED)

project( ETI_SHOOTER )

set( GAME_SRC
    main.cpp
    CDebugDraw.cpp
    CGame.cpp
    CResourceManager.cpp
    CScreenManager.cpp
    CScript.cpp
    CSettingsParser.cpp
    CButton.cpp
	API4Lua.cpp
    CSoundManager.cpp
    CTextBox.cpp
    CInputHandler.cpp
    CAnimation.cpp
    CAnimatedSprite.cpp
	CPlayer.cpp
	CQuadTree.cpp
)

if(SFML_FOUND)
    message("SFML został wykryty!")
    include_directories(${SFML_INCLUDE_DIR})
    add_executable(ETI_SHOOTER ${GAME_SRC})
#win zuo
    if(WIN32)
        target_link_libraries(ETI_SHOOTER sfml-main sfml-window sfml-graphics sfml-system)
#inne
    else(WIN32)
        SET (CMAKE_CXX_FLAGS    "-Wall -std=c++11")
        target_link_libraries(ETI_SHOOTER sfml-window sfml-graphics sfml-system lua sfml-audio thor)
    endif(WIN32)
else(SFML_FOUND)
    message(Nie znaleziono SFML!)
endif(SFML_FOUND)
