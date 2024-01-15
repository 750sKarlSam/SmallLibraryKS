#//Primary target
output: SmallLibrary8.0.o
#	//Recompile this file this means anytime SmallLibrary6.0 is change we're going to recompile the file
#	 you can add additional files to recompile them together into the executeable that we have named output//
	g++ SmallLibrary8.0.o -o output


#//How to construct a makefile/ create the .o file. This is saying compile all the code in the file the -c means do not create an executable
 #but compile into an object file that computer can translate and comprehend. This action changes the .cpp to .o for object file
SmallLibrary8.0.o: SmallLibrary8.0.cpp
	g++ -c SmallLibrary8.0.cpp

clean:
#// * = this means match anything// any file with the .o with be be removed//
	rm *.o output

# //Basic structure of a makefile//
# target: dependencies
# 	action