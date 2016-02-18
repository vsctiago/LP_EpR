#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Worker.h"
#include "LP_Leitura.h"


void createWorkersFile(Worker workers[]) {
    FILE *pWorkers = fopen(W_FILE_NAME, "w");
    if (pWorkers == (FILE*) NULL) {
        printf("Couldn't create %s File. ", W_FILE_NAME);
    } else {
        fwrite(workers, sizeof (Worker), WORKERS_SIZE, pWorkers);
        fclose(pWorkers);
    }
}

void saveWorkersFile(Worker workers[]) {
    FILE *pWorkers = fopen(W_FILE_NAME, "w");
    if (pWorkers == (FILE *) NULL) {
        printf("%s file doesn't exist.\n", W_FILE_NAME);
        printf("Couldn't save %s file.\n", W_FILE_NAME);
    } else {
        fwrite(workers, sizeof (Worker), WORKERS_SIZE, pWorkers);
        printf("%s file saved.\n", W_FILE_NAME);
        fclose(pWorkers);
    }
}

void readWorkersFile(Worker *workers) {

    FILE *pWorkers = fopen(W_FILE_NAME, "r");
    if (pWorkers == (FILE *) NULL) {
        printf("%s file doesn't exist\n", W_FILE_NAME);
        printf("Creating %s file now...\n", W_FILE_NAME);
        createWorkersFile(workers);
        printf("%s file created\n");
        readWorkersFile(workers);
    } else {
        fread(workers, sizeof (Worker), WORKERS_SIZE, pWorkers);
        fclose(pWorkers);
    }
}

void createWorkerCountFile(int *wCount) {
    FILE *pWcount = fopen(W_FILE_NAME_COUNT, "w");
    if (pWcount == (FILE*) NULL) {
        printf("Couldn't create %s File. ", W_FILE_NAME_COUNT);
    } else {
        fwrite(wCount, sizeof (int), 1, pWcount);
        fclose(pWcount);
    }
}

void saveWorkerCountFile(int *wCount) {
    FILE *pWcount = fopen(W_FILE_NAME_COUNT, "w");
    if (pWcount == (FILE *) NULL) {
        printf("%s file doesn't exist.\n", W_FILE_NAME_COUNT);
        printf("Couldn't save %s file.\n", W_FILE_NAME_COUNT);
    } else {
        fwrite(wCount, sizeof (int), 1, pWcount);
        printf("%s file saved.\n", W_FILE_NAME_COUNT);
        fclose(pWcount);
    }
}

int readWorkerCountFile(int *wCount) {

    FILE *pWcount = fopen(W_FILE_NAME_COUNT, "r");
    if (pWcount == (FILE *) NULL) {
        printf("%s file doesn't exist\n", W_FILE_NAME_COUNT);
        printf("Creating %s file now...\n", W_FILE_NAME_COUNT);
        createWorkerCountFile(wCount);
        printf("%s file created\n", W_FILE_NAME_COUNT);
        readWorkerCountFile(wCount);
    } else {
        fread(wCount, sizeof (int), 1, pWcount);
        fclose(pWcount);
    }
}

void setWorkerName(Worker *workers, int pos) {
    readString(workers[pos].name, W_NAME_LENGTH, W_MSG_NAME);
}

void setWorkerPassword(Worker *workers, int pos) {
    readString(workers[pos].password, W_PASSWORD_LENGTH, W_MSG_PASSWORD);
}

void setWorkerType(Worker *workers, int pos) {
    int temp;
    printf("%s", W_MSG_WORKER_TYPE);
    readInt(&temp, W_TYPE_MIN, W_TYPE_MAX, W_MSG_TYPE);
    if (temp == 1)
        workers[pos].type = 1;
    else
        workers[pos].type = 2;
}

bool verifyIfWorkersFull(int *wCount) {
    if (*wCount == WORKERS_SIZE) {
        puts(W_ERROR_MSG_FULL);
        return true;
    } else {
        return false;
    }
}

int verifyIfWorkerBIExist(Worker *workers, long bi, int *wCount) {
    int pos;
    for (pos = 0; pos<*wCount; pos++) {
        if (workers[pos].bi == bi) {
            return pos;
        }
    }
    return EOF;
}

int loginWorker(Worker *workers, int *wCount) {
    int pos;
    long tempBI;
    char tempPASS[W_PASSWORD_LENGTH];

    readLong(&tempBI, W_BI_MIN, W_BI_MAX, W_MSG_BI);
    pos = verifyIfWorkerBIExist(workers, tempBI, wCount);
    if (pos != EOF) {
        readString(tempPASS, W_PASSWORD_LENGTH, W_MSG_PASSWORD);
        if (strcmp(tempPASS, workers[pos].password) == 0) {
            return pos;
        } else {
            puts(W_ERROR_MSG_PASS_WRONG);
            return EOF;
        }
    } else {
        puts(W_ERROR_MSG_BI_NOTFOUND);
        return EOF;
    }
}

void addWorker(Worker *workers, int *wCount) {
    long wBI;

    if (verifyIfWorkersFull(wCount) == false) {
        readLong(&wBI, W_BI_MIN, W_BI_MAX, W_MSG_BI);
        if (verifyIfWorkerBIExist(workers, wBI, wCount) == EOF) {
            workers[*wCount].bi = wBI;
            setWorkerName(workers, *wCount);
            setWorkerPassword(workers, *wCount);
            setWorkerType(workers, *wCount);
            *wCount += 1;
            saveWorkersFile(workers);
            saveWorkerCountFile(wCount);
        } else {
            puts(W_ERROR_MSG_BI_EXISTS);
        }
    }
}

void listAllWorkers(Worker *workers, int *wCount) {
    int pos;

    for (pos = 0; pos<*wCount; pos++) {
        printf("[%d] BI: %ld | %s \t| Type: ", pos, workers[pos].bi, workers[pos].name);
        if(workers[pos].type == 1) {
            printf("Handling\n");
        } else {
            printf("Delivery\n");
        }
    }
}

void editWorker(Worker *workers, int *wCount) {
    int wBI;
    int pos;

    listAllWorkers(workers, wCount);
    readInt(&wBI, W_BI_MIN, W_BI_MAX, "Which Worker to Edit(BI): ");
    pos = verifyIfWorkerBIExist(workers, wBI, wCount);
    if (pos != EOF) {
        setWorkerName(workers, pos);
        setWorkerType(workers, pos);
        saveWorkersFile(workers);
        saveWorkerCountFile(wCount);
    } else {
        puts(W_ERROR_MSG_BI_NOTFOUND);
    }
}

void removeWorker(Worker *workers, int *wCount) {
    long wBI;
    int pos;

    listAllWorkers(workers, wCount);
    readLong(&wBI, W_BI_MIN, W_BI_MAX, "Which Worker to Remove(BI): ");
    pos = verifyIfWorkerBIExist(workers, wBI, wCount);
    if (pos != EOF) {
        for (pos; pos<*wCount - 1; pos++) {
            workers[pos] = workers[pos + 1];
        }
        (*wCount)--;
        saveWorkersFile(workers);
        saveWorkerCountFile(wCount);
    } else {
        puts(W_ERROR_MSG_BI_NOTFOUND);
    }
}
