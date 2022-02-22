/**
 * @file main.cpp
 *
 * @brief Entrée principale du programme.
 *
 * @version 1.0
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */
#include "mainwindow.h"
#include "editcontactdialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>

/**
 * Entrée principale de la classe avec initialisation de la MainWindow
 * @param argc Nombre d'arguments
 * @param argv Tableau d'arguments
 * @return Code erreur
 */
int main(int argc, char *argv[])
{
    // Declare QApplication with arguments (count + args)
    QApplication a(argc, argv);

    // QTranslator, not used here but for furture?
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "CDAA_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Create img folder if doesn't exist. Used for contact's image
    if(!QDir("img").exists())
        QDir().mkdir("img");

    // Init MainWindow
    MainWindow w;
    w.show(); // Show

    return a.exec(); // Returns QApplication code error (0 for no error)
}
