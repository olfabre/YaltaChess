# YaltaChess

Ceci est le rapport qui explique toutes mes démarches, mes recherches pour le codage du jeu en C++.



## Choix initiaux et contraintes

Le codage se fera en C++ en architecture Model Vue Controler. Le jeu aura une interface graphique. Pour intégrer le graphisme, je vais utiliser SFML 3.0.0 qui est une version que je dois compiler et compatible avec mon système d'exploitation. en effet , je code sur mon MacOS Catalina qui est un vieux modèle, je dois systématiquement vérifier la comptabilité des librairies.



## Étape 1: recherche informations

Pour les deux premières séances de TP, j'ai préféré me concentrer sur la recherche d'informations, bien comprendre les technologies que je devrai utiliser et comment les utiliser dans une architecture MVC.

Pour l'instant je ne me concentre pas sur les aspects spéficiques du code: design patterns, algorithmes avancées. 

Mon principal but pour le début du projet est de bien initier le projet avec une bonne organisation et de bonnes bases.



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



## Étpae 3: tester SFML

