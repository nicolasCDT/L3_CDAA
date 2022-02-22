/**
 * @file editcontactdialog.cpp
 *
 * @brief Définition de la classe EditContactDialog.
 *
 * @version 1.0
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#include "editcontactdialog.h"
#include "ui_editcontactdialog.h"

/**
 * Constructeur de la classe EditContactDialog
 * Utilisation en mode création
 * @param parent classe parente (défault =  null)
 */
EditContactDialog::EditContactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditContactDialog)
{
    ui->setupUi(this);
    setModal(true);
}

/**
 * Constructeur de la classe EditContactDialog
 * Utilisation en mode modification
 * @param c Contact a modifier
 * @param parent classe parente (défault =  null)
 */
EditContactDialog::EditContactDialog(Contact* c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditContactDialog)
{
    ui->setupUi(this);
    setModal(true);
    if(c)
        setEditMode(*c);
}

/**
 * Destructeur de la classe EditContactDialog
 */
EditContactDialog::~EditContactDialog()
{
    delete ui;
}

/**
 * Retourne le contact modélisé
 * @return Contact modélisé
 */
Contact EditContactDialog::getContact()
{
    return contact;
}

/**
 * Quand on appuie sur le bouton annuler -> on cache la fenêtre
 */
void EditContactDialog::on_cancelButton_clicked()
{
    this->hide();
}

/**
 * Quand on appuie sur le bouton pour valider
 * On ferme la fenêtre après avoir enregistré les informations dans l'attribut contact
 */
void EditContactDialog::on_submitButton_clicked()
{
    if(this->ui->firstNameBox->text().isEmpty() ||
            this->ui->lastNameBox->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Vous devez donner au moins un nom et un prénom au contact.");
        msgBox.exec();
        return;
    }

    contact.setCompany(ui->companyBox->text().toStdString());
    contact.setFirstName(ui->firstNameBox->text().toStdString());
    contact.setEmail(ui->emailBox->text().toStdString());
    contact.setLastName(ui->lastNameBox->text().toStdString());
    contact.setPhone(ui->telBox->text().toStdString());
    contact.setNote(ui->noteBox->toPlainText().toStdString());
    std::string s = ui->noteBox->toPlainText().toStdString();

    accept();
}

/**
 * On passe la fenête en mode édition :
 *      * On remplit les cases avec le contact passé en paramètre
 *      * On affiche son image si elle existe
 *      * On change le titre de la fenêtre
 * @param c Contact à modifier
 */
void EditContactDialog::setEditMode(Contact c)
{
    contact = c;
    setWindowTitle("Editer un contact"); // Update window title
    ui->title->setText("Editer le contact"); // Update title
    ui->firstNameBox->setText(QString::fromStdString(c.getFirstName()));
    ui->lastNameBox->setText(QString::fromStdString(c.getLastName()));
    ui->emailBox->setText(QString::fromStdString(c.getEmail()));
    ui->telBox->setText(QString::fromStdString(c.getPhone()));
    ui->companyBox->setText(QString::fromStdString(c.getCompany()));
    ui->noteBox->setPlainText(QString::fromStdString(c.getNote()));

    std::string fileName = "img/" + std::to_string(c.getId()) + ".png";

    if(QFileInfo::exists(QString::fromStdString(fileName)))
    {
        QPixmap img(QString::fromStdString(fileName));
        ui->pictureButton->setIcon(img);
    }
}

/**
 * Quand on clique sur l'image :
 * Ouvre une fenêtre pour selectionner une nouvelle image.
 * Les formats acceptés sont : png, jpg et bmp.
 * La transparence n'est pas gérée car les images sont stockés en png
 */
void EditContactDialog::on_pictureButton_clicked()
{
    std::string fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)")).toStdString();
    if(!QFileInfo::exists(QString::fromStdString(fileName)))
        return;
    picturePath = fileName;

    QPixmap img(QString::fromStdString(fileName));
    ui->pictureButton->setIcon(img);
}

/**
 * Renvoie les tâches trouvées dans la note du Contact sous forme de Todos
 * @return Liste des tâches du Contact
 */
Todos EditContactDialog::getTodos()
{
    Todos ts = Todos::extractFromString(ui->noteBox->toPlainText().toStdString());
    return ts;
}

/**
 * Renvoie le chemin vers l'image selectionnée
 * @return Chemin jusu'à l'image du Contact
 */
std::string EditContactDialog::getPicturePath() const
{
    return picturePath;
}

