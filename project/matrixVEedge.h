#ifndef MATRIX_EDGE_H
#define MATRIX_EDGE_H

/*
 * Holds a size*size matrix
 *
 */
typedef struct
{
	int   size;
	int** data;
} Matrix;

/**
 * Initializes matrix pointed by m
 */
void createMatrix(Matrix *m,int n)
{
	int i;
	m->size=n;
	m->data = (int**) malloc(n*sizeof(int*));
        if(m->data==0){ printf("Memory Allocation Error!"); exit(1);}
	for(i=0;i<n;i++)
	{
		m->data[i]= (int*) calloc(n,sizeof(int));
                if(m->data[i]==0){ printf("Memory Allocation Error!"); exit(1);}
	}
}
/**
 * Reads matrix from File pointed by file to matrix pointed by m
 * also returns numbers of edges
 */
int readMatrix(Matrix *m,FILE*file,int n)
{
	int i,j,len=0;
	m->size=n;
	m->data = (int**) malloc(n*sizeof(int*));
        if(m->data==0){ printf("Memory Allocation Error!"); exit(1);}
	for(i=0;i<n;i++)
	{
		m->data[i]= (int*) malloc(n*sizeof(int));
                if(m->data[i]==0){ printf("Memory Allocation Error!"); exit(1);}
		for(j=0;j<n;j++)
		{			
			fscanf (file,"%d",&m->data[i][j]);
            if(m->data[i][j]!=0&&i!=j) len++;//do not count (a,a) edges or zero edges.
		}									//zero edge means it is not present
	}
        return len/2;
}

/**
 * Frees matrix entries and set size to 0.
 */
void clearMatrix(Matrix*m)
{    
    int i;
    int n=m->size;   
    for(i=0;i<n;i++)
    {
        free(m->data[i]);
    }
    free(m->data);
    m->size=0; 
}

/**
 * Write matrix to file.
 * There is additional blank line in the end.
 */
void writeMatrix(Matrix *m,FILE*file)
{
	int i,j; int n= m->size;
	for(i=0;i<n;i++)
	{
		fprintf(file,"%d",m->data[i][0]);
		for(j=1;j<n;j++)
		{			
			fprintf(file," %d",m->data[i][j]);
		}
		fprintf(file,"\n");
	}
}


typedef struct
{
   int ea[3]; //0:vertex1 -- 1:vertex2 -- 2:edge_weight
}edge;

//compare function for qsort
//comparison key is edge_weight
int compare (const void * a, const void * b)
{
  if(((edge*)a)->ea[2] < ((edge*)b)->ea[2]) return -1;
  else if(((edge*)a)->ea[2] > ((edge*)b)->ea[2]) return 1;
  else return 0;  
}
//initialize edge pointed by ed.
void init_edge(edge*ed,int e1,int e2,Matrix*m)
{
	ed->ea[0]=e1; ed->ea[1]=e2; ed->ea[2]=m->data[e1][e2];
}
#endif