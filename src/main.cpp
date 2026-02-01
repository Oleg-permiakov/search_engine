#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include <vector>
#include <exception>
#include "../gtest_main/googletest/include/gtest/gtest.h"
#include "invertedIndex.h"
#include "searchServer.h"
#include <map>


int main() {
    ConverterJSON searcher;
    try {
        searcher.GetTextDocuments();
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }


    auto input_docs = searcher.GetTextDocuments(); /*обновление текста документов*/

    searcher.GetResponsesLimit(); /*колличество запросов*/
    auto queries_input = searcher.GetRequests(); /*список запросов по словам*/


    InvertedIndex idx;
    idx.UpdateDocumentBase(input_docs);
    for (auto &word: queries_input) {
        auto getList = idx.GetWordCount(word);
    }
    SearchServer search_server(idx);
    auto result = search_server.search(queries_input);

    std::vector<std::vector<std::pair<int, float>>> ans;
    std::vector<std::pair<int, float>> vecAn;
    std::pair<int, float> an;
    for (auto &numVecDocs: result) {
        for (auto relative_index: numVecDocs) {
            an.first = relative_index.docs_id;
            an.second = relative_index.rank;
            vecAn.push_back(an);
        }
        ans.push_back(vecAn);
    }
    searcher.putAnswers(ans);

    return 0;
}
