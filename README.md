# LatencyTest

This is a C++ test task by [Deltix Inc.](www.deltixlab.com)

## Rationale

Having a high-end multicore x86-64 machine actively running nothing but your application, You need to find the most efficient way (from the latency minimization perspective) to transfer simple data items (unsigned 32-bit integers) from one thread to another.

## Content

This repository consists of three main parts:
  * `AbstractTransport` - abstract class for a component capable to transfer data between two threads. We also provide a simple default implementation `DefaultTransport`.
  * `AbstractProfiler` - abstract class for a component capable to measure latency of different transport implementations.
  * `Application` - a simple benchmark runner, that performs data transmissions via `AbstractTransport` and calculates statistics using `AbstractProfiler`.

## Your Task

  1. Develop latency testing metodology and write it to `YourProfiler` implementation of `AbstractProfiler` class.
  2. Write `YourTransport` implementation of `AbstractTransport`. Your class must outperform our simple implementation `DefaultTransport` at least on measurements made by `YourProfiler`.
  3. Send us a link to a **GitHub** repository with your implementations.

## Acceptance Criteria

  1. You should not use any kind of message broker framework or profiling toolkit, instead you should implement this logic by yourself. 
  2. Your are allowed but not obligated to use synchronization primitives, collections and utility classes from any commonly used C++ libraries (STL, POSIX Threads, Qt, Boost).
  3. From the other hand, we should be able to build your solution out-of-the-box using Make and Clang on CentOS 7 machine with nothing but compiler and standard headers installed.
