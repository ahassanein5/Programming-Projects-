//
//  main.cpp
//  projTest
//
//  Created by Amr Hassanein on 5/11/20.
//  Copyright © 2020 Amr Hassanein. All rights reserved.
//

#include <iostream>
#include <iomanip>

int main(int argc, const char * argv[]) {
    // declarations
       using std::cout;
       using std::cin;
       using std::endl;
       using std::setw;
       using std::setprecision;
       using std::fixed;
       using std::showpoint;
       
       double weight = 0.00f;
       int minutes = 0;
       double running = 10;
       double biking = 8;
       double lifting = 3;
       double yoga = 2.5;
       int menu;
       double metByWeight, calories;
       
       bool validate = true;
       
       cout << "-------------------------------------------------------------------------" << endl;
       cout << "|                   Amr Hassanein\'s Fitness Center                      |" << endl;
       cout << "-------------------------------------------------------------------------" << endl;
       cout << "|                          Menu                                         |" << endl;
       cout << "|                                                                       |" << endl;
       cout << "|                     1) Stationary Bike                                |" << endl;
       cout << "|                     2) Treadmill                                      |" << endl;
       cout << "|                     3) Weight Lifting                                 |" << endl;
       cout << "|                     4) Hatha Yoga                                     |" << endl;
       cout << "|                     5) Exit                                           |" << endl;
       cout << "|                                                                       |" << endl;
       cout << "-------------------------------------------------------------------------" << endl;


       
       do
       {
               cout << "Enter the workout that you wish to track, or end to exit: ";
               cin >> menu;
           
               if (menu < 1 || menu >5)
               {
                   cout << "The starting number of this dimesion "
                   << "must be a valid number that is at least 1.\n";
                   cin.clear();
                   cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               }
               else {validate = false;}
       } while (validate);
       
       
       
       cout << "Enter your weight: ";
       cin >> weight;
       cout << "Enter the number of minutes: ";
       cin >> minutes;
       
       
       // set all of the formatting with a statement
       cout << setprecision(2) << fixed << showpoint;
       cout << endl;
       
       // Convert the user weight in pounds to kilograms by dividing by 2.2
       double convert = weight / 2.2;
       // Convert the minutes to hour base
       double time = minutes / 60.0;
       
       
       if (menu == 1)
       {
           // multiply MET value by user weight
           double metByWeight = convert * biking;
           // Multiply the product by the time that the user performed
           // the activity in hours to get the number of calories you burned
           double calories = metByWeight * time;
           cout << setw(68) << "Your total calories for riding the stationary bike was: " << calories << endl;
           cout << endl;
           
           if (calories >= 501)
           {
               cout << setw(68)<< "Vigorous intensity aerobic activity";
           }
           else if (calories >= 201)
           {
               cout << setw(68)<< "Moderate intesity activity";
           }
           else if (calories >= 0)
           {
               cout << setw(68)<< "Light intensity aerobic activity";
           }
           cout << endl << endl;
           

       }
       
       else if (menu == 2)
       {
           // convert again for each activity
           // Treadmill
           
           metByWeight = convert * running;
           calories = metByWeight * time;
           cout << setw(68) << "Your total calories for running the treadmill was: "<< calories << endl;
           cout << endl;
           if (calories >= 501)
           {
               cout << setw(68)<< "Vigorous intensity aerobic activity";
           }
           else if (calories >= 201)
           {
               cout << setw(68)<< "Moderate intesity activity";
           }
           else if (calories >= 0)
           {
               cout << setw(68)<< "Light intensity aerobic activity";
           }
           cout << endl << endl;

       }
       
       else if (menu == 3)
       {
           // Weight lifting
           
           metByWeight = convert * lifting;
           calories = metByWeight * time;
           cout << setw(68) << "Your total calories for weight lifting was: "<< calories << endl;
           cout << endl;
           if (calories >= 501)
           {
               cout << setw(68)<< "Vigorous intensity aerobic activity";
           }
           else if (calories >= 201)
           {
               cout << setw(68)<< "Moderate intesity activity";
           }
           else if (calories >= 0)
           {
               cout << setw(68)<< "Light intensity aerobic activity";
           }
           cout << endl << endl;
       }
       
      else if (menu == 4)
      {
          // Hatha Yoga -  is a branch of yoga that emphasizes physical exercises to master the body
          // along with mind exercises to withdraw it from external objects
          
          metByWeight = convert * yoga;
          calories = metByWeight * time;
          cout << setw(68) << "Your total calories for doing Hatha yoga was: "<< calories << endl;
          cout << endl;
          if (calories >= 501)
          {
              cout << setw(68)<< "Vigorous intensity aerobic activity";
          }
          else if (calories >= 201)
          {
              cout << setw(68)<< "Moderate intesity activity";
          }
          else if (calories >= 0)
          {
              cout << setw(68)<< "Light intensity aerobic activity";
          }
          cout << endl << endl;

      }
       
       return 0;
       
}





