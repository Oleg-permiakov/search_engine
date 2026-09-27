#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "ConverterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"


int main() {
    nlohmann::json config;
    std::ifstream config_file("../config.json");
    config_file >> config;
    const std::string nameStart = config["config"]["name"];
    if (config["config"]["version"] == "0.1") {
        std::cout << nameStart << std::endl;
    } else {
        std::cout << "The correct version is started not" << std::endl;
    }


    ConverterJSON searcher;
    auto input_docs = searcher.GetTextDocuments(); /*обновление текста документов*/

    auto rent = searcher.GetResponsesLimit(); /*колличество запросов*/
    std::cout << "Maximum number of request: " << rent << std::endl;

    auto queries_input = searcher.GetRequests(); /*список запросов по строкам словам*/

    InvertedIndex idx;
    idx.UpdateDocumentBase(input_docs);

    SearchServer search_server(idx);
    auto result = search_server.search(queries_input);

    searcher.putAnswers(result);

    std::string str;
    std::cout << "For continuation, end of the program press any symbol" << std::endl;
    std::cin >> str;

    return 0;
}
