/**
 * @file contact.h
 *
 * @brief Déclaration de la classe Contact
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef CDAA_CONTACT_H
#define CDAA_CONTACT_H

#include "utils.h"
#include <string>
#include <cctype>
#include <list>
#include <random>
#include "interaction.h"
#include "interactions.h"
#include "date.h"
#include <unordered_map>
#include "todos.h"


/**
 * Classe modélisant un contact.
 *
 * Un contact est composé :
 *      Son identifiant (-1 si non attribué par la base de données)
 *      Son prénom
 *      Son nom
 *      Son entreprise
 *      Son email
 *      Son numéro de téléphone
 *      Sa date de création
 * Un contact a également des interactions et une liste de tâche (TODO) à faire
 *
 * \brief Modélisation d'un Contact avec ses attributs
 */
class Contact {
private:
    int id; /*!< Identifiant du contact (-1 si non connu). */
    std::string lastName; /*!< Nom du contact. */
    std::string firstName; /*!< Prénom du contact. */
    std::string company; /*!< Entreprise du contact. */
    std::string email; /*!< Adresse email du contact. */
    std::string phone; /*!< Numéro de téléphone du contact. */
    std::string note; /*!< Note concernant le contact */
    Date creationDate; /*!< Date de création du Contact. */
    Interactions interactions; /*!< Liste des interactions liées au contact. */
    Todos todos; /*!< Liste des tâches liées au contact. */

public:
    // Voir contact.cpp pour la documentation des méthodes
    [[nodiscard]] int getId() const;
    void setId(int id);

    [[nodiscard]] const std::string &getLastName() const;
    void setLastName(const std::string &lastName);

    [[nodiscard]] const std::string &getFirstName() const;
    void setFirstName(const std::string &firstName);

    [[nodiscard]] const std::string &getCompany() const;
    void setCompany(const std::string &company);

    [[nodiscard]] const std::string &getEmail() const;
    void setEmail(const std::string &email);

    [[nodiscard]] const std::string &getPhone() const;
    void setPhone(const std::string &phone);

    [[nodiscard]] const Date &getCreationDate() const;
    void setCreationDate(const Date& date);

    [[nodiscard]] const std::string &getNote() const;
    void setNote(const std::string& note);

    [[nodiscard]] const Interactions& getInteractions()  const;
    [[nodiscard]] Interaction* getInteraction(int id);
    [[nodiscard]] Interactions getInteractionsBetween(Date& to, Date& from);
    [[nodiscard]] Interactions getUrgentInteractions();
    void setInteractions(Interactions is);
    void addInteraction(Interaction& interaction);
    void sortInteractions(bool reverse=false);
    void clearInteractions();

    [[nodiscard]] const Todos& getTodos()  const;
    [[nodiscard]] Todo* getTodo(int id);
    [[nodiscard]] Todos getTodosBetween(Date& to, Date& from);
    [[nodiscard]] Todos getUrgentTodos();
    void setTodos(Todos ts);
    void addTodo(Todo& todo);
    void sortTodos(bool reverse=false);
    void clearTodos();

    [[nodiscard]] std::string getQuery(int mode);

    // Virtual
    [[nodiscard]] std::string getFullName() const;

    std::unordered_map<std::string, std::string> toMap() const;

    friend bool operator==(const Contact& a, const Contact& b);
    friend bool operator!=(const Contact& a, const Contact& b);
    friend Contact& operator+=(Contact&a, Todos& b);
    friend Contact& operator+=(Contact&a, Interactions &b);
    friend std::ostream& operator<<(std::ostream& os, const Contact& i);

    Contact();
    Contact(std::string firstName, std::string lastName);
    Contact(std::string firstName, std::string lastName, std::string phone, std::string company, std::string email);
    ~Contact();

    static Contact fromMap(std::unordered_map<std::string, std::string> data);
};


#endif //CDAA_CONTACT_H
