nasm -f win64 src\kernel.asm -o out\kernelASM.obj
gcc -c src\main.c -o out\main.obj
gcc -c src\kernel.c -o out\kernelC.obj
gcc out\main.obj out\kernelC.obj out\kernelASM.obj -o out\dot_product.exe
out\dot_product.exe
