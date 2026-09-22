# Compiler
CXX = em++

# Common Flags for both Dev and Prod
COMMON_FLAGS = --bind \
               -s WASM=1 \
               -s ALLOW_MEMORY_GROWTH=1 \
			   -std=c++23

# Debug Flags: 
DEBUG_FLAGS = -fsanitize=address,leak \
			  -sASSERTIONS=1 \
			  -sSAFE_HEAP=1 \
			  -sDEMANGLE_SUPPORT=1 \
# 			  -sASSERTIONS=2 \

# Dev Flags: Fast build, debug symbols
DEV_FLAGS = -O0 -gsource-map $(DEBUG_FLAGS)

# Prod Flags: Optimized execution, minified JS
PROD_FLAGS = -O3 --closure 1

# Source files and Output
SRCS = src/core.cpp src/bindings.cpp
OUT_DIR = dist
TARGET = $(OUT_DIR)/engine.js

# Default target when you type 'make'
all: dev

# Build for Development
dev:
	mkdir -p $(OUT_DIR)
	$(CXX) $(SRCS) $(COMMON_FLAGS) $(DEV_FLAGS) -o $(TARGET)
	@echo "Dev build complete: $(TARGET)"

# Build for Production
prod:
	mkdir -p $(OUT_DIR)
	$(CXX) $(SRCS) $(COMMON_FLAGS) $(PROD_FLAGS) -o $(TARGET)
	@echo "Production build complete: $(TARGET)"

# Clean generated output
clean:
	rm -rf $(OUT_DIR)
	@echo "Cleaned output directory."

.PHONY: all dev prod clean