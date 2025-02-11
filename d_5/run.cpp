#include "utils.H"

int main()
{

    // Instantiate particle list
    int numParts = 20;

    LinkedList<Particle> parts;

    for (int i = 0; i < numParts; i++)
    {
        Particle p;
        p.x = 0.05*i;
        p.y = 0.05*i;
        p.r = 0.01;
        parts.insertAtEnd(p);
    }





    return 0;
}