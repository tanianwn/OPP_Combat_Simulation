#pragma once
#include "Combatiente.hpp"

class HiedraVenenosa : public Combatiente {
public:
    HiedraVenenosa(); //constructor por default
    HiedraVenenosa(int v, int a, int n, int t); //constructor con paraetros
    //getters
    int getToxikinesis() const;
    //setters
    void setToxikinesis(int t);
    //metodos sobrescritos
    virtual bool estaVivo(); //metodo sobrescrito
    void recibeAtaque(int ptosAtaque);
    void atacar(Combatiente &objetivo);
    void imprimir() const;
private:
    int toxikinesis;
};
