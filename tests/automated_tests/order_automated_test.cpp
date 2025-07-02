#include "lib/include/munit.hpp"
#include "Pedido.hpp"
#include "Veiculo.hpp"
#include "Local.hpp"

// Teste do construtor
static MunitResult test_pedido_ctor(const MunitParameter params[], void* data) {
    Pedido p(1, "Origem", "Destino", 5.0f);
    munit_assert_int(p.id, ==, 1);
    munit_assert_string_equal(p.nomeOrigem.c_str(), "Origem");
    munit_assert_string_equal(p.nomeDestino.c_str(), "Destino");
    munit_assert_float(p.peso, ==, 5.0f);
    munit_assert_string_equal(p.placaVeiculo.c_str(), "");
    munit_assert_false(p.entregue);
    // Esperado: id = 1, nomeOrigem = "Origem", nomeDestino = "Destino", peso = 5.0, placaVeiculo = "", entregue = false
    return MUNIT_OK;
}

// Teste de cadastro de pedido
static MunitResult test_cadastrarPedido(const MunitParameter params[], void* data) {
    extern std::vector<Pedido> pedidos;
    pedidos.clear();

    bool ok = cadastrarPedido(2, "A", "B", 10.0f);
    munit_assert_true(ok);
    munit_assert_int(pedidos.size(), ==, 1);
    munit_assert_int(pedidos[0].id, ==, 2);

    // Teste de cadastro duplicado
    ok = cadastrarPedido(2, "A", "B", 10.0f);
    munit_assert_false(ok);
    munit_assert_int(pedidos.size(), ==, 1);
    // Esperado: cadastro duplicado falha, pedidos.size() == 1
    return MUNIT_OK;
}

// Teste de atualizar pedido
static MunitResult test_atualizarPedido(const MunitParameter params[], void* data) {
    extern std::vector<Pedido> pedidos;
    pedidos.clear();
    cadastrarPedido(3, "X", "Y", 2.0f);

    bool ok = atualizarPedido(3, "NovoX", "NovoY", 7.0f);
    munit_assert_true(ok);
    munit_assert_string_equal(pedidos[0].nomeOrigem.c_str(), "NovoX");
    munit_assert_string_equal(pedidos[0].nomeDestino.c_str(), "NovoY");
    munit_assert_float(pedidos[0].peso, ==, 7.0f);

    ok = atualizarPedido(99, "A", "B", 1.0f);
    munit_assert_false(ok);
    // Esperado: false para pedido que nao existe
    return MUNIT_OK;
}

// Teste de exclusao de pedido
static MunitResult test_excluirPedido(const MunitParameter params[], void* data) {
    extern std::vector<Pedido> pedidos;
    pedidos.clear();
    cadastrarPedido(4, "A", "B", 1.0f);
    bool ok = excluirPedido(4);
    munit_assert_true(ok);
    munit_assert_int(pedidos.size(), ==, 0);

    ok = excluirPedido(4);
    munit_assert_false(ok);
    // Esperado: false para pedido que nao existe
    return MUNIT_OK;
}

// Teste de associar pedido a veiculo e finalizar entrega
static MunitResult test_associar_finalizar(const MunitParameter params[], void* data) {
    extern std::vector<Pedido> pedidos;
    extern std::vector<Veiculo> veiculos;
    pedidos.clear();
    veiculos.clear();

    cadastrarPedido(5, "Origem", "Destino", 3.0f);
    cadastrarVeiculo("ABC1234", "Fiorino", "disponivel", "Origem");

    bool ok = associarPedidoVeiculo(5, "ABC1234");
    munit_assert_true(ok);
    munit_assert_string_equal(pedidos[0].placaVeiculo.c_str(), "ABC1234");
    munit_assert_string_equal(veiculos[0].status.c_str(), "ocupado");

    // Teste de finalizar entrega
    ok = finalizarEntrega(5, "ABC1234");
    munit_assert_true(ok);
    munit_assert_true(pedidos[0].entregue);
    munit_assert_string_equal(veiculos[0].status.c_str(), "disponivel");
    munit_assert_string_equal(veiculos[0].localAtual.c_str(), "Destino");

    // Teste de finalizar entrega novamente (deve falhar)
    ok = finalizarEntrega(5, "ABC1234");
    munit_assert_false(ok);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char*) "/construtor",         test_pedido_ctor,         NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/cadastrarPedido",    test_cadastrarPedido,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/atualizarPedido",    test_atualizarPedido,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/excluirPedido",      test_excluirPedido,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/associar_finalizar", test_associar_finalizar,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    (char*) "/pedido",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}

// Esperado ao rodar todos os testes:
// [OK] /pedido/construtor
// [OK] /pedido/cadastrarPedido
// [OK] /pedido/atualizarPedido
// [OK] /pedido/excluirPedido
// [OK] /pedido/associar_finalizar

//Utilize o comando: "g++ tests/automated_tests/order_test.cpp src/Pedido/Pedido.cpp src/Veiculo/Veiculo.cpp src/Local/Local.cpp tests/automated_tests/lib/munit.cpp -Itests/automated_tests/lib/include -Iinclude -o tests/automated_tests/order_test.exe"

//Para executar os testes, use: "./tests/automated_tests/order_test.exe" no terminal
