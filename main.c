/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Utilizador
 *
 * Created on 6 de Fevereiro de 2016, 15:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Client.h"
#include "Worker.h"
#include "Order.h"
#include "Menu.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Client clients[CLIENTS_SIZE];
    Worker workers[WORKERS_SIZE];
    Order orders[ORDERS_SIZE];
    int clientCount = 0, workerCount = 0, orderCount = 0;
    int menuOpt;
    long clientLogged = 0, workerLogged = 0;
    
    readClientsFile(clients);
    readClientCountFile(&clientCount);
    readWorkersFile(workers);
    readWorkerCountFile(&workerCount);
    
    while(true) {
        mainMenu();
        readInt(&menuOpt, MENUOPTMIN, MENUOPTMAX, "Select Option: ");
        if(menuOpt == 1) {
            addClient(clients, &clientCount);
        } else if(menuOpt == 2) {
            clientLogged = loginClient(clients, &clientCount);
            if(clientLogged != EOF) {
                // MENU DE CLIENTE ETC.. 
                // BREAK WHILE(TRUE) PA SAIR DO PROGRAMA
            }
        } else if(menuOpt == 3) {
            workerLogged = loginWorker(workers, &workerCount);
            if(workerLogged != EOF) {
                // Administration MENU and sheit
                // BREAK WHILE(TRUE) PA SAIR DO PROGRAMA
            }
        } else if(menuOpt == 4) {
            break;
        }
    }
    
    
    
    return (EXIT_SUCCESS);
}

