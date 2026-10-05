# ============================================================
# Industrial Thermal Management & Dynamic Fan Controller
# C++ Application Makefile
# ============================================================

CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -I../include

TARGET = thermal

SOURCES = \
	main.cpp \
	TemperatureSensor.cpp \
	FanController.cpp \
	ThermalMonitor.cpp \
	Logger.cpp

OBJECTS = $(SOURCES:.cpp=.o)

# ============================================================
# Default Build
# ============================================================

all: $(TARGET)

# ============================================================
# Build Application
# ============================================================

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# ============================================================
# Compile Source Files
# ============================================================

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Run Application
# ============================================================

run: $(TARGET)
	cd .. && ./src/$(TARGET)

# ============================================================
# Clean
# ============================================================

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

# ============================================================
# Rebuild
# ============================================================

rebuild: clean all

# ============================================================
# Help
# ============================================================

help:
	@echo ""
	@echo "Industrial Thermal Management"
	@echo ""
	@echo "Available commands:"
	@echo "  make          - Build application"
	@echo "  make run      - Run application"
	@echo "  make clean    - Remove compiled files"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show help"
	@echo ""
