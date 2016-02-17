/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Order.h
 * Author: Utilizador
 *
 * Created on 7 de Fevereiro de 2016, 17:31
 */

#ifndef ORDER_H
#define ORDER_H

#include "LP_Utils.h"
#include "Worker.h"
#include "Product.h"


// LIMITS TO VARIABLES
#define ORDERS_SIZE 100
#define O_ID_MIN 1
#define O_ID_MAX 9999999
#define O_QUANTITY_MIN 1
#define O_QUANTITY_MAX 100
#define O_DATE_DAY_MIN 1
#define O_DATE_DAY_MAX 31
#define O_DATE_MONTH_MIN 1
#define O_DATE_MONTH_MAX 12
#define O_DATE_YEAR_MIN 1837
#define O_DATE_YEAR_MAX 2038
#define O_NUMBER_MIN 1
#define O_NUMBER_MAX 9999
#define O_STREET_LENGTH 100+1
#define O_POSTALCODE_LENGTH 8+1
#define O_CITY_LENGTH 50+1
#define O_ORDERLINE_LENGTH 20

// MESSAGES FOR INPUTS
#define O_MSG_CLIENT_BI "Insert client BI: "
#define O_MSG_QUANTITY "Insert quantity: "
#define O_MSG_EXPECTED_DELIVERY_DATE "Insert expected delivery date:\n"
#define O_MSG_ACTUAL_DELIVERY_DATE "Insert actual delivery date:\n"
#define O_MSG_DATE_YEAR "\tyear: "
#define O_MSG_DATE_MONTH "\tmonth: "
#define O_MSG_DATE_DAY "\tday: "
#define O_MSG_STREET "Insert street: "
#define O_MSG_NUMBER "Insert street number: "
#define O_MSG_POSTALCODE "Insert Postal Code: "
#define O_MSG_CITY "Insert City: "
#define O_MSG_WORKER_APPROVAL_BI "Insert worker approval BI: "
#define O_MSG_WORKER_DELIVER_BI "Insert worker deliver BI: "

// ERROR MESSAGES
#define O_ERROR_MSG_FULL RED "ERROR: " RESET "Full, can't add more orders.\n"
#define O_ERROR_MSG_BI_INVALID RED "ERROR: " RESET "BI invalid! \n"
#define O_ERROR_MSG_BI_NOTFOUND RED "ERROR: " RESET "BI not found!\n"
#define O_ERROR_MSG_ID_NOTFOUND RED "ERROR: " RESET "ID not found!\n"
#define O_ERRO_MSG_REMOVE_ORDER RED "YOU SHOULDN'T REMOVE ANY ORDER\n" RESET

// NOMES DE FICHEIROS
#define O_FILE_NAME "Orders"
#define O_FILE_NAME_COUNT "OrderCount" 

// STRUCT COORDINATES

typedef struct {
    float latitude;
    float longitude;
} Coordinates;

// STRUCT DATE

typedef struct {
    int day;
    int month;
    int year;
} Date;

// STRUCT ORDERLINES

typedef struct {
    int idProduct;
    int quantity;
    float pricePerUnit;
} OrderLine;

// STRUCT ADDRESS

typedef struct {
    char street[O_STREET_LENGTH];
    int number;
    char postalCode[O_POSTALCODE_LENGTH];
    char city[O_CITY_LENGTH];
    Coordinates coord;
} Address;

// STRUCT ORDERS

typedef struct {
    int id;
    long clientBI;
    Date orderDate;
    OrderLine lines[O_ORDERLINE_LENGTH];
    int contlines;
    float serviceCost;
    Address address;
    float totalPrice;
    long approvalWorkerBI;
    Date approvalDate;
    Date expectedDeliveryDate;
    Worker deliveryman;
    Date actualDeliveryDate;
    bool delivered;
} Order;

// Métodos
void createOrdersFile(Order o[]);
void saveOrdersFile(Order o[]);
Client readOrdersFile(Order o[]);
void createOrderCountFile(int *oCount);
void saveOrderCountFile(int *oCount);
int readProductCountFile(int *oCount);
void setOrderId(Order *o, int pos);
void setOrderDate(Order *o, int pos);
void setOrderBI(long *bi, char msg[]);
void setOrderClientBi(Order *o, int pos, Client *c, int *cCount);
void setOrderApprovalDate(Order *o, int pos);
void setCurrentDate(Date *date);
void setDate(Date *date, char msgDate[]);
void setOrderProductId(Order *o, int pos, Product *p, int *pCount);
void setOrderProductQuantity(Order *o, int pos);
void setOrderProductPriceU(Order *o, int pos, float pricePerUnit);
void setOrderLines();
void serOrderServiceCost();
void setOrderStreet(Order *o, int pos);
void setOrderNumber(Order *o, int pos);
void setOrderPostalCode(Order *o, int pos);
void setOrderCity(Order *o, int pos);
void serOrderAddress();
void serOrderTotalPrice();
void setOrderApprovalWorkerBI(Order *o, Worker *w, int pos, int *wCount);
void setOrderExpectedDeliveryDate(Order *o, int pos);
void setOrderDeliveryman(Order *o, Worker *w, int pos, int wCount);
void setOrderActualDeliveryDate(Order *o, int pos);
void addOrder();
void editOrder();
void removeOrder();
void listOrder();




#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* ORDER_H */

