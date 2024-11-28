# Log Analyzer

A C++ project that analyzes web server logs to identify the top 10 most visited pages using a custom hash table and `std::unordered_map`. The project compares the performance of both implementations and provides execution time statistics.

## Features
- Implements a custom hash table with:
    - **Separate chaining** for collision resolution.
    - A **polynomial rolling hash function** using a prime multiplier.
- Compares the performance with `std::unordered_map`.
- Extracts filenames from web server logs.
- Identifies and displays the top 10 most visited pages.
- Provides execution time for both implementations.

## Technologies Used
- **Programming Language:** C++
- **IDE:** CLion
- **Build System:** CMake
- **Libraries:** `<list>`, `<unordered_map>`, `<vector>`, `<algorithm>`, `<ctime>`

## File Structure
```plaintext
log-analyzer/
├── src/                          # Source code directory
│   └── main.cpp                  # Main C++ file for the project
├── logs/                         # Directory for log files
│   └── access_log                # Sample log file
├── report/                       # Directory for documentation
│   └── TermProject.pdf   # Project report
├── README.md                     # Project documentation
```

## How to Use
1. Clone the repository:
   git clone <repository-url>
2. Navigate to the project folder:
   cd log-analyzer
3. Build the project using CMake:
   mkdir build && cd build
   cmake ..
   make
4. Run the program:
   ./log-analyzer
5. Place your web server log file in the `logs/` directory, ensuring the file path in `main.cpp` is:
   const string filePath = "logs/access_log";

## Performance Results
The performance results below compare the execution times of the custom hash table and `std::unordered_map` implementations:

- **Custom Hash Table:** 1.23 seconds
- **std::unordered_map:** 0.98 seconds

## Screenshots
Screenshots of program output have been included in the report, but should demonstrate the following:
- Top 10 most visited web pages for the custom hash table.
- Top 10 most visited web pages for `std::unordered_map`.

To save screenshots:
- Run the program and capture the console output.
- Save screenshots in a folder like `screenshots/` for documentation purposes.

## Future Improvements
- **Optimize the hash function:** Experiment with other hash functions for improved performance.
- **Enhance functionality:** Add support for real-time log analysis.
- **Improve usability:** Build a GUI for better visualization of results.

## License
This project is licensed under the MIT License. See the LICENSE file for details.
