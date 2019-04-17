#include <iostream> 
#include <fstream> 
#include <string> 
#include <math.h>
using namespace std;

int main () {
	
//Opens file A.txt for read purposes.
ifstream A ("A.txt");        
//If A.txt is not opened, prints an error message.
if (A.is_open()==0){
	cout << "Matrix A could not be opened."; 
	return 3;
}
//Creates the string line and in order to find the dimension of the matrix A -therefore the vector b- stored by integer n.
string line;
int n = 0;
while (getline(A, line)){
	n++;
}
//After finding the dimension, sets the cursor to the beginning.
A.clear();
A.seekg(0, ios::beg);

//Creates a dynamically allocated matrix storedA with dimensions nxn.
double** storedA = new double*[n];
for(int i = 0; i < n; i++)
storedA[i] = new double[n];
//Writes the contents of A.txt into the 2D array that will be used throughout the program.
for(int i = 0; i < n; i++){
	for(int j = 0; j < n; j++){
		A >> storedA[i][j];
	}
}
//Closes A.txt.
A.close();

//Opens file b.txt for read purposes.
ifstream b ("b.txt");
//If b.txt is no opened, prints an error message.
if (b.is_open()==0){
	cout << "Vector b could not be opened.";
	return 3;
}

//Creates a dynamically allocated vector b  with dimensions nx1.
double* storedb = new double[n];
//Writes the contents of b.txt into the 1D array that will be used throughout the program.
for(int i = 0; i < n; i++){
	b >> storedb[i];
}
//Closes b.txt.
b.close();

//This grand if statement finds and prints out the condition numbers at one and infinity for matrices A with dimensions 2x2.
if(n == 2){
	//Variable cond1 is the condition number at one, and condinf is the condition number at infinity.
	double cond1, condinf;
	//detA2x2 is the determinant of 2x2 matrix, in order to be able to find the inverse. 
	double detA2x2 = storedA[0][0] * storedA[1][1] - storedA[0][1] * storedA[1][0];
	
	//Creates the dynamically allocated inverse matrix invA2x2, since it will be used while computing the condition numbers.
	double** invA2x2 = new double*[2];
	for(int i = 0; i < 2; i++)
	invA2x2[i] = new double[2];
	//Sets the elements of inverse matrix same as the original, only for initialization.
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			invA2x2[i][j] = storedA[i][j];
		}
	}
	
	//Finds the inverse of matrix A. 
	double temp;
	temp = invA2x2[0][0];
	invA2x2[0][0] = invA2x2[1][1] / detA2x2;
	invA2x2[0][1] = -invA2x2[0][1] / detA2x2;
	invA2x2[1][0] = -invA2x2[1][0] / detA2x2;
	invA2x2[1][1] = temp / detA2x2;

	//The variables under this row and the for loop finds the condition number at one.
	double maxcolA, maxcolinvA, sumcolA, sumcolinvA = 0;
	for(int i = 0; i < 2; ++i){
		sumcolA = 0;
		sumcolinvA = 0;
		//This for loop finds column sums for both matrix A and its inverse.
		for (int j = 0; j < 2; ++j){
  		    	sumcolA = sumcolA +  fabs(storedA[j][i]);
  		   	sumcolinvA = sumcolinvA + fabs(invA2x2[j][i]);
		}
		//This if statement finds the maximum column sum of A.
		if (sumcolA > maxcolA){
			maxcolA = sumcolA;
		}
		//This if statement finds the maximum column sum of inverse of A.
    		if (sumcolinvA > maxcolinvA){
		     	maxcolinvA = sumcolinvA;
  		}	
	}
	//Condition number at one is the product of maximum column sum of A and its inverse's.
	cond1 = maxcolA * maxcolinvA;
	//Prints out the condition number at one.
	cout << "Condition number at one is: " << cond1 << "\n";

	//The variables under this row and the for loop finds the condition number at infinity.
	double maxrowA, maxrowinvA, sumrowA, sumrowinvA = 0;
	for(int i = 0; i < 2; ++i){
		sumrowA = 0;
		sumrowinvA = 0;
		//This for loop finds row sums for both matrix A and its inverse.
		for (int j = 0; j < 2; ++j){
  		    	sumrowA = sumrowA +  fabs(storedA[i][j]);
  		    	sumrowinvA = sumrowinvA + fabs(invA2x2[i][j]);
		}
		//This if statement finds the maximum row sum of A.
		if (sumrowA > maxrowA){
			maxrowA = sumrowA;
		}
		//This if statement finds the maximum row sum of inverse of A.		
  	  	if (sumrowinvA > maxrowinvA){
 		     	maxrowinvA = sumrowinvA;
  	  	}
	}
	//Condition number at infinity is the product of maximum row sum of A and its inverse's.
	condinf = maxrowA * maxrowinvA;
	//Prints out the condition number at infinity.
	cout << "Condition number at infinity is: " << condinf << "\n" ;
}
//Partial pivoting begins here.
double compA, tempA, tempb, factorA;
//This grand for loop turns matrix A into upper triangular form, using partial pivoting.
for(int i = 0; i < n; i++){
	//Initializes maximum value of pivot, compA and its index, q.
      compA = storedA[i][i];
      int q = i;
      	//This for loop compares each pivot candidate and finds the maximum of them, which becomes compA.
            for(int j = i + 1; j < n; j++)
      	      if(fabs(compA) < fabs(storedA[j][i])){
      			compA = storedA[j][i] ;
            		q = j;
           		}
	//This if statement checks if A is singular and if so, quits.
	//Matrix A is singular if a principal diagonalelement is equal to zero.
	//For machine precision, 10^-(-5) is picked. The values smaller than this number are considered to be zero.
	if(fabs(compA) < 0.00001){ 
		cout << "A is singular.";
		return 3;
	}
	//Swaps the maximum row with the current row for A.
	for(int k = 0; k < n; k++)
      {
            tempA = storedA[q][k];
            storedA[q][k] = storedA[i][k];
            storedA[i][k] = tempA;       
      }
      //Swaps the same rows of b.
      tempb = storedb[q];
      storedb[q] = storedb[i];
      storedb[i] = tempb;
	//Turns A into an upper triangular matrix.
      for(int l = i+1; l < n; l++){
            //factorA sets the l'th element of A equal to zero.
		factorA = storedA[l][i]/storedA[i][i];
            storedb[l] = storedb[l] - factorA * storedb[i];
            //This part sets the elements under the diagonal equal to zero.
            for(int m = 0; m < n; m++){
            	storedA[l][m] = storedA[l][m] - factorA * storedA[i][m];
 			if(fabs(storedA[l][m]) < 0.00001)
 				storedA[l][m] = 0;
 		}
      }
}
//Creates solution vector x with dimensions nx1.
double x[n];
//Starts from bottom for backward substitution.
for(int i = n-1; i >= 0; i--){
	//Sets i'th element of x is equal to the i'th element of b divided by the i'th element of A. 
	x[i] = storedb[i] / storedA[i][i];
	//Substracts the product of x[i] and storedA[j][i] from storedb[j] and finds the solution vector x.
	for(int j = 0; j < i; j++){
		storedb[j] = storedb[j] - storedA[j][i]*x[i];
	}
}
//Prints out the solution vector x.
cout << "The solution vector x is: \n";
for (int i = 0; i < n; i++){
	cout << x[i] << "\n";
}
//Creates text file x.txt.
ofstream outx ("x.txt");
//Prints out an error message if there is a problem with creating x.txt.
if (outx.is_open()==0){
	cout << "File x could not be created."; 
	return 3;	
}
//Writes the contents of vector x into text file x.txt.
for (int i = 0; i < n; i++){
	outx << x[i] << "\n";
}
return 0;
}


