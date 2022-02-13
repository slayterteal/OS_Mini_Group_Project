!!! DO NOT SUBMIT !!!

This is purely a testbed for POSIX message queue. 

main.c is one process while, main0.c is meant to be a seperate process. The goal is to send and recieve messages and use the data that is shared.

I'll include links and notes in here as well.

# Message Passing
Message queues allow processes to communicate by exchanging structured messages. As with pipes and FIFOs, processes can message queues follow a message passing IPC model for exchanging data in discrete messages. However, message queues differ from pipes in several important ways:

- While pipes send unstructured byte streams, messages are sent as distinct units. When a message is retrieved from the queue, the process receives exactly one message in its entirety; there is no way to retrieve part of a message and leave the rest in the queue.
- Message queues use special identifiers, rather than file descriptors. As a result, message queues require special functions for sending and receiving data, rather than the standard file interface functions.
- Message queues have associated metadata that allows processes to specify the order in which messages are received. That is, message queues do not require or guarantee a first-in, first-out ordering.
- Message queues have kernel-level persistence and use special functions or utilities for removing them. Killing the process will not remove the message queue.

# Links 
https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/MQueues.html

