/**
 * @file dbinterface.cpp
 *
 * @brief Définition des méthodes de la classe DBInterface
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */
#include "dbinterface.h"

/**
 * Ouvre la connexion vers la base de données SQLite
 * @return Renvoie vrai si la base de données est accessible et disponible.
 */
bool DBInterface::open()
{
    if(!db.open())
        criticalError("Ouverture de la base de données impossible");
    return isOpen();
}

/**
 * Si la connexion est ouverte.
 * @return Connexion ouverte et disponible ?
 */
bool DBInterface::isOpen()
{
    return this->db.isOpen();
}

/**
 * Renvoie les contacts contenus dans le cache
 * @return Contacts en cache
 */
Contacts DBInterface::getContacts()
{
    return this->contacts;
}

/**
 * Renvoie les todos contenus dans le cache
 * @return Todos en cache
 */
Todos DBInterface::getTodos()
{
    return this->todos;
}

/**
 * Renvoie les interactions contenus dans le cache
 * @return Interactions en cache
 */
Interactions DBInterface::getInteractions()
{
    return this->interactions;
}

/**
 * Vide le cache de données de l'interface
 */
void DBInterface::clearCache()
{
    contacts.clear();
    todos.clear();
    interactions.clear();
    dbTodos.clear();
}

/**
 * Charge l'ensemble des données contenues dans la base.
 * @return Si la lecture s'est bien effectuée
 */
bool DBInterface::loadData()
{

    clearCache();

    QSqlQuery query;
    if(!query.exec("SELECT * FROM contact"))
    {
        criticalError("Impossible de charger les tables de la base de données.");
        return false;
    }

    while(query.next())
    {
        Contact c;
        c.setId(query.value(0).toInt());
        c.setFirstName(query.value(1).toString().toStdString());
        c.setLastName(query.value(2).toString().toStdString());
        c.setCompany(query.value(3).toString().toStdString());
        c.setEmail(query.value(4).toString().toStdString());
        c.setPhone(query.value(5).toString().toStdString());
        c.setNote(query.value(7).toString().toStdString());

        std::string sqlDate = query.value(6).toString().toStdString();
        c.setCreationDate(Date(sqlDate));

        contacts.addContact(c);
    }

    for(auto& c: contacts)
    {
        loadContactInteractions(c);
        loadContactTodos(c);
    }

    loadOtherInteractions();

    return true;
}

/**
 * Lecture des interactions qui ne sont pas reliées à un contact
 */
void DBInterface::loadOtherInteractions()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM interaction WHERE owner_id=-1"); // Using ODBC style
    if(query.exec())
    {
        while(query.next())
        {
            Interaction i;
            i.setId(query.value(0).toInt());
            i.setOwnerId(query.value(1).toInt());
            i.setType(query.value(2).toInt());
            std::string desc = query.value(3).toString().toStdString();
            i.setDescription(desc);
            std::string sqlDate = query.value(4).toString().toStdString();
            Date d(sqlDate);
            i.setDate(d);
            interactions.addInteraction(i);
        }
    }
    else
    {
        qDebug() << query.lastError();
    }
}

/**
 * Lecture des interactions d'un contact dans la base de données
 * @param c Contact
 */
void DBInterface::loadContactInteractions(Contact& c)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM interaction WHERE owner_id=?"); // Using ODBC style
    query.bindValue(0, c.getId());
    if(query.exec())
    {
        while(query.next())
        {
            Interaction i;
            i.setId(query.value(0).toInt());
            i.setOwnerId(query.value(1).toInt());
            i.setType(query.value(2).toInt());
            std::string desc = query.value(3).toString().toStdString();
            i.setDescription(desc);
            std::string sqlDate = query.value(4).toString().toStdString();
            Date d(sqlDate);
            i.setDate(d);
            c.addInteraction(i);
            interactions.addInteraction(i);
        }
    }
    else
    {
        qDebug() << query.lastError();
    }
}

/**
 * Lecture des todos d'un contact dans la base de données
 * @param c Contact
 */
void DBInterface::loadContactTodos(Contact &c)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM todo WHERE owner_id=?"); // Using ODBC style
    query.bindValue(0, c.getId());
    if(query.exec())
    {
        while(query.next())
        {
            Todo t;
            t.setId(query.value(0).toInt());
            t.setOwnerId(query.value(1).toInt());
            std::string desc = query.value(2).toString().toStdString();
            t.setDescription(desc);
            std::string sqlDate = query.value(3).toString().toStdString();
            Date d(sqlDate);
            t.setDate(d);
            c.addTodo(t);
            todos.addTodo(t);
        }
    }
    else
    {
        qDebug() << query.lastError();
    }
}

/**
 * Ajoute un contact au cache et à la base de données
 * @param c Contact à ajouter
 * @return Identifiant du contact ajouté
 */
int DBInterface::add(Contact &c)
{
    QSqlQuery query;
    if(!query.exec(QString::fromStdString(c.getQuery(CREATE))))
    {
        QStringList l;
        l << "Problème d'insertion !";
        l << query.lastError().text();
        l << query.lastQuery();
        criticalError(l);
        return -1;
    }
    int id = query.lastInsertId().toInt();
    c.setId(id);
    contacts.addContact(c);
    return id;
}

/**
 * Ajoute une interaction au cache et à la base de données
 * @param i Interaction à ajouter
 * @return Identifiant de l'interaction ajoutée
 */
int DBInterface::add(Interaction &i)
{
    QSqlQuery query;
    if(!query.exec(QString::fromStdString(i.getQuery(CREATE))))
    {
        QStringList l;
        l << "Problème d'insertion !";
        l << query.lastError().text();
        l << query.lastQuery();
        criticalError(l);
        return -1;
    }
    int id = query.lastInsertId().toInt();
    i.setId(id);
    interactions.addInteraction(i);
    return id;
}

/**
 * Ajoute un todo au cache et à la base de données
 * @param t todo à ajouter
 * @return Identifiant du todo ajouté
 */
int DBInterface::add(Todo &t)
{
    QSqlQuery query;
    if(!query.exec(QString::fromStdString(t.getQuery(CREATE))))
    {
        QStringList l;
        l << "Problème d'insertion !";
        l << query.lastError().text();
        l << query.lastQuery();
        criticalError(l);
        return -1;
    }

    int id = query.lastInsertId().toInt();
    t.setId(id);
    todos.addTodo(t);
    return id;
}

/**
 * Modifie un contact dans la base de données
 * @param c Contact à modifier
 */
void DBInterface::update(Contact &c)
{
    Contact* pContact = this->contacts.getContact(c.getId());
    if(pContact)
        *pContact = c;

    this->dbTodos.push_back({CONTACT, UPDATE, c.getId()});
}

/**
 * Modifie une interactino dans la base de données
 * @param i Interaction à modifier
 */
void DBInterface::update(Interaction &i)
{
    Interaction* pInteraction = this->interactions.getInteraction(i.getId());
    if(pInteraction)
        *pInteraction = i;

    this->dbTodos.push_back({INTERACTION, UPDATE, i.getId()});
}

/**
 * Modifie un todo dans la base de données
 * @param t todo à modifier
 */
void DBInterface::update(Todo &t)
{

    Todo* pTodo = this->todos.getTodo(t.getId());
    if(pTodo)
        *pTodo = t;

    this->dbTodos.push_back({TODO, UPDATE, t.getId()});
}

/**
 * Supprime un contact de la base de données.
 * @param c Contact à supprimer
 */
void DBInterface::remove(Contact &c)
{
    this->dbTodos.push_back({CONTACT, DELETE, c.getId()});

    for(const Todo& t: c.getTodos())
        this->dbTodos.push_back({TODO, DELETE, t.getId()});
}

/**
 * @Supprime une interaction de la base de données.
 * @param i Interaction à supprimer
 */
void DBInterface::remove(Interaction &i)
{
    this->dbTodos.push_back({INTERACTION, DELETE, i.getId()});
}

/**
 * Supprime une tâche de la base de données
 * @param t todo à supprimer
 */
void DBInterface::remove(Todo &t)
{
    this->dbTodos.push_back({TODO, DELETE, t.getId()});
}

/**
 * Met à jour la base de données avec l'ensemble des données contenues dans le cache de l'interface.
 * En cas d'erreur, un retour est renvoyé dans le retour Debug() et la sauvegarde de cette entité est annulée.
 */
void DBInterface::flush()
{
    QSqlQuery query; // Query object
    QString q; // Query string

    // Get query from method ->getQuery()
    for(auto& dbTodo : this->dbTodos) {
        switch(dbTodo.type)
        {
            case INTERACTION:
            q = QString::fromStdString(interactions.getInteraction(dbTodo.id)->getQuery(dbTodo.subtype).c_str());
            if(dbTodo.type == DELETE)
                this->interactions.remove(dbTodo.id);
            break;
            case TODO:
                q = QString::fromStdString(todos.getTodo(dbTodo.id)->getQuery(dbTodo.subtype).c_str());
                if(dbTodo.type == DELETE)
                    this->todos.remove(dbTodo.id);
                break;
            case CONTACT:
                q = QString::fromStdString(contacts.getContact(dbTodo.id)->getQuery(dbTodo.subtype).c_str());
                if(dbTodo.type == DELETE)
                    this->contacts.remove(dbTodo.id);

            default:
                break;
        }
        if(!query.exec(q)) // Process
        {
            QStringList l;
            l << "Problème pour sauvegarder les données ! ";
            l << query.lastError().text();
            l << query.lastQuery();
            criticalError(l);
        }
    }

    this->dbTodos.clear(); // Clear cache
}

/**
 * Affiche une erreur critique avant de quitter le programme
 * @param error description de l'erreur
 */
void DBInterface::criticalError(QStringList errors)
{
    criticalError(errors.join("\n"));
}

/**
 * Affiche une erreur critique avant de quitter le programme
 * @param error description de l'erreur
 */
void DBInterface::criticalError(QString error)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(error);
    msgBox.exec();
    exit(1);
}

/**
 * Constructeur de l'interface.
 * @param path Lien vers la base de données SQLite
 */
DBInterface::DBInterface(std::string path)
{
    dbTodos = std::list<DB_todo>();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(path));
}

/**
 * Constructeur sans paramètre: Initialise automatiquement le lien vers la base de données par "CDAA.db".
 */
DBInterface::DBInterface() : DBInterface(std::string("data/CDAA.db")) {}

/**
 * Destructeur par défaut (géré par le compilateur)
 */
DBInterface::~DBInterface() = default;

