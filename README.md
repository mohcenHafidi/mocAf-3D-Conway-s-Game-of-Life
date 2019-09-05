# 3D Conway's Game of Life
This is a real-time Conway's game of life renderer built with OpenGL. A main focus of this project is to build an interactive cellular automata system and use it to bring the Conway's game of life to life (i.e. make The Conway's game of life visual and interactive). Another large focus of this project is to be the most optimal possible in terms of rendering and calculus.

![1 2](https://user-images.githubusercontent.com/53482702/64303926-a60fca80-cf8a-11e9-876f-5bc6be847bde.png)

# Render Samples
## Still lifes and Oscillators patterns
![1 1](https://user-images.githubusercontent.com/53482702/64303925-a60fca80-cf8a-11e9-92c5-b349b31bcdf5.png)

## The R-pentomino pattern
### The R-pentomino at generation 379
![The R-pentomino at generation 379](https://user-images.githubusercontent.com/53482702/64303928-a6a86100-cf8a-11e9-9b6d-c627ba24921f.png)
### The R-pentomino stabilized at generation 1103
![The stabelized R-pentomino at generation 1103](https://user-images.githubusercontent.com/53482702/64303930-a6a86100-cf8a-11e9-9547-7fc1bfb33252.png)


# Features
## Rendering
- Instanced Rendering or Instancing
- The use of VAOs, VBOs and EBOs
- Face culling
- Z-Buffer
- GLSL 330+
- Camera Movements (Mouse & Keyboard)

## Engine
- OpenGL 3.3+
- GLFW for inputs and for the display window
- ASSIMP for Model Loading
- STB.stb_image.h for Image Loading

# Conway's Game of Life Sources
- https://www.ibiblio.org/lifepatterns/october1970.html
- https://cs.stanford.edu/people/eroberts/courses/soco/projects/2001-02/cellular-automata/walks%20of%20life/walksoflife.html

# Contributing
1. Fork it (https://github.com/mohcenHafidi/mocAf-3D-Conway-s-Game-of-Life.git)
1. Create your feature branch (`git checkout -b new-feature-branch`)
1. Commit your changes (`git commit -m "A description for your feature would be nice"`)
1. Push to the branch (`git push origin new-feature-branch`)
1. Create a new Pull Request

