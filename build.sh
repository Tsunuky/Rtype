mkdir -p build
cd build
conan install .. --build=missing -s compiler.libcxx=libstdc++11 -s compiler.version=10
cmake .. -G "Unix Makefiles"
cmake --build . --parallel
echo '[Core]
GAME="./lib/libr-type_game.so"
LIB="./lib/libr-type_sfml.so"' > conf.ini
