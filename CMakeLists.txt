cmake_minimum_required(VERSION 3.8)
project(HoardingCppVersion)
set(CMAKE_CXX_STANDARD 14)
set(GPP_ENABLE_WARNINGS "-O0 -Wall -Werror -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GPP_ENABLE_WARNINGS}")
set(SOURCE_FILES main.cpp GameState.cpp GameState.h Player.cpp Player.h
        Board.cpp Board.h Space.cpp Space.h CSVReader.cpp CSVReader.h Go.cpp Go.h
        Property.cpp Property.h Rules.cpp Rules.h MonopolyUtility.cpp
        MonopolyUtility.h DiceRoller.cpp DiceRoller.h Move.cpp Move.h
        PropertySet.cpp PropertySet.h PropertyManager.cpp PropertyManager.h FreeParking.cpp FreeParking.h PayBank.cpp PayBank.h Jail.cpp Jail.h GoToJail.cpp GoToJail.h)
add_executable(HoardingCppVersion ${SOURCE_FILES})


