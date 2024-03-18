output: *.cpp *.h
	g++ *.cpp -o output

clean:
	rm *.o output *.out