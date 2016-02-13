/* 
 * File:   Client.h
 * Author: Utilizador
 *
 * Created on 6 de Fevereiro de 2016, 15:52
 */

#ifndef CLIENT_H
#define CLIENT_H

// LIMITS TO VARIABLES
#define CLIENTS_SIZE 100
#define C_BI_MIN 10000000
#define C_BI_MAX 99999999
#define C_NAME_LENGTH 100+1
#define C_PASSWORD_LENGTH 20+1
#define C_BANKNUMBER_MIN 10000000
#define C_BANKNUMBER_MAX 99999999
#define C_ACCOUNTNUMBER_MIN 0
#define C_ACCOUNTNUMBER_MAX 99999999
#define C_PHONENUMBER_MIN 900000000
#define C_PHONENUMBER_MAX 999999999


// MESSAGES FOR INPUTS
#define C_MSG_BI "Insert BI: "
#define C_MSG_PASSWORD "Insert Password: "
#define C_MSG_NAME "Insert name: "
#define C_MSG_BANKNUMBER "Insert First 8 Numbers: "
#define C_MSG_ACCOUNTNUMBER "Insert Last 8 Numbers: "
#define C_MSG_PHONENUMBER "Insert PhoneNumber: "


// ERROR MESSAGES
#define C_ERROR_MSG_FULL "ERROR: Full, can't add more cliens. "
#define C_ERROR_MSG_BI_EXISTS "ERROR: That BI already exists. "
#define C_ERROR_MSG_BI_NOTFOUND "ERROR: BI not found! "
#define C_ERROR_MSG_PASS_WRONG "ERROR: Wrong Password. "

// STRUCT CREDITCARD
typedef struct {
    long bankNumber;
    long accountNumber;
} CreditCard;

// STRUCT CLIENT
typedef struct {
    long bi;
    char password[C_PASSWORD_LENGTH];
    char name[C_NAME_LENGTH];
    CreditCard creditCard;
    long phoneNumber;
} Client;


void setBI(Client *c, int pos);
void setPassword(Client *c, int pos);
void setName(Client *c, int pos);
void setCreditCard(Client *c, int pos);
void setPhoneNumber(Client *c, int pos);
void setStreet(Client *c, int pos);
void setNumber(Client *c, int pos);
void setPostalCode(Client *c, int pos);
void setCity(Client *c, int pos);
bool verifyIfClientsFull(int *cCount);
int verifyIfClientBIExist(Client *c, long bi, int *cCount);
void addClient(Client *c, int *cCount);
void listClients(Client *c, int *cCount);
void editClient(Client *c, int *cCount);
void removeClient(Client *c, int *cCount);
void createClientsFile(Client c[]);
void saveClientsFile(Client c[]);
Client readClientsFile(Client c[]);
void createClientCountFile(int *cCount);
void saveClientCountFile(int *cCount);
int readClientCountFile(int *cCount);


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* CLIENT_H */

