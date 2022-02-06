/**
 * @file jsonmanager.cpp
 *
 * @brief Définition de la classe JsonManager.
 *
 * @version 1.0
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#include "jsonmanager.h"

/**
 * Enregistre les informations sous forme de json au chemin indiqué
 * @param filePath Lien vers le futur fichier json
 * @return Si l'opération s'est correctement déroulée
 */
bool JsonManager::write(std::string filePath)
{
    bool isOk = true;
    QFile file(QString::fromStdString(filePath));

    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        isOk = false;
      }

    // Clear the original content in the file
    file.resize(0);

    QJsonArray jsonArray;

    // For each map
    for(auto& map: data)
    {
        // Create node
        QJsonObject obj;
        // Insert (key, value) to node
        for(auto& [key, value]: map)
            obj.insert(QString::fromStdString(key), QString::fromStdString(value));
        // Add node to array
        jsonArray.append(obj);
    }

    // Document
    QJsonDocument jsonDoc;
    jsonDoc.setArray(jsonArray); // Set array
    file.write(jsonDoc.toJson()); // Write file
    file.close(); // Close file

    return isOk;
}

/**
 * Charge en cache l'ensemble des données contenues dans le fichier json précisé en paramètre
 * @param filePath Lien vers le fichier json
 * @return Si la lecture semble s'être bien passé
 */
bool JsonManager::read(std::string filePath)
{
    if(!QFile::exists(QString::fromStdString(filePath)))
        return false; // File doesn't exist

    // Clear cache before loading data
    clear();

    // Open and read file
    QFile jsonFile;
    jsonFile.setFileName(QString::fromStdString(filePath));
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);

    // Parse data into an array
    QString content;
    content = jsonFile.readAll();
    QJsonDocument jsonData = QJsonDocument::fromJson(content.toUtf8());
    QJsonArray json = jsonData.array();

    // complete list
    for(const auto& item: json) {
        std::unordered_map<std::string, std::string> tempData = {};
        for(const auto& i: item.toObject().toVariantMap().toStdMap())
            tempData.insert(std::pair<std::string, std::string>{i.first.toStdString(), i.second.toString().toStdString()});
        data.push_back(tempData);
    }

    return true; // No error
}

/**
 * Renvoie une list de map avec l'ensemble de données
 * @param type type de données voulues
 */
std::list<std::unordered_map<std::string, std::string>> JsonManager::getDataWithType(std::string type)
{
    std::list<std::unordered_map<std::string, std::string>> render = {};
    for(auto const& map: data)
        if(map.at("object_type") == type)
            render.push_back(map);
    return render;
}

/**
 * Vide l'ensemble des informations enregistrées
 */
void JsonManager::clear()
{
    data.clear();
}

/**
 * Ajoute des informations au cache
 * @param map Informations à ajouter (clef, valeur)
 */
void JsonManager::add(std::unordered_map<std::string, std::string> map)
{
    data.push_back(map);
}

/**
 * Constructeur de la classe
 */
JsonManager::JsonManager(){
    data = {};
}

/**
 * Destructeur par défaut géré par le compilateur
 */
JsonManager::~JsonManager() = default;
