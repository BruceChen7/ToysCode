set(stone_src 
    "lexical.cc"
	"stone_ast.cc"
	"parser.cc"  
   )
		  	 
add_subdirectory(test)
add_library(STONE ${stone_src})
