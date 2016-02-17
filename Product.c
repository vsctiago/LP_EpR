#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.h"
#include "LP_Leitura.h"

void createProductsFile(Product products[]) {
    FILE *pProducts = fopen(P_FILE_NAME, "w");
    if (pProducts == (FILE*) NULL) {
        printf("Couldn't create %s File. ", P_FILE_NAME);
    } else {
        fwrite(products, sizeof (Product), PRODUCTS_SIZE, pProducts);
        fclose(pProducts);
    }
}

void saveProductsFile(Product products[]) {
    FILE *pProducts = fopen(P_FILE_NAME, "w");
    if (pProducts == (FILE *) NULL) {
        puts("%s file doesn't exist.", P_FILE_NAME);
        puts("Couldn't save %s file.", P_FILE_NAME);
    } else {
        fwrite(products, sizeof (Product), PRODUCTS_SIZE, pProducts);
        puts("%s file saved.", P_FILE_NAME);
        fclose(pProducts);
    }
}

Client readProductsFile(Product products[]) {

    FILE *pProducts = fopen(P_FILE_NAME, "r");
    if (pProducts == (FILE *) NULL) {
        puts("%s file doesn't exist", P_FILE_NAME);
        puts("Creating %s file now...", P_FILE_NAME);
        createProductsFile(products);
        puts("%s file created", P_FILE_NAME);
        //readProductFile(products); 
    } else {
        fread(products, sizeof (Product), PRODUCTS_SIZE, pProducts);
        fclose(pProducts);
    }
}

void createProductCountFile(int *prCount) {
    FILE *pPRcount = fopen(P_FILE_NAME_COUNT, "w");
    if (pPRcount == (FILE*) NULL) {
        printf("Couldn't create %s File. ", P_FILE_NAME);
    } else {
        fwrite(prCount, sizeof (int), 1, pPRcount);
        fclose(pPRcount);
    }
}

void saveProductCountFile(int *pCount) {
    FILE *pPcount = fopen(P_FILE_NAME_COUNT, "w");
    if (pPcount == (FILE *) NULL) {
        puts("%s file doesn't exist.", P_FILE_NAME_COUNT);
        puts("Couldn't save %s file.", P_FILE_NAME_COUNT);
    } else {
        fwrite(pCount, sizeof (int), 1, pPcount);
        puts("%s file saved.", P_FILE_NAME_COUNT);
        fclose(pPcount);
    }
}

int readProductCountFile(int *pCount) {

    FILE *pPcount = fopen(P_FILE_NAME_COUNT, "r");
    if (pPcount == (FILE *) NULL) {
        puts("%s file doesn't exist");
        puts("Creating %s file now...", P_FILE_NAME_COUNT);
        createClientCountFile(pCount);
        puts("%s file created", P_FILE_NAME_COUNT);
        //readClientCountFile(prCount);
    } else {
        fread(pCount, sizeof (int), 1, pPcount);
        fclose(pPcount);
    }
}

void setProductId(Product *products, int pos) {
    if (pos == 0) {
        products[pos].id = P_ID_MIN;
    } else {
        products[pos].id = products[pos - 1].id + 1;
    }
}

void setProductName(Product *products, int pos) {
    readString(products[pos].name, P_NAME_LENGTH, P_MSG_NAME);
}

void setProductDescription(Product *products, int pos) {
    readString(products[pos].description, P_DESCRIPTION_LENGTH, P_MSG_DESCRIPTION);
}

bool verifyIfProductsFull(int *pCount) {
    if (*pCount == PRODUCTS_SIZE) {
        puts(P_ERROR_MSG_FULL);
        return true;
    } else {
        return false;
    }
}

int verifyIfProductIDExist(Product *products, int id, int *pCount) {
    int pos;
    for (pos = 0; pos<*pCount; pos++) {
        if (products[pos].id == id) {
            return pos;
        }
    }
    return EOF;
}

void addProduct(Product *products, int *pCount) {
    if (verifyIfProductsFull(pCount) == false) {
        setProductId(products, *pCount);
        setProductName(products, *pCount);
        setProductDescription(products, *pCount);
        (*pCount)++;
        saveProductsFile(products);
        saveProductCountFile(pCount);
    }
}

void editProduct(Product *products, int *pCount) {
    int pID, pos;

    listProducts(products, *pCount);
    readInt(&pID, P_ID_MIN, P_ID_MAX, "Which Product to Edit(ID): ");
    pos = verifyIfProductIDExist(products, pID, pCount);
    if (pos != EOF) {
        setProductName(products, *pCount);
        setProductDescription(products, *pCount);
        saveProductsFile(products);
        saveProductCountFile(pCount);
    } else {
        puts(P_ERROR_MSG_ID_NOTFOUND);
    }
}

void removeProduct(Product *products, int *pCount) {
    int pID, pos;

    listProducts(products, *pCount);
    readInt(&pID, P_ID_MIN, P_ID_MAX, "Which Product to Remove(ID): ");
    pos = verifyIfProductIDExist(products, pID, pCount);
    if (pos != EOF) {
        for (pos; pos<*pCount - 1; pos++) {
            products[pos] = products[pos + 1];
        }
        (*pCount)--;
        saveProductsFile(products);
        saveProductCountFile(pCount);
    } else {
        puts(P_ERROR_MSG_ID_NOTFOUND);
    }
}

void listProducts(Product *products, int *pCount) {
    int pos;

    for (pos = 0; pos<*pCount; pos++) {
        printf("\n->Position [%d]\n");
        printf("\tProduct ID:\t%d\n", products[pos].id);
        printf("\tProduct NAME:\t%s\n", products[pos].name);
        printf("\tProduct DESCRIPTION:\t%s\n", products[pos].description);
    }
}