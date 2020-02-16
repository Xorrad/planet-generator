#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <string>
#include <time.h>
#include <ctime>
#include <cmath>
#include <fstream>
#include "utils.h"

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    Planet p1;
    p1.displayPlanet();
    p1.savePlanet();

    system("PAUSE");

    return 0;
}

