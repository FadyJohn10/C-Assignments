#include <iostream>
#include <cmath>
using namespace std;

#define DIM 3
#define SLOTS 8
#define MAX 9999
class BSC;
class BTS;

class MS {
private:
  int ID;
  double pos[DIM];
  static int MSNum;
  bool isConnected;

public:
  BTS *connectedBTS;
  BSC *connectedBSC;
  MS() { //default constructor
    MSNum++;
    ID = MSNum;
    pos[0] = pos[1] = pos[2] = 0;
    isConnected = false;
  }
  MS(double x, double y, double z) { //non default constructor
    MSNum++;
    ID = MSNum;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    isConnected = false;
  }
  // getter functions
  int getID() { return ID; }
  double *getPosition() { return pos; }
  bool connectionStat() { return isConnected; }
  BTS *getConnectedBTS() { return connectedBTS; }
  BSC *getConnectedBSC() { return connectedBSC; }
  static int getMSNum() { return MSNum; }
  // setter functions
  void setPosition(double x, double y, double z) {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }
  void setConnectionStat(bool value) { isConnected = value; }
  void move(double x, double y, double z, BSC BSCobject); //function prototype
  void updateActiveBTS(BSC BSCobject); //function prototype
  ~MS(){} //class destructor
};
int MS::MSNum = 0; //assigning the value of the static variable to 0

class BTS {
private:
  int ID;
  double pos[DIM];
  MS *timeSlotsArray[SLOTS];
  int MSNumConnected;
  static int BTSNum;

public:
  BTS() { //default constructor
    BTSNum++;
    ID = BTSNum;
    pos[0] = pos[1] = pos[2] = 0;
  }
  BTS(double x, double y, double z) { //non default constructor
    BTSNum++;
    ID = BTSNum;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }
  // getter functions
  int getID() { return ID; }
  int getMSNumConnected() { return MSNumConnected; }
  double *getPosition() { return pos; }
  static int getBTSNum() { return BTSNum; }

  // setter functions
  void setPosition(double x, double y, double z) {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }
  // functions
  void joinBTS(MS *MSobject) { // function to connect MS to BTS
    if (MSNumConnected < SLOTS) { // check if there is a free time slot to add MS in
      timeSlotsArray[MSNumConnected] = MSobject; 
      MSobject->connectedBTS = this;
      MSobject->setConnectionStat(true); //change the connection status of the MS to true
      MSNumConnected++;
      cout << "Update: MS" << MSobject->getID() << " is connected to BTS" << this->getID()
           << endl;
    } else
      cout << "Can't add more MSs, all slots are occupied" << endl;
  }
  void leaveBTS(MS *MSobject) { //function to disconnect MS from BTS
    bool isFound = false;
    for (int i = 0; i < MSNumConnected; i++) {
      if (timeSlotsArray[i] == MSobject) { //find targeted MS
        for (int j = i; j < MSNumConnected; j++) {
          timeSlotsArray[j] = timeSlotsArray[j + 1]; //shift the time slots so the targeted MS will be removed
        }
        MSNumConnected--;
        isFound = true;
      }
    }
    if (isFound == false)
      cout << "Can't find the MS to remove" << endl;
    else
      cout << "Update: MS" << MSobject->getID() << " left BTS" << this->getID() << endl;
  }
  void displayTimeSlotsArray() { // function to show time slots which are occupied and which are available at any time
    cout << endl<< "BTS" << this->getID() << " time slots array: " << endl;
    for (int i = 0; i < SLOTS; i++) { //loop through the entire time slots array
      if (i < MSNumConnected) { // looping through indices < MSNumConnected means that this time slot is occupied
        cout << "Time slot " << i + 1 << " is ocuppied by MS"
             << timeSlotsArray[i]->getID() << endl;
      } else {
        cout << "Time slot " << i + 1 << " is not ocuppied" << endl;
      }
    }
  }
  void BTSInfo() { //function to display some info about the BTS
    cout << "BTS" << this->getID()<< " located at (" << this->getPosition()[0]
         << ", " << this->getPosition()[1] << ", " << this->getPosition()[2] << ") Includes " << this->getMSNumConnected()<< " MSs" << endl;
  }
  ~BTS() {}
};
int BTS::BTSNum = 0; //assigning the value of the static variable to 0

class BSC {
private:
  int addedBTS;
  BTS *BTSs[MAX];

public:
  BSC() {
    addedBTS = 0;
  }
  BTS **getBTSsARR() { return BTSs; }
  void addBTS(BTS *newBTS) { //function to add BTS to BSC
    BTSs[addedBTS] = newBTS;
    addedBTS++;
  }
  void print() { //function to print info about BSC and included BTSs
    cout << endl<< "This BSC contains " << addedBTS << " BTSs:" << endl;
    for (int i = 0; i < addedBTS; i++) {
      BTSs[i]->BTSInfo();
    }
  }
  int checkNearestBTS(MS *MSobject) { // function to check the nearest BTS from MS
    double distance, minDistance = 10000000.0;
    int index;

    for (int i = 0; i < addedBTS; i++) {
      if (BTSs[i]->getMSNumConnected() >= 8) { // check if the all the time slots in a BTS are occupied, the function will skip this BTS
        continue;
      }
      distance = sqrt(pow(MSobject->getPosition()[0] - BTSs[i]->getPosition()[0], 2) +
                  pow(MSobject->getPosition()[1] - BTSs[i]->getPosition()[1], 2) +
                  pow(MSobject->getPosition()[2] - BTSs[i]->getPosition()[2], 2));
      if (distance < minDistance) {
        minDistance = distance;
        index = i; // index of the nearest BTS
      }
    }
    return index;
  }
  ~BSC(){} //class destructor
};

void MS::move(double x, double y, double z, BSC BSCobject) { //function to move MS and connect it to the nearest BTS
  pos[0] = x;
  pos[1] = y;
  pos[2] = z;
  if (this->connectionStat() == true) { // check if the MS is connected, then disconnect it
    this->getConnectedBTS()->leaveBTS(this);
  }
  this->updateActiveBTS(BSCobject); // search for the nearest BTS
}
void MS::updateActiveBTS(BSC BSCobject) {
  int index = BSCobject.checkNearestBTS(this); // get the index of the nearest BTS
  BSCobject.getBTSsARR()[index]->joinBTS(this); // connect to the nearest BTS
}

int main() {
  BSC BSC1;
  BTS *bts1 = new BTS(1, 1, 1);
  BTS *bts2 = new BTS(7, 7, 7);
  BTS *bts3 = new BTS(10, 10, 10);
  BSC1.addBTS(bts1);
  BSC1.addBTS(bts2);
  BSC1.addBTS(bts3);
  MS *ms1 = new MS;
  MS *ms2 = new MS(1, 2, 3);
  MS *ms3 = new MS(3, 2, 3);
  MS *ms4 = new MS(1, 0, 3);
  MS *ms5 = new MS(0, 2, 0);
  MS *ms6 = new MS(2, 2, -1);
  MS *ms7 = new MS(3, -3, -2);
  MS *ms8 = new MS(2, 2, 0);
  MS *ms9 = new MS(1, 2, 4);
  MS *ms10 = new MS(8, 8, 6);

  ms1->updateActiveBTS(BSC1);
  ms2->updateActiveBTS(BSC1);
  ms3->updateActiveBTS(BSC1);
  ms4->updateActiveBTS(BSC1);
  ms5->updateActiveBTS(BSC1);
  ms6->updateActiveBTS(BSC1);
  ms7->updateActiveBTS(BSC1);
  ms8->updateActiveBTS(BSC1);
  ms9->updateActiveBTS(BSC1);
  ms10->updateActiveBTS(BSC1);
  ms10->move(11, 12, 13, BSC1);
  bts1->displayTimeSlotsArray();
  bts2->displayTimeSlotsArray();
  bts3->displayTimeSlotsArray();

  BSC1.print();
  
  delete bts1;
  delete bts2;
  delete bts3;
  delete ms1;
  delete ms2;
  delete ms3;
  delete ms4;
  delete ms5;
  delete ms6;
  delete ms7;
  delete ms8;
  delete ms9;
  delete ms10;

  return 0;
}
