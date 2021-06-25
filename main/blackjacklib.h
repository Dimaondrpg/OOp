#ifndef BLACJACK_H
#define BLACJACK_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Card
{
protected:
    enum suit{
        CLUBS,
        DIMAONDS,
        HEARST,
        SPADES};
    enum value{
        cA = 11, c2 = 2,
        c3 = 3, c4 = 4,
        c5 = 5, c6 = 6,
        c7 = 7, c8 = 8,
        c9 = 9, c10 = 10,
        cJ = 10, cQ = 10, cK = 10};
    value m_v;
    suit m_s; 
    bool m_position;
public:
    Card(value v, suit s,bool p) : m_v(v), m_s(s),m_position(p){}
bool Flip() {
    return m_position = !m_position;
}
    
    Card& operator=(const Card& right) {
        if (this == &right) {
            return *this;
        }
        m_v = right.m_v;
        return *this;
    }

int GetValue() const{
    return m_v;
}

	friend ostream& operator<< (ostream &out, const Card &card);
};

ostream& operator<< (ostream &out, const Card &card)
{
	if (card.m_position) {
    out << "Card suit: " << card.m_s << " Card value: " << card.m_v << "\n";
	} else {
		out << "Card suit: X Card value: X" << "\n";
	}

    return out;
}


class Hand
{
protected:
    vector<Card*> hand;
public:
    Hand() { hand.reserve(7);}
    ~Hand() {Clear();};

    void Add(Card* card) {
        hand.push_back(card);
    }

    void Clear() {
        vector<Card*>::iterator iter = hand.begin();
    for (iter =hand.begin(); iter != hand.end(); ++iter)
    {
        delete *iter;
        *iter = 0;
    }
    hand.clear();
;
    }

    int GetValue() {
        int sum = 0;
        for(int i = 0; i < hand.size(); ++i) {
            if(sum >= 21 && hand[i]->GetValue() == 11){
                sum =+ 1;
            } else {
                sum =+ hand[i]->GetValue();
            }
        }    
        return sum;
    }



    void PrintCards(){
    for (Card* n : hand) {
        cout << n << ", ";
    }
}
    
};

class GenericPlayer: public Hand
{
protected:
	string name;
public:
	GenericPlayer(string n) {name = n;}
	~GenericPlayer();

	virtual void IsHitting() const {
		cout << "You  can take a card" << endl;
	}

	bool IsBoosted()  {
		if (GetValue() < 21) {
			return false;
		}
	}

	void Bust() {
		if(IsBoosted()) {
			cout << name << "is busted" << endl;

		}
	}

	friend ostream& operator<< (ostream &out, GenericPlayer &gp);
	
};

ostream& operator<< (ostream &out, GenericPlayer &gp)
{
    out << "Player: " << gp.name << " Cards: "; 
    gp.PrintCards();
    out << "Value: " << gp.GetValue() << endl;


    return out;
}

class Player : public GenericPlayer
{
public:
	Player(string nn) : GenericPlayer(nn){}
	~Player();

	bool IsHitting() {
		string answer;
		cout << "Do you want to take a card?";
		cin >> answer;
		if (answer == "yes"){
			return true;
		} else {return false;}
	}

	void Win() {
		cout << name << " win!" << endl;
	}

	void Lose() {
		cout << name << " lose" << endl;
	}

	void Push() {
		cout << name << " played a draw" << endl;
	}
	
};

class House : public GenericPlayer
{
public:
	House(string nn = "House") : GenericPlayer(nn){}
	~House();

	bool IsHitting() {
		cout << "Is dealer tackes a card?";
		if (GetValue() < 16){
			return true;
		} else {return false;}
	}

	void FlipFirstCard(){
		hand[1]->Flip();
	}
	
};

#endif