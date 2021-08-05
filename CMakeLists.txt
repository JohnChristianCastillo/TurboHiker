cmake_minimum_required(VERSION 3.16.5)
project(TurboHiker)

set(CMAKE_CXX_STANDARD 14)

add_executable( TurboHiker
                main.cpp

                TurboHiker.cpp
                TurboHiker.h

                HelperDataTypes.h

                Model/Model.cpp
                Model/Model.h
                Model/EntityMaker.cpp
                Model/EntityMaker.h
                Model/Entity.cpp
                Model/Entity.h
                Model/MainCharacter.cpp
                Model/MainCharacter.h
                Model/Enemy.cpp
                Model/Enemy.h
                Model/StaticHiker.cpp
                Model/StaticHiker.h

                View/View.cpp
                View/View.h

                Singletons/Random.cpp
                Singletons/Random.h
                Singletons/Transformation.cpp
                Singletons/Transformation.h

                Model/Background.cpp
                Model/Background.h

                Controller/Controller.cpp
                Controller/Controller.h

                Discarded.h Observers/LiveScoring.cpp Observers/LiveScoring.h Model/SimpleAI.cpp Model/SimpleAI.h Singletons/Timer.cpp Singletons/Timer.h)

#[[ COMMAND FOR WORKING WITH WINDOWS

include_directories(c:/SFML/include)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TurboHiker ${SFML_LIBRARIES})
endif ()

if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
]]

include_directories(/usr/include)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TurboHiker ${SFML_LIBRARIES})
endif ()

if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
