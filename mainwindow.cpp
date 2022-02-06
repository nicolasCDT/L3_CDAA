/**
 * @file mainwindow.cpp
 *
 * @brief Définition de la classe MainWindow (fenêtre principale).
 *
 * @version 1.0
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unordered_map>

/**
 * Rafraichit la table des contacts entière.
 * La dernière colonne est un bouton qui affiche un menu avec 3 boutons (QAction) qui utilisent les fonctions anonymes afin de relier sur 3 méthodes:
 *      * editContact(id)
 *      * deleteContact(id)
 *      * historyContact(id)
 */
void MainWindow::refresh()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList()
                << "Identifiant"
                << "Nom"
                << "Entreprise"
                << "Téléphone"
                << "Création"
                << "Actions"
                );
    for(auto& c: this->contacts)
    {
        // Row
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(c.getId())) ); // Set data
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(c.getFullName().c_str())); // Set data
         ui->tableWidget->item(ui->tableWidget->rowCount()-1, 1)->setToolTip(c.getFullName().c_str());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(c.getCompany().c_str())); // Set data
        ui->tableWidget->item(ui->tableWidget->rowCount()-1, 2)->setToolTip(c.getCompany().c_str());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3,  new QTableWidgetItem(c.getPhone().c_str())); // Set data
        ui->tableWidget->item(ui->tableWidget->rowCount()-1, 3)->setToolTip(c.getPhone().c_str());
        QTableWidgetItem item;
        Date d = c.getCreationDate();
        item.setData(Qt::DisplayRole, QDate(d.getYear(), d.getMonth()+1, d.getDay()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4,  new QTableWidgetItem(item)); // Set data

        // Last button with QMenu
        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("...");
        QMenu* menu = new QMenu();
        menu->addAction("Editer", [this, c](bool){editContact(c.getId());});
        menu->addAction("Supprimer", [this, c](bool){deleteContact(c.getId());});
        menu->addAction("Historique", [this, c](bool){historyContact(c.getId());});
        btn_edit->setMenu(menu);

        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 5, btn_edit); // Add button
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


/**
 * Quand l'utilisateur édite l'EditLine de recherche on met à jour la table.
 * @param text Texte entré par l'utilisateur
 */
void MainWindow::on_lineEdit_textEdited(const QString &text)
{
    std::vector<int> hide{};
    for(int row=0; row<ui->tableWidget->rowCount(); row++)
    {
        bool keep = false;
        for(int column=0; column<ui->tableWidget->columnCount()-1; column++)
        {
            if(ui->tableWidget->item(row, column)->text().contains(text, Qt::CaseInsensitive))
                keep = true;
        }

        if(keep)
            ui->tableWidget->showRow(row);
        else
            ui->tableWidget->hideRow(row);
    }
}

/**
 * Quand l'utilisateur clique sur le bouton Ajouter.
 * Ouvre une fenêtre de dialogue du type EditContactDialog afin de saisir le nouvel utilisateur.
 *
 * Si l'ajout est validé, on connecte la fenêtre avec la méthode addConfirm.
 */
void MainWindow::on_actionAddContact_triggered()
{
    editModal = new EditContactDialog(this); // Create Mode
    connect(editModal, SIGNAL(accepted()), this, SLOT(addConfirm()));
    editModal->exec();
}

/**
 * Quand le dialogue EditContactDialog confirme l'ajout d'un contact.
 * On le récupère et on l'ajoute au cache actuel et à la base de données.
 * On analyse également sa note afin de créer les tâches et on prend en charge son image à l'aide de la méthode imgProcess.
 */
void MainWindow::addConfirm()
{
    Contact c = editModal->getContact();
    c.setId(dbInterface.add(c));
    Interaction i;
    i.setType(ADD_CONTACT);
    i.setOwnerId(c.getId());
    std::string description = "Création du contact: " + c.getFullName();
    i.setDescription(description);
    i.setId(dbInterface.add(i));
    c.addInteraction(i);
    interactions.addInteraction(i);
    imgProcess(editModal->getPicturePath(), c.getId());
    for(auto& t : editModal->getTodos()) {
        t.setOwnerId(c.getId());
        t.setId(dbInterface.add(t));
    }

    dbInterface.flush();
    contacts.addContact(c);
    refresh();
}

/**
 * Quand on quitte sur le bouton "Quitter" : on ferme l'application sans erreur (code: 0)
 */
void MainWindow::on_actionClose_triggered()
{
    exit(0);
}

/**
 * Quand un utilisateur clique sur le bouton pour éditer un contact :
 *      Ouvre une fenêtre de dialog du type EditContactDialog en mode édition.
 *      On connecte la validation sur la méthode editConfirm()
 * @param id Identifiant du contact à éditer
 */
void MainWindow::editContact(int id) {
    editModal = new EditContactDialog(contacts.getContact(id), this);
    connect(editModal, SIGNAL(accepted()), this, SLOT(editConfirm()));
    editModal->exec();
}

/**
 * Quand l'utilisateur valide l'édition d'un joueur.
 * La procédure est similaire à la création à l'exception qu'on supprime ses tâches déjà existantes avant de les recréer en fonction de la note.
 */
void MainWindow::editConfirm() {
    Contact c = editModal->getContact();
    Interaction i;
    i.setOwnerId(c.getId());
    Date d;
    i.setDate(d);
    std::string description = "Edition du contact: " + c.getFullName();
    i.setDescription(description);
    i.setType(EDIT_CONTACT);
    i.setId(dbInterface.add(i));
    c.addInteraction(i);
    interactions.addInteraction(i);

    imgProcess(editModal->getPicturePath(), c.getId());

    // Delete old todo
    for(Todo t: c.getTodos()) {
        dbInterface.remove(t);
    }

    Todos ts = Todos::extractFromString(c.getNote()); // Get new todos

    // Add this todos to DB
    for(Todo& t: ts) {
        t.setOwnerId(c.getId());
        t.setId(dbInterface.add(t));
    }

    // Set list to Contact
    c.setTodos(ts);

    dbInterface.update(c); // Update on db
    *contacts.getContact(c.getId()) = c; // Update application cache
    dbInterface.flush(); // Push modifications
    refresh(); // Refresh ui
}

/**
 * Supprime un contact grâce à son id. La méthode affiche une boite de dialogue pour confirmer ou non la suppression du contact.
 * @param id Identifiant du contact à supprimer
 */
void MainWindow::deleteContact(int id) {
    Contact* c = contacts.getContact(id);
    if(!c)
        return;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Confirmation",
                                  QString::fromStdString("Voulez-vous supprimer le contact: " + c->getFullName() + " ?"),
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        this->dbInterface.remove(*c);
        std::string description = "Suppresion du contact: " + c->getFullName();
        contacts.remove(id);
        refresh();
        Interaction i;
        i.setOwnerId(-1); // Non relié à un contact
        Date d;
        i.setDate(d);
        i.setType(REMOVE_CONTACT);
        i.setDescription(description);
        i.setId(dbInterface.add(i));
        interactions.addInteraction(i);
        imgDeleteProcess(id);
        dbInterface.flush();
    }
}

/**
 * Affiche l'historique des interactions d'un contact grâce à son identifiant à l'aide du dialogue HistoryDialog.
 * @param id Identifiant du contact
 */
void MainWindow::historyContact(int id) {
    Contact* c = contacts.getContact(id);
    if(!c)
        return;
    historyModal = new HistoryDialog(*c, this);
    historyModal->exec();
    delete historyModal;
}

/**
 * Quand l'utilisateur demande l'exportation des données.
 * Procédure:
 *      * On demande un dossier d'exportation afin de créer le export.json;
 *      * On ajoute au gestionnaire JsonManager l'ensemble des données sous forme de map;
 *      * On écrit toutes les données au format JSON dans le bon fichier.
 */
void MainWindow::on_actionExport_triggered()
{
    std::string path = QFileDialog::getExistingDirectory(0, ("Dossier d'exporation"), QDir::currentPath()).toStdString();

    if(path == "")
        return;

    for(auto& c: contacts) {
        jsonMgr.add(c.toMap());
        for(auto& t: c.getTodos())
            jsonMgr.add(t.toMap());
    }

    for(auto& i : interactions)
        jsonMgr.add(i.toMap());

    QMessageBox msgBox;
    if(jsonMgr.write(path + "/export.json"))
        msgBox.setText("Le fichier a bien été édité.");
    else
        msgBox.setText("Error d'exporation.");
    msgBox.exec();
}

/**
 * Quand l'utilisateur demande l'importation de données.
 * Procédure:
 *      * On demande le fichier json a charger;
 *      * le JsonManager charge l'ensemble des données;
 *      * On ajoute toutes les données à la base de données et on recharge le cache de l'application.
 */
void MainWindow::on_actionImportation_triggered()
{
    std::string path = QFileDialog::getOpenFileName(this, tr("Open json"), ".", tr("json Files (*.json)")).toStdString();
    if(!QFileInfo::exists(QString::fromStdString(path)))
        return;
    if(!jsonMgr.read(path))
    {
        QMessageBox msgBox;
        msgBox.setText("Impossible de charger ce document json.");
        msgBox.exec();
        return;
    }

    importFromJsonMgr();

   // Recharchement des données:
    dbInterface.loadData();
    contacts = dbInterface.getContacts();
    interactions = dbInterface.getInteractions();
    refresh();
}

/**
 * Importe les données du cache du JsonManager et les inclus dans l'application
 */
void MainWindow:: importFromJsonMgr()
{
   Contacts cs = Contacts::fromListOfMaps(jsonMgr.getDataWithType("contact"));
   Interactions is = Interactions::fromListOfMaps(jsonMgr.getDataWithType("interaction"));
   Todos ts = Todos::fromListOfMaps(jsonMgr.getDataWithType("todo"));

   // Make new id for all contact
   for(auto& c: cs)
   {
        int oldId = c.getId();
        c.setId(dbInterface.add(c));

        // Put all interactions
        for(auto& i: is)
        {
            if(i.getOwnerId() == oldId)
            {
                i.setOwnerId(c.getId());
                dbInterface.add(i);
            }
        }

        // Put all Todos
        for(auto& t: ts)
        {
            if(t.getOwnerId() == oldId)
            {
                t.setId(c.getId());
                dbInterface.add(t);
            }
        }
   }


   // Registrer interactions without owner
   for(auto& i: interactions)
   {
       if(i.getOwnerId() == -1)
           dbInterface.add(i);
   }

}


/**
 * Quand l'utilisateur clique sur le bouton pour obtenir l'historique de toutes les interactions.
 * On affiche une fenêtre de dialogue du type HistoryDialog afin d'afficher les informations.
 */
void MainWindow::on_historyButton_clicked()
{
    historyModal = new HistoryDialog(interactions, this);
    historyModal->exec();
    delete historyModal;

}

/**
 * Quand l'utilisateur demandes les statistiques de l'application.
 * On affiche ces informations à l'aide d'une QMessageBox;
 */
void MainWindow::on_actionStats_triggered()
{
    QMessageBox msgBox;
    int todoCount = 0;
    for(auto& c: contacts)
        todoCount += c.getTodos().size();
    std::string text = "Statistiques:\n";
    text += "Nombre de contacts: " + std::to_string(contacts.size()) + "\n";
    text += "Nombre d'interactions: " + std::to_string(interactions.size()) + "\n";
    text += "Nombre de rendez-vous: " + std::to_string(todoCount) + "\n";
    msgBox.setText(QString::fromStdString(text));
    msgBox.exec();

}

/**
 * Procédure afin de gérer une image.
 * @param fileName Chemin de l'image à traiter
 * @param id Identifiant du contact concerné
 */
void MainWindow::imgProcess(std::string fileName, int id)
{
    if(fileName == "")
        return;

    QPixmap img(QString::fromStdString(fileName));
    img.save(QString::fromStdString("img/" + std::to_string(id) + ".png"));
}

/**
 * Suppression de l'image d'un membre grâce à son identifiant (lors d'une suppression de contact).
 * @param id Identifiant du contact
 */
void MainWindow::imgDeleteProcess(int id)
{
    std::string path = "img/" + std::to_string(id) + ".png";
    if(QFileInfo::exists(QString::fromStdString(path)))
    {
        QFile file(QString::fromStdString(path));
        file.remove();
    }
}

/**
 * Quand l'utilisateur demande à accéder à la fenêtre de gestions des rendez-vous.
 * Affiche une boite de dialogue du type TodoDialog qui prend en paramètre l'ensemble des contacts afin de gérer les rendez-vous.
 */
void MainWindow::on_todoButton_clicked()
{
    todoModal = new TodoDialog(contacts, this);
    todoModal->exec();
}

/**
 * Constructeur de la classe MainWindow
 * @param parent Widget parent (default=null)
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Menu Principal");
    dbInterface.open();
    dbInterface.loadData();
    contacts = dbInterface.getContacts();
    interactions = dbInterface.getInteractions();
    refresh();
    //ui->tableWidget->sortItems(4, Qt::DescendingOrder); // reverse order
}

/**
 * Destructeur de la classe MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
    // delete modal -> Qt
}

