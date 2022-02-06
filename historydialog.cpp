/**
 * @file historydialog.cpp
 *
 * @brief Définition des méthodes de la classe HistoryDialog
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#include "historydialog.h"
#include "ui_historydialog.h"

/**
 * Affiche l'historique dans le QTableWidget en fonction des filtres
 */
void HistoryDialog::refresh()
{
    // Clear and set table header
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList()
                << "Identifiant"
                << "Type"
                << "Description"
                << "Date"
                );

    // for all interactions :
    for(const auto& i: interactions)
    {
        // Check for type
        if(type != -1 && i.getType() != static_cast<unsigned int>(type))
            continue;

        // Check for start
        if(useFrom && i.getDate() < from)
            continue;

        //Check for end
        if(useTo && i.getDate() > to)
            continue;


        // Display row
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(i.getId())) ); // Set data

        if(i.getType() == ADD_CONTACT)
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("Création")); // Set data
        else if(i.getType() == EDIT_CONTACT)
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("Edition")); // Set data
        else
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("Suppression")); // Set data

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::fromStdString(i.getDescription()))); // Set data
        ui->tableWidget->item(ui->tableWidget->rowCount()-1, 2)->setToolTip(i.getDescription().c_str());

        // Use QDate in item to sort correctly
        QTableWidgetItem item;
        Date d = i.getDate();
        item.setData(Qt::DisplayRole, QDate(d.getYear(), d.getMonth()+1, d.getDay()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(item)); // Set data
    }

    // Stretch table
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

/**
 * Bouton quitter qui cache la fenêtre.
 */
void HistoryDialog::on_exitButton_clicked()
{
    this->hide();
}

/**
 * Quand on change le type des interactions à afficher
 * @param index Index du type d'interaction à afficher
 */
void HistoryDialog::on_typeComboBox_currentIndexChanged(int index)
{
    type = index-1;
    refresh();
}

/**
 * Quand l'utilisateur change le texte qui permet de définir la date de début de recherche
 * @param text Texte tapé par l'utilisateur
 */
void HistoryDialog::on_startEditLine_textChanged(const QString &text)
{
    useFrom = Utils::checkForDate(text.toStdString(), &from);
    refresh();
}

/**
 * Quand l'utilisateur change le texte qui permet de définir la date de fin de recherche
 * @param text Texte tapé par l'utilisateur
 */
void HistoryDialog::on_endEditLine_textChanged(const QString &text)
{
    useTo = Utils::checkForDate(text.toStdString(), &to);
    refresh();

}

/**
 * Initialisation de l'interface et des variables
 */
void HistoryDialog::init()
{
    type = -1;

    // ToolTips
    ui->startEditLine->setToolTip("dd/mm/yyy");
    ui->endEditLine->setToolTip("dd/mm/yyy");

    useFrom = false;
    useTo = false;

    refresh();
    ui->tableWidget->sortItems(3, Qt::DescendingOrder); // reverse order
}

/**
 * Constructeur de la classe avec une liste de contacts
 * @param is Liste de Contact de type Contacts
 * @param parent Fenêtre parente
 */
HistoryDialog::HistoryDialog(Contact c, QWidget *parent) :
    QDialog(parent),
    interactions(c.getInteractions()),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle(QString::fromStdString("Historique: " + c.getFullName()));

    init();
}

/**
 * Constructeur de la classe avec une liste d'interactions
 * @param is Liste d'Interaction de type Interactions
 * @param parent Fenêtre parente
 */
HistoryDialog::HistoryDialog(Interactions is, QWidget *parent) :
    QDialog(parent),
    interactions(is),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle("Historique");

    init();
}

/**
 * Destructeur de la classe
 */
HistoryDialog::~HistoryDialog()
{
    delete ui;
}
