/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.h
 * Author: Utilizador
 *
 * Created on 6 de Fevereiro de 2016, 20:26
 */

#ifndef MENU_H
#define MENU_H

#include "Client.h"
#include "Worker.h"
#include "Product.h"
#include "Order.h"

// LIMITS TO VARIABLES
#define MENU_OPT_MIN 0
#define MENU_OPT_MAX 8

// MESSAGES FOR INPUTS
#define MENU_MSG_OPT "Select Option: "
#define MENU_MSG_OPT_INVALID "Invalid Option: "

// ERROR MESSAGES
#define M_ERROR_MSG_INVAL_LOGIN "ERROR: Wrong Password. "


void mainMenu(Client *clients, Worker *workers, Order *orders, Product products,
        int *clientCount, int *workerCount, int *orderCount, int *productCount);
void clientMenu(Client *clients, Order *orders, Product products,
        int *clientCount, int *orderCounts, int *productCount);
void manageMenu(Client *clients, Worker *workers, Order *orders, int *clientCount, int *workerCount, int *orderCount);
void workerHandlingMenu(Client *clients, Worker *workers, Order *orders, int *clientCount, int *workerCount, int *orderCount);
void workerDeliveryMenu();
void mainMenuPrint();
void clientMenuPrint();
void manageMenuPrint();
void workerHandlingMenuPrint();
void workerDeliveryMenuPrint();


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* MENU_H */

