# PulseNet

A Linux based distributed system that simulates a heartbeat monitoring system to detect service failures in real time using sockets in 4 different processes.

Using C and C++, modeling multiple services communicating over UDP/IP to synchronize high frequency data across vehicle microservices.


# System Architecture

PulseNet consists of four independent processes:

Heartbeat Monitor (Gateway)
Acts as the central supervisor, listening for heartbeat messages and tracking service health.
Service / ECU Processes (3 nodes)
Each simulated ECU periodically sends heartbeat packets over UDP to indicate it is alive and functioning.

The monitor:

Tracks heartbeat timestamps per service
Detects missed heartbeats and service timeouts
Logs failures and simulates recovery behavior


# Learning Outcomes

Through this project, I gained hands-on experience with:

Distributed systems fundamentals
Embedded-style networking on Linux
Inter-process communication using UDP
Designing resilient software systems
Writing maintainable, testable C/C++ code
