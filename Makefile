BUILD_DIR = build
CONAN_DIR = $(BUILD_DIR)/conan
SERVER_BUILD_DIR = $(BUILD_DIR)/server
CLIENT_BUILD_DIR = $(BUILD_DIR)/client
ECS_BUILD_DIR = $(BUILD_DIR)/ecs

CMAKE_CMD = cmake
MAKE_CMD = make

all: conan ecs server client

conan:
	@echo "Installing dependencies with Conan..."
	@conan install . --build=missing -g CMakeDeps -g CMakeToolchain -of=$(CONAN_DIR)

ecs: conan
	@echo "Building ECS..."
	@if [ ! -f "$(CONAN_DIR)/conan_toolchain.cmake" ]; then echo "Toolchain file not found! Exiting."; exit 1; fi
	@if [ ! -d "$(ECS_BUILD_DIR)" ]; then mkdir -p $(ECS_BUILD_DIR); fi
	cd $(ECS_BUILD_DIR) && $(CMAKE_CMD) -DCMAKE_TOOLCHAIN_FILE=$(abspath $(CONAN_DIR)/conan_toolchain.cmake) -DCMAKE_BUILD_TYPE=Release ../../ECS && $(MAKE_CMD)

server: conan
	@echo "Building Server..."
	@if [ ! -f "$(CONAN_DIR)/conan_toolchain.cmake" ]; then echo "Toolchain file not found! Exiting."; exit 1; fi
	@if [ ! -d "$(SERVER_BUILD_DIR)" ]; then mkdir -p $(SERVER_BUILD_DIR); fi
	cd $(SERVER_BUILD_DIR) && $(CMAKE_CMD) -DCMAKE_TOOLCHAIN_FILE=$(abspath $(CONAN_DIR)/conan_toolchain.cmake) -DCMAKE_BUILD_TYPE=Release ../../server && $(MAKE_CMD)

# client: conan
# 	@echo "Building Client..."
# 	@if [ ! -f "$(CONAN_DIR)/conan_toolchain.cmake" ]; then echo "Toolchain file not found! Exiting."; exit 1; fi
# 	@if [ ! -d "$(CLIENT_BUILD_DIR)" ]; then mkdir -p $(CLIENT_BUILD_DIR); fi
# 	cd $(CLIENT_BUILD_DIR) && $(CMAKE_CMD) -DCMAKE_TOOLCHAIN_FILE=$(abspath $(CONAN_DIR)/conan_toolchain.cmake) -DCMAKE_BUILD_TYPE=Release ../../client && $(MAKE_CMD)

clean:
	@echo "Cleaning up build files..."
	rm -rf $(BUILD_DIR)
	rm -rf CMakeUserPresets.json