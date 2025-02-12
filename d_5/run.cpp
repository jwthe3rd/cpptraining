#include "utils.H"

#ifndef T
#define T = float;
#endif

int main()
{

    // Instantiate particle list
    int numParticles = 10000;


    LinkedList<Particle<float>> particleSystem;

    for (int i = 0; i < numParticles; i++)
    {
        Particle<float> p;
        p.x = 0.0001*i;
        p.y = 0.0001*i/2;
        p.r = 0.01;
        particleSystem.insertAtEnd(p);
    }


    float render_view_x = 1.0f;
    float render_view_y = 1.0f;

    float origin = 0.0f;


    float allParticleRadii = 0.02f;

    QuadTree<float> qt(Box(origin, origin, render_view_x, render_view_y));

    Node<Particle<float>>* temp = particleSystem.head;

    while (temp)
    {
        qt.insert(temp->data);
        temp = temp->next;
    }

    cout << "QuadTree Points: " << endl;

    qt.print();


    return 0;
}