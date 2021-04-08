---
layout : post
title : L'application 1ère partie
---

L'application permet de lancer, afficher et intéragir avec le programme.

## Traitement des arguments

La première étape de l'application consiste à obtenir les arguments ; le fichier .obj et éventuellement quelques paramètres facultatifs. Pour cela, aucune bibliothèque n'est nécessaire, mais pour faciliter le traitement de chaque argument la bibliothèque **argp** est utilisée. Cette bibliothèque permet, à partir d'un tableau d'éléments, d'ajouter des arguments à l'application qui sont traités dans une fonction spécifiée, et génère une documentation de type _man_.

## La fenêtre

Après que le fichier contenant la géométrie 3D soit traité, elle doit être affiché dans le terminal, où elle peut être manipulé à l'aide du clavier. Pour cela, après avoir fait quelques recherches, nous allons utiliser la bibliothèque **ncurses**. Cette bibliothèque propose une API pour le développement d'interfaces utilisateur (GUI), en utilisant les caractères et couleurs d'un mode semi-graphique. Non seulement ce type d'interface utilisateur se conçoit de manière indépendante du terminal, mais il accélère le rafraîchissement d'écran, diminuant par là le temps de latence que subissent d'ordinaire les utilisateurs de shells à distance.

Pour l'instant, il n'a été programmé que jusqu'au point de créer une nouvelle fenêtre et de reconnaître les touches pressées, soit la touche «Q» pour quitter la fenêtre.