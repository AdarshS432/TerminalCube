# TerminalCube

TerminalCube (TCube) is an NxNxN Rubik's Cube Simulator that can be used in the terminal with a C++ library for easy use in projects.



To compile:

* Clone the Repository (`git clone https://github.com/Wallball-App/TerminalCube.git`)
* Navigate to the cloned directory
* Configure CMake with `cmake --preset [YOUR_PRESET]`
    * The possible presets are:
        - Windows with Mingw: `windows-mingw`
        - Windows with MSVC (Visual Studio 17 2022): `windows-msvc`
        - MacOS with clang: `macos-clang`
        - Linux with GCC: `linux-gcc`
    * NOTE: A C++ Compiler is Required to Build This Project
* Build the project: `cmake --build build/[YOUR_PRESET]`
* Navigate to `build/[YOUR_PRESET]` to view the generated files

How to Use (App):

- Open tcube.exe
- Enter the cube size (i.e. 3 for the standard Rubik's cube)
- Enter algorithms to execute the moves (e.g. R U R' U')
- Use standard Singmaster Notation (R for Right layer etc.)
- For Larger cubes, use this format: [Layer][Face][Wide][Number][Prime]
Layer is a number less than or equal to half the cube size
Face is the face turned (R, U, F, etc.)
Wide moves should be written with a lowercase "w"
Number is the amount of turns
Prime is shown by the symbol " ' ". If a move is prime, it is rotated counterclockwise instead of clockwise.
Example: 3Rw2'

How to Use (Library):
- Build the project (for instructions see above).
- To compile your program using the library, run the command:
    `g++ [YOUR_PROJECT_SOURCE_FILES] -o [YOUR_OUTPUT_EXECUTABLE_NAME] -lTCube -L path/to/build/[YOUR_PRESET] -I path/to/include/`
- NOTE: If using MSVC on Windows, use this command:
    `cl.exe [YOUR_PROJECT_SOURCE_FILES] /Fe:[YOUR_OUTPUT_EXECUTABLE_NAME] /I path/to/include/ /link /LIBPATH:path/to/build/[YOUR_PRESET] TCube.lib`

If using CMake:
```cmake
add_subdirectory([PATH_TO_CLONED_TCUBE_DIRECTORY])

add_executable(MyProject main.cpp)

target_link_libraries(MyProject PRIVATE TCube)
```
NOTE: Make sure to replace `MyProject` with your project name, `main.cpp` with your source files. The `PRIVATE` keyword can be changed to `PUBLIC` or `INTERFACE` depending on your project's dependencies.

# The Mathematics

TCube uses vectors to represent the pieces on any Rubik's cube.

### The Coordinate System:
Right: +x
Up: +y
Forward: +z

The middle layer (or the layer between the two middle layers on even numbered cubes) will be considered the 'zero-layer'.

NOTE: In a physical even-numbered Rubik's Cube, the 'zero-layer' actually exists under the edges in the center, but it is effectively ignored in this simulation, as it does not change the process in calculating the positions of pieces. 

### Rotation and Piece Movement

Since each piece is represented by a vector, rotating a set of pieces becomes easy due to rotation matrices. When any move is executed, the affected pieces are chosen, and their position vectors will then be multiplied by the rotation matrix.

Example:
Vector: 
$\langle
1, 1, 1
\rangle$
"Right, Top, Front" corner
Move: R (Clockwise rotation around +x axis)

Rotation Matrix: 
$\begin{bmatrix}
1 & 0 & 0 \\
0 & \cos(\theta) & -\sin(\theta) \\
0 & \sin(\theta) & \cos(\theta)
\end{bmatrix}$

### Multiplication:

$\theta = -90^\circ$ (Because Counterclockwise is usually $+\theta$)

$$\begin{aligned}
& \begin{bmatrix}
1 & 0 & 0 \\
0 & \cos(-90^\circ) & -\sin(-90^\circ) \\
0 & \sin(-90^\circ) & \cos(-90^\circ)
\end{bmatrix}

\begin{bmatrix}
1 \\ 1 \\ 1
\end{bmatrix}

=
\begin{bmatrix}
1 \\ 1 \\ -1
\end{bmatrix}
& \hspace{50em}
\end{aligned}$$

The final vector: 
$\langle
1, 1, 1
\rangle$
represents the "Right, Top, Back" corner, which would be the location of the piece if that move was performed.
