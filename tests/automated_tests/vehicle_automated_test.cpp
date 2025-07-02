#include "lib/include/munit.hpp"
#include "Veiculo.hpp"

// Teste do construtor
static MunitResult test_veiculo_ctor(const MunitParameter params[], void* data) {
    Veiculo v("ABC1234", "Fiorino", "disponivel", "Centro");
    munit_assert_string_equal(v.placa.c_str(), "ABC1234");
    munit_assert_string_equal(v.modelo.c_str(), "Fiorino");
    munit_assert_string_equal(v.status.c_str(), "disponivel");
    munit_assert_string_equal(v.localAtual.c_str(), "Centro");
    // Esperado: placa="ABC1234", modelo="Fiorino", status="disponivel", localAtual="Centro"
    return MUNIT_OK;
}

// Teste de cadastro de veiculo
static MunitResult test_cadastrarVeiculo(const MunitParameter params[], void* data) {
    // Limpa o vetor global antes do teste
    extern std::vector<Veiculo> veiculos;
    veiculos.clear();

    bool ok = cadastrarVeiculo("XYZ5678", "Kombi", "disponivel", "Bairro A");
    munit_assert_true(ok);
    munit_assert_int(veiculos.size(), ==, 1);
    munit_assert_string_equal(veiculos[0].placa.c_str(), "XYZ5678");
    // Esperado: cadastro com sucesso, veiculos.size() == 1

    // Teste de cadastro duplicado
    ok = cadastrarVeiculo("XYZ5678", "Kombi", "disponivel", "Bairro A");
    munit_assert_false(ok);
    munit_assert_int(veiculos.size(), ==, 1);
    // Esperado: cadastro duplicado falha, veiculos.size() == 1
    return MUNIT_OK;
}

// Teste de atualizar veiculo
static MunitResult test_atualizarVeiculo(const MunitParameter params[], void* data) {
    extern std::vector<Veiculo> veiculos;
    veiculos.clear();
    cadastrarVeiculo("AAA1111", "Uno", "disponivel", "Centro");

    bool ok = atualizarVeiculo("AAA1111", "Uno Novo", "ocupado", "Bairro B");
    munit_assert_true(ok);
    munit_assert_string_equal(veiculos[0].modelo.c_str(), "Uno Novo");
    munit_assert_string_equal(veiculos[0].status.c_str(), "ocupado");
    munit_assert_string_equal(veiculos[0].localAtual.c_str(), "Bairro B");
    // Esperado: modelo="Uno Novo", status="ocupado", localAtual="Bairro B"

    // Atualizar veiculo inexistente
    ok = atualizarVeiculo("ZZZ9999", "X", "X", "X");
    munit_assert_false(ok);
    // Esperado: false para veiculo inexistente
    return MUNIT_OK;
}

// Teste de exclusao de veiculo
static MunitResult test_excluirVeiculo(const MunitParameter params[], void* data) {
    extern std::vector<Veiculo> veiculos;
    veiculos.clear();
    cadastrarVeiculo("BBB2222", "Palio", "disponivel", "Centro");
    bool ok = excluirVeiculo("BBB2222");
    munit_assert_true(ok);
    munit_assert_int(veiculos.size(), ==, 0);
    // Esperado: veiculo removido, veiculos.size() == 0

    ok = excluirVeiculo("INEXISTENTE");
    munit_assert_false(ok);
    // Esperado: false para veiculo inexistente
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char*) "/construtor",         test_veiculo_ctor,        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/cadastrarVeiculo",   test_cadastrarVeiculo,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/atualizarVeiculo",   test_atualizarVeiculo,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/excluirVeiculo",     test_excluirVeiculo,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    (char*) "/veiculo",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}

// Esperado ao rodar todos os testes:
// [OK] /veiculo/construtor
// [OK] /veiculo/cadastrarVeiculo
// [OK] /veiculo/atualizarVeiculo
// [OK] /veiculo/excluirVeiculo

//Para rodar os testes: "g++ tests/automated_tests/veichle_test.cpp src/Veiculo/Veiculo.cpp tests/automated_tests/lib/munit.cpp -Itests/automated_tests/lib/include -Iinclude -o tests/automated_tests/veichle_test.exe"

// Para compilar e executar os testes, use o comando: "./tests/automated_tests/veichle_test.exe" no terminal.
