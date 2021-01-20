# Lifap6 – Graphe d’un terrain et diagramme de Voronoï

Ce programme orienté objet met en œuvre un graphe sous forme de grille. Cela permet de modéliser une carte géographique, dont les coordonnées sont les sommets du graphe.
En outre, le graphe est utilisé pour calculer son diagramme de Voronoï en utilisant l'algorithme de Dijkstra. Ce diagramme est une décomposition de l'espace en régions(librairies). Celles-ci sont déterminées par un ensemble donné de coordonnées, appelés ici sites. Chaque librairie est déterminée par exactement un site et comprend toutes les coordonnées qui sont plus proches du site de la librairie que de tout autre site par rapport à la métrique euclidienne.

## Installation

Pour pouvoir utiliser ce programme, vous devez avoir installé un compilateur C++ (gcc).

## Utilisation

1. ouvrir un terminal
2. dirigez-vous dans le dossier qui doit au moins contenir les dossier bin, obj, src et data (cd /mon/projet/répertoire)
3. Pour exécuter le script, utilisez :

```
make
./bin/main [argv]
```

## Arguments expliqués

Vous pouvez exécuter le programme avec au plus 4 et au moins 0 arguments [argv]. Il convient de mentionner que tous les arguments sont des arguments de position, ce qui signifie que l'ordre des arguments est fixe.  

###### `argv[1] <string>` - la grille
exemple : `</chemin/vers/> ./bin/main data/magrille.txt `  

Le fichier d'entré spécifient votre graphe de grille. Si vous ne voulez pas utiliser cet argument, votre grille sera générée de manière aléatoire. Dans ce cas, vous devez mettre `None` au lieu du nom du fichier, à moins que vous ne donniez d'autres arguments.  
Sinon le fichier doit avoir un format spécifique pour que le programme fonctionne correctement. La première ligne du fichier correspond au nombre de colonnes et nombre de lignes de la grille qui suit. Ensuite, les chiffres dans la grille sont les "hauteurs" de chaque sommet du graphe.
L'exemple suivant montre un fichier txt en format correct :

```
4 3
12 45 3 99
1 78 5 14
19 6 25 44
```

###### `argv[2] <string>` - les sites

exemple : `</chemin/vers/> ./bin/main [argv1] messites.txt `

Le fichier d'entré spécifie les indices des sites dans le diagramme de Voronoï. Si vous ne voulez pas utiliser cet argument, 4 sites seront choisis au hasard. Dans ce cas, vous devez mettre `None` au lieu du nom du fichier, à moins que vous ne donniez d'autres arguments après cet argument.  
Voici un example du fichier txt (il est possible d'utiliser plusieurs lignes) :
` 1 3 2 8`

###### `argv[3] <int> argv[4] <int>` - (i, j) ligne colonne

exemple : `</chemin/vers/> ./bin/main [argv1] [argv2] 1 2 `

Ces arguments spécifient une certaine ligne et une certaine colonne dans votre grille. L'un ne peut pas être utilisé sans l'autre. Si vous ne voulez pas les utiliser, ne mettez rien ici. Sinon, vous obtiendrez la hauteur à cette coordonnée et la hauteur des coordonnées du voisin au nord, au sud, à l'est et à l'ouest.

## Exemples d'exécution du programme

```./bin/main```

```./bin/main data/grille.txt data/sites.txt```

```./bin/main None None 1 2```

```./bin/main data/grille.txt None 0 0```

```./bin/main data/grille.txt data/sites.txt 2 3```

```./bin/main None data/sites.txt```


## Affichage des résultats

En dessous se trouve le résultat produit par:
```./bin/main data/grille.txt data/sites.txt 2 3```


______________________________________________________
	La grille
______________________________________________________
Grille du fichier grille.txt:

	12  45  03  99 	 
	01  78  05  14  
	19  06  25  44  
	66  17  38  02  
	10  09  55  08  
______________________________________________________
	Librairies de la grille
______________________________________________________
<span style="color:red">33</span> 0 <span style="color:red">42 138</span>  
<span style="color:red">44</span>  <span style="color:red">33</span>  <span style="color:red">106</span>  <span style="color:yellow">78</span>  
<span style="color:green">47 60 </span> <span style="color:yellow">55 48</span>  
 0 <span style="color:green">49  42</span> <span style="color:yellow">6</span>    
<span style="color:green">56  57</span> <span style="color:yellow">47</span>  0

	La hauteur à (2,3) est: 44
	La hauteur à l'ouest est: 25
	La hauteur au nord est: 14
	Pas de sommet à l'est 
	La hauteur au sud est: 02
