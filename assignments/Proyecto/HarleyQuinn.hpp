#pragma once
#include "Combatiente.hpp"


class HarleyQuinn : public Combatiente{
public:
    HarleyQuinn();
    HarleyQuinn(int v, int a, int n, int f, bool it);
    //getters
    int getFuerza() const; //nueva
    bool getInmunidadToxinas() const; //nueva
    //setters
    void setFuerza(int f);
    void setInmunidadToxinas(bool it);
    //metodos
    virtual bool estaVivo(); //metodo sobrescrito
    void recibeAtaque(int ptosAtaque);  //sobrescribir
    virtual void atacar(Combatiente &objetivo);  // sobrescribir
    void imprimir() const; // sobrescribir

private:
    int fuerza;
    bool inmunidadToxinas;
};

