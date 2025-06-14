| Pattern                                        | One-Line Idea                                                                                            |
| ---------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| **Atomic Flag Spin-Lock**                      | Busy-wait on an `std::atomic_flag` instead of a heavyweight mutex.                                       |
| **Ticket Spin-Lock**                           | Fair spin-lock that hands out “tickets” with `fetch_add` so threads acquire the lock in FIFO order.      |
| **Double-Checked Locking (DCLP) with Atomics** | Use an atomic pointer to avoid locking on the fast path when lazily initializing singletons or caches.   |
| **Call-Once / Lazy Initialization**            | Implement `std::call_once`-style semantics manually with an atomic state variable.                       |
| **Atomic Reference Counting**                  | Maintain object lifetime with an `std::atomic<std::size_t>` ref-count; basis for `shared_ptr` internals. |
| **Lock-Free Stack (Treiber Stack)**            | Push/pop by CAS-ing the head pointer atomically.                                                         |
| **Lock-Free Queue (Michael-Scott / M\&S)**     | Two atomic pointers (head, tail) updated with CAS; supports multiple producers/consumers.                |
| **Sequence Counter (Seqlock)**                 | Writers increment an atomic “sequence” twice; readers retry if they observe an odd sequence.             |
| **Read–Copy–Update (RCU)**                     | Readers proceed lock-free; writers publish a new copy with atomic pointer swaps.                         |
| **Hazard Pointers**                            | Each thread stores an atomic pointer to the node it is reading to make reclamation safe.                 |
| **SPSC Ring Buffer**                           | Single-producer / single-consumer queue with atomic indices and relaxed ordering.                        |
| **Futex-Style Atomic Wait / Notify**           | Spin briefly, then call a blocking wait when an atomic value is unchanged.                               |
| **Compare-And-Swap (CAS) Retry Loop**          | Classic pattern of read-modify-CAS, looping until success—foundation of most lock-free algorithms.       |
| **Atomic Event / Once-Flag**                   | Use an `atomic<bool>` plus `notify_one/notify_all` (C++20) for lightweight event signaling.              |
