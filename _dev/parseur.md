---
layout : post
title : Le parseur
---

L'idée du parseur est d'importer un fichier représentant une géométrie 3D dans une structure définie en C. Le format choisi pour stocker les objets que notre programme va afficher est **«Wavefront .obj»**.

**OBJ** est un format de fichier contenant la description d'une géométrie 3D ; ce format de fichier est _open source_ et a été adopté par d'autres logiciels 3D pour des traitements d'importation / exportation de données.

## Structure du fichier

Une surface polygonale est décrite par un ensemble de sommets (accompagné de coordonnées de texture et de normales en chaque sommet) et d'un ensemble de faces. Chaque élément est défini respectivement comme suit :

* Un sommet : _v 1.0 0.0 0.0_
* Une coordonnée de texture : _vt 1.0 0.0_
* Une normale : _vn 0.0 1.0 0.0_
* Une face : _f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3_, d'où chaque élément fait référence aux coordonnées des points, de texture et des normales définies précédemment. Ces indices des sommets commencent par l'indice 1.
* Autres ...

Un commentaire peut être placé si la ligne commence par le caractère '#'.

## La mise en œuvre

Le parseur implémenté utilise la fonction _fopen_ pour lire le fichier donné et lit ligne par ligne en utilisant la fonction _getline_, identifiant et en traitant le type d'élément grâce aux fonctions de la bibliothèque **string.h** : _strtok_r_, _strcmp_, _strtof_, _strtoul_.

Pour l'instant il est possible d'interpréter un fichier .obj avec les éléments mentionnés et de sauvegarder ces données dans une structure appelée _obj_s_ défini dans **obj.h** de la manière suivante :

![struct obj]({{site.imgpath}}obj.png)

Chaque erreur a été capturée et traitée comme une valeur entière spécifique en fonction du type d'erreur. Il ne devrait pas non plus y avoir de fuites de mémoire (vérifié avec **Valgrind**).

Plusieurs cas de test ont été mis en œuvre, en utilisant la bibliothèque **Unity**, dans le dossier _tests_, assez simple à utiliser.