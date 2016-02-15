#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.h"
#include "LP_Leitura.h"

void createProductsFile(Product p[]) {
    FILE *pProducts = fopen(P_FILE_NAME, "w");
    if (pProducts == (FILE*) NULL) {
        printf("Couldn't create %s File. ", P_FILE_NAME);
    } else {
        fwrite(p, sizeof (Product), PRODUCTS_SIZE, pProducts);
        fclose(pProducts);
    }
}

void saveProductsFile(Product p[]) {
    FILE *pProducts = fopen(P_FILE_NAME, "w");
    if (pProducts == (FILE *) NULL) {
        puts("%s file doesn't exist.", P_FILE_NAME);
        puts("Couldn't save %s file.", P_FILE_NAME);
    } else {
        fwrite(p, sizeof (Product), PRODUCTS_SIZE, pProducts);
        puts("%s file saved.", P_FILE_NAME);
        fclose(pProducts);
    }
}

Client readProductsFile(Product p[]) {

    FILE *pProducts = fopen(P_FILE_NAME, "r");
    if (pProducts == (FILE *) NULL) {
        puts("%s file doesn't exist", P_FILE_NAME);
        puts("Creating %s file now...", P_FILE_NAME);
        createProductsFile(p);
        puts("%s file created", P_FILE_NAME);
        //readProductFile(p); 
    } else {
        fread(p, sizeof (Product), PRODUCTS_SIZE, pProducts);
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

void saveProductCountFile(int *prCount) {
    FILE *pPRcount = fopen(P_FILE_NAME_COUNT, "w");
    if (pPRcount == (FILE *) NULL) {
        puts("%s file doesn't exist.", P_FILE_NAME_COUNT);
        puts("Couldn't save %s file.", P_FILE_NAME_COUNT);
    } else {
        fwrite(prCount, sizeof (int), 1, pPRcount);
        puts("%s file saved.", P_FILE_NAME_COUNT);
        fclose(pPRcount);
    }
}

int readProductCountFile(int *prCount) {

    FILE *pPRcount = fopen(P_FILE_NAME_COUNT, "r");
    if (pPRcount == (FILE *) NULL) {
        puts("%s file doesn't exist");
        puts("Creating %s file now...", P_FILE_NAME_COUNT);
        createClientCountFile(prCount);
        puts("%s file created", P_FILE_NAME_COUNT);
        //readClientCountFile(prCount);
    } else {
        fread(prCount, sizeof (int), 1, pPRcount);
        fclose(pPRcount);
    }
}

void setProductId(Product *p, int pos) {
    if (pos == 0) {
        p[pos].id = P_ID_MIN;
    } else {
        p[pos].id = p[pos - 1].id + 1;
    }
}

void setProductName(Product *p, int pos) {
    readString(p[pos].name, P_NAME_LENGTH, P_MSG_NAME);
}

void setProductDescription(Product *p, int pos) {
    readString(p[pos].description, P_DESCRIPTION_LENGTH, P_MSG_DESCRIPTION);
}

bool verifyIfProductsFull(int *pCount) {
    if (*pCount == PRODUCTS_SIZE) {
        puts(P_ERROR_MSG_FULL);
        return true;
    } else {
        return false;
    }
}

int verifyIfProductIDExist(Product *p, int id, int *pCount) {
    int pos;
    for (pos = 0; pos<*pCount; pos++) {
        if (p[pos].id == id) {
            return pos;
        }
    }
    return EOF;
}

void addProduct(Product *p, int *pCount) {
    if (verifyIfProductsFull(pCount) == false) {
        setProductId(p, *pCount);
        setProductName(p, *pCount);
        setProductDescription(p, *pCount);
        (*pCount)++;
        saveProductsFile(p);
        saveProductCountFile(pCount);
    }
}

void editProduct(Product *p, int *pCount) {
    int pID, pos;

    listProducts(p, *pCount);
    readInt(&pID, P_ID_MIN, P_ID_MAX, "Which Product to Edit(ID): ");
    pos = verifyIfProductIDExist(p, pID, pCount);
    if (pos != EOF) {
        setProductName(p, *pCount);
        setProductDescription(p, *pCount);
        saveProductsFile(p);
        saveProductCountFile(pCount);
    } else {
        puts(P_ERROR_MSG_ID_NOTFOUND);
    }
}

void removeProduct(Product *p, int *pCount) {
    int pID, pos;

    listProducts(p, *pCount);
    readInt(&pID, P_ID_MIN, P_ID_MAX, "Which Product to Remove(ID): ");
    pos = verifyIfProductIDExist(p, pID, pCount);
    if (pos != EOF) {
        for (pos; pos<*pCount - 1; pos++) {
            p[pos] = p[pos + 1];
        }
        (*pCount)--;
        saveProductsFile(p);
        saveProductCountFile(pCount);
    } else {
        puts(P_ERROR_MSG_ID_NOTFOUND);
    }
}

void listProducts(Product *p, int *pCount) {
    int pos;

    for (pos = 0; pos<*pCount; pos++) {
        printf("\n->Position [%d]\n")
        printf("\tProduct ID:\t%d\n", p[pos].id);
        printf("\tProduct NAME:\t%s\n", p[pos].name);
        printf("\tProduct DESCRIPTION:\t%s\n", p[pos].description);
    }
}