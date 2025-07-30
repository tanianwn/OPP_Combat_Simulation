// Crear el archivo header de la clase Personaje, no olvides las guardas o el pragma.

#pragma once // previene múltiples definiciones como las guardas
#include <string>
#include <iostream>


class Combatiente
{
    public:
        Combatiente(); //por defecto
        Combatiente(int v, int a, int n); //con parametros 
        virtual ~Combatiente(); //destructor
        //getters
        int getVida() const;
        int getSalud() const;
        int getAtaque() const;
        int getNivel() const;
        //setters
        void setVida(int v);
        void setSalud(int s);
        void setAtaque(int a);
        void setNivel(int n);
        //Metodos
        virtual bool estaVivo()= 0; //metodo virtual puro
        int calcularPorcentajeSalud() const; //calcular la salud    
        void imprimirBarraVida() const; //imprimir   barra de vida
        virtual void recibeAtaque(int ptosAtaque); //para recibir el ataque implementado polimorficamente 
        virtual void atacar(Combatiente &objetivo) = 0; //cambio en ataque a virtual puro  
        virtual void imprimir() const; //imprimir características del combatiente y la barra de vida implementado polimorficamente 
        //sobrecarga del operador de salida como friend
        friend std::ostream& operator<<(std::ostream& os, const Combatiente& combatiente);
    private:
        int vida;   // maxima cantidad de puntos de vida
        int salud;  // indica los puntos de vida actuales, se inicia con el valor de vida
        int ataque; // puntos de ataque
        int nivel;  // nivel del combatiente
};