# ASCII-CUBE

A real-time, rotating ASCII cube rendered in your terminal using CPU-based lighting and projection in C++. Inspired by retro demos and raytracing concepts, this project simulates 3D perspective, rotation, and directional lighting in pure ASCII characters — all without external libraries. 

 #Features
 Real-time 3D ASCII cube rendering

Dynamic lighting based on cube surface normals and light source direction

Continuous rotation in 3 axes (X, Y, Z)

# Controls
This version rotates automatically. (Manual control can be implemented!)

# How it works
Uses basic rotation matrices for 3D transformation

Projects 3D coordinates to 2D screen space

Calculates lighting intensity with surface normals and a directional light vector

Maps brightness to ASCII characters for rendering

# Dependencies
None — uses only the C++ Standard Library.
