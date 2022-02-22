/**
 * @file historydialog.h
 *
 * @brief Déclaration de la classe HistoryDialog
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QDate>
#include "contact.h"
#include <ctime>
#include "utils.h"

namespace Ui {
class HistoryDialog;
}

/**
 * Classe d'interface qui permet l'affichage d'une liste d'interactions.
 *
 * @brief Historique d'interactions
 */
class HistoryDialog : public QDialog
{
    Q_OBJECT
private:
    Interactions interactions; /*!< Liste des interactions à afficher. */

    // Search
    int type; /*!< Type d'interactions à afficher */
    Date from; /*!< Date de début de recherche */
    bool useFrom; /*!< Activer la rechercher avec date de début */
    Date to; /*!< Date de fin de recherche */
    bool useTo; /*!< Activer la rechercher avec date de fin */

    bool checkForDate(std::string s, Date* d);

    void refresh();

    void init();

public:
    explicit HistoryDialog(Contact c, QWidget *parent = nullptr);
    explicit HistoryDialog(Interactions is, QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void on_exitButton_clicked();
    void on_typeComboBox_currentIndexChanged(int index);
    void on_startEditLine_textChanged(const QString &text);
    void on_endEditLine_textChanged(const QString &text);

private:
    Ui::HistoryDialog *ui; /*!< Interface de la classe HistoryDialog. */
};

#endif // HISTORYDIALOG_H
