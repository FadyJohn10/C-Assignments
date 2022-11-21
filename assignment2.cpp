#include<bits/stdc++.h> 
using namespace std;

int maxArrNumber(int **arr, int cols, int rows){ //function to get the largest value of the image array
  int max_num = arr[0][0];
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(arr[i][j] > max_num)
        max_num = arr[i][j];
    }
  }
  return max_num;
}

void makeGlcmArray(int **arr, int **glcm, int cols, int rows){ //function to assign values to GLCM array
  for(int i=0; i<rows; i++){
      for(int j=0; j<cols-1; j++){
          int x = arr[i][j], y=arr[i][j+1]; // assign image[i][j] element to x and the next horizontally element to y
          glcm[x][y]++;  // go to index x,y in GLCM array and increase its value by 1
      }
    }
}

void normalizedGlcmArr(double **normalizedglcm, int **glcm, int maxn){ //function to assign values to Normalized GLCM array
  double sum=0;
  for(int i=0; i <= maxn; i++){ // finding the sum of values of GLCM array
    for(int j=0; j <= maxn; j++)
        sum += glcm[i][j];
  }
  for(int i=0; i <= maxn; i++){
    for(int j=0; j <= maxn; j++)
        normalizedglcm[i][j] = glcm[i][j]/sum;
    }
}

void CalcContrast(double **normalizedglcm, int maxn){ //function to calculate contrast
  double contrast = 0;
  for(int i=0; i <= maxn; i++){
    for(int j=0; j <= maxn; j++){
        contrast += pow(abs(i-j) , 2) * normalizedglcm[i][j];
    }
  }
  cout << "Contrast: " << contrast << endl;
}
void CalcEnergy(double **normalizedglcm, int maxn){ //function to calculate energy
  double energy = 0;
  for(int i=0; i <= maxn; i++){
    for(int j=0; j <= maxn; j++){
        energy += pow(normalizedglcm[i][j], 2);
    }
  }
  cout << "Energy: " <<energy << endl;
}
void CalcHomogeneity(double **normalizedglcm, int maxn){ //function to calculate homogeneity
  double homogeneity = 0;
  for(int i=0; i <= maxn; i++){
    for(int j=0; j <= maxn; j++){
        homogeneity +=  normalizedglcm[i][j] / (1 + pow(abs(i-j) , 2));
    }
  }
  cout << "Homogeneity: " << homogeneity << endl;
}

int main() {
  // declaring global variables
  int choice, **arr, max, **glcm, colcount, rowcount;
  double **normalizedglcm;
  bool flag = true;

  menu: // menu section
  cout<<"choose an option:\n" << "1) Create and normalize the GLCM matrix\n" << "2) Compute the statistical parameters of the texture\n" << "3) Print the GLCM matrix\n" << "4) Exit theprogram\n";
  cout<<"Your choice is: ";
  cin>>choice;
  
  if(choice==1){ //creating, normalizing GLCM Matrix, and printing it if user's choice is 1
  //  opening image file input and check
  string filename;
  cout<<"Type the image file name with extension: ";
  cin>>filename;
  ifstream fin(filename);
  if (fin.fail()) { // check file open
     cerr << "could not open input file\n";
     goto menu;
  } 
  fin >> colcount >> rowcount;
  //creating a dynamic 2D array for image values in the text file
  arr = new int *[rowcount];
  for (int i = 0; i < rowcount; ++i) {
      arr[i] = new int[colcount];
  }
  for (int i = 0; i < rowcount; ++i) {
      for (int j = 0; j < colcount; ++j) {
          fin >> arr[i][j];
      }
  }
  max = maxArrNumber(arr, colcount, rowcount);
  // Creating GLCM 2D dynamic array its dimensions are the maximum value in image array
  glcm = new int *[max];
    for (int i = 0; i <= max; i++) {
        glcm[i] = new int[max];
  }
    makeGlcmArray(arr, glcm, colcount, rowcount);
    // Creating normalized GLCM 2D dynamic array
    normalizedglcm = new double *[max];
    for (int i = 0; i <= max; i++) {
        normalizedglcm[i] = new double[max];
    }
    normalizedGlcmArr(normalizedglcm, glcm, max);
    cout<< "GLCM Array created and normalized \n"; 
  flag = false;
  goto menu;
  }
  else if(choice == 2){ // Computing and printing the statistical parameters of the texture if user's choice is 2
    if(flag){ // to check that the user made the GLCM array first (option 1 was chosen first)
      cout << "You should create the GLCM matrix first\n";
      goto menu;
    }
    
    normalizedGlcmArr(normalizedglcm, glcm, max);
    //Statistical parameters of the texture
    CalcContrast(normalizedglcm, max);
    CalcEnergy(normalizedglcm, max);
    CalcHomogeneity(normalizedglcm, max);
    goto menu;
  }
  else if(choice == 3){ //Printing GLCM Array if user's choice is 3
    if(flag){ // to check that the user made the GLCM array first (option 1 was chosen first)
      cout << "you should create the GLCM matrix first\n";
      goto menu;
    }
    cout << endl << "GLCM Array: \n";
    for (int i = 0; i <= max; ++i) {
        for (int j = 0; j <= max; ++j) {
            cout << glcm[i][j] <<" ";
        }
        cout<<endl;
    }
    goto menu;
  }else if(choice == 4){ // Exitting the program
    cout<<"Thanks for using this Program..!";
  }else{ // check if the user's input is invalid, the program displays menu
    cout<<"Invalid option...\n";
    goto menu;
  }
  //Deallocating image and GLCM 2D dynamic arrays
  for (int i=0; i<rowcount; i++)
      delete[] arr[i];
  delete [] arr;
  for (int i=0; i<max; i++){
      delete[] glcm[i];
  }
  delete [] glcm;
  for (int i=0; i<max; i++){
      delete[] normalizedglcm[i];
    }
  delete [] normalizedglcm;
  return 0;
}