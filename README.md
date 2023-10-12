[![fr](https://img.shields.io/badge/language-fr-blue.svg)](https://github.com/anbahmani/cub3d/blob/main/README.fr.md)

# 🎮 Cub3D

This project draws inspiration from Wolfenstein3D, hailed as the first-ever FPS game. Harnessing the technique of ray-casting, it provides a dynamic viewpoint within a maze where the user must navigate to find their way. Dive into this immersive experience inspired by a gaming classic.

I share my personal approach to graphic design using the C programming language, blending algorithmic rigor and mathematics.

## 🌟 Project highlights

- Development in C: I used C to take advantage of its power and flexibility, creating a solid foundation for graphic design.

- Algorithmic approach: Behind every design element is an algorithm. I integrated simple but powerful algorithms to generate graphic renderings.

- Practical Use of Mathematics: Without necessarily diving deep into mathematical complexities, I used fundamental concepts to enhance the efficiency and beauty of the project.

## 🧐 How does it work?
The project is divided into two main parts:
- Parsing, which gathers information from the map (player and wall positions, orientations, obstacles, etc.) in order to prepare its display.
- Raycasting, the technical challenge of this project, which consists in calculating the distance of elements from the player and his point of view in order to display them coherently.

## 📷 Preview

<img src="https://github.com/anbahmani/cub3d/blob/main/screenshot/Screencast.gif"/>

## 🧑‍💻 Run game

```
  git clone git@github.com:anbahmani/cub3d.git
  cd cub3d ; make ; ./cub3d map/map.cub
```

## ⌨️ Commands

| Key           | Action        |
| ------------- |:-------------:|
| `ESC`         | quit     		|
| `A`           | move left     |
| `D`           | move right    |
| `W`           | move forward  |
| `S`           | move backward |
| `→`           | turn right    |
| `←`           | turn left     |