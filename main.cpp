#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "nlohmann_json/include/nlohmann/json.hpp"
#include "ConverterJSON.h"
#include <vector>
#include <exception>
#include "gtest_main/googletest/include/gtest/gtest.h"
#include "invertedIndex.h"
#include "searchServer.h"


int main() {
    ConverterJSON searcher;
    try {
        searcher.setConfig();
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }


    auto listText = searcher.GetTextDocuments(); /*обновление текста документов*/
    searcher.GetResponsesLimit(); /*колличество запросов*/
    auto queries_input = searcher.GetRequests(); /*список запросов*/

    InvertedIndex idx;
    idx.UpdateDocumentBase(listText);
    for (auto &word: queries_input) {
        auto getList = idx.GetWordCount(word);
    }
    auto *search_server = new SearchServer(idx);
    search_server->search(queries_input);
    return 0;
}
