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
#include "Product.h"
#include "Order.h"
#include "Menu.h"
#include "LP_Leitura.h"



int main(int argc, char** argv) {
    Client clients[CLIENTS_SIZE];
    Worker workers[WORKERS_SIZE];
    Order orders[ORDERS_SIZE];
    Product products[PRODUCTS_SIZE];
    int clientCount = 0, workerCount = 0, orderCount = 0, productCount = 0;

    readClientsFile(clients);
    readClientCountFile(&clientCount);
    readWorkersFile(workers);
    readWorkerCountFile(&workerCount);
    

    mainMenu(clients, workers, orders, products, &clientCount, &workerCount, &orderCount, &productCount);


    return (EXIT_SUCCESS);
}

