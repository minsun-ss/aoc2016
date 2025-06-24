build:
	@gcc day$(word 2,$(MAKECMDGOALS)).c -o main
	@./main
	@rm main

%:
	@:
