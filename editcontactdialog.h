/**
 * @file editcontactdialog.h
 *
 * @brief Déclaration de la classe EditContactDialog
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef EDITP_CONTACT_DIALOG_H
#define EDITP_CONTACT_DIALOG_H

#include <QDialog>
#include <iostream>
#include "contact.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixelFormat>


namespace Ui {
class EditContactDialog;
}

/**
 * Classe d'interface pour la création et l'édition d'un contact
 * @brief Interface pour ajouter ou modifier un contact
 */
class EditContactDialog : public QDialog
{
    // Qt
    Q_OBJECT

    std::string picturePath; /*!< Chemin vers l'image. */

    //Attributs
    Contact contact; /*!< Contact modélisé. */
private:
    Ui::EditContactDialog *ui; /*!< Interface de la classe EditContactDialog. */
    // Methods
public:
    [[nodiscard]] Contact getContact();
    [[nodiscard]] Todos getTodos();
    [[nodiscard]] std::string getPicturePath() const;
    EditContactDialog(QWidget *parent = nullptr);
    EditContactDialog(Contact* c, QWidget *parent = nullptr); // Edit mode
    ~EditContactDialog();

private slots:
    void on_cancelButton_clicked();
    void on_submitButton_clicked();

    void on_pictureButton_clicked();

private:
    void setEditMode(Contact c);
};

#endif // EDITP_CONTACT_DIALOG_H
