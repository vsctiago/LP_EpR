/* 
 * File:   Product.h
 * Author: EpRG11
 *
 * Created on 13 de Fevereiro de 2016, 17:25
 */

#ifndef PRODUCT_H
#define	PRODUCT_H

#ifdef	__cplusplus
extern "C" {
#endif


    // LIMITS TO VARIABLES
#define PRODUCTS_SIZE 100
#define P_ID_MIN 1
#define P_ID_MAX 9999999
#define P_NAME_LENGTH 50+1
#define P_DESCRIPTION_LENGTH 200+1
#define P_PRICE_MIN 0.01f
#define P_PRICE_MAX 10000

    // MESSAGES FOR INPUTS
#define P_MSG_BI "Insert product id: "
#define P_MSG_ID "Insert product id: "
#define P_MSG_NAME "Insert name: "
#define P_MSG_DESCRIPTION "Insert description: "
#define P_MSG_PRICE "Insert Unit Price: "

    // ERROR MESSAGES
#define P_ERROR_MSG_FULL "ERROR: Full, can't add more product.\n"
#define P_ERROR_MSG_ID_NOTFOUND "ERROR: ID not found!\n"

    // FILE NAMES
#define P_FILE_NAME "Products"
#define P_FILE_NAME_COUNT "ProductCount" 
    
    typedef struct {
        int id;
        char name[P_NAME_LENGTH];
        char description[P_DESCRIPTION_LENGTH];
        float pricePerUnit;
    } Product;

// METHODS
void createProductsFile(Product products[]);
void saveProductsFile(Product products[]);
void readProductsFile(Product *products);
void createProductCountFile(int *pCount);
void saveProductCountFile(int *pCount);
int readProductCountFile(int *pCount);
void setProductId(Product *products, int pos);
void setProductName(Product *products, int pos);
void setProductDescription(Product *products, int pos);
bool verifyIfProductsFull(int *pCount);
int verifyIfProductIDExist(Product *products, int id, int *pCount);
void addProduct(Product *products, int *pCount); // HANDLING
void editProduct(Product *products, int *pCount); // HANDLING
void removeProduct(Product *products, int *pCount); // HANDLING
void listProducts(Product *products, int *pCount); // HANDLING



#ifdef	__cplusplus
}
#endif

#endif	/* PRODUCT_H */

