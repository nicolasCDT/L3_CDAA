/**
 * @file todo.h
 *
 * @brief Déclaration de la classe todo. Elle permet de définir une tâche à faire plus tard en fonction d'une date (optionnelle)
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#ifndef CDAA_TODO_H
#define CDAA_TODO_H

#include <string>
#include <unordered_map>
#include "date.h"
#include "utils.h"

/**
 * Déclaration de la classe Todo.
 * Elle sert à définir une tâche avec (ou non) une date.
 * \brief Tâche a effectuer
 */
class Todo {
private:
    int id; /*!< Identifiant de la tâche. (Pas d'identifiant -> -1) */
    int ownerId; /*!< Identifiant de la tâche. (Pas d'identifiant -> -1) */
    std::string description; /*!< Description de la tâche à effectuer. */
    Date date; /*!< Date à laquelle la tâche doit être réalisé. Si pas de date -> 1er janvier 1970 (0 secondes) */

    // Voir todo.cpp pour la documentation des méthodes
public:
    void setId(int id);
    [[nodiscard]] int getId() const;

    void setOwnerId(int ownerId);
    [[nodiscard]] int getOwnerId() const;

    void setDescription(std::string& description);
    [[nodiscard]] std::string& getDescription();

    [[nodiscard]] Date& getDate();
    void setDate(const Date& date);

    [[nodiscard]] bool isUrgent();


    [[nodiscard]] std::string getQuery(int mode);

    std::unordered_map<std::string, std::string> toMap() const;

    friend bool operator==(const Todo& a, const Todo& b);
    friend bool operator!=(const Todo& a, const Todo& b);
    friend std::ostream& operator<<(std::ostream& os, const Todo& i);

    Todo();
    Todo(int ownerId, std::string& description, Date& date);
    ~Todo();


    static Todo fromMap(std::unordered_map<std::string, std::string> data);
};

#endif //CDAA_TODO_H
