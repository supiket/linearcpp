This program takes two input text files A.txt and b.txt, prints out the solution vector x to the linear system Ax = b and writes it into text file x.txt. 
A.txt should contain a nxn matrix with spaces in between each column and a new line starting for each row. 
b.txt should contain a nx1 vector. It is important that the row number of b and A should be the same. 
Otherwise, the program may crash.
The elements of A and b can be integers or floating numbers. 
Solution x is calculated by Gaussian elimination with partial pivoting. 
Prints out error mesagges if A.txt or b.txt cannot be opened or x.txt cannot be created.
For checking the singularity condition of matrix A, machine precision is taken to be 10^(-5), the values smaller than machine precision are considered to be equal to zero.
If matrix A is singular, the solution cannot be calculated and the program prints our an error message.
In addition, if matrix A is 2x2, the condition numbers at 1 and infinity are calculated. 
Condition number of a matrix at 1 is the product of maximum absolute column sums of the absolute value of elements of A and its inverse's. 
Condition number of a matrix at infinity is the product of the maximum absolute row sums of the absolute value of elements of A and its inverse's. 
If the condition number is high, it means that a slight change in the input causes a great change in output, therefore the system is sensitive / ill-conditioned.

