# ASCII-CUBE

A real-time, rotating 3D ASCII cube rendered entirely in the terminal using C++.  
No external libraries — just CPU-based math, projection, and lighting.

Demo video: https://drive.google.com/file/d/16abnGL6zp9gUXn4pNqmZ_W8AkyU_7yyZ/view?usp=sharing

##  Features
- Real-time 3D rendering using only ASCII characters  
- Simulated directional lighting via surface normals  
  (Light source is positioned behind the virtual camera)  
- Continuous cube rotation on all three axes (X, Y, Z)  
- Perspective projection and depth buffer using raw math  
- Inspired by early demoscene / ray tracing experiments

# Controls
This version rotates automatically. (Manual control can be implemented!)

# How it works
Uses basic rotation matrices for 3D transformation

Projects 3D coordinates to 2D screen space

Calculates lighting intensity with surface normals and a directional light vector by using basic trigonometry

Maps brightness to ASCII characters for rendering

# Dependencies
None — uses only the C++ Standard Library.
