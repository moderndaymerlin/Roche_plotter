/* New.cpp - A program designed to produce light curves for either a spherical planet or one which has filled its Roche Lobe 

Created by John Robert Burton, last modified 03/12/2017 */

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <string>

#define PI 3.141592658979323846264338327950288

/* Define which constants are used throughout the program */

const float Ms = 1.98892e30;
const float Mj = 1.8987e27;
const float G = 6.67e-11;
const float Rs = 695500000;
const float Rj = 71492000;
const float AU = 1.49598e11;

/* This defines the later processes which enable the menu system to work */

int option_1();
int option_1a();
int option_1b();
int option_1c();
int option_1d();
int option_1e();
int option_2();
int option_3();
int option_4();
int option_5();
int option_6();

/* These values and arrays are defined outside the main and sub-processes as they are used throughtout all sub and main processes */

char cont,sw;

double check,q, M1,M2,P,inc,r,power1,power2,lnterm,RL,period,om,a3,a,mu,term1,term2,term3,term1a,term2a,m1,m2,xm1,xm2,newC1,C1,C2,C3,C4,n,t2,newphi,newphiadj,theta,X,Y,distance,distance2,distance3,D23,A1,inc2,theta2,con1,con2,r2,r3,r2b,r3b,d23,A,Ex,Ey,Ez,E,px1,py1,pz1,px2,py2,pz2,px3,py3,pz3,xi,yi,zi,Xi,Yi,XP1,YP1,XP2,YP2,XP3,YP3,Vi,V1,V2,V3,EE,E1,E2,E3,angi,ang1,ang2,ang3,Dist,Dist1,Dist2,Dist3,Dist4,Ar1,Ar2,Ar3,St,Ar,Sq,Dista,C,DIG,th,th2,Ex2,Ey2,Ez2,Ei,trap,L1;

/* The arrays defined here are made large enough in order to ensure that all the values are included in either the summation of the values or plotting values */

double phi [300];
double phired [300];
double x1 [300];
double xa1 [300];
double grad [300];
double x2 [100];
double y2 [100];
double ya2 [100];
double xa2 [100];
double x3 [100];
double y3 [100];
double z3 [100];
double ya3 [100];
double xa3 [100];
double za3 [100];
double tn [100];
double rn [100];
double rnb [100];
double dn [100];
double dn2 [100];
double Area [5000];
double x12 [300];
double xa12 [300];  
double phi12 [300];
double phired12 [300];
double grad2 [300];

using namespace std;

/* The main process is the menu system of the program. By asking the user to input a particular value, the menu system will run a subroutine corresponding to the input value. The process can be used indefinitely, so many plots, models and light curves can be generated for different input parameters. 

   John Burton, 02/12/2009 */

int main ()
{

 /* like_to_continue is used to ask if the user wishes to continue running the program, or to terminate after a certain process
process_number allows the user to select a specific process to run */

  char like_to_continue,quit,ch;
 float process_number;
 do {

 /* The following are a list of options for the user to select, depending on the process they wish to run */

 cout << "Please select an option by entering a number from 1 to 6, Note that PARS must be set FIRST; " << endl;
 cout << "1. PARS - Allows the user to enter the parameters of the system" << endl;
 cout << "2. POT - Outputs the 1-dimensional potential of the system" << endl;
 cout << "3. POT2D - Outputs the 2-dimensional potential of the system" << endl;
 cout << "4. GRID - Plots a tiled surface on the planet" << endl;
 cout << "5. LIGHT - Allows the user to plot a light curve of this particular grid" << endl;
 cout << "6. PARCH - Allows the user to view and change individual parameters after running the program once" << endl;
 cout << "7. QUIT - Terminates the program" << endl;

 cout << "--> ";

 /* This loop only allows numeric input to be made, no letters, symbols etc */
 do{
  while (!(cin >> process_number)){
   cin.clear();
   if (cin.get() != '\n'){
     cout << "Not an integer, please try again." << endl;
   }
    while (cin.get() !='\n'){}
 cout << "Please select an option by entering a number from 1 to 6, Note that PARS must be set FIRST; " << endl;
 cout << "1. PARS - Allows the user to enter the parameters of the system" << endl;
 cout << "2. POT - Outputs the 1-dimensional potential of the system" << endl;
 cout << "3. POT2D - Outputs the 2-dimensional potential of the system" << endl;
 cout << "4. GRID - Plots a tiled surface on the planet" << endl;
 cout << "5. LIGHT - Allows the user to plot a light curve of this particular grid" << endl;
 cout << "6. PARCH - Allows the user to view and change individual parameters after running the program once" << endl;
 cout << "7. QUIT - Terminates the program" << endl;

 cout << "--> ";
  }
  if (process_number < 1){
   cin.clear();
    while (cin.get() !='\n'){}
  }
  check = (process_number-floor(process_number));
   if (check>0){
    cout << "The value you entered was not an integer, please try again." << endl;
   }
  }while(check>0);

 if (process_number == 1){
  option_1();
  trap = 10;
 }
 else if (process_number == 2 && trap == 10){
  option_2();
 }
 else if (process_number == 3 && trap == 10){
  option_3();
 }
 else if (process_number == 4 && trap == 10){
  option_4();
 }
 else if (process_number == 5 && trap == 10){
  option_5();
 }
 else if (process_number == 6 && trap == 10){
  option_6();
 }
 else if(process_number == 7){
  cout << "Are you sure you would like to quit (y/n)?" << endl;
  cin >> quit;
   if (quit == 'y' || quit == 'Y'){
    cout << "Thank you for using this program, have a pleasant day." << endl;
    return 0;
   }
  }
  if (process_number == 1 || process_number == 2 || process_number == 3 || process_number == 4 || process_number == 5 || process_number == 6 || quit == 'n' || quit == 'N'){
	like_to_continue == 'y';
  }
  else {
   /* This is incase the user enters a number outside of the range (1-6) */
   cout << "Unknown process!" << endl;
   like_to_continue = 'y';
  }
 }while (process_number == 1 || process_number == 2 || process_number == 3 || process_number == 4 || process_number == 5 || process_number == 6 || process_number == 7 || like_to_continue == 'y' || like_to_continue == 'Y' || like_to_continue != 'n' || like_to_continue != 'N');

}

using namespace std;

/* PARS - This subroutine allows the user to input the parameters of the system ,including the orbital inclination, period, radius of planet and mass of the planet and star

   02/12/2009, John Burton */

int option_1()
{
 char like_to_continue;

 /* check1 is used in order to enure that the user cannot enter a non-integer such as 1.5 */

 float selection,check1;

 /* The parameters to be used throughout the rest of the processes are defined by the user in this step or selected from a list of options */

 do {
  cout << "Please select an option from the list below:" << endl;
  cout << "1. WASP-12 parameters." << endl;
  cout << "2. WASP-18 parameters." << endl;
  cout << "3. CoRoT-5 parameters." << endl;
  cout << "4. XO-4 parameters." << endl;
  cout << "5. HAT-P-9 parameters." << endl;
  cout << "6. Custom parameters." << endl;

  do{
   like_to_continue = 'n';
    while (!(cin >> selection)){
     cin.clear();
      while (cin.get() !='\n'){}
      cout << "Please select an option from the list below:" << endl;
  cout << "1. WASP-12 parameters." << endl;
  cout << "2. WASP-18 parameters." << endl;
  cout << "3. CoRoT-5 parameters." << endl;
  cout << "4. XO-4 parameters." << endl;
  cout << "5. HAT-P-9 parameters." << endl;
  cout << "6. Custom parameters." << endl;
    }
    check1 = (selection-floor(selection));
    if (check1>0){
     cout << "The value you entered was not an integer, please try again." << endl;
    }
   } while(check1>0);

   if (selection==1){
    option_1a();
   }
   else if (selection==2){
    option_1b();
   } 
   else if (selection==3){
    option_1c();
   }
   else if (selection==4){
    option_1d();
   }
   else if (selection==5){
    option_1e();
   }
   else if (selection==6){
    cout << "Please enter the system parameters: " << endl;

   do {
    cout << "Mass of the Star in Solar masses:" << endl;
     while (!(cin >> M1)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Mass of the Star in Solar masses:" << endl;
     }
     if (M1<0.0000001 || M1>1000){
      cout << "Unacceptable value entered, please try again.\n";
     }
    } while (M1<0.0000001 || M1>1000);

   do {
    cout << "Mass of the planet in Jupiter masses: " << endl;
     while (!(cin >> M2)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Mass of the planet in Jupiter masses: " << endl;
     }
     if (M2<0.00000001 || M2>10000){
      cout << "Unacceptable value entered, please try again" << endl;
     }
    } while (M2<0.00000001 || M2>10000);

   do {
    cout << "Period of the planet in days: " << endl;
     while (!(cin >> P)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Period of the planet in days: " << endl;
     }
      if (P<0.00000001 || P>100000){
       cout << "Unacceptable value entered, please try again" << endl;
      }
     } while (P<0.000001 || P>100000);

   do {
    cout << "Orbital inclination of the system in degrees: " << endl;
     while (!(cin >> inc)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Orbital inclination of the system in degrees: " << endl;
     }
     if (inc<0){
      cout << "Try Again, the value you entered was outside the acceptable range." << endl;
      }
    } while (inc<0 || inc>360);

   do {
    cout << "Radius of the planet in Jupiter radii:" << endl;
     while (!(cin >> r)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Radius of the planet in Jupiter radii:" << endl;
     }
    if (r<0.000001 || r>10000){
     cout << "Try Again, the value you entered was not acceptable (less than or equal to zero)." << endl;
    }
   } while (r<0.000001 || r>10000);

   do {
   cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    while (!(cin >> n)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
     }
   } while (n < 20 || n > 40);

   do {
    cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    while (!(cin >> t2)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    }
   } while (t2 < 20 || t2 > 40);

  /* The following terms convert the input parameters into a more 'useable' set of values used in following processes */
 
  /* The q value is the ratio of mass one (the star) to mass two (the planet) */
  
   q = (M1*Ms)/(M2*Mj);
   power1 = pow (q, 2.0/3.0);
   power2 = pow (q, 1.0/3.0);
   lnterm = log(1.0+power2);
   RL = (0.49*power1)/((0.6*power1)+lnterm);
   period = (P*24.0*60.0*60.0)/(2*PI);
   om=(2.0*PI)/(P*24.0*60.0*60.0);
   a3 = ((pow(period,2.0))*(G*((M1*Ms)+(M2*Mj))));
   a = pow(a3,1.0/3.0);
   mu = (M2*Mj)/(((M1*Ms)+(M2*Mj)));
   C2 = G*(M1*Ms);
   C3 = G*(M2*Mj);
   C4 = (0.5*(pow(om,2.0)));
   inc2 = (inc*0.0174532925);
   theta2 = (theta*0.0174532925);
   sw = 'f';
  }

  else {
      /* This is incase the user enters a number outside of the range (1-6) */
   cout << "Unknown process!" << endl;
   like_to_continue = 'y';
  }
 } while (like_to_continue=='y');
}

  /* The information has been obtained from http://exoplanet.eu/catalog-all.php. Candidates were selected based on what parameters were avialable, those being mass of the star, mass of the planet, period, radius and inclination. A range of planet masses were selected both in order to demonstate the code and show the user some typical parameters for extra-solar-planets */

/* The phase angle has been set to 90 degrees for the preset parameters. This makes no difference to the structure of the grid, or method in which tiles are put on the surface of the planet */

/* WASP-12. Below is the list of parameters for ESP WASP-12. These parameters are defined so the user can easily access the planet parameters.

   02/12/2009 John Burton */

int option_1a(){

 M1 = 1.35;
 cout << "Mass of the star = " << M1 << " Solar masses" << endl;
 M2 = 1.41;
 cout << "Mass of the planet = " << M2 << " Jupiter masses" << endl;
 P = 1.09;
 cout << "Period of the planet = " << P << " days" << endl;
 r = 1.79;
 cout << "Radius of the planet = " << r << " Jupiter radii" << endl;
 inc = 83.1;
 cout << "Inclination of the planet = " << inc << " degrees" << endl;
 theta = 90.0;

  do {
   cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    while (!(cin >> n)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    }
  } while (n < 20 || n > 40);

  do {
   cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    while (!(cin >> t2)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    }
  } while (t2 < 20 || t2 > 40);

  sw = 'a';
 q = (M1*Ms)/(M2*Mj);
 power1 = pow (q, 2.0/3.0);
 power2 = pow (q, 1.0/3.0);
 lnterm = log(1.0+power2);
 RL = (0.49*power1)/((0.6*power1)+lnterm);
 period = (P*24.0*60.0*60.0)/(2*PI);
 om=(2.0*PI)/(P*24.0*60.0*60.0);
 a3 = ((pow(period,2.0))*(G*((M1*Ms)+(M2*Mj))));
 a = pow(a3,1.0/3.0);
 mu = (M2*Mj)/(((M1*Ms)+(M2*Mj)));
 C2 = G*(M1*Ms);
 C3 = G*(M2*Mj);
 C4 = (0.5*(pow(om,2.0)));
 inc2 = (inc*0.0174532925);
 theta2 = (theta*0.0174532925);
}

/* WASP-18. Below is the list of parameters for ESP WASP-18. These parameters are defined so the user can easily access the planet parameters.

   02/12/2009 John Burton */

int option_1b(){
 M1 = 1.281;
 cout << "Mass of the star = " << M1 << " Solar masses" << endl;
 M2 = 10.43;
 cout << "Mass of the planet = " << M2 << " Jupiter masses"  << endl;
 P = 0.94;
 cout << "Period of the planet = " << P << " days"  << endl;
 r = 1.165;
 cout << "Radius of the planet = " << r << " Jupiter radii" <<endl;
 inc = 96.0;
 cout << "Inclination of the planet = " << inc << " degrees" << endl;
 theta = 90.0;

  do {
   cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    while (!(cin >> n)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    }
  } while (n < 20 || n > 40);
 
  do {
   cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    while (!(cin >> t2)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    }
  } while (t2 < 20 || t2 > 40);

  sw = 'b';
 q = (M1*Ms)/(M2*Mj);
 power1 = pow (q, 2.0/3.0);
 power2 = pow (q, 1.0/3.0);
 lnterm = log(1.0+power2);
 RL = (0.49*power1)/((0.6*power1)+lnterm);
 period = (P*24.0*60.0*60.0)/(2*PI);
 om=(2.0*PI)/(P*24.0*60.0*60.0);
 a3 = ((pow(period,2.0))*(G*((M1*Ms)+(M2*Mj))));
 a = pow(a3,1.0/3.0);
 mu = (M2*Mj)/(((M1*Ms)+(M2*Mj)));
 C2 = G*(M1*Ms);
 C3 = G*(M2*Mj);
 C4 = (0.5*(pow(om,2.0)));
 inc2 = (inc*0.0174532925);
 theta2 = (theta*0.0174532925);
}

/* CoRoT-5. Below is the list of parameters for ESP CoRoT-5. These parameters are defined so the user can easily access the planet parameters.

   02/12/2009 John Burton */

int option_1c(){
 M1 = 1.0;
 cout << "Mass of the star = " << M1 << " Solar masses" << endl;
 M2 = 0.467;
 cout << "Mass of the planet = " << M2 << " Jupiter masses" << endl;
 P = 4.0378962;
 cout << "Period of the planet = " << P << " days" << endl;
 r = 1.388;
 cout << "Radius of the planet = " << r << " Jupiter radii" << endl;
 inc = 85.83;
 cout << "Inclination of the planet = " << inc << " degrees" << endl;
 theta = 90.0;

  do {
   cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    while (!(cin >> n)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    }
  } while (n < 20 || n > 40);
 
  do {
   cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    while (!(cin >> t2)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    }
  } while (t2 < 20 || t2 > 40);
 
  sw = 'c';
 q = (M1*Ms)/(M2*Mj);
 power1 = pow (q, 2.0/3.0);
 power2 = pow (q, 1.0/3.0);
 lnterm = log(1.0+power2);
 RL = (0.49*power1)/((0.6*power1)+lnterm);
 period = (P*24.0*60.0*60.0)/(2*PI);
 om=(2.0*PI)/(P*24.0*60.0*60.0);
 a3 = ((pow(period,2.0))*(G*((M1*Ms)+(M2*Mj))));
 a = pow(a3,1.0/3.0);
 mu = (M2*Mj)/(((M1*Ms)+(M2*Mj)));
 C2 = G*(M1*Ms);
 C3 = G*(M2*Mj);
 C4 = (0.5*(pow(om,2.0)));
 inc2 = (inc*0.0174532925);
 theta2 = (theta*0.0174532925);
}

/* XO-4. Below is the list of parameters for ESP XO-4. These parameters are defined so the user can easily access the planet parameters.

   02/12/2009 John Burton */

int option_1d(){
 M1 = 1.32;
 cout << "Mass of the star = " << M1 << " Solar masses" << endl;
 M2 = 1.72;
 cout << "Mass of the planet = " << M2 << " Jupiter masses" << endl;
 P = 4.12502;
 cout << "Period of the planet = " << P << " days" << endl;
 r = 1.34;
 cout << "Radius of the planet = " << r << " Jupiter radii" << endl;
 inc = 88.7;
 cout << "Inclination of the planet = " << inc << " degrees" << endl;
 theta = 90.0;
 
  do {
   cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    while (!(cin >> n)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    }
  } while (n < 20 || n > 40);
 
  do {
   cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    while (!(cin >> t2)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    }
  } while (t2 < 20 || t2 > 40);
 
  sw = 'd';
 q = (M1*Ms)/(M2*Mj);
 power1 = pow (q, 2.0/3.0);
 power2 = pow (q, 1.0/3.0);
 lnterm = log(1.0+power2);
 RL = (0.49*power1)/((0.6*power1)+lnterm);
 period = (P*24.0*60.0*60.0)/(2*PI);
 om=(2.0*PI)/(P*24.0*60.0*60.0);
 a3 = ((pow(period,2.0))*(G*((M1*Ms)+(M2*Mj))));
 a = pow(a3,1.0/3.0);
 mu = (M2*Mj)/(((M1*Ms)+(M2*Mj)));
 C2 = G*(M1*Ms);
 C3 = G*(M2*Mj);
 C4 = (0.5*(pow(om,2.0)));
 inc2 = (inc*0.0174532925);
 theta2 = (theta*0.0174532925);
}

/* HAT-P-9. Below is the list of parameters for ESP HAT-P-9. These parameters are defined so the user can easily access the planet parameters.

   02/12/2009 John Burton */

int option_1e(){
 M1 = 1.28;
 cout << "Mass of the star = " << M1 << " Solar masses" << endl;
 M2 = 0.78;
 cout << "Mass of the planet = " << M2 << " Jupiter masses" << endl;
 P = 3.92289;
 cout << "Period of the planet = " << P << " days" << endl;
 r = 1.4;
 cout << "Radius of the planet = " << r << " Jupiter radii" << endl;
 inc = 86.5;
 cout << "Inclination of the planet = " << inc << " degrees" << endl;
 theta = 90.0;
 
  do {
   cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    while (!(cin >> n)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of slices to be modelled, greater than 30 and less than 40:" << endl;
    }
  } while (n < 20 || n > 40);
 
  do {
   cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    while (!(cin >> t2)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    }
  } while (t2 < 20 || t2 > 40);
 
  sw = 'e';
 q = (M1*Ms)/(M2*Mj);
 power1 = pow (q, 2.0/3.0);
 power2 = pow (q, 1.0/3.0);
 lnterm = log(1.0+power2); 
 RL = (0.49*power1)/((0.6*power1)+lnterm);
 period = (P*24.0*60.0*60.0)/(2*PI);
 om=(2.0*PI)/(P*24.0*60.0*60.0);
 a3 = ((pow(period,2.0))*(G*((M1*Ms)+(M2*Mj))));
 a = pow(a3,1.0/3.0);
 mu = (M2*Mj)/(((M1*Ms)+(M2*Mj)));
 C2 = G*(M1*Ms);
 C3 = G*(M2*Mj);
 C4 = (0.5*(pow(om,2.0)));
 inc2 = (inc*0.0174532925);
 theta2 = (theta*0.0174532925);
}

/* POT - This subroutine uses the parameters inputted in the above subroutine to generate a one-dimensional data set for the potential of the system.

   02/12/2009, John Burton */

using namespace std;
int option_2()
{
 /* This loop calculates the  potential in one dimension, setting both the y and z co-ordinates to zero */
 int i;
 float f = -1.0;
 ofstream myfile;
 float g;
  int j;
 myfile.open("potential.dat");
  for (i=0;i<300;i++){
   x1[i]=(f+0.01);
   f = f+0.01;
   xa1[i]=x1[i]*a;
   term1 = pow(xa1[i],2.0);
   term2 = pow((xa1[i]-a),2.0);
   term3 = pow((xa1[i]-(mu*a)),2.0);
   term1a = sqrt(term1);
   term2a = sqrt(term2);

   /* The potential calculated with x values from the array */

   phi[i] = -((G*(M1*Ms))/(term1a))-((G*(M2*Mj))/(term2a))-(0.5*pow(om,2.0))*term3;
   phired [i]= (phi[i]/1e11); /* This reduces the phi value to units of one */
    if (phired[i] < -4.0){
     phired[i] = -4.0;
    }

   /* Calculate the point where the gradient goes from positive to negative. */

   grad[i] = phired[i]-phired[i-1];
    if (grad[i-1]>0){
     if (grad[i]<0){
      if (x1[i]>0.5){
       if (x1[i]<1.0){
	m1 = phired[i-1]; 
	m2 = phired[i];
	xm1 = x1[i-1];
	xm2 = x1[i];
g = x1[i-2];
/* In order to find the value of L1 to a greater accuracy, the process is repeated from the lower value of the potential (m1) in much smaller increments of x. */
 for (j=0;j<200;j++){
    x12[j]=(g+0.0001);
    g = g+0.0001;
    xa12[j]=x12[j]*a;
    term1 = pow(xa12[j],2.0);
    term2 = pow((xa12[j]-a),2.0);
    term3 = pow((xa12[j]-(mu*a)),2.0);
    term1a = sqrt(term1);
    term2a = sqrt(term2);

    /* The potential calculated with x values from the array */

      phi12[j] = -((G*(M1*Ms))/(term1a))-((G*(M2*Mj))/(term2a))-(0.5*pow(om,2.0))*term3;

      phired12[j]= (phi12[j]/1e11); /* This reduces the phi value to units of one */
  if (phired12[j] < -4.0){
    phired12[j] = -4.0;
  }

  /* Calculate the point where the gradient goes from positive to negative */
    grad2[j] = phired12[j]-phired12[j-1];
  if (grad2[j-1]>0){
  if (grad2[j]<0){
    if (x12[j]>0.5){
      if (x12[j]<1.0){
	L1 = phired12[j];
	cout << "Seperation distance a = " << (a/AU) << " AU." << endl;
	cout << setprecision (6) << "The value of the potential at the L1 point is " << L1 << " to an accuracy of " << (0.0001*(a/AU)) << " AU." << endl;
      }  
    }
  } 
  } 
 }
       }
      }
     } 
    } 
   myfile << x1[i] << " " << phired[i] << " " << endl;
  }

  myfile.close();

  /* This process opens GNUplot using popen (pipe open) which allows for commands to be used in GNUplot without the need to read out to a file and then plot the data seperately */

  FILE *fp = popen("gnuplot","w");
   if (fp){
     if (sw == 'a'){
    fprintf(fp,"set terminal aqua enhanced title 'One Dimensional Potential for WASP-12'\n");
     }
     else if (sw == 'b'){
    fprintf(fp,"set terminal aqua enhanced title 'One Dimensional Potential for WASP-18'\n");
     }
     else if (sw == 'c'){
    fprintf(fp,"set terminal aqua enhanced title 'One Dimensional Potential for CoRoT-5'\n");
     }
     else if (sw == 'd'){
    fprintf(fp,"set terminal aqua enhanced title 'One Dimensional Potential for XO-4'\n");
     }
     else if (sw == 'e'){
    fprintf(fp,"set terminal aqua enhanced title 'One Dimensional Potential for HAT-P-9'\n");
     }
     else if (sw == 'f'){
    fprintf(fp,"set terminal aqua enhanced title 'One Dimensional Potential for Custom Parameters'\n");
     }
    fprintf(fp,"set xlabel 'x[a]'\n");
    fprintf(fp,"set ylabel 'F' font 'Symbol,16'\n");
    fprintf(fp,"unset key\n");
    fprintf(fp,"set title 'One-dimensional potential'\n"); 
    fprintf(fp,"plot 'potential.dat' w lines lt 9 \n");
    fflush(fp);
    fprintf(fp,"exit \n");
    pclose(fp);
   }
  cout << "The potential for the system has been outputted to file 'potential.dat'" << endl;
}

/* POT2D - This subroutine uses the parameters inputted in the above subroutine to generate a two-dimensional data set for the potential of the system.

   02/12/2009, John Burton */

using namespace std;
int option_3()
{

 /* This loop generates a three-dimensional plot, showing the gravitational potential (Phi) in two-dimensions */

 int j,s;
 float d = -2.0;
 double xsq,xsq2,xsq3;
 ofstream myfile;
 myfile.open ("potential2.dat");

  for (j=0;j<100;j++){
   x2[j]=(d+0.05);
   d = d+0.05;
    if (0<x2[j]<-0.01){
     x2[j] = 0;
    }
   xa2[j] = x2[j]*a;

   xsq = pow(xa2[j],2.0);
   xsq2 = pow((xa2[j]-a),2.0);
   xsq3 = pow((xa2[j]-mu*a),2.0);

   float w = -2.5;
    for (s=0;s<100;s++){
     y2[s]=(w+0.05);
     w = w+0.05;

     ya2[s] = y2[s]*a;

     C1 = -(C2/(sqrt(xsq+pow(ya2[s],2.0))))-(C3/sqrt(xsq2+pow(ya2[s],2.0)))-C4*(xsq3+pow(ya2[s],2.0));

     newC1 = C1/1e11;

     if (newC1<-6){
      newC1 = -6;
     }

     myfile << x2[j] << " " << y2[s] << " " << newC1 << endl;
    }
   myfile << endl;
  } 
 myfile.close();

 /* This process opens GNUplot using popen (pipe open) which allows for commands to be used in GNUplot without the need to read out to a file and then plot the data seperately */

 FILE *fp = popen("gnuplot","w");
  if (fp){
     if (sw == 'a'){
    fprintf(fp,"set terminal aqua enhanced title 'Two Dimensional Potential for WASP-12'\n");
     }
     else if (sw == 'b'){
    fprintf(fp,"set terminal aqua enhanced title 'Two Dimensional Potential for WASP-18'\n");
     }
     else if (sw == 'c'){
    fprintf(fp,"set terminal aqua enhanced title 'Two Dimensional Potential for CoRoT-5'\n");
     }
     else if (sw == 'd'){
    fprintf(fp,"set terminal aqua enhanced title 'Two Dimensional Potential for XO-4'\n");
     }
     else if (sw == 'e'){
    fprintf(fp,"set terminal aqua enhanced title 'Two Dimensional Potential for HAT-P-9'\n");
     }
     else if (sw == 'f'){
    fprintf(fp,"set terminal aqua enhanced title 'Two Dimensional Potential for Custom Parameters'\n");
     }
   fprintf(fp,"set xlabel 'x[a]'\n");
   fprintf(fp,"set ylabel 'y[a]'\n");
   fprintf(fp,"set zlabel 'F' font 'Symbol,16'\n");
   fprintf(fp,"unset key\n");
   fprintf(fp,"set title 'Two-dimensional potential'\n"); 
   fprintf(fp,"set contour base\n");
   fprintf(fp,"set cntrparam levels discrete -1.3,-1.5,-2.5,-3.5\n");
   fprintf(fp,"splot 'potential2.dat' w lines\n");
   fflush(fp);
   fprintf(fp,"exit \n");
   pclose(fp);
  }

 cout << "The potential for the system has been outputted to file 'potential2.dat'" << endl;
}

/* GRID - This subroutine allows the user to input the desired number of tiles in the second annulus (t2), and plot out the model of the undistorted planet.

   02/12/2009, John Burton */

using namespace std;
int option_4()
{
  do{
  float num;
   do {
    cout << "Phase of the system (0-1):" << endl;
     while (!(cin >> num)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Phase of the system (0-1):" << endl;
     }
     if (num<0){
      cout << "Try Again, the value you entered was outside the acceptable range." << endl;
     }
   } while (num<0 || num>1);

   theta = num*360;
   theta2 = (theta*0.0174532925);
   cout << theta << endl;

 /* This process defines the number of tiles per annulus */
 con1 = ((2*PI)/n);
 con2 = ((3*PI)/n);
 r2 = r*sin(con1);
 r3 = r*sin(con2);
 r2b = r*cos(con1);
 r3b = r*cos(con2);
 d23 = ((2*r)/n);
 A = (((PI*r2)+(PI*r3))/(2*t2))*d23;

 ofstream myfile;
 myfile.open("tiles.dat");
 int w;
  for (w=1;w<n;w++){
   rn[w] = r*sin((PI*w)/n);
   rnb[w] = r*cos((PI*w)/n);
   dn[w] = rnb[w-1]-rnb[w];
   tn[w] = (((PI*rn[w-1])+(PI*rn[w]))/(2*A))*sqrt(pow(d23,2.0));
    if (ceil(tn[w])==1){
     dn[w] = rnb[w-1]+rnb[w];
     tn[w] = (((PI*rn[w-1])+(PI*rn[w]))/(2*A))*sqrt(pow(d23,2.0));
    }
     if (w>1){
      myfile << w-1 << " " << ceil(tn[w]) << endl;
     }
  }
 myfile.close();

 /* The following values are the three components of the Earth vector */

 Ex = cos(theta2)*sin(inc2);
 Ey = -sin(theta2)*sin(inc2);
 Ez = cos(inc2);
 E = sqrt((Ex*Ex)+(Ey*Ey)+(Ez*Ez));

 /* The following loop outputs a model of the planet with a grid projected onto its surface */
  if (((n/2)-floor(n/2))!=0){
   myfile.open("grid.dat");
   double preach,transmet;
   preach = (floor(n/2));
   transmet = (ceil(n/2));
   int S,T,U,sandm;
   float fun = 1.0;
    for (T=transmet;T<n+transmet;T++){
     C = fun;
      if (T==transmet){
       /* For the polar regions, a seperate piece of code is required */
        for (U=0;U<21;U++){
         xi = r*cos((n/2)*((2*PI)/((2*n))))*cos(0*((2*PI)/20));
         yi = r*cos((n/2)*((2*PI)/((2*n))))*sin(0*((2*PI)/20));
         zi = r*sin((n/2)*((2*PI)/((2*n))));
         px1 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((U)*((2*PI)/20));
         py1 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((U)*((2*PI)/20));
         pz1 = r*sin((T+1)*((2*PI)/((2*n)+1)));
         px2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((U+1)*((2*PI)/20));
         py2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((U+1)*((2*PI)/20));
         pz2 = r*sin((T+1)*((2*PI)/((2*n)+1)));

         Xi = xi*sin(theta2)+yi*cos(theta2);
         Yi = ((-(xi*cos(theta2))+yi*sin(theta2))*cos(inc2))+zi*sin(inc2);
         XP1 = px1*sin(theta2)+py1*cos(theta2);
         YP1 = ((-(px1*cos(theta2))+py1*sin(theta2))*cos(inc2))+pz1*sin(inc2);
         XP2 = px2*sin(theta2)+py2*cos(theta2);
         YP2 = ((-(px2*cos(theta2))+py2*sin(theta2))*cos(inc2))+pz2*sin(inc2);

         V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
         V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
         E1 = (Ex*px1)+(Ey*py1)+(Ez*pz1);
         E2 = (Ex*px2)+(Ey*py2)+(Ez*pz2);
         ang1 = acos(E1/(E*V1));
         ang2 = acos(E2/(E*V2));
          if (ang1<=PI/2){
           if (ang2<=PI/2){
            myfile << XP1 << " " << YP1 << " " << C << endl << XP2 << " " << YP2 << " " << C << endl << Xi << " " << Yi << " " << C << endl << XP1 << " " << YP1 << " " << C << endl << endl;
           }
          }
         }
        }
         else if (T==(n+preach)){
           for (U=0;U<21;U++){
            xi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*cos(0*((2*PI)/20));
            yi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*sin(0*((2*PI)/20));
            zi = r*sin(((n+(n/2)))*((2*PI)/((2*n))));
            px1 = r*cos(T*((2*PI)/((2*n)+1)))*cos((U)*((2*PI)/20));
            py1 = r*cos(T*((2*PI)/((2*n)+1)))*sin((U)*((2*PI)/20));
            pz1 = r*sin(T*((2*PI)/((2*n)+1)));
            px2 = r*cos(T*((2*PI)/((2*n)+1)))*cos((U+1)*((2*PI)/20));
            py2 = r*cos(T*((2*PI)/((2*n)+1)))*sin((U+1)*((2*PI)/20));
            pz2 = r*sin(T*((2*PI)/((2*n)+1)));

            Xi = xi*sin(theta2)+yi*cos(theta2);
            Yi = ((-(xi*cos(theta2))+yi*sin(theta2))*cos(inc2))+zi*sin(inc2);
            XP1 = px1*sin(theta2)+py1*cos(theta2);
            YP1 = ((-(px1*cos(theta2))+py1*sin(theta2))*cos(inc2))+pz1*sin(inc2);
            XP2 = px2*sin(theta2)+py2*cos(theta2);
            YP2 = ((-(px2*cos(theta2))+py2*sin(theta2))*cos(inc2))+pz2*sin(inc2);

            V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
            V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
            E1 = (Ex*px1)+(Ey*py1)+(Ez*pz1);
            E2 = (Ex*px2)+(Ey*py2)+(Ez*pz2);
            ang1 = acos(E1/(E*V1));
            ang2 = acos(E2/(E*V2));
             if (ang1<=PI/2){
              if (ang2<=PI/2){
	       myfile << XP1 << " " << YP1 << " " << C << endl << XP2 << " " << YP2<< " " << C << endl << Xi << " " << Yi << " " << C << endl << XP1 << " " << YP1 << " " << C << endl;
              }
             }
            }
           }
            else {
             sandm = T-preach;
              for (S=0;S<ceil(tn[sandm]);S++){
  xi = r*cos(T*((2*PI)/((2*n)+1)))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
       yi = r*cos(T*((2*PI)/((2*n)+1)))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  zi = r*sin(T*((2*PI)/((2*n)+1)));
  px1 = r*cos(T*((2*PI)/((2*n)+1)))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py1 = r*cos(T*((2*PI)/((2*n)+1)))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz1 = r*sin(T*((2*PI)/((2*n)+1)));
  px2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz2 = r*sin((T+1)*((2*PI)/((2*n)+1)));
  px3 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py3 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz3 = r*sin((T+1)*((2*PI)/((2*n)+1)));

               Xi = xi*sin(theta2)+yi*cos(theta2);
               Yi = ((-(xi*cos(theta2))+yi*sin(theta2))*cos(inc2))+zi*sin(inc2);
               XP1 = px1*sin(theta2)+py1*cos(theta2);
               YP1 = ((-(px1*cos(theta2))+py1*sin(theta2))*cos(inc2))+pz1*sin(inc2);
               XP2 = px2*sin(theta2)+py2*cos(theta2);
               YP2 = ((-(px2*cos(theta2))+py2*sin(theta2))*cos(inc2))+pz2*sin(inc2);
               XP3 = px3*sin(theta2)+py3*cos(theta2);
               YP3 = ((-(px3*cos(theta2))+py3*sin(theta2))*cos(inc2))+pz3*sin(inc2);

               Vi = sqrt((4*xi*xi)+(4*yi*yi)+(4*zi*zi));
               V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
               V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
               V3 = sqrt((4*px3*px3)+(4*py3*py3)+(4*pz3*pz3));
               Ei = (Ex*xi)+(Ey*yi)+(Ez*zi);
               E1 = (Ex*px1)+(Ey*py1)+(Ez*pz1);
               E2 = (Ex*px2)+(Ey*py2)+(Ez*pz2);
               E3 = (Ex*px3)+(Ey*py3)+(Ez*pz3);
               angi = acos(Ei/(E*Vi));
               ang1 = acos(E1/(E*V1));
               ang2 = acos(E2/(E*V2));
               ang3 = acos(E3/(E*V3));

                if (angi<=PI/2){
                 if (ang1<=PI/2){
                  if (ang2<=PI/2){
                   if (ang3<=PI/2){
                    if (T==25 && S==0){
                      DIG = fun*100.0;
		      myfile << Xi << " " << Yi << " " << DIG << endl << XP1 << " " << YP1 << " " <<  DIG << endl << XP2 << " " << YP2 << " " <<  DIG  << endl << XP3 << " " << YP3 << " " <<  DIG << endl << Xi << " " << Yi << " "  <<  DIG << endl << endl;
                     }
                      else {
                       myfile << Xi << " " << Yi << " " << C << endl << XP1 << " " << YP1 << " " <<  C << endl << XP2 << " " << YP2 << " " <<  C  << endl << XP3 << " " << YP3 << " " <<  C << endl << Xi << " " << Yi << " "  <<  C << endl << endl;
                      }
                     }
                    }
                   }
                  }
                 }
                 myfile << XP3 << " " << YP3 << " " <<  C << endl << endl;
               }
              }
             myfile.close();
            }
 else {
  myfile.open("grid.dat");
  double preach,transmet;
  preach = ((n/2)-1);
  transmet = (ceil(n/2));
  int S,T,U,sandm;
  float fun = 1.0;
   for (T=transmet;T<(n+(transmet+1));T++){
    C = fun;
     if (T==transmet){
      /* For the polar regions, a seperate piece of code is required */
       for (U=0;U<21;U++){
        xi = r*cos((n/2)*((2*PI)/((2*n))))*cos(0*((2*PI)/20));
        yi = r*cos((n/2)*((2*PI)/((2*n))))*sin(0*((2*PI)/20));
        zi = r*sin((n/2)*((2*PI)/((2*n))));
        px1 = r*cos((T+1)*((2*PI)/((2*n))))*cos((U)*((2*PI)/20));
        py1 = r*cos((T+1)*((2*PI)/((2*n))))*sin((U)*((2*PI)/20));
        pz1 = r*sin((T+1)*((2*PI)/((2*n))));
        px2 = r*cos((T+1)*((2*PI)/((2*n))))*cos((U+1)*((2*PI)/20));
        py2 = r*cos((T+1)*((2*PI)/((2*n))))*sin((U+1)*((2*PI)/20));
        pz2 = r*sin((T+1)*((2*PI)/((2*n))));

        Xi = xi*sin(theta2)+yi*cos(theta2);
        Yi = ((-(xi*cos(theta2))+yi*sin(theta2))*cos(inc2))+zi*sin(inc2);
        XP1 = px1*sin(theta2)+py1*cos(theta2);
        YP1 = ((-(px1*cos(theta2))+py1*sin(theta2))*cos(inc2))+pz1*sin(inc2);
        XP2 = px2*sin(theta2)+py2*cos(theta2);
        YP2=((-(px2*cos(theta2))+py2*sin(theta2))*cos(inc2))+pz2*sin(inc2);

        V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
        V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
        E1 = (Ex*px1)+(Ey*py1)+(Ez*pz1);
        E2 = (Ex*px2)+(Ey*py2)+(Ez*pz2);
        ang1 = acos(E1/(E*V1));
        ang2 = acos(E2/(E*V2));
         if (ang1<=PI/2){
          if (ang2<=PI/2){
           myfile << XP1 << " " << YP1 << " " << C << endl << XP2 << " " << YP2 << " " << C << endl << Xi << " " << Yi << " " << C << endl << XP1 << " " << YP1 << " " << C << endl << endl;
          }
         }
        }
       }
        else if (T==n+preach){
         for (U=0;U<21;U++){
          xi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*cos(0*((2*PI)/20));
          yi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*sin(0*((2*PI)/20));
          zi = r*sin(((n+(n/2)))*((2*PI)/((2*n))));
          px1 = r*cos(T*((2*PI)/((2*n))))*cos((U)*((2*PI)/20));
          py1 = r*cos(T*((2*PI)/((2*n))))*sin((U)*((2*PI)/20));
          pz1 = r*sin(T*((2*PI)/((2*n))));
          px2 = r*cos(T*((2*PI)/((2*n))))*cos((U+1)*((2*PI)/20));
          py2 = r*cos(T*((2*PI)/((2*n))))*sin((U+1)*((2*PI)/20));
          pz2 = r*sin(T*((2*PI)/((2*n))));

          Xi = xi*sin(theta2)+yi*cos(theta2);
          Yi = ((-(xi*cos(theta2))+yi*sin(theta2))*cos(inc2))+zi*sin(inc2);
          XP1 = px1*sin(theta2)+py1*cos(theta2);
          YP1 = ((-(px1*cos(theta2))+py1*sin(theta2))*cos(inc2))+pz1*sin(inc2);
          XP2 = px2*sin(theta2)+py2*cos(theta2);
          YP2 = ((-(px2*cos(theta2))+py2*sin(theta2))*cos(inc2))+pz2*sin(inc2);

          V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
          V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
          E1 = (Ex*px1)+(Ey*py1)+(Ez*pz1);
          E2 = (Ex*px2)+(Ey*py2)+(Ez*pz2);
          ang1 = acos(E1/(E*V1));
          ang2 = acos(E2/(E*V2));
           if (ang1<=PI/2){
            if (ang2<=PI/2){
	     myfile << XP1 << " " << YP1 << " " << C << endl << XP2 << " " << YP2<< " " << C << endl << Xi << " " << Yi << " " << C << endl << XP1 << " " << YP1 << " " << C << endl;
            }
           }
          }
         }
          else {
           sandm = ((T-preach));
            for (S=0;S<ceil(tn[sandm]);S++){
  xi = r*cos(T*((2*PI)/((2*n))))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
       yi = r*cos(T*((2*PI)/((2*n))))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  zi = r*sin(T*((2*PI)/((2*n))));
  px1 = r*cos(T*((2*PI)/((2*n))))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py1 = r*cos(T*((2*PI)/((2*n))))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz1 = r*sin(T*((2*PI)/((2*n))));
  px2 = r*cos((T+1)*((2*PI)/((2*n))))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py2 = r*cos((T+1)*((2*PI)/((2*n))))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz2 = r*sin((T+1)*((2*PI)/((2*n))));
  px3 = r*cos((T+1)*((2*PI)/((2*n))))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py3 = r*cos((T+1)*((2*PI)/((2*n))))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz3 = r*sin((T+1)*((2*PI)/((2*n))));

             Xi = xi*sin(theta2)+yi*cos(theta2);
             Yi = ((-(xi*cos(theta2))+yi*sin(theta2))*cos(inc2))+zi*sin(inc2);
             XP1 = px1*sin(theta2)+py1*cos(theta2);
             YP1 = ((-(px1*cos(theta2))+py1*sin(theta2))*cos(inc2))+pz1*sin(inc2);
             XP2 = px2*sin(theta2)+py2*cos(theta2);
             YP2 = ((-(px2*cos(theta2))+py2*sin(theta2))*cos(inc2))+pz2*sin(inc2);
             XP3 = px3*sin(theta2)+py3*cos(theta2);
             YP3=((-(px3*cos(theta2))+py3*sin(theta2))*cos(inc2))+pz3*sin(inc2);

             Vi = sqrt((4*xi*xi)+(4*yi*yi)+(4*zi*zi));
             V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
             V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
             V3 = sqrt((4*px3*px3)+(4*py3*py3)+(4*pz3*pz3));
             Ei = (Ex*xi)+(Ey*yi)+(Ez*zi);
             E1 = (Ex*px1)+(Ey*py1)+(Ez*pz1);
             E2 = (Ex*px2)+(Ey*py2)+(Ez*pz2);
             E3 = (Ex*px3)+(Ey*py3)+(Ez*pz3);
             angi = acos(Ei/(E*Vi));
             ang1 = acos(E1/(E*V1));
             ang2 = acos(E2/(E*V2));
             ang3 = acos(E3/(E*V3));

              if (angi<=PI/2){
               if (ang1<=PI/2){
                if (ang2<=PI/2){
                 if (ang3<=PI/2){
                  if (T==25 && S==0){
                   DIG = fun*100.0;
		   myfile << Xi << " " << Yi << " " << DIG << endl << XP1 << " " << YP1 << " " <<  DIG << endl << XP2 << " " << YP2 << " " <<  DIG  << endl << XP3 << " " << YP3 << " " <<  DIG << endl << Xi << " " << Yi << " "  <<  DIG << endl << endl;
		  }
                   else{
                    myfile << Xi << " " << Yi << " " << C << endl << XP1 << " " << YP1 << " " <<  C << endl << XP2 << " " << YP2 << " " <<  C  << endl << XP3 << " " << YP3 << " " <<  C << endl << Xi << " " << Yi << " "  <<  C << endl << endl;
                   }
                  }
                 }
                }
               }
              }
            myfile << XP3 << " " << YP3 << " " <<  C << endl << endl;
           }
          }
       myfile.close();
       }

   float high,low;
   high = (ceil(r)+(0.5*ceil(r)));
   low = (-(ceil(r))-(0.5*ceil(r)));

    if (r<1.5){
     high = high-0.5;
     low = low+0.5;
    }

   myfile.open("high.dat");
   myfile << high << " " << 0 << " " << 0 << endl;
   myfile.close();

   myfile.open("low.dat");
   myfile << low  << " " << 0 << " " << 0 << endl;
   myfile.close();

   /* This process opens GNUplot using popen (pipe open) which allows for commands to be used in GNUplot without the need to read out to a file and then plot the data seperately */

   FILE *fp = popen("gnuplot","w");
    if (fp){
     if (sw == 'a'){
    fprintf(fp,"set terminal aqua enhanced title 'Grid Model of WASP-12'\n");
     }
     else if (sw == 'b'){
    fprintf(fp,"set terminal aqua enhanced title 'Grid Model of WASP-18'\n");
     }
     else if (sw == 'c'){
    fprintf(fp,"set terminal aqua enhanced title 'Grid Model of CoRoT-5'\n");
     }
     else if (sw == 'd'){
    fprintf(fp,"set terminal aqua enhanced title 'Grid Model of XO-4'\n");
     }
     else if (sw == 'e'){
    fprintf(fp,"set terminal aqua enhanced title 'Grid Model of HAT-P-9'\n");
     }
     else if (sw == 'f'){
    fprintf(fp,"set terminal aqua enhanced title 'Grid Model for Custom Parameters'\n");
     }
     fprintf(fp,"set xlabel 'x[R_J]'\n");
     fprintf(fp,"set ylabel 'y[R_J]'\n");
     fprintf(fp,"set size square\n");
     fprintf(fp,"set title 'Grid model of the undistorted planet'\n"); 
     fprintf(fp,"unset key\n");
     fprintf(fp,"plot 'grid.dat' w lines lt 9 \n");
     fflush(fp);
     fprintf(fp,"exit \n");
     pclose(fp);
    }

  cout << "The data has been read into the file 'grid.dat'" << endl;

  cout << "Would you like to replot with a different inclination (y/n)?" << endl;
  cin >> cont;
  if (cont == 'y' || cont == 'Y'){
 do {
    cout << "Orbital inclination of the system in degrees: " << endl;
     while (!(cin >> inc)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Orbital inclination of the system in degrees: " << endl;
     }
     if (inc<0){
      cout << "Try Again, the value you entered was outside the acceptable range." << endl;
      }
    } while (inc<0 || inc>360);
  }
inc2 = (inc*0.0174532925);

  } while (cont == 'y' || cont == 'Y');

}


/* LIGHT - This subroutine loops through a full 360 degree rotation of the planet, and plots a light curve based on the total flux over the surface area of the tiles

   02/12/2009, John Burton */
using namespace std;
int option_5()
{
 /* The following process loops 36 times in order to give a full rotation of the planet in increments of 10 degrees. For each 10 degrees, the area of each tile is multiplied by the specific intensity of that tile and summed in order to give a flux over the area */

 ofstream myfile;
 fstream readfile;
 ifstream inFile;
 int M;
 int loop;
 int O;

 /* The file 'area.dat' has to be opened her to clear out the results from the previous itertion, as readfile will simply read in the values without deleting the old ones */

 con1 = ((2*PI)/n);
 con2 = ((3*PI)/n);
 r2 = r*sin(con1);
 r3 = r*sin(con2);
 r2b = r*cos(con1);
 r3b = r*cos(con2);
 d23 = ((2*r)/n);
 A = (((PI*r2)+(PI*r3))/(2*t2))*d23;

 myfile.open("tiles.dat");
 int w;
  for (w=1;w<n;w++){
   rn[w] = r*sin((PI*w)/n);
   rnb[w] = r*cos((PI*w)/n);
   dn[w] = rnb[w-1]-rnb[w];
   tn[w] = (((PI*rn[w-1])+(PI*rn[w]))/(2*A))*sqrt(pow(d23,2.0));
    if (ceil(tn[w])==1){
     dn[w] = rnb[w-1]+rnb[w];
     tn[w] = (((PI*rn[w-1])+(PI*rn[w]))/(2*A))*sqrt(pow(d23,2.0));
    }
     if (w>1){
      myfile << w-1 << " " << ceil(tn[w]) << endl;
     }
  }
 myfile.close();

 myfile.open("area.dat");
 myfile.close();

 /* readfile allows the file to remain open during the loop and have values written to it without overwriting the value every time */

 readfile.open("area.dat");
 th = -10.0;
  for(loop=0;loop<37;loop++){
   th=th+10.0;
   th2 = (th*0.0174532925);
   Ex2 = cos(th2)*sin(inc2);
   Ey2 = -sin(th2)*sin(inc2);
   Ez2 = cos(inc2);
   EE = sqrt((Ex2*Ex2)+(Ey2*Ey2)+(Ez2*Ez2));

    if ((n/2)-floor(n/2)!=0){
     myfile.open("light.dat");
     double preach,transmet;
     preach = (floor(n/2));
     transmet = (ceil(n/2));
     int S,T,U,sandm;
     float fun = 1.0;
      for (T=transmet;T<n+transmet;T++){
       C = fun;
        if (T==transmet){
         /* For the polar regions, a seperate piece of code is required */
          for (U=0;U<26;U++){
           xi = r*cos((n/2)*((2*PI)/((2*n))))*cos(0*((2*PI)/25));
           yi = r*cos((n/2)*((2*PI)/((2*n))))*sin(0*((2*PI)/25));
           zi = r*sin((n/2)*((2*PI)/((2*n))));
           px1 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((U)*((2*PI)/25));
           py1 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((U)*((2*PI)/25));
           pz1 = r*sin((T+1)*((2*PI)/((2*n)+1)));
           px2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((U+1)*((2*PI)/25));
           py2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((U+1)*((2*PI)/25));
           pz2 = r*sin((T+1)*((2*PI)/((2*n)+1)));

           Xi = xi*sin(th2)+yi*cos(th2);
           Yi = ((-(xi*cos(th2))+yi*sin(th2))*cos(inc2))+zi*sin(inc2);
           XP1 = px1*sin(th2)+py1*cos(th2);
           YP1 = ((-(px1*cos(th2))+py1*sin(th2))*cos(inc2))+pz1*sin(inc2);
           XP2 = px2*sin(th2)+py2*cos(th2);
           YP2 = ((-(px2*cos(th2))+py2*sin(th2))*cos(inc2))+pz2*sin(inc2);

           V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
           V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
           E1 = (Ex2*px1)+(Ey2*py1)+(Ez2*pz1);
           E2 = (Ex2*px2)+(Ey2*py2)+(Ez2*pz2);
           ang1 = acos(E1/(EE*V1));
           ang2 = acos(E2/(EE*V2));
            if (ang1<=PI/2){
             if (ang2<=PI/2){
              Dist1 = sqrt(pow((Xi-XP1),2.0)+pow((Yi-YP1),2.0));
              Dist2 = sqrt(pow((Xi-XP2),2.0)+pow((Yi-YP2),2.0));
              Dist3 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
              St = 0.5*(Dist1+Dist2+Dist3);
              Sq = (St*(St-Dist1)*(St-Dist2)*(St-Dist3));
              Ar = sqrt(Sq);
              myfile << Ar*C << endl;
             }
            }
           }
          }
         else if (T==(n+preach)){
          for (U=0;U<26;U++){
           xi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*cos(0*((2*PI)/25));
           yi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*sin(0*((2*PI)/25));
           zi = r*sin(((n+(n/2)))*((2*PI)/((2*n))));
           px1 = r*cos(T*((2*PI)/((2*n)+1)))*cos((U)*((2*PI)/25));
           py1 = r*cos(T*((2*PI)/((2*n)+1)))*sin((U)*((2*PI)/25));
           pz1 = r*sin(T*((2*PI)/((2*n)+1)));
           px2 = r*cos(T*((2*PI)/((2*n)+1)))*cos((U+1)*((2*PI)/25));
           py2 = r*cos(T*((2*PI)/((2*n)+1)))*sin((U+1)*((2*PI)/25));
           pz2 = r*sin(T*((2*PI)/((2*n)+1)));

           Xi = xi*sin(th2)+yi*cos(th2);
           Yi = ((-(xi*cos(th2))+yi*sin(th2))*cos(inc2))+zi*sin(inc2);
           XP1 = px1*sin(th2)+py1*cos(th2);
           YP1 = ((-(px1*cos(th2))+py1*sin(th2))*cos(inc2))+pz1*sin(inc2);
           XP2 = px2*sin(th2)+py2*cos(th2);
           YP2=((-(px2*cos(th2))+py2*sin(th2))*cos(inc2))+pz2*sin(inc2);

           V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
           V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
           E1 = (Ex2*px1)+(Ey2*py1)+(Ez2*pz1);
           E2 = (Ex2*px2)+(Ey2*py2)+(Ez2*pz2);
           ang1 = acos(E1/(EE*V1));
           ang2 = acos(E2/(EE*V2));
            if (ang1<=PI/2){
             if (ang2<=PI/2){
              Dist1 = sqrt(pow((Xi-XP1),2.0)+pow((Yi-YP1),2.0));
              Dist2 = sqrt(pow((Xi-XP2),2.0)+pow((Yi-YP2),2.0));
              Dist3 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
              St = 0.5*(Dist1+Dist2+Dist3);
              Sq = (St*(St-Dist1)*(St-Dist2)*(St-Dist3));
              Ar = sqrt(Sq);
              myfile << Ar*C<< endl;
             }
            }
           }
          }
         else {
          sandm = T-preach;
           for (S=0;S<ceil(tn[sandm]);S++){
  xi = r*cos(T*((2*PI)/((2*n)+1)))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
       yi = r*cos(T*((2*PI)/((2*n)+1)))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  zi = r*sin(T*((2*PI)/((2*n)+1)));
  px1 = r*cos(T*((2*PI)/((2*n)+1)))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py1 = r*cos(T*((2*PI)/((2*n)+1)))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz1 = r*sin(T*((2*PI)/((2*n)+1)));
  px2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py2 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz2 = r*sin((T+1)*((2*PI)/((2*n)+1)));
  px3 = r*cos((T+1)*((2*PI)/((2*n)+1)))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py3 = r*cos((T+1)*((2*PI)/((2*n)+1)))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz3 = r*sin((T+1)*((2*PI)/((2*n)+1)));

            Xi = xi*sin(th2)+yi*cos(th2);
            Yi = ((-(xi*cos(th2))+yi*sin(th2))*cos(inc2))+zi*sin(inc2);
            XP1 = px1*sin(th2)+py1*cos(th2);
            YP1 = ((-(px1*cos(th2))+py1*sin(th2))*cos(inc2))+pz1*sin(inc2);
            XP2 = px2*sin(th2)+py2*cos(th2);
            YP2 = ((-(px2*cos(th2))+py2*sin(th2))*cos(inc2))+pz2*sin(inc2);
            XP3 = px3*sin(th2)+py3*cos(th2);
            YP3 = ((-(px3*cos(th2))+py3*sin(th2))*cos(inc2))+pz3*sin(inc2);

            Vi = sqrt((4*xi*xi)+(4*yi*yi)+(4*zi*zi));
            V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
            V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
            V3 = sqrt((4*px3*px3)+(4*py3*py3)+(4*pz3*pz3));
            Ei = (Ex2*xi)+(Ey2*yi)+(Ez2*zi);
            E1 = (Ex2*px1)+(Ey2*py1)+(Ez2*pz1);
            E2 = (Ex2*px2)+(Ey2*py2)+(Ez2*pz2);
            E3 = (Ex2*px3)+(Ey2*py3)+(Ez2*pz3);
            angi = acos(Ei/(EE*Vi));
            ang1 = acos(E1/(EE*V1));
            ang2 = acos(E2/(EE*V2));
            ang3 = acos(E3/(EE*V3));

             if (angi<=PI/2){
              if (ang1<=PI/2){
               if (ang2<=PI/2){
                if (ang3<=PI/2){
		  if (S==95 && T==25){
		   Dist = sqrt(pow((XP2-Xi),2.0)+pow((YP2-Yi),2.0));
		   Dista = sqrt(pow((XP3-XP1),2.0)+pow((YP3-YP1),2.0));
		   Dist1 = sqrt(pow((XP1-Xi),2.0)+pow((YP1-Yi),2.0));
		   Dist2 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
		   Dist3 = sqrt(pow((XP3-XP2),2.0)+pow((YP3-YP2),2.0));
		   Dist4 = sqrt(pow((XP3-Xi),2.0)+pow((YP3-Yi),2.0));
						
		   Ar1 = 0.5*(Dist1+Dist2+Dist3+Dist4);
		   Ar2 = (Dist1*Dist3)+(Dist2*Dist4)+(Dist*Dista);
		   Ar3 = (Dist1*Dist3)+(Dist2*Dist4)-(Dist*Dista);
		   St = ((Ar1-Dist1)*(Ar1-Dist2)*(Ar1-Dist3)*(Ar1-Dist4));
		   Sq = 0.25*((Ar2*Ar3));
		   Ar = sqrt(St-Sq);
		   myfile << Ar*C*100.0 << endl;
		   }
         else {
   Dist = sqrt(pow((XP2-Xi),2.0)+pow((YP2-Yi),2.0));
                Dista = sqrt(pow((XP3-XP1),2.0)+pow((YP3-YP1),2.0));
                Dist1 = sqrt(pow((XP1-Xi),2.0)+pow((YP1-Yi),2.0));
                Dist2 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
                Dist3 = sqrt(pow((XP3-XP2),2.0)+pow((YP3-YP2),2.0));
                Dist4 = sqrt(pow((XP3-Xi),2.0)+pow((YP3-Yi),2.0));

                Ar1 = 0.5*(Dist1+Dist2+Dist3+Dist4);
                Ar2 = (Dist1*Dist3)+(Dist2*Dist4)+(Dist*Dista);
                Ar3 = (Dist1*Dist3)+(Dist2*Dist4)-(Dist*Dista);
                St = ((Ar1-Dist1)*(Ar1-Dist2)*(Ar1-Dist3)*(Ar1-Dist4));
                Sq = 0.25*((Ar2*Ar3));
                Ar = sqrt(St-Sq);
                myfile << Ar*C << endl;
		 }
		}
	       }
	      }
	    }
           }
	 }
      }
       myfile.close();
    }
    else {
     myfile.open("light.dat");
     double preach,transmet;  
     preach = ((n/2)-1);
     transmet = (ceil(n/2));
     int S,T,U,sandm;
     float fun = 1.0;
      for (T=transmet;T<n+transmet;T++){
       C = fun;
        if (T==transmet){
         /* For the polar regions, a seperate piece of code is required */
          for (U=0;U<26;U++){
           xi = r*cos((n/2)*((2*PI)/((2*n))))*cos(0*((2*PI)/25));
           yi = r*cos((n/2)*((2*PI)/((2*n))))*sin(0*((2*PI)/25));
           zi = r*sin((n/2)*((2*PI)/((2*n))));
           px1 = r*cos((T+1)*((2*PI)/((2*n))))*cos((U)*((2*PI)/25));
           py1 = r*cos((T+1)*((2*PI)/((2*n))))*sin((U)*((2*PI)/25));
           pz1 = r*sin((T+1)*((2*PI)/((2*n))));
           px2 = r*cos((T+1)*((2*PI)/((2*n))))*cos((U+1)*((2*PI)/25));
           py2 = r*cos((T+1)*((2*PI)/((2*n))))*sin((U+1)*((2*PI)/25));
           pz2 = r*sin((T+1)*((2*PI)/((2*n))));

           Xi = xi*sin(th2)+yi*cos(th2);
           Yi = ((-(xi*cos(th2))+yi*sin(th2))*cos(inc2))+zi*sin(inc2);
           XP1 = px1*sin(th2)+py1*cos(th2);
           YP1 = ((-(px1*cos(th2))+py1*sin(th2))*cos(inc2))+pz1*sin(inc2);
           XP2 = px2*sin(th2)+py2*cos(th2);
           YP2 = ((-(px2*cos(th2))+py2*sin(th2))*cos(inc2))+pz2*sin(inc2);

           V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
           V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
           E1 = (Ex2*px1)+(Ey2*py1)+(Ez2*pz1);
           E2 = (Ex2*px2)+(Ey2*py2)+(Ez2*pz2);
           ang1 = acos(E1/(EE*V1));
           ang2 = acos(E2/(EE*V2));
            if (ang1<=PI/2){
             if (ang2<=PI/2){
              Dist1 = sqrt(pow((Xi-XP1),2.0)+pow((Yi-YP1),2.0));
              Dist2 = sqrt(pow((Xi-XP2),2.0)+pow((Yi-YP2),2.0));
              Dist3 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
              St = 0.5*(Dist1+Dist2+Dist3);
              Sq = (St*(St-Dist1)*(St-Dist2)*(St-Dist3));
              Ar = sqrt(Sq);
              myfile << Ar*C << endl;
             }
            }
           }
          }
        else if (T==(n+preach)){
         for (U=0;U<26;U++){
          xi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*cos(0*((2*PI)/25));
          yi = r*cos(((n+(n/2)))*((2*PI)/((2*n))))*sin(0*((2*PI)/25));
          zi = r*sin(((n+(n/2)))*((2*PI)/((2*n))));
          px1 = r*cos(T*((2*PI)/((2*n))))*cos((U)*((2*PI)/25));
          py1 = r*cos(T*((2*PI)/((2*n))))*sin((U)*((2*PI)/25));
          pz1 = r*sin(T*((2*PI)/((2*n))));
          px2 = r*cos(T*((2*PI)/((2*n))))*cos((U+1)*((2*PI)/25));
          py2 = r*cos(T*((2*PI)/((2*n))))*sin((U+1)*((2*PI)/25));
          pz2 = r*sin(T*((2*PI)/((2*n))));

          Xi = xi*sin(th2)+yi*cos(th2);
          Yi = ((-(xi*cos(th2))+yi*sin(th2))*cos(inc2))+zi*sin(inc2);
          XP1 = px1*sin(th2)+py1*cos(th2);
          YP1 = ((-(px1*cos(th2))+py1*sin(th2))*cos(inc2))+pz1*sin(inc2);
          XP2 = px2*sin(th2)+py2*cos(th2);
          YP2 = ((-(px2*cos(th2))+py2*sin(th2))*cos(inc2))+pz2*sin(inc2);

          V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
          V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
          E1 = (Ex2*px1)+(Ey2*py1)+(Ez2*pz1);
          E2 = (Ex2*px2)+(Ey2*py2)+(Ez2*pz2);
          ang1 = acos(E1/(EE*V1));
          ang2 = acos(E2/(EE*V2));
           if (ang1<=PI/2){
            if (ang2<=PI/2){
             Dist1 = sqrt(pow((Xi-XP1),2.0)+pow((Yi-YP1),2.0));
             Dist2 = sqrt(pow((Xi-XP2),2.0)+pow((Yi-YP2),2.0));
             Dist3 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
             St = 0.5*(Dist1+Dist2+Dist3);
             Sq = (St*(St-Dist1)*(St-Dist2)*(St-Dist3));
             Ar = sqrt(Sq);
             myfile << Ar*C<< endl;
            }
           }
          }
         }
       else {
        sandm = T-preach;
         for (S=0;S<ceil(tn[sandm]);S++){
  xi = r*cos(T*((2*PI)/((2*n))))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
       yi = r*cos(T*((2*PI)/((2*n))))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  zi = r*sin(T*((2*PI)/((2*n))));
  px1 = r*cos(T*((2*PI)/((2*n))))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py1 = r*cos(T*((2*PI)/((2*n))))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz1 = r*sin(T*((2*PI)/((2*n))));
  px2 = r*cos((T+1)*((2*PI)/((2*n))))*cos((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py2 = r*cos((T+1)*((2*PI)/((2*n))))*sin((S+1+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz2 = r*sin((T+1)*((2*PI)/((2*n))));
  px3 = r*cos((T+1)*((2*PI)/((2*n))))*cos((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  py3 = r*cos((T+1)*((2*PI)/((2*n))))*sin((S+(T*0.5))*((2*PI)/ceil(tn[sandm])));
  pz3 = r*sin((T+1)*((2*PI)/((2*n))));

          Xi = xi*sin(th2)+yi*cos(th2);
          Yi = ((-(xi*cos(th2))+yi*sin(th2))*cos(inc2))+zi*sin(inc2);
          XP1 = px1*sin(th2)+py1*cos(th2);
          YP1 = ((-(px1*cos(th2))+py1*sin(th2))*cos(inc2))+pz1*sin(inc2);
          XP2 = px2*sin(th2)+py2*cos(th2);
          YP2 = ((-(px2*cos(th2))+py2*sin(th2))*cos(inc2))+pz2*sin(inc2);
          XP3 = px3*sin(th2)+py3*cos(th2);
          YP3 = ((-(px3*cos(th2))+py3*sin(th2))*cos(inc2))+pz3*sin(inc2);

          Vi = sqrt((4*xi*xi)+(4*yi*yi)+(4*zi*zi));
          V1 = sqrt((4*px1*px1)+(4*py1*py1)+(4*pz1*pz1));
          V2 = sqrt((4*px2*px2)+(4*py2*py2)+(4*pz2*pz2));
          V3 = sqrt((4*px3*px3)+(4*py3*py3)+(4*pz3*pz3));
          Ei = (Ex2*xi)+(Ey2*yi)+(Ez2*zi);
          E1 = (Ex2*px1)+(Ey2*py1)+(Ez2*pz1);
          E2 = (Ex2*px2)+(Ey2*py2)+(Ez2*pz2);
          E3 = (Ex2*px3)+(Ey2*py3)+(Ez2*pz3);
          angi = acos(Ei/(EE*Vi));
          ang1 = acos(E1/(EE*V1));
          ang2 = acos(E2/(EE*V2));
          ang3 = acos(E3/(EE*V3));

           if (angi<=PI/2){
            if (ang1<=PI/2){
             if (ang2<=PI/2){
              if (ang3<=PI/2){
		if (S==95 && T==25){
		  Dist = sqrt(pow((XP2-Xi),2.0)+pow((YP2-Yi),2.0));
		  Dista = sqrt(pow((XP3-XP1),2.0)+pow((YP3-YP1),2.0));
		  Dist1 = sqrt(pow((XP1-Xi),2.0)+pow((YP1-Yi),2.0));
		  Dist2 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
		  Dist3 = sqrt(pow((XP3-XP2),2.0)+pow((YP3-YP2),2.0));
		  Dist4 = sqrt(pow((XP3-Xi),2.0)+pow((YP3-Yi),2.0));
					  
		  Ar1 = 0.5*(Dist1+Dist2+Dist3+Dist4);
		  Ar2 = (Dist1*Dist3)+(Dist2*Dist4)+(Dist*Dista);
		  Ar3 = (Dist1*Dist3)+(Dist2*Dist4)-(Dist*Dista);
		  St = ((Ar1-Dist1)*(Ar1-Dist2)*(Ar1-Dist3)*(Ar1-Dist4));
		  Sq = 0.25*((Ar2*Ar3));
		  Ar = sqrt(St-Sq);
		  myfile << Ar*C*100.0 << endl;
		  }
		else {
	Dist = sqrt(pow((XP2-Xi),2.0)+pow((YP2-Yi),2.0));
             Dista = sqrt(pow((XP3-XP1),2.0)+pow((YP3-YP1),2.0));
             Dist1 = sqrt(pow((XP1-Xi),2.0)+pow((YP1-Yi),2.0));
             Dist2 = sqrt(pow((XP2-XP1),2.0)+pow((YP2-YP1),2.0));
             Dist3 = sqrt(pow((XP3-XP2),2.0)+pow((YP3-YP2),2.0));
             Dist4 = sqrt(pow((XP3-Xi),2.0)+pow((YP3-Yi),2.0));

             Ar1 = 0.5*(Dist1+Dist2+Dist3+Dist4);
             Ar2 = (Dist1*Dist3)+(Dist2*Dist4)+(Dist*Dista);
             Ar3 = (Dist1*Dist3)+(Dist2*Dist4)-(Dist*Dista);
             St = ((Ar1-Dist1)*(Ar1-Dist2)*(Ar1-Dist3)*(Ar1-Dist4));
             Sq = 0.25*((Ar2*Ar3));
             Ar = sqrt(St-Sq);
             myfile << Ar*C << endl;
		}
	      }
	     }
	    }
	   }
	 }
       }
      }
    } myfile.close();
    

 /* Working out the total area visible from the viewer's pespective */

 inFile.open("light.dat");
  while (!inFile.eof()){
   for (M=0;M<3000;M++){
    inFile >> Area[M];
   }
  }
 inFile.close();
 
 float sum = 0.0;
  for (O=0;O<3000;O++){
   sum = sum+Area[O];
  }

  readfile << (th/360) << " " << sum << endl;

  float IdealArea,rat;
  IdealArea = PI*(r*r);
  rat = IdealArea/sum;
 }
 readfile.close();

 double sumarr[72];
 int sa;
 inFile.open("area.dat");

  for(sa=0;sa<72;sa++){
   inFile >> sumarr[sa];
    if (sumarr[sa]-floor(sumarr[sa])==0){
     sumarr[sa] = 0;
    }
  }
 
 inFile.close();

 /* The following step is designed to set the correct range for the light curves. The highest value of the array is found, along with the lowest, and then an integer (one) is added to the highest value, and taken off the lowest value. These are plotted along with the light curve data on the y axis, so they will not be in the plot area. */

 double high = sumarr[0];
 double low = sumarr[1];
 int h,l;
 double hrange,lrange;
  for (h=0;h<72;h++){
   if(sumarr[h]>high){
     high = sumarr[h];
   }
  }

  hrange = high+(high/10);

 myfile.open("high.dat");
 myfile << 0 << " " << hrange << endl;
 myfile.close();

  for (l=0;l<72;l++){
    if(sumarr[l]<low){
   if (sumarr[l]>1){
     low = sumarr[l];
    }
   }
  }

  cout << low << endl;
  lrange = low-(low/10);

 myfile.open("low.dat");
 myfile << 0 << " " << lrange << endl;
 myfile.close();

 /* This process opens GNUplot using popen (pipe open) which allows for commands to be used in GNUplot without the need to read out to a file and then plot the data seperately */

 FILE *fp = popen("gnuplot","w");
  if (fp){
  if (sw == 'a'){
    fprintf(fp,"set terminal aqua enhanced title 'Light Curve for WASP-12'\n");
     }
     else if (sw == 'b'){
    fprintf(fp,"set terminal aqua enhanced title 'Light Curve for WASP-18'\n");
     }
     else if (sw == 'c'){
    fprintf(fp,"set terminal aqua enhanced title 'Light Curve for CoRoT-5'\n");
     }
     else if (sw == 'd'){
    fprintf(fp,"set terminal aqua enhanced title 'Light Curve for XO-4'\n");
     }
     else if (sw == 'e'){
    fprintf(fp,"set terminal aqua enhanced title 'Light Curve for HAT-P-9'\n");
     }
     else if (sw == 'f'){
    fprintf(fp,"set terminal aqua enhanced title 'Light curve for Custom Parameters'\n");
     }
   fprintf(fp,"set xlabel 'Orbital Phase'\n");
   fprintf(fp,"set ylabel 'Flux [arbitrary units]'\n");
   fprintf(fp,"set title 'Light Curve'\n");
   fprintf(fp,"set xrange [0:1]\n"); 
   fprintf(fp,"unset key\n");
   fprintf(fp,"plot 'area.dat', 'high.dat' w dots lt 2, 'low.dat' w dots lt 2\n");
   fflush(fp);
   fprintf(fp,"exit \n");
   pclose(fp);
   }

  return 0;
}

/* PARCH - This section of the program is designed to allow the user to alter specific parameters after running the program before. This is to avoid having running the PARS section again 

John Burton, 02/12/2009*/

using namespace std;
int option_6()

{
  float process;
  char ltc,q;
  do{
  cout << "If you would like to change a parameter, please enter the corresponding number: " << endl;
  cout << "1. Mass of the star = " << M1 << " Solar Masses." << endl;
  cout << "2. Mass of the planet = " << M2 << " Jupiter Masses." << endl;
  cout << "3. Period of the planet = " << P << " days." << endl;
  cout << "4. Radius of the planet = " << r << " Jupiter radii." << endl;
  cout << "5. Number of slices = " << n << " slices." << endl;
  cout << "6. Number of tiles in annulus 2 = " << t2 << " tiles." << endl;
  cout << "7. Return to main menu." << endl;

   do{
  while (!(cin >> process)){
   cin.clear();
    while (cin.get() !='\n'){}
  }
  if (process < 1){
   cin.clear();
    while (cin.get() !='\n'){}
  }
  check = (process-floor(process));
   if (check>0){
    cout << "The value you entered was not an integer, please try again." << endl;
   }
  }while(check>0);

 if (process == 1){
   do {
    cout << "Mass of the Star in Solar masses:" << endl;
     while (!(cin >> M1)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Mass of the Star in Solar masses:" << endl;
     }
     if (M1<0.0000001 || M1>1000){
      cout << "Unacceptable value entered, please try again.\n";
     }
    } while (M1<0.0000001 || M1>1000);

 }
 else if (process == 2){

   do {
    cout << "Mass of the planet in Jupiter masses: " << endl;
     while (!(cin >> M2)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Mass of the planet in Jupiter masses: " << endl;
     }
     if (M2<0.00000001 || M2>10000){
      cout << "Unacceptable value entered, please try again" << endl;
     }
    } while (M2<0.00000001 || M2>10000);
 }
 else if (process == 3){
    do {
    cout << "Period of the planet in days: " << endl;
     while (!(cin >> P)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Period of the planet in days: " << endl;
     }
      if (P<0.00000001 || P>100000){
       cout << "Unacceptable value entered, please try again" << endl;
      }
     } while (P<0.000001 || P>100000);
 }
 else if (process == 4){
   do {
    cout << "Radius of the planet in Jupiter radii:" << endl;
     while (!(cin >> r)){
      cin.clear();
       while (cin.get() !='\n'){}
      cout << "Radius of the planet in Jupiter radii:" << endl;
     }
    if (r<0.000001 || r>10000){
     cout << "Try Again, the value you entered was not acceptable (less than or equal to zero)." << endl;
    }
   } while (r<0.000001 || r>10000);
 }
 else if (process == 5){
    do {
   cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
    while (!(cin >> n)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of slices to be modelled, greater than 20 and less than 40:" << endl;
     }
   } while (n < 20 || n > 40);
 }
 else if (process == 6){
   do {
    cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    while (!(cin >> t2)){
     cin.clear();
      while (cin.get() !='\n'){}
     cout << "Please enter a number of tiles for the second annulus, greater than 20 and less than 40:" << endl;
    }
   } while (t2 < 20 || t2 > 40);
 }
 else if (process == 7){
     cout << "Return to main menu (y/n)?" << endl;
     cin >> q;
     if (q == 'y' || q == 'Y'){
       return 0;
     }
 }
  else {
   /* This is incase the user enters a number outside of the range (1-6) */
   cout << "Unknown process!" << endl;
   ltc = 'y';
  }
  }while (process == 1 || process == 2 || process == 3 || process == 4 || process == 5 || process == 6 || process == 7 || ltc == 'y' || ltc == 'Y' || ltc != 'n' || ltc != 'N');

}
