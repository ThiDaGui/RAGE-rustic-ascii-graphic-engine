---
layout : post
title : L'application partie finale
---

On termine l'application en utilisant tout ce qui a été fait précédemment.

## Les améliorations
Finalement nous utilisons tout ce qui a été fait précédemment afin de réaliser notre application finale. 

Le but étant de créer une application qui nous permet de visualiser un modèle en 3D avec la possibilité de déplacer la caméra autour de l'objet, il nous suffit d'utiliser le renderer à chaque image afin d'obtenir un rendu avec les nouveaux paramètres de la caméra, puis de convertir l'image en ASCII à l'aide de la fonction réalisés dans la partie "Conversion en ASCII". Cependant certains ajustements ont été fait afin d'avoir le meilleur résultat possible.

Tout d'abord pour avoir un rendu plus propre nous utilisons la librairie **ncurses** qui nous permet de créer une fenêtre intégrée dans la console à la façon de vim, de plus elle nous donne accès à plusieurs fonctions qui nous seront utiles pour dessiner et rafraîchir l'image de façon plus efficace.

Ensuite, la taille de l'image rendue est proportionnelle à la taille de la fenêtre et des caractères afin d'obtenir un résultat satisfaisant peu importe les paramètres de la console utilisée.

De plus, le nombre de caractères ASCII a été augmenté de 10 caractères à 70 afin d'avoir plus de nuances de luminosité sur l'image finale. 

## Fonctionnement et Résultat final

L'application prend jusqu'à 2 arguments, le chemin du fichier .obj que l'on souhaite visualiser et la valeur du fov qui est optionnelle (champ de vision horizontal).

Au départ l'objet est centré à l'origine du repère et la caméra est située à une distance 25 de l'origine avec une source de lumière fixe. La caméra est dans un repère en coordonnées sphériques et toujours pointée vers l'objet. 

**Ncurses** nous permet de simplement récupérer les inputs de l'utilisateur avec la fonction _wgetch()_ qui attend que l'utilisateur appuie sur une touche, l'utilisateur peut donc utiliser les touches 'a' et 'd' pour orbiter la caméra autour de l'objet par la gauche et par la droite respectivement, cette action a pour effet d'incrémenter ou de décrémenter l'angle θ de notre système de coordonnées. Il peut aussi utiliser les touches 'w' et 's' pour modifier l'angle φ et donc orbiter autour de l'objet par le haut et le bas respectivement. Et enfin, les touches 'r' et 'f' permettent de faire avancer et reculer la caméra, elles modifient donc ρ la dernière coordonnée de notre repère sphérique. 

Dès qu'une des coordonnées de la caméra est modifiée, l'image précédente est effacée, le rendu de la nouvelle image est calculé en fonction des nouvelles coordonnées puis converti en ASCII et affichée. Ainsi le rafraîchissement de l'image se fait uniquement lorsque cela est nécessaire. 

À tout moment l'utilisateur peut appuyer sur la touche 'q' pour quitter l'application et la touche '1' pour réinitialiser la position de la caméra.

Les différentes commandes sont visibles en bas à gauche de la fenêtre.
