#include "sudoku.hpp"

//Genereta a vector with all possible colors of a vertex
void possible_colors(int **M, int *V ,int n, int v){
    for(int i=0; i<(n*n); i++){
        if(M[v][i] == 1 && i!=v){
            if(M[i][i] != 0)
                V[(M[i][i])] = 0;
        }
    }
    
}

//Given a color, test if it is valid
bool check_color(int teste, int cor, int **M, int n){
    int V[n+1];
    for (int i = 0; i < n+1; i++)
        V[i] = i;
    possible_colors(M,V,n,teste);
    for(int i=1;i<=n;i++){
        if(V[i] == cor)
            return(true);
    }
    return(false);
}

//Try to solve the Sudoku for a given color
bool solve(int **M, int n, int c, int l, int qc, int ql, int v, Stack p, bool flagR, int Rline, int Rcol){
    bool result=false, aux=false;
    for(int i=ql; i<ql+n*l; i+=n){
        for(int j=qc; j<qc+c; j++){

            if(M[v][i+j] == 0){ //Nonadjacent vertices only

                if(M[i+j][i+j] == M[v][v] && flagR==false){ //matching color
                    aux = true;
                    p.add_stack(i,j,ql,qc,v,1);
                }
                else if(M[i+j][i+j] == 0 && flagR == false){ //color = 0
                    aux = check_color((i+j),M[v][v],M,n);
                    if(aux == true){
                        M[i+j][i+j] = M[v][v];
                        p.add_stack(i,j,ql,qc,v,0);
                    }
                }
                else{  //Vertex removed -> only pass
                    if(i == Rline && j == Rcol)
                        flagR=false;
                }   
            }

            if(aux){

                //Last quadrant
                if((ql+l*n) >= (n*n) && (qc+c) >= n){
                    result = true;
                    return(true);
                }

                //Go to quadrant below
                else if((qc+c)>=n){
                    int line = ql+l*n;
                    result = solve(M,n,c,l,0,line,(i+j),p,flagR,0,0);
                    return(result);
                }

                //Go to the next quadrant
                else{
                    int col = qc+c;
                    result = solve(M,n,c,l,col,ql,(i+j),p,flagR,0,0);
                    return(result);
                }
            }
        }
    }
    //Try to go back to the last vertex written
    if(!result){ 
        No anterior;
        anterior = p.get_first();
        
        if(anterior._refer != (-1)){
            if(M[anterior._refer][anterior._refer] == M[v][v]){
                No rem = p.remove_stack();
                
                //Remove only if the vertex had color = 0
                if(rem._fixo == 0)
                    M[rem._line + rem._column][rem._line + rem._column] = 0;
                 
                flagR = true;
                //Call the function to the vertex removed with a flag
                result = solve(M,n,c,l,rem._qc,rem._ql,rem._refer,p,flagR,rem._line,rem._column);
            }
        }
    }
    return(result);
}