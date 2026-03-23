# 1024-bit BigInt Calculator

> A lightweight, custom C implementation of a 1024-bit integer calculator capable of performing arithmetic operations on exceptionally large hexadecimal numbers.

## 📖 Description

Standard C data types like `unsigned long long` max out at 64 bits, which is insufficient for cryptography, scientific computing, or extremely large mathematical operations. This project bypasses those limits by implementing a custom `BigInt` structure. It stores large numbers as arrays of 32-bit limbs, allowing it to process integers up to 1024 bits in size (represented by up to 256 hexadecimal characters).

The calculator takes two hexadecimal string inputs, parses them into the internal `BigInt` format, and performs the requested mathematical operation, outputting the exact hexadecimal result.

## ✨ Features

* **Massive Number Support:** Handles integers up to 1024 bits (32 `unsigned int` limbs).
* **Hexadecimal Parsing:** Safely parses varying-length hex strings directly into memory.
* **Core Arithmetic:** Supports addition (`+`), subtraction (`-`), and multiplication (`*`).
* **Negative Subtraction:** Intelligently handles `A < B` subtraction scenarios by automatically formatting the result with a negative sign.
* **Memory Efficient:** Operates without dynamic memory allocation, relying strictly on fixed-size arrays.

## 🛠️ Tech Stack

* **Language:** C
* **Core Concepts:** Array manipulation, bitwise shifting, carry/borrow logic, and arbitrary-precision arithmetic.

## 🚀 Getting Started

### Prerequisites

You will need a standard C compiler (such as GCC) installed on your system.

### Installation & Execution

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/C0NFR1NGO/bigint-calculator.git](https://github.com/C0NFR1NGO/bigint-calculator.git)
