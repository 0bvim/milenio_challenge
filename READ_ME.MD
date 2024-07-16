**README: Using the Makefile**

This project uses a Makefile to automate building a shared library (`libcsv.so`) and tests. The Makefile streamlines the compilation, linking, and cleaning processes, making development more efficient.

**Prerequisites:**

- **C++ compiler:** Ensure you have a C++ compiler installed, such as `g++` on Linux/macOS or the Microsoft Visual C++ Build Tools on Windows.
- **Docker (optional):** If you want to build and run a Docker image, install Docker Desktop from [https://www.docker.com/products/docker-desktop/](https://www.docker.com/products/docker-desktop/).

## **General Rules**
- Consider open a terminal or command prompt in your project directory before run `make rules`.

---

**Build container and run application**

1. Run the following command:

	```bash
	make
	```

**Build container and run application inside of container**

1. Build image:

	```bash
	make build_docker
	```

2. Enter in docker with a separated tty

	```bash
	make inside
	```

**Building the Shared Library (libcsv.so):**

1. Run the following command:

   ```bash
   make so
   ```

   This will compile all the source files (`*.cpp`) in the `src` directory into object files (`*.o`) and then link them into the shared library `libcsv.so`.

**Running tests:**

- Test is a standalone program, you can directly execute it from the terminal:

   ```bash
   make test
   ```

- If `main` depends on `libcsv.so`, you might need to set the library path during execution (consult your system's documentation for details).

**Cleaning Up Build Artifacts:**

1. To remove all object files, the shared library, and the executable, run:

   ```bash
   make fclean
   ```

   This will clean up the build directory and generated files.

**Additional Notes:**

- The Makefile assumes your source files are located in the `src` directory.
- The `CFLAGS` variable defines compiler flags for warnings, debugging, and code optimization.
- The `check_os` target detects your operating system and attempts to open the project documentation using the appropriate command (e.g., `start` on Windows, `xdg-open` on Linux, or `open` on macOS).

>This README provides a comprehensive guide to using the Makefile for building, running, and cleaning this project. If you have any further questions, feel free to consult the Makefile itself or search for more details or schedule a interview with me for more details xD.
