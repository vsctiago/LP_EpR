#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Worker.h"

void setBI(Worker *w, int pos) {
    readLong(&w[pos].bi, W_BI_MIN, W_BI_MAX, W_MSG_BI);
}

void setName(Worker *w, int pos) {
    readString(w[pos].name, W_NAME_LENGTH, W_MSG_NAME);
}

void setType(Worker *w, int pos) {
    int temp;
    printf("WorkerType [1] Handling | [2] Delivery");
    readInt(&temp, W_TYPE_MIN, W_TYPE_MAX, W_MSG_TYPE);
    if(temp == 1)
        w[pos].type = 1;
    else
        w[pos].type = 2;
}

bool verifyIfWorkersFull(int *wCount) {
    if(*wCount == WORKERS_SIZE) {
        puts(W_ERROR_MSG_FULL);
        return true;
    } else {
        return false;
    }
}

int verifyIfWorkerBIExist(Worker *w, long bi, int *wCount) {
    int pos;
    for(pos=0; pos<*wCount; pos++) {
        if(w[pos].bi == bi) {
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
    if(pos != EOF) {
        readString(tempPASS, W_PASSWORD_LENGTH, W_MSG_PASSWORD);
        if(strcmp(tempPASS, w[pos].password) == 0) {
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
    
    if(verifyIfWorkersFull(wCount) == false) {
        readLong(&wBI, W_BI_MIN, W_BI_MAX, W_MSG_BI);
        if(verifyIfWorkerBIExist(w, wBI, wCount) == EOF) {
            w[*wCount].bi = wBI;
            setName(w, *wCount);
            setType(w, *wCount);
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
    
    for(pos=0; pos<*wCount; pos++) {
            printf("[%d] BI: %ld | %s\n", pos, w[pos].bi, w[pos].name);
    }
}

void editWorker(Worker *w, int *wCount) {
    int wBI;
    int pos;
    
    listWorkers(w, wCount);
    readInt(&wBI, W_BI_MIN, W_BI_MAX, "Which Worker to Edit(BI): ");
    pos = verifyIfWorkerBIExist(w, wBI, wCount);
    if(pos != EOF){
        setName(w, pos);
        setType(w, pos);
        saveWorkersFile(w);
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
    if(pos != EOF) {
        for(pos; pos<*wCount-1; pos++) {
            w[pos] = w[pos+1];
        }
        (*wCount)--;
        saveWorkersFile(w);
        saveWorkerCountFile(wCount);
    } else {
        puts(W_ERROR_MSG_BI_NOTFOUND);
    }
}

void createWorkersFile(Worker w[]) {
    FILE *pWorkers = fopen("Workers", "w");
    if(pWorkers == (FILE*) NULL){
        printf("Couldn't create Workers File. ");
    } else {
        fwrite(w, sizeof(Worker), WORKERS_SIZE, pWorkers);
        fclose(pWorkers);
    }   
}

void saveWorkersFile(Worker w[]) {
    FILE *pWorkers = fopen("Workers", "w");
    if(pWorkers == (FILE *) NULL) {
        puts("Workers file doesn't exist.");
        puts("Couldn't save Workers file.");
    } else {
        fwrite(w, sizeof(Worker), WORKERS_SIZE, pWorkers);
        puts("Workers file saved.");
        fclose(pWorkers);
    }
}

Worker readWorkersFile(Worker w[]) {
    
    FILE *pWorkers = fopen("Workers", "r");
    if(pWorkers == (FILE *) NULL) {
        puts("Workers file doesn't exist");
        puts("Creating Workers file now...");
        createWorkersFile(w);
        puts("Workers file created");
        readWorkersFile(w);
    } else {
        fread(w, sizeof(Worker), WORKERS_SIZE, pWorkers);
        fclose(pWorkers);
    }
}

void createWorkerCountFile(int *wCount) {
    FILE *pWcount = fopen("WorkerCount", "w");
    if(pWcount == (FILE*) NULL){
        printf("Couldn't create WorkerCount File. ");
    } else {
        fwrite(wCount, sizeof(int), 1, pWcount);
        fclose(pWcount);
    }   
}

void saveWorkerCountFile(int *wCount) {
    FILE *pWcount = fopen("WorkerCount", "w");
    if(pWcount == (FILE *) NULL) {
        puts("WorkerCount file doesn't exist.");
        puts("Couldn't save WorkerCount file.");
    } else {
        fwrite(wCount, sizeof(int), 1, pWcount);
        puts("WorkerCount file saved.");
        fclose(pWcount);
    }
}

int readWorkerCountFile(int *wCount) {
    
    FILE *pWcount = fopen("WorkerCount", "r");
    if(pWcount == (FILE *) NULL) {
        puts("WorkerCount file doesn't exist");
        puts("Creating WorkerCount file now...");
        createWorkerCountFile(wCount);
        puts("WorkerCount file created");
        readWorkerCountFile(wCount);
    } else {
        fread(wCount, sizeof(int), 1, pWcount);
        fclose(pWcount);
    }
}

