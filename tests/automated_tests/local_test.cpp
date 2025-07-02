#include "lib/include/munit.hpp"
#include "Local.hpp"
#include <cmath>

// Teste do construtor default (sem nenhum parâmetro);
static MunitResult test_local_default_ctor(const MunitParameter params[], void* data) {
    Local l;
    munit_assert_string_equal(l.getNome().c_str(), "");
    munit_assert_float(l.getX(), ==, 0.0f);
    munit_assert_float(l.getY(), ==, 0.0f);
    // Esperado: nome="", x=0.0, y=0.0
    return MUNIT_OK;
}

// Teste do construtor com parâmetros (sobrecarga);
static MunitResult test_local_param_ctor(const MunitParameter params[], void* data) {
    Local l("A", 1.5f, 2.5f);
    munit_assert_string_equal(l.getNome().c_str(), "A");
    munit_assert_float(l.getX(), ==, 1.5f);
    munit_assert_float(l.getY(), ==, 2.5f);
    // Esperado: nome="A", x=1.5, y=2.5
    return MUNIT_OK;
}

// Teste dos setters;
static MunitResult test_local_setters(const MunitParameter params[], void* data) {
    Local l;
    l.setNome("B");
    l.setCoordenadas(3.0f, 4.0f);
    munit_assert_string_equal(l.getNome().c_str(), "B");
    munit_assert_float(l.getX(), ==, 3.0f);
    munit_assert_float(l.getY(), ==, 4.0f);
    // Esperado: nome="B", x=3.0, y=4.0
    return MUNIT_OK;
}

// Teste da função calcularDistanciaEntreLocais;
static MunitResult test_local_distancia(const MunitParameter params[], void* data) {
    Local l1("A", 0.0f, 0.0f);
    Local l2("B", 3.0f, 4.0f);
    float d = calcularDistanciaEntreLocais(l1, l2);
    munit_assert_float(d, ==, 5.0f);
    // Esperado: distancia=5.0
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char*) "/default_ctor", test_local_default_ctor, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/param_ctor",   test_local_param_ctor,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/setters",      test_local_setters,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/distancia",    test_local_distancia,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    (char*) "/local",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}

// Esperado ao rodar todos os testes:
// [ OK    ] /local/default_ctor
// [ OK    ] /local/param_ctor
// [ OK    ] /local/setters
// [ OK    ] /local/distancia
// 4 of 4 (100%) tests successful, 0 (0%) test skipped.

//Utilize o seguinte comando para compilar e executar os testes: "g++ tests/automated_tests/local_test.cpp src/Local/Local.cpp tests/automated_tests/lib/munit.cpp -Itests/automated_tests/lib/include -Iinclude -o tests/automated_tests/local_test.exe"

// Utilize o seguinte comando para executar os testes: "tests/automated_tests/local_test.exe"