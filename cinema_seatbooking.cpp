#include<iostream>
#include<conio.h>
#include<vector>

#define RECLINER 320
#define ROYAL 220
#define EXECUTIVE 170

const int rows = 7;
const int cols = 11;
int posX = 0;
int posY = 0;
int total=0;
int flag;
using namespace std;

class Seat{
public:
    int selectedX;
    int selectedY;
    int isSelected=0;
    void reset(){isSelected=0;}

}s;
vector<Seat> selected_seats;

 vector<vector<string>> a={{"[ A1 ]","[ A2 ]","  ","[ A3 ]","[ A4 ]","  ","[ A5 ]","[ A6 ]","  ","[ A7 ]","[ A8 ]"},
                    {"[ B1 ]","[ B2 ]","  ","[ B3 ]","[ B4 ]","  ","[ B5 ]","[ B6 ]","  ","[ B7 ]","[ B8 ]"},
                    {"[ C1 ]","[ C2 ]","  ","[ C3 ]","[ C4 ]","  ","[ C5 ]","[ C6 ]","  ","[ C7 ]","[ C8 ]"},
                    {"[ D1 ]","[ D2 ]","  ","[ D3 ]","[ D4 ]","  ","[ D5 ]","[ D6 ]","  ","[ D7 ]","[ D8 ]"},
                    {"[ E1 ]","[ E2 ]","  ","[ E3 ]","[ E4 ]","  ","[ E5 ]","[ E6 ]","  ","[ E7 ]","[ E8 ]"},
                    {"[ F1 ]","[ F2 ]","  ","[ F3 ]","[ F4 ]","  ","[ F5 ]","[ F6 ]","  ","[ F7 ]","[ F8 ]"},
                    {"[ G1 ]","[ G2 ]","  ","[ G3 ]","[ G4 ]","  ","[ G5 ]","[ G6 ]","  ","[ G7 ]","[ G8 ]"}

    };

void displayMatrix() {
    system("cls");  // Clears the console screen

    for (int i = 0; i < rows; ++i) {
            if(i==0)
            cout<<"\t\tROYAL RECLINERS Rs."<<RECLINER<<"\n\n";
            else if(i==1)
            cout<<"\n\t\t   ROYAL Rs."<<ROYAL<<"\n";
            else if(i==6)
            cout<<"\n\t\tEXECUTIVE Rs."<<EXECUTIVE<<"\n";

        for (int j = 0; j < cols; ++j) {
            if (i == posY && j == posX) {
                cout << "\33[100m\33[7m"<<a[i][j]<<"\33[0m";  // Display the current position
            }
            else {
                    flag=0;
                for(int k=0;k<selected_seats.size();k++){
                        if(selected_seats[k].isSelected){
                            if(selected_seats[k].selectedY==i &&selected_seats[k].selectedX==j){
                            cout <<"\33[7m"<<a[i][j]<<"\33[0m";
                            flag=1;
                            break;
                        }
                    }
                }
                    if(flag==1)
                        continue;
                cout <<a[i][j];
            }
        }
        cout << endl;
    }
        cout<<"\n\n----------------------SCREEN HERE---------------------";
}

// Function to replace the entire content of array2 in array1 with "1"
void replaceElements(const  vector< string>& array2) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            for (const auto& element : array2) {
                if (a[i][j] == "[ "+element+" ]") {
                    a[i][j] = "[    ]";
                }
            }
        }
    }
}

string removeCharacters(const string& input, const string& charsToRemove) {
    string result;

    for (char ch : input) {
        if (charsToRemove.find(ch) == string::npos) {
            // If the character is not in charsToRemove, add it to the result string
            result += ch;
        }
    }
    return result.substr(0, result.length() - 1);;
}

string seat_map(vector<string>& r, int n){

    string t;
    posX=posY=total=0;
    flag;

    //to remove the booked seats from default seat map
    replaceElements(r);
    char key;
    int count=0;
    do {
        flag=0;
        displayMatrix();
        key = _getch();  // Use _getch() to get a key

        switch (key) {
            case 72:  // Up arrow key
                if (posY > 0) {
                    posY--;
                }
                break;
            case 80:  // Down arrow key
                if (posY < rows - 1) {
                    posY++;
                }
                break;
            case 75:  // Left arrow key
                if (posX > 0) {
                    posX--;
                }
                if(posX==2||posX==5 || posX==8)
                    posX--;
                break;
            case 77:  // Right arrow key
                if (posX < cols - 1) {
                    posX++;
                }
                if(posX==2||posX==5 || posX==8)
                    posX++;
                break;
            case 13:  // enter key
                if(a[posY][posX]!="[    ]"){
                        for(int i=0;i<selected_seats.size();i++){
                                if(selected_seats[i].selectedX==posX && selected_seats[i].selectedY==posY){
                                        selected_seats.erase(selected_seats.begin()-i);
                                        --count;
                                    flag=1;
                            }
                        }
                        if(flag==1)
                            break;

                    s.selectedX=posX;
                    s.selectedY=posY;
                    s.isSelected=1;
                    selected_seats.push_back(s);
                    count++;
                }
                break;
        }

    } while (count!=n);

     for(int i=0;i<n;i++)
        if(selected_seats[i].isSelected){
                int seatIndex1=selected_seats[i].selectedY;
            t.append(a[seatIndex1][selected_seats[i].selectedX]);
            if(seatIndex1==0)
                total+=320;
            else if(seatIndex1>1 && seatIndex1<6)
            total+=220;
            else
                total+=170;
            t.append(",");
        }
        t = removeCharacters(t,"[  ]");
        return t;
}

int main(){

    vector<string> booked_seats={"A1","A2","D4","D5","D6"};

    int seatsToBook = 2;
    string t=seat_map(booked_seats,seatsToBook);

    system("cls");
    cout<<"Booked seats :";
    cout<<t;

    return 0;
}
