#pragma once
#include <string>
#include <vector>

class Character;
class Room;
class Shop;

class Game
{
    private:
        Character* player;
        Room* currentRoom;
        std::vector<Room*> allRooms;
        std::vector<bool> clearedRooms;
        std::vector<Shop*> allShops;
        bool running;

        void buildWorld();
        
        void processCommand(const std::string& cmd);

        void combat(Room* room);

        void handleInventory();

        void talkToNPC();

        std::string getSavePath(int slot) const;

        void showSaveSlots() const;

    public:
        Game();

        void start();

        void run();

        void save(int slot = 1);

        bool load(int slot);

        ~Game();
};