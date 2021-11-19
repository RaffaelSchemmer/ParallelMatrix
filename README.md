__Assume-se para este tutorial que o computador configurado possui arquitetura de máquina multicore de 64bits (x86-64).__

C (Flags para compilação):
========

Configurar o ambiente:
--------

1. Donwload Ubuntu 20.10 LTS
2. Em Update Manager instalar todos os Updates disponíveis.
3. sudo apt-get install gcc -y

Compilação das aplicações:
--------

1. gcc -msse3 -o sse matrixS.c
2. gcc -mavx -o avx matrixA.c
3. gcc -fopenmp -mavx -o avxomp matrixO.c

Execução das aplicações:
--------

1. time ./sse
2. time ./avx
3. time ./avxomp
