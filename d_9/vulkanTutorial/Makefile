CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

vulkanTutorial: main.cpp
	g++ $(CFLAGS) -o vulkanTutorial main.cpp $(LDFLAGS)

.PHONY: test clean

test: vulkanTutorial
	./vulkanTutorial

clean:
	rm -f vulkanTutorial