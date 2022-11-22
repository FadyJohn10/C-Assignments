#include <iostream>
#include <cmath>
using namespace std;

#define DIM 3
#define SLOTS 8
#define MAX 9999
class baseStationController;
class baseTransceiverStation;

class mobileStation{
  private:
    int ID;
    double pos[DIM];
    static int numOfMS;

  public:
  baseTransceiverStation *connectedBTS; 
    mobileStation(){
      numOfMS++;
      ID = numOfMS;
      pos[0]=pos[1]=pos[2]=0;
    }
    mobileStation(double newPos[]) {
        numOfMS++;
        ID = numOfMS;
        pos[0]=newPos[0];
        pos[1]=newPos[1];
        pos[2]=newPos[2];
    }
    //getter functions
    int getID() {
        return ID;
    }
    double *getPosition() {
        return pos;
    }
    baseTransceiverStation *getConnectedBTS(){
        return connectedBTS;
    }
    static int getNumOfMS() {
        return numOfMS;
    }
    //setter functions
    void setPosition(double newPos[]) {
        pos[0] = newPos[0];
        pos[1] = newPos[1];
        pos[2] = newPos[2];
    }
    void move(double x, double y, double z, baseStationController aBSC);

};
int mobileStation::numOfMS=0;

class baseTransceiverStation{
  private:
    int ID;
    double pos[DIM];
    mobileStation *slotsArr[SLOTS];
    int numOfOccSlots;
    static int numOfBTS;
    

  public:
    baseTransceiverStation(){
        numOfBTS++;
        ID = numOfBTS;
        pos[0]=pos[1]=pos[2]=0;
    }
    baseTransceiverStation(double newPos[]) {
        numOfBTS++;
        ID = numOfBTS;
        pos[0]=newPos[0];
        pos[1]=newPos[1];
        pos[2]=newPos[2];
    }
    //getter functions
    void getSlotArr(){
        for(int i=0; i<SLOTS; i++){
            if(i < numOfOccSlots){
                cout<<"Time slot " << i+1 << " is ocuppied by MS"<<slotsArr[i]->getID()<<endl;
            }else{
                cout<<"Time slot " << i+1 << " is not ocuppied"<<endl;
            }
        }
    }
    int getID() {
        return ID;
    }
    int getNumOfOccSlots() {
        return numOfOccSlots;
    }
    double* getPosition() {
        return pos;
    }
    static int getNumOfBTS() {
        return numOfBTS;
    }
    //setter functions
    void setPosition(double newPos[]) {
        pos[0] = newPos[0];
        pos[1] = newPos[1];
        pos[2] = newPos[2];
    }
    //functions
    void joinBTS(mobileStation *newMS) {
        if (numOfOccSlots < SLOTS) {
            slotsArr[numOfOccSlots] = newMS;
            newMS->connectedBTS = this;
            numOfOccSlots++;
        }else
            cout << "Can't add more MSs, all slots are occupied" << endl;
    }
    void leaveBTS(mobileStation *newMS){
        bool isFound = false;
        for(int i=0; i<numOfOccSlots; i++){
            if(newMS == slotsArr[i]){
                for (int j=i; j<numOfOccSlots; j++){
                        slotsArr[j] = slotsArr[j+1];
                    }
                    numOfOccSlots--;
                    isFound = true;
            }
        }
        if(!isFound)
            cout << "Can't find the MS to remove" << endl;
    }

};
int baseTransceiverStation::numOfBTS=0;

class baseStationController{
  private:
    baseTransceiverStation *BTSs[MAX];
    int addedBTS;

  public:
    baseStationController(){
        addedBTS=0;
    }
    void addBTS(baseTransceiverStation *b){
      BTSs[addedBTS] = b;
      addedBTS++;
    }
    void print(){
        cout<<"This BSC contains " << addedBTS << " BTSs:" << endl;
        for(int i=0; i<addedBTS; i++){
            cout<< "BTS" << BTSs[i]->getID()<< " contains " << BTSs[i]->getNumOfOccSlots() << " MSs" << endl;
        }
    }
    void updateActiveBTS(mobileStation *aMS){
      double dist, min=10000000.0;
      int minIndex;
      
      for(int i=0; i<addedBTS; i++){
        if(BTSs[i]->getNumOfOccSlots() >= 8){
            continue;
        }
        dist = sqrt(pow(aMS->getPosition()[0]-BTSs[i]->getPosition()[0],2) 
                    +pow(aMS->getPosition()[1]-BTSs[i]->getPosition()[1],2)
                    +pow(aMS->getPosition()[2]-BTSs[i]->getPosition()[2],2));
        if(dist < min){
            min = dist;
            minIndex = i;

        }
      }
      BTSs[minIndex]->joinBTS(aMS);
    }
};
void mobileStation:: move(double x, double y, double z, baseStationController aBSC){
      pos[0] += x;
      pos[1] += y;
      pos[2] += z;
      aBSC.updateActiveBTS(this);
    }


int main(){
  double btspos[3] = {3, 5, 3};
  double btspos2[3] = {2, 3, 1};
  double btspos3[3] = {0, 0, 1};
  mobileStation *ms1 =  new mobileStation;
  mobileStation *ms2 =  new mobileStation;
  mobileStation *ms3 =  new mobileStation;
  mobileStation *ms4 =  new mobileStation;
  mobileStation *ms5 =  new mobileStation;
  mobileStation *ms6 =  new mobileStation;
  mobileStation *ms7 =  new mobileStation;
  mobileStation *ms8 =  new mobileStation;
  mobileStation *ms9 =  new mobileStation;
  mobileStation *ms10 =  new mobileStation;
  mobileStation *ms11 =  new mobileStation;
  baseTransceiverStation *bts1 = new baseTransceiverStation;
  baseTransceiverStation *bts2 = new baseTransceiverStation;
  baseTransceiverStation *bts3 = new baseTransceiverStation;
  baseStationController BSC1;
  
  BSC1.addBTS(bts1);
  BSC1.addBTS(bts2);
  BSC1.addBTS(bts3);

  bts1->setPosition(btspos);
  bts2->setPosition(btspos2);
  bts3->setPosition(btspos3);
  ms2->setPosition(btspos2);
  bts1->joinBTS(ms2);
  bts1->joinBTS(ms3);
  bts1->joinBTS(ms4);
  bts1->joinBTS(ms5);
  bts1->joinBTS(ms6);
  bts1->joinBTS(ms7);
  bts1->joinBTS(ms8);
  bts1->joinBTS(ms9);

  ms1->move(3.0, 5.0, 2.9, BSC1);
  ms11->move(3.0, 5.0, 3, BSC1);

  bts1->getSlotArr();
  cout<<"hh\n";
  bts2->getSlotArr();
  cout<<"hh\n";
  bts3->getSlotArr();

  cout<<bts1->getNumOfOccSlots()<<endl;

  cout<<(ms3->getConnectedBTS())->getID()<<endl;
  cout<<(ms1->getConnectedBTS())->getID()<<endl;
  cout<<ms11->getConnectedBTS()<<endl;

  BSC1.print();

  delete bts1;
  delete bts2;
  delete bts3;
  delete ms1;
  
  return 0;
}