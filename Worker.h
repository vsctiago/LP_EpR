/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Worker.h
 * Author: Utilizador
 *
 * Created on 7 de Fevereiro de 2016, 17:01
 */

#ifndef WORKER_H
#define WORKER_H

// LIMITS TO VARIABLES
#define WORKERS_SIZE 20
#define W_BI_MIN 10000000
#define W_BI_MAX 99999999
#define W_PASSWORD_LENGTH 20+1
#define W_NAME_LENGTH 100+1
#define W_TYPE_MIN 1
#define W_TYPE_MAX 2

// MESSAGES FOR INPUTS
#define W_MSG_BI "Insert BI: "
#define W_MSG_PASSWORD "Insert Password: "
#define W_MSG_NAME "Insert name: "
#define W_MSG_WORKER_TYPE "WorkerType:\n\t[1] Handling\n\t[2] Delivery\n\t"
#define W_MSG_TYPE "Insert Type: "

// ERROR MESSAGES
#define W_ERROR_MSG_FULL "ERROR: Full, can't add more workers.\n"
#define W_ERROR_MSG_BI_EXISTS "ERROR: That BI already exists.\n"
#define W_ERROR_MSG_BI_NOTFOUND "ERROR: Worker BI not found.\n"
#define W_ERROR_MSG_PASS_WRONG "ERROR: Wrong Password.\n"

// NOMES DE FICHEIROS
#define W_FILE_NAME "Workers"
#define W_FILE_NAME_COUNT "WorkerCount" 

typedef enum {
    HANDLING = 1, DELIVERY
} WorkerType;

typedef struct {
    long bi;
    char password[W_PASSWORD_LENGTH];
    char name[W_NAME_LENGTH];
    WorkerType type;
} Worker;

void createWorkersFile(Worker worker[]);
void createWorkersFile(Worker worker[]);
Worker readWorkersFile(Worker worker[]);
void createWorkerCountFile(int *wCount);
void saveWorkerCountFile(int *wCount);
int readWorkerCountFile(int *wCount);
void setWorkerName(Worker *worker, int pos);
void setWorkerType(Worker *w, int pos);
bool verifyIfWorkersFull(int *wCount);
int verifyIfWorkerBIExist(Worker *w, long bi, int *wCount);
long loginWorker(Worker *w, int *wCount);
void addWorker(Worker *w, int *wCount);
void listWorkers(Worker *w, int *wCount);
void editWorker(Worker *worker, int *wCount);
void removeWorker(Worker *w, int *wCount);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* WORKER_H */

