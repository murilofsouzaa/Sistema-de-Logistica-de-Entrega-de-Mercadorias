# Sistema de Logística de Entrega de Mercadorias (SLEM)

## Desenvolvido por:
- Bernardo Leão Braga  
- Murilo Freitas de Souza  

---

## Descrição
O objetivo deste trabalho é desenvolver um Sistema de Logística de Entrega de Mercadorias utilizando os conceitos de algoritmos e estruturas de dados aprendidos na disciplina de Algoritmos e Estruturas de Dados I.  
O sistema deverá simular o gerenciamento de pedidos, veículos e locais, com foco na manipulação eficiente de dados e na implementação de um algoritmo de roteamento básico.

---

## Vídeo (Pitch)

Segue o link para a demonstração -> https://youtu.be/2iX6lFmHXf4

---

## Especificação das Entidades e Operações

### 1. Cadastro de Locais

```cpp
class Local {
  string nome;  // Identificador único do local, ex: "São Paulo", "Rua A, 123"
  int x;        // Coordenada X numérica
  int y;        // Coordenada Y numérica
}

// Operações CRUD da classe Local
void criar(Local local);            // Cadastrar um novo local
vector<Local> listar();             // Listar todos os locais cadastrados
void atualizar(string nome, Local localAtualizado); // Atualizar local pelo nome
void excluir(string nome);          // Excluir local pelo nome
```
### 1. Cadastro de Veículos
```cpp
class Veiculo {
  string placa;       // Identificador único do veículo
  string modelo;      // Modelo do veículo
  bool status;        // true = disponível, false = ocupado
  Local localAtual;   // Referência ao local atual do veículo
}

// Operações CRUD da classe Veículo
void criar(Veiculo veiculo);              // Cadastrar um novo veículo
vector<Veiculo> listar();                  // Listar todos os veículos cadastrados
void atualizar(string placa, Veiculo veiculoAtualizado);  // Atualizar veículo pela placa
void updateStatus(string placa, bool status);             // Atualizar status do veículo
void updateLocalAtual(string placa, Local local);         // Atualizar local atual do veículo
void excluir(string placa);                // Excluir veículo pela placa
```
### 1. Cadastro de Pedidos
```cpp
class Pedido {
  int id;               // Identificador único do pedido
  Local localDeOrigem;  // Referência ao local de origem
  Local destino;        // Referência ao local de destino
  float pesoDoItem;     // Peso do item em kg
  bool entregue;        // Indica se o pedido foi entregue
}

// Operações CRUD da classe Pedido
void criar(Pedido pedido);                // Cadastrar um novo pedido
vector<Pedido> listar();                   // Listar todos os pedidos cadastrados
void atualizar(int id, Pedido pedidoAtualizado);  // Atualizar pedido pelo ID
void excluir(int id);                      // Excluir pedido pelo ID
```
### Cálculo e Exibição de Rota de Entrega

- Dado um pedido pendente, o sistema deve calcular e mostrar a rota de entrega a partir do veículo disponível mais próximo do local de origem do pedido.
- A distância entre dois locais (cidades, pontos de entrega, etc.) será calculada utilizando a distância euclidiana entre suas coordenadas (X, Y).
- A rota deve indicar o veículo selecionado, o local de origem do pedido, o local de destino do pedido e a distância total percorrida.
