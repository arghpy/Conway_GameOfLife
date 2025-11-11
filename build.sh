set -ex

CFLAGS="-Wall -Wextra -Wpedantic"
INCLUDES="-I./thirdparty/raylib-5.5_linux_amd64/include"
LIBS="-lm -L./thirdparty/raylib-5.5_linux_amd64/lib -lraylib -Wl,-rpath=./thirdparty/raylib-5.5_linux_amd64/lib"

CMD="gcc ${CFLAGS} ${INCLUDES} -o GameOfLife GameOfLife.c ${LIBS}"

eval "${CMD}"
