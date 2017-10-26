#include"Grid.h"
#include"hash_table.h"

//sunarthsh gia na fortwnei ta hash tables
hash_table* load_hash_table_with_curves(string ,hash_table*,Grid[],int  );
//sunarthsh gia na anoigei to query file kai na vriskei tous LSH NEAREST
void open_querry_file(string ,hash_table*,Grid[],int );
//sunarthsh gia na anoigei to query file kai na vriskei tous TRUE NEAREST
void open_querry_file_and_find_nearest_n(string ,hash_table*,Grid[],int  );
