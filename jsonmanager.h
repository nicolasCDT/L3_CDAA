/**
 * @file jsonmanager.h
 *
 * @brief Déclaration de la classe JsonManager
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <unordered_map>
#include <list>
#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>



/**
 * Classe servant d'utilitaire pour gérer l'exportation des données en JSON.
 *  Elle permet de générer du JSON à partir de map non triée (clef, valeur).
 * @brief Classe servant d'utilitaire pour gérer l'exportation des données en JSON.
 */
class JsonManager
{
    std::list<std::unordered_map<std::string, std::string>> data; /*!< Liste de maps (non ordordonnées) avec les données à stocker */
public:

    void add(std::unordered_map<std::string, std::string> map);
    // void add(int nb, ...); -> useless here
    bool write(std::string filePath);
    bool read(std::string filePath);
    std::list<std::unordered_map<std::string, std::string>> getDataWithType(std::string type);
    void clear();

    JsonManager();
    ~JsonManager();
};

#endif // JSONMANAGER_H
