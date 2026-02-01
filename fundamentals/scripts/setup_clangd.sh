#!/bin/bash

# Change to project root directory
cd "$(dirname "$0")/.."

echo "🔧 Setting up clangd configuration..."

# Detect compiler and paths
if command -v g++ >/dev/null 2>&1; then
    GCC_VERSION=$(g++ -dumpversion | cut -d. -f1)
    COMPILER="g++"
elif command -v clang++ >/dev/null 2>&1; then
    CLANG_VERSION=$(clang++ --version | head -n1 | sed 's/.*version \([0-9]*\).*/\1/')
    COMPILER="clang++"
else
    echo "⚠️  No suitable C++ compiler found"
    exit 1
fi

# Platform-specific configuration
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    # Windows with MSYS2/Cygwin
    cat > .clangd << 'CLANGD_EOF'
CompileFlags:
  Add:
    - -std=c++23
    - -Wall
    - -Wextra
  Compiler: g++

Index:
  Background: Build

Diagnostics:
  UnusedIncludes: Strict
  MissingIncludes: Strict

InlayHints:
  Enabled: true
  ParameterNames: true
  DeducedTypes: true
CLANGD_EOF

elif [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    cat > .clangd << 'CLANGD_EOF'
CompileFlags:
  Add:
    - -std=c++23
    - -Wall
    - -Wextra
    - -I/usr/local/include
    - -I/opt/homebrew/include
  Compiler: clang++

Index:
  Background: Build

Diagnostics:
  UnusedIncludes: Strict
  MissingIncludes: Strict

InlayHints:
  Enabled: true
  ParameterNames: true
  DeducedTypes: true
CLANGD_EOF

else
    # Linux - detect architecture and GCC paths
    ARCH=$(dpkg --print-architecture 2>/dev/null || echo "x86_64")
    if [ "$ARCH" = "amd64" ]; then
        ARCH="x86_64"
    fi
    
    cat > .clangd << CLANGD_EOF
CompileFlags:
  Add:
    - -std=c++23
    - -Wall
    - -Wextra
    - -I/usr/include/c++/${GCC_VERSION}
    - -I/usr/include/${ARCH}-linux-gnu/c++/${GCC_VERSION}
    - -I/usr/include/c++/${GCC_VERSION}/backward
  Remove:
    - -W*
  Compiler: ${COMPILER}

Index:
  Background: Build

Diagnostics:
  UnusedIncludes: Strict
  MissingIncludes: Strict
  ClangTidy:
    Add:
      - modernize-*
      - performance-*
      - readability-*
    Remove:
      - modernize-use-trailing-return-type

InlayHints:
  Enabled: true
  ParameterNames: true
  DeducedTypes: true
  Designators: true

Hover:
  ShowAKA: true
CLANGD_EOF
fi

echo "✅ clangd configuration created for $OSTYPE with $COMPILER"
