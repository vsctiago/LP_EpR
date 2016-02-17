#include <stdlib.h>
#include <stdio.h>
#include "Menu.h"

void mainMenu(Client *clients, Worker *workers, Order *orders, int *clientCount, int *workerCount, int *orderCount) {
    unsigned int op;
    do {
        mainMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                cleanScreen();
                printf("MSG DESPEDIDA\n");
                break;
            case 1: //Register Client
                cleanScreen();
                addClient(clients, clientCount);
                break;
            case 2: //Login Client
                cleanScreen();
                clientMenu(clients, orders, clientCount, orderCount);
                break;
            case 3: //Manag Worker
                cleanScreen();
                manageMenu(clients, workers, orders, clientCount, workerCount, orderCount);
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void clientMenu(Client *clients, Order *orders, int *clientCount, int *orderCounts) {
    unsigned int op, posLogged = 0;
    posLogged = loginClient(clients, clientCount);
    if (posLogged != EOF) {
        do {
            clientMenuPrint();
            readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
            switch (op) {
                case 0: //exit
                    break;
                case 1: //add Order
                    cleanScreen();
                    //addOrder(); //acabar
                    break;
                case 2: //List Orders Menu
                    cleanScreen();
                    //listClientOrders(); //acabar
                    break;
                case 3: //Remove order
                    cleanScreen();
                    printf("NAO PODE REMOCER ORDER");
                    break;
                case 4: //Edit Profile
                    cleanScreen();
                    //editClient(); //acabar
                    break;
                case 5: //List My Profile
                    cleanScreen();
                    //listMyClient(); talvez
                    break;
                default:
                    printf(MENU_MSG_OPT_INVALID);
            }
        } while (op != 0);
    }
}

void listClientOrdersMenu() {
    unsigned int op;
    do {
        listClientOrdersMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                cleanScreen();
                // listMyOrders();
                break;
            case 1:
                cleanScreen();
                // listMyOrderDetail();
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void manageMenu(Client *clients, Worker *workers, Order *orders, int *clientCount, int *workerCount, int *orderCount) {
    unsigned int op, posLogged = 0;
    ;
    do {
        manageMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: //Register Worker
                cleanScreen();
                //addWorker(); //acabar
                break;
            case 2: //Login Worker
                cleanScreen();
                posLogged = loginWorker(workers, workerCount);
                if (posLogged != EOF) {
                    if (workers[posLogged].type == 1) {
                        workerHandlingMenu(clients, workers, orders, clientCount, workerCount, orderCount);
                    } else {
                        workerDeliveryMenu(clients, workers, orders, clientCount, workerCount, orderCount);
                    }
                } else {
                    printf("ERRO:");
                }
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void workerHandlingMenu(Client *clients, Worker *workers, Order *orders, int *clientCount, int *workerCount, int *orderCount) {
    unsigned int op;
    do {
        workerHandlingMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: //Listar order sem aprovação
                cleanScreen();
                break;
            case 2: //Aprovar order
                cleanScreen();
                break;
            case 3: //
                cleanScreen();
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);

}

void workerDeliveryMenu() {
    unsigned int op;
    do {
        workerDeliveryMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: // listMyOrderDelivery
                cleanScreen();
                break;
            case 2: // setOrderDelivered
                cleanScreen();
                break;
            case 3: //
                cleanScreen();
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void mainMenuPrint() {
    puts("### Welcome to HandDelivery ###");
    puts("1. Register.");
    puts("2. Login.");
    puts("3. Management Area.");
    puts("0. Exit.");
}

void clientMenuPrint() {
    puts("## Client Menu ##");
    puts("1. Add Order.");
    puts("2. List Orders.");
    puts("3. Edit Profile.");
    puts("0. Back.");
}

void manageMenuPrint() {
    puts("## Manager Menu ##");
    puts("1. Register.");
    puts("2. Login.");
    puts("0. Back.");
}

void listClientOrdersMenuPrint(){

}

void workerHandlingMenuPrint(){

}

void workerDeliveryMenuPrint(){

}

