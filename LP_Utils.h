/** 
 * @file
 * @author ESTGF.LP
 *
 * @brief Biblioteca para operações diversas.
 *
 * @warning Esta biblioteca pretende ser uma base de trabalho. Caso pretenda 
 *      pode melhorar ou acrescentar novas funcionalidades de acordo com o 
 *      objectivo
 * 
 * @date 2013-02-01 14:00
 */

#ifndef LP_UTILS_H
#define	LP_UTILS_H


#define RESET   "\033[0m"
#define RED "\033[31m"


#ifdef	__cplusplus
extern "C" {
#endif

    void cleanInputBuffer();

    void cleanScreen();

#ifdef	__cplusplus
}
#endif

#endif	/* LP_UTILS_H */

