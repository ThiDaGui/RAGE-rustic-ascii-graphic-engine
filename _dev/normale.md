---
layout : post
title : Utilisation des normales
---

On peut déterminer une normale de chaque face en faisant le produit vectoriel de deux des cotés du triangle. Cependant, celle ci n'est pas nécessairement normé ce qui peut être embêtant, d'autant plus que normaliser un vecteur peut être coûteux: en effet, le calcul de la racine carré et de l'inversion de celle ci sont des opérations complexes. Heureusement, nous pouvons utiliser la méthode \textit{FastInvSqrt} vu plus tôt.

## Backface culling

La première utilisation des normales est pour déterminer quelles faces seront potentiellement vu par la caméra et d'éliminer des faces dont les normales ne pointent pas vers la caméra, ce qu'on appelle le \textit{backface culling}. Cette étape est importante car la projection est plutôt complexe, mettant en jeu des produits de matrices. Il est donc impératif d'éviter de projeter des triangles qui ne seront de toute manière pas visibles. Ce calcul est relativement simple puisse qu'il suffit de faire un produit scalaire entre la normale et un vecteur qui part de la caméra et va jusqu'à l'un des sommet du triangle. en fonction du signe du résultat, soit on continue la projection soit on passe au triangle suivant.

## Éclairage

Nous pouvons aussi utiliser les normales pour éclairer les faces. Une première méthode, mise en place pour cette soutenance, est de calculer le produit scalaire entre la normale de la face et un vecteur qui correspond à une lumière directionelle. Cette méthode est approximative mais permet de faire une différence entre les différentes faces d'un objet.