#include "invertedIndex.h"
#include <thread>

std::vector<Entry> InvertedIndex::getWordCount(std::string &word){
    std::vector<Entry> result;

    if (freqDictionary.find(word)!=freqDictionary.end()){
        
        result=freqDictionary.find(word)->second;
    }
    return result;
}

void InvertedIndex::updateDocumentBase(const std::vector<std::string>&docs){

    size_t id=0;
    std::mutex mtx;
    std::vector <std::thread> threadCreateBase;

    for(std::string doc:docs){

        threadCreateBase.push_back(std::thread ([&, doc, id](){
            
            std::map<std::string,size_t> inputDic;
            std::regex pat{R"((\w+))"};
            for (std::sregex_iterator it(doc.begin(), doc.end(), pat); it!=std::sregex_iterator{}; ++it){

                inputDic[it->str()]++;
            }

            for(auto it = inputDic.cbegin(); it != inputDic.cend(); ++it){
                Entry buf(id,it->second);
                mtx.lock();
                freqDictionary[it->first].push_back(buf);
                mtx.unlock();
            }
        }));

        id++;

    }

    for (auto &thread : threadCreateBase) thread.join ();

}