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
#define O_SERVICECOST_MIN 0
#define O_SERVICECOST_MAX 100
#define O_NUMBER_MIN 1
#define O_NUMBER_MAX 9999
#define O_STREET_LENGTH 100+1
#define O_POSTALCODE_PREFIX_MIN 1000
#define O_POSTALCODE_PREFIX_MAX 9999
#define O_POSTALCODE_SUFIX_MIN 0
#define O_POSTALCODE_SUFIX_MAX 999
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
#define O_MSG_ADDMORE_LINES "Want to add more? "
#define O_MSG_SERICECOST "Insert service cost: "
#define O_MSG_STREET "Insert street: "
#define O_MSG_NUMBER "Insert street number: "
#define O_MSG_POSTALCODE "Insert Postal Code: \n"
#define O_MSG_POSTALCODE_PREFIX "Prefix: "
#define O_MSG_POSTALCODE_SUFIX "Sufix: "
#define O_MSG_CITY "Insert City: "
#define O_MSG_WORKER_APPROVAL_BI "Insert worker approval BI: "
#define O_MSG_WORKER_DELIVER_BI "Insert worker deliver BI: "
#define O_MSG_LIST_BY_DATE "List All Orders by Date: "
#define O_MSG_LIST_FROM_CLIENT "List From Client BI: "

// ERROR MESSAGES
#define O_ERROR_MSG_FULL RED "ERROR: " RESET "Full, can't add more orders.\n"
#define O_ERROR_MSG_BI_INVALID RED "ERROR: " RESET "BI invalid! \n"
#define O_ERROR_MSG_BI_NOTFOUND RED "ERROR: " RESET "BI not found!\n"
#define O_ERROR_MSG_ID_NOTFOUND RED "ERROR: " RESET "ID not found!\n"

// FILE NAMES
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

typedef struct {
    int prefix;
    int sufix;
} PostalCode;

// STRUCT ADDRESS
typedef struct {
    char street[O_STREET_LENGTH];
    int number;
    PostalCode postalCode;
    char city[O_CITY_LENGTH];
    Coordinates coord;
} Address;

// STRUCT ORDERS
typedef struct {
    int id;
    long clientBI;
    Date orderDate;
    OrderLine lines[O_ORDERLINE_LENGTH];
    int contLines;
    float serviceCost;
    Address address;
    float totalPrice;
    long approvalWorkerBI;
    Date approvalDate;
    Date expectedDeliveryDate;
    long deliveryman;
    bool delivered;
    Date actualDeliveryDate;
} Order;

// METHODS
void createOrdersFile(Order orders[]);
void saveOrdersFile(Order orders[]);
void readOrdersFile(Order *orders);
void createOrderCountFile(int *oCount);
void saveOrderCountFile(int *oCount);
int readProductCountFile(int *oCount);
void setOrderId(Order *orders, int pos);
void setOrderDate(Order *orders, int pos);
void setOrderBI(long *bi, char msg[]);
void setOrderClientBi(Order *orders, int pos, Client *c, int *cCount);
void setOrderApprovalDate(Order *orders, int pos);
void setCurrentDate(Date *date);
void setDate(Date *date, char msgDate[]);
void setOrderProductId(Order *orders, int pos, Product *products, int *pCount);
void setOrderProductQuantity(Order *orders, int pos);
void setOrderProductPriceU(Order *orders, int pos, float pricePerUnit);
void setOrderLines(Order *orders, int pos, Product *products, int *pCount);
void serOrderServiceCost(Order *orders, int pos);
void setOrderStreet(Order *orders, int pos);
void setOrderNumber(Order *orders, int pos);
void setOrderPostalCode(Order *orders, int pos);
void setOrderCity(Order *orders, int pos);
void setOrderAddress(Order *orders, int pos);
void setOrderTotalPrice(Order *orders, int pos);
void setOrderApprovalWorkerBI(Order *orders, Worker *workers, int pos, int *wCount);
void setOrderExpectedDeliveryDate(Order *orders, int pos);
void setOrderDeliveryman(Order *orders, Worker *workers, int pos, int wCount);
void setOrderActualDeliveryDate(Order *orders, int pos);
void addOrder(Order *orders, int pos, Client *clients, int *cCount, Product *products, int *pCount);
void editOrder(); // TODO
void removeOrderClient(Order *orders, int *oCount, long clientBI, int orderID);
void listMyOrders(Order *orders, int *oCount, long clientBI);
void listMyOrdersPendingApproval(Order *orders, int *oCount, long clientBI);
void listMyOrdersPendingDelivery(Order *orders, int *oCount, long clientBI);
void listAllOrdersByDate(Order *orders, int *oCount);
bool checkDate(Date *newDate, Date *oldDate);




#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* ORDER_H */

