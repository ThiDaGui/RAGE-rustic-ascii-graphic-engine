---
layout : post
title : Le rasterizer
---

"La rastérisation est un procédé qui consiste à convertir une image vectorielle en une image matricielle destinée à être affichée sur un écran ou imprimée par un matériel d'impression.". Dans notre cas, cela consiste à prendre un triangle qui est définie en 3D et l'afficher sur notre écrans en 2D.
Ce procédé se déroule en 2 étapes:

## Étape 1

La première étape consiste à déterminer les pixels sur lesquels notre triangle va être projeté. Pour cela on va tester pour chaque cases de la matrice si elle appartient au triangle: si oui alors on la marque sinon on passe à la suivante. Pour optimiser ce procéder on commence par obtenir les coordonnées maximum et minimum sur lequel le triangle pourra être projeté puis on parcoure la matrice entre ces coordonnées. Cela permet d'éviter de parcourir l'entièreté de la matrice pour afficher un seul objet et donc de rendre le procédé beaucoup plus rapide. 

## Étape 2

La deuxième étape consiste à calculer la profondeur de notre triangle afin d'éviter d'afficher par exemple un triangle qui se trouverait derrière un autre : on ne doit afficher que le triangle le plus proche de nous et pas celui derrière. Si cette étape n'était pas présente, en affichant un cube en 3D par exemple, les faces du cube qui ne sont pas visibles de notre point de vue seraient visibles et donc l'image en 2D n'aurait rien à voir avec la réalité.