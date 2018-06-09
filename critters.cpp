#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

class CritterFood {
 public:
  int level, stackSize;
  CritterFood(int healingPower, int quantity);
};

CritterFood::CritterFood(int healingPower, int quantity) {
  level = healingPower;
  stackSize = quantity;
}

class Critter {
 protected:
  int earningsRate;
  int health;  // critter health
 public:
  std::string name;  // critter name

  int maxHealth;  // max critter health

  void introduce() {
    std::cout << "My name is " << name << ", I have " << health << "/"
              << maxHealth << " health, and I produce " << earningsRate
              << " gold per tick!" << std::endl;
  }

  void askForName() { // get critter name
    std::cout << "Input a name for your critter: ";
    getline(std::cin, name);
    std::cout << "You named your critter \"" << name << "\"" << std::endl;
  }

  int feed(CritterFood* critterfood) {
    if (health + (*critterfood).level <= maxHealth) {
      if ((*critterfood).stackSize > 0) {
      	(*critterfood).stackSize--;
      	health += (*critterfood).level;
    	  std::cout << "You successfully fed " << name << " "
      	          << (*critterfood).level << " food!" << std::endl;
      } else {
      	std::cout << "You do not have any more critter food in that slot!";
      }

      if ((*critterfood).stackSize == 0) {
        delete critterfood;
        return 1;
      } else {
        return 2;
      }
    } else {
      std::cout << "Your critter isn't hungry right now!" << std::endl;
      return 0;
    }
  }

  void damage(int amount) { health -= amount; }

  int getHealth() { return health; }

  int getEarningsRate() { return earningsRate; }

  Critter(int maxHealth, int earningsRate);
};

Critter::Critter(int healthValue, int goldEarningsRate) {
  if (healthValue) { // if critter isn't being used as a placeholder.
    health = healthValue;
    maxHealth = healthValue;
    earningsRate = goldEarningsRate;
    askForName();
  }
}

class Player {
 public:
  int gold;
  Critter* critters[10];
  CritterFood* inventory[10];

  void displayInventory() {
  	std::cout << "You have " << gold << " Gold." << std::endl << std::endl;
    for (int i = 0; i < 10; i++) {
      if ((*inventory[i]).stackSize != 0) {
        std::cout << "  " << (*inventory[i]).stackSize << " * Level "
                  << (*inventory[i]).level << " Critter Food" << std::endl;
      } else {
        std::cout << "  Empty" << std::endl;
      }
    }
  }

  void tick() {
    for (int i = 0; i < 10; i++) {
      gold += (*critters[i]).getEarningsRate();
      if (rand() % 10 == 1) {
        (*critters[i]).damage(1 + (rand() % 5));
      }
    }
  }

  Player();
};

Player::Player() {
	gold = 0;
  for (int i = 0; i < 10; i++) {
    inventory[i] = new CritterFood(0, 0);
    critters[i] = new Critter(0, 0);
  }
}

class Shop {
 public:
  int costs[10], quantities[10], levels[10], types[10];
  void show() {
    for (int i = 0; i < 10; i++) {
      if (rand() % 2 == 1) {
        levels[i] = 1 + (rand() % 10);
        quantities[i] = 1 + (rand() % 20);
        costs[i] = levels[i] * quantities[i] - (rand() % quantities[i]);
        if (costs[i] <= 0) {
          costs[i] = 1;
        }
        std::cout << " " << i << ": Level " << levels[i] << " Critter Food (*"
                  << quantities[i] << ")     Cost: " << costs[i] << " gold. "
                  << std::endl;
      } else {
        levels[i] = 1 + (rand() % 10);
        quantities[i] = 10 * (rand() % 20);
        costs[i] = levels[i] * levels[i] * quantities[i] - (rand() % 100);
        if (costs[i] <= 0) {
          costs[i] = 1;
        }
        std::cout << " " << i << ": Critter (" << levels[i]
                  << " gold per tick, has max health of " << quantities[i]
                  << ")     Cost: " << costs[i] << " gold. " << std::endl;
      }
    }
  }
};

int main() {
  Player player;
  delete player.critters[0]; // before setting an inventory slot or otherwise, delete whatever junk was in there before
  player.critters[0] = new Critter(100, 5);
  (*player.critters[0]).damage(10);
  (*player.critters[0]).introduce();
  delete player.inventory[0];
  player.inventory[0] = new CritterFood(5, 2);
  player.displayInventory();
  Critter* critter = player.critters[0];
  while ((*critter).getHealth() < (*critter).maxHealth) {
  	(*critter).feed(player.inventory[0]);	
  }
  (*critter).feed(player.inventory[0]);
  player.displayInventory();
  (*player.critters[0]).introduce();
  Shop shop;
  shop.show();
  return 0;
}
