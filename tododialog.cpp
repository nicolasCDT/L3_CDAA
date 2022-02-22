/**
 * @file tododialog.cpp
 *
 * @brief Définition de la classe TodoDialog
 *          Interface servant à afficher l'ensemble des tâches des contacts
 *
 * @version 1.0
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#include "tododialog.h"
#include "ui_tododialog.h"

/**
 * Actualise l'affichage du QTableWidget avec potentiellement les filtres appliqués
 */
void TodoDialog::refresh()
{
    // Clear and set table header
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList()
                << "Identifiant"
                << "Contact"
                << "Description"
                << "Date"
                );

    // for all interactions :
    for(auto& t: todos)
    {
        // Prevent access violation
        Contact* temp = contacts.getContact(t.getOwnerId());
        if(!temp)
        {
            qDebug() << QString::fromStdString("Propriétaire introuvable pour la todo: " + std::to_string(t.getId()));
            continue;
        }

        Contact owner = *temp;
        std::string searchString = ui->contactNameBox->text().toStdString();
        if(owner.getFullName().find(searchString) == std::string::npos
                && t.getDescription().find(searchString) == std::string::npos
                && t.getDate().getDateCompactString().find(searchString) == std::string::npos)
            continue;

        if(urgent && !t.isUrgent()) // Only display urgent todo
            continue;

        if(!urgent && useFrom && t.getDate() < from && !t.isUrgent()) // from
            continue;

        if(!urgent && useTo && t.getDate() > to) // to
            continue;

        // Display row
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(t.getId())) ); // Set data
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::fromStdString(contacts.getContact(t.getOwnerId())->getFullName()))); // Set data
        ui->tableWidget->item(ui->tableWidget->rowCount()-1, 1)->setToolTip(QString::fromStdString(contacts.getContact(t.getOwnerId())->getFullName()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::fromStdString(t.getDescription()))); // Set data
        ui->tableWidget->item(ui->tableWidget->rowCount()-1, 2)->setToolTip(QString::fromStdString(t.getDescription()));

        if(t.isUrgent()) {
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem("Urgent")); // Set data
        }
        else
        {
            // QDate for sorting
            QTableWidgetItem item;
            Date d = t.getDate();
            item.setData(Qt::DisplayRole, QDate(d.getYear(), d.getMonth()+1, d.getDay()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(item)); // Set data

        }
    }

    // Stretch table
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if(currentViewId != -1) {
        Contact c = *contacts.getContact(todos.getTodo(currentViewId)->getOwnerId());
        ui->viewNoteText->setPlainText(QString::fromStdString(c.getNote()));
    }
}

/**
 * Initialise le completer sur la liste des contacts
 */
void TodoDialog::initCompleter()
{
    QStringList contactList;

    for(auto& c: contacts)
        contactList << QString::fromStdString(c.getFullName());

    QCompleter *completer = new QCompleter(contactList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->contactNameBox->setCompleter(completer);

}

/**
 * Quand le texte dans la barre de recherche est changé.
 * @param text Texte à rechercher
 */
void TodoDialog::on_contactNameBox_textChanged(const QString &text)
{
    nameFilter = text.toStdString();
    refresh();
}

/**
 * Quand l'utilisateur change le texte qui permet de définir la date de début de recherche
 * @param text Texte tapé par l'utilisateur
 */
void TodoDialog::on_fromEditBox_textChanged(const QString &text)
{
    useFrom = Utils::checkForDate(text.toStdString(), &from);
    refresh();
}

/**
 * Quand l'utilisateur change le texte qui permet de définir la date de fin de recherche
 * @param text Texte tapé par l'utilisateur
 */
void TodoDialog::on_toEditBox_textChanged(const QString &text)
{
    useTo = Utils::checkForDate(text.toStdString(), &to);
    refresh();
}

/**
 * Actualise l'affichage quand on active le mode qui permet de voir exclusivement les tâches urgentes (sans date)
 */
void TodoDialog::urgentDisplayUpdate()
{
    ui->toEditBox->setEnabled(!urgent);
    ui->fromEditBox->setEnabled(!urgent);
}

/**
 * Quand l'utilisateur coche/décoche la case permettant d'afficher ou non exclusivement les tâches urgentes (sans date)
 * @param checked
 */
void TodoDialog::on_urgentOnly_stateChanged(int checked)
{
    urgent = (bool)checked;
    urgentDisplayUpdate();
    refresh();
}

/**
 * Quand on selectionne une case de le tableau.
 *  Selectionne l'intégralité de la ligne et met à jour la note liée
 * @param row Ligne de la case selectionée
 * @param column Colonne de la case selectionée
 */
void TodoDialog::on_tableWidget_cellActivated(int row, __attribute__((unused)) int column)
{
    ui->tableWidget->selectRow(row);
    currentViewId = ui->tableWidget->item(row, 0)->text().toInt();
    Contact c = *contacts.getContact(todos.getTodo(currentViewId)->getOwnerId());
    ui->viewNoteText->setPlainText(QString::fromStdString(c.getNote()));
}

/**
 * Constructeur de la classe TodoDialog.
 * @param cs Liste des contacts avec leurs tâches
 * @param parent Fenêtre parente
 */
TodoDialog::TodoDialog(Contacts cs, QWidget *parent) :
    QDialog(parent),
    contacts(cs),
    ui(new Ui::TodoDialog)
{
    ui->setupUi(this);
    urgent = false;
    useTo = false;
    useFrom = false;
    nameFilter = "";
    currentViewId = -1;
    ui->viewNoteText->setEnabled(false);
    setWindowTitle("Consulation des rendez-vous");

    // Register all todos:
    for(const auto& c : contacts)
        for(const auto& t: c.getTodos())
            todos.addTodo(t);

    initCompleter();
    refresh();
    ui->tableWidget->sortItems(3, Qt::DescendingOrder); // reverse order
}

/**
 * @Destructeur de la classe TodoDialog
 */
TodoDialog::~TodoDialog()
{
    delete ui;
}
