#include "httplib.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

std::string lerArquivo(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    std::stringstream buffer;
    buffer << arquivo.rdbuf();
    return buffer.str();
}

int main() {
    std::string caminhoArquivo = "entrada.txt";  // Nome do arquivo a ser enviado
    std::string conteudo = lerArquivo(caminhoArquivo);

    httplib::Client cliente("http://localhost", 8080); // Endereço do Mestre

    json payload;
    payload["texto"] = conteudo;

    auto resposta = cliente.Post("/processar", payload.dump(), "application/json");

    if (resposta && resposta->status == 200) {
        json resultado = json::parse(resposta->body);
        std::cout << "✅ Resultado recebido do Mestre:\n";
        std::cout << "Letras: " << resultado["letras"] << "\n";
        std::cout << "Números: " << resultado["numeros"] << "\n";
    } else {
        std::cerr << "❌ Erro ao enviar requisição ao Mestre.\n";
    }

    return 0;
}
