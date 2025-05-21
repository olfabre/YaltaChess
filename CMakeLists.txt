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

# Liste des fichiers sources
set(SOURCES
    main/main.cpp
    main/Model.cpp
    main/View.cpp
    main/Controller.cpp
    main/HexagonalCubique.cpp
    main/CubeToLabel.cpp
    main/pieces/Pion.cpp
    main/pieces/Cavalier.cpp
    main/pieces/Tour.cpp
    main/pieces/Fou.cpp
    main/pieces/Dame.cpp
    main/pieces/Roi.cpp
    main/cases/Case.cpp
    main/pieces/Piece.cpp
    main/Intro.cpp
    main/ResourceManager.cpp
)

# Liste des fichiers d'en-tête
set(HEADERS
    main/Model.h
    main/View.h
    main/Controller.h
    main/HexagonalCubique.h
    main/CubeToLabel.h
    main/pieces/Piece.h
    main/pieces/Pion.h
    main/pieces/Cavalier.h
    main/pieces/Tour.h
    main/pieces/Fou.h
    main/pieces/Dame.h
    main/pieces/Roi.h
)

# Création de l'exécutable avec tous les fichiers sources
add_executable(SFML_MVC_YaltaChess ${SOURCES})

# Ajout des bibliothèques SFML
target_link_libraries(SFML_MVC_YaltaChess PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# Standard C++17
target_compile_features(SFML_MVC_YaltaChess PRIVATE cxx_std_17)
target_compile_definitions(SFML_MVC_YaltaChess PRIVATE _LIBCPP_ENABLE_CXX17_REMOVED_FILESYSTEM)
target_compile_options(SFML_MVC_YaltaChess PRIVATE -fvisibility=default)

# Inclusion des répertoires pour les headers (y compris sous-dossiers)
target_include_directories(SFML_MVC_YaltaChess PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/main
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces
        ${CMAKE_CURRENT_SOURCE_DIR}/cases
        )
