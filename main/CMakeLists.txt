cmake_minimum_required(VERSION 3.25.2)
project(SFML_MVC_YaltaChess LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

# Inclusion de tous les fichiers .cpp du dossier courant ET des sous-dossiers (pieces et cases)
file(GLOB_RECURSE SRC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cases/*.cpp
        )

# Création de l'exécutable avec tous les fichiers sources
add_executable(SFML_MVC_YaltaChess ${SRC_FILES})

# Ajout des bibliothèques SFML
target_link_libraries(SFML_MVC_YaltaChess PRIVATE sfml-graphics sfml-window sfml-system)

# Standard C++17
target_compile_features(SFML_MVC_YaltaChess PRIVATE cxx_std_17)

# Inclusion des répertoires pour les headers (y compris sous-dossiers)
target_include_directories(SFML_MVC_YaltaChess PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces
        ${CMAKE_CURRENT_SOURCE_DIR}/cases
        )
