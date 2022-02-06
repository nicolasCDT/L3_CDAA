/**
 * @file interactions.h
 *
 * @brief Déclaration de la classe Interactions.
 *      Interface adaptée afin de mieux gérer une liste d'interactions
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#ifndef CDAA_INTERACTIONS_H
#define CDAA_INTERACTIONS_H

#include <list>
#include "interaction.h"

/**
 * Classe modélisant une liste d'interactions permettant des opérations supplémentaires par rapport à la list de la bibliothèque std
 * \brief Liste d'interactions
 */
class Interactions {
private:
    std::list<Interaction> interactions;/*!< Listes des interactions. */

public:
    // Voir interactions.cpp pour la documentation des méthodes
    void addInteraction(const Interaction& i);

    void sortByDate(bool reverse=false);
    void remove(int id);
    void remove(const Interaction& i);

    void clear();

    [[nodiscard]] unsigned int size() const;

    [[nodiscard]] Interaction* getInteraction(int id);
    [[nodiscard]] Interactions getInteractionsBetween(Date& to, Date& from);
    [[nodiscard]] Interactions getUrgentInteractions();


    using iterator = std::list<Interaction>::iterator;
    using const_iterator = std::list<Interaction>::const_iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    // Surcharges d'opérateurs
    friend Interactions operator+(Interactions is, const Interaction& i);
    friend Interactions& operator+=(Interactions& is, const Interaction& i);
    friend Interactions& operator+=(Interactions& is, const Interactions& i);
    friend Interactions operator-(Interactions is, const Interaction& i);
    friend Interactions& operator-=(Interactions& is, const Interaction& i);
    friend std::ostream& operator<<(std::ostream& os, const Interactions& is);

    explicit Interactions(const Interaction& i);
    explicit Interactions(const std::list<Interaction>& interactions);
    Interactions();
    ~Interactions();

    static Interactions fromListOfMaps(std::list<std::unordered_map<std::string, std::string>> data);
};


#endif //CDAA_INTERACTIONS_H
