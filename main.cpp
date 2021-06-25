#include <algorithm>
#include <iostream>

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

    public: void fn_DFS(){
        bool b_IsVis[i_Size];
        std::fill(b_IsVis, b_IsVis+ i_Size, false);

        for(int i_Ct =0; i_Ct < i_Size; i_Ct++){
            int i_Ind = fn_GetIndex(cp_Name[i_Ct]);

            if(i_Ind >=0 && i_Ind < i_Size
               && b_IsVis[i_Ind] == false){
                b_IsVis [i_Ind] = true;
                fn_DFSLink(b_IsVis, i_Size, i_Ct);
                std::cout<< cp_Name[i_Ct] << " ";
            }
        }
    }

    public: void fn_DFSLink(bool* bp_IsVis, int i_Size,
                            int i_Curr){
        for(Vet* op_Tmp = cl2p_Ptr[i_Curr]; op_Tmp != nullptr;
            op_Tmp= op_Tmp->clsp_Ptr){
            int i_Ind = fn_GetIndex(op_Tmp->c_Name);
            if(i_Ind >=0 && i_Ind < i_Size
               && bp_IsVis[i_Ind] == false){
                bp_IsVis [i_Ind] = true;
                std::cout<< op_Tmp->c_Name << " ";
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

    o_List.fn_DFS();

    return 0;
}
