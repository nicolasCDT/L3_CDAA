/**
 * @file interaction.cpp
 *
 * @brief Définition de la classe Interaction
 *      Cette classe gère les commentaires et les rendez-vous. On peut facilement ajouter des types d'interactions
 *      en complétant la structure types.
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#include "interaction.h"

/**
 * Renvoie l'identifiant de l'interaction.
 * S'il n'est pas connu, il est de -1 par défaut.
 * @return Identifiant de l'interaction
 */
int Interaction::getId() const {
    return this->id;
}

/**
 * Définit l'identifiant de l'interaction.
 * @param id Identifiant à attribuer
 */
void Interaction::setId(int id) {
    this->id = id;
}

/**
 * Renvoie l'identifiant du propriétaire de l'interaction.
 * S'il n'est pas connu, il est de -1 par défaut.
 * @return Identifiant du propriétaire
 */
int Interaction::getOwnerId() const {
    return this->ownerId;
}

/**
 * Définit l'identifiant du propriétaire de l'interaction.
 * @param ownerId Identifiant du propriétaire
 */
void Interaction::setOwnerId(int ownerId) {
    this->ownerId = ownerId;
}

/**
 * Renvoie le type de l'interaction (voir énumération types)
 * @return Type de l'interaction
 */
unsigned int Interaction::getType() const {
    return this->type;
}

/**
 * Définit le type de l'interaction
 * @param type Type de l'interaction (voir énumération types)
 */
void Interaction::setType(unsigned int type) {
    if(type < MAX_NUM)
        this->type = type;
}

/**
 * Renvoie la date à laquelle l'interaction s'est déroulé
 * @return Date de l'interaction
 */
Date Interaction::getDate() const {
    return this->date;
}

/**
 * Définit la date de l'interaction
 * @param date Date à attribuer
 */
void Interaction::setDate(Date date) {
    this->date = date;
}

/**
 * Renvoie la description de l'interaction
 * @return Description textuelle de l'interaction
 */
const std::string &Interaction::getDescription() const {
    return this->description;
}

/**
 * Définit la description de l'interaction
 * @param description Description textuelle de l'interaction
 */
void Interaction::setDescription(std::string &description) {
    this->description = description;
}

std::string Interaction::getQuery(int mode) {

    if(mode == DELETE)
        return "DELETE FROM interaction WHERE id=" + std::to_string(this->id);

    Utils::addSlashes(description);

    switch(mode)
    {
        case UPDATE:
            return "UPDATE interaction SET "
                    "type="+std::to_string(type)+", "
                    "description='"+description+"', "
                    "date='" + date.getSqlFormat()+"' "
                    "WHERE id="+std::to_string(id);
        case CREATE:
        return "INSERT INTO interaction "
               "(owner_id, type, description, date) "
               "VALUES (" +
               std::to_string(ownerId) + ", " +
               std::to_string(type) + ", "
               "'"+ description + "', "
               "'" + date.getSqlFormat() + "'"
                ")";
        default:
            break;
    }

    return "";
}

/**
 * Retourne la représentation de l'objet sour forme de map
 * @return Représentation de l'objet sous forme de map
 */
std::unordered_map<std::string, std::string> Interaction::toMap() const
{
    return {
        { "object_type", "interaction" }, // Temp -> have to complet jsondialog to accept node
        { "id", std::to_string(id)  },
        { "owner_id", std::to_string(ownerId) },
        { "type", std::to_string(type) },
        { "description", description },
        { "date", date.getSqlFormat()},
    };
}

/**
 * Surcharge de l'opérateur << afin de fournir une description textuelle de l'interaction dans un flux.
 * @param os Flux
 * @param i Interaction elle-même
 * @return Le flux entrant
 */
std::ostream &operator<<(std::ostream &os, const Interaction &i) {
    os << "Interaction<id: " << i.id;
    os << "; ownerId: " << i.ownerId;
    os << "; type: " << i.type;
    os << "; description: '" << i.description;
    os << "'; date: " << i.date;
    os << ">";
    return os;
}

/**
 * Surcharge de l'opérateur == afin de vérifier l'égalité des interactions
 * @param a Interaction 1
 * @param b Interaction 2
 * @return Sir les deux interactions sont les mêmes (comparées avec identifiant et description)
 */
bool operator==(const Interaction &a, const Interaction &b) {
    return (a.getId() == b.getId() && a.description == b.description);
}

/**
 * Surcharge de l'opérateur != afin de vérifier l'inégalité des interactions.
 * @param a Interaction 1
 * @param b Interaction 2
 * @return Sir les deux interactions sont différentes (comparées avec identifiant et description)
 */
bool operator!=(const Interaction &a, const Interaction &b) {
    return !(a == b);
}

/**
 * Constructeur par défaut de la classe.
 * La date par défaut est la date courante de l'ordinateur.
 * L'identifiant de l'interaction et du propriétaire sont automatiquement définis à -1, le type sur NONE.
 * La description est un string vide.
 */
Interaction::Interaction() {
    this->id = -1;
    this->ownerId = -1;
    this->date = Date();
    this->type = NONE;
    this->description = "";
}

/**
 * Constructeur de la classe avec paramètres.
 * L'identifiant de l'interaction est défini à -1 en attendant que la base de données lui en attribut un.
 * @param ownerId Identifiant du propriétaire
 * @param type Type de l'interaction
 * @param description Description textuelle de l'interaction
 * @param date Date de l'interaction
 */
Interaction::Interaction(int ownerId, unsigned int type, std::string& description, Date& date) {
    this->ownerId = ownerId;
    this->type = type;
    this->id = -1;
    this->description = description;
    this->date = date;
}

/**
 * Destructeur par défaut géré par le compilateur.
 */
Interaction::~Interaction() = default;

/**
 * Méthode statique pour la création d'interactions avec les informations modélisées dans une map.
 * @param data Map (non ordonnée pour des soucis d'efficacité)
 * @return Interaction créée (Interaction par défaut si map invalide)
 */
Interaction Interaction::fromMap(std::unordered_map<std::string, std::string> data)
{
    Interaction i;

    // Prevent for corrupted json
    std::vector<std::string> needed =  {"id", "owner_id", "type", "description", "date"};

    for(const auto& n: needed) {
        if(data.find(n) == data.end()) {
            std::cout << "Erreur d'importation" << std::endl;
            return i; // Default interaction
        }
    }

    // Check Date
    if(!Date(data.at("date")).isValid())
    {
        std::cout << "Erreur d'importation" << std::endl;
        return i;
    }

    // complete object
    i.setId(std::stoi(data.at("id")));
    i.setOwnerId(std::stoi(data.at("owner_id")));
    i.setDescription(data.at("description"));
    i.setDate(Date(data.at("date")));
    i.setType(std::stoi(data.at("type")));

    return i;
}
