# Fundamentals

## Code Style

This project uses **clang-format** for consistent C++ formatting and **clangd** for diagnostics/linting.

### Formatting Style

| Setting | Value | Rationale |
|---------|-------|-----------|
| Base Style | LLVM | Clean, modern, widely adopted in professional C++ |
| Indent | 4 spaces | More readable, common in embedded/game dev |
| Braces | Same line (Attach) | Most common in game dev, widely used in embedded |
| Column Limit | 100 | Practical balance for modern screens |
| Pointer Alignment | Left (`int* ptr`) | Consistent with modern C++ convention |

### Naming Conventions (via clangd/clang-tidy)

| Element | Style | Example |
|---------|-------|---------|
| Classes/Structs/Enums | PascalCase | `PlayerController` |
| Functions/Methods | snake_case | `get_player_health()` |
| Variables | snake_case | `player_count` |
| Constants | SCREAMING_CASE | `MAX_PLAYERS` |
| Member Variables | snake_case with trailing `_` | `health_` |

### Setup

1. **Format on save** (VS Code) - add to `.vscode/settings.json`:
   ```json
   {
     "editor.formatOnSave": true,
     "[cpp]": { "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd" }
   }
   ```

2. **Format on save** (Neovim):
   ```lua
   vim.api.nvim_create_autocmd("BufWritePre", {
     pattern = { "*.cpp", "*.hpp" },
     callback = function() vim.lsp.buf.format() end,
   })
   ```

3. **Manual formatting**:
   ```bash
   clang-format -i file.cpp
   ```
