BUILD_DIR = build
SERVER_BUILD_DIR = $(BUILD_DIR)/server
CLIENT_BUILD_DIR = $(BUILD_DIR)/client
ECS_BUILD_DIR = $(BUILD_DIR)/ecs

CMAKE_CMD = cmake
MAKE_CMD = make

all: ecs srv 

ecs:
	@echo "Building ECS..."
	@if [ ! -d "$(ECS_BUILD_DIR)" ]; then mkdir -p $(ECS_BUILD_DIR); fi
	cd $(ECS_BUILD_DIR) && $(CMAKE_CMD) -DCMAKE_BUILD_TYPE=Release ../../ECS && $(MAKE_CMD)

srv:
	@echo "Building Server..."
	@if [ ! -d "$(SERVER_BUILD_DIR)" ]; then mkdir -p $(SERVER_BUILD_DIR); fi
	cd $(SERVER_BUILD_DIR) && $(CMAKE_CMD) -DCMAKE_BUILD_TYPE=Release ../../server && $(MAKE_CMD)

# client:
# 	@echo "Building Client..."
# 	@if [ ! -d "$(CLIENT_BUILD_DIR)" ]; then mkdir -p $(CLIENT_BUILD_DIR); fi
# 	cd $(CLIENT_BUILD_DIR) && $(CMAKE_CMD) -DCMAKE_BUILD_TYPE=Release ../../client && $(MAKE_CMD)

clean:
	@echo "Cleaning up build files..."
	rm -rf $(BUILD_DIR)
	rm -rf CMakeUserPresets.json