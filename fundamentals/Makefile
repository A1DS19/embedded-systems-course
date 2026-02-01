# Project variables
PROJECT_NAME := $(shell basename $(CURDIR))
BUILD_DIR := build
BIN_DIR := bin
SRC_DIR := src
INCLUDE_DIR := include
TESTS_DIR := tests

# Detect platform
ifeq ($(OS),Windows_NT)
    PLATFORM := Windows
    EXECUTABLE_EXT := .exe
    CMAKE_GENERATOR := "Visual Studio 17 2022"
    RM := del /Q
    MKDIR := mkdir
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        PLATFORM := Linux
        EXECUTABLE_EXT :=
        CMAKE_GENERATOR := "Unix Makefiles"
    endif
    ifeq ($(UNAME_S),Darwin)
        PLATFORM := macOS
        EXECUTABLE_EXT :=
        CMAKE_GENERATOR := "Unix Makefiles"
    endif
    RM := rm -rf
    MKDIR := mkdir -p
endif

# Build configurations
BUILD_TYPE ?= Debug
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Default target
.PHONY: all
all: build

# Help target
.PHONY: help
help:
	@echo "Available targets for $(PLATFORM):"
	@echo "  build       - Build the project (default)"
	@echo "  clean       - Clean build artifacts"
	@echo "  rebuild     - Clean and build"
	@echo "  run         - Build and run the main executable"
	@echo "  debug       - Build with debug info and run with debugger"
	@echo "  release     - Build optimized release version"
	@echo "  test        - Build and run tests"
	@echo "  format      - Format code with clang-format"
	@echo "  setup-lsp   - Setup clangd configuration"
	@echo "  check       - Check build environment"
	@echo "  help        - Show this help message"

# Build target
.PHONY: build
build: $(BUILD_DIR)/Makefile
	@echo "🔨 Building $(PROJECT_NAME) for $(PLATFORM)..."
	@cmake --build $(BUILD_DIR) --config $(BUILD_TYPE)
	@echo "✅ Build complete!"

# Configure CMake
$(BUILD_DIR)/Makefile:
	@echo "🔧 Configuring CMake for $(PLATFORM)..."
	@$(MKDIR) $(BUILD_DIR)
	@cmake -B $(BUILD_DIR) -S . -G $(CMAKE_GENERATOR) $(CMAKE_FLAGS)

# Clean target
.PHONY: clean
clean:
	@echo "🧹 Cleaning build artifacts..."
ifeq ($(PLATFORM),Windows)
	@if exist $(BUILD_DIR) $(RM) $(BUILD_DIR)\*
	@if exist $(BIN_DIR) $(RM) $(BIN_DIR)\*
	@if exist lib $(RM) lib\*
else
	@$(RM) $(BUILD_DIR)/* $(BIN_DIR)/* lib/* 2>/dev/null || true
	@touch $(BUILD_DIR)/.gitkeep $(BIN_DIR)/.gitkeep lib/.gitkeep
endif
	@echo "✅ Clean complete!"

# Rebuild target
.PHONY: rebuild
rebuild: clean build

# Run target
.PHONY: run
run: build
	@echo "🚀 Running $(PROJECT_NAME)..."
ifeq ($(PLATFORM),Windows)
	@$(BIN_DIR)\main$(EXECUTABLE_EXT)
else
	@./$(BIN_DIR)/main$(EXECUTABLE_EXT)
endif

# Debug target
.PHONY: debug
debug: BUILD_TYPE = Debug
debug: build
	@echo "🐛 Running $(PROJECT_NAME) with debugger..."
ifeq ($(PLATFORM),Windows)
	@echo "Start debugging in Visual Studio or use windbg"
	@$(BIN_DIR)\main$(EXECUTABLE_EXT)
else ifeq ($(PLATFORM),macOS)
	@lldb ./$(BIN_DIR)/main$(EXECUTABLE_EXT)
else
	@gdb -q ./$(BIN_DIR)/main$(EXECUTABLE_EXT)
endif

# Release build
.PHONY: release
release: BUILD_TYPE = Release
release: clean build

# Test target
.PHONY: test
test: build
	@echo "🧪 Building and running tests..."
	@cmake --build $(BUILD_DIR) --target test_main --config $(BUILD_TYPE) 2>/dev/null || echo "⚠️  No tests configured"
ifeq ($(PLATFORM),Windows)
	@if exist $(BIN_DIR)\test_main$(EXECUTABLE_EXT) $(BIN_DIR)\test_main$(EXECUTABLE_EXT)
else
	@if [ -f $(BIN_DIR)/test_main$(EXECUTABLE_EXT) ]; then ./$(BIN_DIR)/test_main$(EXECUTABLE_EXT); fi
endif

# Format target
.PHONY: format
format:
	@echo "🎨 Formatting code..."
	@bash scripts/format.sh 2>/dev/null || echo "⚠️  Format script failed. Check clang-format installation."

# Setup LSP target
.PHONY: setup-lsp
setup-lsp:
	@echo "🔧 Setting up LSP configuration..."
	@bash scripts/setup_clangd.sh

# Check build environment
.PHONY: check
check:
	@echo "🔍 Checking build environment for $(PLATFORM)..."
	@command -v cmake >/dev/null 2>&1 && echo "✅ CMake found" || echo "❌ CMake not found"
	@command -v make >/dev/null 2>&1 && echo "✅ Make found" || echo "❌ Make not found"
ifeq ($(PLATFORM),Windows)
	@where cl >nul 2>&1 && echo "✅ MSVC found" || echo "⚠️  MSVC not found"
	@where g++ >nul 2>&1 && echo "✅ g++ found" || echo "⚠️  g++ not found"
else
	@command -v g++ >/dev/null 2>&1 && echo "✅ g++ found" || echo "❌ g++ not found"
	@command -v clang++ >/dev/null 2>&1 && echo "✅ clang++ found" || echo "⚠️  clang++ not found"
endif
	@command -v clang-format >/dev/null 2>&1 && echo "✅ clang-format found" || echo "⚠️  clang-format not found (optional)"
