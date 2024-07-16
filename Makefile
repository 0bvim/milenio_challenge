# Compiler and flags
CC = c++
CFLAGS = -Wall -Werror -Wextra -pedantic -g3 -O3

# Source and object files
SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(SRC_FILES:.cpp=.o)
TARGET := libcsv.so
EXECUTABLE := $(SRC_DIR)/main
BUILD_DIR := ./build/

# Default target
.DEFAULT_GOAL := all

# All: Build and run the Docker container
all: build_docker run

# Build the Docker image
build_docker:
	docker build -t alpine-app:latest .

# Run the Docker container
run:
	docker run --rm --name alpine-container alpine-app:latest

# Run and stay inside of container to make tests or have some fun =D
inside:
	docker run -it --rm --name alpine-container alpine-app:latest sh

# Stop and remove all running Docker containers
break:
	docker stop $$(docker ps -qa)
	docker rm $$(docker ps -qa)

# Remove all Docker images
erase:
	docker rmi -f $$(docker images -qa)

# Build shared library
so: $(OBJ_FILES)
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(OBJ_FILES)

# Compile source files to object files with Position Independent Code (PIC)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(EXECUTABLE)

# Rule to check the OS and open the documentation
check_os:
ifeq ($(OS),Windows_NT)
	@echo "Detected OS: Windows"
	@echo "Opening documentation..."
	start docs/html/index.html
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		@echo "Detected OS: Linux"
		@echo "Opening documentation..."
		xdg-open docs/html/index.html
	else ifeq ($(UNAME_S),Darwin)
		@echo "Detected OS: macOS"
		@echo "Opening documentation..."
		open docs/html/index.html
	else
		@echo "Unsupported OS"
		exit 1
	endif
endif

# To visualize documentation
docs: check_os

test:
	@mkdir -p ${BUILD_DIR}
	@cd $(BUILD_DIR) && cmake .. && make && make test

# Build the executable
bin: $(EXECUTABLE)

# Clean up build artifacts
fclean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(TARGET) $(SRC_DIR)/*.o $(EXECUTABLE)

# Phony targets
.PHONY: all build_docker run break erase so bin fclean test
