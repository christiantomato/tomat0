//define nodes for the abstract syntax tree
/*
- variable assignments
- factors vs terms
- identifiers
- statements
*/

#ifndef AST_NODE
#define AST_NODE

//define the enum for all the different types of nodes in the syntax tree
typedef enum ast_node_type {
    AST_DECLARATION,
    AST_FUNCTION_CALL,
    AST_STATEMENTS
} type;

//each node will be of the form (type, children[])
typedef struct ast_node_struct {
    //ast node type
    int type;
    //have a reference to the children (differs depending on the specific type of ast node)
    
    
} ast_node;


#endif