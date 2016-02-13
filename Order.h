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


// LIMITS TO VARIABLES
#define ORDERS_SIZE 100
#define O_NUMBER_MIN 1
#define O_NUMBER_MAX 9999
#define O_STREET_LENGTH 100+1
#define O_POSTALCODE_LENGTH 8+1
#define O_CITY_LENGTH 50+1
#define O_ORDERLINE_LENGTH 20

// MESSAGES FOR INPUTS
#define O_MSG_STREET "Insert street: "
#define O_MSG_NUMBER "Insert street number: "
#define O_MSG_POSTALCODE "Insert Postal Code: "
#define O_MSG_CITY "Insert City: "

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

// STRUCT ADDRESS
typedef struct {
    char street[O_STREET_LENGTH];
    int number;
    char postalCode[O_POSTALCODE_LENGTH];
    char city[O_CITY_LENGTH];
} Address;

// STRUCT ORDERLINES
typedef struct {
    int idProduct;
    int quantity;
    float pricePerUnit;
} OrderLine;

// STRUCT ORDERS
typedef struct {
    int id;
    long clientBI;
    Date orderDate;
    Date approvalDate;
    long approvalWorkerBI;
    Date expectedDeliveryDate;
    Date actualDeliveryDate;
    Worker deliveryman;
    OrderLine lines[O_ORDERLINE_LENGTH];
    float serviceCost;
    Address address;
    Coordinates coord;
    float totalPrice;
    bool delivered;
} Order;


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* ORDER_H */

