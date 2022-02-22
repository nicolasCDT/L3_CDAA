/**
 * @file contacts.h
 *
 * @brief Déclaration de la classe Contacts
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef CDAA_CONTACTS_H
#define CDAA_CONTACTS_H

#include <list>
#include <string>
#include <iostream>
#include <QtSql>
#include "contact.h"
#include "interactions.h"
#include "interaction.h"
#include "todos.h"
#include "todo.h"


/**
 * Objet pour manier plus facilement une liste de Contact.
 * \brief Liste de Contact permettant une gestion plus facile et opérations spécifiques
 */
class Contacts {
private:
    std::list<Contact> contacts; /*!< Liste des Contact modélisés par cette classe. */

public:
    // Voir contacts.cpp pour la documentation des méthodes

    void addContact(const Contact& c);
    std::list<Contact> getContacts();
    unsigned int size() const;
    [[nodiscard]] Contact* getContact(int id);
    [[nodiscard]] Contacts searchByName(const std::string& name);
    [[nodiscard]] Contacts searchByCompany(const std::string& company);

    void sortByDate(bool reverse=false);
    void sortByName(bool reverse=false);

    [[nodiscard]] Todos getTodosBetween(Date to, Date from);
    [[nodiscard]] Todos getUrgentTodos();
    [[nodiscard]] Interactions getInteractionsBetween(Date to, Date from);
    [[nodiscard]] Interactions getUrgentInteractions();

    void remove(int id);

    void clear();

    Interactions getInteractionsSortedByDate(bool reverse=false);
    Todos getTodosSortedByDate(bool reverse=false);

    // Iterator
    using iterator = std::list<Contact>::iterator;
    using const_iterator = std::list<Contact>::const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    friend std::ostream& operator<<(std::ostream& os, const Contacts& c);

    // Constructeurs et destructeur
    Contacts();
    explicit Contacts(std::list<Contact> c);
    explicit Contacts(const Contact& c);
    ~Contacts();

    static Contacts fromListOfMaps(std::list<std::unordered_map<std::string, std::string>> data);

};


#endif //CDAA_CONTACTS_H
