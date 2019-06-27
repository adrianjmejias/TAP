





#include <vector>

#include <map>
#include <unordered_map>



std::vector<int> GenerateRandom(size_t size, std::function<int()> generator){
    std::vector<int> randVec;
    for(int ii= 0; ii< size; ii++){
        randVec.push_back(generator());
    }
    return randVec;
}

int main(){

    std::vector<int> testCases = {100, 10000, 1000000, 1000000000};
    std::unordered_map<int> _umap;
    std::map<int> _map;


    for(auto test : testCases){
        auto vectorTest = GenerateRandom(test, [](){
            int randInt;

            // Generar Random


            return randInt;
        });


        
        {
            size_t iiSize = _map.size() -1;
    
            for(auto &b : testCases){
                _map.insert(b);
            }
            
            for(; iiSize>= 0; iiSize--){
                _map.erase(testCases[ii]);
            }
        }
    
    
        
        {
            size_t iiSize = _umap.size() -1;
            
            for(auto b : testCases){
                _umap.insert(b);
            }
            
            for(; iiSize>= 0; iiSize--){
                _umap.erase(testCases[ii]);
            }
        }
    }






}
