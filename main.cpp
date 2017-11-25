/*-------------------------------------Info------------------------------------
 *	Name:				Date:			Current Version:
 *	Martin Barcelon		11-15-2017		1.0
 *
 *	Email:
 *	martin.barcelon@stonybrook.edu
 *
 *	Student ID:
 *	110250249
 *
 */
/*-------------------------------Short Description-----------------------------
 *  This program uses a temperature plate grid where the user specifys the top,
 * sides and bottom temperature squares. The grid itself has 6 rows and 8
 * columns. The program initializes the temperature grid based on user inputs
 * and then uses pass by reference to change the grid using the "makeGrid"
 * function.
 * ----------------------------------------------------------------------------
 */

#include <iostream> //Required for cout.
#include <math.h> //Required for fabs();
#include <iomanip> //Required for setw().

//Initialize constant variables
const int NROWS=6;
const int NCOLS=8;

using namespace std;

//Initialize functions makeGrid and equalizeGird.
void makeGrid(double (&arrayTemp)[NROWS][NCOLS],int rows,int columns,
              double top,double bottom,double left,double right);
void equalizeGrid(double arrayTemp[NROWS][NCOLS],int rows,int columns,
                  double epsilon);

int main()
{
    //Initialize the 4 sides' variables, tolerance variable and the vector
    double top,bottom,left,right,tolerance;
    double plate[NROWS][NCOLS];

    //Let user input the parameters of the plate's sides.
    cout << "Enter the temperature of the top,"
        << "bottom and sides of the plate: \n";
    cout << "Top: ";
    cin >> top;
    cout << "Bottom: ";
    cin >> bottom;
    cout << "Left: ";
    cin >> left;
    cout << "Right: ";
    cin >> right;

    //Let user enter the value for the tolerance.
    cout <<"Enter a tolerance value: ";
    cin>>tolerance;

    //Take absolute value of the tolerance using the fabs() function.
    tolerance = fabs(tolerance);

    //Change the plate vector to reflect the temperature grid before its
    //equalized.
    makeGrid(plate,NROWS,NCOLS,top,bottom,left,right);

    //Equalize the temperatures in the vector plate until all fall under
    //tolerance.
    equalizeGrid(plate,NROWS,NCOLS,tolerance);

    //Prevents shutdown of cmd after program is run
    cin.get();
    cin.get();

    return 0;
}

void makeGrid(double (&arrayTemp)[NROWS][NCOLS],int rows,int columns,
              double top,double bottom,double left,double right){

    //Set all the values within the array.
    for (int i = 0; i < rows; i++) {
        for (int j=0;j < columns;j++) {
            //Assume that it is NOT any one of the sides.
            arrayTemp[i][j]=0;
            //Check if the point is the top side.
            if (i==0) {
                arrayTemp[i][j] = top;
            }
            //Check if the point is the bottom side.
            if (i==rows - 1) {
                arrayTemp[i][j] = bottom;
            }
            //Check if the point is the left side.
            if (i != 0 && i != rows-1 && j ==0){
                arrayTemp[i][j] = left;
            }
            //Check if the point is the right side.
            if (i != 0 && i != rows-1 && j==columns-1) {
                arrayTemp[i][j] = right;
            }
            //Check if the point is the bottom left corner.
            if (i==rows -1 && j==0) {
                arrayTemp[i][j] = (bottom+left)/2;
            }
            //Check if the point is the bottom right corner.
            if (i == rows - 1 && j == columns-1) {
                arrayTemp[i][j] = (bottom + right)/2;
            }
            //Check if the point is the top left corner.
            if (i==0 && j==0) {
                arrayTemp[i][j] = (top + left)/2;
            }
            //Check if the point is the top right corner.
            if (i==0 && j==columns-1) {
                arrayTemp[i][j] = (top + right)/2;
            }
        }
    }

    //Output the array to the user.
    cout << "\nUser entered plate grid:\n";
    for (int i=0; i < rows;i++) {
        for (int j=0;j < columns;j++) {
            //setw() is a manipulator that sets field width.
            //Output the float value.
            cout <<setw(10)<<arrayTemp[i][j];
        }
    }
}

void equalizeGrid(double arrayTemp[NROWS][NCOLS],int rows,int columns,
                  double tolerance) {

    //Initialize the counter,iteration,avg and check vector.
    int counter,iteration=0;
    double avg;
    double check[35][20];

    //Keep running until all squares in grid reach equilibrium.
    do
    {
        //Only run for the internal squares not external ones.
        for (int i = 1;i < rows-1;i++){
            for (int j = 1; j < columns-1; j++) {

                //Calculate the average for the squares above,below,left,right
                //of the current square.
                avg = (arrayTemp[i-1][j]+arrayTemp[i+1][j]
                              +arrayTemp[i][j-1]+arrayTemp[i][j+1])/4.0;

                //If the absolute value (fabs()) of average - current square
                //is less than the tolerance, make check = 1.
                if (fabs(avg - arrayTemp[i][j])<tolerance) {
                    check[i][j] = 1;
                }
                //Until check is 1, keep using the re-calculated average as
                //square.
                if (check[i][j] != 1) {
                    arrayTemp[i][j] = avg;
                }
            }
        }

        //Increment iteration.
        iteration++;

        //Check if all the squares finally reached acceptable equilibrium.
        counter = 0;
        for (int i=1;i<rows-1;i++) {
            for (int j=1;j<columns-1;j++) {
                if (check[i][j]==1) {
                    counter++;
                }
            }
        }
    }
    while (counter < ((rows-2)*(columns-2)));

    //Output the final equilibrium state.
    cout << "\nPlate grid at equilibrium temperatures:\n";
    for (int i = 0;i<rows;i++) {
        for (int j=0;j<columns;j++) {
            //setw() is a manipulator that sets field width.
            //Output the float value.
            cout<<setw(10)<<arrayTemp[i][j];
        }
    }

    //Output the number of iterations required to reach equilibrium.
    cout << "\nThe plate reached equilibrium after " <<(iteration+1)
    <<" iterations."<<endl;
}
