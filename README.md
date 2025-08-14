
# Compile and Run (macOS)

## 1. Install Raylib (using Homebrew)

```bash
brew install raylib
```

## 2. Compile (Apple Silicon/M1/M2/M3)

```bash
g++ -o tetwist src/blockMain.cpp src/blockSub.cpp src/board.cpp src/color.cpp src/gameHandler.cpp src/main.cpp src/pos.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -lm -ldl -pthread -framework OpenGL
```

## 3. Run

```bash
./tetwist
```

# Compile and Run (Linux/Windows)

```bash
g++ -o tetwist src/blockMain.cpp src/blockSub.cpp src/board.cpp src/color.cpp src/gameHandler.cpp src/main.cpp src/pos.cpp -lraylib -lm -ldl -pthread -lGL; tetwist
```


## Resources used

Programming with Nick - https://www.youtube.com/watch?v=wVYKG_ch4yM
