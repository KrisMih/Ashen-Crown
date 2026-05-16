CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = AshenCrown

SRCS = main.cpp \
       src/entities/entity.cpp \
       src/entities/character.cpp \
       src/entities/classes.cpp \
       src/entities/enemy.cpp \
       src/items/item.cpp \
       src/items/inventory.cpp \
       src/items/statuseffects.cpp \
       src/world/room.cpp \
       src/world/shop.cpp \
       src/core/game.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)