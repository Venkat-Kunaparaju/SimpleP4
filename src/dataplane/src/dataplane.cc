
#include <dataplane.hh>



/*
Use vectors to represent the header fields. Global variable that is a pointer to the current header vector. 
Header vector gets updated, and pointer updated to point to header vector whenever change happens. 
*/


/* Temp function to figure out mapping of fields */
int dummyStart() {

    /* Testing values */
    std::string tempHeader[] = {"IP Src", "IP Dest", "Port Src", "Port Dest", "Protocol"};
    int tempHeaderMetadata[] = {32, 32, 16, 16, 8};

    std::string tempMetadata[] = {"Ingress Port", "Egress Port"};
    std::string tempActions[] = {"Drop", "Forward"};

    int tempLengthHeader = tempHeader->length();
    int tempLengthPerm = tempMetadata->length();

    /* Populate initial field values */
    for (int i = 0; i < tempLengthHeader; i++) {
        header.push_back(tempHeader[i]);
        headerMetadata.push_back(tempHeaderMetadata[i]);
    }
    /* Populate perm values */
    for (int i = 0; i < tempLengthPerm; i++) {
        metadata.push_back(tempMetadata[i]);
        actions.push_back(tempActions[i]);
    }

    /* Initial pipeline  */
    simplePipeline = new struct pipeline;

    
    /* Testing values */
    std::string tempExactFields[3][3];
    tempExactFields[0][0] = "IP Src";
    tempExactFields[0][1] = "IP Dest";
    tempExactFields[1][0] = "Port Src";
    tempExactFields[1][1] = "Port Dest";
    tempExactFields[2][0] = "IP Src";
    tempExactFields[2][1] = "Protocol";



    /* Initialize the 3 tables */
    for (int i = 0; i < 3; i++) {
        struct table * temp = new struct table;
        simplePipeline->tableVect.push_back(temp);
        //fprintf(stderr, "SUCESS\n");
        simplePipeline->tableVect[i]->exactFields.push_back(tempExactFields[i][0]);
        simplePipeline->tableVect[i]->exactFields.push_back(tempExactFields[i][1]);
    }

    /* Test if exactfields are valid fields */
    int check = 0;
    for (int i = 0; i < simplePipeline->tableVect.size(); i++) {
        for (int x = 0; x < simplePipeline->tableVect[i]->exactFields.size(); x++) {
            for (int y = 0; y < tempLengthHeader; y++) {
                if (tempHeader[y].compare(simplePipeline->tableVect[i]->exactFields[x]) == 0) {
                    check = 1;
                    break;
                }
            }
            if (check == 0) {
                fprintf(stderr, "Invalid field found asl\n");
            }
            check = 0;
        }
    }

    fprintf(stderr, "Finished Test\n");

    return 1;


}

/*
Used to update dataplane configuration based on specified changes in simplep4 program
Check for valid data done in compiler
Return: 1 on sucess and population of respective fields
*/
int population() {
    std::cout << "POPULATION\n";
    return 1;
}
/*
 Set up initial config and poll in startup state until simpleP4 program compiled 
Return: 1 once done polling
*/
int startUp() {
    //dummyStart();
    pthread_mutex_lock(&readFromControlplane); //Poll until writtenToDataplane is 1
    population();
    pthread_mutex_unlock(&readFromControlplane); //Reset value to 0 once done reading
    return 1;
}
int dataplaneMain() {
    std::cout << "DATAPLANE\n";
    startUp();
    return 0;
}