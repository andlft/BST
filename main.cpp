#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("abce.in");
ofstream fout ("abce.out");

class Node
{
public:
    int nr;
    Node * stanga;
    Node * dreapta;
    Node * parinte;
    Node():nr(0), stanga(nullptr), dreapta(nullptr), parinte(nullptr){}
    Node(int val):nr(val), stanga(nullptr), dreapta(nullptr), parinte(nullptr){}

};


class BST
{
public :

    Node * radacina;

    BST():radacina(nullptr){}


    Node * nod_nou(int val)
    {
        Node * nod_aux = new Node;
        nod_aux->nr = val;
        nod_aux->stanga = nullptr;
        nod_aux->dreapta = nullptr;
        nod_aux->parinte = nullptr;

        return nod_aux;
    }

    void inserare(Node * nod)
    {
        if(radacina == nullptr)
        {
            radacina = nod;//inserare pentru radacina
        }
        else
        {
            Node * nod_aux = radacina;
            while(nod_aux != nullptr)
            {
                if(nod->nr == nod_aux->nr)
                {
                    return;
                }
                else if ((nod->nr < nod_aux->nr)&&(nod_aux->stanga == nullptr))
                {
                    nod_aux->stanga = nod;
                    nod->parinte = nod_aux; //se pune nodul ca fiul stang al nod_aux
                    break;
                }
                else if (nod->nr < nod_aux->nr)
                {
                    nod_aux = nod_aux->stanga;   // se coboara spre stanga
                }
                else if ((nod->nr > nod_aux->nr)&&(nod_aux->dreapta == nullptr))
                {
                    nod_aux->dreapta = nod;    //se pune nodul ca fiul drept al nod_aux
                    nod->parinte = nod_aux;
                    break;
                }
                else
                {
                    nod_aux = nod_aux->dreapta;   //se coboara spre dreapta
                }
            }
        }
    }

    Node * min_nod(Node* nod) //gasirea minimului de sub un nod(numai prin coborare spre stanga)
    {
        if(nod == nullptr)
        {
            return nullptr;
        }
        else if (nod->stanga == nullptr)
        {
            return nod;
        }
        else
        {
            return min_nod(nod->stanga);
        }
    }

    Node * max_nod(Node * nod)  //gasirea maximului de sub un nod (numai prin coborare spre dreapta)
    {
        if(nod == nullptr)
        {
            return nullptr;
        }
        else if (nod->dreapta == nullptr)
        {
            return nod;
        }
        else
        {
            return max_nod(nod->dreapta);
        }
    }

    Node * stergere(Node * nod, int val)
     {

        if (nod == nullptr)
        {
            return nullptr;
        }
        else if (val < nod -> nr)
        {
            nod -> stanga = stergere(nod -> stanga, val);//coborare spre stanga
        }

        else if (val > nod -> nr)
        {
            nod -> dreapta = stergere(nod -> dreapta, val);//coborare spre dreapta
        }

        else
        {

            if (nod -> stanga == nullptr) //caz numai fiu drept
            {
                Node * nod_aux = nod -> dreapta;
                if(nod_aux != nullptr)
                {
                    nod_aux->parinte = nod->parinte;
                }
                delete nod;
                return nod_aux;
            }
            else if (nod -> dreapta == nullptr) //caz numai fiu stang
            {
                Node * nod_aux = nod -> stanga;
                {
                    nod_aux->parinte = nod->parinte;
                }
                delete nod;
                return nod_aux;
            }
            else  // caz doi fii
            {
                Node * nod_aux = min_nod(nod -> dreapta);
                nod -> nr = nod_aux-> nr;
                nod -> dreapta = stergere(nod -> dreapta, nod_aux -> nr);

            }
        }
        return nod;
    }

    Node * cautare(int val)
    {
        if(radacina == nullptr)
        {
            return radacina;
        }
        else
        {
            Node *nod_aux = radacina;
            while(nod_aux != nullptr)
            {
                if(val==nod_aux->nr)
                {
                    return nod_aux;
                }
                else if(val < nod_aux->nr)
                {
                    nod_aux = nod_aux->stanga;  //se coboara spre stanga
                }
                else
                {
                    nod_aux = nod_aux->dreapta;  //se coboara spre dreapta
                }
            }
            return nullptr;
        }
    }

    Node * succesor(int val)
    {
        if(cautare(val)==nullptr) //pentru cazul in care val nu e in arbore (nu cred ca e optim :( )
        {
            while(cautare(val)==nullptr)
            {
                val++;
            }
            return cautare(val);
        }
        else {
            Node *nod = cautare(val);   //gasirea "optima"
            if (nod->dreapta != nullptr) {
                return min_nod(nod->dreapta);
            } else {
                Node *par = nod->parinte;
                while (par != nullptr && par->dreapta == nod) {
                    nod = par;
                    par = par->parinte;
                }
                return par;
            }
        }
    }
    Node * predecesor(int val)
    {
        if(cautare(val)==nullptr)  // pentru cazul in care val nu e in arbore
        {
            while (cautare(val) == nullptr) {
                val--;
            }
            return cautare(val);
        }
        else
        {
            Node *nod = cautare(val); //gasirea "optima"
            if (nod->stanga != nullptr) {
                return max_nod(nod->stanga);
            } else {
                Node *par = nod->parinte;
                while (par != nullptr && par->stanga == nod) {
                    nod = par;
                    par = par->parinte;
                }
                return par;
            }
        }
    }

    void afisareXY(int x, int y)
    {
        while (cautare(x) == nullptr)
        {
            x++;
        }
        Node * nod = cautare(x);
        while(nod->nr < y)
        {
            fout<<nod->nr<<" ";
            Node * suc = succesor(x);
            if(suc->nr == nod->nr)
            {
                break;
            }
            nod = succesor(x);
        }
        fout<<"\n";
    }

    Node * nod_nou()
    {
        return new Node();
    }
};

int main(){
    BST bst;
    int optiune, val, val2;
    int cycles;

    fin>>cycles;
    for (int i = 0; i < cycles; i++)
    {

        fin >> optiune;
        fin >> val;


        if(optiune == 1)
        {
            Node * nod = bst.nod_nou();
            nod->nr = val;
            bst.inserare(nod);
        }
        if(optiune == 2)
        {
            bst.stergere(bst.radacina, val);
        }
        if(optiune == 3)
        {
            fout<<(bst.cautare(val)!=nullptr)<<"\n";
        }
        if(optiune == 4)
        {
            fout<<bst.predecesor(val)->nr<<"\n";
        }
        if(optiune == 5)
        {
            fout<<bst.succesor(val)->nr<<"\n";
        }
        if(optiune == 6)
        {
            fin>>val2;
            bst.afisareXY(val, val2);
        }

    }

    return 0;
}


