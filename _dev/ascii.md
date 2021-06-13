---
layout : post
title : Conversion en ASCII
---

Dans cette partie nous réalisons un programme qui nous permet de convertir une image 2D en ASCII Art, celui-ci nous sera utile plus tard afin d'obtenir le résultat final une fois que le rendu 3D sera opérationnel. 

## Manipulation de l'image

Pour importer et manipuler des images nous avons d'abord pensé à utiliser la bibliothèque **SDL** que nous avions utilisé lors d'un TP de S3, mais finalement nous avons décidé d'utiliser la bibliothèque **stb_image** qui est l'option la plus simple et la plus répandu pour manipuler des images en C. Cette bibliothèque a aussi l'avantage d'importer les images sous formes de tableau d'entiers, ce qui correspond aussi au format que nous utilisons lors du rendu graphique. Ainsi nous limitons le nombre d'ajustements qu'il faudra réaliser lors de l'intégration au reste du projet.

## Redimensionnement de l'image

La bibliothèque **stb_image** contient des fonctions qui nous permettent de redimensionner facilement une image. Pour cela nous utilisons la fonction **stbir_resize_uint8** de la bibliothèque **stb_image_resize**, afin d'obtenir une image ne dépassant pas les limites de la fenêtre de la console. De plus nous prenons soin de ne pas déformer l'image en conservant son ratio, pour cela nous prenons une largeur fixe en fonction de la taille de la fenêtre et nous la multiplions par le ratio pour obtenir les dimensions finales de l'image. Nous avons choisi de fixer la largeur plutôt que la hauteur car c'est souvent la dimension la plus problématique dans notre cas.

## Conversion en nuances de gris

La première étape est de convertir l'image en nuance de gris. Nous partons d'une image en couleur composée de pixels de 3 canaux de couleurs et 1 canal de transparence optionnel en fonction du format de l'image. Pour réaliser la conversion en nuances de gris nous parcourons l'image et pour chaque pixels nous réalisons une moyenne des valeurs des canaux de couleurs, nous ajouterons des poids aux différents canaux afin d'obtenir un résultat plus satisfaisant. Ainsi nous obtenons une nouvelle image en nuances de gris d'un canal ou deux s'il existait un canal de transparence dans l'image de départ.

## Conversion en ASCII

Ensuite, pour convertir l'image en ASCII Art nous découpons l'image en groupes de pixels rectangulaires, la taille du rectangle sera donnée par l'utilisateur dans l'application mais nous utiliserons des groupes de 5 x 10 pixels pour notre démonstration. Pour chaque rectangles nous réalisons une moyenne des valeurs qui sera comprise entre 0 et 255, nous divisons cette valeur par 255 afin d'obtenir une valeur comprise entre 0 et 1 et nous y associons le caractère correspondant de la manière suivante :

0.0 <= x <= 0.1 == '@' \
0.1 < x <= 0.2 == '%' \
0.2 < x <= 0.3 == '#' \
0.3 < x <= 0.4 == '*' \
0.4 < x <= 0.5 == '+' \
0.5 < x <= 0.6 == '=' \
0.6 < x <= 0.7 == '-' \
0.7 < x <= 0.8 == ':' \
0.8 < x <= 0.9 == '.' \
0.9 < x <= 1.0 == ' '

## Gestion des bords

Lorsque le rectangle chevauche les bords de l'image, nous faisons la moyenne sur un rectangle plus petit et nous leurs associons un caractère de la même manière. Toutefois le caractère associé est toujours de même taille, l'image finale peut donc être légèrement plus grande que l'image de départ.
