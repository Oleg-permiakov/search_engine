#include <iostream>
#include <filesystem>
#include <string>
#include "ConverterJSON.h"
#include <vector>
#include <exception>
#include "invertedIndex.h"
#include "searchServer.h"


int main() {
    ConverterJSON searcher;
    auto input_docs = searcher.GetTextDocuments(); /*обновление текста документов*/
    // std::cout << input_docs.size() << std::endl;
    // for (auto input_doc: input_docs) {
    //     std::cout << input_doc << std::endl;
    // }


    auto rent = searcher.GetResponsesLimit(); /*колличество запросов*/
    std::cout << "Maximum number of request: " << rent << std::endl;

    auto queries_input = searcher.GetRequests(); /*список запросов по словам*/
    // for (auto i : queries_input) {
    //     std::cout << i << std::endl;
    // }

    InvertedIndex idx;
    idx.UpdateDocumentBase(input_docs);
    // auto res = idx.GetWordCount("milk", input_docs);
    // for (auto re: res) {
    //     std::cout << "{"<<re.doc_id<<", "<<re.count<<"}" << std::endl;
    // }

    // auto dict = idx.GetFreqDictionary();
    // for (std::map<std::string, std::vector<Entry>>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
    //     std::cout << it->first << " : ";
    //     for (auto res: it->second) {
    //         std::cout <<"{"<< res.doc_id << ", " << res.count <<"}"<< ", ";
    //     }
    //     std::cout << std::endl;
    // }

/*____________________________________________________________________________________________________*/
    // SearchServer search_server(idx);
    // auto result = search_server.search(queries_input);
    //
    // std::vector<std::vector<std::pair<int, float>>> ans;
    // std::vector<std::pair<int, float>> vecAn;
    // std::pair<int, float> an;
    // for (auto &numVecDocs: result) {
    //     for (auto relative_index: numVecDocs) {
    //         an.first = relative_index.docs_id;
    //         an.second = relative_index.rank;
    //         vecAn.push_back(an);
    //     }
    //     ans.push_back(vecAn);
    // }
    // searcher.putAnswers(ans);
    //
    // return 0;
}
