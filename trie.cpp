#include <map>
#include <string>


class node : protected std::map<std::string, node*>
{
    bool terminal = false;

    bool has(char c){



        return false;
    }
};

class Trie {




    bool Load(const std::string path){

        try
        {
            


        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        




        return true;
    }
};



int main(int argc, char const *argv[])
{



    
    return 0;
}
