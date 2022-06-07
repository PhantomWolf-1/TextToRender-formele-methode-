#pragma once



class State;

class Transition {

private:
	std::shared_ptr<State> from;
	//State* from;
	std::string keyword;
	std::shared_ptr<State> to;
	//State* to;

public:
	Transition(std::shared_ptr<State> fr, std::string kw, std::shared_ptr<State> t) : from(fr), keyword(kw), to(t) {};
	~Transition() { };

	State* GetFromState() {
		return from.get();
	};

	std::string GetKeyword() {
		return keyword;
	}

	State* GetToState() {
		return to.get();
	};
};


class State {

private:
	std::string stateName;
	std::vector<std::shared_ptr<Transition>> transitions;
	bool isStart;
	bool isFinal;


public:
	State(std::string name) : stateName(name) { isStart = false; isFinal = false; };
	//~State();

	bool isDeterministic(const std::vector<std::string> alphabet) {
		std::vector<std::string> tmpAlphabet = alphabet;
		int transitionCount = 0;
		for (int i = 0; i < transitions.size(); i++) {
			for (int j = 0; j < tmpAlphabet.size(); j++) {
				if (transitions[i]->GetKeyword() == tmpAlphabet[j]) {
					transitionCount++;
					tmpAlphabet.erase(std::remove(tmpAlphabet.begin(), tmpAlphabet.end(), tmpAlphabet[j]), tmpAlphabet.end());
				}
			}
		}


		if (transitionCount == alphabet.size()) {
			return true;
		}

		return false;
	};


	void PrintState() {
		std::cout << "state: " << stateName << std::endl;
		std::cout << "Transitions: "  << std::endl;
		for (int i = 0; i < transitions.size(); i++) {
			std::cout << "from: " << transitions.at(i)->GetFromState()->stateName << " ----- " << transitions.at(i)->GetKeyword() << " -----> " << transitions.at(i)->GetToState()->stateName << std::endl;
		}

		std::cout << std::endl;
	};

	void AddTransition(std::shared_ptr<Transition> t) {
		transitions.push_back(t);
	}

	std::vector<std::shared_ptr<Transition>> GetTransitions() {
		return transitions;
	}

	bool GetIsStart() {
		return isStart;
	};

	bool GetIsFinal() {
		return isFinal;
	}
	
	void SetIsStart(bool value) {
		isStart = value;
	};

	void SetIsFinal(bool value) {
		isFinal = value;
	}
};
