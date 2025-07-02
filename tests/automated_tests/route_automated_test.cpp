#include "lib/include/munit.hpp"
#include "Rota.hpp"
#include "Local.hpp"
#include <vector>
#include <string>
#include <cmath>

// Teste de rota simples com 3 locais em linha
static MunitResult test_rota_simples(const MunitParameter params[], void* data) {
    // Limpa locais globais
    extern Local locais[];
    extern int qtdLocais;
    qtdLocais = 0;

    cadastrarLocal("A", 0.0f, 0.0f);
    cadastrarLocal("B", 1.0f, 0.0f);
    cadastrarLocal("C", 2.0f, 0.0f);

    std::vector<std::string> nomes = {"A", "B", "C"};
    std::vector<std::string> rota = calcularRotaEntrega(nomes);

    munit_assert_int(rota.size(), ==, 3);
    munit_assert_string_equal(rota[0].c_str(), "A");
    munit_assert_string_equal(rota[1].c_str(), "B");
    munit_assert_string_equal(rota[2].c_str(), "C");
    // Esperado: rota A -> B -> C
    return MUNIT_OK;
}

// Teste de rota em quadrado
static MunitResult test_rota_quadrado(const MunitParameter params[], void* data) {
    extern Local locais[];
    extern int qtdLocais;
    qtdLocais = 0;

    cadastrarLocal("A", 0.0f, 0.0f);
    cadastrarLocal("B", 1.0f, 0.0f);
    cadastrarLocal("C", 1.0f, 1.0f);
    cadastrarLocal("D", 0.0f, 1.0f);

    std::vector<std::string> nomes = {"A", "B", "C", "D"};
    std::vector<std::string> rota = calcularRotaEntrega(nomes);

    munit_assert_int(rota.size(), ==, 4);
    munit_assert_string_equal(rota[0].c_str(), "A");
    // O segundo local deve ser B ou D (ambos a mesma distancia de A)
    bool ok = (rota[1] == "B" || rota[1] == "D");
    munit_assert_true(ok);
    // Esperado: rota comeca em A, depois B ou D, depois os outros
    return MUNIT_OK;
}

// Teste de distanciaEntreLocais
static MunitResult test_distancia_entre_locais(const MunitParameter params[], void* data) {
    extern Local locais[];
    extern int qtdLocais;
    qtdLocais = 0;

    cadastrarLocal("X", 0.0f, 0.0f);
    cadastrarLocal("Y", 3.0f, 4.0f);

    extern Local locais[];
    float dist = calcularDistanciaEntreLocais(locais[0], locais[1]);
    munit_assert_float(dist, ==, 5.0f);
    // Esperado: distancia = 5.0
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char*) "/rota_simples",   test_rota_simples,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/rota_quadrado",  test_rota_quadrado,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/distancia",      test_distancia_entre_locais, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    (char*) "/rota",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}

// Esperado ao rodar todos os testes:
// [OK] /rota/rota_simples
// [OK] /rota/rota_quadrado
// [OK] /rota/distancia

//Para compilar: "g++ tests/automated_tests/route_automated_test.cpp src/Rota/Rota.cpp src/Local/Local.cpp tests/automated_tests/lib/munit.cpp -Itests/automated_tests/lib/include -Iinclude -o tests/automated_tests/route_automated_test.exe"

//Para rodar os testes: "tests/automated_tests/route_automated_test.exe" no terminal.