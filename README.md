# Résolution du puzzle tetravex

## Qu'est-ce que le tetravex ?

C'est un jeu de réfléxion dont le but est de résoudre le puzzle. La partie commence sur un plateau vierge de taille 3×3 (taille par défaut), et neuf carrés, ayant chacun un numéro sur chaque bord (donc quatre numéros par carré). Ces numéros varient de 0 à 9 inclus. Le but est de placer ces carrés sur la grille, en faisant en sorte que le numéro d'un bord soit le même que celui du carré adjacent. Chaque face de chaque carré est donc posée à côté d'une face de même nombre.
Le jeu est terminé quand la grille est remplie avec tous les carrés, correctement placés.
Les tailles de jeu comprennent respectivement 4, 9, 16, 25 et 36 carrés.

![Tetravex](https://upload.wikimedia.org/wikipedia/commons/thumb/5/59/Tetravex-couleur.png/1200px-Tetravex-couleur.png)

Source : https://fr.wikipedia.org/wiki/Tetravex

## Dans le projet

Il y a deux parties ce projet :

 * L'implémentation du puzzle tetravex avec plusieurs grilles à résoudre, il est possible d'y jouer via le terminal
 * L'implémentatation d'un algorithme de backtracking permettant de résoudre le puzzle
