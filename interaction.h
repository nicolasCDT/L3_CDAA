/**
 * @file interaction.h
 *
 * @brief Déclaration de la classe Interaction
 *      Cette classe gère les commentaires et les rendez-vous. On peut facilement ajouter des types d'interactions
 *      en complétant la structure types.
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef CDAA_INTERACTION_H
#define CDAA_INTERACTION_H

#include "date.h"
#include <string>
#include "utils.h"
#include <unordered_map>
#include <ostream>


/**
 * Enumération des différents types d'interactions possibles avec cette classe.
 */
enum types
{
    ADD_CONTACT,        // 0
    REMOVE_CONTACT,     // 1
    EDIT_CONTACT,       // 2
    MAX_NUM,            // END
    NONE
};

/**
 * Interaction liée à un contact.
 * Elle permet de modéliser des interactions de plusieurs types (voir énumération 'types').
 * Chaque interaction est modélisée par un identifiant, un propriétaire, un type, une description et une date.
 * \brief Interaction liée à un contact
 */
class Interaction {
private:
    int id; /*!< Identifiant de l'interaction (-1 si non connu). */
    int ownerId; /*!< Identifiant du propriétaire de l'interaction. */
    unsigned int type; /*!< Type de l'interaction (voir énumération types). */
    std::string description; /*!< Description textuelle de l'interaction. */
    Date date; /*!< Date de l'interaction. */

public:

    // Voir Interaction.cpp pour la documentation des méthodes
    [[nodiscard]] int getId() const;
    void setId(int id);

    [[nodiscard]] int getOwnerId() const;
    void setOwnerId(int ownerId);

    [[nodiscard]] unsigned int getType() const;
    void setType(unsigned int type);

    [[nodiscard]] Date getDate() const;
    void setDate(Date date);

    [[nodiscard]] const std::string& getDescription() const;
    void setDescription(std::string& description);


    [[nodiscard]] std::string getQuery(int mode);

    std::unordered_map<std::string, std::string> toMap() const;

    friend bool operator==(const Interaction& a, const Interaction& b);
    friend bool operator!=(const Interaction& a, const Interaction& b);
    friend std::ostream& operator<<(std::ostream& os, const Interaction& i);

    // Constructeurs et destructeur
    Interaction(int ownerId, unsigned int type, std::string& description, Date& date);
    Interaction();
    ~Interaction();


    static Interaction fromMap(std::unordered_map<std::string, std::string> data);
};

#endif //CDAA_INTERACTION_H
