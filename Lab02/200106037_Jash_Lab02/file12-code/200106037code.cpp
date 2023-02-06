// Author: Jash Kalpesh Desai 
// Roll No: 200106037

// Date: 24.01.2023 (Tuesday)

// Course: BT305 - Computational Biology
// Lab Number: 02

// Description: This program reads the coordinates of all the atoms in a protein from a file and finds the central atom of the protein. It then reads the file that contains all the information regarding the atoms in the protein and prints the information regarding the central atom from the Protein Data Bank (PDB) file.

// Logic: The program first reads the coordinates of all the atoms in the protein from a file and stores them in three vectors - x, y and z. It then calculates the theoritical mean of the coordinates and finds the atom that is closest to this theoritical mean. It then reads the file that contains all the information regarding the atoms in the protein and prints the information regarding the central atom from the Protein Data Bank (PDB) file.

// Input: input00.txt, input01.txt
// Output: Central atom details from the PDB file

#include <bits/stdc++.h>
using namespace std;

// function to calculate the distance between two points in 3D space with respective x, y and z coordinates
float distance(float x1, float y1, float z1, float x2, float y2, float z2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

int main(){
    // reading the input file that contains the coordinates of all the atoms in our protein - input00.txt
    ifstream inputCoordinatesFile("input00.txt"); 

    // vector to store the x, y and z coordinates of all the atoms in our protein 
    vector<float> x,y,z;

    // sum of all the x, y and z coordinates of all the atoms in our protein
    float xSum=0; float ySum=0; float zSum=0;

    // reading the coordinates of all the atoms in our protein and storing them in the vectors x, y and z
    while(!inputCoordinatesFile.eof()){
        float a,b,c;
        inputCoordinatesFile >> a >> b >> c;
        // cout << a << " " << b << " " << c << '\n';
        x.push_back(a); y.push_back(b); z.push_back(c);
        xSum+=a; ySum+=b; zSum+=c;
    }

    // calculating the total number of atoms in our protein
    int numOfAtoms =  x.size();

    // checking if the number of atoms in our protein is equal to the number of x, y and z coordinates
    assert(numOfAtoms == y.size() && numOfAtoms == z.size());

    // calculating the mean of the coordinates
    float xMean = xSum/numOfAtoms; 
    float yMean = ySum/numOfAtoms;
    float zMean = zSum/numOfAtoms;

    // declaring the minimum distance variable to keep track
    float minDist = INT_MAX;

    // finding the central atom
    float xCoordinate=0; float yCoordinate=0; float zCoordinate=0;

    // iterating over all the atoms in our protein
    for(int protein_i=0; protein_i<numOfAtoms; protein_i++){
        // distance between current coordinate and the mean coordinate
        float currentDist = distance(xMean, yMean, zMean, x[protein_i], y[protein_i], z[protein_i]);

        // updating the minimum distance and the central atom coordinates if the current distance is less than the minimum distance
        if(currentDist<minDist){
            xCoordinate=x[protein_i];
            yCoordinate=y[protein_i];
            zCoordinate=z[protein_i];
            minDist=currentDist;
        }
    }

    // printing the central atom coordinates
    cout << "Central atom coordinates: " << xCoordinate << " " << yCoordinate << " " << zCoordinate << '\n';

    // declaring iterator to find the position of the central atom in the vector x
    auto itr = find(x.begin(), x.end(), xCoordinate);

    // storing position of the central atom as an integer
    int centralAtomNumber = itr - (x.begin());

    // reading the file that contains all the information regarding atoms in our protein
    ifstream inputAtomFile("input01.txt");

    // declaring currentAtomNumber to keep track of current atom in the file
    int currentAtomNumber=1;

    // declaring atomDescription to store the description of the central atom
    string atomDescription;

    // iterating over the file until we reach our required atom
    while(!inputAtomFile.eof()){
        // reading the atom description corresponding to the current atom
        getline(inputAtomFile, atomDescription);

        // printing the information regarding the central atom from the Protein Data Bank (PDB) file
        if(currentAtomNumber==centralAtomNumber){  
            cout << "Description of the central-atom corresponding to the PDB file: " << '\n';
            cout << atomDescription << '\n';
        }

        // incrementing the currentAtomNumber
        currentAtomNumber++;
    }
    // closing the input files
    inputCoordinatesFile.close();
    inputAtomFile.close();

    return 0;
}

/* 
Post-Code Analysis and Discussion:
    There can be another way to find the central atom in our protein structure by calculating the distance between all the atoms and storing it in a 2D matrix, then, finding the atom that has the minimum distance from all the other atoms. This is the same method that was discussed in Lab session 02.
    
    This method is more time consuming than the method used in this program. Also, it will require more memory to store the 2D matrix. Hence, the method used in this program is more efficient than the method discussed above.

    Thus, I have used the method used in this program to find the central atom in our protein structure.

    Note 01: The central atom obtained by the method used is same as that obtained by using the Brute-Force Method.

    Note 02: The method used in this program is not the most efficient method to find the central atom in our protein structure. There are other methods that are more efficient than the method used in this program. However, the method used in this program is the most efficient method that I could think of. 
*/
