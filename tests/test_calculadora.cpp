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

TEST(test_calculadora, programa_1_push_write){
    Programa p;
    p.agregarInstruccion("a", Instruccion(PUSH, 40));
    p.agregarInstruccion("a", Instruccion(WRITE, "x"));
    p.agregarInstruccion("a", Instruccion(JUMP, "fin"));

    Calculadora c(p);
    c.ejecutar("a");
    EXPECT_EQ(c.valorVariable("x"), 40);
}

TEST(test_calculadora, programa_read_add){
    Programa p;
    p.agregarInstruccion("a", Instruccion(PUSH, 21));
    p.agregarInstruccion("a", Instruccion(WRITE, "x"));
    p.agregarInstruccion("a", Instruccion(READ, "x"));
    p.agregarInstruccion("a", Instruccion(READ, "x"));
    p.agregarInstruccion("a", Instruccion(ADD));
    p.agregarInstruccion("a", Instruccion(WRITE, "y"));

    Calculadora c(p);
    c.ejecutar("a");
    EXPECT_EQ(c.valorVariable("x"), 21);
    EXPECT_EQ(c.valorVariable("y"), 42);
}

TEST(test_calculadora, programa_jump){
    Programa p;
    p.agregarInstruccion("a", Instruccion(PUSH, 15));
    p.agregarInstruccion("a", Instruccion(PUSH, 6));
    p.agregarInstruccion("a", Instruccion(ADD));
    p.agregarInstruccion("a", Instruccion(JUMP, "b"));
    p.agregarInstruccion("b", Instruccion(WRITE, "x"));
    p.agregarInstruccion("b", Instruccion(READ, "x"));
    p.agregarInstruccion("b", Instruccion(READ, "x"));
    p.agregarInstruccion("b", Instruccion(ADD));
    p.agregarInstruccion("b", Instruccion(WRITE, "y"));
    p.agregarInstruccion("b", Instruccion(JUMP, "fin"));

    Calculadora c(p);
    c.ejecutar("a");
    EXPECT_EQ(c.valorVariable("x"), 21);
    EXPECT_EQ(c.valorVariable("y"), 42);

}
