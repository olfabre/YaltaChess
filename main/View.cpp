#include "View.h"
#include <cmath>
#include <stdexcept>
#include "Model.h"
#include "cases/Case.h"
#include "ResourceManager.h"
#include <array>
#include <cmath> // pour std::cos et std::sin



using namespace sf;
using namespace std;

sf::Vector2f rotateAroundCenter(const sf::Vector2f& point, const sf::Vector2f& center, float angleRad) {
    float dx = point.x - center.x;
    float dy = point.y - center.y;
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);
    return sf::Vector2f{
            center.x + dx * cosA - dy * sinA,
            center.y + dx * sinA + dy * cosA
    };
}

namespace {
    void drawOutlinedSprite(RenderTarget& target,
                            const Sprite& sprite,
                            Color outlineColor,
                            float thickness)
    {
        // dessine 8 copies décalées pour simuler un liseré
        array<Vector2f,8> offsets = {
                Vector2f(-thickness, -thickness),
                Vector2f(-thickness,  0.f),
                Vector2f(-thickness,  thickness),
                Vector2f( 0.f,       -thickness),
                Vector2f( 0.f,        thickness),
                Vector2f( thickness, -thickness),
                Vector2f( thickness,  0.f),
                Vector2f( thickness,  thickness)
        };
        for (auto& off : offsets) {
            Sprite outline = sprite;
            outline.setColor(outlineColor);
            outline.move(off);
            target.draw(outline);
        }
        // Dessine le sprite original par-dessus
        target.draw(sprite);
    }
}


YaltaChessView::YaltaChessView(RenderWindow &win, const Model &mod)
        : window(win), model(mod), eventText(tempFont)
{
    // Charge la police (unique, tirée de ton dossier de ressources)
    // Charge la police (SFML 3)
    // Charger la police Google font
    // SFML 3 : charger la police
    // Charge la police SFML 3 depuis le répertoire de l'exécutable
    auto execPath = filesystem::current_path();
    auto fontPath = execPath / "Roboto-Regular.ttf";
    if (!coordFont.openFromFile(fontPath.string()))
        throw runtime_error("Impossible de charger Roboto-Regular.ttf");

    // Configure le texte d'événement
    eventText.setFont(coordFont);
    eventText.setString("Bienvenue dans Yalta Chess !");
    eventText.setCharacterSize(24);
    eventText.setFillColor(Color::White);
    eventText.setPosition(Vector2f(20.f, 20.f)); // Position en haut à gauche

    // Initialise tous les labels
    initBorderLabels();

    // --- initialisation de la vue tournée du plateau ---
    float BOARD_SIZE = 1000.f;
    float OFFSET     = 50.f;
    Vector2f mid(OFFSET + BOARD_SIZE/2.f, OFFSET + BOARD_SIZE/2.f);

    boardView = window.getDefaultView();   // copie les dimensions de la fenêtre
    boardView.setCenter(mid);              // centre géométrique du plateau
    boardView.setRotation(sf::degrees(-60.f));           // +60° sens horaire ; mettez -60.f si besoin



    blinkClock.restart();

}


void YaltaChessView::initBorderLabels()
{
    const float WIDTH    = 1000.f;
    const float OFFSET   = 50.f;
    const float OUTSET   = 25.f;  // distance label → bordure
/*

    const vector<vector<string>> labels = {
           { "8","7","6","5","9","10","11","12" },
           { "l","k","j","i","e","f","g","h"       },
           { "12","11","10","9","4","3","2","1"    },
           { "h","g","f","e","d","c","b","a"       },
           { "1","2","3","4","5","6","7","8"       },
           { "a","b","c","d","i","j","k","l"       }
    };
*/


    const vector<vector<string>> labels = {
            { "l","k","j","i","e","f","g","h" }, //good
            { "12","11","10","9","4","3","2","1"       },//good
            { "h","g","f","e","d","c","b","a"    }, //good
            { "1","2","3","4","5","6","7","8"       }, //good
            { "a","b","c","d","i","j","k","l"       },
            { "8","7","6","5","9","10","11","12"       } //good
    };





    Vector2f mid(WIDTH/2.f + OFFSET, WIDTH/2.f + OFFSET);
    float size   = WIDTH/2.f;
    float height = sqrt(size*size - (size/2.f)*(size/2.f));

    // Sommets du hexagone (flat-top)
    vector<Vector2f> v123 = {
            {-size*0.5f, -height}, { size*0.5f, -height},
            { size,        0      }, { size*0.5f,  height},
            {-size*0.5f,  height}, {-size,       0      }
    };

    for (int k = 0; k < 6; ++k)
    {
        const auto& sideLabels = labels[k];
        int count = int(sideLabels.size());

        // Extrémités de l'arête k
        Vector2f A   = mid + v123[k];
        Vector2f B   = mid + v123[(k+1)%6];
        Vector2f dir = B - A;

        // Angle « naturel » de l'arête
        float baseAngle = atan2(dir.y, dir.x) * 180.f / 3.14159265f + 90.f;

        for (int j = 0; j < count; ++j)
        {
            // position sur l'arête
            float t   = (j + 0.5f) / float(count);
            Vector2f pos = A + dir * t;

            // décale vers l'extérieur de OUTSET px
            Vector2f out = pos - mid;
            float len = sqrt(out.x*out.x + out.y*out.y);
            if (len > 0.f) {
                out /= len;
                pos += out * OUTSET;
            }

            // création du texte
            Text txt(coordFont, sideLabels[j], 18);
            txt.setFillColor(Color::Black);

            // centre l'origine du texte
            auto b = txt.getLocalBounds();
            txt.setOrigin(
                    Vector2f{
                            b.position.x + b.size.x/2.f,
                            b.position.y + b.size.y/2.f
                    }
            );

            // override angles pour côtés lettres
            // on décide si la face k est numérique (1,3,5) ou alphabétique (0,2,4)
            bool isNumberSide = (k == 1 || k == 3 || k == 5);
// on ajoute –45° pour les chiffres, +45° pour les lettres
            float extraAngle = isNumberSide ? +360.f : +90.f;
// on oriente chaque label à baseAngle + décalage souhaité
            txt.setRotation(sf::degrees(baseAngle + extraAngle));


            //txt.setRotation(degrees(angleDeg));
            txt.setPosition(pos);
            borderLabels.push_back(txt);
        }
    }
}


// Version "brute" sans rotation finale
sf::Vector2f YaltaChessView::gridToPixelRaw(const Vector2i& g) const
{
    const float W = 1000.f;
    const float O = 50.f;
    // même calcul que gridToPixel **avant** la rotation
    Vector2f mid(W/2.f + O, W/2.f + O);
    float size   = W/2.f;
    float side   = size/2.f;
    float height = std::sqrt(size*size - side*side);

    // vecteurs vers les 6 sommets (flat-top)
    std::array<Vector2f,6> v123 = {{
                                           {-size*0.5f, -height},
                                           { size*0.5f, -height},
                                           { size,        0      },
                                           { size*0.5f,  height},
                                           {-size*0.5f,  height},
                                           {-size,       0      }
                                   }};

    // même logique de sextant que dans gridToPixel
    static const std::array<std::pair<Vector2i,Vector2i>,6> intervals = {{
                                                                                 {{0,4},{0,4}},
                                                                                 {{0,4},{4,8}},
                                                                                 {{8,12},{4,8}},
                                                                                 {{8,12},{8,12}},
                                                                                 {{4,8},{8,12}},
                                                                                 {{4,8},{0,4}}
                                                                         }};

    for (int z = 0; z < 6; ++z) {
        auto [ix, iy] = intervals[z];
        if (g.x >= ix.x && g.x < ix.y && g.y >= iy.x && g.y < iy.y) {
            // fraction à l'intérieur du sextant
            float rx1 = (g.x % 4)     /4.f;
            float ry1 = (g.y % 4)     /4.f;
            float mid_r_x = (rx1 + (rx1+1/4.f))*0.5f;
            float mid_r_y = (ry1 + (ry1+1/4.f))*0.5f;

            // calcul de la position "à plat"
            Vector2f s1 = v123[z] * 0.5f;
            Vector2f s2 = v123[(z + 2) % 6] * 0.5f;
            Vector2f corner = mid + v123[(z + 4) % 6];
            Vector2f U1 = v123[(z + 1) % 6] * ry1 - s1 * ry1 + s2;
            Vector2f midU = v123[(z + 1) % 6] * mid_r_y - s1 * mid_r_y + s2;
            return corner + s1 * mid_r_y + midU * mid_r_x;
        }
    }
    return mid; // fallback
}



// 1) Ce helper instantie les mêmes v123, vabc, intervals que Model
Vector2f YaltaChessView::gridToPixel(const Vector2i& g) const {
    const float W = 1000.f;
    const float O = 50.f;
    Vector2f mid(W/2.f + O, W/2.f + O);
    float size   = W/2.f;
    float side   = size/2.f;
    float height = std::sqrt(size*size - side*side);

    // vecteurs vers les 6 sommets
    std::array<Vector2f,6> v123 = {{
                                           Vector2f(-size*0.5f, -height),
                                           Vector2f( size*0.5f, -height),
                                           Vector2f( size,        0      ),
                                           Vector2f( size*0.5f,  height),
                                           Vector2f(-size*0.5f,  height),
                                           Vector2f(-size,       0      )
                                   }};

    // vecteurs internes
    std::array<Vector2f,6> vabc = {{
                                           Vector2f(-height * std::cos(30.f * M_PI/180.f),
                                                    -height * std::sin(30.f * M_PI/180.f)),
                                           Vector2f(0.f, -height),
                                           Vector2f( height * std::cos(30.f * M_PI/180.f),
                                                     -height * std::sin(30.f * M_PI/180.f)),
                                           Vector2f( height * std::cos(30.f * M_PI/180.f),
                                                     height * std::sin(30.f * M_PI/180.f)),
                                           Vector2f(0.f, height),
                                           Vector2f(-height * std::cos(30.f * M_PI/180.f),
                                                    height * std::sin(30.f * M_PI/180.f))
                                   }};

    // intervalles sextants: on appelle explicitement le constructeur de pair
    static const std::array<std::pair<Vector2i,Vector2i>,6> intervals = {{
                                                                                 std::pair<Vector2i,Vector2i>(Vector2i( 0, 4), Vector2i( 0, 4)),
                                                                                 std::pair<Vector2i,Vector2i>(Vector2i( 0, 4), Vector2i( 4, 8)),
                                                                                 std::pair<Vector2i,Vector2i>(Vector2i( 8,12), Vector2i( 4, 8)),
                                                                                 std::pair<Vector2i,Vector2i>(Vector2i( 8,12), Vector2i( 8,12)),
                                                                                 std::pair<Vector2i,Vector2i>(Vector2i( 4, 8), Vector2i( 8,12)),
                                                                                 std::pair<Vector2i,Vector2i>(Vector2i( 4, 8), Vector2i( 0, 4))
                                                                         }};

    for (int z = 0; z < 6; ++z) {
        auto [ix, iy] = intervals[z];
        if (g.x >= ix.x && g.x < ix.y && g.y >= iy.x && g.y < iy.y) {
            float rx1 = (g.x % 4) / 4.f;
            float ry1 = (g.y % 4) / 4.f;
            float rx2 = (g.x % 4 + 1) / 4.f;
            float ry2 = (g.y % 4 + 1) / 4.f;
            float mid_r_x = (rx1 + rx2) * 0.5f;
            float mid_r_y = (ry1 + ry2) * 0.5f;

            Vector2f s1 = v123[z] * 0.5f;
            Vector2f s2 = v123[(z + 2) % 6] * 0.5f;
            Vector2f corner = mid + v123[(z + 4) % 6];

            Vector2f U1 = vabc[(z + 1) % 6] * ry1 - s1 * ry1 + s2;
            Vector2f midU = vabc[(z + 1) % 6] * mid_r_y - s1 * mid_r_y + s2;

            //return corner + s1 * mid_r_y + midU * mid_r_x;
            Vector2f pos = corner + s1 * mid_r_y + midU * mid_r_x;
            // Rotation de -90° autour du centre
            //const float angle = M_PI / 3; // -90° en radians
           //pos = rotateAroundCenter(pos, mid, angle);
            return pos;
        }
    }

    return mid; // fallback
}





void YaltaChessView::draw()
{
    const float BOARD_SIZE = 1000.f;
    const float OFFSET = 50.f;
    const float BORDER_WIDTH = 50.f;
    Vector2f mid(OFFSET + BOARD_SIZE/2.f, OFFSET + BOARD_SIZE/2.f);
    float size = BOARD_SIZE/2.f;
    float side = size/2.f;
    float height = sqrt(size*size - side*side);
    array<Vector2f,6> v = {
            Vector2f(-size*0.5f, -height),
            Vector2f( size*0.5f, -height),
            Vector2f( size,        0      ),
            Vector2f( size*0.5f,  height),
            Vector2f(-size*0.5f,  height),
            Vector2f(-size,       0      )
    };
    window.setView(boardView);
    window.clear(Color::Black);

    // Dessin du texte d'événement (en mode coordonnées fenêtre)
    window.setView(window.getDefaultView());
    window.draw(eventText);
    window.setView(boardView);

    // Dessin du plateau et des labels (inchangé)
    ConvexShape whiteBorder;
    whiteBorder.setPointCount(6);
    for (int i = 0; i < 6; ++i) {
        Vector2f dir = v[i];
        float len = sqrt(dir.x*dir.x + dir.y*dir.y);
        if (len != 0) dir /= len;
        Vector2f pt = mid + v[i] + dir * BORDER_WIDTH;
        whiteBorder.setPoint(i, pt);
    }
    whiteBorder.setFillColor(Color::White);
    window.draw(whiteBorder);
    ConvexShape outline;
    outline.setPointCount(6);
    for (int i = 0; i < 6; ++i)
        outline.setPoint(i, whiteBorder.getPoint(i));
    outline.setFillColor(Color::Transparent);
    outline.setOutlineColor(Color::Black);
    outline.setOutlineThickness(2.f);
    window.draw(outline);


    // --- MISE À JOUR DES ptr de pièce dans chaque case ---
    // (nécessaire pour que c->estOccupee() et c->getPiece() fonctionnent)
    for (const auto& c : model.getCases()) {
        c->setPiece(nullptr);
    }

    // Puis on relie chaque Piece* à sa Case* en O(1)
    for (const auto& p : model.getPieces()) {
        Case* ca = model.getCaseAtCube(p->getPositionCube());
        if (ca) {
            ca->setPiece(p.get());
        }
    }

    // dessin de toutes les cases en mode normal
    for (const auto& c : model.getCases()) {
        window.draw(*c);
    }

// dessin des cases surlignées (sélection uniquement) en orange
    for (Case* c : highlightedCases) {
        if (selectedCase && c == selectedCase) {
            ConvexShape highlight = c->getShape(); // copie
            // Orange pour la sélection
            highlight.setFillColor(Color(255, 165, 0, 230)); // orange opaque
            highlight.setOutlineColor(Color::Black);
            highlight.setOutlineThickness(2.f);
            window.draw(highlight);
        }
    }

    // dessin de la case sous le curseur en orange
    if (hoveredCase) {
        ConvexShape highlight = hoveredCase->getShape();   // copie
        highlight.setFillColor(Color(255, 220, 130, 240)); // orange
        highlight.setOutlineColor(Color::Black);
        highlight.setOutlineThickness(2.f);
        window.draw(highlight);
    }


    // =========== NOUVEAU ===========
    // On a fini tout ce qui doit être dans la vue « échiquier ».
    // On repasse maintenant au repère normal pour les labels,
    // les noms de joueurs, les menus, etc.
    //window.setView(window.getDefaultView());
    // ===============================

    for (auto& txt : borderLabels)
        window.draw(txt);
    //window.setView(window.getDefaultView());





// --- DESSIN DES JOUEURS ---
    auto const& players = model.getPlayers();            // vector<PlayerInfo>
    int currentIdx      = model.getCurrentPlayerIdx();    // qui doit jouer

// Centre et rayon pour placer les infos autour de l'échiquier
    //Vector2f mid(OFFSET + BOARD_SIZE/2.f, OFFSET + BOARD_SIZE/2.f);
    float    infoRadius = BOARD_SIZE/2.f + 30.f;

    // Durée d'un cycle (en secondes)
    const float blinkPeriod = 0.5f;
// true pendant la première moitié du cycle, false pendant la seconde
    bool blinkOn = fmod(blinkClock.getElapsedTime().asSeconds(), blinkPeriod*2.f) < blinkPeriod;


// Pour chaque joueur, on choisit un angle en fonction de sa couleur
    for (size_t i = 0; i < players.size(); ++i) {
        auto const& p = players[i];

        // 1) Calcule l'angle (en degrés) selon p.color
        float angleDeg = 0.f;
        switch (p.color) {
            //case BLANC: angleDeg = -90.f; break;  // en haut
            //case ROUGE: angleDeg = -30.f; break;  // à droite
            //case NOIR:  angleDeg = 150.f; break;  // à gauche
            case BLANC: angleDeg =  90.f;  break;  // en bas
            case ROUGE: angleDeg = -150.f; break;  // en haut-gauche
            case NOIR:  angleDeg =  -30.f; break;  // en haut-droite

        }

        //float boardRotDeg   = boardView.getRotation().asDegrees();     // -60°
        float worldAngleDeg = angleDeg + boardView.getRotation().asDegrees();                  // ex : 90 + (-60) = 30
        float a = worldAngleDeg * 3.14159265f / 180.f;

        // 2) Positionne le texte & le cercle
        Vector2f pos = mid + Vector2f(std::cos(a), std::sin(a)) * infoRadius;

        float viewRotDeg  = boardView.getRotation().asDegrees();   // ex. -60
        float labelRotDeg = angleDeg - viewRotDeg;


        // Cercle indicateur (vert si actif, rouge sinon)
        CircleShape dot(8.f);
        //dot.setOrigin(8.f, 8.f);
        dot.setOrigin({8.f, 8.f});
        dot.setPosition(pos + Vector2f(-40.f, 0.f));
        //dot.setFillColor((int)i == currentIdx ? Color::Green : Color::Red);
        //window.draw(dot);
        if ((int)i == currentIdx) {
            // joueur actif : vert qui clignote
            if (blinkOn)
                dot.setFillColor(Color::Green),
                        window.draw(dot);
        }
        else {
            // autres joueurs : point rouge fixe
            dot.setFillColor(Color::Red);
            window.draw(dot);
        }

        // Texte du prénom ("Vous" pour l'humain)
        Text label(coordFont,
                   p.isHuman ? "Vous" : p.name,
                   20);
        label.setFillColor(Color::Yellow);

        // **Orienter le texte** en sens anti-horaire vers le haut
        label.setRotation(sf::degrees(-viewRotDeg  - 120.f));
        // aligne un peu à droite du point
        label.setPosition(pos + Vector2f(-30.f, -10.f));
        window.draw(label);
    }















    for (const auto& p : model.getPieces()) {
        // Prépare le sprite de la pièce
        string key = p->getTypeName() + "_" +
                     (p->getCouleur() == BLANC ? "White" :
                      p->getCouleur() == NOIR  ? "Black" : "White");
        const auto& tex = ResourceManager::get(key);

        Sprite spr(tex);
        auto ts = tex.getSize();
        // SFML3 : setOrigin prend un Vector2f
        spr.setOrigin({ ts.x/2.f, ts.y/2.f });
        Cube c = p->getPositionCube();
        Vector2f pos = gridToPixel(Hex::cubeVersGrille(c));
        spr.setPosition(pos);
        float undo = -boardView.getRotation().asDegrees();   // si vue = -60°, undo = +60°
        spr.setRotation(sf::degrees(-60.0f));
        if (p->getCouleur() == ROUGE)
            spr.setColor(Color(195,83,51));





        // Juste après avoir positionné spr :
        float thickness    = 1.f;
        Color outlineColor = (p->getCouleur() == BLANC ? Color(0,0,0) : Color(246,243,232));
        // offsets pour simuler 8 directions
        array<Vector2f,8> offsets = {
                Vector2f(-thickness, -thickness),
                Vector2f(-thickness,  0.f),
                Vector2f(-thickness,  thickness),
                Vector2f( 0.f,       -thickness),
                Vector2f( 0.f,        thickness),
                Vector2f( thickness, -thickness),
                Vector2f( thickness,  0.f),
                Vector2f( thickness,  thickness)
        };

// 1) on récupère et place le sprite de mask
        const auto& maskTex = ResourceManager::getMask(key);
        Sprite maskSpr(maskTex);
        maskSpr.setOrigin({ maskTex.getSize().x/2.f,
                            maskTex.getSize().y/2.f });
        maskSpr.setPosition(pos);
        maskSpr.setRotation(sf::degrees(-60.0f));
        maskSpr.setColor(outlineColor);

// 2) on dessine 8 copies décalées du mask pour former le liseré
        for (auto& off : offsets) {
            Sprite s = maskSpr;
            s.move(off);
            window.draw(s);
        }

// 3) enfin on dessine la pièce originale
        window.draw(spr);
    }







    window.display();
}


// View.cpp
void YaltaChessView::setHighlightedCases(const std::vector<Case*>& cases) {
    highlightedCases = cases;
}

void YaltaChessView::setEventMessage(const string& message) {
    eventText.setString(message);
}
