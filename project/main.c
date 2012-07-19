//Ahmet Çelik 2009400111
//input is connected undirected graph
//output is a MST of graph

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrixVEedge.h"
#include "DisjSets.h"
#define SONSUZ 0x7FFFFFFF //4-byte maximum signed integer

//algorithm from course textbook
int kruskal(Matrix*result,DisjSets*dset,edge*ex,int len)
{
	int edgeOK=0,i=0,sum=0;
	edge * e =0;
	int v1,v2;
        qsort(ex,len,sizeof(edge), compare);// sorts edge by weights.
        i=0;
	while(edgeOK<(result->size)-1)
	{
		e=&ex[i++]; //selects minimum weighted edge.		
		v1=e->ea[0]; v2=e->ea[1];		
		int v1_eq = disj_find(dset,v1);
		int v2_eq = disj_find(dset,v2);
		if(v1_eq!=v2_eq)//checks their sets
		{
			edgeOK++;//accepted tree
			result->data[v1][v2]=1;//print in result matrix
			result->data[v2][v1]=1;
                        sum+=e->ea[2];  //adds weights to total
			disj_union(dset,v1_eq,v2_eq);//now they are in same set
		}
	}
        return sum;
}

void prim(int* parent,int*near,int*intree,Matrix*graph)
{
	int i,k,len=graph->size;
	for(i=0;i<len;i++)//prepare arrays.
	{
		parent[i]=-1;//hold parents.
		near[i]=SONSUZ;
		intree[i]=0; //indicates whether or not in the tree
	}
	near[0]=0; //choose 0th element
	intree[0]=1;
	int chosen=0;
        int nearest=SONSUZ;//holds nearest element to tree
	for(i=0;i<len;i++)
	{						
		for(k=0;k<len;k++)
		{
                        if(graph->data[chosen][k]>0&&intree[k]==0&&graph->data[chosen][k]<near[k])
                        {//choose an vertex that is not tree but closest to tree.
                                near[k]=graph->data[chosen][k];
				parent[k]=chosen;  
                        }
		}
                nearest=SONSUZ;
                for(k=0;k<len;k++)//search for nearest among vertices not in the tree
		{
			if(intree[k]==0&&near[k]<nearest){
				chosen=k;
                                nearest=near[chosen];
			}
		}
		intree[chosen]=1;
	}
}

int main(int argc,char* argv[])
{
        if(argc!=4)
        { 
            printf("Wrong Arguments!");
            return 1;
        }
        
	FILE * fhand=fopen ( argv[1], "r" );
        if(fhand==0)
        {
            printf("File Open Error.");
            return 1;
        }
	int i,len; fscanf(fhand,"%d",&len);
	Matrix edgeMat; int edgeCount= readMatrix(&edgeMat,fhand,len); 
        fclose(fhand);
	
        if(strcmp(argv[2],"-p")==0)
        {
            int *parent= (int*) malloc(len*sizeof(int)); //holds MST tree as parent array
            int *intree= (int*) malloc(len*sizeof(int));//holds edges in MST
            int *near= (int*) malloc(len*sizeof(int));  //holds distance to MST 
            if(parent==0||intree==0||near==0)
            {
                printf("Memory Allocation Error!"); 
                exit(1);
            }
            fhand=fopen ( argv[3], "w" );
            if(fhand==0){
                printf("File Write Protected or In Use!");
                return 1;
            }
            prim(parent,near,intree,&edgeMat);
            int sum=0;
            Matrix result; createMatrix(&result,len);
            for(i=1;i<len;i++)
            {
                    if(parent[i]!=-1)
                    {
                      result.data[i][parent[i]]=1;result.data[parent[i]][i]=1;
                      sum+=edgeMat.data[i][parent[i]];
                    }
            }  
            fprintf(fhand,"%d\n%d\n",len,sum);            
            writeMatrix(&result,fhand);
            clearMatrix(&result);
            fclose(fhand);
        }
        else if(strcmp(argv[2],"-k")==0)
        {
            //Edge_heap eheap; init_heap(&eheap,len*len/2); 
            edge *ex= (edge*) malloc(edgeCount*sizeof(edge));
            if(ex==0){ printf("Memory Allocation Error!"); exit(1);}
            int n,m,k=0;  
            for(n=0;n<len-1;n++)
            {		//just travels upper triangular of matrix
                    for (m=n+1;m<len;m++)
                    {    
                            if(edgeMat.data[n][m]!=0)
                            {
                                    init_edge(&ex[k],n,m,&edgeMat); 
                                    //insert(&edgeMat,&eheap,&ex[k]);
                                    if(++k==edgeCount) break;
                            }
                    }
                    if(k==edgeCount) break;
            }
            clearMatrix(&edgeMat);
            Matrix result; createMatrix(&result,len); 
            DisjSets dset; init_DisjSets(&dset,len);
        
            fhand=fopen ( argv[3], "w" );
            if(fhand==0){
                printf("File Write Protected or In Use!");
                return 1;
            }
            fprintf(fhand,"%d\n%d\n",len,kruskal(&result,&dset,ex,edgeCount));           
            writeMatrix(&result,fhand);
            clearMatrix(&result);
            fclose(fhand);
        }
        else
        {
            printf("Wrong Arguments!");
            return 1;
        }
    return 0;
}
