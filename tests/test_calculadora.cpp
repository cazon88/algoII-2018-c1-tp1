#include "gtest/gtest.h"

#include "../src/Instruccion.h"
#include "../src/Programa.h"
#include "../src/Calculadora.h"

TEST(test_calculadora, variables) {
    Programa p;
    Calculadora c(p);
    EXPECT_EQ(c.valorVariable("x"), 0);
    c.asignarVariable("x", 5);
    EXPECT_EQ(c.valorVariable("x"), 5);
    c.asignarVariable("x", 10);
    EXPECT_EQ(c.valorVariable("x"), 10);
}

//READ & WRITE
TEST(test_calculadora, programa_read_write){
    Programa p;
    p.agregarInstruccion("r", Instruccion(WRITE, "n"));
    p.agregarInstruccion("r", Instruccion(READ, "x"));
    p.agregarInstruccion("r", Instruccion(WRITE, "y"));
    p.agregarInstruccion("r", Instruccion(READ, "z"));
    p.agregarInstruccion("r", Instruccion(WRITE, "m"));



    Calculadora c(p);
    c.asignarVariable("x", 3);
    c.asignarVariable("m", 20);
    c.ejecutar("r");

    //Write con pila vacia
    EXPECT_EQ(c.valorVariable("n"), 0);
    //Leyo X y creo la variable Y,dado que no existia, con el valor de X
    EXPECT_EQ(c.valorVariable("y"), 3);
    //Z inexistente => leyó 0 y le asigno a una variable M, que ya existia, el valor 0.
    EXPECT_EQ(c.valorVariable("z"), 0);
}

//PUSH
TEST(test_calculadora, programa_push){
    Programa p;
    p.agregarInstruccion("r", Instruccion(PUSH, 40));
    p.agregarInstruccion("r", Instruccion(WRITE, "x"));
    p.agregarInstruccion("r", Instruccion(WRITE, "y"));
    p.agregarInstruccion("r", Instruccion(PUSH, 10));
    p.agregarInstruccion("r", Instruccion(PUSH, 3));
    p.agregarInstruccion("r", Instruccion(WRITE, "z"));
    Calculadora c(p);
    c.ejecutar("r");

    //Se pusheo en la pila el valor 40 y se lo asigno
    //a la variable X.
    EXPECT_EQ(c.valorVariable("x"), 40);
    //Se vacio la pila?
    EXPECT_EQ(c.valorVariable("y"), 0);
    //El tope es lo ultimo que agregue
    EXPECT_EQ(c.valorVariable("z"), 3);
}

//ADD
TEST(test_calculadora, programa_add){
    Programa p;
    p.agregarInstruccion("r", Instruccion(PUSH, 5));
    p.agregarInstruccion("r", Instruccion(PUSH, 10));
    p.agregarInstruccion("r", Instruccion(PUSH, 32));
    p.agregarInstruccion("r", Instruccion(ADD));
    p.agregarInstruccion("r", Instruccion(WRITE, "x"));
    p.agregarInstruccion("r", Instruccion(ADD));
    p.agregarInstruccion("r", Instruccion(WRITE, "y"));
    p.agregarInstruccion("r", Instruccion(ADD));
    p.agregarInstruccion("r", Instruccion(WRITE, "z"));

    Calculadora c(p);
    c.ejecutar("r");
    // Add de 10 + 32
    EXPECT_EQ(c.valorVariable("x"), 42);
    // ADD con solo un valor en la pila, 5
    EXPECT_EQ(c.valorVariable("y"), 5);
    // ADD sin valores en la pila
    EXPECT_EQ(c.valorVariable("z"), 0);
}

//SUB

TEST(test_calculadora, programa_sub){
    Programa p;
    p.agregarInstruccion("r", Instruccion(PUSH, 11));
    p.agregarInstruccion("r", Instruccion(PUSH, 99));
    p.agregarInstruccion("r", Instruccion(PUSH, 57));
    p.agregarInstruccion("r", Instruccion(SUB));
    p.agregarInstruccion("r", Instruccion(WRITE, "x"));
    p.agregarInstruccion("r", Instruccion(SUB));
    p.agregarInstruccion("r", Instruccion(WRITE, "y"));
    p.agregarInstruccion("r", Instruccion(SUB));
    p.agregarInstruccion("r", Instruccion(WRITE, "z"));

    Calculadora c(p);
    c.ejecutar("r");
    // SUB de 99-57
    EXPECT_EQ(c.valorVariable("x"), 42);
    // SUB con solo un valor en la pila, 11.
    EXPECT_EQ(c.valorVariable("y"), -11);
    // SUB sin valores en la pila
    EXPECT_EQ(c.valorVariable("z"), 0);
}

//MUL
TEST(test_calculadora, programa_mul){
    Programa p;
    p.agregarInstruccion("r", Instruccion(PUSH, 5));
    p.agregarInstruccion("r", Instruccion(PUSH, 6));
    p.agregarInstruccion("r", Instruccion(PUSH, 7));
    p.agregarInstruccion("r", Instruccion(MUL));
    p.agregarInstruccion("r", Instruccion(WRITE, "x"));
    p.agregarInstruccion("r", Instruccion(MUL));
    p.agregarInstruccion("r", Instruccion(WRITE, "y"));
    p.agregarInstruccion("r", Instruccion(MUL));
    p.agregarInstruccion("r", Instruccion(WRITE, "z"));

    Calculadora c(p);
    c.ejecutar("r");
    // MUL de 7*6
    EXPECT_EQ(c.valorVariable("x"), 42);
    // MUL con solo un valor en la pila, 5
    EXPECT_EQ(c.valorVariable("y"), 0);
    // MUL sin valores en la pila
    EXPECT_EQ(c.valorVariable("z"), 0);
}

//JUMP
TEST(test_calculadora, programa_jump){
    Programa p;

    //Rutina r1
    p.agregarInstruccion("r1", Instruccion(PUSH, 3));
    p.agregarInstruccion("r1", Instruccion(PUSH, 5));
    p.agregarInstruccion("r1", Instruccion(ADD));
    p.agregarInstruccion("r1", Instruccion(JUMP,"r2"));
    p.agregarInstruccion("r1", Instruccion(WRITE,"x"));


    //Rutina r2
    p.agregarInstruccion("r2", Instruccion(PUSH, 2));
    p.agregarInstruccion("r2", Instruccion(ADD));
    p.agregarInstruccion("r2", Instruccion(WRITE,"y"));
        //Test de condicion de corte del programa
    p.agregarInstruccion("r2", Instruccion(JUMP,"fin"));
    p.agregarInstruccion("r2", Instruccion(WRITE,"x"));


    Calculadora c(p);
    c.asignarVariable("x", 1);
    c.ejecutar("r1");

    // Se espera que dps del jump no se continue ejecutando la rutina
    EXPECT_EQ(c.valorVariable("x"), 1);
    //Se continuo ejecutando la rutina r2 por el jum en r1
    EXPECT_EQ(c.valorVariable("y"), 10);

}

//JUMPZ
TEST(test_calculadora, programa_jumpz){
    Programa p;

    //Rutina r1
    p.agregarInstruccion("r1", Instruccion(PUSH, 3));
    p.agregarInstruccion("r1", Instruccion(PUSH, 5));
    p.agregarInstruccion("r1", Instruccion(ADD));
    p.agregarInstruccion("r1", Instruccion(JUMPZ,"r2"));
    p.agregarInstruccion("r1", Instruccion(WRITE,"x"));
    p.agregarInstruccion("r1", Instruccion(MUL));
    //test - Pila con valor en 0
    p.agregarInstruccion("r1", Instruccion(JUMPZ,"r3"));


    //Rutina r2
    p.agregarInstruccion("r2", Instruccion(PUSH, 2));
    p.agregarInstruccion("r2", Instruccion(ADD));
    p.agregarInstruccion("r2", Instruccion(WRITE,"y"));

    //Rutina r3
    p.agregarInstruccion("r3", Instruccion(PUSH, 3));
    p.agregarInstruccion("r3", Instruccion(ADD));
    p.agregarInstruccion("r3", Instruccion(WRITE,"z"));
    // test - Pila vacia
    p.agregarInstruccion("r3", Instruccion(JUMPZ,"fin"));
    p.agregarInstruccion("r3", Instruccion(PUSH, 5));
    p.agregarInstruccion("r3", Instruccion(WRITE,"m"));


    Calculadora c(p);
    c.asignarVariable("x", 1);
    c.asignarVariable("m", 1);
    c.ejecutar("r1");

    // No se debe ejecutar el JUMPZ
    EXPECT_EQ(c.valorVariable("x"), 8);
    // No salto a la rutina r2, por eso y = 0
    EXPECT_EQ(c.valorVariable("y"), 0);
    //Salto a la rutina
    EXPECT_EQ(c.valorVariable("z"), 3);
    // Salto a fin y no continuo ejecutando
    EXPECT_EQ(c.valorVariable("m"), 1);

}