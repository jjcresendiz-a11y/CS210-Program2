# Program 2 — Complexity Analysis

**Student:** Jesus Resendiz  
**Project:** STL Load Balancer

## Implementation completed

- Implemented `loadbalancer.cpp` methods: time access, time increment, request insertion, request removal, empty check, and size check.
- Implemented the queue-based simulation in `p2.cpp`.
- Added a fixed random seed (`1`) so the program produces repeatable output.
- Corrected the Makefile so `make` builds the Program 2 executable named `p2`.
- Left the queue selected as the final default configuration for the Queue Gradescope submission.
- Tested the stack and all three priority-queue configurations separately.

## Operation complexity

Let `n` be the number of requests currently stored in the load balancer.

| Container | Add request | Read next request | Remove next request | Empty/size | Extra memory |
|---|---:|---:|---:|---:|---:|
| `queue` | O(1) | O(1) | O(1) | O(1) | O(n) |
| `stack` | O(1) | O(1) | O(1) | O(1) | O(n) |
| `priority_queue` | O(log n) | O(1) | O(log n) | O(1) | O(n) |

The queue and stack use constant-time insertion and removal because they only operate at their permitted ends. A priority queue is implemented as a binary heap: `top()` is constant time, but inserting and removing can move an element through the heap, which takes O(log n).

The three priority queues have the same asymptotic complexity. Their comparators only change which request is considered highest priority:

- `MaxProcessTime`: longest request first.
- `MinProcessTime`: shortest request first.
- `MaxPID`: newest/highest-PID request first.

## Simulation complexity

The simulation runs for 10,000 time units. The queue and stack versions take O(T) container-operation time for T simulation steps. The priority-queue versions take O(T log n) in the worst case because arrivals and removals can require heap reorganization. Since the program stores requests, all versions use O(n) memory.

## Output comparison

The following results were produced with the fixed seed `1` and the same 10,000-time-unit simulation. The number of output lines is the number of completed requests.

| Configuration | Completed requests | Average completed process time | First completed PIDs |
|---|---:|---:|---|
| Queue (FIFO) | 197 | 247.05 | 1, 4, 7, 5, 3 |
| Stack (LIFO) | 204 | 236.21 | 7, 9, 17, 10, 8 |
| Max process time | 105 | 463.73 | 3, 8, 10, 2, 6 |
| Min process time | 399 | 121.08 | 7, 9, 13, 1, 4 |
| Max PID | 204 | 236.21 | 7, 9, 17, 10, 8 |

The stack and MaxPID results are identical in this run because PID values increase in insertion order. Choosing the newest request by PID therefore produces the same order as taking the most recently inserted request from a stack.

The MaxProcessTime queue completed fewer requests because it repeatedly selected long jobs. The MinProcessTime queue completed more requests because it prioritized short jobs, although that policy can make long requests wait much longer. The FIFO queue gives requests the fairest arrival-order treatment and avoids priority-based starvation, but it does not maximize the number of short requests completed in this test.

## Files used for the comparison

- `queue_output.txt`
- `stack_output.txt`
- `max_process_time_output.txt`
- `min_process_time_output.txt`
- `max_pid_output.txt`

The final source configuration has `queue<request>` active in `loadbalancer.h` and `front()` active in `loadbalancer.cpp`. For the other Gradescope assignment, activate one alternative declaration in `loadbalancer.h` and activate `top()` in `loadbalancer.cpp`.
