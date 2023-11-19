# Game
You lost it.

# Build
## Requirements:
- `Powershell`       | need to enable scripts with `Set-ExecutionPolicy RemoteSigned`.
- `CMake`               | need to be in the path, version 3.12 at least.
- `Visual Studio`  | with MSbuild 2022.

## How to:
Use the command `./generate.ps1` and hope for the best.

## Generation:
- Visual Studio solution in `./_build/Game.sln`.
- Binary executables in `./_build/Output/{mode}/Game.exe`.

# Dependencies:
- `GLM`  (OpenGL Mathematics)                                        | Clone: https://github.com/g-truc/glm
- `Glad` (Get entry points for `opengl32.dll`'s methods) | Generated at: https://glad.dav1d.de
- `Glfw` (Windows and inputs helper)                              | Official website: https://www.glfw.org
- `FreeType` (Font renderer)                                             | Clone: https://gitlab.freedesktop.org/freetype
- `ReactPhysics3D` (Physic Engine)                                     | Clone: https://github.com/DanielChappuis/reactphysics3d