#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include "Model.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <unistd.h>  // Pour getcwd

class GameLogger : public GameObserver {
private:
    ofstream logFile;
    string getCurrentTimestamp() {
        auto now = chrono::system_clock::now();
        auto time = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    string getLogFilename() {
        auto now = chrono::system_clock::now();
        auto time = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&time), "%Y%m%d_%H%M%S");
        
        // Obtenir le chemin absolu du répertoire de travail
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            cout << "Répertoire de travail actuel : " << cwd << endl;
            return string(cwd) + "/logs/game_" + ss.str() + ".log";
        } else {
            cerr << "Erreur : Impossible d'obtenir le répertoire de travail" << endl;
            return "logs/game_" + ss.str() + ".log";
        }
    }

public:
    GameLogger() {
        try {
            // Obtenir le chemin absolu du dossier logs
            char cwd[1024];
            string logsDir;
            if (getcwd(cwd, sizeof(cwd)) != nullptr) {
                logsDir = string(cwd) + "/logs";
                cout << "Chemin absolu du dossier logs : " << logsDir << endl;
            } else {
                logsDir = "logs";
                cerr << "Erreur : Impossible d'obtenir le répertoire de travail" << endl;
            }

            // Créer le dossier logs s'il n'existe pas
            if (!filesystem::exists(logsDir)) {
                cout << "Création du dossier logs..." << endl;
                if (!filesystem::create_directory(logsDir)) {
                    cerr << "Erreur : Impossible de créer le dossier " << logsDir << endl;
                    cerr << "Erreur : " << strerror(errno) << endl;
                    return;
                }
                cout << "Dossier logs créé avec succès" << endl;
            } else {
                cout << "Le dossier logs existe déjà" << endl;
            }
            
            // Créer un nouveau fichier de log avec horodatage
            string filename = getLogFilename();
            cout << "Tentative de création du fichier de log : " << filename << endl;
            
            // Vérifier les permissions du dossier
            if (filesystem::status(logsDir).permissions() == filesystem::perms::none) {
                cerr << "Erreur : Pas de permissions sur le dossier " << logsDir << endl;
                return;
            }
            
            logFile.open(filename, ios::app);
            if (logFile.is_open()) {
                logFile << "\n=== Nouvelle partie démarrée à " << getCurrentTimestamp() << " ===\n";
                logFile.flush();  // Force l'écriture immédiate
                cout << "Fichier de log créé avec succès : " << filename << endl;
            } else {
                cerr << "Erreur : Impossible de créer le fichier de log " << filename << endl;
                cerr << "Erreur : " << strerror(errno) << endl;
            }
        } catch (const exception& e) {
            cerr << "Exception lors de la création du logger : " << e.what() << endl;
        }
    }

    ~GameLogger() {
        if (logFile.is_open()) {
            logFile << "=== Partie terminée à " << getCurrentTimestamp() << " ===\n\n";
            logFile.flush();
            logFile.close();
        }
    }

    void onPieceMoved(Piece* piece, const Cube& from, const Cube& to) override {
        if (!logFile.is_open()) {
            cerr << "Erreur : Fichier de log non ouvert dans onPieceMoved" << endl;
            return;
        }
        
        string couleur;
        switch(piece->getCouleur()) {
            case BLANC: couleur = "Blanc"; break;
            case NOIR: couleur = "Noir"; break;
            case ROUGE: couleur = "Rouge"; break;
        }
        
        logFile << getCurrentTimestamp() << " - Déplacement : " 
                << couleur << " " << piece->getTypeName()
                << " de (" << from.x << "," << from.y << "," << from.z << ")"
                << " vers (" << to.x << "," << to.y << "," << to.z << ")\n";
        logFile.flush();
    }

    void onPieceCaptured(Piece* captured) override {
        if (!logFile.is_open()) {
            cerr << "Erreur : Fichier de log non ouvert dans onPieceCaptured" << endl;
            return;
        }
        
        string couleur;
        switch(captured->getCouleur()) {
            case BLANC: couleur = "Blanc"; break;
            case NOIR: couleur = "Noir"; break;
            case ROUGE: couleur = "Rouge"; break;
        }
        
        logFile << getCurrentTimestamp() << " - Capture : "
                << couleur << " " << captured->getTypeName() << " capturé\n";
        logFile.flush();
    }

    void onGameStateChanged(bool isGameOver, const string& message) override {
        if (!logFile.is_open()) {
            cerr << "Erreur : Fichier de log non ouvert dans onGameStateChanged" << endl;
            return;
        }
        
        if (isGameOver) {
            logFile << getCurrentTimestamp() << " - Fin de partie : " << message << "\n";
            logFile.flush();
        }
    }
};

#endif 