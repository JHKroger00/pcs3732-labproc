# Interrupções de Teclado e UART no processador ARM

Projeto para a disciplina Laboratório de Processadores. Envolve explorar as interrupções que ocorrem na placa ARM Versatile (emulada pelo QEMU) com o uso de um teclado, junto a uma UART, que transmitirá seus dados de volta para o terminal.

## Instalação das Ferramentas

Para executar o código, é necessário dispor do QEMU e da Toolchain GNU ARM. Abaixo são mostradas as instruções de instalação para o Windows e para o Linux.

### Windows

O instalador do QEMU para Windows pode ser encontrado na [página de downloads do QEMU](https://www.qemu.org/download/#windows). Depois de executar o instalador, é preciso adicionar o local da pasta em que o QEMU foi instalado à variável de ambiente PATH. Este [vídeo]() explica como realizar toda a instalação do QEMU para o Windows 10.

O instalador da Toolchain GNU ARM pode ser encontrado no próprio [site da ARM](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). Se o instalador não estiver disponível para o lançamento mais recente, basta baixar o instalador de uma versão anterior (que irá funcionar normalmente).

### Linux

Para instalar o QEMU, é possível executar os seguintes comandos em um terminal (permitindo a emulação da placa ARM Versatile):

  ```
  sudo apt update
  sudo apt install qemu qemu-kvm qemu-system-arm
  ```

A instalação da Toolchain GNU ARM varia um pouco para diferentes distribuições do Linux (e para versões diferentes de uma dada distribuição, como o Ubuntu), e é um pouco mais complexa do que no Windows (por não haver um instalador disponível). Portanto, é recomendado pesquisar na internet como instalar esta ferramenta de acordo com o sistema operacional utilizado (e.g. "How to install arm-none-eabi-gdb on Ubuntu 20.04"). A resposta disponível neste [link](https://askubuntu.com/questions/1243252/how-to-install-arm-none-eabi-gdb-on-ubuntu-20-04-lts-focal-fossa) explica como fazer a instalação no Ubuntu 20.04.

Vale ressaltar que as únicas ferramentas que são necessárias para a compilação e a geração do binário do código são `arm-none-eabi-as`, `arm-none-eabi-gcc`, `arm-none-eabi-ld`, `arm-none-eabi-objcopy`, e `arm-none-eabi-gdb`. Assim, pode ser necessário adaptar os comandos utilizados para que se faça a instalação apenas destas ferramentas (adicionando-as, por exemplo, à pasta `usr/bin`, para tornar os comandos disponíveis em todo o sistema).

## Build e Execução

`./mk` para compilar e executar o código.

`./mkgdb` para compilar, executar o código, e aguardar uma conexão do GDB.

Nesse caso, o GDB deve ser conectado ao código rodando por outro terminal.

Um jeito de fazer isso é com os comandos:

  ```
  file t.elf
  target remote localhost:1234
  load
  ```

## Avisos

O driver do teclado em particular pode não funcionar se o ambiente de execução for o Docker. Nesse caso, pode-se instalar o GDB e o QEMU no Linux ou no Windows.

O Windows não possui suporte à TUI (Text User Interface) do GDB. Portanto, caso se queira visualizar uma interface mais amigável (a fim de que se possa ver o código no terminal, por exemplo), é necessário utilizar um ambiente Linux.
