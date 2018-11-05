#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iostream> // Inclure ceci pour utiliser des "std::string"
#include <set> // Inclure ceci pour utiliser des ensembles (voir la déclaration d'attribut "std::set<int> states;" ci-dessous par exemple)
#include <map>
#include <vector>
#include <ctime>	
#include <cstdlib>



namespace fa {
    
    struct trans {
        bool operator<(const trans& other) const;
        int from;
        int to;
        char alpha;
    };


  class Automaton{
        public:
            std::set<int> getterStates() const;
            std::set<int> getterInitialStates() const;
            std::set<int> getterFinalStates() const;
            std::set<struct trans> getterTransitions() const;
            std::set<char> alphabets getterAlphabets() const;

            // Ici, on place les signatures des méthodes de la classe Automaton, par exemple pour addState et removeState :
            void addState(int state);
            void removeState(int state);
            // Autres signatures de méthodes...
            bool hasState (int state) const;
            std::size_t countStates() const;
            void setStateInitial(int state);
            bool isStateInitial(int state) const;
            void setStateFinal(int state);
            bool isStateFinal(int state) const;
            bool isDeterministic() const;
            bool isComplete() const;
            void addTransition(int from, char alpha, int to);   // <-
   			void removeTransition(int from, char alpha, int to);   // <-
   			bool hasTransition(int from, char alpha, int to) const;     // <-
   			std::size_t countTransitions() const;


        	std::size_t getAlphabetSize() const;
        	void prettyPrint(std::ostream& os) const;
            void dotPrint(std::ostream& os) const;

            void makeComplete();
            void makeComplement();
            bool isLanguageEmpty() const;


            //tp4
            static Automaton createProduct(const Automaton& lhs, const Automaton& rhs);
            bool hasEmptyIntersectionWith(const Automaton& other) const;

        private:
            // Ici, on place les déclarations d'attributs, par exemple :
            std::string name; // Le nom de l'automate si nécessaire (simplement à titre d'exemple)
            std::set<int> states; // L'ensemble des états de l'automate
            std::set<int> initialStates; // L'ensemble des états initiaux de l'automate
            std::set<int> finalStates; // L'ensemble des états initiaux de l'automate
            std::set<struct trans> transitions;
            std::set<char> alphabets;
            // Autres déclaration d'attributs (par exemple les transitions, pour lesquelles je vous conseille de créer une autre classe "Transition")...
            
    };

} // namespace fa

#endif // AUTOMATON_H
