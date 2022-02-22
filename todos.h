/**
 * @file todos.h
 *
 * @brief Déclaration de la classe todos. Liste plus adaptée à gérer les tâches de type todo
 *
 * @version 1.0
 *
 * @date 16/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef CDAA_TODOS_H
#define CDAA_TODOS_H

#include <list> // std::list
#include "todo.h"
#include <utility> // std::move
#include <cstdarg> // va
#include <regex> // check date
#include <sstream> // istringstream

/**
 * Classe permettant de modéliser une liste de tâches (Todo) plus adaptée à notre application.
 * @brief Classe permettant de modéliser une liste de Todo
 */
class Todos {
private:
    std::list<Todo> todos; /*!< Listes des tâches (Todo) à modéliser */

public:
    // Voir todos.cpp pour la documentation des méthodes
    void addTodo(const Todo& i);

    void sortByDate(bool reverse=false);
    void remove(int id);
    void remove(const Todo& t);

    void clear();

    [[nodiscard]] unsigned int size() const;

    [[nodiscard]] Todo* getTodo(int id);
    [[nodiscard]] Todos getTodosBetween(Date& to, Date& from);
    [[nodiscard]] Todos getUrgentTodos();

    // Iteration
    using iterator = std::list<Todo>::iterator;
    using const_iterator = std::list<Todo>::const_iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    // Surcharges d'opérateurs
    friend Todos operator+(Todos ts, const Todo& t);
    friend Todos& operator+=(Todos& ts, const Todo& t);
    friend Todos& operator+=(Todos& ts, const Todos& t);
    friend Todos operator-(Todos ts, const Todo& t);
    friend Todos& operator-=(Todos& ts, const Todo& t);
    friend std::ostream& operator<<(std::ostream& os, const Todos& ts);

    Todos();
    explicit Todos(std::list<Todo> todos);
    explicit Todos(const Todo& todo);
    ~Todos();

    [[nodiscard]] static Todos extractFromString(std::string str);

    static Todos fromListOfMaps(std::list<std::unordered_map<std::string, std::string>> data);
};


#endif //CDAA_TODOS_H
