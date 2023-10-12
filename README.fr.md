[![en](https://img.shields.io/badge/language-en-red.svg)](https://github.com/anbahmani/cub3d/blob/main/README.md)

# 🎮 Cub3D

Ce projet s'inspire de Wolfenstein3D, considéré comme le tout premier jeu FPS. Exploitant la technique du ray-casting, il offre un point de vue dynamique dans un labyrinthe où l'utilisateur doit naviguer pour trouver son chemin. Plongez dans cette expérience immersive inspirée d'un classique du jeu vidéo.

Je partage mon approche personnelle du design graphique en utilisant le langage de programmation C, mêlant rigueur algorithmique et mathématiques.

## 🌟 Points forts du projet

- Réalisation en C : J'ai utilisé le langage C pour profiter de sa puissance et de sa flexibilité, créant ainsi une base solide pour la conception graphique.
- Approche algorithmique : Derrière chaque élément de conception se trouve un algorithme. J'ai intégré des algorithmes simples mais puissants pour générer des rendus graphiques.
- Utilisation pratique des mathématiques : Sans nécessairement plonger profondément dans les complexités mathématiques, j'ai utilisé des concepts fondamentaux pour améliorer l'efficacité et la beauté du projet.

## 🧐 Comment cela fonctionne-t-il ?
Le projet se décompose en deux segments fondamentaux, chacun abordant des aspects essentiels et complexes de la programmation graphique :
- Analyse des Données (Parsing) : Cette première phase consiste en une exploration approfondie et une assimilation des éléments constitutifs de la carte du jeu. Elle implique la collecte minutieuse d'informations critiques telles que les positions des joueurs, la configuration des murs, les orientations, les obstacles et d'autres paramètres pertinents. Le but est de structurer ces données de manière à préparer et à optimiser le processus de rendu visuel qui suivra. Ce stade demande une attention particulière aux détails pour garantir que tous les éléments nécessaires soient localisés, identifiés, et correctement interprétés en préparation de la prochaine étape.
- Raycasting : Représentant le cœur technique et le défi de ce projet, le raycasting est une technique sophistiquée de calcul visuel. Il s'agit de déterminer avec précision la distance entre les divers éléments de la scène et le joueur, en tenant compte de la perspective de ce dernier. En simulant la projection de rayons pour chaque ligne de pixels de l'affichage, cette méthode permet de calculer quelles portions de la scène sont visibles et comment elles doivent être rendues, en fonction de leur distance et de leur angle par rapport au point de vue du joueur. Le résultat est un rendu graphique en trois dimensions qui maintient une cohérence spatiale, offrant une expérience immersive et réaliste à l'utilisateur.

Ces deux composantes, bien que distinctes dans leurs fonctionnalités, doivent travailler de concert pour produire un environnement de jeu crédible. Elles exigent non seulement une compréhension approfondie des concepts algorithmiques et géométriques mais aussi une capacité à les intégrer harmonieusement afin de créer une interface visuelle convaincante et une interaction intuitive pour les joueurs.

## 📷 Aperçu

<img src="https://github.com/anbahmani/cub3d/blob/main/screenshot/Screencast.gif"/>

## 🧑‍💻 Lancer le jeu

```
  git clone git@github.com:anbahmani/cub3d.git
  cd cub3d ; make ; ./cub3d map/map.cub
```

## ⌨️ Commandes

| Touche           | Action        |
| ------------- |:-------------:|
| `ESC`         | quitter     		|
| `A`           | se déplacer vers la gauche    |
| `D`           | se déplacer vers la droite   |
| `W`           | avancer  |
| `S`           | reculer |
| `→`           | tourner à droite   |
| `←`           | tourner à gauche    |