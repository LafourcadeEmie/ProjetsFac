/**
    Programme pou l'utilisation de Grid et SitesLibrairies
    @file main.cpp
    @author Emie Lafourcade, Johanna Trost
    @version 1.0 12/12/20
*/

#include "Grid.h"
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <iostream>

int main(int argc, const char **argv)
{
  srand(time(NULL));
  Grid *grid;
  string filenameGrid = "None";
  string filenameSites = "None";

  try
  {
    if (argv[1] != NULL)
    {
      filenameGrid = argv[1];
    }

    cout << "------------------------------------------------------\n"
         << "\tLa grille \n"
         << "------------------------------------------------------" << endl;
    cout << "\n";

    if (filenameGrid == "None")
    {
      // creation d'une grille avec nb cols et lignes et modif d'hauteur
      cout << "Grille generée de manière aléatoire: "
           << ":\n"
           << endl;
      int colonnes = (rand() % 8 + 5);
      int lignes = (rand() % 8 + 5);
      // int colonnes = 20;
      // int lignes = 20;
      grid = new Grid(lignes, colonnes);
      for (int h = 0; h < lignes * colonnes; h++)
        grid->modifhauteur(grid->ligne(h), grid->colonne(h), rand() % 40 + 10);
      grid->affichage();
      cout << endl;
    }
    else
    {
      // creation de la grille à partir du fichier txt
      cout << "Grille du fichier " << filenameGrid << ":\n"
           << endl;
      grid = new Grid(filenameGrid);
      grid->affichage();
      cout << endl;
    }

    if (argv[1] != NULL && argv[2] != NULL)
    {
      filenameSites = argv[2];
    }
    else
    {
      filenameSites = "None";
    }

    cout << "------------------------------------------------------\n"
         << "\tLibrairies de la grille \n"
         << "------------------------------------------------------" << endl;
    cout << "\n";

    if (filenameSites == "None")
    {
      int nbPoints = 4;
      vector<int> indicesSites;
      int indice;

      cout << "Indices des sites: " << endl;
      for (int x = 0; x < nbPoints - 1; x++)
      {
        indice = rand() % ((grid->getLine() * grid->getCol()) - 1);
        cout << indice << ", ";
        indicesSites.push_back(indice);
      }
      indice = rand() % ((grid->getLine() * grid->getCol()) - 1);
      cout << indice << "\n"
           << endl;
      indicesSites.push_back(indice);

      SitesLibrairies librairies(*grid, "", indicesSites);
      librairies.affichage(*grid);
    }
    else
    {
      SitesLibrairies librairies(*grid, filenameSites);
      librairies.affichage(*grid);
      cout << endl;
    }

    if (argv[1] != NULL && argv[2] != NULL && argv[3] != NULL && argv[4] != NULL)
    {
      int i = atoi(argv[3]);
      int j = atoi(argv[4]);

      cout << "\nLa hauteur à (" << i << "," << j << ") est: " << grid->hauteur(grid->indice(i, j)) << endl;

      int index = grid->indiceOuest(i, j);
      if (index != -1 && index != -2)
      {
        cout << "\t La hauteur à l'ouest est: " << grid->hauteur(index) << endl;
      }
      else
      {
        cout << "\tPas de sommet à l'ouest" << endl;
      }

      index = grid->indiceNord(i, j);
      if (index != -1 && index != -2)
      {
        cout << "\t La hauteur au nord est: " << grid->hauteur(index) << endl;
      }
      else
      {
        cout << "\tPas de sommet au nord" << endl;
      }

      index = grid->indiceEst(i, j);
      if (index != -1 && index != -2)
      {
        cout << "\t La hauteur à l'est est: " << grid->hauteur(index) << endl;
      }
      else
      {
        cout << "\tPas de sommet à l'est" << endl;
      }

      index = grid->indiceSud(i, j);
      if (index != -1 && index != -2)
      {
        cout << "\t La hauteur au sud est: " << grid->hauteur(index) << endl;
      }
      else
      {
        cout << "\tPas de sommet au sud" << endl;
      }
    }

    delete grid;
  }
  catch (exception &e)
  {
    cerr << "exception caught: " << e.what() << '\n';
  }

  return EXIT_SUCCESS;
}
