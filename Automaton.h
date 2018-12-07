#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iostream> // Inclure ceci pour utiliser des "std::string"
#include <set> // Inclure ceci pour utiliser des ensembles (voir la déclaration d'attribut "std::set<int> states;" ci-dessous par exemple)
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <math.h>



namespace fa {

    struct trans {
        bool operator<(const trans& other) const;
        int from;
        int to;
        char alpha;
    };


  class Automaton{
        public:
            std::set<int> getStates() const;
            std::set<int> getInitialStates() const;
            std::set<int> getFinalStates() const;
            std::set<struct trans> getTransitions() const;
            std::set<char> getAlphabets() const;

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
            void removeNonAccessibleStates();
            void removeNonCoAccessibleStates();
            std::set<int> readString(const std::string& word) const;
            bool match(const std::string& word) const;
            static Automaton createDeterministic(const Automaton& automaton);

            //tp4
            static Automaton createProduct(const Automaton& lhs, const Automaton& rhs);
            bool hasEmptyIntersectionWith(const Automaton& other) const;

            //tp6
            static Automaton createMinimalMoore(const Automaton& automaton);
            static Automaton createWithoutEpsilon(const Automaton& automaton);



            // n'oublie pas de vérifier qu'on ne peut pas utiliser dans nos tests
            std::set<struct trans> * getTransitionsPointer();
            // n'oublie pas de vérifier qu'on ne peut pas utiliser dans nos tests



        private:
            // Ici, on place les déclarations d'attributs, par exemple :
            std::string name; // Le nom de l'automate si nécessaire (simplement à titre d'exemple)
            std::set<int> states; // L'ensemble des états de l'automate
            std::set<int> initialStates; // L'ensemble des états initiaux de l'automate
            std::set<int> finalStates; // L'ensemble des états initiaux de l'automate
            std::set<struct trans> transitions;
            std::set<char> alphabets;
            int getTheBiggestState() const;
            int getToWithFromAndAlpha(int from, char alpha) const;
            std::set<int> from(int state) const;
            std::set<int> to(int state);
            bool depthFirstSearch(std::set<int> *visited, int current) const;
            bool depthFirstSearchReversed(std::set<int> *visited, int current);
            static bool CompareMap(std::map<int,int> &mapSrc, std::map<int,int> &mapDst);
            void readStringPartial(const std::string& word, int current, std::set<int> path, std::set<int> *derivated_states) const;
            std::set<int> getToSetWithFromAndAlpha(int from, char alpa) const;
            void deterministicRecProcess(std::set<int> new_step, std::map<std::set<int>,std::map<char,std::set<int>>> *process_board);
            Automaton createDeterministic();



            // Autres déclaration d'attributs (par exemple les transitions, pour lesquelles je vous conseille de créer une autre classe "Transition")...


    };

} // namespace fa

#endif // AUTOMATON_H
