#include <stdlib.h>
#include <stdio.h>
#include "Menu.h"

void mainMenu(Client *clients, Worker *workers, Order *orders, Product *products,
        int *clientCount, int *workerCount, int *orderCount, int *productCount) {
    int op;
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
                clientMenu(clients, orders, products, clientCount, orderCount, productCount);
                break;
            case 3: //Manag Worker
                cleanScreen();
                manageMenu(clients, workers, orders, products, clientCount, workerCount, orderCount, productCount);
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void clientMenu(Client *clients, Order *orders, Product *products,
        int *clientCount, int *orderCounts, int *productCount) {
    int op, posLogged = 0;
    posLogged = loginClient(clients, clientCount);
    if (posLogged != EOF) {
        do {
            clientMenuPrint();
            readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
            switch (op) {
                case 0: //exit
                    break;
                case 1:
                    cleanScreen();
                    listProducts(products, productCount);
                    break;
                case 2:
                    cleanScreen();
                    addOrder(orders, *orderCounts, clients, clientCount, products, productCount);
                    break;
                case 3:
                    cleanScreen();
                    listMyOrders(orders, *orderCounts, clients[posLogged].bi);
                    removeOrderClient(orders, *orderCounts, clients[posLogged].bi);
                    break;
                case 4: //
                    cleanScreen();
                    listMyClient(clients[posLogged]);
                    printf("\n\n");
                    break;
                case 5: //
                    cleanScreen();
                    editClient(clients, clientCount, posLogged);
                    printf("\n\n");
                    break;
                case 6: //
                    cleanScreen();
                    listMyOrders(orders, orderCounts, orders[posLogged].clientBI);
                    printf("\n\n");
                    break;
                case 7: //
                    cleanScreen();
                    listMyOrdersPendingApproval(orders, orderCounts, orders[posLogged].clientBI);
                    printf("\n\n");
                    break;
                case 8: //
                    cleanScreen();
                    listMyOrdersPendingDelivery(orders, orderCounts, orders[posLogged].clientBI);
                    printf("\n\n");
                    break;
                default:
                    printf(MENU_MSG_OPT_INVALID);
            }
        } while (op != 0);
    }
}

void manageMenu(Client *clients, Worker *workers, Order *orders, Product *products,
        int *clientCount, int *workerCount, int *orderCount, int *productCount) {
    
    int op, posLogged = 0;
    
    do {
        manageMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: //Register Worker
                cleanScreen();
                addWorker(workers, workerCount);
                printf("\n\n");
                break;
            case 2: //Login Worker
                cleanScreen();
                posLogged = loginWorker(workers, workerCount);
                if (posLogged != EOF) {
                    if (workers[posLogged].type == 1) {
                        workerHandlingMenu(clients, workers, orders, products, clientCount, workerCount, orderCount, productCount, posLogged);
                    } else {
                        workerDeliveryMenu(clients, workers, orders, clientCount, workerCount, orderCount, posLogged);
                    }
                }
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void workerHandlingMenu(Client *clients, Worker *workers, Order *orders, Product *products,
        int *clientCount, int *workerCount, int *orderCount, int *productCount, unsigned int posLogged) {
    
    int op;
    do {
        workerHandlingMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: 
                cleanScreen();
                workerHandlingProductsMenu(Product, productCount);
                break;
            case 2: 
                cleanScreen();
                workerHandlingOrdersMenu(clients, workers, orders, products, clientCount, workerCount, orderCount, productCount, posLogged);
                break;
            case 3: 
                cleanScreen();
                workerHandlingClientsMenu(clients, clientCount);
                break;
            case 4: 
                cleanScreen();
                workerHandlingWorkersMenu(Worker, workerCount);
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void workerHandlingProductsMenu(Product *products, int *productCount) {
    int op;
    do {
        workerHandlingProductsMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: 
                cleanScreen();
                addProduct(products, productCount);
                break;
            case 2: 
                cleanScreen();
                editProduct(products, productCount);
                break;
            case 3: 
                cleanScreen();
                removeProduct(products, productCount);
                break;
            case 4: 
                cleanScreen();
                listProducts(products, productCount);
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void workerHandlingOrdersMenu(Client *clients, Worker *workers, Order *orders, Product *products, int *clientCount, int *workerCount, int *orderCount, int *productCount, int posLogged) {
    int op;
    do {
        workerHandlingOrdersMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: 
                cleanScreen();
                setOrderApprovalWorkerBI(orders, workers, *orderCount, workers[posLogged].bi, workerCount);
                break;
            case 2: 
                cleanScreen();
                int pos = 0;
                do {
                    listMyOrders(orders, orderCount, clients[pos].bi);
                } while(pos < *clientCount);
                break;
            case 3: 
                cleanScreen();
                listAllOrdersByDate(orders, orderCount);
                break;
            case 4: 
                cleanScreen();
                do {
                    listMyOrdersPendingApproval(orders, orderCount, clients[pos].bi);
                } while(pos < *clientCount);
                break;
            case 5: 
                cleanScreen();
                do {
                    listMyOrdersPendingDelivery(orders, orderCount, clients[pos].bi);
                } while(pos < *clientCount);
                break;
            case 6: 
                cleanScreen();
                listAllPendingApprovedProducts(orders, products, productCount, orderCount);
                break;
            case 7: 
                cleanScreen();
                listOrdersByTotalValueFromClient(orders, clients, orderCount, clientCount);
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void workerHandlingClientsMenu(Client *clients, int *clientCount) {
    int op;
    do {
        workerHandlingClientsMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: 
                cleanScreen();
                listAllClients(clients, clientCount);
                break;
            case 2: 
                cleanScreen();
                editClientAdmin(clients, clientCount);
                break;
            case 3: 
                cleanScreen();
                removeClientAdmin(clients, clientCount);
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void workerHandlingWorkersMenu(Worker *workers, int *workerCount) {
    int op;
    do {
        workerHandlingWorkersMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1: 
                cleanScreen();
                listAllWorkers(workers, workerCount);
                break;
            case 2: 
                cleanScreen();
                editWorker(workers, workerCount);
                break;
            case 3: 
                cleanScreen();
                removeWorker(workers, workerCount);
                break;
            default:
                printf(MENU_MSG_OPT_INVALID);
        }
    } while (op != 0);
}

void workerDeliveryMenu(Client *clients, Worker *workers, Order *orders, int *clientCount, int *workerCount, int *orderCount, int posLogged) {
    int op, pos = 0;
    do {
        workerDeliveryMenuPrint();
        readInt(&op, MENU_OPT_MIN, MENU_OPT_MAX, MENU_MSG_OPT);
        switch (op) {
            case 0: //exit
                break;
            case 1:
                cleanScreen();
                do {
                    listMyOrdersPendingDelivery(orders, orderCount, clients[pos].bi);
                } while(pos < *clientCount);
                break;
            case 2:
                cleanScreen();
                setOrderDelivered(orders, orderCount, workers[posLogged].bi);
                break;
            case 3:
                cleanScreen();
                listPendingOrdersByWorkerByDate(orders, orderCount, workers[posLogged].bi);
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
    puts("1. List Products");
    puts("2. Add Order");
    puts("3. Remove Order");
    puts("4. List Profile");
    puts("5. Edit Profile");
    puts("6. List My Orders");
    puts("7. List My Orders Pending Approval");
    puts("8. List My Orders Pending Delivery");
    puts("0. Back.");
}

void manageMenuPrint() {
    puts("## Manager Menu ##");
    puts("1. Register.");
    puts("2. Login.");
    puts("0. Back.");
}

void workerHandlingMenuPrint() {
    puts("## Worker Handling Menu ##");
    puts("1. Product Menu.");
    puts("2. Order Menu.");
    puts("3. Client Menu.");
    puts("4. Worker Menu.");
    puts("0. Back.");
}

void workerHandlingProductsMenuPrint() {
    puts("## Worker Handling Products Menu ##");
    puts("1. Add Product.");
    puts("2. Edit Product.");
    puts("3. Remove Product.");
    puts("4. List Products.");
    puts("0. Back.");
}

void workerHandlingOrdersMenuPrint() {
    puts("## Worker Handling Orders Menu ##");
    puts("1. Approve Order.");
    puts("2. List All Orders.");
    puts("3. List Orders By Date.");
    puts("4. List All Orders Pending Approval.");
    puts("5. List All Orders Pending Delivery.");
    puts("6. List All Pending Products in Approved Orders.");
    puts("7. List All Orders and Total Value from Client.");
    puts("0. Back.");
}

void workerHandlingClientsMenuPrint() {
    puts("## Worker Handling Clients Menu ##");
    puts("1. List Clients.");
    puts("2. Edit Client.");
    puts("3. Remove Client.");
    puts("0. Back.");
}

void workerHandlingWorkersMenuPrint() {
    puts("## Worker Handling Workers Menu ##");
    puts("1. List Workers.");
    puts("2. Edit Worker.");
    puts("3. Remove Worker.");
    puts("0. Back.");
}

void workerDeliveryMenuPrint() {
    puts("## Worker Delivery Menu ##");
    puts("1. List All Orders Pending Delivery.");
    puts("2. Confirm Order Delivery.");
    puts("3. List All Pending Orders By Date.");
    puts("0. Back.");
}


