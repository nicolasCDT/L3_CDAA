/**
 * @file mainwindow.h
 *
 * @brief Déclaration de la classe MainWindow
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contacts.h"
#include <QPushButton>
#include <QLayout>
#include <QMenu>
#include "editcontactdialog.h"
#include "historydialog.h"
#include "tododialog.h"
#include <dbinterface.h>
#include <jsonmanager.h>

QT_BEGIN_NAMESPACE
/**
 * NameSpace géré par Qt
 */
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * Classe ave l'interface principale de l'application.
 * Elle met en relation l'ensemble des autres classes et les gère.
 * C'est également cette classe qui contient le cache actuelle de l'application et qui intéragit avec l'interface de base de données (DBInterface).
 * @brief Classe ave l'interface principale de l'application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DBInterface dbInterface; /*!< Interface de base de données */
    Contacts contacts; /*!< Liste des contacts */
    Interactions interactions; /*!< Liste des interactions */
    JsonManager jsonMgr; /*!< Interface pour le Json (exportation) */

public:
    void refresh();
    void imgProcess(std::string fileName, int id);
    void importFromJsonMgr();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_textEdited(const QString &text);
    void on_actionAddContact_triggered();

    void on_actionClose_triggered();

    void editContact(int id);
    void deleteContact(int id);
    void historyContact(int id);

    void addConfirm();
    void editConfirm();

    void imgDeleteProcess(int id);

    // UI
    void on_actionExport_triggered();

    void on_actionImportation_triggered();

    void on_actionStats_triggered();
    void on_historyButton_clicked();

    void on_todoButton_clicked();
private:
    Ui::MainWindow *ui; /*!< Interface de la classe MainWindow */
    EditContactDialog* editModal; /*!< Fenêtre d'édition/création de contact */
    HistoryDialog* historyModal; /*!< Fenêtre d'historique d'interactions */
    TodoDialog* todoModal; /*!< Fenêtre pour consulter les rendez-vous */

};
#endif // MAINWINDOW_H
