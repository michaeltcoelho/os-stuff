### Threads

Thread is an active entity, it means that it's an executing unit of a process. Threads work simultaneously with others, many threads executing, which require coodination, sharing of I/O devices, CPU, memory.


### Process vs Thread

A single thread of process is represented by its virtual address space, which contains all the virtual to physical addresses for the process, for its code, its data, files.
The process is also represented by its execution context, registers, program counters, stack pointer.
The OS represents all said information above in a process control block (PCB).
Threads represent multiple, independent execution contexts, they are part of the same virtual address space, so sharing code, data and files, however each thread has its own execution context, values of registers, program counter, stack etc. The OS representation of such a multithreaded process will be more complex process control block (PCB) then the former one. It will keep for each thread one data structure with execution context information.

### Are threads useful on a single CPU? or when numbers of Threads > numbers of CPUs?

Let's say we have a thread of process that requests some data from the disk, it takes some time for the disk to provide the data back to the thread, in the meantime the threads is idle, let's call the idle time by t_idle. If the t_idle is longer than the time it takes to make the context switch, then it starts making sense to perhaps context switch from the idle thread to another thread. It turns out that, the t_time must be longer than two context switches, one for the idle thread and another one for the next thread to be executed.
The benefits of using multithread is that when context switching, different from processes, threads share the same virtual address space and because of that its costs is much lower than the process context switches.

In sum, multithread is useful because it hides the latency behind IO operations, which causes the running thread idling time, benefiting from context switching and making a better use of the CPU. Even on a single CPU.

### Basic Threads mechanisms
