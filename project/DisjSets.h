#ifndef DISJ_SETS_H
#define DISJ_SETS_H
//Ahmet Çelik 2009400111

//this code is a modified version of course textbook C++ code for disjSets.

typedef struct 
{
    int size; // size of set. not need indeed.
    int* s;// dynamic array for sets
}DisjSets;

//initilizes disjset.
void init_DisjSets(DisjSets* st,int n)
{	int i;
	st->size=n;
	st->s =(int*) malloc(n*sizeof(int));
	for(  i = 0; i < n; i++ )
          st->s[ i ] = -1;//initializes to  -1
}

int disj_find( DisjSets* st,int x )
{
       int temp= x  ;
       while( st->s[ temp ] >= 0 )
            temp=st->s[temp];       
       return temp;
}

//unions two distinct roots.
void disj_union( DisjSets* st,int root1, int root2 )
{
    if( st->s[ root2 ] < st->s[ root1 ] )  // root2 is deeper
        st->s[ root1 ] = root2;        // Make root2 new root
    else
    {
        if( st->s[ root1 ] == st->s[ root2 ] )
            st->s[ root1 ]--;          // Update height if same
        st->s[ root2 ] = root1;        // Make root1 new root
    }
}
#endif
