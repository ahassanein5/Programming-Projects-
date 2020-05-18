//
//  main.cpp
//  ProjectPart3
//
//  Created by Amr Hassanein on 5/9/2018.
//  Copyright © 2018 Amr Hassanein. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;


//CONSTANTS
const int HELICOPTER_SIZE = 19;
const int TURBO_PROP_SIZE = 15;
const int MIDSIZE_JET_SIZE = 24;
const int HEAVY_JET_SIZE = 33;
const int NUM_AIRCRAFTS = 4;
const int AIRCRAFT_SIZES[NUM_AIRCRAFTS] = {19, 15, 24, 33};


void mainMenu();
//Precondition: none
//PostCondition: menu is printed to screen
void searchArrays(int *jagged[], const int AIRCRAFT_SIZES[], const int num_aircrafts);
void userChoice(int& transportationType, fstream& theLog, int *jagged[], const int aircraft_size[], const int num_aircrafts, int i,int j,int k,int l);
//Precondition: file is and input/output file and is opened
//Postcondition: transportationType is selected by the user as an int
void flightDestination(string &destination);
//Precondition: empty string is needed, destination
//Postcondtion: a flight path is selected by the user and held by destination
void windspeedInput (short int& windSpeed);
//Precondtion: windSpeed is an int that is empty
//Postcondition: windSpeed is entered by the user and returned
void getTime(int transportationType, string destination, float &time, short int windSpeed);
//Precondition: transportationType is an int chosen by the user, Desination is a string input by the user
//              windSpeed is a short int input by the user to hold the wind speed
//Postcondition: the time it takes to fly to the destination is calculated and placed in time
void hoursAndMinutes(int& minutes, float time, int& hours);
//Precondition: time is the time it takes to fly the path
//Postcondition: the time is split into minutes and hours and placed in their respective variables
void getStatus(int hours, string& flightStatus);
//Precondition: hours is number of hours it takes to fly the path
//Postcondition: a string is returned into flightStatus giving the status length of the flight
void getFlightNumber(int& flightNumber, int count);
//Postcondition: random integer is chosen and returned into flightNumber
void outputToFile (int count, fstream& theLog, int flightNumber, int transportationType, string destination, string flightStatus, int minutes, int hours);
void printLogFile(fstream& theLog);
//Precondition: theLog is a file that hold all flights that were tracked
//Postcondition: theLog is printed to the screen
void secretPassword(fstream& theLog);
void fillArrays(int *jagged[], int flightNumber, int transportationType, int& i, int& j, int& k, int& l);
void printArrays(int *jagged[], int i, int j, int k, int l);






//CONSTANTS
int HELICOPTER = 130,
TURBO_PROP = 250,
MIDSIZE_JET = 400,
HEAVY_JET = 550;
const float CLE_ORD = 273.00f,
ORD_JFK = 641.00f,
DEN_JFK = 1409.00f,
JFK_SFO = 2242.00f,
JFK_MIA = 949.00f,
DFW_CYYZ = 1041.00f;



int main()
{
    //DECLARATIONS
    int transportationType;
    int minutes, flightNumber, count = 0, hours = 0;
    int i = 0, j = 0, k = 0, l = 0;
    short int windSpeed;
    float time = 0;
    string destination = " ", flightStatus = " ";
    char repeat = 'Y';
    fstream theLog;
    theLog.open("airlineLog.txt", ios::in | ios::out | ios::app);
    
    int *jagged[NUM_AIRCRAFTS];
    
    
    jagged[0] = nullptr;
    jagged[1] = nullptr;
    jagged[2] = nullptr;
    jagged[3] = nullptr;
    
    
    jagged[0] = new int[HELICOPTER_SIZE];
    jagged[1] = new int[TURBO_PROP_SIZE];
    jagged[2] = new int[MIDSIZE_JET_SIZE];
    jagged[3] = new int[HEAVY_JET_SIZE];
    
    while(repeat == 'Y' || repeat == 'y')
    {
        mainMenu();
        getFlightNumber(flightNumber, count);
        userChoice(transportationType, theLog, jagged, AIRCRAFT_SIZES, NUM_AIRCRAFTS, i, j, k, l);
        fillArrays(jagged, flightNumber, transportationType, i, j, k, l);
        flightDestination(destination);
        windspeedInput(windSpeed);
        getTime(transportationType, destination, time, windSpeed);
        hoursAndMinutes(minutes, time, hours);
        getStatus(hours, flightStatus);
        outputToFile(count, theLog, flightNumber, transportationType, destination, flightStatus, minutes, hours);
        count++;
        
        
        //OUTPUT
        cout << fixed << setprecision(0);
        cout << "\nYour total flight time is " << hours << " hours and " << minutes << " minutes" << endl;
        cout << "Ent Y or N if you would like to try again...";
        cin >> repeat;
        if(repeat == 'N' || repeat == 'n')
        {
            theLog.close();
            delete [] jagged[0];
            delete [] jagged[1];
            delete [] jagged[2];
            delete [] jagged[3];
        }
        
    }
    
    
    
    
    return 0;
}







void mainMenu() //MAIN MENU
{
    cout << " ------------------------------------------- " << endl;
    cout << "|        Amr\'s Airline Activity system      |" << endl;
    cout << "|-------------------------------------------|" << endl;
    cout << "|               MAIN MENU                   |" << endl;
    cout << "|             1) Helicopter                 |" << endl;
    cout << "|             2) Turbo Prop                 |" << endl;
    cout << "|             3) Midsized Jet               |" << endl;
    cout << "|             4) Heavy Jet                  |" << endl;
    cout << "|             5) Print Transaction Log      |" << endl;
    cout << "|             6) Print Aircraft Usage       |" << endl;
    cout << "|             7) Search for a Flight        |" << endl;
    cout << "|             8) Quit                       |" << endl;
    
    cout << " ------------------------------------------- " << endl;
}

void searchArrays(int *jagged[], const int AIRCRAFT_SIZES[],const int num_aircrafts)
{
    int num;
    cout << "Please enter the flight number youd like to search for... ";
    cin >> num;
    if (num < 0 || num > 99999)
    {
        cout << "the number you have entered is invalid. Goodbye..." << endl;
        exit(0);
    }
    for(int i = 0; i < NUM_AIRCRAFTS; i++)
    {
        for(int j = 0; j < AIRCRAFT_SIZES[i]; j++)
        {
            if (num == jagged[i][j])
            {
                if(i == 0)
                {
                    cout << "This flight is a Helicopter, and it is in slot " << (j + 1) << endl;
                }
                else if(i == 1)
                {
                    cout << "This flight is a Helicopter, and it is in slot " << (j + 1) << endl;
                }
                else if(i == 2)
                {
                    cout << "This flight is a Helicopter, and it is in slot " << (j + 1) << endl;
                }
                else if(i == 3)
                {
                    cout << "This flight is a Helicopter, and it is in slot " << (j + 1) << endl;
                }
            }
        }
    }
}

void userChoice(int& transportationType, fstream& theLog, int *jagged[], const int aircraft_size[], const int num_aircrafts, int i,int j,int k,int l)
{
    bool validate = true;
    do
    {
        cout << "Please enter which type of transportation you would like: ";
        cin >> transportationType;
        if (cin.fail() || transportationType <= 0 || transportationType > 8)
        {
            cout << "Invalid entry, try again....";
            cin.clear();
            cin.ignore();
        }
        else if(transportationType == 5)
        {
            secretPassword(theLog);
            cout << "Goodbye" << endl;
            exit(0);
        }
        else if(transportationType == 6)
        {
            printArrays(jagged, i, j, k, l);
            exit(0);
        }
        else if(transportationType == 7)
        {
            searchArrays(jagged, AIRCRAFT_SIZES, NUM_AIRCRAFTS);
            exit(0);
        }
        else if (transportationType == 8)
        {
            exit(0);
        }
        else
        {
            validate = false;
        }
    }
    while (validate);
}

void flightDestination(string &destination)
{
    //USER INPUT FOR DESTINATION
    bool validate = true;
    do
    {
        cout << "Please enter your start and ending destination (such as CLE-ORD): ";
        cin >> destination;
        if (cin.fail() || (destination != "CLE-ORD" && destination != "ORD-JFK" && destination != "DEN-JFK" && destination != "JFK-SFO" && destination != "JFK-MIA" && destination != "DFW-CYYZ"))
        {
            cout << "Invalid entry, try again....";
            cin.clear();
            cin.ignore();
        }
        else
        {
            validate = false;
        }
    }
    while (validate);
}

void windspeedInput (short int& windSpeed)
{
    //USER INPUT FOR WINDSPEED
    bool validate = true;
    do
    {
        cout << "Enter your wind speed (negative for tail wind): ";
        cin >> windSpeed;
        if (cin.fail() || windSpeed < -100 || windSpeed > 100)
        {
            cout << "Invalid entry, try again....";
            cin.clear();
            cin.ignore();
        }
        else
        {
            validate = false;
        }
    }
    while (validate);
}

void getTime(int transportationType, string destination, float &time, short int windSpeed)
{
    //TIME CALCULATION DEPENDING ON USER CHOICE
    switch (transportationType)
    {
        case 1:
            if (destination == "CLE-ORD")
            {
                time = (CLE_ORD / (HELICOPTER - windSpeed));
            }
            else if (destination == "ORD-JFK")
            {
                time = (ORD_JFK / (HELICOPTER - windSpeed));
            }
            else if (destination == "DEN-JFK")
            {
                time = (DEN_JFK / (HELICOPTER - windSpeed));
            }
            else if (destination == "JFK-SFO")
            {
                time = (JFK_SFO / (HELICOPTER - windSpeed));
            }
            else if (destination == "JFK-MIA")
            {
                time = (JFK_MIA / (HELICOPTER - windSpeed));
            }
            else
            {
                time = (DFW_CYYZ / (HELICOPTER - windSpeed));
            }
            break;
        case 2:
            if (destination == "CLE-ORD")
            {
                time = (CLE_ORD / (TURBO_PROP - windSpeed));
            }
            else if (destination == "ORD-JFK")
            {
                time = (ORD_JFK / (TURBO_PROP - windSpeed));
            }
            else if (destination == "DEN-JFK")
            {
                time = (DEN_JFK / (TURBO_PROP - windSpeed));
            }
            else if (destination == "JFK-SFO")
            {
                time = (JFK_SFO / (TURBO_PROP - windSpeed));
            }
            else if (destination == "JFK-MIA")
            {
                time = (JFK_MIA / (TURBO_PROP - windSpeed));
            }
            else
            {
                time = (DFW_CYYZ / (TURBO_PROP - windSpeed));
            }
            break;
        case 3:
            if (destination == "CLE-ORD")
            {
                time = (CLE_ORD / (MIDSIZE_JET - windSpeed));
            }
            else if (destination == "ORD-JFK")
            {
                time = (ORD_JFK / (MIDSIZE_JET - windSpeed));
            }
            else if (destination == "DEN-JFK")
            {
                time = (DEN_JFK / (MIDSIZE_JET - windSpeed));
            }
            else if (destination == "JFK-SFO")
            {
                time = (JFK_SFO / (MIDSIZE_JET - windSpeed));
            }
            else if (destination == "JFK-MIA")
            {
                time = (JFK_MIA / (MIDSIZE_JET - windSpeed));
            }
            else
            {
                time = (DFW_CYYZ / (MIDSIZE_JET - windSpeed));
            }
            break;
        case 4:
            if (destination == "CLE-ORD")
            {
                time = (CLE_ORD / (HEAVY_JET - windSpeed));
            }
            else if (destination == "ORD-JFK")
            {
                time = (ORD_JFK / (HEAVY_JET - windSpeed));
            }
            else if (destination == "DEN-JFK")
            {
                time = (DEN_JFK / (HEAVY_JET - windSpeed));
            }
            else if (destination == "JFK-SFO")
            {
                time = (JFK_SFO / (HEAVY_JET - windSpeed));
            }
            else if (destination == "JFK-MIA")
            {
                time = (JFK_MIA / (HEAVY_JET - windSpeed));
            }
            else
            {
                time = (DFW_CYYZ / (HEAVY_JET - windSpeed));
            }
            break;
            
    }
    
}

void hoursAndMinutes(int& minutes, float time, int& hours)
{
    minutes = (time * 60);
    minutes %= 60;
    hours = time;
}

void getStatus(int hours, string& flightStatus)
{
    //FLIGHT STATUS
    if (hours < 3)
    {
        flightStatus = "Short-haul";
    }
    else if (hours < 6)
    {
        flightStatus = "Medium-haul";
    }
    else if (hours < 12)
    {
        flightStatus = "Long-haul";
    }
    else
    {
        flightStatus = "Ultra Long-haul";
    }
}

void getFlightNumber(int& flightNumber, int count)
{
    srand(time(0));
    flightNumber = 1 + rand() % 99999;
    cout << "Flight Number: " << setfill ('0') << setw(5) << flightNumber << endl;
    cout << "Today\'s hits: " << setfill ('0') << setw(5) << count << endl;
}

void outputToFile (int count, fstream& theLog, int flightNumber, int transportationType, string destination, string flightStatus, int minutes, int hours)
{
    if (count == 0)
    {
        theLog << left
        << setw(10) << "FLIGHT#"
        << setw(10) << "Type"
        << setw(10) << "MINUTES"
        << setw(10) << "ROUTE"
        << setw(15) << "FLIGHT TIME" << " " << " "
        << setw(20) << "STATUS"
        << setw(25) << "TIME IN" << endl;
    }
    time_t now = time(0);
    // convert now to c-string form
    char* timeOf = ctime(&now);
    // we want a way to limit the size to be just 20 in length
    timeOf[20] = '\0'; //
    
    theLog << left
    << setw(5) <<  setfill ('0') << flightNumber << setfill(' ')
    << setw(8) << right << transportationType
    << setw(10) << minutes
    << setw(13) << destination
    << setw(8) << hours << setw(1) << ":" << setw(2) << setfill ('0') << minutes << setfill(' ')
    << setw(18)  << flightStatus
    << setw(25) << timeOf << endl;
}

void printLogFile(fstream& theLog)
{
    // reset everything and go to the beginning of the file
    theLog.clear();
    theLog.seekg(0, std::ios::beg);
    // start the streaming >>
    string lines;
    while(!(getline(theLog, lines).eof()))
    {
        cout << lines << endl;
    }
    
    // reset everything and go to the end of the file
    theLog.clear();
    theLog.seekg(0, std::ios::end);
    
    
}

void secretPassword(fstream& theLog)
{
    string password;
    cout << "You wanna see the file? Well you just have to enter the password...";
    cin >> password;
    if (password == "Not-telling")
    {
        printLogFile(theLog);
    }
    else
    {
        cout << "WRONG--program failure. Goodbye";
        exit(0);
        
    }
}


void fillArrays(int *jagged[], int flightNumber, int transportationType, int& i, int& j, int& k, int& l)
{
    
    if(transportationType == 1)
    {
        jagged[0][i] = flightNumber;
        i++;
        if(i == (HELICOPTER_SIZE - 1))
            i = 0;
    }
    else if(transportationType == 2)
    {
        jagged[1][j] = flightNumber;
        j++;
        if(j == (TURBO_PROP_SIZE - 1))
            j = 0;
    }
    else if(transportationType == 3)
    {
        jagged[2][k] = flightNumber;
        k++;
        if(k == (MIDSIZE_JET_SIZE - 1))
            k = 0;
    }
    else if(transportationType == 4)
    {
        jagged[3][l] = flightNumber;
        l++;
        if(l == (HEAVY_JET_SIZE - 1))
            l = 0;
    }
    
}

void printArrays(int *jagged[], int i, int j, int k, int l)
{
    
    cout << "Helicopters in use/total: " << i  << "/" << HELICOPTER_SIZE << endl;
    cout << "Turbo Props in use/total: " << j << "/" << TURBO_PROP_SIZE << endl;;
    cout << "Medium Jets in use/total: " << k << "/" << MIDSIZE_JET_SIZE << endl;
    cout << "Heavy Jets in use/total: " << l << "/" << HEAVY_JET_SIZE << endl;
    
}





