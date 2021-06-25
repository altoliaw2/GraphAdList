#include <algorithm>
#include <iostream>
#include <queue>

struct Vet{
    public: char c_Name;
    public: Vet* clsp_Ptr;
};

struct AdList{
    public: Vet** cl2p_Ptr;
    public: char* cp_Name;
    public: int i_Size;

    public: AdList(char* cp_Name, int i_Size){
        cl2p_Ptr= new Vet*[i_Size];
        std::fill(cl2p_Ptr, cl2p_Ptr+ i_Size, nullptr);
        this->cp_Name = cp_Name;
        this->i_Size = i_Size;
    }

    public: bool fn_InsVet(char c_NameA, char c_NameB){
        int i_Ind = -1;
        for(int i_Ct= 0; i_Ct < i_Size; i_Ct++){
            if(c_NameA == cp_Name[i_Ct]){
                i_Ind = i_Ct;
                break;
            }
        }
        if(i_Ind == -1){
            return false;
        }

        Vet* o_Ele  = new Vet();
        o_Ele->c_Name = c_NameB;
        o_Ele->clsp_Ptr = cl2p_Ptr[i_Ind];
        cl2p_Ptr[i_Ind] = o_Ele;

    }

    public: ~AdList(){
        for(int i_Ct =0; i_Ct< i_Size; i_Ct++){
            for(Vet* o_Ele = cl2p_Ptr[i_Ct];
                o_Ele != nullptr;){
                Vet* o_Ele2  = o_Ele->clsp_Ptr;
                delete o_Ele;
                o_Ele = o_Ele2;
            }
        }
        delete [] cl2p_Ptr;
    }

    public: void fn_BFS(){

        bool b_IsVis[i_Size];
        std::fill(b_IsVis, b_IsVis+ i_Size, false);

        std::queue<char> o_Qu;

        for(int i_Ct =0; i_Ct < i_Size; i_Ct++){

            int i_Ind = fn_GetIndex(cl2p_Ptr[i_Ct]->c_Name);

            if(i_Ind >=0 && i_Ind < i_Size
               && b_IsVis[i_Ind] == false){

                o_Qu.push(cl2p_Ptr[i_Ct]->c_Name);
                b_IsVis [i_Ind] = true;

                for(;o_Qu.empty() == false;){
                    std::cout<< o_Qu.front() << " ";
                    o_Qu.pop();

                    for(Vet* o_Tmp = cl2p_Ptr[i_Ct]->clsp_Ptr;
                        o_Tmp != nullptr;
                        o_Tmp = o_Tmp->clsp_Ptr){
                        int i_TmpInd = fn_GetIndex(o_Tmp->c_Name);
                        if(i_TmpInd >=0 && i_TmpInd < i_Size
                           && b_IsVis[i_TmpInd] == false){
                            o_Qu.push(cl2p_Ptr[i_Ct]->c_Name);
                            b_IsVis [i_TmpInd] = true;
                        }
                    }
                }
            }
        }
    }

    private: int fn_GetIndex(char c_Name){
        int i_Ind = -1;
        for(int i_Ct =0; i_Ct < i_Size; i_Ct++){
                if(cp_Name[i_Ct] == c_Name){
                    i_Ind= i_Ct;
                    break;
                }
        }
        return i_Ind;
    }
};

int main(){
    char c_Arr[] = {'A', 'B', 'C', 'D', 'E'};
    int i_Size  = sizeof(c_Arr)/sizeof(char);
    AdList o_List = AdList(c_Arr, i_Size);
    o_List.fn_InsVet('A', 'A');
    o_List.fn_InsVet('A', 'B');
    o_List.fn_InsVet('A', 'C');
    o_List.fn_InsVet('A', 'D');

    o_List.fn_InsVet('B', 'C');
    o_List.fn_InsVet('B', 'E');

    o_List.fn_InsVet('C', 'D');

    o_List.fn_InsVet('D', 'A');

    o_List.fn_InsVet('E', 'C');

    o_List.fn_BFS();

    return 0;
}
