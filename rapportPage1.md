# YaltaChess

Ceci est le rapport qui explique toutes mes démarches, mes recherches pour le codage du jeu en C++.

J'y intégre tous les résultats de mes recherches au fur-et-à-mesure de mes recherches et de l'avancement de mon projet.

## Sources

 CMake SFML Project Template https://github.com/SFML/cmake-sfml-project





## Choix initiaux et contraintes

Le codage se fera en C++ en architecture Model Vue Controler. Le jeu aura une interface graphique. Pour intégrer le graphisme, je vais utiliser SFML 3.0.0 qui est une version que je dois compiler et compatible avec mon système d'exploitation. en effet , je code sur mon MacOS Catalina qui est un vieux modèle, je dois systématiquement vérifier la comptabilité des librairies.



## Étape 1: compréhension, réflexion, recherche

Pour les deux premières séances de TP, j'ai préféré me concentrer sur la recherche d'informations, bien comprendre les technologies que je devrai utiliser et comment les utiliser dans une architecture MVC.

Pour l'instant je ne me concentre pas sur les aspects spéficiques du code: design patterns, algorithmes avancées mais davantage dans la mise en route du projet, l'architecture MVC et les relations entre les entités.

Mon principal but est débuter correctement le projet avec une bases solides et une organisation adaptée pour coder proprement en MVC.



## Étape 2: installation de SFML 

```bash
brew install sfml
```

L'installation a été très longue (1 heure) 

Je vérifie l'installation s'est bien passée

```bash
pkg-config --modversion sfml-system
3.0.0
```

L'installation de SFML 3 s'est bien passée.



## Étape 3: tester SFML



J'ai crée un fichier `CMakePresets.json`

Ce fichier sert à **simplifier la configuration de ton projet avec CMake** en définissant des paramètres prédéfinis. Il permet de centraliser les options importantes pour que tu n'aies pas à les taper manuellement à chaque fois.

```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "default",
      "description": "default settings",
      "generator": "Unix Makefiles",
      "binaryDir": "${workspaceFolder}/build",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug"
      }
    }
  ]
}
```

### À quoi ça sert ?

- 📂 **`binaryDir`** : C'est l'endroit où ton projet va être compilé (au lieu de mélanger les fichiers générés avec ton code source).
- 🐞 **`CMAKE_BUILD_TYPE`** : Ici, le mode `Debug` est activé, ce qui inclut des informations utiles pour déboguer ton code (comme les symboles de débogage).
  

j'ai crée un dossier `main` où je vais placer le code principal

Dans ce dossier, j'ai crée un fichier `CMakeLists.txt`

Ce fichier est **le cœur de ton projet** sous CMake. Il décrit comment ton projet doit être configuré, compilé et lié.

```txt
cmake_minimum_required(VERSION 3.25.2)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0)
FetchContent_MakeAvailable(SFML)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)
```

```txt
cmake_minimum_required(VERSION 3.25.2)
project(CMakeSFMLProject LANGUAGES CXX) 
```

- Spécifie la version minimale de CMake requise.
- Définit le nom de ton projet (`CMakeSFMLProject`) et précise que c'est un projet en **C++**.

```txt
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
```

- Change l'emplacement des exécutables générés.
- Ici, les exécutables seront placés dans le dossier `/build/bin`.

```txt
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0)
FetchContent_MakeAvailable(SFML)
```

- **`FetchContent`** est une méthode puissante qui télécharge et configure automatiquement des bibliothèques externes.
- Ici, il télécharge et configure la bibliothèque **SFML** (version 3.0.0) directement depuis GitHub.

```txt
add_executable(main main.cpp)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)
```

- **`add_executable`** crée ton exécutable principal (`main`) en utilisant ton fichier `main.cpp`.
-  **`target_link_libraries`** indique que ton exécutable doit être lié avec **SFML** (le module graphique).
-  **`target_compile_features`** précise que ton code utilise les fonctionnalités du standard **C++17**.





J'ai crée un fichier `main.cpp` ou le contneu sera provisoir 

```cpp
#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "YaltaChess");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
```





### Commandes pour compiler mon code principal

```bash
cmake -B build // par defaut mais dans mon cas, c'est la ligne du bas
cmake -B build_main -S main
```

La commande initiale (`cmake -B build`) **génère les fichiers de configuration** (Makefiles, cache, etc.) et télécharge les dépendances (comme SFML via `FetchContent`). C'est normal que ce soit plus long la première fois.



```bash
cmake --build build // par defaut mais dans mon cas, c'est la ligne du bas
cmake --build build_main
```

La commande suivante (`cmake --build build`) **compile tout le projet**, y compris les dépendances. C'est aussi plus long au premier passage. Cette commande **ne recompilera que les fichiers modifiés**, rendant la compilation beaucoup plus rapide.(builds "incrémentiels" )





j'ai crée un dossier `tests` où je vais placer le code pour tester 

J'ai créer un fichier `testSFML3.cpp`

```cpp
#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake Test SFML");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
```

j'ai créé un fichier `CMakeLists.txt`

```txt
cmake_minimum_required(VERSION 3.25.2)
project(TestSFML LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0)
FetchContent_MakeAvailable(SFML)

add_executable(testSFML3 testSFML3.cpp)
target_link_libraries(testSFML3 PRIVATE sfml-graphics)
target_compile_features(testSFML3 PRIVATE cxx_std_17)
```







### Commandes pour lancer le code de test SFML



```bash
cmake -B build_test -S tests   
```

Génèration des fichiers de configuration

```bash
cmake --build build_test
```

Compilation de tout le projet

```bash
./build_test/testSFML3
```

Lancement du test







