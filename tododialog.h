/**
 * @file tododialog.h
 *
 * @brief Déclaration de la classe TodoDialog
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef TODODIALOG_H
#define TODODIALOG_H

#include <QDialog>
#include "contacts.h"
#include <QCompleter>
#include "todos.h"

namespace Ui {
class TodoDialog;
}

/**
 * Classe permettant l'affichage des différentes tâches avec plusieurs filtres :
 *      * Nom du contact
 *      * Date minimum
 *      * Date maximum
 *      * Afficher exclusivement les rendez-vous urgents
 * Classe permettant l'affichage des différentes tâches avec plusieurs filtres
 */
class TodoDialog : public QDialog
{
    Q_OBJECT

private:
    int currentViewId; /*!< Index du TODO selectionne */
    bool urgent; /*!< Affichage des tâches urgentes uniquement */
    bool useFrom; /*!< Filtrer avec une date de début */
    bool useTo; /*!< Filtrer avec une date de fin */
    Date from; /*!< Date de début de recherche */
    Date to; /*!< Date de fin de recherche */
    std::string nameFilter; /*!< Nom a rechercher */
    Contacts contacts; /*!< Listes des contacts */
    Todos todos; /*!< Listes des tâches */

    void initCompleter();
    void refresh();
    void urgentDisplayUpdate();

public:
    explicit TodoDialog(Contacts cs, QWidget *parent = nullptr);
    ~TodoDialog();

private slots:
    void on_contactNameBox_textChanged(const QString &text);
    void on_fromEditBox_textChanged(const QString &text);
    void on_toEditBox_textChanged(const QString &text);

    void on_urgentOnly_stateChanged(int checked);

    void on_tableWidget_cellActivated(int row, int column);

private:
    Ui::TodoDialog *ui; /*!< Interface de la classe TodoDialog */
};

#endif // TODODIALOG_H
