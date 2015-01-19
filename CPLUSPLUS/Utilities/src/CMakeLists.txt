set(utilities_src
	get_first_follow.cc
	logging.cc 
	re_to_nfa.cc 
	)
add_library(Toyscode ${utilities_src})
