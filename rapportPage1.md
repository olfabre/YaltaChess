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

```cmake
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

```cmake
cmake_minimum_required(VERSION 3.25.2)
project(CMakeSFMLProject LANGUAGES CXX) 
```

- Spécifie la version minimale de CMake requise.
- Définit le nom de ton projet (`CMakeSFMLProject`) et précise que c'est un projet en **C++**.

```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
```

- Change l'emplacement des exécutables générés.
- Ici, les exécutables seront placés dans le dossier `/build/bin`.

```cmake
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0)
FetchContent_MakeAvailable(SFML)
```

- **`FetchContent`** est une méthode puissante qui télécharge et configure automatiquement des bibliothèques externes.
- Ici, il télécharge et configure la bibliothèque **SFML** (version 3.0.0) directement depuis GitHub.

```cmake
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

```cmake
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





### Étape 4: mise en place de la structure MVC



Voici ma structure optimisée avec SFML 3 pour bien démarrer mon projet. 

Cette base inclut les bonnes pratiques et une architecture claire:

- **Séparation claire** : Chaque composant respecte bien le pattern MVC.
- **Lisibilité** : Les classes sont courtes et claires.
- **Extensibilité** : Cette structure permet d'ajouter facilement des entités, des scènes ou d'autres fonctionnalités.
-  **Optimisation SFML 3** : Utilisation de `std::optional` pour améliorer la gestion d'événements.

L'architecture **MVC** (Modèle-Vue-Contrôleur) est une structure de code puissante qui permet de séparer la logique métier, l'affichage et la gestion des interactions utilisateur. 



L'architecture MVC se divise en trois parties principales :

- **Modèle (Model)** → Gestion des données et logique métier.
- **Vue (View)** → Gestion de l'affichage graphique avec SFML.
- **Contrôleur (Controller)** → Gestion des événements et interactions utilisateur.



```bash
/YaltaChess
│ 
│── /main
│   ├── CMakeLists.txt
│   ├── Model.h
│   ├── Model.cpp
│   ├── View.h
│   ├── View.cpp
│   ├── Controller.h
│   ├── Controller.cpp
│   └── main.cpp
│── /build_main   <-- (sera créé lors de la compilation)
```



1 fichier `/main/Model.h`

Gère les données, les règles du jeu, et la logique métier.

```cpp
#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>

class Model {
public:
    Model();  
    void update();  // Mise à jour des données du modèle (ex : position des pièces d'échecs).
};

#endif // MODEL_H
```





1 fichier `/main/Model.cpp`

Gère les données, les règles du jeu, et la logique métier.

```cpp
#include "Model.h"

Model::Model() {
    // Initialisation des données (ex : position initiale des pièces)
}

void Model::update() {
    // Exemple : Mettre à jour les positions des pièces, gérer les règles du jeu, etc.
}
```

**Rôle du `Model` :**

- Stocke les informations clés (ex : position des pièces d'échecs).
- Met à jour les données en fonction des règles métier (ex : déplacement légal des pièces).



1 fichier `/main/View.h`

Gère l'affichage et le rendu graphique à l'écran.

```cpp
#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

class View {
public:
    View(sf::RenderWindow& window);
    void render(); // Dessine les éléments graphiques
private:
    sf::RenderWindow& m_window; // Référence vers la fenêtre SFML
};

#endif // VIEW_H
```





1 fichier `/main/View.cpp`

Gère l'affichage et le rendu graphique à l'écran.

```cpp
#include "View.h"

View::View(sf::RenderWindow& window) : m_window(window) {}

void View::render() {
    m_window.clear(sf::Color::Black);  // Couleur de fond par défaut
    // Dessine les éléments graphiques ici: les pièces, l'échiquier, etc
    m_window.display();
}
```



**Rôle du `View` :**

- Affiche les éléments graphiques.
- Récupère les informations du `Model` pour afficher correctement les données à l'utilisateur.
- Ne contient **aucune** logique métier.







1 fichier `/main/Controller.h`

Gère les entrées utilisateur (clics, clavier) et met à jour le modèle et la vue.

```cpp
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"

class Controller {
public:
    Controller(Model& model, View& view);
    void processEvents(sf::RenderWindow& window); // Gère les événements SFML
private:
    Model& m_model;
    View& m_view;
};

#endif // CONTROLLER_H
```





1 fichier `/main/Controller.cpp`

Gère les entrées utilisateur (clics, clavier) et met à jour le modèle et la vue.

```cpp
#include "Controller.h"

Controller::Controller(Model& model, View& view) : m_model(model), m_view(view) {}

void Controller::processEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
      // Ici, gestion des clics sur les pièces d'échecs, les déplacements, etc.
    }
}
```

**Rôle du `Controller` :**

- Récupère les événements utilisateurs (clics, mouvements de souris, etc.).
- Met à jour le `Model` en fonction de ces interactions.
- Informe la `View` des changements pour que l'affichage soit correct.



1 fichier `/main/main.cpp`

Point d'entrée principal du programme qui connecte le modèle, la vue et le contrôleur.

```cpp
#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "SFML MVC Example");
    window.setFramerateLimit(144);

    Model model; // Création du modèle
    View view(window); // Création de la vue (lié à la fenêtre)
    Controller controller(model, view); // Création du contrôleur

    while (window.isOpen()) {
        controller.processEvents(window);  // Gestion des événements (entrées utilisateurs)
        model.update();                    // Mise à jour des données
        view.render();                     // Rendu graphique et mise à jour affichage
    }

    return 0;
}
```



**Rôle du `main` :**

- Initialise les trois composants (`Model`, `View`, `Controller`).
- Utilise une boucle infinie pour :
  - Traiter les événements avec le **Controller**.
  - Mettre à jour les données avec le **Model**.
  - Afficher les résultats avec la **View**.



**Cycle de fonctionnement du code (Flux MVC)**

Voici le cycle complet de fonctionnement :

1. **Démarrage du programme**
    → Le `main` crée une fenêtre SFML et initialise les trois composants.
2. **Événements utilisateur (input)**
    → Le `Controller` intercepte les interactions (ex : clic sur une pièce).
    → Il met à jour le `Model` en conséquence (ex : déplacement d'une pièce).
3. **Mise à jour des données**
    → Le `Model` applique les règles du jeu (ex : vérifie si le déplacement est légal).
4. **Affichage (output)**
    → La `View` récupère les informations du `Model` et met à jour l’écran.
5. **Répétition**
    → Ce cycle se répète tant que la fenêtre est ouverte.









Je dois aussi modifier le fichier ` /main/CMakeLists.txt`

```cmake
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

# Inclusion de tous les fichiers du dossier actuel (car CMakeLists.txt est dans /main)
file(GLOB_RECURSE SRC_FILES ./*.cpp)

# Création de l'exécutable avec tous les fichiers sources
add_executable(SFML_MVC_YaltaChess ${SRC_FILES})

# Ajout des bibliothèques SFML
target_link_libraries(SFML_MVC_YaltaChess PRIVATE sfml-graphics sfml-window sfml-system)

# Standard C++17
target_compile_features(SFML_MVC_YaltaChess PRIVATE cxx_std_17)

# Inclusion des répertoires pour les headers
target_include_directories(SFML_MVC_YaltaChess PRIVATE ${CMAKE_SOURCE_DIR}/main)

```

#### **1. Définition de la version de CMake**

```cmake
cmake_minimum_required(VERSION 3.25.2)
```

- Cette ligne indique la version minimale de CMake requise.
   → **`VERSION 3.25.2`** est nécessaire car SFML 3 utilise des fonctionnalités modernes de CMake.



#### **2. Nom du projet**

```cmake
project(SFML_MVC_YaltaChess LANGUAGES CXX)
```

- Définit le nom du projet (`SFML_MVC_YaltaChess`).
- **`LANGUAGES CXX`** indique que ton projet est en C++.



#### **3. Définir le répertoire de sortie des exécutables**

```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
```

- Cette ligne précise que l'exécutable sera généré dans le dossier `/bin` à l'intérieur du répertoire de build (`build_main`).
   → Cela permet de garder une structure propre avec un exécutable bien séparé des fichiers de compilation.



#### **4. Gestion de la bibliothèque SFML via `FetchContent`**

```cmake
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)
```

- **`include(FetchContent)`** : Active le module `FetchContent` qui permet de télécharger et de configurer des bibliothèques directement depuis GitHub.
- **`FetchContent_Declare()`** : Indique à CMake d'aller chercher SFML 3 sur le dépôt GitHub officiel.
-  **`GIT_TAG 3.0.0`** : Utilise la version 3.0.0 de SFML (la plus récente).
- **`FetchContent_MakeAvailable(SFML)`** : Télécharge et configure automatiquement SFML dans ton projet.



#### **5. Inclusion des fichiers sources**

```cmake
file(GLOB_RECURSE SRC_FILES ./*.cpp)
```

- Cette commande recherche **récursivement** tous les fichiers `.cpp` dans le répertoire `/main` (car ton `CMakeLists.txt` est dans `/main`).
   → Cela permet d'ajouter automatiquement tous tes fichiers sources sans les lister manuellement.
   → **Exemple :** Si tu ajoutes `Piece.cpp`, il sera automatiquement inclus.



#### **6. Création de l'exécutable**

```cmake
add_executable(SFML_MVC_YaltaChess ${SRC_FILES})
```

- Cette ligne crée l'exécutable nommé **`SFML_MVC_YaltaChess`** en utilisant tous les fichiers contenus dans la variable `${SRC_FILES}`.
   → C'est l'étape clé qui génère ton programme final.



#### **7. Ajout des bibliothèques SFML**

```cmake
target_link_libraries(SFML_MVC_YaltaChess PRIVATE sfml-graphics sfml-window sfml-system)
```

- **`target_link_libraries`** : Relie ton projet aux bibliothèques nécessaires de SFML :

- **`sfml-graphics`** : Pour la gestion des graphismes (sprites, formes, etc.).
- **`sfml-window`** : Pour la gestion des fenêtres et des événements.
- **`sfml-system`** : Pour les outils de gestion du temps et les utilitaires.



#### **8. Activation du standard C++17**

```cmake
target_compile_features(SFML_MVC_YaltaChess PRIVATE cxx_std_17)
```

-  Active la norme **C++17** pour ton projet.
   → SFML 3 est conçu pour fonctionner avec cette version ou supérieure.



#### **9. Inclusion des répertoires de headers**

```cmake
target_include_directories(SFML_MVC_YaltaChess PRIVATE ${CMAKE_SOURCE_DIR}/main)
```

- Indique à CMake d'inclure le dossier `/main` pour retrouver les fichiers `.h` (headers).
   → Cela permet que les `#include "Model.h"` ou `#include "Controller.h"` fonctionnent sans chemin compliqué.



#### **10. Commandes finales pour compiler et exécuter**

Dans ton terminal, à la racine de ton projet :

##### ➤ **Générer les fichiers de build**

```bash
cmake -B build_main -S main
```

- Généra le répertoire `build_main` avec les fichiers de compilation.



##### ➤ **Compiler le projet**

```bash
cmake --build build_main
```

-  Compile ton projet et génère l'exécutable dans `build_main/bin/SFML_MVC_YaltaChess`.



##### ➤ **Exécuter ton projet**

```bash
./build_main/bin/SFML_MVC_YaltaChess
```

-  Lance ton application SFML.





### Étape 5: création de la hierarchie orientée objet des pièces 

Chaque pièce d’échecs Yalta sera un objet dérivant d'une classe abstraite commune (`Piece`), selon ce schéma :

```scss
Piece (abstraite)
 │
 ├── Roi
 ├── Dame
 ├── Tour
 ├── Fou
 ├── Cavalier
 └── Pion
```



**Organisation des fichiers**

````bash
/main
│── Model.h
│── Model.cpp
│── View.h
│── View.cpp
│── Controller.h
│── Controller.cpp
│── main.cpp
│
└── /pieces
    ├── Piece.h
    ├── Piece.cpp
    ├── Roi.h
    ├── Roi.cpp
    ├── Dame.h
    ├── Dame.cpp
    ├── Tour.h
    ├── Tour.cpp
    ├── Fou.h
    ├── Fou.cpp
    ├── Cavalier.h
    ├── Cavalier.cpp
    ├── Pion.h
    └── Pion.cpp

````



Fichier `pieces/Piece.h`

```cpp
#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

enum Couleur { BLANC, NOIR, ROUGE };

// Classe abstraite représentant une pièce du jeu Yalta
class Piece {
protected:
    sf::Vector2i position; // Position sur l'échiquier
    Couleur couleur;       // Couleur de la pièce (joueur)

public:
    Piece(sf::Vector2i pos, Couleur coul);
    virtual ~Piece() = default;

    // Vérifie la validité du déplacement spécifique à chaque pièce
    virtual bool mouvementValide(sf::Vector2i nouvellePos) const = 0;

    // Dessine graphiquement la pièce (SFML)
    virtual void dessiner(sf::RenderWindow& window) const = 0;

    // Accesseurs
    sf::Vector2i getPosition() const;
    void setPosition(sf::Vector2i nouvellePos);
    Couleur getCouleur() const;
};

#endif
```



Fichier `pieces/Piece.cpp`

```cpp
#include "Piece.h"

Piece::Piece(sf::Vector2i pos, Couleur coul)
        : position(pos), couleur(coul) {}

sf::Vector2i Piece::getPosition() const {
    return position;
}

void Piece::setPosition(sf::Vector2i nouvellePos) {
    position = nouvellePos;
}

Couleur Piece::getCouleur() const {
    return couleur;
}
```



Un exemple de pièce du jeu qui va heriter de `piece` : fichiers `Roi.h` et `Roi.cpp`



```cpp
#ifndef ROI_H
#define ROI_H

#include "Piece.h"

// Classe Roi héritant de Piece
class Roi : public Piece {
public:
    Roi(sf::Vector2i pos, Couleur coul);
    bool mouvementValide(sf::Vector2i nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;
};

#endif
```



```cpp
#include "Roi.h"
#include <cmath>

Roi::Roi(sf::Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Roi::mouvementValide(sf::Vector2i nouvellePos) const {
    int dx = std::abs(nouvellePos.x - position.x);
    int dy = std::abs(nouvellePos.y - position.y);
    return (dx <= 1 && dy <= 1);
}

void Roi::dessiner(sf::RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}

```



### Étape 6: création de la hierarchie orientée objet des cases

La structure avec les cases intégrées

```bash
/main
│── Model.h
│── Model.cpp
│── View.h
│── View.cpp
│── Controller.h
│── Controller.cpp
│── main.cpp
│
├── /pieces
│   ├── Piece.h
│   ├── Piece.cpp
│   ├── Roi.h
│   ├── Roi.cpp
│   ├── Dame.h
│   ├── Dame.cpp
│   ├── Tour.h
│   ├── Tour.cpp
│   ├── Fou.h
│   ├── Fou.cpp
│   ├── Cavalier.h
│   ├── Cavalier.cpp
│   ├── Pion.h
│   └── Pion.cpp
│
└── /cases (nouveau dossier)
    ├── Case.h
    └── Case.cpp


```



Fichier `cases/Case.h`

```cpp
#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include "../pieces/Piece.h"

class Case {
private:
    sf::Vector2i position;
    Piece* piece; // Pointeur vers une pièce ou nullptr si vide

public:
    Case(sf::Vector2i pos);

    bool estOccupee() const;
    Piece* getPiece() const;
    void setPiece(Piece* p);
    sf::Vector2i getPosition() const;

    void dessiner(sf::RenderWindow& window);
};

#endif

```



Fichier cases/Case.cpp

```cpp
#include "Case.h"

Case::Case(sf::Vector2i pos) : position(pos), piece(nullptr) {}

bool Case::estOccupee() const { return piece != nullptr; }

Piece* Case::getPiece() const { return piece; }

void Case::setPiece(Piece* p) { piece = p; }

sf::Vector2i Case::getPosition() const { return position; }

void Case::dessiner(sf::RenderWindow& window) {
    sf::RectangleShape carre({100.f, 100.f});
    carre.setPosition(position.x * 100.f, position.y * 100.f);
    carre.setFillColor((position.x + position.y) % 2 ? sf::Color(209,139,71) : sf::Color(255,206,158));
    window.draw(carre);
}

```



Quelques  modifications doivent être apportée:



Fichier `cases/Case.h`

```cpp
// Case.h (correction)
#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include "../pieces/Piece.h"

class Case {
private:
    sf::Vector2i position;
    Piece* piece; // Pointeur vers une pièce ou nullptr

public:
    Case(sf::Vector2i pos);

    bool estOccupee() const;
    Piece* getPiece() const;
    void setPiece(Piece* p);
    sf::Vector2i getPosition() const;

    // Correction : ajout de const ici
    void dessiner(sf::RenderWindow& window) const;
};

#endif

```



Fichier `cases/Case.cpp`

```cpp
#include "Case.h"

Case::Case(sf::Vector2i pos) : position(pos), piece(nullptr) {}

bool Case::estOccupee() const { return piece != nullptr; }

Piece* Case::getPiece() const { return piece; }

void Case::setPiece(Piece* p) { piece = p; }

sf::Vector2i Case::getPosition() const { return position; }

// Correction ici :
void Case::dessiner(sf::RenderWindow& window) const {
    sf::RectangleShape carre({100.f, 100.f});
    carre.setPosition(sf::Vector2f(position.x * 100.f, position.y * 100.f));
    carre.setFillColor((position.x + position.y) % 2 ? sf::Color(209,139,71) : sf::Color(255,206,158));
    window.draw(carre);
}

```



Fichier `CMakeLists.txt` pour prendre en compte les pièces et cases

```txt
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

```



on compile de nouveau

```bash
cmake -B build_main -S main
cmake --build build_main

./build_main/bin/SFML_MVC_YaltaChess 
```

<img src="1.jpg" alt="1" style="zoom:50%;" />





Notre échiquier actuel utilise des cases carrées disposées dans un tableau 2D simple. C'est une première étape. Or, l'échiquier Yalta est hexagonal avec 96 cases trapézoïdales!

Pour gérer ce type spécifique d’échiquier, il faut adapter ta structure graphique et logique.

**Comment dessiner l'échiquier Yalta sous SFML clairement**

- Chaque case sera dessinée comme un **polygone SFML** (`sf::ConvexShape`).

```cpp
void Model::initialiserEchiquierYalta() {
    std::vector<std::vector<sf::Vector2f>> coordCases = {
            {{400,400},{450,380},{500,400},{450,420}},
            {{500,400},{550,380},{600,400},{550,420}},
            {{345.f,825.f},{395.f,805.f},{445.f,825.f},{395.f,845.f}},
     //etc...
    };
```

- Chaque case aura une coordonnée spécifique (personnalisée).
- On stockera dans notre classe `Case` chaque position sous forme de polygone (`sf::ConvexShape`) et on l’affichera ensuite directement.

**Problème rencontré pour la création de l'échiquier avec cette méthode**

En effet, cela signifie que je serais obligé de prendre toutes les coordonnées des 96 cases à partir du logiciel Photoshop sur une vraie photo d'un échiquier Yalta en fond.

Le travail reste tout de même **colossal**.

**Y'aurait-il une autre solution ?**

oui d'après mes recherches sur internet, j'ai trouvé une autre solution. Beaucoup moins chronophage et longue à réaliser:



1. La structure globale

   ![3](3.jpg)

- On part d'un **hexagone** (une forme à 6 côtés égaux).
- Cet hexagone central est divisé en **6 zones** distinctes appelées **"sextants"** (comme 6 parts égales d'un gâteau hexagonal).
- Chaque sextant contient des **petites cases** (cellules) dans lesquelles les pièces d'échecs peuvent se déplacer.

   

   

2. La forme de chaque case

- Contrairement aux cases habituelles (carrées), ici chaque case est un **quadrilatère** (4 côtés, mais pas forcément égaux).
- Pourquoi des quadrilatères ?
   Car c’est la forme géométrique qui permet de parfaitement remplir chaque sextant pour obtenir l’échiquier hexagonal global sans trous ni chevauchements.



3. Comment on dessine précisément chaque case ?

Voici simplement comment c’est fait dans ton programme :

Étape par étape :

**Étape 1 :** On choisit un **point central** de l’écran (`mid`) :

```cpp
mid = (largeur_ecran / 2, hauteur_ecran / 2)
```

**Étape 2 :** Autour de ce point central, on calcule **6 points extérieurs** pour créer l'hexagone global :

```cpp
points_hexagone = [
  haut-gauche, haut-droite, droite,
  bas-droite, bas-gauche, gauche
]
```

**Étape 3 :** Pour chaque sextant (zone), on prend deux points consécutifs de l'hexagone pour dessiner les cases à l’intérieur en effectuant des calculs géométriques précis (on appelle ça **interpolation linéaire**).

**Étape 4 :** On utilise ces points pour calculer les coins de chaque petite case (quadrilatère). Cela donne à chaque petite case sa position précise sur l'écran.



4. Alternance de couleurs des cases

Chaque case est alternativement colorée en blanc ou en noir selon une règle mathématique simple :

- Si la somme des coordonnées de la case (en x, y, et la zone) est paire, la case est blanche ; sinon, elle est noire :

```cpp
couleur = ((x + y + zone) % 2 == 0) ? blanc : noir;
```

Cela crée l’effet échiquier caractéristique.



5. Centrage final sur l’écran

Pour que l’échiquier soit parfaitement centré dans ta fenêtre graphique :

On décale toutes les cases d'une même distance (ici 50 pixels) vers la droite et vers le bas, afin que l'échiquier apparaisse exactement au milieu de l'écran :

```cpp
centre_final = (largeur_echiquier / 2 + décalage_x, hauteur_echiquier / 2 + décalage_y)
```



En résumé, dessiner l’échiquier Yalta, c'est :

- Créer un hexagone, puis le découper en 6 zones égales.
- Remplir chaque zone par des cases à 4 côtés, calculées mathématiquement.
- Alterner blanc/noir les cases.
- Décaler légèrement le tout pour le centrer sur l'écran.



Rappel pour compiler

```bash
cmake -B build_main -S main
cmake --build build_main

./build_main/bin/SFML_MVC_YaltaChess 
```



### Étape 7: création d'une fenêtre intro

Je me suis servi d'une I.A. générative pour créer l'image png qui porte le nom de mon application.

On a crée une classe Intro pour typer un objet de type Intro. On a donc créer un objet Intro qui s'occupe

d'afficher l'image d'introduction

```cpp
Intro intro(window);
if (!intro.initialize()) { // Charge l'image intro.png
    return -1; // Si l'image n'est pas trouvée, le programme s'arrête.
}
```

On a ajouté une boucle de façon que tant que l'intro n'est pas finie (elle dure 5 secondes), la fenetre reste ouverte et montre l'image.

Dans le fichier `intro.cpp`on s'occupe de charger l'image (initialisation) et redimensionne l'image pour qu'elle s'adapte à la fenêter du jeu (1100 x 1100)

Nous avons aussi intégré la polcie d'ecriture  **Press Start 2P** récupérée chez google font https://fonts.google.com/share?selection.family=Press+Start+2P pour faire un titre au dessus de l'image











https://chatgpt.com/share/67d899f9-7af8-8009-a9f4-23be488ebe83

Cette nouvelle implémentation peut crée un échiquier Yalta avec :

- Des cases hexagonales (obtenues en rotant des carrés)

- Trois branches distinctes !

- Une alternance de cases blanches et noires

- Une structure propre et modulaire

