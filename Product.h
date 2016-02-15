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

    // MESSAGES FOR INPUTS
#define P_MSG_BI "Insert id: "
#define P_MSG_NAME "Insert name: "
#define P_MSG_DESCRIPTION "Insert description: "

    // ERROR MESSAGES
#define P_ERROR_MSG_FULL "ERROR: Full, can't add more product.\n"
#define P_ERROR_MSG_ID_NOTFOUND "ERROR: ID not found!\n"

    // NOMES DE FICHEIROS
#define P_FILE_NAME "Products"
#define P_FILE_NAME_COUNT "ProductCount" 
    
    typedef struct {
        int id;
        char name[P_NAME_LENGTH];
        char description[P_DESCRIPTION_LENGTH];
    } Product;


#ifdef	__cplusplus
}
#endif

#endif	/* PRODUCT_H */

