#pragma once
#include <string>
#include <vector>

class Character;
class Room;

class Game
{
    private:
        Character* player;
        Room* currentRoom;
        std::vector<Room*> allRooms;
        bool running;

        void buildWorld();

        void processCommand(const std::string& cmd);

        void combat(Room* room);

        void handleInventory();
        
        void talkToNPC();

    public:
        Game();

        void start();

        void run();

        void save(const std::string& filename = "save.txt");

        bool load(const std::string& filename = "save.txt");

        ~Game();
};