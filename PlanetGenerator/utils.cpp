#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <string>
#include <time.h>
#include <ctime>
#include <cmath>
#include <fstream>
#include "utils.h"

#define CREATURE_TINY_DIAMETER 24000
#define MAX_CREATURE_HEIGHT 20
#define MAX_CREATURE_WEIGHT 20000

using namespace std;

int random(int minimum, int maximum);
string randomName();
string randomPlanetName();
bool isVoiel(char l);
bool isDecimal(float value);

string diet_list[]= {"Carnivore", "Herbivore", "Homnivore"};
int diet_number = 3;
///////////////////////////////////////////////////////
Planet::Planet(){
    name = randomPlanetName();
    diameter = random(1000, 50000);
    temperature = random(-60, 60);
    atmosphere = random(0, 2);
    if(atmosphere)
    {
        int i = random(0, 3);
        if(i == 0)
        {
            oxygen = false;
        }
        else
        {
            oxygen = true;
        }
    }
    else
    {
        int i = random(0, 10);
        if(i == 0)
        {
            oxygen = true;
        }
        else
        {
            oxygen = false;
        }
    }
    gravity = random(0, 5);

    int m = random(0, (diameter/2)*1); //MAX CREATURE ON THE PLANET
    //int m = 20;
    for(int i = 0; i<=m; i++){
        Creature c(this);
        creatures.push_back(c);
    }
}
void Planet::displayPlanet()
{
    cout << "Name: " << name << endl;
    cout << "Diameter: " << diameter << "Km" << endl;
    cout << "Temperature: " << temperature << "°" << endl;
    cout << "Atmosphere: " << (atmosphere ? "Yes" : "No") << endl;
    cout << "Oxygen: " << (oxygen ? "Yes" : "No") << endl;
    cout << "Gravity: " << (gravity != 0 ? "Yes" : "No") << endl;
    cout << "Creature(s): " << creatures.size() << endl;
}
void Planet::displayCreature()
{
    for(int i=0; i<creatures.size(); i++){
        cout << "Name: " << creatures.at(i).name << endl;
        cout << "Fur: " << (creatures.at(i).fur ? "Yes" : "No") << endl;
        cout << "Diet: " << creatures.at(i).diet << endl;
        cout << "Height: " << creatures.at(i).height << " Meter(s)" << endl;
        cout << "Weight: " << creatures.at(i).weight << " Kilo(s)" << endl;
        cout << "Leg: " << creatures.at(i).leg_number << endl << endl;
    }
}

void Planet::savePlanet()
{

     CreateDirectory("Planets" ,NULL);
     string f = "Planets/" + name + ".txt";
     ofstream file(f.c_str());

     file << "The planet " << name << endl;
     file << " Diameter: " << diameter << "Km" << endl;
     file << " Temperature: " << temperature << "°" << endl;
     file << " Atmosphere: " << (atmosphere ? "Yes" : "No") << endl;
     file << " Oxygen: " << (oxygen ? "Yes" : "No") << endl;
     file << " Gravity: " << (gravity != 0 ? "Yes" : "No") << endl;
     file << " Creature(s): " << creatures.size() << endl << endl;

     file << "The Creatures: " << endl << endl;
     for(int i=0; i<creatures.size(); i++){
        file << " Name: " << creatures.at(i).name << endl;
        file << " Fur: " << (creatures.at(i).fur ? "Yes" : "No") << endl;
        file << " Diet: " << creatures.at(i).diet << endl;
        file << " Height: " << creatures.at(i).height << " Meter(s)" << endl;
        file << " Weight: " << creatures.at(i).weight << " Kilo(s)" << endl;
        file << " Leg: " << creatures.at(i).leg_number << endl << endl;
    }

    cout << "The planet has been saved !" << endl;

}
Creature::Creature(Planet *planet)
{
    /* SET THE CREATURE HEIGHT */
    if(planet->diameter < CREATURE_TINY_DIAMETER && planet->gravity != 0)
        { //SMALL GRAVITY
        height = random(1, MAX_CREATURE_HEIGHT/planet->gravity);

        do
        {
            leg_number = random(1, 8);
        }
        while(isDecimal((float)leg_number/2));
    }
    else
    { //BIG GRAVITY
        height = random(1, MAX_CREATURE_HEIGHT);

        do
        {
            leg_number = random(1, 8);
        }
        while(isDecimal((float)leg_number/2));
    }

    /* CHOISE IF THE CREATURE HAVE FUR */
    if(planet->temperature < 0)
    {
        int i = random(1, 20);
        fur = (i!= 1) ? true : false;
    }
    else
    {
        int i = random(1, 20);
        fur = (i!= 1) ? false : true;
    }

    /* SET THE CREATURE WEIGHT */
    if(planet->gravity != 0)
    {
        if(planet->diameter >= CREATURE_TINY_DIAMETER)
        {
            if(height <= 2)
            {
                weight = random(height*20, height*200);
            }
            else
            {
                weight = random(height*500, height*1000);
            }
        }
    }
    else
    {
        if(height <= 2)
        {
            weight = random(height*20, height*100);
        }
        else
        {
            weight = random(height*400, height*700);
        }
    }

    /* SET THE DIET OF TE CREATURE */
    int n = random(0, diet_number);
    diet = diet_list[n];

    name = randomName();
}

int random(int minimum, int maximum)
{
    return rand()%(maximum-minimum)+minimum;
}

string randomName(){

    string name("");
    vector<char> temp;
    char a[] = {'a', 'e', 'i', 'o', 'u', 'y'}; //6
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; //26

    int r = 0;
    int m = random(5, 16); //THE MAX CHARACTER IN THE NAME

    for(int i=0; i<=m; i++)
    {
        if(i==0)
        {
            r = random(0, 25);
            temp.push_back(toupper(alphabet[r]));
        }
        else if(i==m-1)
        {
            r = random(0, 2);
            if(r == 1)
            {
                char l;
                do
                {
                    r = random(0, 25);
                    l = alphabet[r];
                }
                while(isVoiel(l));
                temp.push_back(l);
                temp.push_back('a');
            }
            else
            {
                int i = random(0, 2);
                if(i == 1)
                {
                    temp.push_back('u');
                    temp.push_back('m');
                }
                else
                {
                    temp.push_back('u');
                    temp.push_back('s');
                }
            }
            break;
        }
        else
        {
            if(!isVoiel(temp.at(i-1))) //CHECK IF THE LATEST-LATEST char is Voiel
            {
                r = random(0, 5);
                temp.push_back(a[r]);
            }
            else
            {
                if(temp.size() >= 3)
                {
                    if(isVoiel(temp.at(i-1)) && isVoiel(temp.at(i-2)))
                    {
                        char l;
                        do
                        {
                            r = random(0, 25);
                            l = alphabet[r];
                        }
                        while(isVoiel(l));
                        temp.push_back(l);
                    }
                    else
                    {
                        r = random(0, 25);
                        temp.push_back(alphabet[r]);
                    }
                }
                else
                {
                    r = random(0, 25);
                    temp.push_back(alphabet[r]);
                }
            }
        }
    }

    for(int i=0; i<temp.size(); i++)
    {
        name += temp.at(i);
    }

    return name;
}

string randomPlanetName() {
    string name("");
    vector<char> temp;
    char a[] = {'a', 'e', 'i', 'o', 'u', 'y'}; //6
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; //26

    int r = 0;
    int m = random(5, 8); //THE MAX CHARACTER IN THE NAME

    for(int i=0; i<=m; i++)
    {
        if(i==0)
        {
            r = random(0, 25);
            temp.push_back(toupper(alphabet[r]));
        }
        else if(i==m-1)
        {
            r = random(0, 2);
            if(r == 1)
            {
                char l;
                do
                {
                    r = random(0, 25);
                    l = alphabet[r];
                }
                while(isVoiel(l));
                temp.push_back(l);
                temp.push_back('a');
            }
            else
            {
                int i = random(0, 2);
                if(i == 1)
                {
                    temp.push_back('u');
                    temp.push_back('m');
                }
                else
                {
                    temp.push_back('u');
                    temp.push_back('s');
                }
            }
            break;
        }
        else
        {
            if(!isVoiel(temp.at(i-1))) //CHECK IF THE LATEST-LATEST char is Voiel
            {
                r = random(0, 5);
                temp.push_back(a[r]);
            }
            else
            {
                if(temp.size() >= 3)
                {
                    if(isVoiel(temp.at(i-1)) && isVoiel(temp.at(i-2)))
                    {
                        char l;
                        do
                        {
                            r = random(0, 25);
                            l = alphabet[r];
                        }
                        while(isVoiel(l));
                        temp.push_back(l);
                    }
                    else
                    {
                        r = random(0, 25);
                        temp.push_back(alphabet[r]);
                    }
                }
                else
                {
                    r = random(0, 25);
                    temp.push_back(alphabet[r]);
                }
            }
        }
    }

    for(int i=0; i<temp.size(); i++)
    {
        name += temp.at(i);
    }

    return name;
}
bool isVoiel(char l){

    if(l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u' || l == 'y')
    {
        return true;
    }

    return false;
}

bool isDecimal(float value){
    if (fabsf(roundf(value) - value) <= 0.00001f) {
        return false;
    } else {
        return true;
    }
}
