# Interrupções de Teclado e UART no processador ARM

Projeto para a disciplina Laboratório de Processadores. Envolve explorar as interrupções que ocorrem na placa ARM Versatile (emulada pelo QEMU) com o uso de um teclado, junto a uma UART, que transmitirá seus dados de volta para o terminal.

## Build e Execução

`./mk` para compilar e executar o código.

`./mkgdb` para compilar, executar o código, e aguardar uma conexão do GDB.

Nesse caso, o GDB deve ser conectado ao código rodando por outro terminal.

Um jeito de fazer isso é com os comandos:

  file t.elf
  target remote localhost:1234
  load

## Avisos

O driver do teclado em particular pode não funcionar se o ambiente de execução for o Docker. Nesse caso, pode-se instalar o GDB e o QEMU no Linux ou no Windows.
