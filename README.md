
# Catch-Up Simulation

This repository presents a "catch-up" simulation project aimed at deepening my understanding and proficiency in the C programming language. The simulation allows users to add new runners by clicking the left mouse button. The catcher will then attempt to catch the runners. Once the catcher catches a runner, they switch roles.

## Project Objectives

- **C Programming Practice**: Improve skills in C programming through a practical project.
- **Mathematical Concepts**: Show how to use Euler's method for numerical integration.
- **Physical Concepts**: Demonstrate how to detect and handle collisions.
- **Polymorphism**: Use function pointers to achieve polymorphism in C.
- **Generics**: Implement generics using void pointers.
- **Minimal Dependencies**: Use raylib only for graphics and sound, without other physics libraries.

## Demonstration

## Installation and Usage

### Prerequisites

- [raylib](https://www.raylib.com/) library
- [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/) tool

### Steps

1. Install raylib and pkg-config using Homebrew:
   ```sh
   brew install raylib
   brew install pkg-config
   ```

2. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/catch-up-simulation.git
   ```

3. Navigate to the project directory:
   ```sh
   cd catch-up-simulation
   ```

4. Build and run the project using `make`:
   ```sh
   make run
   ```

   The `Makefile` uses `pkg-config` for managing compiler and linker flags for raylib.

## Contribution

Contributions are welcome! Please fork this repository and submit pull requests.
