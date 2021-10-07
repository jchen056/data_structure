#include <iostream>
using namespace std;
#include<string>
#include<vector>
#include<math.h>
#include <fstream>
//used to reads from files
#include <stdio.h>
#include <string.h>
#include <sstream> 

class Atom{
    private:
        int indexN;
        string atom;
        string seq;
        int number;
        double x;
        double y;
        double z;
    public:
    //constructir
        /*Atom(int indexN, string atom,string seq,int number,double x,double y,double z){
            this->indexN=indexN;
            this->atom=atom;
            this->seq=seq;
            this->number=number;
            this->x=x;
            this->y=y;
            this->z=z;
        }*/
    //getters and setters
        int getIndex(){return this->indexN;}
        string getAtom(){return this->atom;}
        string getSeq(){return this->seq;}
        int getNumber(){return this->number;}
        double getX(){return this->x;}
        double getY(){return this->y;}
        double getZ(){return this->z;}
        void setIndex(int n){this->indexN=n;}
        void setAtom(string a){this->atom=a;}
        void setSeq(string s){this->seq=s;}
        void setNumber(int num){this->number=num;}
        void setX(double x){this->x=x;}
        void setY(double y){this->y=y;}
        void setZ(double z){this->z=z;}
    
};

int main()
{   ofstream MyFile("filter.pdb");// Create and open a text file
    MyFile << "ATOM      1  N   ARG     1      63.636  53.551  30.120  1.00  0.00           N\n"<<
    "ATOM      2  H1  ARG     1      64.306  54.131  30.680  1.00  0.00           H\n"<<
    "ATOM      3  H2  ARG     1      64.226  53.261  29.310  1.00  0.00           H\n";// Write to the file
    MyFile.close();// Close the file
    
    
    
    /*read files*/
    vector<string> txt;
    string myText;// Create a text string, which is used to store info temporarily
    ifstream MyReadFile("filter.pdb");// Read from the text file
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
        txt.push_back(myText);
        cout<<myText<<endl;
    }
    MyReadFile.close();// Close the file
    
    

    string o;//useless
    int p;//vector is index;
    string q;//vector is atom
    string r;//vec is seq
    int i;
    double s;//vec is x
    double t;//vec is y
    double v;//vec is z
    double oo;//useless
    double pp;
    string qq;
  
    vector<Atom> mol;
    
 
    ifstream ifs("filter.pdb");
    string line;
    while(getline(ifs,line)){
        stringstream ss(line);
        ss>>o>>p>>q>>r>>i>>s>>t>>v>>oo>>pp>>qq;
            //ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Atom atm=Atom();
        atm.setIndex(p);
        atm.setAtom(q);
        atm.setSeq(r);
        atm.setNumber(i);
        atm.setX(s);
        atm.setY(t);
        atm.setZ(v);
        mol.push_back(atm);
        }
    

    
    
    
    //double zzz=mol[1].getZ();
    //cout<<zzz<<endl;
    
    /*compute distance between points in 3D space*/
    //set mol[0] as the reference point and compute the distance from mol[0] for all points
    int size=mol.size();
    double a=mol[0].getX();
    double b=mol[0].getY();
    double c=mol[0].getZ();
  
  
    /*double aa=mol[1].getX();
    double bb=mol[1].getY();
    double cc=mol[1].getZ();
    cout<<a<<" "<<b<<" "<<c<<" "<<endl;
    cout<<aa<<" "<<bb<<" "<<cc<<" "<<endl;*/
    
    vector<double> distance;
    for(int i=0;i<size;i++){
        double dx=mol[i].getX()-a;
        double dy=mol[i].getY()-b;
        double dz=mol[i].getZ()-c;
        double d=sqrt(dx*dx+dy*dy+dz*dz);
        distance.push_back(d);
    }
    cout<<distance[0]<<endl;
    cout<<distance[1]<<endl;
    cout<<distance[2]<<endl;
    
    /*reduce dimension to 3D*/
    vector<double> xx;
    vector<double> yy;
    vector<double> zz;
    for(int i=0;i<size;i++){
        double dx=mol[i].getX()-a;
        xx.push_back(dx);
        double dy=mol[i].getY()-b;
        yy.push_back(dy);
        double dz=mol[i].getZ()-c;
        zz.push_back(dz);
    }
    //printf("(%f,%f,%f)\n",xx[0],yy[0],zz[0]);
    //printf("(%f,%f,%f)\n",xx[1],yy[1],zz[1]);
    return 0;
}
