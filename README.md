# 🖥️ Operating System Scheduling & Partitioning Simulator

## 📌 Overview
A C++ console-based simulator that demonstrates key **Operating System concepts**:

- **CPU Scheduling** (FCFS, SJF, Round Robin)
- **Memory Partitioning** (Fixed & Variable)

It calculates performance metrics and recommends the best scheduling algorithm based on average waiting time.

---

## ✨ Key Features

### 🔄 CPU Scheduling
- **Non-Preemptive**:  
  - First Come First Serve (FCFS)  
  - Shortest Job First (SJF)  
- **Preemptive**:  
  - SJF Preemptive  
  - Round Robin (custom quantum)
- **Smart Selection**:  
  - Auto-determines best algorithm using average waiting time

### 🧠 Memory Partitioning
- **Fixed Size**:  
  - Allocates predefined memory blocks  
  - Tracks internal & external fragmentation
- **Variable Size**:  
  - Simulates dynamic memory allocation per process

### 📊 Metrics Calculated
- Turnaround Time  
- Waiting Time  
- Completion Time  
- Fragmentation Report

---

## 🚀 How to Run

```bash
g++ scheduler.cpp -o scheduler
./scheduler
