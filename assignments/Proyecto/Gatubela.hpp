#pragma once
#include "Combatiente.hpp"

class Gatubela : public Combatiente {
public:
    Gatubela(); //constructor por defecto
    Gatubela(int v, int a, int n, float b, int g); //constructor con parametros
    //Getters
    float getBloqueo() const;
    int getGarras() const;
    //Setters
    void setBloqueo (float b);
    void setGarras (int g);
    //metodos sobrescritos
    virtual bool estaVivo(); //metodo sobrescrito
    void recibeAtaque(int ptosAtaque);
    virtual void atacar(Combatiente &objetivo); //sobreescrito
    void imprimir() const;
private:
    float bloqueo;
    int garras;
    int contadorAtaques; // para contar los ataques realizados, para usar garras
};