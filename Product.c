#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.h"
#include "LP_Leitura.h"

void createProductFile(Product p[]) {
    FILE *pProduct = fopen("Product", "w");
    if (pProduct == (FILE*) NULL) {
        printf("Couldn't create Product File. ");
    } else {
        fwrite(p, sizeof (Product), PRODUCT_SIZE, pProduct);
        fclose(pProduct);
    }
}

void saveProductFile(Product p[]) {
    FILE *pProduct = fopen("Product", "w");
    if (pProduct == (FILE *) NULL) {
        puts("Product file doesn't exist.");
        puts("Couldn't save Product file.");
    } else {
        fwrite(p, sizeof (Product), PRODUCT_SIZE, pProduct);
        puts("Product file saved.");
        fclose(pProduct);
    }
}

Client readProductFile(Product p[]) {

    FILE *pProduct = fopen("Product", "r");
    if (pProduct == (FILE *) NULL) {
        puts("Product file doesn't exist");
        puts("Creating Product file now...");
        createProductFile(p);
        puts("Product file created");
        //readProductFile(p); 
    } else {
        fread(p, sizeof (Product), PRODUCT_SIZE, pProduct);
        fclose(pProduct);
    }
}

void createProductCountFile(int *prCount) {
    FILE *pPRcount = fopen("ProductCount", "w");
    if (pPRcount == (FILE*) NULL) {
        printf("Couldn't create ProductCount File. ");
    } else {
        fwrite(prCount, sizeof (int), 1, pPRcount);
        fclose(pPRcount);
    }
}

void saveProductCountFile(int *prCount) {
    FILE *pPRcount = fopen("ProductCount", "w");
    if (pPRcount == (FILE *) NULL) {
        puts("ProductCount file doesn't exist.");
        puts("Couldn't save ProductCount file.");
    } else {
        fwrite(prCount, sizeof (int), 1, pPRcount);
        puts("ProductCount file saved.");
        fclose(pPRcount);
    }
}

int readProductCountFile(int *prCount) {

    FILE *pPRcount = fopen("ProductCount", "r");
    if (pPRcount == (FILE *) NULL) {
        puts("ProductCount file doesn't exist");
        puts("Creating ProductCount file now...");
        createClientCountFile(prCount);
        puts("ProductCount file created");
        //readClientCountFile(prCount);
    } else {
        fread(prCount, sizeof (int), 1, pPRcount);
        fclose(pPRcount);
    }
}

void setId(Product *p, int pos) {
    if (pos == 0) {
        p[pos].id = 1;
    } else {
        p[pos].id = p[pos - 1].id + 1;
    }
}

void setName(Product *p, int pos) {
    readString(p[pos].name, P_NAME_LENGTH, P_MSG_NAME);
}

void setDescription(Product *p, int pos) {
    readString(p[pos].description, P_DESCRIPTION_LENGTH, P_MSG_DESCRIPTION);
}

bool verifyIfProductsFull(int *pCount) {
    if (*pCount == PRODUCT_SIZE) {
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
        setId(p, *pCount);
        setName(p, *pCount);
        setDescription(p, *pCount);
        (*pCount)++;
        saveProductFile(p);
        saveProductCountFile(pCount);
    }
}

void editProduct(Product *p, int *pCount) {
    int pID, pos;

    listProducts(p, *pCount);
    readInt(&pID, P_ID_MIN, P_ID_MAX, "Which Product to Edit(ID): ");
    pos = verifyIfProductIDExist(p, pID, pCount);
    if (pos != EOF) {
        setName(p, *pCount);
        setDescription(p, *pCount);
        saveProductFile(p);
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
        saveProductFile(p);
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