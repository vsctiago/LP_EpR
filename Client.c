#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Client.h"
#include "LP_Leitura.h"


void createClientsFile(Client clients[]) {
    FILE *pClients = fopen("Clients", "w");
    if (pClients == (FILE*) NULL) {
        printf("Couldn't create Clients File. ");
    } else {
        fwrite(clients, sizeof (Client), CLIENTS_SIZE, pClients);
        fclose(pClients);
    }
}

void saveClientsFile(Client clients[]) {
    FILE *pClients = fopen("Clients", "w");
    if (pClients == (FILE *) NULL) {
        puts("Clients file doesn't exist.");
        puts("Couldn't save Clients file.");
    } else {
        fwrite(clients, sizeof (Client), CLIENTS_SIZE, pClients);
        puts("Clients file saved.");
        fclose(pClients);
    }
}

void readClientsFile(Client *clients) {

    FILE *pClients = fopen("Clients", "r");
    if (pClients == (FILE *) NULL) {
        puts("Clients file doesn't exist");
        puts("Creating Clients file now...");
        createClientsFile(clients);
        puts("Clients file created");
        readClientsFile(clients);
    } else {
        fread(clients, sizeof (Client), CLIENTS_SIZE, pClients);
        fclose(pClients);
    }
}

void createClientCountFile(int *cCount) {
    FILE *pCcount = fopen("ClientCount", "w");
    if (pCcount == (FILE*) NULL) {
        printf("Couldn't create ClientCount File. ");
    } else {
        fwrite(cCount, sizeof (int), 1, pCcount);
        fclose(pCcount);
    }
}

void saveClientCountFile(int *cCount) {
    FILE *pCcount = fopen("ClientCount", "w");
    if (pCcount == (FILE *) NULL) {
        puts("ClientCount file doesn't exist.");
        puts("Couldn't save ClientCount file.");
    } else {
        fwrite(cCount, sizeof (int), 1, pCcount);
        puts("ClientCount file saved.");
        fclose(pCcount);
    }
}

int readClientCountFile(int *cCount) {

    FILE *pCcount = fopen("ClientCount", "r");
    if (pCcount == (FILE *) NULL) {
        puts("ClientCount file doesn't exist");
        puts("Creating ClientCount file now...");
        createClientCountFile(cCount);
        puts("ClientCount file created");
        readClientCountFile(cCount);
    } else {
        fread(cCount, sizeof (int), 1, pCcount);
        fclose(pCcount);
    }
}

void setClientBI(Client *clients, int pos) {
    readLong(&clients[pos].bi, C_BI_MIN, C_BI_MAX, C_MSG_BI);
}

void setClientPassword(Client *clients, int pos) {
    readString(clients[pos].password, C_PASSWORD_LENGTH, C_MSG_PASSWORD);
}

void setClientName(Client *clients, int pos) {
    readString(clients[pos].name, C_NAME_LENGTH, C_MSG_NAME);
}

void setClientCreditCard(Client *clients, int pos) {
    puts("Insert CreditCard:::");
    readLong(&clients[pos].creditCard.bankNumber, C_BANKNUMBER_MIN, C_BANKNUMBER_MAX, C_MSG_BANKNUMBER);
    readLong(&clients[pos].creditCard.accountNumber, C_ACCOUNTNUMBER_MIN, C_ACCOUNTNUMBER_MAX, C_MSG_ACCOUNTNUMBER);
}

void setClientPhoneNumber(long *phoneNumber) {
    bool val = false;
    do {
        readLong(phoneNumber, C_PHONENUMBER_MIN, C_PHONENUMBER_MAX, C_MSG_PHONENUMBER);
        if (*phoneNumber > 960000000 && *phoneNumber < 969999999 ||
                *phoneNumber > 930000000 && *phoneNumber < 939999999 ||
                *phoneNumber > 920000000 && *phoneNumber < 929999999 ||
                *phoneNumber > 910000000 && *phoneNumber < 919999999 ||
                *phoneNumber == 0) {
            val = true;
        } else {
            puts("Error: Number invalid!!");
        }
    } while (val == false);
}

void setClientPhoneNumber1(Client *clients, int pos) {
    do {
        setClientPhoneNumber(&clients[pos].phoneNumber1);
        if(clients[pos].phoneNumber1 == 0)
            printf("Error: Invalid Number - can't be 0!!");
    } while(clients[pos].phoneNumber1 == 0);
}

void setClientPhoneNumber2(Client *clients, int pos) {
    bool val = false;
    do {
        setClientPhoneNumber(&clients[pos].phoneNumber2);
            if (clients[pos].phoneNumber2 == clients[pos].phoneNumber1) {
                puts("Error: Repeated number!!");
            } else {
                val = true;
            }
    } while (val == false);
}

bool verifyIfClientsFull(int *cCount) {
    if (*cCount == CLIENTS_SIZE) {
        puts(C_ERROR_MSG_FULL);
        return true;
    } else {
        return false;
    }
}

int verifyIfClientBIExist(Client *clients, long bi, int *cCount) {
    int pos;
    for (pos = 0; pos<*cCount; pos++) {
        if (clients[pos].bi == bi) {
            return pos;
        }
    }
    return EOF;
}

int loginClient(Client *clients, int *cCount) {
    int pos;
    long tempBI;
    char tempPASS[C_PASSWORD_LENGTH];

    readLong(&tempBI, C_BI_MIN, C_BI_MAX, C_MSG_BI);
    pos = verifyIfClientBIExist(clients, tempBI, cCount);
    if (pos != EOF) {
        readString(tempPASS, C_PASSWORD_LENGTH, C_MSG_PASSWORD);
        if (strcmp(tempPASS, clients[pos].password) == 0) {
            return pos;
        } else {
            puts(C_ERROR_MSG_PASS_WRONG);
            return EOF;
        }
    } else {
        puts(C_ERROR_MSG_BI_NOTFOUND);
        return EOF;
    }
}

void addClient(Client *clients, int *cCount) {
    long cBI;

    if (verifyIfClientsFull(cCount) == false) {
        readLong(&cBI, C_BI_MIN, C_BI_MAX, C_MSG_BI);
        if (verifyIfClientBIExist(clients, cBI, cCount) == EOF) {
            clients[*cCount].bi = cBI;
            setClientPassword(clients, *cCount);
            setClientName(clients, *cCount);
            setClientCreditCard(clients, *cCount);
            setClientPhoneNumber1(clients, *cCount);
            setClientPhoneNumber2(clients, *cCount);
            (*cCount)++;
            saveClientsFile(clients);
            saveClientCountFile(cCount);
        } else {
            puts(C_ERROR_MSG_BI_EXISTS);
        }
    }
}

void editClient(Client *clients, int *cCount) {
    int cBI;
    int pos;

    listClients(clients, cCount);
    readInt(&cBI, C_BI_MIN, C_BI_MAX, "Which Client to Edit(BI): ");
    pos = verifyIfClientBIExist(clients, cBI, cCount);
    if (pos != EOF) {
        setClientPassword(clients, pos);
        setClientName(clients, pos);
        setClientCreditCard(clients, pos);
        setClientPhoneNumber1(clients, pos);
        setClientPhoneNumber2(clients, pos);
        saveClientsFile(clients);
        saveClientCountFile(cCount);
    } else {
        puts(C_ERROR_MSG_BI_NOTFOUND);
    }
}

void removeClient(Client *clients, int *cCount) {
    long cBI;
    int pos;

    listClients(clients, cCount);
    readLong(&cBI, C_BI_MIN, C_BI_MAX, "Which Client to Remove(BI): ");
    pos = verifyIfClientBIExist(clients, cBI, cCount);
    if (pos != EOF) {
        for (pos; pos<*cCount - 1; pos++) {
            clients[pos] = clients[pos + 1];
        }
        (*cCount)--;
        saveClientsFile(clients);
        saveClientCountFile(cCount);
    } else {
        puts(C_ERROR_MSG_BI_NOTFOUND);
    }
}

void listClients(Client *clients, int *cCount) {
    int pos;

    for (pos = 0; pos<*cCount; pos++) {
        printf("[%d] BI: %ld | %s\n", pos, clients[pos].bi, clients[pos].name);
    }
}


