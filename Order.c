#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Order.h"



void setStreet(Order *o, int pos){
    readString(o[pos].address.street, O_STREET_LENGTH, O_MSG_STREET);
}

void setNumber(Order *o, int pos) {
    readInt(&o[pos].address.number, O_NUMBER_MIN, O_NUMBER_MAX, O_MSG_NUMBER);
}

void setPostalCode(Order *o, int pos){
    readString(o[pos].address.postalCode, O_POSTALCODE_LENGTH, O_MSG_POSTALCODE);
}

void setCity(Order *o, int pos){
    readString(o[pos].address.city, O_CITY_LENGTH, O_MSG_CITY);
}