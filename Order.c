#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Order.h"
#include "Client.h"
#include "LP_Leitura.h"
#include "Worker.h"
#include "Product.h"


void createOrdersFile(Order o[]) {
    FILE *pOrders = fopen(O_FILE_NAME, "w");
    if (pOrders == (FILE*) NULL) {
        printf("Couldn't create %s File. ", O_FILE_NAME);
    } else {
        fwrite(o, sizeof (Order), ORDERS_SIZE, pOrders);
        fclose(pOrders);
    }
}

void saveOrdersFile(Order o[]) {
    FILE *pOrders = fopen(O_FILE_NAME, "w");
    if (pOrders == (FILE *) NULL) {
        puts("%s file doesn't exist.", O_FILE_NAME);
        puts("Couldn't save %s file.", O_FILE_NAME);
    } else {
        fwrite(o, sizeof (Order), ORDERS_SIZE, pOrders);
        puts("%s file saved.", O_FILE_NAME);
        fclose(pOrders);
    }
}

Client readOrdersFile(Order o[]) {

    FILE *pOrders = fopen(O_FILE_NAME, "r");
    if (pOrders == (FILE *) NULL) {
        puts("%s file doesn't exist", O_FILE_NAME);
        puts("Creating %s file now...", O_FILE_NAME);
        createOrdersFile(o);
        puts("%s file created", O_FILE_NAME);
        //readProductFile(p); 
    } else {
        fread(o, sizeof (Product), O_FILE_NAME, pOrders);
        fclose(pOrders);
    }
}

void createOrderCountFile(int *oCount) {
    FILE *pOcount = fopen(O_FILE_NAME_COUNT, "w");
    if (pOcount == (FILE*) NULL) {
        printf("Couldn't create %s File. ", O_FILE_NAME_COUNT);
    } else {
        fwrite(oCount, sizeof (int), 1, pOcount);
        fclose(pOcount);
    }
}

void saveOrderCountFile(int *oCount) {
    FILE *pOcount = fopen(O_FILE_NAME_COUNT, "w");
    if (pOcount == (FILE *) NULL) {
        puts("%s file doesn't exist.", O_FILE_NAME_COUNT);
        puts("Couldn't save %s file.", O_FILE_NAME_COUNT);
    } else {
        fwrite(oCount, sizeof (int), 1, pOcount);
        puts("%s file saved.", O_FILE_NAME_COUNT);
        fclose(pOcount);
    }
}

int readProductCountFile(int *oCount) {

    FILE *pOcount = fopen(O_FILE_NAME_COUNT, "r");
    if (pOcount == (FILE *) NULL) {
        puts("%s file doesn't exist");
        puts("Creating %s file now...", O_FILE_NAME_COUNT);
        createClientCountFile(oCount);
        puts("%s file created", O_FILE_NAME_COUNT);
        //readClientCountFile(prCount);
    } else {
        fread(oCount, sizeof (int), 1, pOcount);
        fclose(pOcount);
    }
}

void setOrderId(Order *o, int pos) {
    if (pos == 0) {
        o[pos].id = 1;
    } else {
        o[pos].id = o[pos - 1].id + 1;
    }
}

void setOrderBI(long *bi, char msg[]) {
    readLong(&bi, C_BI_MIN, C_BI_MAX, msg);
}

void setOrderClientBi(Order *o, int pos, Client *c, int cCount) {
    long *pBi, verify = EOF;

    do {
        setOrderBI(&pBi, O_MSG_CLIENT_BI);
        verify = verifyIfClientBIExist(c, pBi, cCount);
        if (verify == EOF) {
            printf(O_ERROR_MSG_BI_NOTFOUND);
        } else {
            o[pos].clientBI = pBi;
            setOrderDate(o, pos);
        }
    } while (verify = EOF);
}

void setCurrentDate(Date *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    date.year = tm.tm_year + 1900;
    date.month = tm.tm_mon + 1;
    date.day = tm.tm_mday;
}

void setDate(Date *date, char msgDate[]) {
    printf("%s", msgDate);
    readInt(date->year, O_DATE_YEAR_MIN, O_DATE_YEAR_MAX, O_MSG_DATE_YEAR);
    readInt(date->month, O_DATE_MONTH_MIN, O_DATE_MONTH_MAX, O_MSG_DATE_MONTH);
    readInt(date->day, O_DATE_DAY_MIN, O_DATE_DAY_MAX, O_MSG_DATE_DAY);
}

void setOrderDate(Order *o, int pos){
    setCurrentDate(o[pos].orderDate);
}

void setOrderProductId(Order *o, int pos, Product *p, int pCount){
    long *pId, verify = EOF;
    
    do {
        readLong(&pId,P_ID_MAX,P_ID_MIN,P_MSG_ID);
        verify = verifyIfProductIDExist(p, pId, pCount);
        if (verify == EOF) {
            printf(O_ERROR_MSG_ID_NOTFOUND);
        } else {
            p[pos].id = pId;
            setOrderProductPriceU(o, pos, p[verify].pricePerUnit);
            o[pos].contlines++;
        }
    } while (verify = EOF);
}

void setOrderProductQuantity(Order *o, int pos){
    readInt(o[pos].lines[o[pos].contlines].quantity, O_QUANTITY_MIN, O_QUANTITY_MAX, O_MSG_QUANTITY);
}

void setOrderProductPriceU(Order *o, int pos, float pricePerUnit){
    o[pos].lines[o[pos].contlines].pricePerUnit;
}

void setOrderLines() {
}

void serOrderServiceCost() {
}

void setOrderStreet(Order *o, int pos) {
    readString(o[pos].address.street, O_STREET_LENGTH, O_MSG_STREET);
}

void setOrderNumber(Order *o, int pos) {
    readInt(&o[pos].address.number, O_NUMBER_MIN, O_NUMBER_MAX, O_MSG_NUMBER);
}

void setOrderPostalCode(Order *o, int pos) {
    readString(o[pos].address.postalCode, O_POSTALCODE_LENGTH, O_MSG_POSTALCODE);
}

void setOrderCity(Order *o, int pos) {
    readString(o[pos].address.city, O_CITY_LENGTH, O_MSG_CITY);
}

void serOrderAddress() {
}

void serOrderTotalPrice() {
}

void setOrderApprovalWorkerBI(Order *o, Worker *w, int pos, int wCount) {
    long *pBi , val = EOF;

    do {
        setOrderBI(&pBi, O_MSG_WORKER_APPROVAL_BI);
        val = verifyIfWorkerBIExist(w, pBi, wCount);
        if (val != EOF && w[val].type == WorkerType.HANDLING) {
            o[pos].approvalWorkerBI = pBi;
            setOrderApprovalDate(o, pos);
        } else {
            printf(O_ERROR_MSG_BI_INVALID);
        }
    } while (val = EOF);
}

void setOrderApprovalDate(Order *o, int pos) {
    setCurrentDate(o[pos].approvalDate);
}

void setOrderExpectedDeliveryDate(Order *o, int pos) {
    setDate(o[pos].expectedDeliveryDate, O_MSG_EXPECTED_DELIVERY_DATE);
}

void setOrderDeliveryman(Order *o, Worker *w, int pos, int wCount) {
    long delivermanBi, val = EOF;

    do {
        setOrderBI(&delivermanBi, O_MSG_WORKER_DELIVER_BI);
        val = verifyIfWorkerBIExist(w, delivermanBi, wCount);
        if (val != EOF && w[val].type == WorkerType.DELIVERY) {
            o[pos].deliveryman = w[val];
        } else {
            printf(O_ERROR_MSG_BI_INVALID);
        }
    } while (val = EOF);
}

void setOrderActualDeliveryDate(Order *o, int pos) {
    setDate(o[pos].actualDeliveryDate, O_MSG_ACTUAL_DELIVERY_DATE);
}

void addOrder(){}

void editOrder(){}

void removeOrder(){
    printf(O_ERRO_MSG_REMOVE_ORDER);
}

void listOrder(){}
