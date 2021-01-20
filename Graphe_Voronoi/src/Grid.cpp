/**
    Contient toutes les fonctions appartenant aux classes Grid et SitesLibrairies
    nécessaires pour créer un graphe de "grille" et construire ses bibliothèques
    @file Grid.cpp
    @author Emie Lafourcade, Johanna Trost
    @version 1.0 12/12/20
*/

#include "Grid.h"

Grid::Grid(const int L, const int C) //Constructeur avec paramètres
{
    for (int i = 0; i < L * C; i++) //On fait un tableau de taille L*C
    {
        Noeud nouveau;
        nouveau.hauteur = 0;  //On met la hauteur de tous les noeuds à 0
        g.push_back(nouveau); //On met le noeud à la suite dans le tableau
    }

    col = C;  //Le nombre de(g.colonnes de la grille est C
    line = L; //Le nombre de lignes de la grille est L
}

Grid::Grid(const Grid &copie) //Constructeur par copie
{

    col = copie.col;
    line = copie.line;
    for (unsigned int i = 0; i < copie.g.size(); i++)
    {
        Noeud nouveau;
        nouveau.hauteur = copie.g[i].hauteur;
        g.push_back(nouveau);
    }
}

Grid::Grid(const string fichier) //Constructeur avec fichier
{
    // ouvrir fichier
    ifstream input(fichier);

    if (!input)
    {
        cerr << "Ne pas pouvoir ouvrir le fichier : " << fichier << endl;
    }
    else
    {
        vector<int> vec((istream_iterator<int>(input)), istream_iterator<int>());
        col = vec[0];
        line = vec[1];
        for (vector<int>::size_type i = 2; i != vec.size(); i++)
        {
            Noeud nouveau;
            nouveau.hauteur = vec[i];
            g.push_back(nouveau);
        }
    }
    //Close The File
    input.close();
}

int Grid::getTaille() const
{
    return col * line;
}

int Grid::getLine() const
{
    return line;
}

int Grid::getCol() const
{
    return col;
}

void Grid::affichage()
{
    int n = 0;
    for (int i = 0; i < line; i++) //On parcours les lignes
    {
        for (int j = 0; j < col; j++) //On parcours les(g.colonnes
        {
            cout << g[n].hauteur << "  ";
            n++;
        }

        cout << endl;
    }
}

void Grid::modifhauteur(const int i, const int j, const int h)
{
    if (i < line && j < col && i >= 0 && j >= 0) //On verifie que le noeud (i,j) existe
        g[indice(i, j)].hauteur = h;             //on lui met la hauteur h
    else
        cout << "ce noeud n'existe pas" << endl;
}

int Grid::indice(const int i, const int j)
{
    if (i < line && j < col && i >= 0 && j >= 0) //On verifie que le noeud (i,j) existe
        return i * col + j;                      //On retourne son indice dans la tableau
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

int Grid::colonne(const int indice)
{
    if ((unsigned int)indice < g.size() && indice >= 0) //On verifie que l'indice du noeud est dans le tableau
        return indice % col;                            //On retourne la(g.colonne de la grille dans laquelle le noeud est
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

int Grid::ligne(const int indice)
{
    if ((unsigned int)indice < g.size() && indice >= 0) //On verifie que l'indice du noeud est dans le tableau
        return indice / col;                            //On retourne la ligne de la grille dans laquelle le noeud est
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

int Grid::hauteur(const int indice)
{
    if ((unsigned int)indice < g.size() && indice >= 0) //On verifie que l'indice du noeud est dans le tableau
        return g[indice].hauteur;                       //On retourne sa hauteur
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

bool Grid::existNord(const int i)
{
    if (i < line && i >= 0) //On verifie que la ligne du noeud est dans la grille
        return i - 1 >= 0;  //On retourne si la ligne d'au dessus existe
    else
    {
        // cout << "ce noeud n'existe pas" << endl;
        return false; //On retourne faux si le noeud n'existe pas
    }
}

bool Grid::existSud(const int i)
{
    if (i < line && i >= 0)  //On verifie que la ligne du noeud est dans la grille
        return i + 1 < line; //On retourne si la ligne d'au dessous existe

    else
    {
        // cout << "ce noeud n'existe pas" << endl;
        return false; //On retourne faux si le noeud n'existe pas
    }
}

bool Grid::existEst(const int j)
{
    if (j < col && j >= 0)  //On verifie que la(g.colonne du noeud est dans la grille
        return j + 1 < col; //On retourne si la(g.colonne à sa droite existe
    else
    {
        // cout << "ce noeud n'existe pas" << endl;
        return false; //On retourne faux si le noeud n'existe pas
    }
}

bool Grid::existOuest(const int j)
{
    if (j < col && j >= 0) //On verifie que la(g.colonne du noeud est dans la grille
        return j - 1 >= 0; //On retourne si la(g.colonne à sa gauche existe
    else
    {
        // cout << "ce noeud n'existe pas" << endl;
        return false; //On retourne faux si le noeud n'existe pas
    }
}

int Grid::indiceNord(const int i, const int j)
{
    if (i < line && j < col && i >= 0 && j >= 0) //On verifie que le noeud (i,j) existe
    {
        if (existNord(i))             //On verifie que son voisin Nord existe
            return (i - 1) * col + j; //On retourne son indice dans le tableau
        else
            return -2; //On retourne -2 si le voisin n'existe pas
    }
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

int Grid::indiceSud(const int i, const int j)
{
    if (i < line && j < col && i >= 0 && j >= 0) //On verifie que le noeud (i,j) existe
    {
        if (existSud(i))              //On verifie que son voisin Sud existe
            return (i + 1) * col + j; //On retourne son indice dans le tableau
        else
            return -2; //On retourne -2 si le voisin n'existe pas
    }
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

int Grid::indiceEst(const int i, const int j)
{
    if (i < line && j < col && i >= 0 && j >= 0) //On verifie que le noeud (i,j) existe
    {
        if (existEst(j))              //On verifie que son voisin Est existe
            return i * col + (j + 1); //On retourne son indice dans le tableau
        else
            return -2; //On retourne -2 si le voisin n'existe pas
    }
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

int Grid::indiceOuest(const int i, const int j)
{
    if (i < line && j < col && i >= 0 && j >= 0) //On verifie que le noeud (i,j) existe
    {
        if (existOuest(j))            //On verifie que son voisin Ouest existe
            return i * col + (j - 1); //On retourne son indice dans le tableau
        else
            return -2; //On retourne -2 si le voisin n'existe pas
    }
    else
    {
        cout << "ce noeud n'existe pas" << endl;
        return -1; //On retourne -1 si le noeud n'existe pas
    }
}

float Grid::distanceVoisin(const int indiceA, const int indiceB)
{
    int diffAB = hauteur(indiceA) - hauteur(indiceB);
    return sqrt(1 + diffAB * diffAB); // distance euclidienne
}

vector<int> SitesLibrairies::vecVoisins(const int indice, Grid graphe)
{
    vector<int> vec;
    int i = graphe.ligne(indice);
    int j = graphe.colonne(indice);

    int x = graphe.indiceOuest(i, j); //On récupère l'indice du fils Ouest
    if (x != -1 && x != -2)           //Si il existe bien on le met dans le vecteur
        vec.push_back(x);

    x = graphe.indiceNord(i, j); //On récupère l'indice du fils Nord
    if (x != -1 && x != -2)      //Si il existe bien on le met dans le vecteur
        vec.push_back(x);

    x = graphe.indiceEst(i, j); //On récupère l'indice du fils Est
    if (x != -1 && x != -2)     //Si il existe bien on le met dans le vecteur
        vec.push_back(x);

    x = graphe.indiceSud(i, j); //On récupère l'indice du fils Sud
    if (x != -1 && x != -2)     //Si il existe bien on le met dans le vecteur
        vec.push_back(x);

    return vec;
}

SitesLibrairies::SitesLibrairies(Grid &g, const string fichier /*=""*/, vector<int> indiceDepart /*=vector<int>()*/)
{
    // remgridLibrairiesi indiceDepart avec valeurs du fichier si un fichier est donné
    if (fichier != "")
    {
        // ouvrir fichier
        ifstream input(fichier);

        if (!input)
        {
            cerr << "Echec ouverture fichier : " << fichier << endl;
        }
        else
        {
            vector<int> vec((istream_iterator<int>(input)), istream_iterator<int>());
            for (vector<int>::size_type i = 0; i != vec.size(); i++)
            {
                indiceDepart.push_back(vec[i]);
            }
        }
        //Close The File
        input.close();
    }

    // init de table gridLibrairies qui memorise les infos necessaires au parcours
    for (int i = 0; i < g.getTaille(); i++)
    {
        NoeudLibrairies nouveau;
        nouveau.distance = INT32_MAX;      //On met la distance de tous les noeuds à MAX
        nouveau.pere = INT32_MAX;          //On met les pères de tous les noeuds à MAX
        nouveau.coloration = 31;           //On met tous les noeuds à rouge (Couleur à la valeur minimum)
        gridLibrairies.push_back(nouveau); //On met le noeud à la suite dans le tableau
    }

    // parcours de l'ensemble de points de départ (sites)
    for (unsigned int j = 0; j < indiceDepart.size(); j++)
    {
        // Dijkstra

        // tous les sommets sont blancs au début de chaque parcours
        for (unsigned int i = 0; i < gridLibrairies.size(); i++)
        {
            gridLibrairies[i].couleur = 'b';
        }
        // init de point de départ
        gridLibrairies[indiceDepart[j]].pere = -1;
        gridLibrairies[indiceDepart[j]].couleur = 'n';
        gridLibrairies[indiceDepart[j]].distance = 0;
        gridLibrairies[indiceDepart[j]].coloration += j;

        auto cmp = [](const pair<int, int> p1, const pair<int, int> p2) { //fonction qui permet de trouver l'indice du noeud ayant la plus petite distance
            return (p1.second > p2.second);
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp); //Une file de paires<indices de noeud, distance>
        pq.push(make_pair(indiceDepart[j], 0));
        int u; // indice du sommet traité actuellement
        vector<int> voisins;
        while (!pq.empty())
        {
            u = pq.top().first; //On traite le noeud le plus proche de la racine
            pq.pop();
            int v;

            voisins = vecVoisins(u, g); //On mets tous ces voisins dans un vecteur

            for (unsigned int i = 0; i < voisins.size(); i++) // parcourir tous voisins
            {
                v = voisins[i];
                if (gridLibrairies[v].couleur == 'b') //Si le noeud n'a pas déjà été "considéré" (il est blanc)
                {
                    gridLibrairies[v].couleur = 'g'; // gris indique qu'on a déjà "consideré" ce sommet

                    // Si sa distance au noeud racine qu'on traite est inférieur à la distance qu'il indique dans le tableau
                    if (gridLibrairies[v].distance > g.distanceVoisin(v, u) + gridLibrairies[u].distance)
                    {
                        gridLibrairies[v].pere = u;                                                       //u devient le père du noeud
                        gridLibrairies[v].distance = g.distanceVoisin(v, u) + gridLibrairies[u].distance; //Il prend comme distance la distance jusqu'à u
                    }

                    pq.push(make_pair(v, gridLibrairies[v].distance)); //On enfiles le voisins de u pour les traiter ensuite
                }
            }
            gridLibrairies[u].couleur = 'n'; // noir indique que ce sommet était traité
        }
    }

    coloration(g, indiceDepart); // indique quel sommet correspond à quelle librairie
}

void SitesLibrairies::coloration(Grid &g, const vector<int> indiceDepart)
{
    vector<int> indicesSuivants;
    for (unsigned int m = 0; m < gridLibrairies.size(); m++)   //On parcourt tous les noeuds
        for (unsigned int n = 0; n < indiceDepart.size(); n++) //On parcourt les pères
            if (gridLibrairies[m].pere == indiceDepart[n])     //Si un noeud est fils d'un de ces pères
            {
                gridLibrairies[m].coloration = gridLibrairies[indiceDepart[n]].coloration; //Le noeud prend la couleur de son père
                indicesSuivants.push_back(m);                                              //On met ce noeud dans la file
            }

    if (indicesSuivants.size() != 0)    //Si on a encore des fils à colorier
        coloration(g, indicesSuivants); //On appelle la fonction avec comme "indicesSuivants" les noeuds qu'on vient de colorier et qui ont des fils
}

void SitesLibrairies::affichage(const Grid g) const
{
    int n = 0;
    for (int i = 0; i < g.getLine(); i++) //On parcours les lignes
    {
        for (int j = 0; j < g.getCol(); j++) //On parcours les colonnes
        {
            int couleur = gridLibrairies[n].coloration;
            int distance = gridLibrairies[n].distance;

            if (gridLibrairies[n].distance != 0) //Si ce n'est pas un noeud racine on l'affiche de sa couleur
            {
                cout << "\033[1;" << couleur << "m"
                     << distance << "  "
                     << "\033[0m";
            }
            else //Si c'est un noeud racine on le surligne
                cout
                    << "\033[1;" << couleur + 10 << "m"
                    << " " << distance << " "
                    << "\033[0m"
                    << " ";
            n++;
        }

        cout << endl;
    }
}