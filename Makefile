.PHONY: all clean ecs client server prepare

BUILD_DIR = build
OS := $(shell uname -s)

ifeq ($(OS), Windows_NT)
	RM = del /Q
	MKDIR = mkdir
	CPM_FETCH = powershell -Command "(New-Object System.Net.WebClient).DownloadFile('https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake', 'cmake/CPM.cmake')"
else
	RM = rm -rf
	MKDIR = mkdir -p
	CPM_FETCH = wget -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake
endif

CMAKE_GENERATED_FILES = \
	CMakeCache.txt \
	CPackConfig.cmake \
	CPackSourceConfig.cmake \
	cmake_install.cmake \
	cpm-package-lock.cmake

CMAKE_GENERATED_DIRS = \
	CMakeFiles \
	CPM_modules \
	_deps

all: build

build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_DIR)

ecs:
	cmake --build $(BUILD_DIR) --target ecs

client:
	cmake --build $(BUILD_DIR) --target client

server:
	cmake --build $(BUILD_DIR) --target server

client_2:
	cmake --build $(BUILD_DIR) --target client_2
clean:
	$(RM) $(BUILD_DIR) $(CMAKE_GENERATED_FILES) $(CMAKE_GENERATED_DIRS)