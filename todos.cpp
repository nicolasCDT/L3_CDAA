/**
 * @file todos.cpp
 *
 * @brief Définition de la classe todos. Liste plus adaptée à gérer les tâches de type todo
 *
 * @version 1.0
 *
 * @date 16/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#include "todos.h"

/**
 * Itérateur qui pointe sur le début de la liste
 * @return Itérateur (début)
 */
Todos::iterator Todos::begin() {
    return this->todos.begin();
}

/**
 * Itérateur constant qui pointe sur le début de la liste
 * @return Itérateur constant (début)
 */
Todos::const_iterator Todos::begin() const {
    return this->todos.begin();
}

/**
 * Itérateur qui ponte sur la fin de la liste
 * @return Itérateur (fin)
 */
Todos::iterator Todos::end() {
    return this->todos.end();
}

/**
 * Itérateur constant qui pointe sur la fin de la liste
 * @return Itérateur (fin)
 */
Todos::const_iterator Todos::end() const {
    return this->todos.end();
}

/**
 * Vide l'intégralité de la liste modélisée
 */
void Todos::clear() {
    this->todos.clear();
}


/**
 * Ajoute une tâche à la liste
 * @param t Tâche à ajouter
 */
void Todos::addTodo(const Todo &t) {
    this->todos.push_back(t);
}

/**
 * Tri les tâches par ordre chronologique
 * @param reverse Ordre inversé ? (false par défaut)
 */
void Todos::sortByDate(bool reverse) {
    if(reverse)
        this->todos.sort([](Todo t, Todo &t1) {return t.getDate() > t1.getDate();});
    else
        this->todos.sort([](Todo &t,  Todo &t1) {return t.getDate() < t1.getDate();});

}

/**
 * Retire la première tâche trouvée avec l'identifiant précisé
 * @param id Identifiant de la tâche
 */
void Todos::remove(int id) {
    for(const auto& t : this->todos)
        if(t.getId() == id) {
            this->todos.remove(t);
            return; // Return to prevent access violation
        }
}

/**
 * Retire une tâche de la liste
 * @param t Tâche à retirer (Todo)
 */
void Todos::remove(const Todo& t) {
    this->todos.remove(t);
}

/**
 * Renvoie la taille de la liste
 * @return Nombre d'éléments dans la liste
 */
unsigned int Todos::size() const{
    return this->todos.size();
}

/**
 * Renvoie un pointeur sur la première tâche trouvé avec l'identifiant id
 * @param id Identifiant de la tâche à chercher
 * @return Tâche avec l'identifiant id
 */
Todo* Todos::getTodo(int id) {
    for(auto& t : this->todos)
        if(t.getId() == id)
            return &t;
    return nullptr;
}

/**
 * Renvoie une liste todos de todo avec les tâches comprises entre les deux dates
 * @param to Date de début de recherche
 * @param from Date de fin de recherche
 * @return Liste
 */
Todos Todos::getTodosBetween(Date &to, Date &from) {
    Todos ts{};
    for(auto& t: this->todos)
        if(t.getDate() >= to && t.getDate() <= from)
            ts.addTodo(t);
    return ts;
}

/**
 * Retourne les tâches sans date, et donc importantes
 * @return Tâches sans date.
 */
Todos Todos::getUrgentTodos() {
    Todos ts;
    for(auto& t: this->todos) {
        if(t.getDate().getTotalSeconds() == -1)
            ts.addTodo(t);
    }
    return ts;
}

/**
 * Surcharge de l'opérateur +. Ajoute une Todo à la liste
 * @param ts Liste de Todo
 * @param t Todo à ajouter à la liste
 * @return Nouvelle liste avec le Todo en plus
 */
Todos operator+(Todos ts, const Todo &t) {
    ts.addTodo(t);
    return ts;
}

/**
 * Surcharge de l'opérateur +=. Ajoute une Todo à la liste
 * @param ts Liste de Todo
 * @param t Todo à ajouter à la liste
 * @return Liste ts avec le Todo en plus
 */
Todos &operator+=(Todos &ts, const Todo &t) {
    ts.addTodo(t);
    return ts;
}

/**
 * Surcharge de l'opérateur +=. Ajoute un Todos à la liste
 * @param ts Liste de Todo
 * @param t Todos à ajouter à la liste
 * @return Liste ts avec les Todos en plus
 */
Todos &operator+=(Todos &ts, const Todos &t) {
    for(auto& todo : t.todos)
        ts.addTodo(todo);
    return ts;
}

/**
 * Surcharge de l'opérateur -. Retire une Todo à la liste
 * @param ts Liste de Todo
 * @param t Todo à retirer à la liste
 * @return Nouvelle liste sans le Todo t
 */
Todos operator-(Todos ts, const Todo &t) {
    ts.remove(t);
    return ts;
}

/**
 * Surcharge de l'opérateur -=. Retire une Todo à la liste
 * @param ts Liste de Todo
 * @param t Todo à retirer à la liste
 * @return Liste sans le Todo t
 */
Todos &operator-=(Todos &ts, const Todo &t) {
    ts.remove(t);
    return ts;
}

/**
 * Renvoie une description textuelle de l'objet dans le flux
 * @param os Flux
 * @param i Objet a décrire
 * @return Flux
 */
std::ostream& operator<<(std::ostream& os, const Todos& ts) {
    os << "Todos (";
    os << ts.size();
    os << "):" << std::endl;
    for(auto& t: ts)
        os << "    ->" << t << std::endl;
    return os;
}

/**
 * Constructeur de la classe (initialise une liste vide)
 */
Todos::Todos() {
    this->todos = std::list<Todo>();
}

/**
 * Constructeur de la classe avec une liste de tâche (copie la liste dans la nouvelle structure)
 * @param todos Liste de tâche
 */
Todos::Todos(std::list<Todo> todos) {
    this->todos = std::move(todos);
}

/**
 * Constructeur avec une tâche
 * @param todo Tache avec laquelle initialiser la liste
 */
Todos::Todos(const Todo& todo) {
    this->todos = std::list<Todo>();
    this->todos.push_back(todo);
}

/**
 * Destructeur par défaut (gérer par le compilateur)
 */
Todos::~Todos() = default;

/**
 * Extrait les Todos venant d'un string
 * @param str Texte où extraire les tâches Todo
 * @return Todos content les Todo
 */
Todos Todos::extractFromString(std::string str) {
    Todos ts;
    std::istringstream f(str);
    std::string line;
    while(std::getline(f, line)) { // For each lien
        if(line.rfind("@todo", 0) == 0) { // If todo in
            Todo t;
            std::string description;
            std::size_t index = line.find("@date");
            if(index != std::string::npos && line.size() >= index+16) // check length
            {
                std::string temp_date = line.substr(index+6, 10);
                std::smatch match;
                std::regex regex{R"(\d\d/\d\d/\d\d\d\d)"};
                if(std::regex_search(temp_date, match, regex)) { // Check for format
                    Date d(temp_date, true);
                    description = line.substr(5, index-6);
                    t.setDate(d);
                }
                else // invalid -> create with 0 sec
                {
                    std::string date = "01/01/1970";
                    Date d(date, true);
                    t.setDate(d);
                    description = line.substr(5);
                }
            }
            else // no date -> create with 0 sec
            {
                std::string date = "01/01/1970";
                Date d(date, true);
                t.setDate(d);
                description = line.substr(5);
            }
            t.setDescription(description);
            ts.addTodo(t);
        }
    }
    return ts;
}

/**
 * Retourne une liste d'interactions générée par une liste de map
 * @param data Liste de map où puiser les données
 * @return Liste d'interactions
 */
Todos Todos::fromListOfMaps(std::list<std::unordered_map<std::string, std::string>> data)
{
    Todos ts;

    for(auto const& m : data) {
        Todo t = Todo::fromMap(m);
        if(t != Todo())
            ts.addTodo(t);
    }

    return ts;
}

