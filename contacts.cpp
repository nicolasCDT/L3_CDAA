/**
 * @file contacts.cpp
 *
 * @brief Définition des méthodes de la classe Contacts
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#include "contacts.h"

/**
 * Ajoute un Contact à la liste
 * @param c Contact à ajouter
 */
void Contacts::addContact(const Contact& c) {
    this->contacts.push_back(c);
}

/**
 * Renvoie une liste de Contact
 * @return Liste de Contact
 */
std::list<Contact> Contacts::getContacts() {
    return this->contacts;
}

/**
 * Vide l'intégralité de la liste modélisée
 */
void Contacts::clear() {
    this->contacts.clear();
}

/**
 * Renvoie le nombre de Contact dans la liste
 * @return
 */
unsigned int Contacts::size() const {
    return this->contacts.size();
}

/**
 * Renvoie un pointeur sur un Contact cherché grâce à son identifiant
 * @param id Identifiant du Contact à chercher
 * @return Pointeur sur le Contact (nullptr si non trouvé)
 */
Contact* Contacts::getContact(int id) {
    for(auto& c : this->contacts)
        if(c.getId() == id)
            return &c;
    return nullptr;
}

/**
 * Cherche un Contact grâce à son nom.
 * @param name Nom recherché
 * @return Contacts contenant les Contact recherchés
 */
Contacts Contacts::searchByName(const std::string& name) {
    Contacts cs;
    for(auto& c : this->contacts)
        if(c.getFullName().find(name) != std::string::npos)
            cs.addContact(c);
    return cs;
}

/**
 * Cherche un Contact grâce à son entreprise
 * @param company Entreprise recherchée
 * @return Contacts contenant les Contact recherchés
 */
Contacts Contacts::searchByCompany(const std::string &company) {
    Contacts cs;
    for(auto& c : this->contacts)
        if(c.getCompany().find(company) != std::string::npos)
            cs.addContact(c);
    return cs;
}

/**
 * Tri l'ensemble des Contact s par leur date de création
 * @param reverse Inverser le tri ou non
 */
void Contacts::sortByDate(bool reverse) {
    if(reverse)
        this->contacts.sort([](const Contact &c, const Contact &c1) {return c.getCreationDate() > c1.getCreationDate();});
    else
        this->contacts.sort([](const Contact &c, const Contact &c1) {return c.getCreationDate() < c1.getCreationDate();});
}

/**
 * Tri l'ensemble des Contact s par leur nom
 * @param reverse Inverser le tri ou non
 */
void Contacts::sortByName(bool reverse) {
    if(reverse)
        this->contacts.sort([](const Contact &c, const Contact &c1) {return c.getFullName() > c1.getFullName();});
    else
        this->contacts.sort([](const Contact &c, const Contact &c1) {return c.getFullName() < c1.getFullName();});
}

/**
 * Renvoie l'ensemble de TODO existant entre deux Date s
 * @param to Date de début
 * @param from Date de fin
 * @return Todos avec les TODO recherchés
 */
Todos Contacts::getTodosBetween(Date to, Date from) {
    Todos ts;
    for(auto& c: this->contacts)
        ts += c.getTodosBetween(to, from);
    return ts;
}

/**
 * Renvoie un TODOS avec l'ensemble des TODO les plus urgents (sans Date)
 * @return TODOS avec les TODO urgents
 */
Todos Contacts::getUrgentTodos() {
    Todos ts;
    for(auto& c: this->contacts)
        ts += c.getUrgentTodos();
    return ts;
}

/**
 * Renvoie une Interactions contenant toutes les Interaction s entre deux Date s
 * @param to Date de début
 * @param from Date de fin
 * @return Interactions avec les Interactions recherchées
 */
Interactions Contacts::getInteractionsBetween(Date to, Date from) {
    Interactions is;
    for(auto& c: this->contacts)
        is += c.getInteractionsBetween(to, from);
    return is;
}

/**
 * Renvoie sous forme d'Interactions l'ensemble des Interaction s urgentes (sans Date)
 * @return Interactions avec les Interaction s urgente
 */
Interactions Contacts::getUrgentInteractions() {
    Interactions is;
    for(auto& c: this->contacts)
        is += c.getUrgentInteractions();
    return is;
}

/**
 * Retire un Contact de la liste avec son identifiant
 * @param id Identifiant du Contact a supprimer
 */
void Contacts::remove(int id) {
    for(auto& c: this->contacts)
        if(c.getId() == id) {
            this->contacts.remove(c);
            return; //prevent access memory violation
        }
}

/**
 * Renvoie l'ensemble des Interaction s sous forme d'Interactions classées par Date
 * @param reverse Inverser le tri ?
 * @return Interactions triées par Date
 */
Interactions Contacts::getInteractionsSortedByDate(bool reverse) {
    Interactions is;
    for(auto& c: this->contacts)
        is += c.getInteractions();
    is.sortByDate(reverse);
    return is;
}

/**
 * Renvoie l'ensemble des TODO s sous forme d'un TODOS classés par Date
 * @param reverse Inverser le tri ?
 * @return TODOS triés par Date
 */
Todos Contacts::getTodosSortedByDate(bool reverse) {
    Todos ts;
    for(auto& c: this->contacts)
        ts += c.getTodos();
    ts.sortByDate(reverse);
    return ts;
}

/**
 * Itérateur qui pointe sur le début de la liste
 * @return Itérateur début
 */
Contacts::iterator Contacts::begin() {
    return this->contacts.begin();
}

/**
 * Itérateur constant qui pointe sur le début de la liste
 * @return Itérateur constant début
 */
Contacts::const_iterator Contacts::begin() const {
    return this->contacts.begin();
}

/**
 * Itérateur qui pointe sur la fin de la liste
 * @return Itérateur fin
 */
Contacts::iterator Contacts::end() {
    return this->contacts.end();
}

/**
 * Itérateur constant qui pointe sur la fin de la liste
 * @return Itérateur constant fin
 */
Contacts::const_iterator Contacts::end() const {
    return this->contacts.end();
}

/**
 * Surcharge de l'opérateur << qui renvoie une description textuelle de l'objet dans le flux
 * @param os Flux
 * @param c Objet à décrire
 * @return Flux
 */
std::ostream& operator<<(std::ostream& os, const Contacts &c) {
    os << "Contacts (" << c.size() << "): " << std::endl;
    for(auto& contact : c)
        os << "    ->" << contact << std::endl;
    return os;
}

/**
 * Constructeur sans paramètre: initialise juste la liste de Contact s
 */
Contacts::Contacts() {
    this->contacts = std::list<Contact>();
}

/**
 * Constructeur avec une liste de Contact à ajouter dans l'objet
 * @param c Liste de Contact s
 */
Contacts::Contacts(std::list <Contact> c) {
    this->contacts = std::move(c);
}

/**
 * Constructeur avec un Contact à ajouter
 * @param c Contact à ajouter à l'objet
 */
Contacts::Contacts(const Contact& c) {
    this->contacts = std::list<Contact>();
    this->contacts.push_back(c);
}

/**
 * Destructeur par défaut géré par le compilateur
 */
Contacts::~Contacts() = default;

/**
 * Retourne une liste de contact générée par une liste de map
 * @param data Liste de map où puiser les données
 * @return Liste de contact
 */
Contacts Contacts::fromListOfMaps(std::list<std::unordered_map<std::string, std::string>> data)
{
    Contacts cs;

    for(auto const& m : data) {
        Contact c = Contact::fromMap(m);
        if(c != Contact())
            cs.addContact(c);
    }

    return cs;
}
