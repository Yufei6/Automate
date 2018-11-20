#include "Automaton.h"

#include <cassert>


namespace fa {
	// Complexity: O(log n)
  	void fa::Automaton::addState(int state){
	    // Ici, on écrit le code pour ajouter un état à l'automate
	    // La méthode "addState" doit naturellement ajouter un état à l'automate
	    // On ajoute donc l'état "state" à l'ensemble des états de l'automate (donc à l'attribut "states"):
	    states.insert(state);
	    // Pour débugger plus facilement, vous pouvez afficher le nombre d'états dans l'automate après insertion :
	    // std::cout << "Après insertion de l'état " << state << ", l'automate possède " << states.size() << " état(s)." << std::endl;
	}


	// Complexity: O(log n)
	void fa::Automaton::removeState(int state){
		states.erase(state);
		// std::cout << "Après suppression de l'état " << state << ", l'automate possède " << states.size() << " état(s)." << std::endl;

	}


	// Complexity: O(log n)
	bool fa::Automaton::hasState(int state) const{
		std::set<int>::iterator iter;
		iter=states.find(state);
		if(iter!=states.end()){
			return true;
		}
		else{
			return false;
		}

	}


	// Complexity: O(1)
	std::size_t fa::Automaton::countStates() const{
		return states.size();
	}


	// Complexity: O(log n)
	void fa::Automaton::setStateInitial(int state){
		initialStates.insert(state);
		// std::cout << "Set initial state: " << state << "!!" <<std::endl;
	}


	// Complexity: O(log n)
	bool fa::Automaton::isStateInitial(int state) const{
		std::set<int>::iterator iter;
		iter=initialStates.find(state);
		return iter!=initialStates.end();
	}


	// Complexity: O(log n)
	void fa::Automaton::setStateFinal(int state){
		finalStates.insert(state);
		// std::cout << "Set final state: " << state << "!!" <<std::endl;

	}

	// Complexity: O(log n)
	bool fa::Automaton::isStateFinal(int state) const{
		std::set<int>::iterator iter;
		iter=finalStates.find(state);
		return iter!=finalStates.end();
	}
	

        
    bool fa::trans::operator<(const trans& other) const {
        return std::tie(from, to, alpha) < std::tie(other.from, other.to, other.alpha);
    }


    // Complexity: O
	void fa::Automaton::addTransition(int from, char alpha, int to){
		alphabets.insert(alpha);
		if(!hasTransition(from, alpha, to)){
        	struct trans new_transition;
        	new_transition.from = from;
        	new_transition.alpha = alpha;
        	new_transition.to = to;
        	transitions.insert(new_transition);
		}
	}


	// Complexity: 
	void fa::Automaton::removeTransition(int from, char alpha, int to){
        trans trans_to_delete;
        trans_to_delete.from = from;
        trans_to_delete.to = to;
        trans_to_delete.from = from;
 		transitions.erase(trans_to_delete);
	}



	bool fa::Automaton::hasTransition(int from, char alpha, int to) const{
            trans trans_to_search;
            trans_to_search.from = from;
            trans_to_search.to = to;
            trans_to_search.from = from;
            return transitions.find(trans_to_search) != transitions.end() ;
            // if (transitions.find(trans_to_search) != transitions.end()) {
            //     return true;
            // }
            // return false;
	}


	std::size_t fa::Automaton::countTransitions() const{
		return transitions.size();
	}


	// void fa::Automaton::addAlphabet(char alpha){
	// 	alphabets.insert(alpha);
	// 	// std::cout << "Après insertion de l'alphabet " << alpha << ", l'alphabets possède " << alphabets.size() << " caractere(s)." << std::endl;
	// }

	// void fa::Automaton::removeAlphabet(char alpha){
	// 	alphabets.erase(alpha);
	// 	// std::cout << "Après suppression de l'alphabet " << alpha << ", l'alphabets possède " << alphabets.size() << " caractere(s)." << std::endl;
	// }

	// bool fa::Automaton::hasAlphabet(char alpha){
	// 	std::set<char>::iterator iter;
	// 	iter=alphabets.find(alpha);
	// 	if(iter!=alphabets.end()){
	// 		return true;
	// 	}
	// 	else{
	// 		return false;
	// 	}
	// }


	std::size_t fa::Automaton::getAlphabetSize() const{
		return alphabets.size();
	}



	void fa::Automaton::prettyPrint(std::ostream& os) const{
		os << "Initial states: " << std::endl;
		std::set<int>::iterator iter_init_state;
		iter_init_state=initialStates.begin();
		while(iter_init_state != initialStates.end()){
			os << " " << *iter_init_state << " ";
			iter_init_state++;
		}
		os << std::endl;

		os << "Final states: " << std::endl;
		std::set<int>::iterator iter_final_state;
		iter_final_state=finalStates.begin();
		while(iter_final_state != finalStates.end()){
			os << " " << *iter_final_state << " ";
			iter_final_state++;
		}
		os << std::endl;

		os << "Transitions: " << std::endl;
		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		while(iter_all_state != states.end()){
			os << "	For state " << *iter_all_state << ":" <<std::endl;
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				os << "		For letter  " << *iter_alpha << " : ";
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						os<< (*iter_trans).to <<" ";
					}
					iter_trans++;
				}
				os<< std::endl;
				iter_alpha++;
			}
			iter_all_state++;
		}
	}




//  Commande:            dot diagramme.dot -T png -o diagramme.png
	void fa::Automaton::dotPrint(std::ostream& os) const{
		os << "digraph automaton {" << std::endl ;
		os << "size = \"8.5, 11\";" << std::endl ;
		os << "fontsize = 10;" << std::endl ;

		std::set<int>::iterator iter_init_state;
		iter_init_state=initialStates.begin();
		while(iter_init_state != initialStates.end()){
			os << *iter_init_state << "[ style = filled, color=lightgrey ];" << std::endl;
			iter_init_state++;
		}
		

		std::set<int>::iterator iter_final_state;
		iter_final_state=finalStates.begin();
		while(iter_final_state != finalStates.end()){
			os <<  *iter_final_state << "[ shape = doublecircle ];" << std::endl;
			iter_final_state++;
		}

		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		while(iter_all_state != states.end()){
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						os<< (*iter_trans).from << "->" <<  (*iter_trans).to << " [ label = \"" << (*iter_trans).alpha << "\" ]; " <<std::endl;
					}
					iter_trans++;
				}
				os<< std::endl;
				iter_alpha++;
			}
			iter_all_state++;
		}
		os << "}" << std::endl ;

	}




	bool fa::Automaton::isDeterministic() const{
		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		int count_to=0;
		while(iter_all_state != states.end()){
			if(!isStateFinal(*iter_all_state)){
				std::set<char>::iterator iter_alpha=alphabets.begin();
				while(iter_alpha != alphabets.end()){
					std::set<struct trans>::iterator iter_trans;
					iter_trans = transitions.begin();
					while(iter_trans != transitions.end()){
						if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
							count_to++;
						}
						iter_trans++;
					}
					if(count_to > 1){
						return false;
					}
					iter_alpha++;
					count_to=0;
				}
				iter_all_state++;
			}
		}
		return true;
	}

	bool fa::Automaton::isComplete() const{
		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		int count_to=0;
		while(iter_all_state != states.end()){
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						count_to++;
					}
					iter_trans++;
				}
				if(count_to == 0 ){
					return false;
				}
				iter_alpha++;
				count_to=0;
			}
			iter_all_state++;
		}
		return true;
	}



	void fa::Automaton::makeComplete(){
		int garbage_state=-1;
		while(garbage_state==-1){
			int temp=getTheBiggestState()+1;
			if(!hasState(temp)){
				garbage_state=temp;
			}
		}

		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		int count_to=0;
		while(iter_all_state != states.end()){
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						count_to++;
					}
					iter_trans++;
				}
				if(count_to ==0){
					addTransition(*iter_all_state, *iter_alpha, garbage_state);
				}
				iter_alpha++;
				count_to=0;
			}
			iter_all_state++;
		}


	}


	// Complexity: 
	void fa::Automaton::makeComplement(){
		std::set<int>::iterator iter=states.begin();
		while(iter != states.end()){
			if(isStateFinal(*iter)){
				finalStates.erase(*iter);
			}
			else{
				finalStates.insert(*iter);
			}
			iter++ ;
		}
	}


	// Comolexity: 
	bool fa::Automaton::isLanguageEmpty() const{
		return false;
	}





	Automaton fa::Automaton::createProduct(const Automaton& lhs, const Automaton& rhs){
		fa::Automaton new_automaton;
		std::set<int> lhs_init=lhs.getInitialStates();
		std::set<int> rhs_init=rhs.getInitialStates();
		std::set<int>::iterator left_initStates = lhs_init.begin();
		std::set<int>::iterator right_initStates = rhs_init.begin();
		std::set<int>::iterator left_States = lhs.getStates().begin();
		std::set<int>::iterator right_States = rhs.getStates().begin();
		std::map<int,std::map<char,std::set<int>>> transitions_left = lhs.getTransitions();
		std::map<int,std::map<char,std::set<int>>> transitions_right = rhs.getTransitions();

		std::size_t n2 = rhs.getTheBiggestState() + 1;

		//create init states
		while(left_initStates != lhs_init.end()){
			while(right_initStates != rhs_init.end()){
				new_automaton.setStateInitial((*left_initStates * n2) + (*right_initStates));
				right_initStates++;
			}
			left_initStates++;
		}

		//create transitions
		new_automaton.alphabets.insert(lhs.alphabets.begin() , lhs.alphabets.end());
		new_automaton.alphabets.insert(rhs.alphabets.begin() , rhs.alphabets.end());
		std::set<char>::iterator iter_alpha=new_automaton.alphabets.begin();
		std::set<int>::iterator iter_new_initStates=new_automaton.initialStates.begin();
		while(iter_new_initStates!= new_automaton.initialStates.end()){
			while(iter_alpha != new_automaton.alphabets.end()){
				std::int s1 = *iter_new_initStates/n2;
				std::int s2 = *iter_new_initStates%n2;
				std::set<int>::iterator for_s1 = transitions.find(s1).find(*iter_alpha).begin();
				std::set<int>::iterator for_s2 = transitions.find(s2).find(*iter_alpha).begin();
				while()

			}
		}

		






		// "<Produit> de deux automates"
		// new_automaton.initialStates.insert(lhs.initialStates.begin() , lhs.initialStates.end());
		// new_automaton.finalStates.insert(rhs.finalStates.begin() , rhs.finalStates.end());
		// new_automaton.alphabets.insert(lhs.alphabets.begin() , lhs.alphabets.end());
		// new_automaton.alphabets.insert(rhs.alphabets.begin() , rhs.alphabets.end());
		// new_automaton.states.insert(lhs.states.begin(),lhs.states.end());
		// new_automaton.states.insert(rhs.states.begin(),rhs.states.end());
		// new_automaton.transitions.insert(lhs.transitions.begin() , lhs.transitions.end());
		// new_automaton.transitions.insert(rhs.transitions.begin() , rhs.transitions.end());
		// std::set<int>::iterator left_final= lhs.finalStates.begin();
		// std::set<int>::iterator	right_init;
		// while(left_final!=lhs.finalStates.end()){
		// 	right_init=rhs.initialStates.begin();
		// 	while(right_init!=rhs.initialStates.end()){
		// 		new_automaton.addTransition(*left_final, '^', *right_init);
		// 		right_init++;
		// 	}
		// 	left_final++;
		// }
		// return new_automaton;

		// new_automaton.addTransition(101,'𝛜',102)
	}

	bool fa::Automaton::hasEmptyIntersectionWith(const Automaton& other) const{
		return false;
	}



	std::set<int> fa::Automaton::getStates() const{
		return states;
	}

    std::set<int> fa::Automaton::getInitialStates() const{
    	return initialStates;
    }

    std::set<int> fa::Automaton::getFinalStates() const{
    	return finalStates;
    }

    std::set<struct trans> fa::Automaton::getTransitions() const{
    	return transitions;
    }

    std::set<char> fa::Automaton::getAlphabets() const{
    	return alphabets;
    }

    int fa::Automaton::getTheBiggestState() const{
    	std::set<int>::iterator first = states.begin();
    	std::size_t tmp=countStates();
    	for(size_t i=1; i<tmp; i++){
    		first++;
    	}
    	return *first;
    }





}
