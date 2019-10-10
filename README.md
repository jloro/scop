# Scop

Scop is a 42 project. You have to parse and display a *.obj* file using openGL in C.

![Alt text](/ressource/screenshots/note.jpeg?raw=true "note")


### Installing

Just git clone with submodule and run `cmake -B build`.

```
git clone --recurse-submodule https://github.com/jloro/scop.git
```

And run `./scop`.


## Commands

=== COMMANDS ===

Arrows : move object on X/Y axis

Page up/down : move object on Z axis

P : Polygon mode

F : Activate/Deactivate flat/smooth mode

G : Activate/Deactivate grey mode

T : Activate/Deactivate texture mode

X Y Z : Change rotation axis

M : Pause rotation

\- \+ : Change rotation speed

keypad - + : Change move speed

H : Recompile shader

R : Reset

### Examples

`42.obj`

![Alt text](/ressource/screenshots/1.jpeg?raw=true "42")

`sphere.obj`

![Alt text](/ressource/screenshots/2.jpeg?raw=true "Sphere")

`deer.obj`

![Alt text](/ressource/screenshots/3.jpeg?raw=true "Deer")

## Built With

* [Libmat](https://github.com/jloro/libmat) - My libmat for matrix and vectors in C.
* [GLFW](https://github.com/glfw/glfw) - A library for handling window and input events.
* [OpenGL](https://www.opengl.org/) - OpenGL

## Authors

* **Jules Loro** - [jloro](https://github.com/jloro)
