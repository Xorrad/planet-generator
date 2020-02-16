class Planet;

class Creature{
public:
    std::string name;
    bool fur;
    int max_year_old;
    int height; // HEIGHT OF THE CREATURE IN METER
    int weight; // WEIGHT OF THE CREATURE IN KILO
    int leg_number;
    std::string diet;
    Creature(Planet *planet);
};
class Planet{
public:
    std::string name;
    int diameter;
    int temperature;
    bool atmosphere;
    bool oxygen;
    bool gravity;
    std::vector<Creature> creatures;
    Planet();
    void displayPlanet();
    void displayCreature();
    void savePlanet();
};

int random(int minimum, int maximum);
std::string randomName();
std::string randomPlanetName();
bool isVoiel(char l);
