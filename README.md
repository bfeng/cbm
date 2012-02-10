This is a programming assignment from CS553: Cloud Computing.

This project aims to teach you how to benchmark different parts of a computer system, from the processors, memory, disk, and network.
You can be creative with this project. You are free to use C, C++ and any abstractions such as sockets, threads, events, etc. that might be needed. Although you are free to use any machines (PC, UNIX, etc) for your initial development, you must use the CSRocks cluster (csrocks.cs.iit.edu) for your final evaluation.
In this project, you need to design a benchmarking program that has four components:
1. CPU: Measure the processor speed, in terms of floating point operations per second (Giga FLOPS, 109 FLOPS) and integer operations per second (Giga IOPS, 109 IOPS); measure the processor speed at varying levels of concurrency (1 thread, 2 threads, 4 threads, and 8 threads).
2. Memory: Measure the memory speed; your parameter space should include read operations, write operations, sequential access, random access, varying block sizes (1 byte (B), 10B, 100B, 1KB, 10KB, 100KB, 1MB), and varying the concurrency (1 thread, 2 threads, 4 threads, and 8 threads). The metrics you should be measuring are throughput
(Megabytes per second, MB/sec) and latency (milliseconds, ms).
3. Disk: Measure the disk speed; your parameter space should include read operations, write operations, sequential access, random access, varying block sizes (1B, 10B, 100B, 1KB, 10KB, 100KB, 1MB, 10MB, 100MB, 1GB), and varying the concurrency (1 thread, 2 threads, 4 threads, and 8 threads). The metrics you should be measuring are throughput (MB/sec) and latency (ms). Hint: there are multiple ways to read and write to disk, explore the different APIs, and pick the fastest one out of all them.
4. Network: Measure the network speed in terms of bytes/second; your parameter space should include the 1Gb/s Ethernet controller (between 2 physical nodes), the loopback interface card (between 2 processes on the same node), the TCP protocol stack, UDP, varying packet/buffer size (1B, 10B, 100B, 1KB, 10KB, 100KB, 1MB), and varying the concurrency (1 thread, 2 threads, 4 threads, and 8 threads). The metrics you should be measuring are throughput (Megabits per second, Mb/sec) and latency (ms).

Other requirements:
You must write all benchmarks from scratch. You can use well known benchmarking software to verify your results, but you must implement your own benchmarks. Do not use code you find online, as you will get 0 credits for this assignment.
All of the benchmarks will have to evaluate concurrency performance; concurrency can be achieved using threads. Be aware of the thread synchronizing issues to avoid inconsistency or deadlock in your system.
Your CPU, memory, disk, and network (loopback) benchmarks can all be done on a single node. The network (1Gb/s Ethernet) benchmarks will have to be done between 2 nodes.
Experiments should be done in such a way that they take multiple seconds to minutes to run, in order to amortize any startup costs of the experiments.
Not all timing functions have the same accuracy; you must find one that has at least 1ms accuracy or better.
Since there are many experiments to run, find ways (e.g. scripts) to automate the performance evaluation.
Since there are only ~15 nodes in CSRocks and 60 students in the class, plus 2 other classes that use this cluster (CS546 and CS550), it's likely that the cluster will be heavily used; it is important to understand what else is running (processes, CPU consumption,
etc) on each node during your benchmarks so that you can explain the results.
Since CSRocks is a heavily used cluster, your results will likely vary widely at peak times. In order to mitigate this, all benchmarks must be run 3 times, and the reported values should be the average and standard deviation.
No GUIs are required. Simple command line interfaces are fine.
