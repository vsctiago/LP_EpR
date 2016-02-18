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

void readOrdersFile(Order *orders) {

    FILE *pOrders = fopen(O_FILE_NAME, "r");
    if (pOrders == (FILE *) NULL) {
        printf("%s file doesn't exist\n", O_FILE_NAME);
        printf("Creating %s file now...\n", O_FILE_NAME);
        createOrdersFile(orders);
        printf("%s file created\n", O_FILE_NAME);
        readOrdersFile(orders); 
    } else {
        fread(orders, sizeof (Order), ORDERS_SIZE, pOrders);
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
        readOrderCountFile(oCount);
    } else {
        fread(oCount, sizeof (int), 1, pOcount);
        fclose(pOcount);
    }
}

int verifyIfOrderIDExist(Order *orders, int id, int *oCount) {
    int pos;
    for (pos = 0; pos<*oCount; pos++) {
        if (orders[pos].id == id) {
            return pos;
        }
    }
    return EOF;
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

void setOrderClientBi(Order *orders, int pos, long clientBI) {
    orders[pos].clientBI = clientBI;
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
    long pId, val = EOF;
    
    do {
        readLong(&pId,P_ID_MAX,P_ID_MIN,P_MSG_ID);
        val = verifyIfProductIDExist(products, pId, pCount);
        if (val == EOF) {
            printf(O_ERROR_MSG_ID_NOTFOUND);
        } else {
            orders[pos].lines[orders[pos].contLines].idProduct = pId;
            setOrderProductQuantity(orders, pos);
            setOrderProductPriceU(orders, pos, products[val].pricePerUnit);
            orders[pos].contLines++;
        }
    } while (val == EOF);
}

void setOrderProductQuantity(Order *orders, int pos){
    readInt(&orders[pos].lines[orders[pos].contLines].quantity, O_QUANTITY_MIN, O_QUANTITY_MAX, O_MSG_QUANTITY);
}

void setOrderProductPriceU(Order *orders, int pos, float pricePerUnit){
    orders[pos].lines[orders[pos].contLines].pricePerUnit = pricePerUnit;
}

void setOrderLines(Order *orders, int pos, Product *products, int *pCount) {
    bool val = true;
    do {
        setOrderProductId(orders, pos, products, pCount);
        readBool(&val, O_MSG_ADDMORE_LINES);
    } while(val == true);
}

void setOrderServiceCost(Order *orders, int pos) {
    readFloat(&orders[pos].serviceCost, O_SERVICECOST_MIN, O_SERVICECOST_MAX, O_MSG_SERICECOST);
}

void setOrderStreet(Order *orders, int pos) {
    readString(orders[pos].address.street, O_STREET_LENGTH, O_MSG_STREET);
}

void setOrderNumber(Order *orders, int pos) {
    readInt(&orders[pos].address.number, O_NUMBER_MIN, O_NUMBER_MAX, O_MSG_NUMBER);
}

void setOrderPostalCode(Order *orders, int pos) {
    printf(O_MSG_POSTALCODE);
    readInt(&orders[pos].address.postalCode.prefix, O_POSTALCODE_PREFIX_MIN, O_POSTALCODE_PREFIX_MAX, O_MSG_POSTALCODE_PREFIX);
    readInt(&orders[pos].address.postalCode.sufix, O_POSTALCODE_SUFIX_MIN, O_POSTALCODE_SUFIX_MAX, O_MSG_POSTALCODE_SUFIX);
}

void setOrderCity(Order *orders, int pos) {
    readString(orders[pos].address.city, O_CITY_LENGTH, O_MSG_CITY);
}

void setOrderAddress(Order *orders, int pos) {
    setOrderStreet(orders, pos);
    setOrderNumber(orders, pos);
    setOrderPostalCode(orders, pos);
    setOrderCity(orders, pos);
}

void setOrderTotalPrice(Order *orders, int pos) {
    float total = 0, linePrice = 0;
    int i = 0;
    for(i=0; i < orders->contLines; i++) {
        linePrice += (orders[pos].lines[i].pricePerUnit * orders[pos].lines[i].quantity);
        total += linePrice;
        linePrice = 0;
    }
    orders[pos].totalPrice = total;
}

void setOrderApprovalWorkerBI(Order *orders, Worker *workers, int *oCount, long workerBI, int *wCount) {
    int pos = EOF;
    int orderID = 0;

    do {
        
        readInt(&orderID, O_ID_MIN, O_ID_MAX, O_MSG_ID);
        pos = verifyIfOrderIDExist(orders, orderID, oCount);
        if (pos != EOF && orders[pos].approvalWorkerBI != 0) {
            orders[pos].approvalWorkerBI = workerBI;
            setOrderApprovalDate(orders, pos);
            setOrderExpectedDeliveryDate(orders, pos);
            setOrderDeliveryman(orders, workers, pos, wCount);
            orders[pos].delivered = false;
            saveOrdersFile(orders);
            saveOrderCountFile(&pos);
        } else {
            printf(O_ERROR_MSG_BI_INVALID);
        }
    } while (pos = EOF);
}

void setOrderExpectedDeliveryDate(Order *orders, int pos) {
    setDate(&orders[pos].expectedDeliveryDate, O_MSG_EXPECTED_DELIVERY_DATE);
}

void setOrderDeliveryman(Order *orders, Worker *workers, int pos, int *wCount) {
    long delivermanBi, val = EOF;

    do {
        setOrderBI(&delivermanBi, O_MSG_WORKER_DELIVER_BI);
        val = verifyIfWorkerBIExist(workers, delivermanBi, wCount);
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

void setOrderDelivered(Order *orders, int *oCount, long deliverymanBI) {
    int pos, tmpID;
    
    readInt(&tmpID, O_ID_MIN, O_ID_MAX, O_MSG_ID);
    pos = verifyIfOrderIDExist(orders, tmpID, oCount);
    if(pos != EOF) {
        if(orders[pos].delivered == false && orders[pos].deliveryman == deliverymanBI &&
            orders[pos].approvalWorkerBI != 0) {
        
            orders[pos].delivered = true;
            setOrderActualDeliveryDate(orders, pos);
            saveOrdersFile(orders);
            saveOrderCountFile(&pos);
        }
    } else {
        printf(O_ERROR_MSG_ID_NOTFOUND);
    }
    
}

void addOrder(Order *orders, int pos, Product *products, int *pCount, long clientBI) {
    
    setOrderId(orders, pos);
    setOrderClientBi(orders, pos, clientBI);
    setOrderDate(orders, pos);
    listProducts(products, pCount);
    setOrderLines(orders, pos, products, pCount);
    setOrderServiceCost(orders, pos);
    setOrderAddress(orders, pos);
    setOrderTotalPrice(orders, pos);
    orders[pos].approvalWorkerBI = 0;
    saveOrdersFile(orders);
    saveOrderCountFile(&pos);
}

void editOrder(Order *orders, int pos){
    
}

void removeOrderClient(Order *orders, int *oCount, long clientBI){
    int pos = 0, i = 0, orderID = 0;
    readInt(&orderID, O_ID_MIN, O_ID_MAX, O_MSG_ID);
    
    pos = verifyIfOrderIDExist(orders, orderID, oCount);
    if(pos != EOF) {
        if(orders[pos].clientBI == clientBI && orders[pos].approvalWorkerBI != 0) {
            for(i=pos; i<*oCount; i++) {
                orders[i] = orders[i + 1];
            }
            (*oCount)--;
            saveOrdersFile(orders);
            saveOrderCountFile(oCount);
        } else {
            printf(O_ERROR_MSG_CANNOT_REMOVE);
        }
    } else {
        printf(P_ERROR_MSG_ID_NOTFOUND);
    }
}

void listMyOrders(Order *orders, int *oCount, long clientBI) {
    int pos = 0;
    
    for(pos=0; pos<*oCount; pos++) {
        if(orders[pos].clientBI == clientBI) {
            printf("[%d] BI: %ld | "
                    "OrderDate: %d/%d/%d | "
                    "Total: %.2f",
                    orders[pos].id,
                    orders[pos].clientBI,
                    orders[pos].orderDate.day,
                    orders[pos].orderDate.month,
                    orders[pos].orderDate.year,
                    orders[pos].totalPrice);
        }
    }
}

void listMyOrdersPendingApproval(Order *orders, int *oCount, long clientBI) {
    int pos = 0;
    for(pos=0; pos<*oCount; pos++) {
        if(orders[pos].clientBI == clientBI && orders[pos].approvalWorkerBI == 0) {
            printf("[%d] BI: %ld | "
                    "OrderDate: %d/%d/%d | "
                    "Total: %.2f",
                    orders[pos].id,
                    orders[pos].clientBI,
                    orders[pos].orderDate.day,
                    orders[pos].orderDate.month,
                    orders[pos].orderDate.year,
                    orders[pos].totalPrice);
        }
    }
}

void listMyOrdersPendingDelivery(Order *orders, int *oCount, long clientBI) {
    int pos = 0;
    for(pos=0; pos<*oCount; pos++) {
        if(orders[pos].clientBI == clientBI && orders[pos].approvalWorkerBI != 0 &&
                orders[pos].delivered == 0) {
            
            printf("[%d] BI: %ld | "
                    "OrderDate: %d/%d/%d | "
                    "Total: %.2f",
                    orders[pos].id,
                    orders[pos].clientBI,
                    orders[pos].orderDate.day,
                    orders[pos].orderDate.month,
                    orders[pos].orderDate.year,
                    orders[pos].totalPrice);
        }
    }
}

void listAllOrdersByDate(Order *orders, int *oCount) {
    Date date;
    int pos = 0;
    
    setDate(&date, O_MSG_LIST_BY_DATE);
    for(pos = 0; pos<*oCount; pos++) {
        if(orders[pos].expectedDeliveryDate.year == date.year &&
                orders[pos].expectedDeliveryDate.month == date.month &&
                orders[pos].expectedDeliveryDate.day == date.day) {
            
            printf("---------------------------");
            printf("[%d] BI: %ld | "
                    "OrderDate: %d/%d/%d | "
                    "Total: %.2f",
                    orders[pos].id, orders[pos].clientBI,
                    orders[pos].orderDate.day,
                    orders[pos].orderDate.month,
                    orders[pos].orderDate.year,
                    orders[pos].totalPrice);
        }
    }
}

void listPendingOrdersByWorkerByDate(Order *orders, int *oCount, long deliverymanBI) {
    Date date;
    int pos = 0;
    
    setDate(&date, O_MSG_LIST_BY_DATE);
    for(pos = 0; pos<*oCount; pos++) {
        if(orders[pos].deliveryman == deliverymanBI &&
                orders[pos].expectedDeliveryDate.year == date.year &&
                orders[pos].expectedDeliveryDate.month == date.month &&
                orders[pos].expectedDeliveryDate.day == date.day) {
            
            printf("---------------------------");
            printf("[%d] BI: %ld | "
                    "OrderDate: %d/%d/%d | "
                    "Total: %.2f",
                    orders[pos].id, orders[pos].clientBI,
                    orders[pos].orderDate.day,
                    orders[pos].orderDate.month,
                    orders[pos].orderDate.year,
                    orders[pos].totalPrice);
        }
    }
}

void listAllPendingApprovedProducts(Order *orders, Product *products, int *pCount, int *oCount) {
    int pPos = 0, oPos = 0, linePos = 0, totalPending = 0, tmpPid = 0;
    
    for(pPos=0; pPos<*pCount; pPos++) {
        tmpPid = products[pPos].id;
        for(oPos=0; oPos<*oCount; oPos++) {
            if(orders[oPos].approvalWorkerBI != 0 && orders[oPos].delivered == false) {
                for(linePos=0; linePos<orders[oPos].contLines; linePos++) {
                    if(orders[oPos].lines[linePos].idProduct == tmpPid) {
                        totalPending++;
                    }
                }
            }
        }
        printf("Product ID: [%d] |"
                "Total Pending: %d",
                tmpPid,
                totalPending);
        
        totalPending = 0;
    }
}

float listOrdersByTotalValueFromClient(Order *orders, Client *clients, int *oCount, int *cCount) {
    int oPos = 0, pos = 0;
    float totalValue = 0;
    long tmpBI;
    
    setOrderBI(&tmpBI, O_MSG_LIST_FROM_CLIENT);
    pos = verifyIfClientBIExist(clients, tmpBI, cCount);
    if(pos != EOF) {
        for(oPos=0; oPos<*oCount; oPos++) {
            if(orders[oPos].clientBI == tmpBI) {
                printf("Order ID: [%d] | "
                        "Total: %.2f",
                        orders[oPos].id,
                        orders[oPos].totalPrice);

                totalValue += orders[oPos].totalPrice;
            }
        }
        printf("Total Value from all Order: %f", totalValue);
    } else {
        printf(C_ERROR_MSG_BI_NOTFOUND);
    }
    return totalValue;
}

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


