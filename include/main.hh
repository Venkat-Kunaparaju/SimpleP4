#include <basic.hh>

#define NUMTHREAD 3
#define MUTEX 1

extern int startUp();
extern int dataplaneMain(); //Dataplane main
extern int controlplaneMain(); //Controlplane main
extern int controlMain(); //Usercontrolplane main

extern pthread_mutex_t writtenToDataplane; //Used by controlplane
extern int doneControlplane; //Used by controlplane
extern pthread_mutex_t readFromDataplane; //Used by controlplane
extern int doneReadControlplane; //Used by controlplanne


extern pthread_mutex_t readFromControlplane; //Used by dataplane
extern int doneDataplane; //Used by dataplane
extern pthread_mutex_t writeToControlplane; //Used by dataplane
extern int doneWriteDataplane; //Used by dataplane

extern char readControlplaneBuffer[BUFFERSIZE]; //Used by dataplane
extern char writeControlplaneBuffer[BUFFERSIZE]; //Used by dataplane

extern char writeDataplaneBuffer[BUFFERSIZE]; //Used by controlplane
extern char readDataplaneBuffer[BUFFERSIZE]; //Used by controlplane

extern struct ctrl control; //Used for interface between user and control plane

/* Switchboard functions */
int dummyFunc();
int threadinit();
int init();
int testFunc();
int main();
int controlToData();
int dataToControl();
int simplep4ToData();





