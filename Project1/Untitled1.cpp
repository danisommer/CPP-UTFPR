#include <iostream>
#include <string>
#include <vector>
#include <poppler-document.h>
#include <poppler-page.h>
#include <xlsxwriter.h>

// Função para extrair datas e horários de um arquivo PDF
void extrairDatasHorariosPDF(const char* nomeArquivoPDF, std::vector<std::string>& datas, std::vector<std::string>& horarios) {
    poppler::document* doc = poppler::document::load_from_file(nomeArquivoPDF);

    if (!doc) {
        std::cerr << "Erro ao abrir o arquivo PDF." << std::endl;
        return;
    }

    for (int i = 0; i < doc->pages(); ++i) {
        poppler::page* page = doc->create_page(i);
        std::string text = page->text().to_latin1();

        size_t pos = 0;
        while ((pos = text.find_first_of("0123456789", pos)) != std::string::npos) {
            // Encontrar data (DD/MM/AAAA)
            std::string data;
            if (sscanf(text.c_str() + pos, "%2d/%2d/%4d", &dia, &mes, &ano) == 3) {
                datas.push_back(data);

                // Procurar horários
                size_t posHorario = text.find("HH:MM", pos);
                if (posHorario != std::string::npos) {
                    std::string horario = text.substr(posHorario, 5);
                    horarios.push_back(horario);
                } else {
                    horarios.push_back("N/A");
                }

                // Procurar o próximo horário
                pos = posHorario + 5;
            } else {
                pos++;
            }
        }
    }

    delete doc;
}

int main() {
    std::string nomeArquivoPDF;
    std::cout << "Digite o nome do arquivo PDF: ";
    std::cin >> nomeArquivoPDF;

    std::vector<std::string> datas;
    std::vector<std::string> horarios;

    extrairDatasHorariosPDF(nomeArquivoPDF.c_str(), datas, horarios);

    // Criar um arquivo Excel e escrever os dados
    lxw_workbook* workbook = workbook_new("dados.xlsx");
    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
    int row = 0;

    for (size_t i = 0; i < datas.size(); ++i) {
        worksheet_write_string(worksheet, row, 0, datas[i].c_str(), NULL);
        worksheet_write_string(worksheet, row, 1, horarios[i].c_str(), NULL);
        row++;
    }

    workbook_close(workbook);

    std::cout << "Os dados foram exportados para dados.xlsx." << std::endl;

    return 0;
}
