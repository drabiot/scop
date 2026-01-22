<div align="center">
  # 🎥 Scop
</div>

<img width="200" height="170" alt="Screenshot from 2026-01-22 17-50-47" src="https://github.com/user-attachments/assets/cb338c1d-c9f2-48b7-9a58-51001d1f1ad0" />

---

Scop is a Graphic & Gaming specialty project of 42 that is a basic GPU rendering with OpenGL.

This mini project is a first step towards using OpenGL.

![Static Badge](https://img.shields.io/badge/os-linux-orange)
![Static Badge](https://img.shields.io/badge/language-c%2B%2B17-blue)


## Demo

![ezgif-714344b923f93d0e](https://github.com/user-attachments/assets/71c86289-7fda-4fcf-b62b-40aff71bc386)

## Run Locally

Clone the project

```bash
  git clone https://github.com/drabiot/scop.git
```

Go to the project directory

```bash
  cd scop
```

Compile the project

```bash
  make -j
````

Open the project

```bash
  ./scop <path-to-model.obj>
  ./scop ressources/42.obj
```


## Documentation

#### Mandatory

The Goal of the project is to build a small program that displays a 3D object created using a modeling tool like Blender.
This 3D object will be stored in a .obj file.

Inside a window, the 3D object must be displayed in perspective (i.e., things that are far away look smaller), and it should rotate around its main axis of symmetry (basically, its center).

Using various colors, you should make the different faces of the object visually distinguishable. The object must be movable along all three axes, in both directions.

Finally, pressing a dedicated key should apply a texture to the object. Pressing that same key again should toggle it back to the colored view. A smooth transition between the two is expected—no hard cuts.


#### Bonus
To complete the project, a camera is integrated. A complex system of lights and shadows, along with a skybox, enhances the project and more.

## Controls

| Utility | Key |
| ----------------- | ------------------------------------------------------------------ |
| Move Model | ⬆-⬅-⬇-➡, PgUp-PgDn |
| Move Camera | W-A-S-D, Space-Shift |
| Speed Camera | Tab |
| Stop the Model Rotation | P |
| Apply Texture | O |
| Change Color | K |

You can use your mouse with Drag-click to change your point of view.

## Change Light Color

| | Key |
| ----------------- | ------------------------------------------------------------------ |
| Red | R + ⬆-⬇ |
| Green | G + ⬆-⬇ |
| Blue | B + ⬆-⬇ |

You can change RGB value of the light. Each value start at 255 and can be lowered to 0.

