.PHONY: all clean ecs game server prepare

BUILD_DIR = build

all: prepare build

prepare:
	mkdir -p cmake
	@test -f cmake/CPM.cmake || wget -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake

build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_DIR)

ecs:
	cmake --build $(BUILD_DIR) --target ecs

client:
	cmake --build $(BUILD_DIR) --target client

server:
	cmake --build $(BUILD_DIR) --target server

clean:
	rm -rf $(BUILD_DIR)
