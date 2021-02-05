#include <iostream>
#include <fstream>
#include <string>
#include "stack.hpp"
#include "sudoku.hpp"

using namespace std;

int main(int argc, char *argv[]){

    int N,I,J;

    ifstream file (argv[1]);
    if (file.is_open()){
        file >> N >> I >> J;

        //Creating Adjacency matrix
        int** sudoku = new int*[N*N];
        for(int i = 0; i < N*N; i++)
            sudoku[i] = new int[N*N];

        for(int i = 0; i < N*N; i++){
            int aux_line = N;
            while(i>=aux_line)
                aux_line = aux_line + N;

            for(int j = (aux_line-N); j<aux_line; j++)
                sudoku[i][j] = 1;

            int aux_col = i;
            while(aux_col>=0)
                aux_col = aux_col - N;

            aux_col = aux_col + N;
            for(int j = aux_col; j<(N*N); j+=N)
                sudoku[i][j] = 1;


            //Process to walk in desired quadrant only
            int rest = i%N;
            int quoc = i/N;
            
            int quad_l = quoc/J;
            int quad_c = rest/I;

            quad_l = N*J*quad_l;
            quad_c = I*quad_c;

            for(int j = quad_l; j<(quad_l+N*J); j+=N){
                for(int k = quad_c; k<quad_c+I; k++){
                    if(sudoku[i][j+k] != 1)
                       sudoku[i][j+k]=1;
                }
            }

            file >> sudoku[i][i];
        }

        int color[N+1], k;

        Stack mem;
        bool flag = false, final;

        //Loop to walk only in the first quadrant
        for(int a = 0; a < N*J; a+=N){
            for(int i = 0; i < I; i++){

                //Case that color = 0
                if(sudoku[i+a][i+a] == 0){
                    for (int i = 0; i < N+1; i++)
                        color[i] = i;

                    possible_colors(sudoku,color,N,(a+i));

                    k=1;
                    //Find a possible color and try it
                    while(k<=N){
                        if(color[k] != 0){
                            sudoku[i+a][i+a] = color[k];
                            final = solve(sudoku,N,I,J,I,0,(i+a),mem,flag,0,0);
                            if(final)
                                k+=N;
                        }
                        k++;
                    }
                    
                }
                else //Case that the vertex has its own color
                    final = solve(sudoku,N,I,J,I,0,(i+a),mem,flag,0,0);
                
                if(!final)
                    break;
            }
            //if(!final)
              //  break;
        }

        if(final)
            cout << "solucao" << endl;
        else
            cout << "sem solucao" << endl;
        
        int count = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cout << sudoku[count][count] << " ";
                count++;
            }
            cout << endl;
        }
    }
    
    else{
        cout << "Unable to open file" << endl;
        return(1);
    }

    file.close();

    return(0);
}