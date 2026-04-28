[![C++ CI](https://github.com/hedoptix/log-analyser/actions/workflows/ci.yml/badge.svg)](https://github.com/hedoptix/log-analyser/actions/workflows/ci.yml)
## :rocket: C++ Log Analyser
A Linux-based CLI log analyser built with C++17, designed to process and analyse real-world log files.
## How to Use
- :arrow_down: **Clone the Repository** <br/><br/>
```git clone https://github.com/hedoptix/log-analyser.git``` <br/>
```cd log-analyser``` <br/><br/>
- :arrow_forward: **Build & Run** <br/><br/>
```cmake -S . -B build``` <br/>
```cmake --build build``` <br/>
```./build/log_analyser logs/sample.log --stats```
## :pushpin: Features
- :white_check_mark: Parse structured log files (timestamp + level + message)
- :white_check_mark: Count log levels: INFO, WARNING, ERROR
- :white_check_mark: CLI options:
  - ```--stats``` → show statistics
  - ```--level``` → filter logs
- :white_check_mark: Handles invalid lines
- :white_check_mark: Unit tested with Google Test
- :white_check_mark: Dockerized environment
- :white_check_mark: Support both plain text and JSON log formats
## :bricks: Tech Stack
- C++17
- CMake
- Docker
- Google Test (gtest)
- WSL / Linux
## 	:file_folder: Project Structure
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
## :gear: Build & Run (Docker)
**1. Build Docker image** <br/><br/>
```docker build -t log-analyser-env .``` <br/><br/>
**2. Run container** <br/><br/>
```docker run -it -v ${PWD}:/app log-analyser-env /bin/bash``` <br/><br/>
**3. Build project** <br/><br/>
```cmake -S . -B build``` <br/>
```cmake --build build```
## :arrow_forward: Usage
```./build/log_analyser logs/sample.log``` <br/><br/>
**Show stats** <br/>
```./build/log_analyser logs/sample.log --stats``` <br/><br/>
**Filter by level** <br/>
```./build/log_analyser logs/sample.log --level ERROR``` <br/><br/>
**Multiple Files** <br/>
```./build/log_analyser logs/a.log logs/b.log logs/c.log --stats``` <br/>
:point_right: The analyser will process all files and combine the results. <br/><br/>
```./build/log_analyser logs/*.log --stats``` <br/>
:point_right: The shell expands *.log into all matching log files automatically.
## :test_tube: Running Tests
```./build/runTests```
### :page_facing_up: Text Log Example
```2024-03-01 10:15:23 INFO Starting app``` <br/>
```2024-03-01 10:15:25 ERROR Database failure``` <br/>
```2024-03-01 10:15:30 WARNING Low memory```
### :page_facing_up: JSON Log Example
```{"time":"2024-01-01 10:00:00","level":"ERROR","message":"fail"}```
## :dart: About This Project
This project demonstrates:
- File processing in C++
- Regex parsing
- CLI design
- Unit testing
- Docker usage
## :girl: Author
Hedi<br/>
Australia
