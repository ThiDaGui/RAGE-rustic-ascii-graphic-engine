---
layout : post
title : Le site web
---

Le site web et un site statique réalisé avec **Jekyll** et déployé en continu sur **GitLab Pages**. On y trouve toutes les informations concernant le projet : présentation, détails de développement, ressources utilisées, download des rapports et du projet.

## Choix des technologies

La première étape a été de choisir les technologies à utiliser, cette étape a pris largement plus de temps que ce que j’avais prévu. Dès le départ je savais que je voulais utiliser **GitLab Pages** pour le déploiement et l'hébergement ce qui nous permet de réunir tous les aspects du projet dans un unique endroit.

Ensuite je me suis intéressé aux très (trop ?) nombreuses solutions pour la création d'un site statique. Pour cette étape je ne voulais pas utiliser un simple template en HTML, CSS et Bootstrap comme lors du projet de S2. Cependant je suis beaucoup plus familier avec les technologies utilisées pour créer des sites dynamiques, je me suis donc pas mal perdu en explorant toutes les solutions disponibles.

Au final j’ai décidé d’utiliser le très populaire **Jekyll** surtout pour sa faciliter d’utilisation tout en me fournissant toutes les fonctionnalités qui me sont nécessaires. 
Et enfin puisque le but était de créer un site plutôt minimal, j’ai choisi le thème minimal pour GitHub Pages, cependant ce choix posera quelques problèmes plus tard quand j’essaierai de le déployer en utilisant GitLab Pages.\
J'ai du faire ce choix car GitHub Pages est une solution beaucoup plus populaire pour ce type de projet ce qui fait que le choix de thèmes pour GitLab Pages est très limité et aucun ne me convenait pour atteindre le rendu que je désirais.

## Création du site

Le thème que j'ai choisi étant optimisé pour GitHub, j’ai téléchargé le repo GitHub du thème minimal pour y apporter toutes les modifications nécessaires au déploiement sur GitLab Pages tout en me familiarisant avec Jekyll. Le framework était à première vue assez différent de ce que j’ai pu utiliser jusque là, cependant passé cette première étape d’adaptation je me suis rendu compte de sa facilité d’utilisation et j’ai pu retrouver des concepts familier comme les "includes" qui servent de composants ou encore l’interpolation de variables. 

## Mise en production

Pour cette partie j’ai utilisé l'outil de **CI/CD** de GitLab pour déployer le site sur GitLab Pages. Pour cette étape j’ai aussi rencontré quelques problèmes. Tout d’abord je n’avais pas la possibilité d’utiliser les _shared runners_ de GitLab pour le déploiement car le GitLab du cri n’en possède pas. J’ai donc configuré un **Docker** sur ma machine et l’ai enregistré en tant que _runner_ GitLab pour le projet afin de pouvoir générer et déployer le site en continue. Ensuite j’ai modifié le fichier YAML du projet afin de pouvoir déployer le site en production directement depuis la branche web de notre projet et non depuis la branche master. 

Enfin, quelques problèmes de dépendances plus tard, la pipeline était configuré et prête à l'emploi. Bien que ces problèmes n’était au final pas bien difficiles à résoudre, le débogage était plutôt long puisqu'après chaque modifications je devais attendre plusieurs minutes avant de voir si le _runner_ parvenait à générer le site ou non.

## Résultat
Au final le résultat est très concluant, nous avons un site sobre et opérationnel et surtout extrêmement simple à maintenir. En effet maintenant que toute la structure est faite et que la pipeline est configurée, ajouter du contenu au site se fait simplement en modifiant un fichier **Markdown**, ce qui est faisable directement depuis le site GitLab. Et après chaque nouveaux commits la nouvelle version du site est automatiquement mis en production. 

