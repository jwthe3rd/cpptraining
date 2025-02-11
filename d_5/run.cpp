#include "utils.H"

int main()
{

    // Instantiate particle list
    int numParticles = 100;

    LinkedList<Particle> particleSystem;

    for (int i = 0; i < numParticles; i++)
    {
        Particle p;
        p.x = 0.01*i;
        p.y = 0.01*i/2;
        p.r = 0.01;
        particleSystem.insertAtEnd(p);
    }


    float render_view_x = 1.0f;
    float render_view_y = 1.0f;

    float origin = 0.0f;


    float allParticleRadii = 0.02f;

    Box rootNode;

    rootNode.x_l = origin;rootNode.y_l = origin;
    rootNode.x_u = render_view_x; rootNode.y_u = render_view_y;

    int maxParticleNumber = 4;

    QuadTree qt(rootNode);

    qt.addParticles(particleSystem, maxParticleNumber);

    //cout << qt.quadtree.size() << endl;

    for (Box elem : qt.quadtree)
    {
        cout << "Parent: " << elem.x_u << ", " << elem.x_l << ", " << elem.y_u << ", " << elem.y_l;
        if (elem.children.size()==0)
        {cout << " --> Leaf Node!";}
        cout << endl;
        for (Box *elem2 : elem.children)
        {

        cout << "Child: -----> " << elem2->x_u << ", " << elem2->x_l << ", " << elem2->y_u << ", " << elem2->y_l << endl;
        }
    }





    return 0;
}