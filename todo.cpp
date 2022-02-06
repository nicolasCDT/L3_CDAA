/**
 * @file todo.cpp
 *
 * @brief Définition de la classe todo.
 *          Elle permet de définir une tâche à faire plus tard en fonction d'une date (optionnelle)
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#include "todo.h"

/**
 * Définit l'identifiant de la tâche.
 * Si nouvelle tâche : -1
 * @param id
 */
void Todo::setId(int id) {
    this->id = id;
}

/**
 * Renvoie l'identifiant de la tâche.
 * Par défaut, une tâche non enregistré a pour identifiant -1.
 * @return
 */
int Todo::getId() const {
    return this->id;
}

/**
 * Définit l'identifiant du propriétaire de la tâche
 * @param id  Identifiant du propriétaire
 */
void Todo::setOwnerId(int ownerId) {
    this->ownerId = ownerId;
}

/**
 * Définit l'identifiant du propriétaire de la tâche
 * @return Identifiant du propriétaire
 */
int Todo::getOwnerId() const {
    return this->ownerId;
}


/**
 * Définit la description de la tâche.
 * @param description Description de la tâche à réaliser.
 */
void Todo::setDescription(std::string &description) {
    this->description = description;
}

/**
 * Renvoie la description de la tâche.
 * @return Description de la tâche.
 */
std::string &Todo::getDescription() {
    return this->description;
}

/**
 * Définit la date à laquelle la tâche doit être réalisée.
 * S'il n'y a pas de date, spécifié une date au 1er janvier 1970 (0 seconde)
 * @param date Date à laquelle la tâche doit être réalisée.
 */
void Todo::setDate(const Date &date) {
    this->date = date;
}

/**
 * Renvoie la date à laquelle la tâche doit être réalisée.
 * @return Date à laquelle la tâche doit être réalisée.
 */
Date& Todo::getDate() {
    return this->date;
}

/**
 * Renvoie si oui ou non la tâche est urgente
 * @return Urgente ou non
 */
bool Todo::isUrgent()
{
    return getDate().getTotalSeconds() == -1;
}


std::string Todo::getQuery(int mode)
{
    if(mode == DELETE)
        return "DELETE FROM todo WHERE id=" + std::to_string(this->id);

    // Secure to prevent SQL Injections
    Utils::addSlashes(this->description);

    switch(mode)
    {
        case UPDATE:
            return "UPDATE todo SET "
                    "description='" + description + "', "
                    "date='" + date.getSqlFormat()+"' "
                    "WHERE id="+std::to_string(id);
        case CREATE:
            return "INSERT INTO todo "
                   "(owner_id, description, date) "
                   "VALUES "
                   "(" + std::to_string(ownerId) +", '"+ description +"', '"+date.getSqlFormat()+"')";
        default:
            break;
    }

    return "";
}
/**
 * Retourne la représentation de l'objet sour forme de map
 * @return Représentation de l'objet sous forme de map
 */
std::unordered_map<std::string, std::string> Todo::toMap() const
{
    return {
        { "object_type", "todo" }, // Temp -> have to complet jsondialog to accept node
        { "id", std::to_string(id)  },
        { "owner_id", std::to_string(ownerId) },
        { "description", description },
        { "date", date.getSqlFormat()},
    };
}

/**
 * Surcharge de l'opérateur == (testé grâce aux identifiants et à la description)
 * @param a Todo a comparer
 * @param b Todo a comparer
 * @return S'ils sont égaux
 */
bool operator==(const Todo &a, const Todo &b) {
    return (a.getId() == b.getId() && a.description == b.description);
}

/**
 * Surcharge de l'opérateur != (testé grâce aux identifiants et à la description)
 * @param a Todo a comparer
 * @param b Todo a comparer
 * @return S'ils sont différents
 */
bool operator!=(const Todo &a, const Todo &b) {
    return !(a==b);
}

/**
 * Renvoie une description textuelle de l'objet dans le flux
 * @param os Flux
 * @param i Objet a décrire
 * @return Flux
 */
std::ostream &operator<<(std::ostream &os, const Todo &i) {
    os << "Todo<id: " << i.id;
    os << "; ownerId: " << i.ownerId;
    os << "; description: '" << i.description;
    os << "'; date: " << i.date;
    os << ">";
    return os;
}

/**
 * Constructeur par défaut de la classe.
 */
Todo::Todo() {
    this->id = -1;
    this->ownerId = -1;
    this->description = "";
    this->date = Date();
}

/**
 * Constructeur par défaut
 * @param ownerId Identifiant du propriétaire
 * @param description Description de la tâche
 * @param date Date à laquelle la tâche doit être effectuée
 */
Todo::Todo(int ownerId, std::string &description, Date &date) {
    this->id = -1;
    this->ownerId = ownerId;
    this->description = description;
    this->date = date;
}

/**
 * Destructeur par défaut (géré par le compilateur)
 */
Todo::~Todo() = default;

/**
 * Méthode statique pour la création de todo avec les informations modélisées dans une map.
 * @param data Map (non ordonnée pour des soucis d'efficacité)
 * @return Todo créée (Todo par défaut si map invalide)
 */
Todo Todo::fromMap(std::unordered_map<std::string, std::string> data)
{
    Todo t;

    // Prevent for corrupted json
    std::vector<std::string> needed =  {"id", "owner_id", "description", "date"};

    for(const auto& n: needed) {
        if(data.find(n) == data.end()) {
            std::cout << "Erreur d'importation" << std::endl;
            return t; // Default todo
        }
    }

    // Check Date
    if(!Date(data.at("date")).isValid())
    {
        std::cout << "Erreur d'importation" << std::endl;
        return t;
    }

    // complete object
    t.setId(std::stoi(data.at("id")));
    t.setOwnerId(std::stoi(data.at("owner_id")));
    t.setDescription(data.at("description"));
    t.setDate(Date(data.at("date")));

    return t;
}

