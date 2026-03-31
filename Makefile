CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
TARGET = slau_solver.exe
SRCS = src/main.cpp src/matrix_utils.cpp src/solvers.cpp src/experiments.cpp src/ui.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	del /Q $(TARGET) *.o 2>nul

run: $(TARGET)
	.\$(TARGET)