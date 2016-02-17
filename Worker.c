#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Worker.h"

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

Worker readWorkersFile(Worker workers[]) {

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

void setWorkerName(Worker *worker, int pos) {
    readString(worker[pos].name, W_NAME_LENGTH, W_MSG_NAME);
}

void setWorkerType(Worker *w, int pos) {
    int temp;
    printf("%s", W_MSG_WORKER_TYPE);
    readInt(&temp, W_TYPE_MIN, W_TYPE_MAX, W_MSG_TYPE);
    if (temp == 1)
        w[pos].type = 1;
    else
        w[pos].type = 2;
}

bool verifyIfWorkersFull(int *wCount) {
    if (*wCount == WORKERS_SIZE) {
        puts(W_ERROR_MSG_FULL);
        return true;
    } else {
        return false;
    }
}

int verifyIfWorkerBIExist(Worker *w, long bi, int *wCount) {
    int pos;
    for (pos = 0; pos<*wCount; pos++) {
        if (w[pos].bi == bi) {
            return pos;
        }
    }
    return EOF;
}

long loginWorker(Worker *w, int *wCount) {
    int pos, tempBI;
    char tempPASS[W_PASSWORD_LENGTH];

    readLong(&tempBI, W_BI_MIN, W_BI_MAX, W_MSG_BI);
    pos = verifyIfWorkerBIExist(w, tempBI, wCount);
    if (pos != EOF) {
        readString(tempPASS, W_PASSWORD_LENGTH, W_MSG_PASSWORD);
        if (strcmp(tempPASS, w[pos].password) == 0) {
            return tempBI;
        } else {
            puts(W_ERROR_MSG_PASS_WRONG);
            return EOF;
        }
    } else {
        puts(W_ERROR_MSG_BI_NOTFOUND);
        return EOF;
    }
}

void addWorker(Worker *w, int *wCount) {
    long wBI;

    if (verifyIfWorkersFull(wCount) == false) {
        readLong(&wBI, W_BI_MIN, W_BI_MAX, W_MSG_BI);
        if (verifyIfWorkerBIExist(w, wBI, wCount) == EOF) {
            w[*wCount].bi = wBI;
            setWorkerName(w, *wCount);
            setWorkerType(w, *wCount);
            *wCount += 1;
            saveWorkersFile(w);
            saveWorkerCountFile(wCount);
        } else {
            puts(W_ERROR_MSG_BI_EXISTS);
        }
    }
}

void listWorkers(Worker *w, int *wCount) {
    int pos;

    for (pos = 0; pos<*wCount; pos++) {
        printf("[%d] BI: %ld | %s\n", pos, w[pos].bi, w[pos].name);
    }
}

void editWorker(Worker *worker, int *wCount) {
    int wBI;
    int pos;

    listWorkers(worker, wCount);
    readInt(&wBI, W_BI_MIN, W_BI_MAX, "Which Worker to Edit(BI): ");
    pos = verifyIfWorkerBIExist(worker, wBI, wCount);
    if (pos != EOF) {
        setWorkerName(worker, pos);
        setWorkerType(worker, pos);
        saveWorkersFile(worker);
        saveWorkerCountFile(wCount);
    } else {
        puts(W_ERROR_MSG_BI_NOTFOUND);
    }
}

void removeWorker(Worker *w, int *wCount) {
    int wBI;
    int pos;

    listWorkers(w, wCount);
    readLong(&wBI, W_BI_MIN, W_BI_MAX, "Which Worker to Remove(BI): ");
    pos = verifyIfWorkerBIExist(w, wBI, wCount);
    if (pos != EOF) {
        for (pos; pos<*wCount - 1; pos++) {
            w[pos] = w[pos + 1];
        }
        (*wCount)--;
        saveWorkersFile(w);
        saveWorkerCountFile(wCount);
    } else {
        puts(W_ERROR_MSG_BI_NOTFOUND);
    }
}
