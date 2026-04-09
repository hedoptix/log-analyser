## :rocket: C++ Log Analyser
A Linux-based CLI log analyser built with C++17, designed to process and analyse real-world log files.
### :pushpin: Features
- :white_check_mark: Parse structured log files (timestamp + level + message)
- :white_check_mark: Count log levels: INFO, WARNING, ERROR
- :white_check_mark: CLI options:
  - ```--stats``` → show statistics
  - ```--level``` → filter logs
- :white_check_mark: Handles invalid lines
- :white_check_mark: Unit tested with Google Test
- :white_check_mark: Dockerized environment
### :bricks: Tech Stack
- C++17
- CMake
- Docker
- Google Test (gtest)
- WSL / Linux
### 	:file_folder: Project Structure
```
loganalyser/
├── include/ 
├── src/
├── tests/ 
├── logs/ 
├── CMakeLists.txt 
├── Dockerfile
└── README.md
```
### :gear: Build & Run (Docker)
**1. Build Docker image** <br/><br/>
```docker build -t log-analyser-env .``` <br/><br/>
**2. Run container** <br/><br/>
```docker run -it -v ${PWD}:/app log-analyser-env /bin/bash``` <br/><br/>
**3. Build project** <br/><br/>
```cmake -S . -B build``` <br/>
```cmake --build build```
### :arrow_forward: Usage
```./build/log_analyser logs/sample.log``` <br/><br/>
**Show stats** <br/>
```./build/log_analyser logs/sample.log --stats``` <br/><br/>
**Filter by level** <br/>
```./build/log_analyser logs/sample.log --level ERROR```
### :test_tube: Running Tests
```./build/runTests```
### :page_facing_up: Example Log Format
```2024-03-01 10:15:23 INFO Starting app``` <br/>
```2024-03-01 10:15:25 ERROR Database failure``` <br/>
```2024-03-01 10:15:30 WARNING Low memory```
### :dart: About This Project
This project demonstrates:
- File processing in C++
- Regex parsing
- CLI design
- Unit testing
- Docker usage
### :girl: Author
Hedi<br/>
Australia
