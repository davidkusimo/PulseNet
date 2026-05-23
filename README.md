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

<img width="418" height="336" alt="image" src="https://github.com/user-attachments/assets/950ec8ef-32b5-4e34-8f37-a254da9c037e" />

<img width="317" height="62" alt="image" src="https://github.com/user-attachments/assets/216aea6d-c139-406b-bb9d-6a8139c8fb78" />

# Learning Outcomes

Through this project, I gained hands-on experience with:

Distributed systems fundamentals
Embedded-style networking on Linux
Inter-process communication using UDP
Designing resilient software systems
Writing maintainable, testable C/C++ code

<img width="256" height="31" alt="image" src="https://github.com/user-attachments/assets/ef09fcbe-5626-434f-97f4-6771693b2f49" />
