/**
 * @file interactions.cpp
 *
 * @brief Définition de la classe Interactions.
 *      Interface adaptée afin de mieux gérer une liste d'interactions
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#include "interactions.h"

/**
 * Ajoute une interaction à la liste modélisée
 * @param i Interaction à ajouter à la liste
 */
void Interactions::addInteraction(const Interaction& i) {
    this->interactions.push_back(i);
}

/**
 * Tri les interactions par date du plus ancien au plus récent (par défaut).
 * @param reverse Par défaut false, si True: les dates seront rangés de la plus récentes à la plus ancienne.
 */
void Interactions::sortByDate(bool reverse) {
    if(reverse)
        this->interactions.sort([](const Interaction &i, const Interaction &i1) {return i.getDate() > i1.getDate();});
    else
        this->interactions.sort([](const Interaction &i, const Interaction &i1) {return i.getDate() < i1.getDate();});
}

/**
 * Vide l'intégralité de la liste modélisée
 */
void Interactions::clear() {
    this->interactions.clear();
}


/**
 * Renvoie une interaction avec son identifiant.
 * @param id Identifiant de l'interaction voulue.
 * @return Interaction (nullptr si non trouvée).
 */
Interaction* Interactions::getInteraction(int id) {
    for(Interaction& i : this->interactions)
        if(i.getId() == id)
            return &i;
    return nullptr;
}

/**
 * Renvoie le nombre d'interactions dans la liste.
 * @return Nombre d'interactions.
 */
unsigned int Interactions::size() const{
    return static_cast<unsigned int>(this->interactions.size());
}

/**
 * Itérateur classique: premier élément.
 * @return Itérateur fixé au début de la liste.
 */
Interactions::iterator Interactions::begin() {
    return this->interactions.begin();
}

/**
 * Itérateur constant: premier élément.
 * @return  Itérateur constant fixé au début de la liste.
 */
Interactions::const_iterator Interactions::begin() const {
    return this->interactions.begin();
}

/**
 * Itérateur classique marquant la fin de la liste.
 * @return Itérateur fixé sur le dernier élément de la liste.
 */
Interactions::iterator Interactions::end() {
    return this->interactions.end();
}

/**
 * Itérateur constant marquant la fin de la liste.
 * @return Itérateur constant fixé sur le dernier élément de la liste.
 */
Interactions::const_iterator Interactions::end() const {
    return this->interactions.end();
}

/**
 * Retire le premier élément trouvé avec l'identifiant passé en paramètre
 * @param id Identifiant de l'interaction à supprimer
 */
void Interactions::remove(int id) {
    for(const auto& i : this->interactions)
        if(i.getId() == id) {
            this->interactions.remove(i);
            return; // Return to prevent access violation
        }
}

/**
 * Retire l'élément i de la liste
 * @param i Interaction a retirer
 */
void Interactions::remove(const Interaction& i) {
    this->interactions.remove(i);
}

/**
 * Renvoie un objet Interactions contant les interactions de cette liste se trouvant entre deux dates
 * @param to Date de début de recherche
 * @param from Date de fin de recherche
 * @return Liste d'interactions se trouvant entre les deux dates
 */
Interactions Interactions::getInteractionsBetween(Date &to, Date &from) {
    Interactions is{};
    for(const auto& i: this->interactions)
        if(i.getDate() >= to && i.getDate() <= from)
            is.addInteraction(i);
    return is;
}

/**
 * Retourne les interactions sans date, et donc importantes
 * @return Interactions sans date.
 */
Interactions Interactions::getUrgentInteractions() {
    Interactions is;
    for(auto& i: this->interactions) {
        if(i.getDate().getTotalSeconds() == -1)
            is.addInteraction(i);
    }
    return is;
}

/**
 * Surcharge de l'opérateur +: ajoute une interaction à la liste
 * @param is Liste d'interactions
 * @param i Interaction à ajouter
 * @return Nouvelle liste avec une interaction i en plus
 */
Interactions operator+(Interactions is, const Interaction &i) {
    is.addInteraction(i);
    return is;
}

/**
 * Ajoute l'interaction i à la liste is
 * @param is Liste d'interactions
 * @param i Interaction à ajouter
 * @return La liste avec la nouvelle interaction
 */
Interactions &operator+=(Interactions &is, const Interaction &i) {
    is.addInteraction(i);
    return is;
}

/**
 * Ajoute une liste d'interactions à la liste actuelle
 * @param is Liste d'Interaction courante
 * @param i Liste à ajouter à is
 * @return Listes concaténées
 */
Interactions &operator+=(Interactions &is, const Interactions &i) {
    for(auto& interaction : i.interactions)
        is.addInteraction(interaction);
    return is;
}

/**
 * Retire une interaction à une liste
 * @param is Liste d'interactions
 * @param i Interaction
 * @return Nouvelle liste avec une interaction en moins (si trouvée)
 */
Interactions operator-(Interactions is, const Interaction &i) {
    is.remove(i);
    return is;
}

/**
 * Retire une interaction à une liste
 * @param is Liste d'interactions
 * @param i Interaction
 * @return La liste is sans l'interaction i
 */
Interactions &operator-=(Interactions &is, const Interaction &i) {
    is.remove(i);
    return is;
}

/**
 * Renvoie une description textuelle de l'objet dans le flux
 * @param os Flux
 * @param is Objet à décrire
 * @return Flux
 */
std::ostream& operator<<(std::ostream& os, const Interactions& is) {
    os << "Interactions (";
    os << is.size();
    os << "):" << std::endl;
    for(auto& i: is)
        os << "    ->" << i << std::endl;
    return os;
}

/**
 * Constructeur par défaut
 */
Interactions::Interactions() {
    this->interactions = std::list<Interaction>();
}

/**
 * Constructeur avec une interaction
 * @param i Interaction utilisée pour initialiser la liste
 */
Interactions::Interactions(const Interaction& i) {
    this->interactions = std::list<Interaction>{i};
}

/**
 * Constructeur avec une liste (std) d'interactions.
 * @param interactions intercations à copier dans la nouvelle structeur
 */
Interactions::Interactions(const std::list<Interaction>& interactions) {
    this->interactions = std::list<Interaction>();
    for(const Interaction& i : interactions)
        this->interactions.push_back(i);
}


/**
 * Destructeur par défaut, géré par le compilateur.
 */
Interactions::~Interactions() = default;

/**
 * Retourne une liste d'interactions générée par une liste de map
 * @param data Liste de map où puiser les données
 * @return Liste d'interactions
 */
Interactions Interactions::fromListOfMaps(std::list<std::unordered_map<std::string, std::string>> data)
{
    Interactions is;

    for(auto const& m : data) {
        Interaction i = Interaction::fromMap(m);
        if(i != Interaction())
            is.addInteraction(i);
    }

    return is;
}
