---
layout : post
title : La caméra
---

Le principal objectif pour la troisième soutenance est d'implémenter un système de caméra mobile. Il faut donc dissocier le repère de la caméra et celui du monde.

## Système de coordonnées

L'application étant un visualisateur d'objets en trois dimensions, avoir une caméra qui reste en orbite autour de l'objet est idéal.
Nous avons donc choisi d'utiliser un système de coordonnés sphérique pour contrôler la caméra. Nous avons donc 3 coordonnées 
(ρ, θ, φ). ρ correspond à la distance entre la caméra et l'origine du monde, θ à la longitude de la caméra
et φ sa latitude. Par la suite il suffira de faire varier ces 3 coordonnées pour faire orbiter la caméra autour de l'objet.