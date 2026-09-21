#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
#include "kmap.cpp"
using namespace std;

struct Data{
    char name;
    int value[16];
    int valueamount;
}present[4],input[4],nextstate[4],output[4];

struct Circuit{
    string name;
    string content[6600];
}inveter[6600],N[660],function_[660];
int same_N[660];
int psa=1,ina=1,nea=1,oua=1;
int inveteramount=0,andgateamount=0,orgateamount=0,functionamount=0,Namount=0;

void table_to_data(char*);
void make_kmap_in();
void store_kmapout();
void to_bench(char*);
void change_functionname_and_Nname();

int main(int argc,char *argv[])
{   for(int i=0;i<4;i++){
        present[i].name=' ';
        input[i].name=' ';
        nextstate[i].name=' ';
        output[i].name=' ';
    }
    table_to_data(argv[1]);
    make_kmap_in();
    top();
    store_kmapout();
    change_functionname_and_Nname();
    to_bench(argv[2]);
    return 0;
}

void table_to_data(char *a){
    ifstream table_in(a,ios::in);
    //store to presentstate
    string ps;
    table_in >> ps>>ps>>ps;
    for(int i=0;i<ps.length();i++){
        if(ps.at(i)==',')
            psa++;
    }
    for(int i=0;i<psa;i++){
        present[i].name=ps.at(10+i*2);
    }
    if(ps.at(10)=='0'){
        psa=0;
        present[0].name=' ';
    }
    int c=0;
    table_in>> ps;
    while(ps.at(0)!='/'){
        for(int i=0;i<psa;i++){
            present[i].value[c]=stoi(ps);
            present[i].valueamount=c+1;
            table_in>>ps;
        }c++;
    }

    //store to input
    string in=ps;
    for(int i=0;i<in.length();i++){
        if(in.at(i)==',')
            ina++;
    }
    for(int i=0;i<ina;i++){
        input[i].name=in.at(8+i*2);
    }
    if(in.at(8)=='0'){
        ina=0;
        input[0].name=' ';
    }
    c=0;
    table_in>> in;
    while(in.at(0)!='/'){
        for(int i=0;i<ina;i++){
            input[i].value[c]=stoi(in);
            input[i].valueamount=c+1;
            table_in>>in;
        }c++;
    }

    //store to nextstate
    string ne=in;
    for(int i=0;i<ne.length();i++){
        if(ne.at(i)==',')
            nea++;
    }
    for(int i=0;i<nea;i++){
        nextstate[i].name=ne.at(7+i*2);
    }
    if(ne.at(7)==0){
        nea=0;
        nextstate[0].name=' ';
    }
    c=0;
    table_in>> ne;
    while(ne.at(0)!='/'){
        for(int i=0;i<nea;i++){
            nextstate[i].value[c]=stoi(ne);
            nextstate[i].valueamount=c+1;
            table_in>>ne;
        }c++;
    }

    //store to output
    string ou=ne;
    for(int i=0;i<ou.length();i++){
        if(ou.at(i)==',')
            oua++;
    }
    for(int i=0;i<oua;i++){
        output[i].name=ou.at(9+i*2);
    }
    if(ou.at(9)=='0'){
        oua=0;
        output[0].name=' ';
    }
    c=0;
    while(table_in>> ou){
        for(int i=0;i<oua;i++){
            output[i].value[c]=stoi(ou);
            output[i].valueamount=c+1;
        }c++;
    }
}
void make_kmap_in(){
    ofstream kmap_in("kmap_in.txt",ios::out);
    int functionnumber=nea+oua;
    kmap_in << functionnumber<<endl;
    int variablenumber=ina+psa;

    //nextstate function
    if(nextstate[0].valueamount==2){
        for(int i=0;i<nea;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<nextstate[i].value[0]<<' '<<nextstate[i].value[1]<<endl;
        }
    }
    else if(nextstate[0].valueamount==4){
        for(int i=0;i<nea;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<nextstate[i].value[0]<<' '<<nextstate[i].value[1]<<' '<<nextstate[i].value[3]<<' '
                    <<nextstate[i].value[2]<<endl;
        }
    }
    else if(nextstate[0].valueamount==8){
        for(int i=0;i<nea;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<nextstate[i].value[0]<<' '<<nextstate[i].value[1]<<' '<<nextstate[i].value[3]<<' '
                    <<nextstate[i].value[2]<<' '<<nextstate[i].value[4]<<' '<<nextstate[i].value[5]<<' '
                    <<nextstate[i].value[7]<<' '<<nextstate[i].value[6]<<endl;
        }
    }
    else if(nextstate[0].valueamount==16){
        for(int i=0;i<nea;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<nextstate[i].value[0]<<' '<<nextstate[i].value[1]<<' '<<nextstate[i].value[3]<<' '
                    <<nextstate[i].value[2]<<' '<<nextstate[i].value[4]<<' '<<nextstate[i].value[5]<<' '
                    <<nextstate[i].value[7]<<' '<<nextstate[i].value[6]<<' '<<nextstate[i].value[12]<<' '
                    <<nextstate[i].value[13]<<' '<<nextstate[i].value[15]<<' '<<nextstate[i].value[14]<<' '
                    <<nextstate[i].value[8]<<' '<<nextstate[i].value[9]<<' '<<nextstate[i].value[11]<<' '
                    <<nextstate[i].value[10]<<endl;
        }
    }

    //output function
    if(output[0].valueamount==2){
        for(int i=0;i<oua;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<output[i].value[0]<<' '<<output[i].value[1]<<endl;
        }
    }
    else if(output[0].valueamount==4){
        for(int i=0;i<oua;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<output[i].value[0]<<' '<<output[i].value[1]<<' '<<output[i].value[3]<<' '
                    <<output[i].value[2]<<endl;
        }
    }
    else if(output[0].valueamount==8){
        for(int i=0;i<oua;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<output[i].value[0]<<' '<<output[i].value[1]<<' '<<output[i].value[3]<<' '
                    <<output[i].value[2]<<' '<<output[i].value[4]<<' '<<output[i].value[5]<<' '
                    <<output[i].value[7]<<' '<<output[i].value[6]<<endl;
        }
    }
    else if(output[0].valueamount==16){
        for(int i=0;i<oua;i++){
            kmap_in << variablenumber<<endl;
            kmap_in <<output[i].value[0]<<' '<<output[i].value[1]<<' '<<output[i].value[3]<<' '
                    <<output[i].value[2]<<' '<<output[i].value[4]<<' '<<output[i].value[5]<<' '
                    <<output[i].value[7]<<' '<<output[i].value[6]<<' '<<output[i].value[12]<<' '
                    <<output[i].value[13]<<' '<<output[i].value[15]<<' '<<output[i].value[14]<<' '
                    <<output[i].value[8]<<' '<<output[i].value[9]<<' '<<output[i].value[11]<<' '
                    <<output[i].value[10]<<endl;
        }
    }
}
void store_kmapout(){
    ifstream kmap_out("kmap_out.txt",ios::in);
    string namearr[100];
    char digitarr[100];
    for(int i=0;i<psa;i++){
        namearr[i]=present[i].name;
    }
    for(int i=psa;i<ina+psa;i++){
        namearr[i]=input[i-psa].name;
    }

    //store N
    int c=0,n=1,fn=0;
    while(kmap_out>>digitarr[0]){
        if(digitarr[0]=='#'){
            kmap_out>>digitarr[0]>>digitarr[0];
            functionamount++;
            c=0;
            fn=0;
        }
        else{
            fn++;
        }
        for(int i=1;i<psa+ina;i++){
            kmap_out>>digitarr[i];
        }
        for(int i=0;i<psa+ina;i++){
            N[andgateamount].name="N"+to_string(n);
            if(digitarr[i]=='0'){
                inveter[inveteramount].name="!"+namearr[i];
                inveteramount++;
                N[andgateamount].content[i]="!"+namearr[i];
            }
            else if(digitarr[i]=='1'){
                N[andgateamount].content[i]=namearr[i];
            }
        }andgateamount++;c++,n=n+1;
        function_[functionamount-1].content[c-1]=N[andgateamount-1].name;
        if(fn==1)
            orgateamount++;
    }

}
void change_functionname_and_Nname(){
    int x=0,x2;
    string buf;
    Namount=andgateamount;
    for(int i=0;i<andgateamount;i++){
        x=0;
        for(int j=0;j<100;j++){
            if(N[i].content[j]!=""){
                x++;
                buf=N[i].content[j];
                x2=i;
            }
        }
        if(x==1){
            andgateamount--;
            for(int k1=0;k1<functionamount;k1++){
                    for(int k2=0;k2<100;k2++){
                        if(function_[k1].content[k2]==N[x2].name)
                            function_[k1].content[k2]=buf;
                    }
                }
                N[i].name=buf;
        }
    }

    //deal with same N
    int c=0;
    for(int i=0;i<andgateamount-1;i++){
        for(int j=i+1;j<andgateamount;j++){
            if(N[i].content[0]==N[j].content[0]&&N[i].content[1]==N[j].content[1]&&N[i].content[2]==N[j].content[2]&&N[i].content[3]==N[j].content[3]){
                for(int k1=0;k1<functionamount;k1++){
                    for(int k2=0;k2<100;k2++){
                        if(function_[k1].content[k2]==N[j].name)
                            function_[k1].content[k2]=N[i].name;
                    }
                }
                same_N[c]=j;
                c++;
                N[j]=N[i];
                andgateamount--;
            }
        }
    }

    //delete the same invetername
    for(int i=0;i<inveteramount-1;i++){
        for(int j=i+1;j<inveteramount;j++){
            if(inveter[j].name==inveter[i].name){
                inveter[j].name="";
            }
        }
    }
}
void to_bench(char *b){
    ofstream circuit(b,ios::out);
    //write nodes
    circuit << '#' <<' '<< ina << " input";
    if(ina>1)
        circuit<<'s';
    circuit<<endl;

    circuit << '#' <<' '<< oua << " output";
    if(oua>1)
        circuit<<'s';
    circuit<<endl;

    circuit << '#' <<' ' << inveteramount << " inveter";
    if(inveteramount>1)
        circuit<<'s';
    circuit<<endl;

    circuit << '#' <<' '<< psa << " flip-flop";
    if(psa>1)
        circuit<<'s';
    circuit<<endl;

    circuit << '#' <<' ' << andgateamount+orgateamount << " gate";
    if(andgateamount+orgateamount>1)
        circuit<<'s';

    circuit<< '('<<andgateamount<<" AND";
    if(andgateamount>1)
        circuit<<'s';
    circuit<<'+'<<orgateamount<<" OR";
    if(orgateamount>1)
        circuit<<'s';
    circuit<<')'<<endl<<endl;

    //write inputs
    for(int i=0;i<ina;i++){
        if(input[i].name!=' ')
            circuit<< "INPUT("<<input[i].name<<')'<<endl;
    }
    if(input[0].name!=' ')
        circuit<<endl;

    //write output
    for(int i=0;i<oua;i++){
        if(output[i].name!=' ')
            circuit<< "OUTPUT("<<output[i].name<<')'<<endl;
    }
    if(output[0].name!=' ')
        circuit<<endl;

    //write inveter
    for(int i=0;i<inveteramount;i++){
        if(inveter[i].name!="")
            circuit<< inveter[i].name<<" = NOT("<<inveter[i].name[1]<<')'<<endl;
    }

    //write N
    int sameornot=0;
    for(int i=0;i<Namount-oua;i++){
        sameornot=0;
        for(int j=0;j<Namount;j++){
            if(i==same_N[j]){
                sameornot=1;
                break;
            }
        }
        if(i==0)
            sameornot=0;
        if(N[i].name!=""&&N[i].name.at(0)=='N'&&sameornot==0){
            circuit<< N[i].name<<" = AND(";
            for(int j=0;j<4;j++){
                if(N[i].content[j]!="")
                    circuit<< N[i].content[j]<<',';
            }
            circuit.seekp(-1,ios::cur);
            circuit<<')'<<endl;
        }
    }

    //write D
    for(int i=0;i<nea;i++){
        if(present[0].name!=' '){
            circuit<< 'D'<<present[i].name<<" = OR(";
            for(int j=0;j<4;j++){
                if(function_[i].content[j]!="")
                    circuit<< function_[i].content[j]<<',';
            }
            circuit.seekp(-1,ios::cur);
            circuit<<')'<<endl;
        }
    }

    //write state
    for(int i=0;i<psa;i++){
        if(present[i].name!=' '){
            circuit<< present[i].name<<" = D(D"<< present[i].name<<",CLK)"<<endl;
        }
    }

    //write output result
    for(int i=0;i<oua;i++){
        if(output[i].name!=' '){
            if(function_[i+nea].content[1]==""){
                circuit<< output[i].name<<" = AND(";
                for(int j=0;j<4;j++){
                    if(N[andgateamount+nea+i-2].content[j]!="")
                        circuit<< N[andgateamount+nea+i-2].content[j]<<',';
                }
                circuit.seekp(-1,ios::cur);
                circuit<<')'<<endl;
            }
            else if(function_[i+nea].content[1]!=""){
                circuit<< output[i].name<<" = OR(";
                for(int j=0;j<660;j++){
                    if(function_[i+nea].content[j]!="")
                        circuit<< function_[i+nea].content[j]<<',';
                }
                circuit.seekp(-1,ios::cur);
                circuit<<')'<<endl;
            }
        }
    }
    circuit<<"#END";
}
