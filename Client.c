#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Client.h"
#include "LP_Leitura.h"

void createClientsFile(Client c[]) {
    FILE *pClients = fopen("Clients", "w");
    if (pClients == (FILE*) NULL) {
        printf("Couldn't create Clients File. ");
    } else {
        fwrite(c, sizeof (Client), CLIENTS_SIZE, pClients);
        fclose(pClients);
    }
}

void saveClientsFile(Client c[]) {
    FILE *pClients = fopen("Clients", "w");
    if (pClients == (FILE *) NULL) {
        puts("Clients file doesn't exist.");
        puts("Couldn't save Clients file.");
    } else {
        fwrite(c, sizeof (Client), CLIENTS_SIZE, pClients);
        puts("Clients file saved.");
        fclose(pClients);
    }
}

Client readClientsFile(Client c[]) {

    FILE *pClients = fopen("Clients", "r");
    if (pClients == (FILE *) NULL) {
        puts("Clients file doesn't exist");
        puts("Creating Clients file now...");
        createClientsFile(c);
        puts("Clients file created");
        readClientsFile(c);
    } else {
        fread(c, sizeof (Client), CLIENTS_SIZE, pClients);
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

void setClientBI(Client *c, int pos) {
    readLong(&c[pos].bi, C_BI_MIN, C_BI_MAX, C_MSG_BI);
}

void setClientPassword(Client *c, int pos) {
    readString(c[pos].password, C_PASSWORD_LENGTH, C_MSG_PASSWORD);
}

void setClientName(Client *c, int pos) {
    readString(c[pos].name, C_NAME_LENGTH, C_MSG_NAME);
}

void setClientCreditCard(Client *c, int pos) {
    puts("Insert CreditCard:::");
    readLong(&c[pos].creditCard.bankNumber, C_BANKNUMBER_MIN, C_BANKNUMBER_MAX, C_MSG_BANKNUMBER);
    readLong(&c[pos].creditCard.accountNumber, C_ACCOUNTNUMBER_MIN, C_ACCOUNTNUMBER_MAX, C_MSG_ACCOUNTNUMBER);
}

void setClientPhoneNumber(long *phoneNumber) {
    bool val = false;
    do {
        readLong(&phoneNumber, C_PHONENUMBER_MIN, C_PHONENUMBER_MAX, C_MSG_PHONENUMBER);
        if (phoneNumber > 960000000 && phoneNumber < 969999999 ||
                phoneNumber > 930000000 && phoneNumber < 939999999 ||
                phoneNumber > 920000000 && phoneNumber < 929999999 ||
                phoneNumber > 910000000 && phoneNumber < 919999999) {
            val = true;
        } else {
            puts("Error: Number invalid!!");
        }
    } while (val == false);
}

void setClientPhoneNumber1(Client *c, int pos) {
    setClientPhoneNumber(&c[pos].phoneNumber1);
}

void setClientPhoneNumber2(Client *c, int pos) {
    bool val = false;
    do {
        setClientPhoneNumber(&c[pos].phoneNumber2);
            if (c[pos].phoneNumber2 == c[pos].phoneNumber1) {
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

int verifyIfClientBIExist(Client *c, long bi, int *cCount) {
    int pos;
    for (pos = 0; pos<*cCount; pos++) {
        if (c[pos].bi == bi) {
            return pos;
        }
    }
    return EOF;
}

long loginClient(Client *c, int *cCount) {
    int pos, tempBI;
    char tempPASS[C_PASSWORD_LENGTH];

    readLong(&tempBI, C_BI_MIN, C_BI_MAX, C_MSG_BI);
    pos = verifyIfClientBIExist(c, tempBI, cCount);
    if (pos != EOF) {
        readString(tempPASS, C_PASSWORD_LENGTH, C_MSG_PASSWORD);
        if (strcmp(tempPASS, c[pos].password) == 0) {
            return tempBI;
        } else {
            puts(C_ERROR_MSG_PASS_WRONG);
            return EOF;
        }
    } else {
        puts(C_ERROR_MSG_BI_NOTFOUND);
        return EOF;
    }
}

void addClient(Client *c, int *cCount) {
    long cBI;

    if (verifyIfClientsFull(cCount) == false) {
        readLong(&cBI, C_BI_MIN, C_BI_MAX, C_MSG_BI);
        if (verifyIfClientBIExist(c, cBI, cCount) == EOF) {
            c[*cCount].bi = cBI;
            setClientPassword(c, *cCount);
            setClientName(c, *cCount);
            setClientCreditCard(c, *cCount);
            setClientPhoneNumber1(c, *cCount);
            setClientPhoneNumber2(c, *cCount);
            (*cCount)++;
            saveClientsFile(c);
            saveClientCountFile(cCount);
        } else {
            puts(C_ERROR_MSG_BI_EXISTS);
        }
    }
}

void editClient(Client *c, int *cCount) {
    int cBI;
    int pos;

    listClients(c, cCount);
    readInt(&cBI, C_BI_MIN, C_BI_MAX, "Which Client to Edit(BI): ");
    pos = verifyIfClientBIExist(c, cBI, cCount);
    if (pos != EOF) {
        setClientPassword(c, pos);
        setClientName(c, pos);
        setClientCreditCard(c, pos);
        setClientPhoneNumber(c, pos);
        saveClientsFile(c);
        saveClientCountFile(cCount);
    } else {
        puts(C_ERROR_MSG_BI_NOTFOUND);
    }
}

void removeClient(Client *c, int *cCount) {
    int cBI;
    int pos;

    listClients(c, cCount);
    readLong(&cBI, C_BI_MIN, C_BI_MAX, "Which Client to Remove(BI): ");
    pos = verifyIfClientBIExist(c, cBI, cCount);
    if (pos != EOF) {
        for (pos; pos<*cCount - 1; pos++) {
            c[pos] = c[pos + 1];
        }
        (*cCount)--;
        saveClientsFile(c);
        saveClientCountFile(cCount);
    } else {
        puts(C_ERROR_MSG_BI_NOTFOUND);
    }
}

void listClients(Client *c, int *cCount) {
    int pos;

    for (pos = 0; pos<*cCount; pos++) {
        printf("[%d] BI: %ld | %s\n", pos, c[pos].bi, c[pos].name);
    }
}


