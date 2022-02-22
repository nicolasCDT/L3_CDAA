/**
 * @file dbinterface.h
 *
 * @brief Déclaration de la classe DBInterface
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include "contacts.h"
#include "utils.h"
#include "todo.h"
#include "interaction.h"
#include <QDebug>
#include <QtSql>
#include <QMessageBox>

/**
 * L'interface permet de gérer plus facilement et plus efficacement la base de données.
 * Elle permet de charger les données, et de les stockers. Le données modifiées sont actualisées dans la base de données
 * quand la méthode flush est appelée. Cela limite un maximum les appels inutiles vers la base de données.
 * @brief Interface de base de données.
 */
class DBInterface
{
private:
    QSqlDatabase db; /*!< Connexion à la base de données SQLite. */
    Contacts contacts; /*!< Listes des contacts en base de données */
    Todos todos; /*!< Listes des todos en base de données */
    Interactions interactions; /*!< Listes des interactions en base de données */

    std::list<DB_todo> dbTodos; /*!< Listes des tâches a effectuer en cas de flush() */
    // Contains only update and delete, created value is insert immediatly to get id

    void clearCache();

    void loadContactInteractions(Contact& c);
    void loadContactTodos(Contact& c);
    void loadOtherInteractions();

    void criticalError(QStringList errors);
    void criticalError(QString error);


public:
    bool open();
    [[nodiscard]] bool isOpen();

    bool loadData();

    [[nodiscard]] Contacts getContacts();
    [[nodiscard]] Todos getTodos();
    [[nodiscard]] Interactions getInteractions();

    void update(Contact& c);
    void update(Interaction& i);
    void update(Todo& t);

    int add(Contact& c);
    int add(Interaction& i);
    int add(Todo& t);

    void remove(Contact& c);
    void remove(Interaction& i);
    void remove(Todo& t);

    void flush();

    // Constructor & destructor
    DBInterface(std::string path);
    DBInterface();
    ~DBInterface();
};

#endif // DBINTERFACE_H
