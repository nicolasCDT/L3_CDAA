/**
 * @file contact.cpp
 *
 * @brief Définition des méthodes de la classe Contact
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#include "contact.h"
#include <utility>

/**
 * Retourne l'identifiant de du Contact
 * @return Identifiant du contact
 */
int Contact::getId() const
{
    return id;
}

/**
 * Définit l'identifiant du Contact
 * @param id Identifiant à définir au Contact
 */
void Contact::setId(int id)
{
    this->id = id;
}

/**
 * Renvoie le nom de famille du Contact
 * @return N de famille du Contact
 */
const std::string& Contact::getLastName() const
{
    return lastName;
}

/**
 * Définit le nom de famille du Contact.
 * @param lastName Nom de famille du contact
 */
void Contact::setLastName(const std::string & lastName)
{
    this->lastName = lastName;
    this->lastName[0] = toupper(this->lastName[0]);
}

/**
 * Renvoie le prénom du Contact
 * @return Prénom du Contact
 */
const std::string & Contact::getFirstName() const
{
    return firstName;
}

/**
 * Définit le prénom du Contact
 * @param firstName Prénom du Contact
 */
void Contact::setFirstName(const std::string & firstName)
{
    this->firstName = firstName;
    this->firstName[0] = toupper(this->firstName[0]);
}

/**
 * Renvoie le nom de l'entreprise du Contact
 * @return Nom de l'entreprise du Contact
 */
const std::string & Contact::getCompany() const
{
    return company;
}

/**
 * Définit l'entreprise du Contact
 * @param company Entreprise du Contact
 */
void Contact::setCompany(const std::string & company)
{
    this->company = company;
    this->company[0] = toupper(this->company[0]);
}

/**
 * Renvoie l'email du Contact
 * @return  Email du Contact
 */
const std::string & Contact::getEmail() const
{
    return email;
}

/**
 * Définit l'email du Contact
 * @param email email du Contact
 */
void Contact::setEmail(const std::string & email)
{
    this->email = email;
}

/**
 * Renvoie le téléphone du Contact
 * @return Téléphone du Contact
 */
const std::string & Contact::getPhone() const
{
    return phone;
}

/**
 * Définit le téléphone du Contact
 * @param phone Téléphone du Contact
 */
void Contact::setPhone(const std::string & phone)
{
    this->phone = phone;
}

/**
 * Renvoie le nom complet du Contact
 * @return [Nom] [Prénom]
 */
std::string Contact::getFullName() const
{
    return lastName + " " + firstName;
}

/**
 * Renvoie la note actuelle du Contact
 * @return Note du Contact
 */
const std::string& Contact::getNote() const
{
    return note;
}

/**
 * Définit la note du contact
 * @param note du contact
 */
void Contact::setNote(const std::string& note)
{
    this->note = note;
}

/**
 * Renvoie les interactions du Contact
 * @return Interactions du Contact
 */
const Interactions &Contact::getInteractions() const {
    return this->interactions;
}

/**
 * Renvoie une interaction du Contact gâce à son id
 * @param id Identifiant de l'Interaction cherché
 * @return Interaction voulue
 */
Interaction* Contact::getInteraction(int id) {
    return this->interactions.getInteraction(id);
}

/**
 * Ajoute une Interaction au Contact
 * @param interaction Interaction à attribuer au contact
 */
void Contact::addInteraction(Interaction &interaction) {
    interaction.setOwnerId(this->id);
    this->interactions.addInteraction(interaction);
}

/**
 * Tri les interactions du Contact par ordre chronologique
 * @param reverse Inverser l'ordre ?
 */
void Contact::sortInteractions(bool reverse) {
    this->interactions.sortByDate(reverse);
}

/**
 * Renvoie la date de création du Contact
 * @return Date de création
 */
const Date &Contact::getCreationDate() const {
    return this->creationDate;
}

/**
 * Définit la date de création du Contact
 * @param date Date de création
 */
void Contact::setCreationDate(const Date &date) {
    this->creationDate = date;
}

/**
 * Renvoie la liste des Todo du Contact sous forme de Todos
 * @return Todos de Todo du Contact
 */
const Todos &Contact::getTodos() const {
    return this->todos;
}

/**
 * Renvoie un Todo reconnu par son identifiant
 * @param id Identifiant du Todo voulu
 * @return Todo recherché
 */
Todo *Contact::getTodo(int id) {
    return this->todos.getTodo(id);
}

/**
 * Ajoute un Todo à la liste Todos du Contact
 * @param todo Todo à ajouter
 */
void Contact::addTodo(Todo &todo) {
    this->todos.addTodo(todo);
}

/**
 * Tri les tâches du Contact par ordre chronologique
 * @param reverse Inverser l'ordre ?
 */
void Contact::sortTodos(bool reverse) {
    this->todos.sortByDate(reverse);
}

/**
 * Renvoie les Interaction situées entre deux dates sous forme d'Interactions
 * @param to Date de début de recherche
 * @param from Date de fin de recherche
 * @return Interactions avec les interactions concernées
 */
Interactions Contact::getInteractionsBetween(Date &to, Date &from) {
    return this->interactions.getInteractionsBetween(to, from);
}

/**
 * Renvoie les Interaction s sans date, donc urgentes
 * @return Interaction s sans date.
 */
Interactions Contact::getUrgentInteractions() {
    return this->interactions.getUrgentInteractions();
}

/**
 * Définit une nouvelle liste d'interactions
 * @param is Nouvelle liste d'interactions
 */
void Contact::setInteractions(Interactions is)
{
    interactions = is;
}

/**
 * Vide la liste des interactions actuelle
 */
void Contact::clearInteractions()
{
    interactions.clear();
}

/**
 * Renvoie les todo situées entre deux dates sous forme de Todos
 * @param to Date de début de recherche
 * @param from Date de fin de recherche
 * @return Todos avec les Todo concernés
 */
Todos Contact::getTodosBetween(Date &to, Date &from) {
    return this->todos.getTodosBetween(to, from);
}

/**
 * Renvoie les tâches sans date, donc urgentes.
 * @return Tâche (Todo) sans date.
 */
Todos Contact::getUrgentTodos() {
    return this->todos.getUrgentTodos();
}

/**
 * Définit une nouvelle liste de tâches
 * @param ts Nouvelle liste de tâches
 */
void Contact::setTodos(Todos ts)
{
    todos = ts;
}

/**
 * Vide la liste des tâches actuelle
 */
void Contact::clearTodos()
{
    todos.clear();
}

/**
 * Renvoie la query qui concerne l'objet en fonction du mode.
 *  -> voir dbinterface.cpp pour le mode
 * @param mode Mode (CREATE, UPDATE, DELETE)
 * @return Query
 */
std::string Contact::getQuery(int mode)
{
    if(mode == DELETE)
        return "DELETE FROM contact WHERE id=" + std::to_string(this->id);

    // Secure to prevent SQL Injections
    Utils::addSlashes(this->firstName);
    Utils::addSlashes(this->lastName);
    Utils::addSlashes(this->company);
    Utils::addSlashes(this->phone);
    Utils::addSlashes(this->email);
    Utils::addSlashes(this->note);

    switch(mode)
    {
        case UPDATE:
            return "UPDATE contact SET "
                   "first_name='"+firstName+"', "
                   "last_name='"+lastName+"', "
                   "company='"+company+"', "
                   "email='"+email+"', "
                   "phone='"+phone+"', "
                   "creation_date='"+creationDate.getSqlFormat()+"', "
                   "note='"+note+"' "
                   "WHERE id="+std::to_string(id);
        case CREATE:
            return "INSERT INTO contact "
                   "(first_name, last_name, company, email, phone, creation_date, note) "
                   "VALUES "
                   "('"+firstName+"', '"+lastName+"', '"+company+"', '"+
                    email+"', '"+phone+"', '"+creationDate.getSqlFormat()+"', '" + note +"')";
        default:
            break;
    }

    return "";
}

/**
 * Retourne la représentation de l'objet sour forme de map
 * @return Représentation de l'objet sous forme de map
 */
std::unordered_map<std::string, std::string> Contact::toMap() const
{
    return {
        { "object_type", "contact" }, // Temp -> have to complet jsondialog to accept node
        { "id", std::to_string(id)  },
        { "first_name", firstName },
        { "last_name", lastName },
        { "company", company },
        { "phone", phone },
        { "email", email },
        { "creation_date", creationDate.getSqlFormat() },
        { "note", note },
    };
}

/**
 * Surcharge de l'opérateur == afin de vérifier l'égalité de deux contacts. (fixée sur l'identifiant et le nom)
 * @param a Premier Contact
 * @param b Deuxième Contact
 * @return S'ils sont égaux
 */
bool operator==(const Contact &a, const Contact &b) {
    return a.id == b.id && a.getFullName() == b.getFullName();
}

/**
 * Surcharge de l'opérateur != afin de vérifier l'inégalité de deux contacts. (fixée sur l'identifiant et le nom)
 * @param a Premier Contact
 * @param b Deuxième Contact
 * @return S'ils sont différents
 */
bool operator!=(const Contact &a, const Contact &b) {
    return !(a==b);
}

/**
 * Ajoute d'une liste de Todos au Contact a.
 * @param a Contact
 * @param b Liste de Todos
 * @return Contact modifié.
 */
Contact& operator+=(Contact &a, Todos &b) {
    for(auto& t: b)
    {
        t.setOwnerId(a.getId());
        a.addTodo(t);
    }
    return a;
}

/**
 * Ajoute d'une liste d'Interactions au Contact a.
 * @param a Contact
 * @param b Liste d'Interactions
 * @return Contact modifié.
 */
Contact& operator+=(Contact &a, Interactions &b) {
    for(auto& i: b)
    {
        i.setOwnerId(a.getId());
        a.addInteraction(i);
    }
    return a;
}

/**
 * Renvoie une description textuelle de l'objet dans le flux
 * @param os Flux
 * @param c Objet à décrire
 * @return Flux
 */
std::ostream &operator<<(std::ostream &os, const Contact &c) {
    os << "Contact<";
    os << c.getFullName();
    os << ", ";
    os << c.getCompany();
    os << ", ";
    os << c.getCreationDate();
    os << ", Interactions("<< c.getInteractions().size() << ")";
    os << ", Todos(" << c.getTodos().size() << ")";
    os << ">";
    return os;
}

/**
 * Constructeur par défaut.
 */
Contact::Contact() {
    this->id = -1;
}

/**
 * Constructeur avec le nom et le prénom de la personne
 * @param firstName Prénom du Contact
 * @param lastName Nom du Contact
 */
Contact::Contact(std::string firstName, std::string lastName) {
    this->id = -1;
    this->firstName = std::move(firstName);
    this->lastName = std::move(lastName);
}

Contact::~Contact() = default;

/**
 * Méthode statique pour la création de contact avec les informations modélisées dans une map.
 * @param data Map (non ordonnée pour des soucis d'efficacité)
 * @return Contact crée (contact par défaut si map invalide)
 */
Contact Contact::fromMap(std::unordered_map<std::string, std::string> data)
{
    Contact c;

    // Prevent for corrupted json
    std::vector<std::string> needed =  {"id", "first_name", "last_name", "company", "phone", "email",
                                        "creation_date", "note"};

    for(const auto& n: needed) {
        if(data.find(n) == data.end()) {
           std::cout << "Erreur d'importation" << std::endl;
            return c; // Default contact
        }
    }

    // Check Date
    if(!Date(data.at("creation_date")).isValid())
    {
        std::cout << "Erreur d'importation" << std::endl;
        return c;
    }

    // Complete contact
    c.setId(std::stoi(data.at("id")));
    c.setFirstName(data.at("first_name"));
    c.setLastName(data.at("last_name"));
    c.setCompany(data.at("company"));
    c.setPhone(data.at("phone"));
    c.setEmail(data.at("email"));
    c.setCreationDate(Date(data.at("creation_date")));
    c.setNote(data.at("note"));

    return c;
}
