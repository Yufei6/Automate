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
            trans_to_search.alpha = alpha;
            return transitions.find(trans_to_search) != transitions.end() ;
	}


	std::size_t fa::Automaton::countTransitions() const{
		return transitions.size();
	}





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



//********************************************* TP4 ***************************************************
	Automaton fa::Automaton::createProduct(const Automaton& lhs, const Automaton& rhs){
		fa::Automaton new_automaton;
		std::set<int> lhs_init=lhs.getInitialStates();
		std::set<int> rhs_init=rhs.getInitialStates();
		std::set<int>::iterator left_initStates = lhs_init.begin();
		std::set<int>::iterator right_initStates = rhs_init.begin();



		std::size_t n2 = rhs.getTheBiggestState() + 1;

		//create init states
		while(left_initStates != lhs_init.end()){
			while(right_initStates != rhs_init.end()){
				new_automaton.setStateInitial((*left_initStates * n2) + (*right_initStates));
				new_automaton.addState((*left_initStates * n2) + (*right_initStates));
				right_initStates++;
			}
			left_initStates++;
		}

		//create les alphabets communes
		std::set<char> s3 ;
   		std::set<char>::iterator iter = s3.begin() ;
   		set_intersection(lhs.alphabets.begin(),lhs.alphabets.end(),rhs.alphabets.begin(),rhs.alphabets.end(),inserter(s3,iter));
   		new_automaton.alphabets=s3;
		// create transitions
		std::set<int>::iterator iter_new_States=new_automaton.states.begin();
		while(iter_new_States!= new_automaton.states.end()){
			std::set<char>::iterator iter_alpha=new_automaton.alphabets.begin();
			while(iter_alpha != new_automaton.alphabets.end()){
				int s1 = *iter_new_States/n2;
				int s2 = *iter_new_States%n2;
				int res_l = lhs.getToWithFromAndAlpha(s1,*iter_alpha);
				int res_r = rhs.getToWithFromAndAlpha(s2,*iter_alpha);

				if( res_l ==0 || res_r ==0){
					iter_alpha++;
				}
				else{
					int new_state = (res_l * n2) + res_r;
					if (!new_automaton.hasState(new_state)){
						new_automaton.addState(new_state);
						new_automaton.addTransition(*iter_new_States, *iter_alpha, new_state);
						if(lhs.isStateFinal(res_l) && rhs.isStateFinal(res_r)){
							new_automaton.setStateFinal(new_state);
						}
					}
					new_automaton.addTransition(*iter_new_States, *iter_alpha, new_state);
					iter_alpha++;
				}
			}
			iter_new_States++;
		}
		return new_automaton;
	}

	bool fa::Automaton::hasEmptyIntersectionWith(const Automaton& other) const{
		fa::Automaton new_automate = createProduct(*this,other);
		return new_automate.getAlphabetSize()==0 || new_automate.countTransitions() ==0 || new_automate.countStates() ==0;
	}


  //********************************************** fin de TP4 ***********************************




  //*************************************   tp6   ***********************************
  Automaton fa::Automaton::createMinimalMoore(const Automaton& automaton){
    fa::Automaton tmp_automate;
    tmp_automate = automaton;
    if(!tmp_automate.isComplete()){
      tmp_automate.makeComplete();
    }
    // if(!tmp_automate.isDeterministic()){
    //   tmp_automate.Deterministic();
    // }

    fa::Automaton new_automate;
    std::map<int,int> map0;
    std::set<int> states = automaton.getStates();
    std::set<int>::iterator states_iter = states.begin();
    while(states_iter != states.end()){
      if(automaton.isStateFinal(*states_iter)){
        map0.insert(std::pair<int,int>(*states_iter,2));
      }
      else{
        map0.insert(std::pair<int,int>(*states_iter,1));
      }
    }



    return new_automate;
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

    int fa::Automaton::getToWithFromAndAlpha(int from, char alpha) const{
    	std::set<int>::iterator iter_to = states.begin();
    	while(iter_to != states.end()){
    		struct trans try_transition;
    		try_transition.from = from;
    		try_transition.alpha = alpha;
    		try_transition.to = *iter_to;
    		if(transitions.find(try_transition) != transitions.end()){
    			return *iter_to;
    		}
    		iter_to ++;
    	}
    	return 0;

    }




    std::set<int> fa::Automaton::from(int state) {
        std::set<int> to_set;
        std::set<struct trans>::iterator trans_iter = transitions.begin();
        while(trans_iter != transitions.end()){
            struct trans transition = *trans_iter;
            if (transition.from == state) {
                to_set.insert(transition.to);
            }
            trans_iter++;
        }
        return to_set;
    }

    bool fa::Automaton::depthFirstSearch(std::set<int> *visited, int current) {
        if ((*visited).find(current) != (*visited).end()) {
            return false;
        }
        std::set<int> destinations = from(current);
        // std::cout << "From " << current << ": ";
        // for (std::set<int>::iterator it = destinations.begin(); it != destinations.end(); it++) {
        //     std::cout << *it << " ";
        // }
        // std::cout << std::endl;
        (*visited).insert(current);
        bool path_found = false;
        if ( ! destinations.empty() ) {
            std::set<int>::iterator dest_iter = destinations.begin();
            while (dest_iter != destinations.end()) {
                path_found = depthFirstSearch(visited, *dest_iter) || path_found;
                dest_iter++;
            }
        }
        if (finalStates.find(current) != finalStates.end()) {
            return true;
        }
        return path_found;
    }

    bool fa::Automaton::isLanguageEmpty() {   // ! const
        std::set<int> visited_states;
        bool path_found = false;
        std::set<int>::iterator init_iter = initialStates.begin();
        while (init_iter != initialStates.end() && !path_found) {
            path_found = depthFirstSearch(&visited_states, *init_iter);
            init_iter++;
        }
        return !path_found;
    }

    void fa::Automaton::removeNonAccessibleStates() {
        std::set<int> visited_states;
        std::cout << std::endl;
        std::set<int>::iterator init_iter = initialStates.begin();
        while (init_iter != initialStates.end()) {
            depthFirstSearch(&visited_states, *init_iter);
            init_iter++;
        }
        for (std::set<int>::iterator states_iter = states.begin(); states_iter != states.end(); states_iter++) {
            if (visited_states.find(*states_iter) == visited_states.end()) {
                removeState(*states_iter);
                states_iter--;   //Pour éviter le saut d'indice lorsqu'un élément du set est supprimé
            }
        }
    }

    void fa::Automaton::removeNonCoAccessibleStates() {

    }

    void fa::Automaton::coAccessibleStatesFinder(std::set<int> *states, std::set<int> *co_acc_states, std::set<int> *non_co_acc_state, std::set<int> current_path, int current_position) {

    }
}
