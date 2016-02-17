#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Client.h"
#include "Worker.h"
#include "Product.h"
#include "Order.h"
#include "LP_Leitura.h"


void createOrdersFile(Order orders[]) {
    FILE *pOrders = fopen(O_FILE_NAME, "w");
    if (pOrders == (FILE*) NULL) {
        printf("Couldn't create %s File. ", O_FILE_NAME);
    } else {
        fwrite(orders, sizeof (Order), ORDERS_SIZE, pOrders);
        fclose(pOrders);
    }
}

void saveOrdersFile(Order orders[]) {
    FILE *pOrders = fopen(O_FILE_NAME, "w");
    if (pOrders == (FILE *) NULL) {
        printf("%s file doesn't exist.\n", O_FILE_NAME);
        printf("Couldn't save %s file.\n", O_FILE_NAME);
    } else {
        fwrite(orders, sizeof (Order), ORDERS_SIZE, pOrders);
        printf("%s file saved.\n", O_FILE_NAME);
        fclose(pOrders);
    }
}

Order readOrdersFile(Order orders[]) {

    FILE *pOrders = fopen(O_FILE_NAME, "r");
    if (pOrders == (FILE *) NULL) {
        printf("%s file doesn't exist\n", O_FILE_NAME);
        printf("Creating %s file now...\n", O_FILE_NAME);
        createOrdersFile(orders);
        printf("%s file created\n", O_FILE_NAME);
        //readOrderFile(p); 
    } else {
        fread(orders, sizeof (Product), ORDERS_SIZE, pOrders);
        fclose(pOrders);
    }
}

void createOrderCountFile(int *oCount) {
    FILE *pOcount = fopen(O_FILE_NAME_COUNT, "w");
    if (pOcount == (FILE*) NULL) {
        printf("Couldn't create %s File. \n", O_FILE_NAME_COUNT);
    } else {
        fwrite(oCount, sizeof (int), 1, pOcount);
        fclose(pOcount);
    }
}

void saveOrderCountFile(int *oCount) {
    FILE *pOcount = fopen(O_FILE_NAME_COUNT, "w");
    if (pOcount == (FILE *) NULL) {
        printf("%s file doesn't exist.\n", O_FILE_NAME_COUNT);
        printf("Couldn't save %s file.\n", O_FILE_NAME_COUNT);
    } else {
        fwrite(oCount, sizeof (int), 1, pOcount);
        printf("%s file saved.\n", O_FILE_NAME_COUNT);
        fclose(pOcount);
    }
}

int readOrderCountFile(int *oCount) {

    FILE *pOcount = fopen(O_FILE_NAME_COUNT, "r");
    if (pOcount == (FILE *) NULL) {
        printf("%s file doesn't exist\n");
        printf("Creating %s file now...\n", O_FILE_NAME_COUNT);
        createOrderCountFile(oCount);
        printf("%s file created\n", O_FILE_NAME_COUNT);
        //readOrderCountFile(prCount);
    } else {
        fread(oCount, sizeof (int), 1, pOcount);
        fclose(pOcount);
    }
}

void setOrderId(Order *orders, int pos) {
    if (pos == 0) {
        orders[pos].id = 1;
    } else {
        orders[pos].id = orders[pos - 1].id + 1;
    }
}

void setOrderDate(Order *orders, int pos){
    setCurrentDate(&orders[pos].orderDate);
}

void setOrderBI(long *bi, char msg[]) {
    readLong(bi, C_BI_MIN, C_BI_MAX, msg);
}

void setOrderClientBi(Order *orders, int pos, Client *clients, int *cCount) {
    long pBi, verify = EOF;

    do {
        setOrderBI(&pBi, O_MSG_CLIENT_BI);
        verify = verifyIfClientBIExist(clients, pBi, cCount);
        if (verify == EOF) {
            printf(O_ERROR_MSG_BI_NOTFOUND);
        } else {
            orders[pos].clientBI = pBi;
            setOrderDate(orders, pos);
        }
    } while (verify = EOF);
}

void setOrderApprovalDate(Order *orders, int pos) {
    setCurrentDate(&orders[pos].approvalDate);
}

void setCurrentDate(Date *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    date->year = tm.tm_year + 1900;
    date->month = tm.tm_mon + 1;
    date->day = tm.tm_mday;
}

void setDate(Date *date, char msgDate[]) {
    printf("%s", msgDate);
    readInt(&date->year, O_DATE_YEAR_MIN, O_DATE_YEAR_MAX, O_MSG_DATE_YEAR);
    readInt(&date->month, O_DATE_MONTH_MIN, O_DATE_MONTH_MAX, O_MSG_DATE_MONTH);
    readInt(&date->day, O_DATE_DAY_MIN, O_DATE_DAY_MAX, O_MSG_DATE_DAY);
}

void setOrderProductId(Order *orders, int pos, Product *products, int *pCount){
    long pId, verify = EOF;
    
    do {
        readLong(&pId,P_ID_MAX,P_ID_MIN,P_MSG_ID);
        verify = verifyIfProductIDExist(products, pId, pCount);
        if (verify == EOF) {
            printf(O_ERROR_MSG_ID_NOTFOUND);
        } else {
            orders[pos].lines[orders[pos].contLines].idProduct = pId;
            setOrderProductPriceU(orders, pos, products[verify].pricePerUnit);
            orders[pos].contLines++;
        }
    } while (verify = EOF);
}

void setOrderProductQuantity(Order *orders, int pos){
    readInt(&orders[pos].lines[orders[pos].contLines].quantity, O_QUANTITY_MIN, O_QUANTITY_MAX, O_MSG_QUANTITY);
}

void setOrderProductPriceU(Order *orders, int pos, float pricePerUnit){
    orders[pos].lines[orders[pos].contLines].pricePerUnit = pricePerUnit;
}

void setOrderLines() {
}

void serOrderServiceCost() {
}

void setOrderStreet(Order *orders, int pos) {
    readString(orders[pos].address.street, O_STREET_LENGTH, O_MSG_STREET);
}

void setOrderNumber(Order *orders, int pos) {
    readInt(&orders[pos].address.number, O_NUMBER_MIN, O_NUMBER_MAX, O_MSG_NUMBER);
}

void setOrderPostalCode(Order *orders, int pos) {
    readString(orders[pos].address.postalCode, O_POSTALCODE_LENGTH, O_MSG_POSTALCODE);
}

void setOrderCity(Order *orders, int pos) {
    readString(orders[pos].address.city, O_CITY_LENGTH, O_MSG_CITY);
}

void serOrderAddress() {
}

void serOrderTotalPrice() {
}

void setOrderApprovalWorkerBI(Order *orders, Worker *workers, int pos, int *wCount) {
    long pBi , val = EOF;

    do {
        setOrderBI(&pBi, O_MSG_WORKER_APPROVAL_BI);
        val = verifyIfWorkerBIExist(workers, pBi, wCount);
        if (val != EOF && workers[val].type == 1) {
            orders[pos].approvalWorkerBI = pBi;
            setOrderApprovalDate(orders, pos);
        } else {
            printf(O_ERROR_MSG_BI_INVALID);
        }
    } while (val = EOF);
}

void setOrderExpectedDeliveryDate(Order *orders, int pos) {
    setDate(&orders[pos].expectedDeliveryDate, O_MSG_EXPECTED_DELIVERY_DATE);
}

void setOrderDeliveryman(Order *orders, Worker *workers, int pos, int wCount) {
    long delivermanBi, val = EOF;

    do {
        setOrderBI(&delivermanBi, O_MSG_WORKER_DELIVER_BI);
        val = verifyIfWorkerBIExist(workers, delivermanBi, &wCount);
        if (val != EOF && workers[val].type == 2) {
            orders[pos].deliveryman = workers[val].bi;
        } else {
            printf(O_ERROR_MSG_BI_INVALID);
        }
    } while (val = EOF);
}

void setOrderActualDeliveryDate(Order *orders, int pos) {
    setDate(&orders[pos].actualDeliveryDate, O_MSG_ACTUAL_DELIVERY_DATE);
}

void addOrder(){}

void editOrder(){}

void removeOrder(){
    printf(O_ERRO_MSG_REMOVE_ORDER);
}

void listOrder(){}

bool checkDate(Date *newDate, Date *oldDate) {
    bool val = false;
    if(newDate->year > oldDate->year) {
        val = true;
        return val;
    } else if(newDate->year == oldDate->year) {
        if(newDate->month > oldDate->month) {
            val = true;
            return val;
        } else if(newDate->month == oldDate->month) {
            if(newDate->day >= oldDate->day) {
                val = true;
                return val;
            }
        }
    }
    return val;
}


