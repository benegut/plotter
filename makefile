Plotter: Plotter.cpp Raw_Data.cpp Tools.cpp
	g++ -Wall Tools.cpp Raw_Data.cpp Plotter.cpp -o Plotter -lboost_iostreams -lboost_system -lboost_filesystem -lfftw3 -lm
