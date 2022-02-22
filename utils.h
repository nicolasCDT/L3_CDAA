/**
 * @file utils.h
 *
 * @brief Déclaration de la classe Utils
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <algorithm>
#include "date.h"

/**
 * Types possibles à utiliser dans la structure DB_todo
 */
enum DBTodoTypes
{
    INTERACTION,
    TODO,
    CONTACT,
};

/**
 * Sous-types possibles à utiliser dans la structure DB_todo
 */
enum DBTodoSubTypes
{
    UPDATE, // 0
    DELETE, // 1
    CREATE  // 2
};

/**
 * Structure DB_todo qui permet de modéliser une tâche à effectuer pour l'interface de base de données
 */
typedef struct DB_t
{
    unsigned int type; /*!< Type (INTERACTION, TODO, CONTACT) */
    unsigned int subtype; /*!< Sous-type (UPDATE, DELETE, CREATE) */
    int id; /*!< Identifiant de l'entité à traiter */
}DB_todo;


/**
 * Contient des utilitaires pour le bon fonctionnement du projet.
 * @brief Classe utilitaire (statique)
 */
class Utils
{
public:
    static void addSlashes(std::string& s);
    static bool checkForDate(std::string s, Date* d);
};

#endif // UTILS_H
