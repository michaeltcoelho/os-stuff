## Processos

Podemos definir processos como programas em execucao
Processos mantem estado, que sao informacoes sobre si e a plataforma
na qual ele esta sendo executado.

O SO gerencia o hardware em nome das aplicacoes. As aplicacoes quando nao estao sendo
executadas sao consideradas entidades estaticas em um dispositivo de armazenamento persistente.
Como disco rigido, memoria flash etc.

Quando a aplicacao e executada, ou seja, e carregada em memoria, essa assumira diferentes estados
durante sua execucao.

## Como e um processo

O processo encapsula seu estado em algo que e chamado de address space. O seu estado e dividido em alguns tipos, como:

### Tipos de estados de um processo

- Texto de Dados
    - Estado estatico, e carregado em memoria durante a inicializacao do processo.
- Heap
    - Estado criado dinamicamente durante a execucao do processo.
- Stack
    - Uma estrutura de dados LIFO, criado dinamicamente durante o tempo de execucao. Aumenta e reduz sua capacidade de armazenamento
    - Armazena escopo de funcoes.

### Address space

E definido por um range de enderecos virtuais em memoria, indo de V0 ate VMax.
O kernel mantem uma tabela virtual de enderecos que sao utilizadas por processos, nessa tabela (uma estrutura de dados hash table) 
ha um mapeamento do endereco virtual 0x03f5 para um endereco fisico, 0x45u4g.

Pode nao haver enderecos disponiveis na memoria fisica, sendo assim o kernel ira fazer o SWAP do address spaces de alguns processos para o disco e quando for necessario, ira carrega-lo em memoria novamente.

## Como o SO sabe o que um processo esta executando?

Um programa e composto de intrucoes, essas sao executadas sequencialmente ou nao pela CPU, pode haver loops, jumps e interrupcoes no meio do programa
Para saber em qual momento (instrucao) da execucao a CPU esta, e utilizado um regitrador chamado PC - Program Counter e alguns outros registradoes que ira armazenar a proxima instrucao a ser executada, dados cacheados para nao necessitar ir a memoria DRAM novamente etc.

## O que e um PCB (Process Control Block)?

E uma estrutura de dados que o SO mantem para cada processo que ele esta gerenciando. Nessa estrutura e mantido os estados referente ao processo.

- Estado do processo
- Numero do processo
- PC - Program Counter
- Registradores
- Limites de memoria
- Lista de arquivos abertos
- Prioridade
- Signal Mask
- Informacoes de CPU Scheduling

E criado quando o processo e criado.
Certos campos sao atualizados no PCB quando o estado do processo muda.

### Como um PCB e usado?

Quando ocorre a Context Switching, ou seja, quando o Time Slicing e atingido, o processador ira salvar o estado do processo sendo executado e, em seguida, recuperar o estado de um outro programa na memoria e comecar a executar suas instrucoes.

O PCB e atualizado e salvo na memoria, enquanto o PCB do outro programa e restaurado a partir da memoria.

## Context Switching

Mudar a CPU a partir do contexto de um processo P1 para o contexto de um outro processo P2

Essa troca e custosa!

- custos diretos: Numero de ciclos de CPU para carregar e armazenar instrucoes
- custos indiretos: Cache desatualizados, perda da dados no cache.

## Ciclo de vida de um Processo

Processos podem estar em dois estados, running or idle

Quando o estado de um processo e Running, ele pode ser interrompido, assim ocorrendo o Context Switching. Com isso, o estado do processo e Idle, ele esta em memoria junto com seu contexto, contudo nao esta sendo executado pelo processador, ele esta em um estado que e chamado de Ready state.

### Estados de Processos

- New: Quando o processo e criado, o SO ira iniciar e criar um PCB e alguns recursos iniciais. Assim o processo e admitido.
- Ready: O processo esta pronto para comecar a ser executado pelo processador, ele esta pronto para ir para o Running state.
- Running: O processo esta sendo executado pelo processador, ele pode ser interrompido, com Context Switching acontecendo e voltar para o Ready state.
- Waiting: Caso haja alguma chamada I/O pelo porcesso ou este esteja aguardando por um outro evento. Apos completado, vai para o Ready State.
- Terminated: Quando todas as operacoes sao completadas ou quando acontece um erro na execucao, o processo e terminado e um codigo de resposta e retornado.

## Como processos sao criados?

Durante o processo de booting, o kernel ira criar alguns processos, chamados de processos Root.
Um exemplo de um processo Root e o Init, que e o processo pai de todos os processos, diretamento ou indiretamente, e,
automaticamente, adota todos os processos orfaos.

Os processos tem um relacao um com o outro, o processo que esta criando um novo a partir dele e chamado de Parent, e o processo criado, e chamado de Child.

Init -> shell -> ls - aqui vemos que o processo Root Init, criou o processo filho shell, que este criou o processo filho ls.

### Mecanismos para criacao de processos

Ha dois mecanismos para a criacao de processos:

- Fork: 
    Ira copiar o PCB do processo Parent, para o PCB do novo processo Child
    O processo Child continua a execucao das intrucoes a partir do Fork.
    O PCB do processo Child tem os mesmos valores do PCB do processo Parent.

- Exec:
    Ira substituir a imagem do processo atual pelo novo programa.
    Ira carregar o novo programa no mesmo processo e a execucao se dara a partir da
    primeira instrucao do programa.

## Qual o papel do CPU Scheduler?

O CPU executa os processos que estao em Ready state, acontece que pode haver muitos processos em Ready state na Ready Queue, quem ira decidir qual processo a CPU ira executar? Ha um processo responsavel por controlar quem ira consumir os recursos de CPU em uma maquina, esse processo e chamado de CPU Scheduler, e quanto tempo esta disponivel para ele ser executado,

O OS deve ser eficiente:
- preempt:  interromper e salvar o contexto do processo que esta em processamento
- schedule: executar o CPU Scheduler para escolher o proximo processo
- dispatch: disparar o processo para execucao e trocar a CPU para seu contexto.

## Por quanto tempo um processo deve executar? Com qual frequencia o CPU Scheduler deve ser executado?

Tempo util de trabalho da CPU = Tempo processando o programa / tempo total

O tempo que um processo tem para ser executado e chamado de Timeslice

## Processos podem interagir entre si?

Sim, atraves da IPC - Inter Proccess Communication. Os mecanismos sao:
- Transferir dados/infos entre address spaces
- Manter protecao e isolacao entre processos
- Fornece flexibilidade e performance

### Messaging-passing IPC

O SO fornece um canal de comunicacao, como um buffer entre ambos os processos
P1 <-> channel <-> P2

Processos
  - write (send) / read(recv) mensagens para/a partir de buffers - channels.

- Requer que o dado seja copiado para dentro/fora do kernel, passando pelo buffer.


### Shared Memory IPC

O OS cria um canal compartilhado - buffer - e mapeia para o address space do outro processo
O processo read/write diretamento a partir do buffer
+ O OS nao se intromete no buffer, nao tem que controllar. A troca de dados nao e custosa. Nao requer que dado seja copiado para dentro e fora do kernel.
- Talvez reeimplementar codigo em ambos os lados.
- Mapear o buffer para o address space do outro processo e custoso.

