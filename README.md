# 🧠 42 Philosophers

**Philosophers** is a project from the 42 curriculum that explores **multithreading**, **synchronization**, and **time management** in C by simulating the classic *Dining Philosophers Problem*.

Each philosopher is represented by a thread that cycles through **eating**, **sleeping**, and **thinking**, while competing for limited shared resources (forks). The main challenge is to ensure **no data races, no deadlocks**, and **precise timing**, all under the unpredictable nature of thread scheduling!

---

## ⚙️ Features

- ✅ Each philosopher runs as an independent thread
- ✅ Shared forks are protected with **mutexes**
- ✅ Avoids **deadlocks** using an ordered fork-picking strategy
- ✅ Accurately tracks time with millisecond precision
- ✅ Thread-safe printing (no overlapping messages)
- ✅ Optional argument: number of meals before simulation stops
- ✅ Shutdown when a philosopher dies with no leaks

---

## 🧩 Understanding the Simulation

At its core, the program creates **N philosophers** seated around a table.
Each philosopher alternates between three main states:

1. **Thinking** 🧘 – waiting before attempting to eat again
2. **Eating** 🍝 – takes both forks (mutexes) and updates their last meal time
3. **Sleeping** 😴 – releases forks and rests before thinking again

If a philosopher doesn’t eat within `time_to_die` milliseconds, well... he dies, and the simulation ends in a state of grief. 🖤

---

## 🧵 Thread Synchronization

To avoid race conditions and ensure fairness:
- Each fork is a **mutex** shared between two philosophers.
- Philosophers pick up forks in a specific order depending on their ID (odd/even) to avoid deadlocks.
- A **monitor thread** constantly checks for starvation or completion of all meals.

A **thread-safe printing mechanism** guarantees that no two messages overlap in the terminal.

---

## ⏱️ Timing Precision

To ensure realistic and reproducible behavior across different machines, I set a **minimum of 60 ms** for all time parameters (`time_to_die`, `time_to_eat`, and `time_to_sleep`).

### Why 60 ms?
- For what I've read, `usleep()` and the OS scheduler are not that precise.
- Mutex locking, printing, and thread switching add a bit of latency.
- Extremely short intervals can cause unfair deaths or inconsistent results between systems.
- 60 ms ensures a stable behavior.

---

## How To Use

### ⚙️ Parameters
./philo  number_of_philosophers  time_to_die  time_to_eat  time_to_sleep [number_of_times_each_philosopher_must_eat]


### Compilation
```bash
make
./philo 5 800 200 200

./philo 5 800 200 200 7
```

## Debug mode

In Makefile there is: `DEBUG=0`, you can set to 1 and recompile with `make re`.

After everyone eat the number of meals set, or one philo dies, the program shows how many meals each philo took!

---

## Thanks for Reading!

If you found it interesting or helpful, feel free to ⭐ the repository, it really means a lot!
